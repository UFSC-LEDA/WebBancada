#include "hx711_manager.h"
#include "settings.h"

void HX711Manager::begin(int dout1, int sck1, int dout2, int sck2) {
  hx1.begin(dout1, sck1);
  hx2.begin(dout2, sck2);

  hx1.set_gain(128);
  hx2.set_gain(128);
}

void HX711Manager::tare() {
  hx1.tare();
  hx2.tare();

  offset[0] = hx1.get_offset();
  offset[1] = hx2.get_offset();

  Serial.println("HX711: tare executado");
}

void HX711Manager::readForces(ForceData &out) {
  out.cells[0] = hx1.get_units(1) * calibration[0];
  out.cells[1] = hx1.get_units(1) * calibration[1];
  out.cells[2] = hx2.get_units(1) * calibration[2];
  out.cells[3] = hx2.get_units(1) * calibration[3];

  out.lift   = (out.cells[0] + out.cells[1]) / 2.0;
  out.drag   = out.cells[3];
  out.moment = out.cells[2];
}

void HX711Manager::taskEntry(void *pv) {
  HX711Manager *self = (HX711Manager*)pv;
  while (true) {
    ForceData f;
    self->readForces(f);
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
