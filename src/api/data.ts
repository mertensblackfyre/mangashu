import axios from "axios";
import { ref } from "vue";
const geoCodingURL = "https://api.geoapify.com/v1/geocode/search";

export const handleSubmit = async () => {
   const data = ref([]);
   const error = ref<null>(null);

   try {
      const response = await axios.get(
         `${geoCodingURL}?text=France&apiKey=f1ee77bd589648639821fc26719d7a45`,
         {
            withCredentials: false,
         }
      );
      if (!response) {
         throw new Error("No data");
      }
      data.value = await response.data;
      // const resp = await axios.get(
      //    `${newsURL}?country=${this.input}&apiKey=53ae439ca1624a9a9870e92d88f4bbdd`,
      //    {
      //       withCredentials: false,
      //    }
      // );
      // return {resp,response}
      console.log(data);
   } catch (err: any) {
      error.value = err;
      // console.log(error);
   }
   return { data, error };
};
