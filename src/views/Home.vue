<template>
   <main class="h-screen w-screen">
      <SearchInput @get-country="getCountry" />
      <GlobeComponent :coordinates="coordinates" :country="country" />
   </main>
</template>

<script lang="ts">
import SearchInput from "../components/SearchInput.vue";
import GlobeComponent from "../components/Globe.vue";
import axios from "axios";

const geoCodingURL = "https://api.geoapify.com/v1/geocode/search";

export default {
   name: "HomeView",
   components: {
      SearchInput,
      GlobeComponent,
   },
   data() {
      return {
         country: "Spain",
         coordinates: [],
      };
   },
   methods: {
      async getGeoCodingData() {
         const response = await axios.get(
            `${geoCodingURL}?text=${this.country}&apiKey=f1ee77bd589648639821fc26719d7a45`,
            {
               withCredentials: false,
            }
         );
         if (!response) {
            throw new Error("No data");
         }
         return response.data;
      },
      async getCountry(country: string) {
         const data = await this.getGeoCodingData();
         this.coordinates = data.features[0]["geometry"]["coordinates"];
         this.country = country;
      },
   },
};
</script>
