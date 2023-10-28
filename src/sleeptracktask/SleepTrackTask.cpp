#include <cstdint>
#include "sleeptracktask/SleepTrackTask.h"
#include "components/motion/MotionController.h"

using namespace Pinetime::Applications;

SleepTrackTask::SleepTrackTask(Pinetime::Controllers::MotionController& motionController, Pinetime::Controllers::Settings& settingsController) 
  : motionController {motionController}, settingsController {settingsController} {}

void SleepTrackTask::Start() {
  messageQueue = xQueueCreate(10, 1);

  if (pdPASS != xTaskCreate(SleepTrackTask::Process, "Sleeptrack", 1000, this, 0, &taskHandle)) {
    APP_ERROR_HANDLER(NRF_ERROR_NO_MEM);
  }
}

void SleepTrackTask::Process(void* instance) {
  auto* app = static_cast<SleepTrackTask*>(instance);
  app->Work();
}

void SleepTrackTask::Work() {
  // fill epochHistory buffer
  for (uint8_t i {0}; i < epochWindowSize; ++i) {
    epochHistory++;
    epochHistory[0] = SleepTrackTask::GetEpoch();
  }
  while (true) {
    epochHistory++;
    epochHistory[0] = SleepTrackTask::GetEpoch();
  }
  if (SleepTrackTask::GetActivity() < settingsController.GetSleepThresh()) {
    motionController.SetSleepMinutes(motionController.GetSleepMinutes() + 1);
  }
}

int16_t SleepTrackTask::GetEpoch() {
  int_16_t epoch {0};
  for (uint8_t i {1}; i < 15; ++i) {
    epoch += motionController.stats.zMean;
    xTaskDelay(4000); // delay for 4000 ticks? How long is a tick?
  }
  return epoch;
}

int16_t SleepTrackTask::GetActivity() {
  return (0.04*epochHistory[0] + 0.2*epochHistory[1] + 4*epochHistory[2] + 0.2*epochHistory[3] + 0.04*epochHistory[4]);
}


