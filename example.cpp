#include <iostream>
#include "GPSReader.h"

using namespace std;


int main() {
	try {
		GPSReader g;
		g.connectToGPS("/dev/ttyUSB0", "localhost");
		g.readGPS(50000000);
		cout << "latitude: " << g.getLatitude() << endl;
	} catch(const char* msg) {
		cout << msg << endl;
	}
}
