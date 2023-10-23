#pragma once

#include "displayapp/screens/Screen.h"
#include <lvgl/lvgl.h>

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class Sleep : public Screen {
      public:
        Sleep();
        ~Sleep() override;
      };
    }
  }
}
