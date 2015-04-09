#include <iostream>
#include <iomanip>
#include "GPSReader.h"
#include "MockGPSReader.h"


int main() {
	MockGPSReader g;
	try {
		g.connectToGPS();
		g.readGPS(50000000);
//		cout << "latitude: " << g.getLatitude() << endl;
	} catch(const char* msg) {
		std::cout << msg << std::endl;
	}

	for (int i = 0; i < 5; i++) {
		g.setDataFromCommands(5984, 5824);
		std::cout << std::setprecision(10) << "lat: " << g.getLatitude() << ", long: " << g.getLongitude() << "\n";
		std::cout << "heading: " << g.getHeading() << ", speed: " << g.getSpeed() << "\n\n";
	}
}
