#pragma once

#include <cstdint>
#include <lvgl/lvgl.h>
#include "components/settings/Settings.h"
#include "displayapp/screens/Screen.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class SettingSleep : public Screen {
      public:
        SettingSleep(Pinetime::Controllers::Settings& settingsController);
        ~SettingSleep() override;
        void UpdateSelected(lv_obj_t* object, lv_event_t event);

      private:
        Controllers::Settings& settingsController;
        lv_obj_t* sleepThresh;
        lv_obj_t* btnPlus;
        lv_obj_t* btnMinus;
      };
    }
  }
}
