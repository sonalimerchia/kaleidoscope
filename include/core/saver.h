#include "visualizer/sketchpad.h"
#include <stdio.h>
#include <stdlib.h>
#include <nfd.h>

#ifndef KALEIDOSCOPE_INCLUDE_CORE_SAVER_H_
#define KALEIDOSCOPE_INCLUDE_CORE_SAVER_H_

namespace kaleidoscope {

class Saver {
 public:
  static void Save(const visualizer::Sketchpad &pad);
};
}

#endif //KALEIDOSCOPE_INCLUDE_CORE_SAVER_H_
