/* eslint-disable react-hooks/rules-of-hooks */
import Head from "next/head"
import axios from "axios"

import { Button } from "@/components/ui/button"
import { Input } from "@/components/ui/input"
import "mapbox-gl/dist/mapbox-gl.css"
import mapboxgl from "mapbox-gl"

import "mapbox-gl/dist/mapbox-gl.css"
import React, { useEffect, useRef, useState } from "react"

import { Card } from "@/components/Card"

mapboxgl.accessToken =
  "pk.eyJ1IjoiYW1yODY0NCIsImEiOiJjbGV6c3VtbDYwMmc5M3RvNGU3NWcxNHppIn0.YbW3-ZtzO1MiNIPH4VPYHA"

const geoCodingURL = "https://api.geoapify.com/v1/geocode/search"

const newsURL = `https://newsapi.org/v2/top-headlines`
export default function IndexPage() {
  const [lng, setLng] = useState(-70.9)
  const [lat, setLat] = useState(42.35)
  const [zoom, setZoom] = useState(1)

  const mapContainer = useRef<any>(null)
  const map = useRef<mapboxgl.Map | any>(null)
  const [input, setInput] = useState("")

  useEffect(() => {
    if (map.current) return
    map.current = new mapboxgl.Map({
      container: mapContainer.current,
      projection: "globe",
      style: "mapbox://styles/mapbox/streets-v12",
      center: [lng, lat],
      zoom: zoom,
    })
  })

  const handleSub = async () => {
    try {
      const response = await axios.get(
        `${geoCodingURL}?text=${input}&apiKey=f1ee77bd589648639821fc26719d7a45`,
        {
          withCredentials: false,
        }
      )
      // "country=us&" +
      // "apiKey=53ae439ca1624a9a9870e92d88f4bbdd"
      const resp = await axios.get(
        `${newsURL}?country=${input}&apiKey=53ae439ca1624a9a9870e92d88f4bbdd`,
        {
          withCredentials: false,
        }
      )
      console.log(resp.data)

      // setLng(response?.data?.features[0].geometry.coordinates[0])
      // setLat(response?.data?.features[0].geometry.coordinates[1])

      new mapboxgl.Marker({
        color: "#123131",
        scale: 0.6,
      })
        .setLngLat([
          response?.data?.features[0].geometry.coordinates[0],
          response?.data?.features[0].geometry.coordinates[1],
        ])
        .setPopup(
          new mapboxgl.Popup().setHTML(`
            <div class="max-w-sm bg-white border border-gray-200 rounded-lg shadow dark:bg-gray-800 dark:border-gray-700">
                <a href="#">
                    <img class="rounded-t-lg" src="/docs/images/blog/image-1.jpg" alt="" />
                </a>
                <div class="p-5">
                    <a href="#">
                        <h5 class="mb-2 text-2xl font-bold tracking-tight text-gray-900 dark:text-white">Noteworthy technology acquisitions 2021</h5>
                    </a>
                    <p class="mb-3 font-normal text-gray-700 dark:text-gray-400">Here are the biggest enterprise technology acquisitions of 2021 so far, in reverse chronological order.</p>
                    <a href="#" class="inline-flex items-center px-3 py-2 text-sm font-medium text-center text-white bg-blue-700 rounded-lg hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800">
                        Read more
                        <svg aria-hidden="true" class="w-4 h-4 ml-2 -mr-1" fill="currentColor" viewBox="0 0 20 20" xmlns="http://www.w3.org/2000/svg"><path fill-rule="evenodd" d="M10.293 3.293a1 1 0 011.414 0l6 6a1 1 0 010 1.414l-6 6a1 1 0 01-1.414-1.414L14.586 11H3a1 1 0 110-2h11.586l-4.293-4.293a1 1 0 010-1.414z" clip-rule="evenodd"></path></svg>
                    </a>
                </div>
            </div>
            `)
        )
        .addTo(map.current)

      map.current.flyTo({
        zoom: 4,
        center: [
          response?.data?.features[0].geometry.coordinates[0],
          response?.data?.features[0].geometry.coordinates[1],
        ],
        essential: true,
      })
    } catch (error) {
      console.log(error)
    }
  }
  return (
    <>
      <Head>
        <title>Next.js</title>
        <meta
          name="description"
          content="Next.js template for building apps with Radix UI and Tailwind CSS"
        />
        <meta name="viewport" content="width=device-width, initial-scale=1" />
        <link rel="icon" href="/favicon.ico" />
      </Head>
      <main className="relative h-screen w-full ">
        <div className="absolute z-50 my-7 flex max-w-sm items-center justify-center bg-white sm:left-[40%]">
          <Input
            type="search"
            placeholder="Search..."
            onChange={(e: any) => setInput(e.target.value)}
          />
          <Button type="submit" onClick={handleSub}>
            Search
          </Button>
        </div>
        <div className="h-full w-full" ref={mapContainer} />
      </main>
    </>
  )
}
