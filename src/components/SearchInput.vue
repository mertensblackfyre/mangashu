<template>
   <div class="max-w-2xl mx-auto my-3 absolute z-50 w-full left-1/2">
      <label
         for="default-search"
         class="mb-2 text-sm font-medium text-gray-900 sr-only"
         >Search</label
      >
      <div class="relative">
         <div
            class="flex absolute inset-y-0 left-0 items-center pl-3 pointer-events-none"
         >
            <svg
               class="w-5 h-5 text-gray-500"
               fill="none"
               stroke="currentColor"
               viewBox="0 0 24 24"
               xmlns="http://www.w3.org/2000/svg"
            >
               <path
                  stroke-linecap="round"
                  stroke-linejoin="round"
                  stroke-width="2"
                  d="M21 21l-6-6m2-5a7 7 0 11-14 0 7 7 0 0114 0z"
               ></path>
            </svg>
         </div>
         <input
            v-model="search"
            type="search"
            id="default-search"
            placeholder="Search countries..."
            required
         />
         <button
            @click="handleInput(search)"
            type="submit"
            class="text-white absolute right-2.5 bottom-2.5 bg-blue-700 focus:ring-4 focus:outline-none font-medium rounded-lg text-sm px-4 py-2 hover:bg-blue-700 focus:ring-blue-800"
         >
            Search
         </button>
      </div>
   </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
   name: "SearchInput",
   data() {
      return {
         search: "",
      };
   },
   methods: {
      handleInput(search: string) {
         this.search = search;
         this.$emit("searchInput", this.search);
      },
   },
});
</script>
