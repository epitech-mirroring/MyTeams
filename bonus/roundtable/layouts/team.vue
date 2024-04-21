<script setup lang="ts">

import Navbar from "~/components/navbar.vue";
import ChannelsNavbar from "~/components/channels-navbar.vue";

import { useTeamsStore } from "~/stores/teams";
const route = useRoute();
const teamsStore = useTeamsStore();
const teamUUID = ref(route.params['team_uuid'] as string);

const team = teamsStore.getTeam(teamUUID.value);
</script>

<template>
  <div class="team-layout">
    <navbar />
    <channels-navbar />
    <div class="content" v-if="team">
      <div class="team-header">
        <div class="team-header-left">
          <span class="title">{{ team.name }}</span>
          <span class="description">{{ team.description }}</span>
        </div>
        <div class="team-header-actions">
          <div class="team-header-action leave" @click="leaveTeam(team)">
            <i class="fas fa-sign-out-alt"></i>
          </div>
        </div>
      </div>
      <div class="sub-content">
        <slot />
      </div>
    </div>
    <div v-else>
      <p>Team not found</p>
    </div>
  </div>
</template>

<style scoped lang="postcss">
.team-layout {
  @apply flex flex-row items-start;
  @apply h-screen;
  @apply w-screen;
}

.content {
  @apply flex-1;
  @apply overflow-hidden;
  @apply h-screen;

  .team-header {
    @apply flex flex-row items-start justify-between;
    @apply border-b-2 border-gray-200;
    @apply p-4;
    @apply w-full h-24;

    .team-header-left {
      @apply flex flex-col items-start;
      @apply space-y-2;

      .title {
        @apply text-2xl;
        @apply font-bold;
      }

      .description {
        @apply text-gray-400;
      }
    }

    .team-header-actions {
      @apply flex flex-row items-center;
      @apply space-x-2;

      .team-header-action {
        @apply flex flex-row items-center justify-center;
        @apply bg-gray-200;
        @apply rounded-md;
        @apply w-8 h-8;
        @apply cursor-pointer;
        @apply transition-all duration-300;

        &.leave:hover {
          @apply bg-red-400;
          @apply text-white;
        }
      }
    }
  }

  .sub-content {
    @apply px-4;
    @apply w-full;
    height: calc(100% - 6rem);
    @apply overflow-hidden;
  }
}
</style>
