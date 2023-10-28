#include <lvgl/lvgl.h>
#include "displayapp/screens/Sleep.h"
#include "displayapp/DisplayApp.h"
#include "displayapp/screens/Symbols.h"
#include "displayapp/InfiniTimeTheme.h"
#include "components/motion/MotionController.h"

using namespace Pinetime::Applications::Screens;

Sleep::Sleep(Pinetime::Controllers::MotionController& motionController) : motionController{motionController} {
  lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(title, "You slept for");
  lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(title, lv_scr_act(), LV_ALIGN_IN_TOP_MID, 15, 15);

  sleepTime = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_style_local_text_font(sleepTime, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_42);
  lv_label_set_text_fmt(sleepTime, "%lu", motionController.GetSleepMinutes());
  lv_label_set_align(sleepTime, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(sleepTime, lv_scr_act(), LV_ALIGN_CENTER, 0, -20);
}

Sleep::~Sleep() {
  lv_obj_clean(lv_scr_act());
}
