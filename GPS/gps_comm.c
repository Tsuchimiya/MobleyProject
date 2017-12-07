#include <gps.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

void computeCourse(gps_data_t* data, gps_data_t* before)
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
  } else if(dx>=0 ???? {
    course=atan2(dx/dy);
  }

  data->fix.track=course;
}

void main()
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
          before=data;
          if(nbMeasures>1)
          {
            computeCourse(&data, &before);
          }
          printf("latitude: %lf, longitude: %lf, speed: %lf, course: %lf, latt. error: %.2lf, long. error: %.2lf, timestamp: %lf\n",
          data.fix.latitude, data.fix.longitude, data.fix.speed, data.fix.track, data.fix.epy, data.fix.epx, data.fix.time);
        } else {
          printf("no GPS data available\n");
        }
      }
    }
  }
}
