<template>
   <main class="h-screen w-screen relative">
      <SearchInput @get-ip="getIPAddress" />
      <GlobeComponent :coordinates="coordinates" :ip="ip" />
   </main>
</template>

<script lang="ts">
import SearchInput from "../components/SearchInput.vue";
import GlobeComponent from "../components/Globe.vue";
import axios from "axios";

import { defineComponent } from "vue";

const newsURL = `https://geo.ipify.org/api/v2/country,city?apiKey=${process.env.VUE_APP_GEO_CODER_KEY}`;

export default defineComponent({
   name: "HomeView",
   components: {
      SearchInput,
      GlobeComponent,
   },
   data() {
      return {
         ip: "176.224.81.52",
         coordinates: [21.21, -12.21],
         data: {},
      };
   },
   methods: {
      async getIPData(ip: string) {
         try {
            const response = await axios.get(`${newsURL}&ipAddress=${ip}`, {
               withCredentials: false,
            });

            if (!response) {
               throw new Error("No data");
            }

            return response.data;
         } catch (error) {
            console.log(error);
         }
      },

      async getIPAddress(ip: string) {
         this.ip = ip;
         const data = await this.getIPData(this.ip);
         this.coordinates = [data?.location?.lng, data?.location?.lat];
         return;
      },
   },
});
</script>
