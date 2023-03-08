import mapboxgl from "mapbox-gl";
import React, { useEffect, useRef, useState } from "react";

mapboxgl.accessToken = process.env.NEXT_PUBLIC_MAPBOX_GL_ACCESS_TOKEN ?? "";
const Map = () => {
   const [lng, setLng] = useState(-70.9);
   const [lat, setLat] = useState(42.35);
   const [zoom, setZoom] = useState(1);

   const mapContainer = useRef<any>(null);
   const map = useRef<mapboxgl.Map | any>(null);
   const [input, setInput] = useState("");

   useEffect(() => {
      if (map.current) return;
      map.current = new mapboxgl.Map({
         container: mapContainer.current,
         projection: "globe",
         style: "mapbox://styles/mapbox/streets-v12",
         center: [lng, lat],
         zoom: zoom,
      });
   });

   return (
      <main className="h-screen w-full ">
         <div className="absolute z-50 my-7 flex max-w-sm items-center justify-center bg-white sm:left-[40%]">
            <input
               //  className=""
               type="search"
               placeholder="Search..."
               onChange={(e: any) => setInput(e.target.value)}
            />
            <button type="submit">Search</button>
         </div>
         <div className="h-full w-full" ref={mapContainer} />
      </main>
   );
};

export default Map;
