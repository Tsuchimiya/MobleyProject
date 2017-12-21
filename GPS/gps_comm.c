#include "gps_comm.h"




void *listenGPS(void * arg)
{
  int timeout=250000;
  int open;
  int nbMeasures=0;
  struct gps_data_t data;
  struct gps_data_t before;

  if (open=gps_open("localhost","2947",&data)==-1)
  {
    printf("[GPS] ERROR: communication can't be opened");
    exit(-1);
  }
  gps_stream(&data, WATCH_ENABLE | WATCH_JSON, NULL);

  while(1)
  {
    before=data;
    if (gps_waiting(&data, timeout))
    {
      if (gps_read(&data)==-1)
      {
        printf("[GPS] ERROR: no data\n");
      } else {
        if ((data.status == STATUS_FIX)
        && (data.fix.mode == MODE_2D || data.fix.mode == MODE_3D)
        && !isnan(data.fix.latitude)
        && !isnan(data.fix.longitude))
        {
          nbMeasures++; // peut poser pb et VA déborder à modifier
	  
          if(nbMeasures>3)
          {
            
	      // update des coordonnees
	    update_coords(data.fix.longitude,data.fix.latitude,before.fix.longitude,before.fix.latitude);
          }else{
	    sendVitesse(20);
	  }

	  if (DEBUG){
          printf("latitude: %lf, longitude: %lf, speed: %lf, course: %lf, latt. error: %.2lf, long. error: %.2lf, timestamp: %lf\n",
          data.fix.latitude, data.fix.longitude, data.fix.speed, data.fix.track, data.fix.epy, data.fix.epx, data.fix.time);

	  }

	  // maj des coords sur l'IHM
	  majCoords(data.fix.latitude,data.fix.longitude);
	


        } else {
          printf("no GPS data available\n");
        }
      }
    }
  }
}

