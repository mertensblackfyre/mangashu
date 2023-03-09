<template>
   <main class="w-screen h-screen relative">
      <SearchInput />
      <Globe :response="data" />
   </main>
</template>

<script lang="ts">
import { defineComponent, Ref } from "vue";
import SearchInput from "./components/SearchInput.vue";
import Globe from "./components/Globe.vue";
import { handleSubmit } from "./api/data";

// const newsURL = `https://newsapi.org/v2/top-headlines`;
export default defineComponent({
   name: "App",
   components: {
      SearchInput,
      Globe,
   },
   setup() {
      let res: { data: Ref<never[]>; err: unknown } = handleSubmit();
      return { res };
   },
});
</script>
