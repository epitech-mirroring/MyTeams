export const useTeamsStore = defineStore('teams', {
  state: () => {
    return {
      teams: [] as Team[]
    }
  },
  getters: {
    getTeams(): Team[] { return this.teams },
    getTeam: (state) => (uuid: string) => state.teams.find(team => team.uuid === uuid),
    isSubscribed: (state) => (uuid: string, team: Team) => {
      const t = state.teams.find(t => t.uuid === team.uuid)
      return t ? t.subscribers.includes(uuid) : false
    }
  },
  actions: {
    addTeam(team: Team) {
      if (!this.teams.find(t => t.uuid === team.uuid))
        this.teams.push(team)
    },
    removeTeam(uuid: string) {
      const index = this.teams.findIndex(team => team.uuid === uuid)
      if (index !== -1) {
        this.teams.splice(index, 1)
      }
    },
    addSubscriber(uuid: string, team: Team) {
      const t = this.teams.find(t => t.uuid === team.uuid)
      if (t && !t.subscribers.includes(uuid))
        t.subscribers.push(uuid)
    },
    removeSubscriber(uuid: string, team: Team) {
      const t = this.teams.find(t => t.uuid === team.uuid)
      if (t) {
        const index = t.subscribers.findIndex(sub => sub === uuid)
        if (index !== -1) {
          t.subscribers.splice(index, 1)
        }
      }
    },
    addChannel(team: Team, channel: Channel) {
      const t = this.teams.find(t => t.uuid === team.uuid)
      if (t && !t.channels.find(c => c.uuid === channel.uuid))
        t.channels.push(channel)
    },
    removeChannel(team: Team, uuid: string) {
      const t = this.teams.find(t => t.uuid === team.uuid)
      if (t) {
        const index = t.channels.findIndex(c => c.uuid === uuid)
        if (index !== -1) {
          t.channels.splice(index, 1)
        }
      }
    },
    addThread(team: Team, channel: Channel, thread: Thread) {
      const t = this.teams.find(t => t.uuid === team.uuid)
      if (t) {
        const c = t.channels.find(c => c.uuid === channel.uuid)
        if (c && !c.threads.find(th => th.uuid === thread.uuid))
          c.threads.push(thread)
      }
    },
    removeThread(team: Team, channel: Channel, uuid: string) {
      const t = this.teams.find(t => t.uuid === team.uuid)
      if (t) {
        const c = t.channels.find(c => c.uuid === channel.uuid)
        if (c) {
          const index = c.threads.findIndex(th => th.uuid === uuid)
          if (index !== -1) {
            c.threads.splice(index, 1)
          }
        }
      }
    },
  }
})

export interface Message {
  sender_uuid: string
  content: string
}

export interface Thread {
  uuid: string
  sender_uuid: string
  title: string
  content: string
  timestamp: number
  messages: Message[]
}

export interface Channel {
  uuid: string
  name: string
  description: string
  threads: Thread[]
}

export interface Team {
  uuid: string
  name: string
  description: string
  subscribers: string[]
  channels: Channel[]
}
