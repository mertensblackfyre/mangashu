import { useMap } from "react-leaflet";

export function ChangeView({ coords }) {
  const map = useMap();
  map.setView(coords, map.getZoom());

  return null;
}
