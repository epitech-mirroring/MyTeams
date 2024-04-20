<script setup lang="ts">
import { replyToThread } from "~/composables/threads";
import type { Thread } from "~/stores/teams";

const route = useRoute()
const teamUUID = computed(() => route.params['team_uuid'] as string)
const channelUUID = computed(() => route.params['channel_uuid'] as string)
const teamsStore = useTeamsStore();
const userStore = useUsersStore();
const team = computed(() => teamsStore.getTeam(teamUUID.value));
const channel = computed(() => team.value ? team.value.channels.find(channel => channel.uuid === channelUUID.value) : null);
const user = computed(() => userStore.user);
const userSubscribed = computed(() => user.value && team.value ? teamsStore.isSubscribed(user.value?.uuid, team.value) : false);
const isModalOpen = ref(false);

watch(userSubscribed, (value) => {
  if (!value) {
    setPageLayout("default");
  } else {
    setPageLayout("team");
  }
});

onMounted(() => {
  if (!userSubscribed.value) {
    setPageLayout("default");
  } else {
    setPageLayout("team");
  }
});

const handleCreateThread = () => {
  const title = document.getElementById("create-thread-title") as HTMLInputElement;
  const content = document.getElementById("create-thread-content") as HTMLTextAreaElement;

  if (!title.value || !content.value) return;
  if (!team.value || !channel.value) return;
  createThread(team.value, channel.value, title.value, content.value);

  title.value = "";
  content.value = "";
  isModalOpen.value = false;
};

const handleCreateReply = (thread: Thread) => {
  const content = document.getElementById("create-reply-content") as HTMLInputElement;

  if (!content.value) return;
  if (!team.value || !channel.value) return;
  replyToThread(team.value, channel.value, thread, content.value);

  content.value = "";
};
</script>

<template>
  <div v-if="userSubscribed && channel" class="channel-page">
    <div class="threads" v-if="channel.threads.length > 0">
      <div class="thread" v-for="thread in channel.threads" :key="thread.uuid">
        <div class="thread-first">
          <div class="thread-header">
            <div class="thread-header-left">
              <span class="thread-title">{{ thread.title }}</span>
              <span class="thread-time">
              {{ new Date(thread.timestamp * 1000).toLocaleDateString() }} @ {{ new Date(thread.timestamp * 100).toLocaleTimeString() }}
            </span>
            </div>
            <div class="thread-author">
              <span>{{ userStore.getUser(thread.sender_uuid)?.username }}</span>
              <img class="author-avatar" :src="'https://api.dicebear.com/8.x/lorelei/svg?flip=true&seed=' + thread.sender_uuid"  alt=""/>
            </div>
          </div>
          <div class="thread-content">
            <span>{{ thread.content }}</span>
          </div>
        </div>
        <div class="thread-replies">
          <div class="thread-reply" v-for="(reply, index) in thread.messages" :key="index">
            <div class="thread-reply-head">
              <div class="thread-reply-author">
                <img class="author-avatar" :src="'https://api.dicebear.com/8.x/lorelei/svg?flip=true&seed=' + reply.sender_uuid"  alt=""/>
                <span class="author-name">{{ userStore.getUser(reply.sender_uuid)?.username }}</span>
              </div>
              <span class="reply-time">
                {{ new Date(reply.timestamp * 1000).toLocaleDateString() }} @ {{ new Date(reply.timestamp * 100).toLocaleTimeString() }}
              </span>
            </div>
            <div class="thread-reply-content">
              <span>{{ reply.content }}</span>
            </div>
          </div>
          <div class="thread-create-reply">
            <input type="text" placeholder="Reply" id="create-reply-content" />
            <div class="thread-create-reply-button" @click="handleCreateReply(thread)">
              <i class="fa-duotone fa-paper-plane fa-fw"></i>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="threads" v-else>
      <div class="no-threads">
        <span>No threads</span>
      </div>
    </div>
    <div class="create-thread" @click="isModalOpen = true">
      <i class="fa-duotone fa-comments"></i>
    </div>
  </div>
  <div v-else class="join-team-page">
    <span class="join-message">
      You are not subscribed to this team
    </span>
    <div class="join-button" @click="team ? joinTeam(team) : null">
      <span>Join team</span>
      <div class="ripple"></div>
      <div class="ripple"></div>
      <div class="ripple"></div>
    </div>
  </div>
  <div class="create-thread-modal" v-if="isModalOpen" @click="isModalOpen = false">
    <div class="create-thread-modal-content" @click.stop>
      <input id="create-thread-title" type="text" placeholder="Title" />
      <textarea id="create-thread-content" placeholder="Content"></textarea>
      <button @click="handleCreateThread">Create</button>
    </div>
  </div>
</template>

<style scoped lang="postcss">

.channel-page {
  @apply h-full;
  @apply overflow-hidden;
  @apply relative;
}

.threads {
  @apply flex flex-col items-start justify-start;
  @apply p-4;
  @apply min-w-[200px] h-full;
  @apply overflow-y-auto;
  @apply space-y-4;

  .thread {
    @apply flex flex-col items-start justify-start;
    @apply w-full;
    @apply bg-white;
    @apply rounded-md;
    @apply shadow-md;
    @apply space-y-2;
    @apply border-2 border-gray-200;

    .thread-first {
      @apply w-full;
      @apply space-y-4;
      @apply bg-gray-100;
      @apply p-4;
      @apply rounded-b-md;

      .thread-header {
        @apply flex flex-row items-center justify-between;
        @apply w-full;

        .thread-header-left {
          @apply flex flex-col items-start;

          .thread-title {
            @apply text-xl;
            @apply font-bold;
          }

          .thread-time {
            @apply text-gray-400;
          }
        }

        .thread-author {
          @apply flex flex-row items-center;
          @apply space-x-2;

          .author-avatar {
            @apply w-8 h-8 rounded-full;
          }

          span {
            @apply text-gray-400;
          }
        }
      }

      .thread-content {
        @apply text-gray-700;
      }
    }

    .thread-replies {
      @apply w-full;
      @apply text-gray-400;

      .thread-reply {
        @apply flex flex-col items-start justify-start;
        @apply w-full;
        @apply space-x-2;
        @apply p-2;

        .thread-reply-head {
          @apply flex flex-row items-center justify-between;
          @apply w-full;

          .thread-reply-author {
            @apply flex flex-row items-center;
            @apply space-x-2;

            .author-avatar {
              @apply w-8 h-8 rounded-full;
            }

            .author-name {
              @apply text-gray-700;
            }
          }

          .reply-time {
            @apply text-gray-400;
            @apply text-xs;
          }
        }

        .thread-reply-content {
          @apply text-gray-700;
        }
      }

      .thread-create-reply {
        @apply flex flex-row items-center justify-between;
        @apply w-full;
        @apply space-x-2;
        @apply px-2;
        @apply mb-2;

        input {
          @apply w-full;
          @apply p-2 px-4;
          @apply rounded-full;
          @apply border-2 border-gray-100;
          @apply text-gray-700;
        }

        .thread-create-reply-button {
          @apply flex flex-row items-center justify-center;
          @apply w-8 h-8;
          @apply rounded-full;
          @apply cursor-pointer;
          @apply transition-all duration-300;

          i {
            @apply text-blue-500;
          }

          &:hover {
            @apply bg-blue-100;
          }
        }
      }
    }
  }

  .no-threads {
    @apply flex flex-col items-center justify-center;
    @apply h-full;
    @apply w-full;
    @apply space-y-4;

    span {
      @apply text-gray-400 text-2xl;
    }
  }
}

.create-thread {
  @apply flex flex-row items-center justify-center;
  @apply bg-blue-500;
  @apply rounded-full rounded-br-none;
  @apply absolute;
  @apply bottom-4 right-4;
  @apply w-12 h-12;
  @apply cursor-pointer;
  @apply transition-all duration-300;
  @apply text-white;
  @apply shadow-md;

  &:hover {
    @apply bg-blue-600;
  }
}

.join-team-page {
  @apply flex flex-col items-center justify-center;
  @apply h-screen;
  @apply w-full;
  @apply relative;
  @apply space-y-4;

  .join-message {
    @apply text-gray-400 text-2xl;
  }

  @keyframes ripple {
    0% {
      transform: scale(0);
    }
    100% {
      transform: scale(1.5);
      opacity: 0;
    }
  }

  .join-button {
    @apply bg-green-400 text-white px-4 py-2 rounded-md;
    @apply transition-all duration-300;
    @apply relative;
    @apply scale-125;
    @apply cursor-pointer;
    @apply w-40 h-12;

    &:hover {
      @apply bg-green-500;
    }

    span {
      @apply text-white font-bold;
      @apply absolute;
      @apply top-1/2 left-1/2;
      @apply transform -translate-x-1/2 -translate-y-1/2;
      @apply z-20;
    }

    &:hover {
      &:before {
        @apply bg-green-500;
      }

      .ripple {
        @apply ring-2 ring-green-400;
      }
    }

    &:before {
      content: '';
      @apply absolute;
      @apply w-full h-full;
      @apply rounded-md;
      @apply bg-green-400;
      @apply z-10;
      @apply top-0 left-0;
    }

    .ripple {
      @apply ring-2 ring-green-400;
    }
  }
}

.ripple {
  content: '';
  @apply absolute;
  @apply ring-2 ring-gray-500;
  @apply rounded-md;
  @apply w-full h-full;
  @apply transform translate-x-1/2 translate-y-1/2;
  @apply top-0 left-0;
  @apply z-0 opacity-75;
  @apply scale-0;
  animation: ripple 3s ease-out infinite;

  &:nth-child(1) {
    animation-delay: 0s;
  }

  &:nth-child(2) {
    animation-delay: 0.5s;
  }

  &:nth-child(3) {
    animation-delay: 1s;
  }
}

.create-thread-modal {
  @apply fixed;
  @apply top-0 left-0;
  @apply w-full h-full;
  @apply bg-gray-900 bg-opacity-50;
  @apply flex flex-row items-center justify-center;
  @apply z-50;

  .create-thread-modal-content {
    @apply bg-white;
    @apply w-96;
    @apply p-4;
    @apply rounded-md;
    @apply shadow-md;

    input {
      @apply w-full;
      @apply p-2;
      @apply rounded-md;
      @apply border-2 border-gray-300;
      @apply mb-4;
    }

    textarea {
      @apply w-full;
      @apply p-2;
      @apply rounded-md;
      @apply border-2 border-gray-300;
      @apply mb-4;
    }

    button {
      @apply w-full;
      @apply p-2;
      @apply rounded-md;
      @apply bg-blue-500;
      @apply text-white;
      @apply cursor-pointer;
      @apply transition-all duration-300;

      &:hover {
        @apply bg-blue-600;
      }
    }
  }
}
</style>
