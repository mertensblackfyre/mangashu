<template>
   <head>
      <link
         href="https://api.tiles.mapbox.com/mapbox-gl-js/v0.53.0/mapbox-gl.css"
         rel="stylesheet"
      />
   </head>
   <main class="w-full h-screen relative">
      <SearchInput />
      <Globe />
   </main>
</template>

<script lang="ts">
import SearchInput from "./components/SearchInput.vue";
import Globe from "./components/Globe.vue";
export default {
   name: "App",
   components: {
      SearchInput,
      Globe,
   },
};
</script>
