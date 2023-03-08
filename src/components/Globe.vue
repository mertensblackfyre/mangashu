<template>
   <div ref="mapContainer"></div>
</template>

<script lang="ts">
import mapboxgl from "mapbox-gl";
import "mapbox-gl/dist/mapbox-gl.css";
import { onMounted, ref } from "vue";

mapboxgl.accessToken =
   "pk.eyJ1IjoiYW1yODY0NCIsImEiOiJjbGV6c3VtbDYwMmc5M3RvNGU3NWcxNHppIn0.YbW3-ZtzO1MiNIPH4VPYHA";

const mapContainer = ref<HTMLElement>();

onMounted(() => {
   const map = new mapboxgl.Map({
      container: mapContainer.value,
      style: "mapbox://styles/mapbox/streets-v11",
      center: [-74.5, 40],
      zoom: 9,
      projection: "globe" as string,
   } as any);

   map.on("style.load", () => {
      map.setFog({});
   });
});

export default {
   name: "GlobeComponent",
};
</script>
