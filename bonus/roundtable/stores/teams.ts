export const useTeamsStore = defineStore('teams', {
  state: () => {
    return {
      teams: [] as Team[]
    }
  },
  getters: {
    getTeams(): Team[] { return this.teams }
  },
  actions: {
    fetchTeams() {
      const userStore = useUserStore()

      if (!userStore.isLogged)
        return
      fetch('http://127.0.0.1:8080/teams', {
        method: 'GET',
        headers: {
          'Authorization': `Bearer ${userStore.currentUser?.uuid}`
        }
      })
        .then(res => res.json())
        .then((teamsIn: {team_uuid: string, team_name: string, team_description: string}[]) => {
          this.teams = teamsIn.map(team => ({
            uuid: team.team_uuid,
            name: team.team_name,
            description: team.team_description,
            subscribers: []
          }))

          for (const team of this.teams) {
            fetch('http://127.0.0.1:8080/teams/users?team-uuid=' + team.uuid, {
              method: 'GET',
              headers: {
                'Authorization': `Bearer ${userStore.currentUser?.uuid}`,
              }
            }).catch()
              .then(res => res.json())
              .then((subscribers: {uuid: string, username: string, status: string}[]) => {
                team.subscribers = subscribers.map(subscriber => subscriber.uuid)
              })
          }
        })
    },
    getTeam(uuid: string): Team | undefined {
      return this.teams.find(team => team.uuid === uuid)
    },
    isSubscribed(team: Team): boolean {
      const userStore = useUserStore()
      return team.subscribers.includes(userStore.currentUser?.uuid || '')
    },
    joinTeam(team: Team) {
      const userStore = useUserStore()
      fetch('http://127.0.0.1:8080/teams/join', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${userStore.currentUser?.uuid}`
        },
        body: JSON.stringify({team_uuid: team.uuid})
      }).then(value => {
        if (value.status === 204) {
          team.subscribers.push(userStore.currentUser?.uuid || '')
        }
      })
    }
  }
})

export interface Team {
  uuid: string
  name: string
  description: string
  subscribers: string[]
}
