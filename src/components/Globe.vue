<template>
   <div ref="mapContainer" class="w-full h-full"></div>
</template>

<script lang="ts" setup>
import mapboxgl from "mapbox-gl";
import { onMounted, ref } from "vue";
import "mapbox-gl/dist/mapbox-gl.css";

mapboxgl.accessToken =
   "pk.eyJ1IjoiYW1yODY0NCIsImEiOiJja3pqemhkcDkwMnJyMnZtbndlb2Y2NnVjIn0.rlFLYSYDyp5BgsWIA2o9cQ";

const mapContainer = ref<HTMLElement>();
// console.log(lng);
// console.log(props);

onMounted(() => {
   const map = new mapboxgl.Map({
      container: mapContainer.value,
      style: "mapbox://styles/mapbox/streets-v12",
      center: [-74.5, 40],
      zoom: 1,
      projection: "globe",
   } as any);

   map.on("style.load", () => {
      map.setFog({});
   });
   // map.flyTo({
   //    zoom: 4,
   //    center: [],
   //    essential: true,
   // });
});
</script>

<script lang="ts">
export default {
   name: "GlobeComponent",
   data() {
      return {
         coor: [-74.5, 40],
      };
   },
};
</script>
