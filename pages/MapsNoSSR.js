import { MapContainer, TileLayer, Marker, useMap } from "react-leaflet";
import "leaflet/dist/leaflet.css";
import "leaflet-defaulticon-compatibility/dist/leaflet-defaulticon-compatibility.css";
import "leaflet-defaulticon-compatibility";
import React, { useEffect, useState } from "react";

export function ChangeView({ coords }) {
  const map = useMap();
  map.setView(coords);

  return null;
}

const Maps = ({ results }) => {
  const [geoData, setGeoData] = useState({ lat: 64.536634, lng: 16.779852 });
  useEffect(() => {
    setGeoData({ lat: results.latitude, lng: results.longitude });
  }, [results]);
  console.log(geoData);

  return (
    <MapContainer
      center={[geoData.lat, geoData.lng]}
      zoom={12}
      scrollWheelZoom={false}
      style={{
        height: "600px",
        width: "100%",
        position: "absolute",
        zIndex: "1",
      }}
    >
      <TileLayer
        attribution='&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
      />
      {geoData.lat && geoData.lng && (
        <Marker position={[geoData.lat, geoData.lng]} />
      )}
      <ChangeView coords={geoData} />
    </MapContainer>
  );
};

export default Maps;
