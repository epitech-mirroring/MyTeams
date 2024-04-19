<script setup lang="ts">
const route = useRoute()
const teamUUID = computed(() => route.params['team-uuid'] as string)
const teamsStore = useTeamsStore();
const team = computed(() => teamsStore.getTeam(teamUUID.value));
const isUserSubscribed = computed(() => team.value ? teamsStore.isSubscribed(team.value) : false);


watch(isUserSubscribed, () => {
  if (isUserSubscribed.value) {
    setPageLayout('team');
  } else {
    setPageLayout('default');
  }
})
</script>

<template>
  <div v-if="isUserSubscribed">
  </div>
  <div v-else class="join-team-page">
    <span class="join-message">
      You are not subscribed to this team
    </span>
    <div class="join-button" @click="team ? teamsStore.joinTeam(team) : null">
      <span>Join team</span>
      <div class="ripple"></div>
      <div class="ripple"></div>
      <div class="ripple"></div>
    </div>
  </div>
</template>

<style scoped lang="postcss">

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
