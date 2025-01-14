#include <cstdint>
#include "sleeptracktask/SleepTrackTask.h"
#include "components/motion/MotionController.h"

using namespace Pinetime::Applications;

SleepTrackTask::SleepTrackTask(Pinetime::Controllers::MotionController& motionController, Pinetime::Controllers::Settings& settingsController) 
  : motionController {motionController}, settingsController {settingsController} {}

void SleepTrackTask::Start() {
  messageQueue = xQueueCreate(10, 1);

  if (pdPASS != xTaskCreate(SleepTrackTask::Process, "Sleeptrack", 500, this, 0, &taskHandle)) {
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

    if (SleepTrackTask::GetActivity() < static_cast<int16_t>(settingsController.GetSleepThresh())) {
      motionController.SetSleepMinutes(motionController.GetSleepMinutes() + 1);
    }
  }
}

int16_t SleepTrackTask::GetEpoch() {
  int16_t epoch {0};
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = 4096;

  for (uint8_t i {1}; i < 15; ++i) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency); // delay for 4 seconds or 4096 ticks at 1024 Hz
    epoch = epoch + motionController.X() + motionController.Y() + motionController.Z();
  }
  return epoch;
}

int16_t SleepTrackTask::GetActivity() {
  return static_cast<int16_t>(0.04*epochHistory[0] + 0.2*epochHistory[1] + 1*epochHistory[2] + 0.2*epochHistory[3] + 0.04*epochHistory[4]);
}


