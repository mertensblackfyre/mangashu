<template>
   <div class="flex flex-row w-full">
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
export default {
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
      },
   },
};
</script>
