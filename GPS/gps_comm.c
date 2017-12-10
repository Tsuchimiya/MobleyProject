#include "gps_comm.h"

#define PI 3.14159265

void computeCourse(struct gps_data_t* data,struct gps_data_t* before)
{
  double toDeg = 180.0/PI;
  double course;
  double x2=data->fix.longitude;
  double x1=before->fix.longitude;
  double y2=data->fix.latitude;
  double y1=before->fix.latitude;
  double dx=x2-x1;
  double dy=y2-y1;

  if (dx==0 && dy==0) {
    course=0;
  } else if(dx==0 && dy>0) {
    course=0;
  } else if(dx>0 && dy!=0) {
    course=atan2(dx,dy)*toDeg;
  } else if(dx>0 && dy==0) { //atan2(dx,0) returns error
    course=90.0;
  } else if(dx==0 && dy<0) {
    course=180.0;
  } else if(dx<0 && dy!=0) {
    course=360.0+atan2(dx,dy)*toDeg;
  } else if(dx<0 && dy==0) {
    course=270.0;
  } else {
    printf("[GPS] course out of range\n");
  }

  data->fix.track=course;
}

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
          nbMeasures++;
          if(nbMeasures>1)
          {
            computeCourse(&data, &before);
          }

	  if (DEBUG){
          printf("latitude: %lf, longitude: %lf, speed: %lf, course: %lf, latt. error: %.2lf, long. error: %.2lf, timestamp: %lf\n",
          data.fix.latitude, data.fix.longitude, data.fix.speed, data.fix.track, data.fix.epy, data.fix.epx, data.fix.time);

	  }

	  majCoords(data.fix.latitude,data.fix.longitude);



        } else {
          printf("no GPS data available\n");
        }
      }
    }
  }
}
