#pragma once
#include <cstdint>
#include <task.h>
#include <queue.h>
#include "utility/CircularBuffer.h"
#include "components/settings/Settings.h"

namespace Pinetime {
  namespace Applications {
    class SleepTrackTask {
    public:
      explicit SleepTrackTask(Pinetime::Controllers::MotionController& motionController, Pinetime::Controllers::Settings& settingsController);
      void Start();
      void Work();
      
    private:
      static void Process(void* instance);
      int16_t GetEpoch();
      int16_t GetActivity();
      static constexpr uint8_t epochWindowSize {5};
      
      Utility::CircularBuffer<int16_t, epochWindowSize> epochHistory {};
      TaskHandle_t taskHandle;
      QueueHandle_t messageQueue;
      Controllers::MotionController& motionController;
      Controllers::Settings& settingsController;
    };
  }
}
