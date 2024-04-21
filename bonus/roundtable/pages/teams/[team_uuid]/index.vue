<script setup lang="ts">
const route = useRoute()
const teamUUID = computed(() => route.params['team_uuid'] as string)
const teamsStore = useTeamsStore();
const userStore = useUsersStore();
const team = computed(() => teamsStore.getTeam(teamUUID.value));
const user = computed(() => userStore.user);
const userSubscribed = computed(() => user.value && team.value ? teamsStore.isSubscribed(user.value?.uuid, team.value) : false);

watch(userSubscribed, (value) => {
  setTimeout(() => {
    if (!value) {
      setPageLayout("default");
    } else {
      setPageLayout("team");
    }
  }, 0);
});

onMounted(() => {
  // Wait for hydration
  setTimeout(() => {
    if (!userSubscribed.value) {
      setPageLayout("default");
    } else {
      setPageLayout("team");
    }
  }, 0);
});
</script>

<template>
  <div v-if="userSubscribed">
    <div class="users-subscribed">
      <div class="user-header">
        <h1>Users</h1>
      </div>
      <div class="users-grid">
        <div v-for="user in team?.subscribers.map(uuid => userStore.getUser(uuid))" :key="user?.uuid" class="user" v-if="user">
          <div class="user-avatar">
            <img :src="getAvatar(user)" alt="" />
          </div>
          <div class="user-name">
            <span>{{ user?.username }}</span>
          </div>
          <div class="user-status" :class="user?.status">
            <span>{{ user?.status }}</span>
          </div>
        </div>
      </div>
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
</template>

<style scoped lang="postcss">

.users-subscribed {
  @apply flex flex-col items-start justify-start;
  @apply h-screen;
  @apply w-full;
  @apply relative;
  @apply space-y-4;

  .user-header {
    @apply text-gray-400 text-2xl;
  }

  .users-grid {
    @apply grid grid-cols-3 gap-4;

    .user {
      @apply flex flex-col items-center justify-center;
      @apply bg-gray-100 rounded-md;
      @apply aspect-square;
      @apply p-4;
      @apply relative;
      @apply border-2 border-gray-200;
      @apply shadow-md;

      .user-avatar {
        @apply w-16 h-16;
      }

      .user-name {
        @apply text-gray-800 text-lg;
        @apply capitalize;
      }

      .user-status {
        @apply absolute;
        @apply w-3 h-3;
        content: '';
        @apply rounded-full;
        @apply border-2 border-white;
        @apply top-1/2 left-1/2;
        @apply translate-x-3;
        @apply transition-all duration-300;
        @apply flex flex-row items-center justify-center;

        &.ONLINE {
          @apply bg-green-500;
          @apply border-2 border-white;
          @apply bottom-0 right-0;
        }

        &.OFFLINE {
          @apply bg-gray-500;
          @apply border-2 border-white;
          @apply bottom-0 right-0;
        }

        &.AWAY {
          @apply bg-yellow-500;
          @apply border-2 border-white;
          @apply bottom-0 right-0;
        }

        &.BUSY {
          @apply bg-red-500;
          @apply border-2 border-white;
          @apply bottom-0 right-0;
        }

        span {
          @apply text-xs text-white font-bold;
          @apply tracking-tight;
          @apply sr-only;
          @apply opacity-0;
          @apply transition-opacity duration-300 delay-100;
        }

        &:hover {
          @apply w-16 h-5;
          @apply translate-y-1;

          span {
            @apply not-sr-only;
            @apply opacity-100;
          }
        }
      }
    }
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
      content: '';
      @apply absolute;
      @apply ring-2 ring-green-400;
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
  }
}
</style>
