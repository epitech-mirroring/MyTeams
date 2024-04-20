import type { Channel, Team } from "~/stores/teams";

export const refreshChannelsOfTeam = async (team: Team) => {
  const teams = useTeamsStore()
  const userStore = useUsersStore()

  const hasSubscribed = await isUserSubscribed(team)
  if (!hasSubscribed)
    return
  const resp: Channel[] = await fetch(`http://127.0.0.1:8080/teams/channels?team-uuid=${team.uuid}`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
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
}

export const refreshChannels = async () => {
  const teams = useTeamsStore()

  for (const team of teams.getTeams) {
    await refreshChannelsOfTeam(team)
  }
}
