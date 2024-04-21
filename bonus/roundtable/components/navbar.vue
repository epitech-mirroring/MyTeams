<script setup lang="ts">
import { useMessagesStore } from "~/stores/messages";
import { type User, useUsersStore } from "~/stores/users";
import { useTeamsStore } from "~/stores/teams";

const teamsStore = useTeamsStore();
const userStore = useUsersStore();
const messagesStore = useMessagesStore();
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
  } else {
    refreshAll()
  }
})

const isNewTeamModalOpen = ref(false);
const isDmModalOpen = ref(false);
const searchUsername = ref("");

const handleCreateTeam = () => {
  const name = document.getElementById("team-name") as HTMLInputElement;
  const description = document.getElementById("team-description") as HTMLInputElement;

  if (!name || !description) return;

  createTeam(name.value, description.value);
  isNewTeamModalOpen.value = false;
  name.value = "";
  description.value = "";
};

const userOptionFilter = (option: User) => {
  if (option.uuid === user.value?.uuid)
    return false;
  if (!searchUsername.value || searchUsername.value === "")
    return true;
  return option.username.toLowerCase().includes(searchUsername.value.toLowerCase());
};
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
          <div v-for="dm in messagesStore.getConversations" :key="dm.uuid" class="navbar-group-item dm" @click="router.push({path: `/messages/${dm.uuid}`})">
            <div class="avatar">
              <img :src="getAvatar(userStore.getUser(dm.uuid))" alt="avatar" />
              <div class="status" :class="[userStore.getUser(dm.uuid)?.status]">
              </div>
            </div>
            <span>{{ userStore.getUser(dm.uuid)?.username }}</span>
          </div>
          <div class="navbar-group-item dm create-dm" @click="isDmModalOpen = true">
            <div class="item-header">
              <i class="fas fa-search"></i>
              <span class="name">Open DM</span>
            </div>
          </div>
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
          <div v-for="team in teamsStore.getTeams" :key="team.uuid" class="navbar-group-item team" @click="router.push({path: `/teams/${team.uuid}`})">
            <span>{{ team.name }}</span>
            <i :class="{'fas': true, 'fa-wifi-slash': !teamsStore.isSubscribed(user.uuid, team), 'fa-wifi': teamsStore.isSubscribed(user.uuid, team)}"></i>
          </div>
          <div class="navbar-group-item team create-team" @click="isNewTeamModalOpen = true">
            <div class="item-header">
              <i class="icon fa-duotone fa-plus"></i>
              <span class="name">Create Team</span>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="navbar-footer" v-if="user">
      <div class="footer-left">
        <div class="avatar">
          <img :src="getAvatar(user)" alt="avatar" />
          <div class="status" :class="[user?.status]">
            <span>{{ user?.status }}</span>
          </div>
        </div>
        <span>{{ user?.username }}</span>
      </div>
      <i class="fas fa-sign-out-alt fa-fw logout" @click="logout()"></i>
    </div>
  </div>
  <div v-if="isNewTeamModalOpen" class="modal" @click="isNewTeamModalOpen = false">
    <div class="modal-content" @click.stop>
      <div class="inputs">
        <div class="input-group">
          <label for="team-name">Team Name</label>
          <input type="text" id="team-name" />
        </div>
        <div class="input-group">
          <label for="team-description">Team Description</label>
          <input type="text" id="team-description" />
        </div>
      </div>
      <div class="modal-actions">
        <button class="modal-action close" @click="isNewTeamModalOpen = false">Cancel</button>
        <button class="modal-action validate" @click="handleCreateTeam">Create</button>
      </div>
    </div>
  </div>
  <div v-if="isDmModalOpen" class="modal" @click="isDmModalOpen = false" id="dm-modal">
    <div class="modal-content" @click.stop>
      <div class="modal-header">
        <span class="modal-title">Search for a user</span>
      </div>
      <div class="inputs">
        <div class="input-group mb-2">
          <label for="team-name">Username</label>
          <input type="text" id="username" v-model="searchUsername" />
        </div>
        <div class="input-options">
          <div v-for="option in userStore.userList.filter(userOptionFilter)" :key="option.uuid" class="input-option" @click="router.push({path: `/messages/${option.uuid}`}); isDmModalOpen = false">
            <div class="avatar">
              <img :src="getAvatar(option)" alt="avatar" />
              <div class="status" :class="[option.status]">
              </div>
            </div>
            <span>{{ option.username }}</span>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped lang="postcss">
#dm-modal {
  .modal-content .inputs .input-options {
    @apply flex flex-col;
    @apply space-y-2;
    @apply w-full;
    @apply max-h-[300px];
    @apply overflow-y-auto;

    .input-option {
      @apply flex flex-row items-center justify-start;
      @apply cursor-pointer;
      @apply hover:bg-gray-100;
      @apply p-2;
      @apply rounded-md;
      @apply relative;

      .avatar {
        @apply w-8 h-8;
        @apply rounded-full;
        @apply overflow-hidden;

        img {
          @apply w-full h-full;
        }

        .status {
          @apply absolute;
          @apply w-3 h-3;
          content: '';
          @apply rounded-full;
          @apply border-2 border-white;
          @apply bottom-0 left-0;
          @apply translate-x-7;
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
        }
      }
    }
  }
}

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
          @apply p-1;
          @apply rounded-md;
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

          &.create-team {
            @apply mt-2;
            @apply bg-gray-100;

            .item-header {
              @apply text-sm;
              @apply space-x-2;
              @apply transition-all duration-300 ease-in-out;
              @apply text-gray-400;

              .name {
                @apply font-normal;
              }

              &:hover {
                @apply text-gray-500;
              }
            }
          }
        }

        .dm {
          @apply flex flex-row items-center justify-start;
          @apply cursor-pointer;
          @apply hover:text-gray-900;
          @apply relative;

          .avatar {
            @apply w-8 h-8;
            @apply rounded-full;
            @apply overflow-hidden;

            img {
              @apply w-full h-full;
            }

            .status {
              @apply absolute;
              @apply w-3 h-3;
              content: '';
              @apply rounded-full;
              @apply border-2 border-white;
              @apply bottom-0 left-0;
              @apply translate-x-7;
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
            }
          }
        }

        .create-dm {
          @apply mt-2;
          @apply bg-gray-100;

          .item-header {
            @apply text-sm;
            @apply space-x-2;
            @apply transition-all duration-300 ease-in-out;
            @apply text-gray-400;

            .name {
              @apply font-normal;
            }

            &:hover {
              @apply text-gray-500;
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
