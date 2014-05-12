#include "GPSReader.h"

GPSReader::GPSReader() {
	m_timestamp = "";
	m_latitude = 0;
	m_longitude = 0;
	m_altitude = 0;
	m_speed = 0;
	m_heading = 0;
	m_mode = 0;
	m_satellitesUsed = 0;
	m_gpsConnection = NULL;
}

GPSReader::~GPSReader() {
	if (m_gpsConnection != NULL) {
		delete m_gpsConnection;
	}
}

string GPSReader::secondsToTime(double seconds) {
	time_t rawtime = (time_t) seconds;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	return asctime(timeinfo);
}

void GPSReader::connectToGPS(string portName, string connectionName) {

	system(("sudo pkill gpsd; gpsd " + portName).c_str());
	system("sudo gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock");

	m_gpsConnection = new gpsmm(connectionName.c_str(), DEFAULT_GPSD_PORT);
	if (m_gpsConnection->stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
		throw "GPSReader::connectToGPS(), unable to connect to GPS.";
	}
}

void GPSReader::readGPS() {
	struct gps_data_t* newdata;

	if (!m_gpsConnection->waiting(50000000)) {
		throw "GPSReader::readGPS(), timeout.";
	}

	if ((newdata = m_gpsConnection->read()) == NULL) {
		throw "GPSReader::readGPS(), read error.";
	} else {
		m_timestamp = secondsToTime(newdata->fix.time);
		m_latitude = newdata->fix.latitude;
		m_longitude = newdata->fix.longitude;
		m_altitude = newdata->fix.altitude;
		m_speed = newdata->fix.speed;
		m_heading = newdata->fix.track;
		m_mode = newdata->fix.mode;
		m_satellitesUsed = newdata->satellites_used;
	}
}

string GPSReader::getTimestamp() {
	return m_timestamp;
}

double GPSReader::getLatitude() {
	return m_latitude;
}

double GPSReader::getLongitude() {
	return m_longitude;
}

double GPSReader::getAltitude() {
	return m_altitude;
}

double GPSReader::getSpeed() {
	return m_speed;
}

double GPSReader::getHeading() {
	return m_heading;
}

int GPSReader::getMode() {
	return m_mode;
}

int GPSReader::getSatellites_used() {
	return m_satellitesUsed;
}
