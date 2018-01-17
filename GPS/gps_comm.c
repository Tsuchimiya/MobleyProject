#include "gps_comm.h"
#define SEUIL_DIST 0.00002

int initGPS = 0;
int go = 0;

double distanceBetweenPoints ( struct gps_data_t data, struct gps_data_t before){
    return sqrt(pow((data.fix.longitude-before.fix.longitude),2) + pow((data.fix.latitude-before.fix.latitude),2));
}

void initializeGPS(){
  initGPS=0;
  go = 1;
}

void *listenGPS(void * arg)
{
  int timeout=250000;
  int open;
  int nbMeasures=0;
  struct gps_data_t data;
  struct gps_data_t before;
  initGPS = 0;
  go = 0;
  if (open=gps_open("localhost","2947",&data)==-1)
    {
      printf("[GPS] ERROR: communication can't be opened");
      exit(-1);
    }
  gps_stream(&data, WATCH_ENABLE | WATCH_JSON, NULL);
  int jump = 0;
  while(1)
    {
      if (jump && stateVoiture == VOITURE_FORWARD)
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


		// TRES SALE TODO separer dans 2 threads differents
		if (go){
		 
		  if(initGPS>1)
		    {
		      printf("[GPS] update des coords\n");
		      // update des coordonnees
		      if (jump){
			jump =0;
		      }
		      else{
			jump = 1;

			if (distanceBetweenPoints(data,before) >= 0){
			  if(update_coords(data.fix.longitude,data.fix.latitude,before.fix.longitude,before.fix.latitude)==222){
			    printf("[GPS] reinit GPS \n");
			    initGPS=1;
			  }
			}else{
			  printf("[GPS] data et before trop collés, on fait avancer la voiture legerement \n");
			  sendVitesse(50);
			  stateVoiture = VOITURE_FORWARD;
			}
		      }
		    }else{
		    jump = 0;
		    initGPS = 0;
		    if (nbMeasures == 0){
		      before = data;
		      printf("[GPS] Before = %lf , %lf \n \n", data.fix.latitude, data.fix.longitude);
		    }

	    
		    printf("[GPS] init \n");
		    if (stateVoiture == VOITURE_STOPPED){
		      stateVoiture = VOITURE_FORWARD;
		      sendVitesse(50);
		    }
		    nbMeasures++; 
		    if (nbMeasures > 10){
		      initGPS = 2;
		      nbMeasures = 0;
		      sendVitesse(0);
		      stateVoiture=VOITURE_STOPPED;
		    }
		  }
		}

		if (DEBUG){
		  printf("latitude: %lf, longitude: %lf, speed: %lf, course: %lf, latt. error: %.2lf, long. error: %.2lf, timestamp: %lf\n",
			 data.fix.latitude, data.fix.longitude, data.fix.speed, data.fix.track, data.fix.epy, data.fix.epx, data.fix.time);
		}
	
		// maj des coords sur l'IHM
		
		majCoords(l,l1);
	  

	      } else {
	      printf("no GPS data available\n");
	    }
	  }
	}
    }
}

