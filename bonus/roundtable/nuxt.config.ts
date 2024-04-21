// https://nuxt.com/docs/api/configuration/nuxt-config
export default defineNuxtConfig({
  devtools: { enabled: true },
  css: [
    '~/assets/css/main.css',
  ],
  postcss: {
    plugins: {
      tailwindcss: {},
      autoprefixer: {},
    },
  },
  modules: ['@pinia/nuxt', '@nuxtjs/tailwindcss', '@pinia-plugin-persistedstate/nuxt'],
  app: {
    head: {
      script: [
        { src: 'https://kit.fontawesome.com/27271e5dd9.js', crossorigin: 'anonymous' }
      ]
    }
  },
  runtimeConfig: {
    public: {
      SERVER_URL: process.env.SERVER_URL || 'http://127.0.0.1:8080'
    }
  }
})
