#include <Arduino.h>
#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Define the GPIO pin number for the PWM signal
const uint pwm_pin = 15;

// Define the PWM signal frequency and duty cycle
const uint32_t pwm_frequency = 175000; // 175 kHz
const float duty_cycle = 50.0; // 50%

// Defines the top value for the PWM counter
const uint16_t PWM_WRAP = 8;

void setup()
{
  // Configure the PWM signal
  gpio_set_function(pwm_pin, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(pwm_pin);

  // Set the PWM frequency
  pwm_set_clkdiv(slice_num, (float)clock_get_hz(clk_sys) / (pwm_frequency * (1 << PWM_WRAP)));

  // Set the PWM duty cycle
  uint16_t wrap_value = (1 << PWM_WRAP) - 1;
  uint16_t level = (uint16_t)(wrap_value * (duty_cycle / 100.0));
  pwm_set_wrap(slice_num, wrap_value);
  pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pwm_pin), level);
  pwm_set_enabled(slice_num, true);
}

void loop()
{
  tight_loop_contents();
}
