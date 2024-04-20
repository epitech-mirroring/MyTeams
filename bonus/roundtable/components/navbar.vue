<script setup lang="ts">
const teamsStore = useTeamsStore();
const userStore = useUsersStore();
const router = useRouter();

const isLogged = computed(() => userStore.isLogged);
const user = computed(() => userStore.user);

watch(isLogged, (value) => {
  if (!value) {
    router.push({path: "/login"});
    return;
  }
});

onMounted(() => {
  if (!isLogged.value) {
    router.push({path: "/login"});
    return;
  }
})
</script>

<template>
  <div class="navbar">
    <div class="navbar-title">
      <img src="~/assets/images/logo.png" alt="logo" />
      <span>RoundTable</span>
    </div>
    <div class="navbar-groups" v-if="user">
      <div class="navbar-group">
        <div class="navbar-group-header">
          <div class="navbar-group-header-icon">
            <i class="fas fa-user fa-fw"></i>
          </div>
          <span>Direct Messages</span>
        </div>
        <div class="navbar-group-items">
        </div>
      </div>
      <div class="navbar-group">
        <div class="navbar-group-header">
          <div class="navbar-group-header-icon">
            <i class="fas fa-users fa-fw"></i>
          </div>
          <span>Teams</span>
        </div>
        <div class="navbar-group-items">
          <div v-for="team in teamsStore.getTeams" :key="team.uuid" class="navbar-group-item team">
            <router-link :to="'/teams/' + team.uuid">{{ team.name }}</router-link>
            <i :class="{'fas': true, 'fa-wifi-slash': !teamsStore.isSubscribed(user.uuid, team), 'fa-wifi': teamsStore.isSubscribed(user.uuid, team)}"></i>
          </div>
        </div>
      </div>
    </div>
    <div class="navbar-footer">
      <div class="footer-left">
        <div class="avatar">
          <img :src="'https://api.dicebear.com/8.x/lorelei/svg?flip=true&seed=' + user?.uuid" alt="avatar" />
          <div class="status" :class="[userStore.user?.status]">
            <span>{{ userStore.user?.status }}</span>
          </div>
        </div>
        <span>{{ userStore.user?.username }}</span>
      </div>
      <i class="fas fa-sign-out-alt fa-fw logout" @click="logout()"></i>
    </div>
  </div>
</template>

<style scoped lang="postcss">
.navbar {
  @apply flex flex-col items-start justify-start;
  @apply border-r-2 border-gray-200;
  @apply p-4;
  @apply h-full;
  @apply min-w-[200px];
  @apply bg-white;
  @apply z-10;

  .navbar-title {
    @apply flex flex-row items-center justify-start;
    @apply mb-4;

    img {
      @apply w-8 h-8;
      @apply mr-2;
    }

    span {
      @apply text-xl;
      @apply font-bold;
    }
  }

  .navbar-groups {
    @apply flex flex-col;
    @apply space-y-4;
    @apply w-full h-full;

    .navbar-group {
      @apply flex flex-col;
      @apply space-y-4;

      .navbar-group-header {
        @apply flex flex-row items-center justify-start;
        @apply text-lg;
        @apply font-bold;
        @apply text-gray-800;
        @apply space-x-2;

        .navbar-group-header-icon {
          @apply w-6 max-w-6;
          @apply flex flex-row items-center justify-center;
        }
      }

      .navbar-group-items {
        @apply flex flex-col;
        @apply space-y-2;

        .navbar-group-item {
          @apply flex flex-row items-center justify-start;
          @apply text-base;
          @apply text-gray-700;
          @apply space-x-2;
        }

        .team {
          @apply flex flex-row items-center justify-start;
          @apply cursor-pointer;
          @apply hover:text-gray-900;

          i {
            @apply text-xs;
            @apply text-gray-500;

            &.fa-wifi-slash {
              @apply text-red-500;
            }
          }
        }
      }
    }
  }

  .navbar-footer {
    @apply flex flex-row items-center justify-between;
    @apply mt-auto;
    @apply text-base;
    @apply text-gray-700;
    @apply space-x-2;
    @apply w-full;
    @apply relative;

    .footer-left {
      @apply flex flex-row items-center justify-start;
      @apply space-x-2;

      .avatar {
        @apply w-6 h-6;
        @apply rounded-full;
        @apply overflow-hidden;

        img {
          @apply w-full h-full;
        }

        .status {
          @apply absolute;
          @apply w-2 h-2;
          content: '';
          @apply rounded-full;
          @apply border-2 border-white;
          @apply bottom-0 left-0;
          @apply translate-x-4;
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

      span {
        @apply text-base;
        @apply font-bold;
        @apply text-gray-800;
        @apply capitalize;
      }
    }

    .logout {
      @apply cursor-pointer;
      @apply hover:text-red-500;
    }
  }
}
</style>
