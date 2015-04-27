#include "GPSReader.h"
#include <sstream>

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
		m_timestamp = secondsToTimeStamp(newdata->fix.time);
		m_latitude = newdata->fix.latitude;
		std::cout << "GPS_TEST:" << newdata->fix.latitude << std::endl;
		m_longitude = newdata->fix.longitude;
		m_altitude = newdata->fix.altitude;
		m_speed = newdata->fix.speed;
		m_heading = newdata->fix.track;
		m_mode = newdata->fix.mode;
		m_satellitesUsed = newdata->satellites_used;
	}
}

std::string GPSReader::getTimestamp() {
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

int GPSReader::getSatellitesUsed() {
	return m_satellitesUsed;
}
