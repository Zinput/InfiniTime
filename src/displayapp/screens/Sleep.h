#pragma once

#include <cstdint>
#include <lvgl/lvgl.h>
#include "components/motion/MotionController.h"
#include "displayapp/screens/Screen.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class Sleep : public Screen {
      public:
        Sleep(Pinetime::Controllers::MotionController& motionController);
        ~Sleep() override;
      private:
        Controllers::MotionController& motionController;
        lv_obj_t* sleepTime;
      };
    }
  }
}
