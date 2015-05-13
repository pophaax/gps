#include <iostream>
#include <iomanip>
#include "GPSReader.h"
#include "MockGPSReader.h"


int main() {
	GPSReader g;
	try {
		g.connectToGPS();
	} catch(const char* msg) {
		std::cout << msg << std::endl;
	}

	while(true) {
		g.readGPS(50000000);

		std::cout<< "lat: " << g.getLatitude() << ", long: " << g.getLongitude()
				 << ", heading: " << g.getHeading() << ", speed: " << g.getSpeed()
				 << ", sat: " << g.getSatellitesUsed() << ", time: " << g.getTimestamp()
				 << std::endl << std::endl;
	}
}
