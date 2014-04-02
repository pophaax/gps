#ifndef __GPSREADER_H__
#define __GPSREADER_H__

#include <iostream>
#include <stdlib.h>
#include <libgpsmm.h>

using namespace std;

/**---------------------------------------
 *	USAGE:
 * 
 *	GPSReader g;
 *	gpsmm gps_rec = g.connectToGPS();
 *	g.readGPS(gps_rec);
 * 
 * 	COMPILATION:
 * 	
 * 	Flags: -lgps
 *----------------------------------------*/

class GPSReader {

private:
	string m_timestamp;
	double m_latitude;
	double m_longitude;
	double m_altitude;
	double m_speed;
	double m_heading;
	int m_mode;
	int m_satellitesUsed;
	string secondsToTime(double seconds);

public:

	/*Constructor*/
	GPSReader();

	/*Destructor*/
	~GPSReader();

	/*Sets up a connection to the USB-connected GPS*/
	gpsmm connectToGPS();

	/*Starts an endless loop that reads data from the GPS*/
	void readGPS(gpsmm &gps_rec);

	/*Returns the latest updated timestamp by the GPS*/
	string getTimestamp();

	/*Returns the latest updated latitude by the GPS*/
	double getLatitude();

	/*Returns the latest updated longitude by the GPS*/
	double getLongitude();

	/*Returns the latest updated altitude by the GPS - Only accurate if mode is 3*/
	double getAltitude();

	/*Returns the latest updated speed by the GPS*/
	double getSpeed();

	/*Returns the latest updated heading by the GPS - North is 0 degrees, 90 degrees is east*/
	double getHeading();

	/*Returns the latest updated mode by the GPS - Value 3 is the best*/
	int getMode();

	/*Returns the latest updated number of satellites by the GPS that the GPS has a connection to*/
	int getSatellites_used();
};

#endif
