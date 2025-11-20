#pragma once
#include <Arduino.h>
#include <HX711.h>

struct ForceData {
  float cells[4];
  float lift, drag, moment;
};

class HX711Manager {
public:
  void begin(int dout1, int sck1, int dout2, int sck2);
  void readForces(ForceData &out);
  static void taskEntry(void *pv);

  // === ADICIONADO ===
  void tare();

private:
  HX711 hx1, hx2;

  long offset[2] = {0, 0};      // offsets para cada célula HX711
  float calibration[4] = {1,1,1,1};
};
