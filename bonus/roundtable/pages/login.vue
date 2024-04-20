<script setup lang="ts">

import { useUsersStore } from "~/stores/users";

const userStore = useUsersStore();
const isLogged = computed(() => userStore.isLogged);
const router = useRouter();

const login = async () => {
  const username = document.getElementById("username") as HTMLInputElement;

  if (username.value) {
    await loginWithUsername(username.value);
    if (isLogged.value) {
      setTimeout(() => {
        router.push({path: "/"});
      }, 1000);
    }
  }
};

definePageMeta({
  layout: "default",
})

</script>

<template>
  <div class="main-container">
    <div class="login-container">
      <div class="login-header">
        <img class="login-logo" src="~/assets/images/logo.png" alt="logo" />
        <div class="login-title">
          Login
        </div>
      </div>
      <div v-if="!isLogged" class="login-form">
        <div class="input-group">
          <label for="username">Username</label>
          <input type="text" id="username" />
        </div>
        <div class="login-actions">
          <button class="login-button" @click="login">Login / Sign Up</button>
        </div>
      </div>
      <div v-else>
        <div class="login-form">
          <div class="login-text">
            <p >Welcome back, <span>{{ userStore.currentUser?.username }}</span></p>
          </div>
          <div class="login-actions">
            <button class="logout-button" @click="logout">Logout</button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped lang="postcss">
  .main-container {
    @apply flex flex-col items-center justify-center;
    @apply h-screen w-screen;
    @apply bg-gray-100;

    .login-container {
      @apply flex flex-col items-center justify-center;
      @apply bg-white;
      @apply rounded-lg;
      @apply shadow-lg;
      @apply p-4;
      @apply min-w-[300px];

      .login-header {
        @apply flex flex-row items-center justify-start;
        @apply w-full;
        @apply border-b-2 border-gray-200;
        @apply pb-2;
        @apply space-x-4;

        .login-title {
          @apply text-2xl font-bold;
        }

        .login-logo {
          @apply w-9 h-10;
        }
      }

      .login-form {
        @apply flex flex-col items-center justify-center;
        @apply w-full;
        @apply space-y-4;
        @apply pt-4;

        .input-group {
          @apply flex flex-col items-start justify-start;
          @apply w-full;
          @apply space-y-2;
          @apply relative;

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

        .login-text {
          @apply text-lg font-semibold;
          @apply text-gray-800;

          span {
            @apply text-blue-500;
          }
        }

        .login-actions {
          @apply flex flex-row items-center justify-center;
          @apply w-full;

          .login-button {
            @apply bg-blue-500 text-white;
            @apply rounded-lg;
            @apply p-2 px-4;
            @apply cursor-pointer;
            @apply transition-all duration-200;

            &:hover {
              @apply bg-blue-600;
            }
          }

          .logout-button {
            @apply bg-red-500 text-white;
            @apply rounded-lg;
            @apply p-2 px-4;
            @apply cursor-pointer;
            @apply transition-all duration-200;

            &:hover {
              @apply bg-red-600;
            }
          }
        }
      }
    }
  }
</style>
