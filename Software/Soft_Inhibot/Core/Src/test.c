#include "test.h"
#include "tim.h"

enum
{
  RGB_LED_COUNT = 13,
  RGB_BYTES_PER_LED = 3,
  RGB_BITS_PER_BYTE = 8,
  RGB_FRAME_BITS = RGB_LED_COUNT * RGB_BYTES_PER_LED * RGB_BITS_PER_BYTE,
  RGB_DUMMY_SLOTS = 1
};

static uint8_t rgb_led_data[RGB_LED_COUNT][RGB_BYTES_PER_LED];
static union
{
  uint32_t alignment;
  uint16_t samples[RGB_FRAME_BITS + RGB_DUMMY_SLOTS];
} rgb_pwm_data;
static uint32_t rgb_bit_period_ticks;
static uint8_t rgb_hue;
static uint8_t rgb_is_initialized;

static void rgb_send_frame(void)
{
  uint32_t sample_index = 0;
  uint32_t zero_pulse_ticks = (rgb_bit_period_ticks * 28U) / 100U;
  uint32_t one_pulse_ticks = (rgb_bit_period_ticks * 56U) / 100U;
  uint32_t start_tick;

  if (rgb_is_initialized == 0U)
  {
    Error_Handler();
    return;
  }

  for (uint32_t led = 0; led < RGB_LED_COUNT; ++led)
  {
    for (uint32_t byte = 0; byte < RGB_BYTES_PER_LED; ++byte)
    {
      for (uint32_t bit = 0x80U; bit != 0U; bit >>= 1U)
      {
        rgb_pwm_data.samples[sample_index++] =
            ((rgb_led_data[led][byte] & bit) != 0U) ? (uint16_t)one_pulse_ticks : (uint16_t)zero_pulse_ticks;
      }
    }
  }
  rgb_pwm_data.samples[sample_index] = 1U;

  __HAL_TIM_SET_COUNTER(&htim1, 0U);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, rgb_pwm_data.samples[0]);
  if (HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)rgb_pwm_data.samples,
                            RGB_FRAME_BITS + RGB_DUMMY_SLOTS) != HAL_OK)
  {
    Error_Handler();
    return;
  }

  start_tick = HAL_GetTick();
  while (HAL_DMA_GetState(htim1.hdma[TIM_DMA_ID_CC1]) == HAL_DMA_STATE_BUSY)
  {
    if ((HAL_GetTick() - start_tick) >= 10U)
    {
      (void)HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
      Error_Handler();
      return;
    }
  }

  if (HAL_DMA_GetState(htim1.hdma[TIM_DMA_ID_CC1]) != HAL_DMA_STATE_READY)
  {
    (void)HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
    Error_Handler();
    return;
  }

  if (HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
    return;
  }
  HAL_Delay(1U);
}

static void rgb_store_led_hsv(uint8_t index, uint8_t h, uint8_t s, uint8_t v)
{
  uint16_t hue_position = (uint16_t)h * 6U;
  uint8_t sector = (uint8_t)(hue_position / 256U);
  uint16_t fraction = hue_position % 256U;
  uint32_t p = ((uint32_t)v * (255U - s)) / 255U;
  uint32_t q = ((uint32_t)v * (255U - ((uint32_t)s * fraction) / 255U)) / 255U;
  uint32_t t = ((uint32_t)v * (255U - ((uint32_t)s * (255U - fraction)) / 255U)) / 255U;
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  if (index >= RGB_LED_COUNT)
  {
    Error_Handler();
    return;
  }

  switch (sector)
  {
    case 0U:
      red = (uint8_t)v;
      green = (uint8_t)t;
      blue = (uint8_t)p;
      break;
    case 1U:
      red = (uint8_t)q;
      green = (uint8_t)v;
      blue = (uint8_t)p;
      break;
    case 2U:
      red = (uint8_t)p;
      green = (uint8_t)v;
      blue = (uint8_t)t;
      break;
    case 3U:
      red = (uint8_t)p;
      green = (uint8_t)q;
      blue = (uint8_t)v;
      break;
    case 4U:
      red = (uint8_t)t;
      green = (uint8_t)p;
      blue = (uint8_t)v;
      break;
    default:
      red = (uint8_t)v;
      green = (uint8_t)p;
      blue = (uint8_t)q;
      break;
  }

  rgb_led_data[index][0] = green;
  rgb_led_data[index][1] = red;
  rgb_led_data[index][2] = blue;
}

void setup_rgb(void)
{
  RCC_ClkInitTypeDef clock_config = {0};
  uint32_t flash_latency = 0;
  uint32_t timer_clock_hz;

  HAL_RCC_GetClockConfig(&clock_config, &flash_latency);
  timer_clock_hz = HAL_RCC_GetPCLK2Freq();
  if (clock_config.APB2CLKDivider != RCC_HCLK_DIV1)
  {
    timer_clock_hz *= 2U;
  }

  rgb_bit_period_ticks = (timer_clock_hz + 400000U) / 800000U;
  if (rgb_bit_period_ticks < 2U || rgb_bit_period_ticks > 65536U)
  {
    Error_Handler();
    return;
  }

  htim1.Init.Prescaler = 0U;
  htim1.Init.Period = rgb_bit_period_ticks - 1U;
  __HAL_TIM_SET_PRESCALER(&htim1, 0U);
  __HAL_TIM_SET_AUTORELOAD(&htim1, rgb_bit_period_ticks - 1U);

  for (uint32_t led = 0; led < RGB_LED_COUNT; ++led)
  {
    rgb_led_data[led][0] = 0U;
    rgb_led_data[led][1] = 0U;
    rgb_led_data[led][2] = 0U;
  }

  rgb_hue = 0U;
  rgb_is_initialized = 1U;
  rgb_send_frame();
}

void set_led_hsv(uint8_t index, uint8_t h, uint8_t s, uint8_t v)
{
  if (rgb_is_initialized == 0U)
  {
    Error_Handler();
    return;
  }

  if (index >= RGB_LED_COUNT)
  {
    Error_Handler();
    return;
  }

  rgb_store_led_hsv(index, h, s, v);
  rgb_send_frame();
}

void loop_rgb(void)
{
  if (rgb_is_initialized == 0U)
  {
    Error_Handler();
    return;
  }

  for (uint8_t led = 0; led < RGB_LED_COUNT; ++led)
  {
    rgb_store_led_hsv(led, rgb_hue, 255U, 30U);
  }
  rgb_send_frame();
  ++rgb_hue;
}
