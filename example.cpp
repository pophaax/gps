#include <iostream>
#include <iomanip>
#include "GPSReader.h"
#include "MockGPSReader.h"


int main() {
	GPSReader g;

	while(true) {
		try {
			g.readGPS(50000000);
		} catch(const char* msg) {
			std::cout << "ERROR:" << msg << std::endl;
		}
		std::cout << std::setprecision(10) << "lat: " << g.getLatitude() << ", long: " << g.getLongitude() << "\n";
		std::cout << "heading: " << g.getHeading() << ", speed: " << g.getSpeed() << "\n\n";
	}
}
