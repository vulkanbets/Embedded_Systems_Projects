#ifndef MYPWM_HPP
#define MYPWM_HPP

// Define the GPIO pin number for the PWM signal
const uint pwm_pin = 14;

// Define the PWM signal frequency and duty cycle
const uint32_t pwm_frequency = 100000; // 100 kHz
const float duty_cycle = 50.0; // 50%

// Defines the top value for the PWM counter
const uint16_t PWM_WRAP = 8;

// Get the slice number of the pwm pin
const uint slice_num = pwm_gpio_to_slice_num(pwm_pin);

// Calculate the PWM duty cycle
const uint16_t wrap_value = (1 << PWM_WRAP) - 1;
const uint16_t level = (uint16_t)(wrap_value * (duty_cycle / 100.0));

void SetUpPinPwm()
{
  // Set the PWM frequency
  pwm_set_clkdiv(slice_num, (float)clock_get_hz(clk_sys) / (pwm_frequency * (1 << PWM_WRAP)));

  // Set the PWM duty cycle
  pwm_set_wrap(slice_num, wrap_value);
  pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pwm_pin), level);
}

void StartPwmSckClock()
{
  gpio_set_function(pwm_pin, GPIO_FUNC_PWM);  // Configure the PWM signal
  pwm_set_enabled(slice_num, true);   // <-- Activate PWM Signal on PIN "pwm_pin"
}

void ResetPwmSckClock()
{
  delayMicroseconds(1);
  pwm_set_enabled(slice_num, false);   // De-activate PWM Signal on PIN "pwm_pin"
  pinMode(pwm_pin, OUTPUT);     // <-- Set pwm_pin to digital pin & as an output.
  digitalWrite(pwm_pin, HIGH);  // <-- Set the pwm_pin to HIGH. SCK should Idle on High.
}

#endif // MYPWM_HPP