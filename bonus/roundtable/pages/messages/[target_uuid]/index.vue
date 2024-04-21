<script setup lang="ts">

const route = useRoute();
const router = useRouter();
const targetUUID = computed(() => route.params.target_uuid as string);
const userStore = useUsersStore();
const messagesStore = useMessagesStore();
const target = computed(() => userStore.getUser(targetUUID.value));
const user = computed(() => userStore.currentUser);
const conversation = computed(() => messagesStore.getConversation(targetUUID.value));

definePageMeta({
  layout: "default",
  title: "Messages",
});

onMounted(() => {
  if (!target.value) {
    router.push({ path: "/404" });
  }
});

const handleSendMessage = () => {
  const input = document.getElementById("message-input") as HTMLInputElement;
  if (!input || !input.value || !target.value) return;

  sendMessage(target.value, input.value);
  input.value = "";
};
</script>

<template>
  <div v-if="user && target" class="messages-page">
    <div class="messages">
      <div class="message" v-for="(message, index) in conversation?.messages" :key="index" :class="{'reversed': message.sender_uuid === user.uuid}">
        <div class="message-header" v-if="index === 0 || message.sender_uuid !== conversation?.messages[index - 1].sender_uuid">
          <img :src="getAvatar(message.sender_uuid === user.uuid ? user : target)" alt="avatar" />
          <span>{{ message.sender_uuid === user.uuid ? 'You' : target.username }}</span>
        </div>
        <div class="message-content">
          <span>{{ message.content }}</span>
        </div>
      </div>
      <div class="message-input">
        <input type="text" placeholder="Type a message..." id="message-input" @keyup.enter="handleSendMessage" />
        <div class="send-button">
          <i class="fas fa-paper-plane"></i>
        </div>
      </div>
    </div>
    <div class="target-info">
      <div class="target-info-header">
        <img :src="getAvatar(target)" alt="avatar" />
        <span>{{ target.username }}</span>
        <span class="status">
          {{ target.status }}
        </span>
      </div>
      <div class="target-info-actions">
        <div class="action">
          <i class="fas fa-phone"></i>
        </div>
        <div class="action">
          <i class="fas fa-video"></i>
        </div>
        <div class="action">
          <i class="fas fa-ellipsis-v"></i>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped lang="postcss">
.messages-page {
  @apply flex flex-row items-start;
  @apply h-screen;
  @apply w-full;

  .messages {
    @apply flex flex-col items-start justify-start;
    @apply w-full;
    @apply h-full;
    @apply p-4;
    @apply overflow-y-auto;
    @apply relative;
    @apply space-y-4;

    .message {
      @apply flex flex-col items-start;
      @apply w-fit;
      @apply space-y-2;

      .message-header {
        @apply flex flex-row items-center;
        @apply space-x-2;
        @apply w-full;

        img {
          @apply w-8 h-8 rounded-full;
        }

        span {
          @apply text-lg font-semibold;
        }
      }

      &.reversed {
        @apply ml-auto;

        .message-header {
          @apply flex-row-reverse;
        }

        .message-content {
          @apply ml-auto;
        }
      }

      .message-content {
        @apply w-fit;
        @apply text-gray-600;
      }
    }

    .message-input {
      @apply px-2 py-4;
      @apply w-full;
      @apply flex flex-row items-center justify-start;
      @apply gap-4;
      @apply border-t-2 border-gray-200;
      @apply absolute;
      @apply bottom-0 -left-2;
      @apply bg-white;

      input {
        @apply w-full;
        @apply p-2;
        @apply border-2 border-gray-200;
        @apply rounded-md;
      }

      .send-button {
        @apply w-12 h-12;
        @apply flex flex-row items-center justify-center;
        @apply rounded-full;
        @apply cursor-pointer;

        i {
          @apply text-blue-400;
          @apply transition-all duration-300;
          @apply p-2;
          @apply rounded-full;

          &:hover {
            @apply text-blue-500;
            @apply ring-2 ring-blue-400;
            @apply rotate-12;
          }
        }
      }
    }
  }

  .target-info {
    @apply flex flex-col items-center;
    @apply w-1/4;
    @apply border-l-2 border-gray-200;
    @apply h-full;

    .target-info-header {
      @apply flex flex-col items-center;
      @apply p-4;
      @apply border-b-2 border-gray-200;
      @apply w-full;

      img {
        @apply w-16 h-16 rounded-full;
      }

      span {
        @apply text-lg font-semibold;
      }

      & .status {
        @apply text-gray-400;
      }
    }

    .target-info-actions {
      @apply flex flex-row items-center justify-around;
      @apply w-full;
      @apply p-4;

      .action {
        @apply flex flex-col items-center justify-center;
        @apply w-12 h-12;
        @apply rounded-full;
        @apply bg-gray-200;
        @apply cursor-pointer;

        i {
          @apply text-lg;
        }
      }
    }
  }
}
</style>
