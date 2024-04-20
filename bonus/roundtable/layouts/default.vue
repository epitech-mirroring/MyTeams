<script setup lang="ts">

import Navbar from "~/components/navbar.vue";

</script>

<template>
  <div class="main-layout">
    <navbar />
    <div class="content">
      <slot />
    </div>
  </div>
</template>

<style scoped lang="postcss">
  .main-layout {
    @apply flex flex-row items-start;
    @apply h-screen;
    @apply w-screen;
  }

  .content {
    @apply flex-1;
    @apply pl-4;
    @apply overflow-hidden;
  }
</style>
