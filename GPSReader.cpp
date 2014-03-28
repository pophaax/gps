#include "GPSReader.h"

GPSReader::GPSReader() {
}

string GPSReader::secondsToTime(double seconds)
{
  time_t rawtime=(time_t) seconds;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  return asctime(timeinfo);
}

gpsmm GPSReader::connectToGPS() {
  
    system("sudo pkill gpsd; gpsd /dev/ttyUSB0");
    system("sudo gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock");
    
    gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
  
    if (gps_rec.stream(WATCH_ENABLE|WATCH_JSON) == NULL) {
	cerr << "No GPSD running.\n";
    }
    
    return gps_rec;
}

void GPSReader::readGPS(gpsmm &gps_rec) {

	struct gps_data_t* newdata;
	
	if (!gps_rec.waiting(50000000)) {
	  std::cout << "Been waiting for a long time now, pal!" << endl;
	}
	

	if ((newdata = gps_rec.read()) == NULL) {
	    cerr << "Read error.\n";
	} else {

		timestamp = secondsToTime(newdata->fix.time);

		latitude = newdata->fix.latitude;

		 longitude = newdata->fix.longitude;

		 altitude = newdata->fix.altitude;

		 speed = newdata->fix.speed;

		 heading = newdata->fix.track;

		 mode = newdata->fix.mode;

	  satellites_used = newdata->satellites_used;
	}
}

string GPSReader::getTimestamp() {
  return timestamp;
}

double GPSReader::getLatitude() {
  return latitude;
}

double GPSReader::getLongitude() {
  return longitude;
}

double GPSReader::getAltitude() {
  return altitude;
}

double GPSReader::getSpeed() {
  return speed;
}

double GPSReader::getHeading() {
  return heading;
}

int GPSReader::getMode() {
  return mode;
}

int GPSReader::getSatellites_used() {
  return satellites_used;
}

GPSReader::~GPSReader() {

  
}