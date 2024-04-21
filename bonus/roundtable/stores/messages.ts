import type { User } from "~/stores/users";

export const useMessagesStore = defineStore('messages', {
  state: () => {
    return {
      conversations: [] as Conversation[]
    }
  },
  getters: {
    getConversations(): Conversation[] { return this.conversations },
    getConversation: (state) => (uuid: string | User) => {
      return state.conversations.find(c => c.uuid === (typeof uuid === 'string' ? uuid : uuid.uuid))
    },
    getMessages: (state) => (conversation: Conversation | string) => {
      const c = typeof conversation === 'string' ? state.conversations.find(c => c.uuid === conversation) : conversation
      return c ? c.messages : []
    }
  },
  actions: {
    addConversation(conversation: Conversation) {
      if (!this.conversations.find(c => c.uuid === conversation.uuid))
        this.conversations.push(conversation)
      else {
        const c = this.conversations.find(c => c.uuid === conversation.uuid)
        if (c) {
          c.messages = conversation.messages
        }
      }
    },
    clearConversations() {
      this.conversations = []
    },
    removeConversation(uuid: string) {
      const index = this.conversations.findIndex(c => c.uuid === uuid)
      if (index !== -1) {
        this.conversations.splice(index, 1)
      }
    },
  },
  persist: true
})

export interface Conversation {
  uuid: string
  messages: Message[]
}
