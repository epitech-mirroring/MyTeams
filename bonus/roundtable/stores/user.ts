export const useUserStore = defineStore('user', {
  state: () => {
    return {
      // for initially empty lists
      userList: [] as UserInfo[],
      // for data that is not yet loaded
      user: null as UserInfo | null,
    }
  },
  getters: {
    // for computed properties
    onlineUsers(): UserInfo[] {
      return this.userList.filter(user => user.status === UserStatus.ONLINE)
    },
    currentUser(): UserInfo | null {
      return this.user
    },
    isLogged(): boolean {
      return !!this.user
    }
  },
  actions: {
    // for methods that modify the state
    login(username: string) {
      fetch('http://127.0.0.1:8080/login', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username })
      })
        .then(res => res.json())
        .then((user: {user_uuid: string}) => {
          console.log('Logged in as', username)
          this.user = { uuid: user.user_uuid, username, status: UserStatus.ONLINE }
        })
    },
    logout() {
      console.log('Logged out')
      fetch('http://127.0.0.1:8080/logout', {
        method: 'POST',
        headers: {
          'Authorization': `Bearer ${this.user?.uuid}`
        },
      }).then()
      this.user = null
    },
  }
})

enum UserStatus {
  ONLINE = 'ONLINE',
  OFFLINE = 'OFFLINE',
  AWAY = 'AWAY',
}

interface UserInfo {
  uuid: string
  username: string
  status: UserStatus
}
