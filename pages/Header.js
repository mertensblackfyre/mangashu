import React, { useEffect, useState } from "react";

import styles from "../styles/Home.module.css";
import { ChevronRightIcon } from "@heroicons/react/solid";
import dynamic from "next/dynamic";
const MapsNoSSR = dynamic(() => import("./MapsNoSSR.js"), { ssr: false });

const Header = () => {
  const [ipAddress, setIPAddress] = useState("");
  const [results, setResults] = useState([]);

  const handleSubmit = (e) => {
    e.preventDefault();
    getData();
    return ipAddress;
  };

  const getData = async () => {
    try {
      const res = await fetch(
        `https://ip-geolocation-ipwhois-io.p.rapidapi.com/json/?ip=${ipAddress}`,
        {
          method: "GET",
          headers: {
            "x-rapidapi-host": "ip-geolocation-ipwhois-io.p.rapidapi.com",
            "x-rapidapi-key":
              "6d47b7972emsha5bcdb005cde6b7p1c9062jsnee0862a69811",
          },
        }
      );
      const data = await res.json();
      setResults(data);

      return results;
    } catch (error) {
      console.log("Error");
    }
  };

  useEffect(() => {
    getData();

    return () => {
      getData();
    };
  }, []);

  return (
    <>
      <section className={styles.header}>
        <h1>IP Address Tracker</h1>
        <form className={styles.form} onSubmit={handleSubmit}>
          <input
            type="text"
            className={styles.input}
            placeholder="Search for any IP address or domain"
            name="IP"
            value={ipAddress}
            onChange={(e) => setIPAddress(e.target.value)}
          />
          <button type="submit" className={styles.btn} onSubmit={handleSubmit}>
            <ChevronRightIcon className={styles.icon} />
          </button>
        </form>
      </section>
      <section className={styles.infoContainer}>
        {Object.keys(results).map((key) => {
          if (
            key == "ip" ||
            key == "isp" ||
            key == "timezone_gmt" ||
            key == "region"
          ) {
            return (
              <article className={styles.onebox} key={key}>
                <strong>{key}</strong>
                <p>{results[key]}</p>
              </article>
            );
          }
        })}
      </section>

      <div id="map">
        <MapsNoSSR results={results} />
      </div>
    </>
  );
};

export default Header;
