import React, { useEffect, useState } from "react";
import { MapContainer, TileLayer, Marker, Popup } from "react-leaflet";
import "leaflet/dist/leaflet.css";
import "leaflet-defaulticon-compatibility/dist/leaflet-defaulticon-compatibility.css";
import "leaflet-defaulticon-compatibility";

import { ChangeView } from "./ChangeView.js";

const Maps = ({ results }) => {
  const [geoData, setGeoData] = useState({ lat: 64.536634, lng: 16.779852 });
  useEffect(() => {
    setGeoData({ lat: results.latitude, lng: results.longitude });
  }, [results]);

  return (
    <MapContainer
      center={[geoData.lat, geoData.lng]}
      zoom={12}
      doubleClickZoom={true}
      scrollWheelZoom={true}
      dragging={true}
      animate={true}
      scrollWheelZoom={false}
      style={{
        height: "700px",
        width: "100%",
        position: "absolute",
        zIndex: "1",
      }}
    >
      {geoData.lat && geoData.lng && (
        <ChangeView coords={[geoData.lat, geoData.lng]} zoom={20} />
      )}

      <TileLayer
        url={`https://api.mapbox.com/styles/v1/mapbox/streets-v11/tiles/256/{z}/{x}/{y}@2x?access_token=pk.eyJ1IjoiYW1yODY0NCIsImEiOiJja3pqemhkcDkwMnJyMnZtbndlb2Y2NnVjIn0.rlFLYSYDyp5BgsWIA2o9cQ`}
        attribution='Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, <a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery &copy; <a href="https://www.mapbox.com/">Mapbox</a>'
      />
      {geoData.lat && geoData.lng && (
        <Marker position={[geoData.lat, geoData.lng]}>
          <Popup position={[geoData.lat, geoData.lng]}>
            Current Position: {geoData.lat}, {geoData.lng}
          </Popup>
        </Marker>
      )}
    </MapContainer>
  );
};

export default Maps;
