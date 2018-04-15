// Core library for code-sense - IDE-based
#include "Energia.h"

// Include application, user and local libraries
#include "rtosGlobals.h"
#include "Event.h"

namespace ECG
{
  volatile unsigned *raw      = new unsigned[125];
  volatile unsigned *raw_swap = new unsigned[125];
  volatile bool     enable    = false;
  const int LOp   = P3_4;
  const int LOn   = P3_6;
  const int A_pin = A7;
  unsigned  fill_mks = 100;
};

Event EventOverload;

void setup()
{
    EventOverload.begin();
    EventUnload.begin();
    Serial.begin(9600);
}

void loop()
{
   EventOverload.waitFor();
   for(int j = 0; j < 150; j++)
   {
    Serial.println(raw_swap[j]);
   }
   delay(1500);
}

