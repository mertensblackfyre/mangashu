import React, { useEffect, useState } from "react";

const Maps = ({ results }: any) => {
   const [geoData, setGeoData] = useState({ lat: 64.536634, lng: 16.779852 });
   useEffect(() => {
      setGeoData({ lat: results.latitude, lng: results.longitude });
   }, [results]);

   return (
     
   );
};

export default Maps;
