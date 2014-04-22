#include "GPSReader.h"

GPSReader::GPSReader() {
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

void GPSReader::connectToGPS() {

	system("sudo pkill gpsd; gpsd /dev/ttyUSB0");
	system("sudo gpsd /dev/ttyUSB0 -F /var/run/gpsd.sock");

	gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

	if (gps_rec.stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
		cerr << "No GPSD running.\n";
	}
	m_gpsConnection = &gps_rec;
}

void GPSReader::readGPS() {
	struct gps_data_t* newdata;

	if (!m_gpsConnection->waiting(50000000)) {
		std::cout << "Been waiting for a long time now, pal!" << endl;
	}

	if ((newdata = m_gpsConnection->read()) == NULL) {
		cerr << "Read error.\n";
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