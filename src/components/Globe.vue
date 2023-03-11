<template>
   <div ref="map" id="map" class="w-screen h-screen"></div>
</template>

<script lang="ts">
import mapboxgl from "mapbox-gl";

import "mapbox-gl/dist/mapbox-gl.css";
import { defineComponent, onUpdated } from "vue";

export default defineComponent({
   name: "GlobeComponent",
   props: ["coordinates", "country", "data"],
   data() {
      return {
         map: {},
      };
   },

   mounted() {
      this.createMap();
   },

   methods: {
      async createMap(): Promise<void> {
         try {
            mapboxgl.accessToken = process.env.VUE_APP_MAP_KEY;

            const map = new mapboxgl.Map({
               container: "map",
               style: "mapbox://styles/mapbox/streets-v12",
               center: this.coordinates,
               zoom: 1,
            });
            onUpdated(() => {
               map.flyTo({
                  center: this.coordinates,
                  zoom: 14,
               });
               new mapboxgl.Marker().setLngLat(this.coordinates).addTo(map);
            });
            return;
         } catch (error: any) {
            console.log(error);
         }
      },
   },
});
</script>
