import { MapContainer, TileLayer, Marker, Popup } from "react-leaflet";
import "leaflet/dist/leaflet.css";
import "leaflet-defaulticon-compatibility/dist/leaflet-defaulticon-compatibility.css";
import "leaflet-defaulticon-compatibility";
import React, { useEffect, useState } from "react";
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
        height: "500px",
        width: "100%",
        position: "absolute",
        zIndex: "1",
      }}
    >
      {geoData.lat && geoData.lng && (
        <ChangeView coords={[geoData.lat, geoData.lng]} zoom={15} />
      )}

      <TileLayer
        attribution='&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
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
