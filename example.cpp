#include <iostream>
#include "GPSReader.h"

using namespace std;


int main() {

  GPSReader g;
  g.connectToGPS("/dev/ttyUSB0", "localhost");
  g.readGPS(50000000);
  std::cout << "latitude: " << g.getLatitude() << "\n";

}
