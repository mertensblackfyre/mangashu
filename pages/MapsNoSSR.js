import { MapContainer, TileLayer, Marker, Popup } from "react-leaflet";
import "leaflet/dist/leaflet.css";
import "leaflet-defaulticon-compatibility/dist/leaflet-defaulticon-compatibility.css";
import "leaflet-defaulticon-compatibility";

const Maps = ({ results }) => {
  console.log(results.latitude);

  return (
    <MapContainer
      center={[59.2322, -12.42221]}
      zoom={14}
      scrollWheelZoom={false}
      style={{
        height: "800px",
        width: "100%",
        position: "absolute",
        zIndex: "1",
      }}
    >
      <TileLayer
        attribution='&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
        url="https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png"
      />
      <Marker position={[59.2322, -12.42221]} draggable={true} animate={true}>
        <Popup>Hey ! you found me</Popup>
      </Marker>
    </MapContainer>
  );
};

export default Maps;
