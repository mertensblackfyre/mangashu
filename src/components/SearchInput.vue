<template>
   <div class="flex flex-row absolute left-1/2 z-50">
      <input
         v-model="country"
         type="search"
         id="default-search"
         placeholder="Search countries..."
         required
      />
      <button
         @click="onChange(country)"
         type="submit"
         class="text-white bg-blue-700 focus:ring-4 focus:outline-none font-medium rounded-lg text-sm px-4 py-2 hover:bg-blue-700 focus:ring-blue-800"
      >
         Search
      </button>
   </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
   name: "SearchInput",
   data() {
      return {
         country: "",
      };
   },
   methods: {
      onChange(country: string) {
         this.country = country;
         this.$emit("get-country", this.country);
         return;
      },
   },
});
</script>
