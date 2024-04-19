<script setup lang="ts">

import Navbar from "~/components/navbar.vue";
import ChannelsNavbar from "~/components/channels-navbar.vue";
</script>

<template>
  <div class="team-layout">
    <navbar />
    <channels-navbar />
    <div class="content">
      <slot />
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
  @apply pl-4;
  @apply overflow-y-auto overflow-x-hidden;
}
</style>
