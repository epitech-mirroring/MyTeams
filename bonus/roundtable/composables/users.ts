import type { Channel, Team } from "~/stores/teams";
import { type User, UserStatus, useUsersStore } from "~/stores/users";
import { refreshAll } from "~/composables/teams";

export const loginWithUsername = async (username: string) => {
  const r: {user_uuid: string} = await fetch('http://127.0.0.1:8080/login', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({username})
  }).then(res => res.json())

  const userStore = useUsersStore()
  userStore.setUser({uuid: r.user_uuid, username: username, status: UserStatus.ONLINE})
  await refreshAll();
  setInterval(refreshAll, 5000)
}

export const logout = () => {
  const userStore = useUsersStore()

  fetch('http://127.0.0.1:8080/logout', {
    method: 'POST',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
    }
  }).then(() => {
    userStore.setUser(null)
  })
}

export const refreshUsers = async () => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const resp: User[] = await fetch('http://127.0.0.1:8080/users', {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
    }
  }).then(res => res.json())
    .then(users => {
      return users.map((user: { uuid: string, name: string, status: string }) => {
        return {
          uuid: user.uuid,
          username: user.name,
          status: user.status as UserStatus
        } as User
      })
    })

  resp.forEach(user => {
    userStore.addUser(user)
  })
}

export const isUserSubscribed = async (team: Team | undefined) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  if (!team || !userStore.currentUser)
    return false
  const r: {subscribed: boolean} = await fetch(`http://127.0.0.1:8080/teams/is-subscribed?team-uuid=${team.uuid}`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}`
    },
  }).then(res => res.json())

  if (r.subscribed)
    teams.addSubscriber(userStore.currentUser.uuid, team)
  else
    teams.removeSubscriber(userStore.currentUser.uuid, team)

  return r.subscribed
}
