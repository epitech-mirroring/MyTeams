<script setup lang="ts">

</script>

<template>
  <div class="nothing-selected-page">
    <div>
      <i class="fas fa-arrow-left fa-2x"></i>
    </div>
    <div>
      <span>Select a team or a direct message to start chatting</span>
    </div>
    <img src="~/assets/svg/office-bg.svg" alt="office" />
  </div>
</template>

<style scoped lang="postcss">
  .nothing-selected-page {
    @apply flex flex-col items-center justify-center;
    @apply h-screen;
    @apply w-full;
    @apply relative;

    img {
      @apply absolute top-0 left-0 w-full h-full;
      @apply object-cover;
      @apply z-0;
      @apply opacity-25;
      @apply pointer-events-none;
      @apply transform scale-50;
    }

    div {
      @apply z-10;
    }

    i {
      @apply text-gray-400;
    }

    span {
      @apply text-gray-400;
    }
  }
</style>
