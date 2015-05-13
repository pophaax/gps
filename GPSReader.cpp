#include "GPSReader.h"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iostream>

GPSReader::GPSReader() :
	m_model(GPSModel("",0,0,0,0,0,0))
{
	m_mode = 0;
	m_gpsConnection = NULL;
}

GPSReader::~GPSReader() {
	if (m_gpsConnection != NULL) {
		delete m_gpsConnection;
	}
}

std::string GPSReader::secondsToTimeStamp(double seconds) {
	time_t fullSeconds = static_cast<time_t>(seconds);
	double partSecond = seconds - fullSeconds;
	int partSecondsFourDecimals = static_cast<int>(partSecond * 10000.0 + 0.5);
	struct tm * timeinfo;
	timeinfo = localtime(&fullSeconds);
	char timeInfoBuffer[100];
	strftime(timeInfoBuffer, 100, "%F %T", timeinfo);
	std::string timeStamp(timeInfoBuffer);
	timeStamp.append(".");
	timeStamp.append(std::to_string(partSecondsFourDecimals));
	return timeStamp;
}

void GPSReader::connectToGPS() {

	//system(("sudo pkill gpsd; gpsd " + portName).c_str());
	//system("sudo gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock");

	m_gpsConnection = new gpsmm("localhost", DEFAULT_GPSD_PORT);
	if (m_gpsConnection->stream(WATCH_ENABLE | WATCH_JSON) == NULL) {

		throw "GPSReader::connectToGPS(), unable to connect to GPS.";
	}
}

void GPSReader::readGPS(int timeout) {
	struct gps_data_t* newdata;

	if (!m_gpsConnection->waiting(timeout)) {
		throw "GPSReader::readGPS(), timeout.";
	}

	if ((newdata = m_gpsConnection->read()) == NULL) {
		throw "GPSReader::readGPS(), read error.";
	} else {


		// (n & ( 1 << k )) >> k
		// TIME_SET		(1llu<<2)
		// LATLON_SET	(1llu<<4)

		unsigned long int flags = newdata->set;

		printf("TIME\t:%lu\t",(flags & ( 1 << 2 )) >> 2);
		printf("LATLON\t:%lu\n",(flags & ( 1 << 2 )) >> 4);




		m_model.timestamp = secondsToTimeStamp(newdata->fix.time);

		if(!std::isnan(newdata->fix.latitude)){
			m_model.latitude = newdata->fix.latitude;
		} else {
			m_model.latitude = 0;
		}

		if(!std::isnan(newdata->fix.longitude)){
			m_model.longitude = newdata->fix.longitude;
		} else {
			m_model.longitude = 0;
		}

		if(!std::isnan(newdata->fix.altitude)){
			m_model.altitude = newdata->fix.altitude;
		} else {
			m_model.altitude = 0;
		}

		if(!std::isnan(newdata->fix.speed)){
			m_model.speed = newdata->fix.speed;
		} else {
			m_model.speed = 0;
		}

		if(!std::isnan(newdata->fix.track)){
			m_model.heading = newdata->fix.track;
		} else {
			m_model.heading = 0;
		}

		m_mode = newdata->fix.mode;
		m_model.satellitesUsed = newdata->satellites_used;
	}
}

std::string GPSReader::getTimestamp() {
	return m_model.timestamp;
}

double GPSReader::getLatitude() {
	return m_model.latitude;
}

double GPSReader::getLongitude() {
	return m_model.longitude;
}

double GPSReader::getAltitude() {
	return m_model.altitude;
}

double GPSReader::getSpeed() {
	return m_model.speed;
}

double GPSReader::getHeading() {
	return m_model.heading;
}

int GPSReader::getMode() {
	return m_mode;
}

int GPSReader::getSatellitesUsed() {
	return m_model.satellitesUsed;
}

GPSModel GPSReader::getModel() {
	return m_model;
}
