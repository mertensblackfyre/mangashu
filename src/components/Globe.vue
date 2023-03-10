<template>
   <div ref="map" id="map" class="w-full h-full"></div>
</template>

<script lang="ts">
import mapboxgl from "mapbox-gl";
// import { onMounted, ref } from "vue";
import "mapbox-gl/dist/mapbox-gl.css";

export default {
   name: "GlobeComponent",
   props: ["coordinates", "country"],
   data() {
      return {
         map: {},
         coor: [this.coordinates[0], this.coordinates[1]],
      };
   },
   // const mapContainer = ref<HTMLElement>();
   mounted() {
      this.createMap();
   },
   //    setup() {
   //       mapboxgl.accessToken =
   //          "pk.eyJ1IjoiYW1yODY0NCIsImEiOiJja3pqemhkcDkwMnJyMnZtbndlb2Y2NnVjIn0.rlFLYSYDyp5BgsWIA2o9cQ";

   //       onMounted(() => {
   //          new mapboxgl.Map({
   //             container: mapContainer.value,
   //             style: "mapbox://styles/mapbox/streets-v12",
   //             center: [12.12, 12.12],
   //             zoom: 1,
   //             projection: "globe",
   //          } as any);
   //       });
   //    },
   methods: {
      async createMap() {
         try {
            mapboxgl.accessToken =
               "pk.eyJ1IjoiYW1yODY0NCIsImEiOiJja3pqemhkcDkwMnJyMnZtbndlb2Y2NnVjIn0.rlFLYSYDyp5BgsWIA2o9cQ";

            this.map = new mapboxgl.Map({
               container: "map",
               style: "mapbox://styles/mapbox/streets-v12",
               center: [39.3260685, 39.3260685],
               zoom: 1,
               projection: "globe" as any,
            });
         } catch (error: any) {
            console.log(error);
         }
      },
   },
};
</script>
