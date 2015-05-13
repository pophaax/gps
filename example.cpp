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

		std::cout << std::setprecision(10) << "lat: " << g.getLatitude() << ", long: " << g.getLongitude() << "\n";
		std::cout << "heading: " << g.getHeading() << ", speed: " << g.getSpeed() << "\n\n";
	}
}
