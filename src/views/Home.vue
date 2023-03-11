<template>
   <main class="h-screen w-screen relative">
      <SearchInput @get-country="getCountry" />
      <GlobeComponent :coordinates="coordinates" :country="country" />
   </main>
</template>

<script lang="ts">
import SearchInput from "../components/SearchInput.vue";
import GlobeComponent from "../components/Globe.vue";
import axios from "axios";
// import lookup from "country-code-lookup";
import { defineComponent } from "vue";

const geoCodingURL = "https://api.geoapify.com/v1/geocode/search";
const newsURL = `https://newsapi.org/v2/top-headlines`;

export default defineComponent({
   name: "HomeView",
   components: {
      SearchInput,
      GlobeComponent,
   },
   data() {
      return {
         country: "Spain",
         coordinates: [21.21, -12.21],
      };
   },
   methods: {
      capitalizeFirstLetter(string: string): string {
         return string.charAt(0).toUpperCase() + string.slice(1);
      },
      async getGeoCodingData(country: string) {
         try {
            const response = await axios.get(
               `${geoCodingURL}?text=${country}&apiKey=${process.env.VUE_APP_GEO_CODER_KEY}`,
               {
                  withCredentials: false,
               }
            );
            if (!response) {
               throw new Error("No data");
            }

            return response.data;
         } catch (error) {
            console.log(error);
         }
      },
      async getNews(country: any) {
         try {
            const resp = await axios.get(
               `${newsURL}?country=${country}&apiKey=${process.env.VUE_APP_NEWS_KEY}`,
               {
                  withCredentials: false,
               }
            );
            return resp.data;
         } catch (error) {
            console.log(error);
         }
      },
      async getCountry(country: string) {
         this.country = country;
         // const countryCode = lookup.byCountry(
         //    this.capitalizeFirstLetter(country)
         // );
         // const data = await this.getNews(countryCode?.fips.toLowerCase());

         // console.log(data);

         const data = await this.getGeoCodingData(this.country);
         this.coordinates = data.features[0]["geometry"]["coordinates"];
         return;
      },
   },
});
</script>
