import type { Channel, Team, Thread } from "~/stores/teams";

export const refreshThreadsOfChannel = async (team: Team, channel: Channel) => {
  const teams = useTeamsStore()
  const userStore = useUsersStore()

  const hasSubscribed = await isUserSubscribed(team)
  if (!hasSubscribed)
    return
  const resp: Thread[] = await fetch(`http://127.0.0.1:8080/teams/channels/threads?team-uuid=${team.uuid}&channel-uuid=${channel.uuid}`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
    }
  }).then(res => res.json())
    .then(threads => {
      return threads.map((thread: { thread_uuid: string, sender_uuid: string, title: string, message: string, timestamp: number }) => {
        return {
          uuid: thread.thread_uuid,
          sender_uuid: thread.sender_uuid,
          title: thread.title,
          content: thread.message,
          timestamp: thread.timestamp,
          messages: []
        } as Thread
      })
    })

  resp.forEach(thread => {
    teams.addThread(team, channel, thread)
  })
}

export const createThread = async (team: Team, channel: Channel, title: string, content: string) => {
  const userStore = useUsersStore()

  const isSubscribed = await isUserSubscribed(team)
  if (!isSubscribed)
    return
  const created: { thread_uuid: string, timestamp: number } = await fetch('http://127.0.0.1:8080/teams/channels/threads/create', {
    method: 'POST',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`,
    },
    body: JSON.stringify({
      team_uuid: team.uuid,
      channel_uuid: channel.uuid,
      title,
      message: content,
    })
  }).then(r => r.json())

  const thread: Thread = {
    uuid: created.thread_uuid,
    sender_uuid: userStore.currentUser!.uuid,
    title,
    content,
    timestamp: created.timestamp,
    messages: []
  }
  useTeamsStore().addThread(team, channel, thread)
}

export const refreshThreads = async () => {
  const teams = useTeamsStore()

  for (const team of teams.getTeams) {
    for (const channel of team.channels) {
      await refreshThreadsOfChannel(team, channel)
    }
  }
}
