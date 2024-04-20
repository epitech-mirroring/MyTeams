<script setup lang="ts">
import type { Channel } from "~/stores/teams";

const teamsStore = useTeamsStore();
const userStore = useUsersStore();
const route = useRoute();
const router = useRouter();
const team = computed(() => teamsStore.getTeam(route.params['team_uuid'] as string));
const channelUUID = computed(() => route.params['channel_uuid'] as string | null);
const channel = computed(() => team.value ? team.value.channels.find(channel => channel.uuid === channelUUID.value) : null);

const openChannel = (channel: Channel) => {
  if (!team.value) return;
  router.push(`/teams/${team.value.uuid}/channels/${channel.uuid}`);
};
</script>

<template>
  <div class="channels-navbar">
    <div class="navbar-title">
      <i class="navbar-title-icon fas fa-hashtag"></i>
      <span>Channels</span>
    </div>
    <div class="navbar-items" v-if="team">
      <div class="navbar-item" v-for="channel in team.channels" :key="channel.uuid" @click="openChannel(channel)" :class="{ 'selected': channel.uuid === channelUUID }">
        <div class="item-header">
          <i class="icon fa-duotone fa-comments"></i>
          <span class="name">{{ channel.name }}</span>
        </div>
        <span class="description">{{ channel.description }}</span>
      </div>
    </div>
  </div>
</template>

<style scoped lang="postcss">
.channels-navbar {
  @apply flex flex-col items-start justify-start;
  @apply border-r-2 border-gray-200;
  @apply p-4;
  @apply h-full;
  @apply min-w-[200px];
  @apply bg-white;
  @apply z-0;

  .navbar-title {
    @apply flex flex-row items-center justify-start;
    @apply mb-8;

    span {
      @apply text-xl;
      @apply font-bold;
    }

    .navbar-title-icon {
      @apply w-6 max-w-6;
      @apply flex flex-row items-center justify-center;
    }
  }

  .navbar-items {
    @apply flex flex-col items-start justify-start;
    @apply w-full;

    .navbar-item {
      @apply flex flex-col items-start justify-start;
      @apply w-full;
      @apply p-1;
      @apply rounded-md;
      @apply cursor-pointer;
      @apply transition-all duration-300 ease-in-out;

      .item-header {
        @apply flex flex-row items-center justify-start;
        @apply text-base;
        @apply space-x-0.5;

        .name {
          @apply font-bold;
        }
      }

      .description {
        @apply text-gray-400;
      }

      &:hover {
        @apply bg-gray-200;
      }

      &.selected {
        @apply bg-gray-200;
      }
    }
  }
}
</style>
