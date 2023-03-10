<template>
   <div ref="map" id="map" class="w-full h-full"></div>
</template>

<script lang="ts">
import mapboxgl from "mapbox-gl";

import "mapbox-gl/dist/mapbox-gl.css";
import { onUpdated } from "vue";

export default {
   name: "GlobeComponent",
   props: ["coordinates", "country"],
   data() {
      return {
         map: {},
      };
   },

   mounted() {
      this.createMap();
   },

   methods: {
      async createMap() {
         try {
            mapboxgl.accessToken =
               "pk.eyJ1IjoiYW1yODY0NCIsImEiOiJja3pqemhkcDkwMnJyMnZtbndlb2Y2NnVjIn0.rlFLYSYDyp5BgsWIA2o9cQ";

            const map = new mapboxgl.Map({
               container: "map",
               style: "mapbox://styles/mapbox/streets-v12",
               center: this.coordinates,
               zoom: 1,
            });
            onUpdated(() => {
               map.flyTo({
                  center: this.coordinates,
                  zoom: 4,
               });
            });
         } catch (error: any) {
            console.log(error);
         }
      },
   },
};
</script>
