import type { Channel, Team } from "~/stores/teams";
import { type User, UserStatus, useUsersStore } from "~/stores/users";
import { refreshAll } from "~/composables/teams";

export const loginWithUsername = async (username: string) => {
  const r: {user_uuid: string, instance_id: number} = await fetch(`${useRuntimeConfig().public.SERVER_URL}/login`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({username})
  }).then(res => res.json())

  const userStore = useUsersStore()
  userStore.setUser({uuid: r.user_uuid, username: username, status: UserStatus.ONLINE, instance_id: r.instance_id})
  await refreshAll();
  setInterval(refreshAll, 5000)
}

export const logout = () => {
  const userStore = useUsersStore()

  fetch(`${useRuntimeConfig().public.SERVER_URL}/logout`, {
    method: 'POST',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    }
  }).then(() => {
    userStore.setUser(null)
  })
}

export const refreshUsers = async () => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  const resp: User[] = await fetch(`${useRuntimeConfig().public.SERVER_URL}/users`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
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

  const userUuids = resp.map(u => u.uuid)
  const usersInStore = userStore.userList.map(u => u.uuid)

  usersInStore.forEach(uuid => {
    if (!userUuids.includes(uuid))
      userStore.removeUser(uuid)
  })
}

export const isUserSubscribed = async (team: Team | undefined) => {
  const userStore = useUsersStore()
  const teams = useTeamsStore()

  if (!team || !userStore.currentUser)
    return false
  const r: {subscribed: boolean} = await fetch(`${useRuntimeConfig().public.SERVER_URL}/teams/is-subscribed?team-uuid=${team.uuid}`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    },
  }).then(res => res.json())

  if (r.subscribed)
    teams.addSubscriber(userStore.currentUser.uuid, team)
  else
    teams.removeSubscriber(userStore.currentUser.uuid, team)

  return r.subscribed
}

export const updateStatus = async (status: UserStatus) => {
  const userStore = useUsersStore()

  if (!userStore.isLogged)
    return
  const resp = await fetch(`${useRuntimeConfig().public.SERVER_URL}/status`, {
    method: 'POST',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser!.uuid}_${userStore.currentUser?.instance_id}`
    },
    body: JSON.stringify({status})
  }).then()

  if (resp.ok)
    userStore.updateUserStatus(userStore.currentUser!.uuid, status)
}

export const getAvatar = (user: User | undefined) => {
  const style = 'micah'
  const api = `https://api.dicebear.com/8.x/${style}/svg?flip=true&seed=`

  if (!user)
    return `${api}anonymous`
  if (user.username === 'Axel')
    return `${api}o`
  return `${api}${user.username}`
}
