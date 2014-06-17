#ifndef __GPSREADER_H__
#define __GPSREADER_H__

#include <string>
#include <stdlib.h>
#include <libgpsmm.h>

using namespace std;

/**---------------------------------------
 *	USAGE:
 * 
 *	GPSReader g;
 *	g.connectToGPS(string portName, string connectionName);
 *	g.readGPS();
 * 
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
	gpsmm * m_gpsConnection;

	string secondsToTimeStamp(double seconds);
	string parseDate(int year, int mon, int day);
	string parseTime(int hour, int min, int sec);
	string parseDateTime(int year, int mon, int day, int hour, int min, int sec);

public:
	/*Constructor*/
	GPSReader();

	/*Destructor*/
	~GPSReader();

	/*Sets up a connection to the USB-connected GPS*/
	void connectToGPS();

	/*reads data from the GPS given a number of attempts and timeout for each attempt*/
	void readGPS(int timeout);

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
	int getSatellitesUsed();
};

#endif
