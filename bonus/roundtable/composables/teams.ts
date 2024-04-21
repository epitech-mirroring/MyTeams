import type { Team } from "~/stores/teams";
import type { UserStatus } from "~/stores/users";
import { refreshChannels } from "~/composables/channels";
import { refreshThreads } from "~/composables/threads";
import { refreshConversations } from "~/composables/messages";

export const refreshTeams = async () => {
  const teams = useTeamsStore()
  const userStore = useUsersStore()

  const resp: Team[] = await fetch(`${useRuntimeConfig().public.SERVER_URL}/teams`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    }
  }).then(res => res.json())
    .then(teams => teams.map((team: { team_uuid: string, team_name: string, team_description: string }) => {
      return {
        uuid: team.team_uuid,
        name: team.team_name,
        description: team.team_description,
        subscribers: [],
        channels: []
      } as Team
    }))

  resp.forEach(team => teams.addTeam(team))

  const teamUuids = resp.map(team => team.uuid)
  const teamsInStore = teams.getTeams.map(team => team.uuid)
  teamsInStore.forEach(uuid => {
    if (!teamUuids.includes(uuid))
      teams.removeTeam(uuid)
  })
}

export const refreshSubscribersOfTeam = async (team: Team) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const hasSubscribed = await isUserSubscribed(team)
  if (!hasSubscribed)
    return
  const resp: {uuid: string, username: string, status: UserStatus}[] = await fetch(`${useRuntimeConfig().public.SERVER_URL}/teams/users?team-uuid=${team.uuid}`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    }
  }).then(res => res.json())

  resp.forEach(user => {
    userStore.addUser(user)
    teams.addSubscriber(user.uuid, team)
  })

  // Get subscribers in store to remove those who are not in the response
  const subscribers = teams.getTeam(team.uuid)?.subscribers || []
  subscribers.forEach(sub => {
    if (!resp.find(u => u.uuid === sub)) {
      console.log('Removing subscriber', sub)
      teams.removeSubscriber(sub, team)
    }
  })
}

export const refreshSubscribers = async () => {
  const teams = useTeamsStore()

  for (const team of teams.getTeams) {
    await refreshSubscribersOfTeam(team)
  }
}

export const refreshAll = async () => {
  await refreshUsers()
  await refreshTeams()
  await refreshSubscribers()
  await refreshChannels()
  await refreshThreads()
  await refreshConversations()
}

export const joinTeam = async (team: Team) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const resp = await fetch(`${useRuntimeConfig().public.SERVER_URL}/teams/join`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    },
    body: JSON.stringify({team_uuid: team.uuid})
  }).then()

  if (resp.ok && userStore.currentUser)
    teams.addSubscriber(userStore.currentUser.uuid, team)
}

export const leaveTeam = async (team: Team) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const resp = await fetch(`${useRuntimeConfig().public.SERVER_URL}/teams/leave`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    },
    body: JSON.stringify({team_uuid: team.uuid})
  }).then()

  if (resp.ok && userStore.currentUser)
    teams.removeSubscriber(userStore.currentUser.uuid, team)
}

export const createTeam = async (name: string, description: string) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const resp: {team_uuid: string} = await fetch(`${useRuntimeConfig().public.SERVER_URL}/teams/create`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    },
    body: JSON.stringify({name, description})
  }).then(res => res.json())

  teams.addTeam({
    uuid: resp.team_uuid,
    name,
    description,
    subscribers: [],
    channels: []
  })
}
