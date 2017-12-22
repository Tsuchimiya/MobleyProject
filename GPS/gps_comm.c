#include "gps_comm.h"


int initGPS = 0;

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
  int jump = 0;
  while(1)
  {
    if (jump)
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
         
	  double l = data.fix.latitude;
	  double l1 = data.fix.longitude;
          if(initGPS>=1)
          {
            printf("[GPS] update des coords\n");
	      // update des coordonnees
	    if (jump){
	      jump = 0;
	    }
	    else{
	      jump = 1;
	      update_coords(data.fix.longitude,data.fix.latitude,before.fix.longitude,before.fix.latitude);
	    }
          }else{
	    if (jump){
	      jump = 0;
	    }
	    else{
	      jump = 1;
	    }
	    
	    printf("[GPS] init \n");
	    sendVitesse(40);
		 nbMeasures++; 
		if (nbMeasures > 10){
			initGPS = 2;
			nbMeasures = 0;
		}
	  }

	  if (DEBUG){
          printf("latitude: %lf, longitude: %lf, speed: %lf, course: %lf, latt. error: %.2lf, long. error: %.2lf, timestamp: %lf\n",
          data.fix.latitude, data.fix.longitude, data.fix.speed, data.fix.track, data.fix.epy, data.fix.epx, data.fix.time);
	  }
	
	  // maj des coords sur l'IHM
		
	//  majCoords(l,l1);
	  

        } else {
          printf("no GPS data available\n");
        }
      }
    }
  }
}

