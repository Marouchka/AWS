// Automatic Watering System (AWS)
// Object-oriented programming to eventually support multiple sensors/pump system
#include "pump.h"
#include "sensor.h"

class AWS{
	// Overarching "world" class containing the sensor and pump objects
	// Also eventually possible to connect to ThingSpeak via a Wifi shield

// private

public: 

  AWS();
  ~AWS();
  
  sensor * sensor1;
  pump * pump1;

};

