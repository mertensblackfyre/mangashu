<template>
   <div class="flex flex-col justify-center items-center h-[100vh]">
      <div class="grid grid-cols-2 gap-4 px-2 w-full">
         <div
            class="flex flex-col items-start justify-center rounded-2xl bg-white bg-clip-border px-3 py-4 shadow-3xl shadow-shadow-500 dark:!bg-navy-700 dark:shadow-none"
         >
            <p class="text-sm text-gray-600">Education</p>
            <p class="text-base font-medium text-navy-700 dark:text-white">
               Stanford University
            </p>
         </div>

         <div
            class="flex flex-col justify-center rounded-2xl bg-white bg-clip-border px-3 py-4 shadow-3xl shadow-shadow-500 dark:!bg-navy-700 dark:shadow-none"
         >
            <p class="text-sm text-gray-600">Languages</p>
            <p class="text-base font-medium text-navy-700 dark:text-white">
               English, Spanish, Italian
            </p>
         </div>

         <div
            class="flex flex-col items-start justify-center rounded-2xl bg-white bg-clip-border px-3 py-4 shadow-3xl shadow-shadow-500 dark:!bg-navy-700 dark:shadow-none"
         >
            <p class="text-sm text-gray-600">Department</p>
            <p class="text-base font-medium text-navy-700 dark:text-white">
               Product Design
            </p>
         </div>

         <div
            class="flex flex-col justify-center rounded-2xl bg-white bg-clip-border px-3 py-4 shadow-3xl shadow-shadow-500 dark:!bg-navy-700 dark:shadow-none"
         >
            <p class="text-sm text-gray-600">Work History</p>
            <p class="text-base font-medium text-navy-700 dark:text-white">
               English, Spanish, Italian
            </p>
         </div>

         <div
            class="flex flex-col items-start justify-center rounded-2xl bg-white bg-clip-border px-3 py-4 shadow-3xl shadow-shadow-500 dark:!bg-navy-700 dark:shadow-none"
         >
            <p class="text-sm text-gray-600">Organization</p>
            <p class="text-base font-medium text-navy-700 dark:text-white">
               Simmmple Web LLC
            </p>
         </div>

         <div
            class="flex flex-col justify-center rounded-2xl bg-white bg-clip-border px-3 py-4 shadow-3xl shadow-shadow-500 dark:!bg-navy-700 dark:shadow-none"
         >
            <p class="text-sm text-gray-600">Birthday</p>
            <p class="text-base font-medium text-navy-700 dark:text-white">
               20 July 1986
            </p>
         </div>
      </div>
   </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";

export default defineComponent({
   name: "DataComponent",
});
</script>
