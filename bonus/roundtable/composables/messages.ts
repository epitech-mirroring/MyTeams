import type { Conversation } from "~/stores/messages";
import type { User } from "~/stores/users";

export const getConversationList = async (): Promise<string[]> => {
  const userStore = useUsersStore()

  return await fetch(`${useRuntimeConfig().public.SERVER_URL}/messages/conversations`, {
    method: 'GET',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
    }
  }).then(res => res.json())
}

export const refreshConversations = async () => {
  const messages = useMessagesStore()
  const userStore = useUsersStore()

  const conversations = await getConversationList()
  for (const c of conversations) {
    const conv: Conversation = await fetch(`${useRuntimeConfig().public.SERVER_URL}/messages?uuid=${c}`, {
      method: 'GET',
      headers: {
        'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`
      }
    }).then(res => res.json())
      .then((messages: {timestamp: number, sender_uuid: string, content: string}[]) => {
        return {
          uuid: c,
          messages: messages.map(m => {
            return {
              timestamp: m.timestamp,
              sender_uuid: m.sender_uuid,
              content: m.content
            } as Message
          })
        } as Conversation
      })

    messages.addConversation(conv)
  }

  const conversationUuids = conversations
  const conversationsInStore = messages.getConversations.map(c => c.uuid)
  conversationsInStore.forEach(uuid => {
    if (!conversationUuids.includes(uuid))
      messages.removeConversation(uuid)
  })
}

export const sendMessage = async (target: User, content: string) => {
  const userStore = useUsersStore()
  const messages = useMessagesStore()

  const conversation = {
    uuid: target.uuid,
    messages: []
  } as Conversation

  const alreadyExists = messages.getConversations.find(c => c.uuid === target.uuid)
  if (alreadyExists) {
    conversation.messages = alreadyExists.messages
  }

  const resp = await fetch(`${useRuntimeConfig().public.SERVER_URL}/messages/send`, {
    method: 'POST',
    headers: {
      'Authorization': `Bearer ${userStore.currentUser?.uuid}_${userStore.currentUser?.instance_id}`,
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({
      recipient_uuid: target.uuid,
      message: {
        content
      }
    })
  }).then()

  if (resp.ok) {
    const message = {
      timestamp: Date.now(),
      sender_uuid: userStore.currentUser?.uuid,
      content
    } as Message
    conversation.messages.push(message)
    messages.addConversation(conversation)
  }
}
