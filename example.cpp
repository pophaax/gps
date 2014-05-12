#include <iostream>
#include "GPSReader.h"

using namespace std;


int main() {

  GPSReader g;
  g.connectToGPS("/dev/ttyUSB0", "localhost");
  std::cout << "latitude: " << g.getLatitude() << "\n";

}
