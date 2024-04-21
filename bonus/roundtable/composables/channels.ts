import type { Channel, Team } from "~/stores/teams";

export const refreshChannelsOfTeam = async (team: Team) => {
  const teams = useTeamsStore()
  const userStore = useUsersStore()

  const hasSubscribed = await isUserSubscribed(team)
  if (!hasSubscribed)
    return
  const resp: Channel[] = await fetch(`${useRuntimeConfig().public.SERVER_URL}/teams/channels?team-uuid=${team.uuid}`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    }
  }).then(res => res.json())
    .then(channels => {
      return channels.map((channel: { uuid: string, name: string, description: string }) => {
        return {
          uuid: channel.uuid,
          name: channel.name,
          description: channel.description,
          threads: []
        } as Channel
      })
    })

  resp.forEach(channel => {
    teams.addChannel(team, channel)
  })

  const channelUuids = resp.map(channel => channel.uuid)
  const channelsInStore = teams.getChannels(team.uuid).map(channel => channel.uuid)
  channelsInStore.forEach(uuid => {
    if (!channelUuids.includes(uuid))
      teams.removeChannel(team, uuid)
  })
}

export const refreshChannels = async () => {
  const teams = useTeamsStore()

  for (const team of teams.getTeams) {
    await refreshChannelsOfTeam(team)
  }
}

export const createChannel = async (team: Team, name: string, description: string) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const resp: {channel_uuid: string} = await fetch(`${useRuntimeConfig().public.SERVER_URL}/teams/channels/create`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
    },
    body: JSON.stringify({
      team_uuid: team.uuid,
      name,
      description
    })
  }).then(res => res.json())

  teams.addChannel(team, {
    uuid: resp.channel_uuid,
    name: name,
    description: description,
    threads: []
  })
}
