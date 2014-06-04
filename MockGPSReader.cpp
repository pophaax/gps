#include "MockGPSReader.h"

MockGPSReader::MockGPSReader() {
	m_timestamp = "";
	m_latitude = 0;
	m_longitude = 0;
	m_altitude = 0;
	m_speed = 0;
	m_heading = 0;
	m_mode = 0;
	m_satellitesUsed = 0;
}

MockGPSReader::~MockGPSReader() {
}


void MockGPSReader::connectToGPS(string portName, string connectionName) {
}

void MockGPSReader::readGPS(int timeout) {
}

string MockGPSReader::getTimestamp() {
	return m_timestamp;
}

double MockGPSReader::getLatitude() {
	return m_latitude;
}

double MockGPSReader::getLongitude() {
	return m_longitude;
}

double MockGPSReader::getAltitude() {
	return m_altitude;
}

double MockGPSReader::getSpeed() {
	return m_speed;
}

double MockGPSReader::getHeading() {
	return m_heading;
}

int MockGPSReader::getMode() {
	return m_mode;
}

int MockGPSReader::getSatellitesUsed() {
	return m_satellitesUsed;
}

void MockGPSReader::setTimestamp(string timestamp) {
	m_timestamp = timestamp;
}

void MockGPSReader::setLatitude(double latitude) {
	m_latitude = latitude;
}

void MockGPSReader::setLongitude(double longitude) {
	m_longitude = longitude;
}

void MockGPSReader::setAltitude(double altitude) {
	m_altitude = altitude;
}

void MockGPSReader::setSpeed(double speed) {
	m_speed = speed;
}

void MockGPSReader::setHeading(double heading) {
	m_heading = heading;
}

void MockGPSReader::setMode(int mode) {
	m_mode = mode;
}

void MockGPSReader::setSatellitesUsed(int satellitesUsed) {
	m_satellitesUsed = satellitesUsed;
}
