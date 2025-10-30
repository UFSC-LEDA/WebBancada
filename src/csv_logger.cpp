#include "csv_logger.h"

void appendCSV(String line) {
  File f = SPIFFS.open(CSV_FILENAME, FILE_APPEND);
  if(!f) return;
  f.println(line);
  f.close();
}
