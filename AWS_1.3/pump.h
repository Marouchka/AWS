#include <Arduino.h> // Particularly for byte

class pump{

public:
  // member variables
  byte powerPin; // pin to power on/off (supports both digital and analog)
  
  // member functions
  pump(); // Constructor
  pump(byte pin); 
  ~pump(); // Destructor
  
  };
