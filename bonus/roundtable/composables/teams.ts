import type { Team } from "~/stores/teams";
import type { UserStatus } from "~/stores/users";
import { refreshChannels } from "~/composables/channels";
import { refreshThreads } from "~/composables/threads";

export const refreshTeams = async () => {
  const teams = useTeamsStore()
  const userStore = useUsersStore()

  const resp: Team[] = await fetch('http://127.0.0.1:8080/teams', {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
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
}

export const refreshSubscribersOfTeam = async (team: Team) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const hasSubscribed = await isUserSubscribed(team)
  if (!hasSubscribed)
    return
  const resp: {uuid: string, username: string, status: UserStatus}[] = await fetch(`http://127.0.0.1:8080/teams/users?team-uuid=${team.uuid}`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
    }
  }).then(res => res.json())

  resp.forEach(user => {
    userStore.addUser(user)
    teams.addSubscriber(user.uuid, team)
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
}

export const joinTeam = async (team: Team) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const resp = await fetch(`http://127.0.0.1:8080/teams/join`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
    },
    body: JSON.stringify({team_uuid: team.uuid})
  }).then()

  if (resp.ok && userStore.currentUser)
    teams.addSubscriber(userStore.currentUser.uuid, team)
}

export const leaveTeam = async (team: Team) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const resp = await fetch(`http://127.0.0.1:8080/teams/leave`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
    },
    body: JSON.stringify({team_uuid: team.uuid})
  }).then()

  if (resp.ok && userStore.currentUser)
    teams.removeSubscriber(userStore.currentUser.uuid, team)
}
