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

std::string GPSReader::parseDate(int year, int mon, int day) {
	std::stringstream sstm;

	sstm << (year+1900) << "-";
	if(mon < 10) sstm << "0";
	sstm << mon << "-";
	if(day < 10) sstm << "0";
	sstm << day;

	return sstm.str();
}

std::string GPSReader::parseTime(int hour, int min, int sec) {
	std::stringstream sstm;

	if(hour < 10) sstm << "0";
	sstm << hour << ":";
	if(min < 10) sstm << "0";
	sstm << min << ":";
	if(sec < 10) sstm << "0";
	sstm << sec;

	return sstm.str();
}

std::string GPSReader::parseDateTime(int year, int mon, int day, int hour, int min, int sec) {
	return parseDate(year, mon, day)+" "+parseTime(hour, min, sec);
}

std::string GPSReader::secondsToTimeStamp(double seconds) {
	time_t rawtime = (time_t) seconds;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return parseDateTime(
		timeinfo->tm_year,
		timeinfo->tm_mon,
		timeinfo->tm_mday,
		timeinfo->tm_hour,
		timeinfo->tm_min,
		timeinfo->tm_sec
	);
}

void GPSReader::connectToGPS() {

	//system(("sudo pkill gpsd; gpsd " + portName).c_str());
	//system("sudo gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock");

	m_gpsConnection = new gpsmm("localhost::isnanst", DEFAULT_GPSD_PORT);
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
