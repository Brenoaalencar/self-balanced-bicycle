#pragma once

#include "i2c_bus.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <math.h>

class IMU {
public:
    IMU();
    void init();
    float roll() const;
    float pitch() const;
    float roll_d() const;
    float pitch_d() const;
    void set_verbose(bool v);

private:
    static constexpr int PERIOD_MS = 4;
    static constexpr float GYRO_SCALE = 65.5f;
    static constexpr float ACCEL_SCALE = 4096.0f;

    float rate_roll, rate_pitch, rate_yaw;
    float acc_x, acc_y, acc_z;
    float angle_roll, angle_pitch;
    float kalman_roll, kalman_pitch;
    float kalman_unc_roll, kalman_unc_pitch;
    float last_roll, last_pitch;
    float roll_rate, pitch_rate;
    bool verbose;

    static void task_imu(void* pvParams);
    void kalman_1d(float& state, float& uncertainty, float input, float measurement, float& output, float& out_uncertainty);
};
