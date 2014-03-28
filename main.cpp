#include <iostream>
#include <thread> 
#include "GPSReader.h"

using namespace std; 

void startGPSReader(GPSReader g, gpsmm gps_rec)
{
  g.readGPS(gps_rec);
}

int main()
{
    GPSReader g;
    gpsmm gps_rec = g.connectToGPS();
	printf("Test"); 
    thread thread_gps(startGPSReader, g, gps_rec);
    thread_gps.join();
}
