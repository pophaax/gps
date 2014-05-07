#include <iostream>
#include "GPSReader.h"

using namespace std;


int main() {

  GPSReader g;
  g.connectToGPS();
  std::cout << "latitude: " << g.getLatitude() << "\n";

}
