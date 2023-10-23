#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class SettingSleep : public Screen {
      public:
        SettingSleep();
        ~SettingSleep() override;
      };
    }
  }
}
