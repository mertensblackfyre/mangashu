<template>
   <main class="w-screen h-screen relative">
      <SearchInput @searchInput="handleSubmit" />
      <Globe :search="input" />
   </main>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import SearchInput from "./components/SearchInput.vue";
import Globe from "./components/Globe.vue";
import axios from "axios";
const geoCodingURL = "https://api.geoapify.com/v1/geocode/search";

const newsURL = `https://newsapi.org/v2/top-headlines`;

export default defineComponent({
   name: "App",
   components: {
      SearchInput,
      Globe,
   },
   data() {
      return {
         input: "",
      };
   },
   methods: {
      async handleSubmit(input: string) {
         try {
            this.input = input;
            const response = await axios.get(
               `${geoCodingURL}?text=${this.input}&apiKey=f1ee77bd589648639821fc26719d7a45`,
               {
                  withCredentials: false,
               }
            );
            // "country=us&" +
            // "apiKey=53ae439ca1624a9a9870e92d88f4bbdd"
            const resp = await axios.get(
               `${newsURL}?country=${this.input}&apiKey=53ae439ca1624a9a9870e92d88f4bbdd`,
               {
                  withCredentials: false,
               }
            );

            console.log(resp, response);
         } catch (error) {
            console.log("====================================");
            console.log(error);
            console.log("====================================");
         }
      },
   },
});
</script>
