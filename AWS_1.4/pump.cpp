#include "pump.h"

// CONSTRUCTOR
pump::pump()
{
  
}

pump::pump(byte pin)
{
  // const byte pin: pin to power on/off the pump
  powerPin = pin;
}

// DESTRUCTOR
pump::~pump()
{
  
}

