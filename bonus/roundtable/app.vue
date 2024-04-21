<script setup lang="ts">

import { logout, updateStatus } from "~/composables/users";
import { UserStatus } from "~/stores/users";

const lastMoveTime = ref(0);
const usersStore = useUsersStore();
const user = computed(() => usersStore.currentUser);
const wasSwitchedAutomatically = ref(false);
const timeBeforeAway = 1000 * 60 * 5;
const timeBeforeOffline = 1000 * 60 * 10;

onMounted(() => {
  window.addEventListener("mousemove", () => {
    lastMoveTime.value = Date.now();
  });

  setInterval(() => {
    if (!user.value)
      return;
    if (Date.now() - lastMoveTime.value > timeBeforeAway) {
      // If user not already away then set user status to away
      if (user.value?.status === UserStatus.ONLINE) {
        updateStatus(UserStatus.AWAY);
        wasSwitchedAutomatically.value = true;
      } else {
        // If it's been more than 10 minutes since last moved and the user
        // and the user was set to away automatically then set user status to offline
        if (Date.now() - lastMoveTime.value > timeBeforeOffline) {
          logout();
        }
      }
    } else if (Date.now() - lastMoveTime.value < timeBeforeAway &&
      wasSwitchedAutomatically.value) {
      updateStatus(UserStatus.ONLINE);
      wasSwitchedAutomatically.value = false;
    }
  }, 1000);
});

</script>

<template>
  <NuxtLayout>
    <NuxtPage/>
  </NuxtLayout>
</template>

<style lang="postcss">
.modal {
  @apply fixed inset-0;
  @apply bg-black bg-opacity-50;
  @apply z-50;

  .modal-content {
    @apply fixed top-1/2 left-1/2;
    @apply transform -translate-x-1/2 -translate-y-1/2;
    @apply bg-white;
    @apply p-4;
    @apply rounded-md;
    @apply z-50;
    @apply min-w-[300px] max-w-[400px];
    @apply space-y-8;

    .modal-header {
      @apply flex flex-row items-center justify-between;
      @apply border-b-2 border-gray-200;
      @apply p-2;

      .modal-title {
        @apply text-lg font-semibold;
      }

      .modal-close {
        @apply cursor-pointer;
        @apply transition-all duration-200;

        &:hover {
          @apply text-red-500;
        }
      }
    }

    .input-group {
      @apply flex flex-col items-start justify-start;
      @apply w-full;
      @apply space-y-2;

      label {
        @apply text-sm font-semibold;
        @apply transform translate-y-[90%] translate-x-2;
        @apply text-gray-400;
        @apply px-1;
        @apply bg-white;
        @apply transition-all duration-300;
      }

      &:focus-within {
        label {
          @apply text-sm font-semibold;
          @apply transform translate-y-1/2 translate-x-2;
          @apply text-gray-800;
          @apply px-1;
          @apply bg-transparent;
        }
      }

      input {
        @apply w-full;
        @apply border-2 border-gray-200;
        @apply rounded-lg;
        @apply p-2;
        background-color: white !important;

        &:focus {
          @apply outline-none;
          @apply border-2 border-blue-500;
        }
      }
    }

    .modal-actions {
      @apply flex flex-row items-center justify-around;
      @apply w-full;

      .modal-action {
        @apply bg-blue-500 text-white;
        @apply rounded-lg;
        @apply p-2 px-4;
        @apply cursor-pointer;
        @apply transition-all duration-200;

        &:hover {
          @apply bg-blue-600;

          &.close {
            @apply bg-red-400;
          }

          &.validate {
            @apply bg-green-400;
          }
        }

        & + .modal-action {
          @apply ml-2;
        }

        &.close {
          @apply bg-red-500;
        }

        &.validate {
          @apply bg-green-500;
        }
      }
    }
  }
}
</style>
