export const useUsersStore = defineStore('users', {
  state: () => {
    return {
      // for initially empty lists
      userList: [] as User[],
      // for data that is not yet loaded
      user: null as User | null,
    }
  },
  getters: {
    // for computed properties
    onlineUsers(): User[] {
      return this.userList.filter(user => user.status === UserStatus.ONLINE)
    },
    currentUser(): User | null {
      return this.user
    },
    isLogged(): boolean {
      return !!this.user
    },
    getUser: (state) => (uuid: string) => state.userList.find(user => user.uuid === uuid)
  },
  actions: {
    // for methods that modify state
    setUser(user: User | null) {
      this.user = user
    },
    addUser(user: User) {
      if (!this.userList.find(u => u.uuid === user.uuid))
        this.userList.push(user)
      else {
        const u = this.userList.find(u => u.uuid === user.uuid)
        if (u) {
          u.status = user.status
        }
      }
    },
    removeUser(uuid: string) {
      const index = this.userList.findIndex(user => user.uuid === uuid)
      if (index !== -1) {
        this.userList.splice(index, 1)
      }
    },
    updateUserStatus(uuid: string, status: UserStatus) {
      const user = this.userList.find(user => user.uuid === uuid)
      if (user) {
        user.status = status
      }
    }
  }
})

export enum UserStatus {
  ONLINE = 'ONLINE',
  OFFLINE = 'OFFLINE',
  AWAY = 'AWAY',
}

export interface User {
  uuid: string
  username: string
  status: UserStatus
}
