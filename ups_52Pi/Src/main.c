/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
ADC_ChannelConfTypeDef sConfig = {0};
ADC_AnalogWDGConfTypeDef AnalogWDGConfig = {0};
RTC_HandleTypeDef hrtc;

IWDG_HandleTypeDef hiwdg;

TIM_HandleTypeDef htim3;


#define V_IN_THRESHOLD 1200

#define bool uint16_t
#define false 0
#define true 1
	
#define START_TIME_RPI 75 //x1 seconds
#define HALT_TIME_RPI 7  //x1 seconds
#define PAUSE_TIME 17 //x0.1 seconds

struct AnalogFilter{
	uint16_t in_value;
	uint16_t time_rate;
	uint16_t analog_limit;
	uint16_t time_count;
	bool trip;
};


struct SwitchFilter{
	bool outstate;
	uint16_t scanrate;
	GPIO_TypeDef * port;
	uint16_t pin;
	uint16_t curr_scan;
};

struct Timer_v_in{
	bool timer_v_in_trigger;
  uint16_t timer_v_in_on;
  uint16_t timer_v_in_off;
	uint16_t timer_v_off_pause;
};

uint16_t v_rpi, v_in, v_bat = 0;

 
int tmp, im = 0;
bool halt = false;

struct AnalogFilter pa0,pa1,pa2; // analog pin filter
struct SwitchFilter key_k1; //switch key filter
struct Timer_v_in  timer_v_in; //startup and shutdown timer


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_IWDG_Init(void);
static void MX_TIM3_Init(void);


/**
  * @brief  The application entry point.
  * @retval int
  */
	

	
bool AnalogPinTrip(struct AnalogFilter * ana)
{
  if (ana->analog_limit == 0) return false;
 	
	if (ana->in_value > ana->analog_limit)
	{
		if (ana->time_count >= ana->time_rate)
		{
			ana->trip=true;
		} else
		  ana->time_count++;
	} else
  {	
	  ana->time_count = 0;
		ana->trip=false;
	}
	return ana->trip;
}

void InitAnalogPins(void)
{
	//v_rpi
	pa0.trip = false;
	pa0.in_value = 0;
	pa0.time_rate = 3;
	pa0.time_count = 0;
	pa0.analog_limit = 2440; //0.8*5.08 volts

	//v_bat
  pa1.trip = false;
	pa1.in_value = 0;
	pa1.time_rate = 3;
	pa1.time_count = 0;
	pa1.analog_limit = 1613; //2.7 volts  -> battery discharged
	
	//v_in
  pa2.trip = false;
	pa2.in_value = 0;
	pa2.time_rate = 3; // 0.3 sec waiting for v_in supplying 
	pa2.time_count = 0;
	pa2.analog_limit = V_IN_THRESHOLD; //0.8*5.12 volts	
}



bool _switch_filter(struct SwitchFilter * source)
{	
	if (!(HAL_GPIO_ReadPin(source->port,source->pin)))
	{
		if (source->curr_scan >= source->scanrate){	
		    
			source->outstate = true;
		} else
	
		source->curr_scan++;
		
		
		if  (source->scanrate == 0xFFFF) source->curr_scan = 0;
		
	} else
	{
	    source->curr_scan = 0;	
			source->outstate = false;
	}

	
	return source->outstate;
}

void InitSwitches(void)
{
	 //Onboard Key K1

		key_k1.outstate = false;
	  key_k1.port = GPIOB;
	  key_k1.pin = GPIO_PIN_1;
	  key_k1.scanrate = 4;
}

void InitTimer_v_in(void)
{
	 timer_v_in.timer_v_in_on = 0;
	 timer_v_in.timer_v_in_off = 0;
	 timer_v_in.timer_v_in_trigger = false;
	 timer_v_in.timer_v_off_pause = 0;
}

uint32_t GetADC_Value(uint32_t channel)
{

		uint32_t g_ADCValue = 0;
		sConfig.Channel = channel;

		sConfig.Rank = 1;

		sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5; //or any other value available.

		//add to channel select

		if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
		{
				return -1;
		}
    HAL_ADC_Start(&hadc);
		

		if (HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY) == HAL_OK)
			
		g_ADCValue = HAL_ADC_GetValue(&hadc);

		//remove from channel select

		HAL_ADC_Stop(&hadc);
		
		sConfig.Rank = ADC_RANK_NONE;

		if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
		{
			return -1;
		}

		return (g_ADCValue);
}

void Switch_out_rpi(uint16_t state)
{
	  if (state) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);
	  else
							 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
	
}

void Switch_tps61088(uint16_t state)
{
	  if (state) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
	  else
							 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);
	
}

void Switch_ip5328_key(uint16_t state)
{
	  if (state) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
	  else
							 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
	
}

void Switch_halt_signal(uint16_t state)
{
	  if (state) HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	  else
							 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	
}


void SystemHalt(void)
{
	 HAL_IWDG_Refresh(&hiwdg);
	 HAL_SuspendTick();
   HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) // 10Hz Timer
{
   	pa0.in_value = v_rpi;
	  AnalogPinTrip(&pa0);
	
		pa1.in_value = v_bat;
	  AnalogPinTrip(&pa1);
	
		pa2.in_value = v_in;
	  AnalogPinTrip(&pa2);
	
	  _switch_filter(&key_k1); 
	
	  //PA2 V_IN voltage supplied
	
	  if (pa2.trip) {
			
			
			Switch_tps61088(1);
			Switch_halt_signal(1);
			
			if (timer_v_in.timer_v_in_on <= START_TIME_RPI*10) timer_v_in.timer_v_in_on++;
			
			if (timer_v_in.timer_v_in_trigger && (timer_v_in.timer_v_off_pause >= PAUSE_TIME)){
				 timer_v_in.timer_v_in_on = 0;
				 timer_v_in.timer_v_in_off = 0;
			}
			
			
			timer_v_in.timer_v_off_pause = 0;
			timer_v_in.timer_v_in_trigger = false;
    } 
		else // V_IN voltage insuffisient
		{ 
			
			
			if (timer_v_in.timer_v_off_pause >= PAUSE_TIME)
			{
			    Switch_halt_signal(0);
      
					if (timer_v_in.timer_v_in_off <= HALT_TIME_RPI*10+(START_TIME_RPI*10-timer_v_in.timer_v_in_on)) 
							timer_v_in.timer_v_in_off++;
			
					else {
							Switch_tps61088(0); // Switch off 5V step-up converter
							//SystemHalt();
					}
			 } else
		   	timer_v_in.timer_v_off_pause++;
				  
			
			timer_v_in.timer_v_in_trigger = true;
		}
}

	
int main(void)
{
  HAL_Init();
  SystemClock_Config();
	
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_IWDG_Init();
  MX_TIM3_Init();
	InitAnalogPins();
	InitSwitches();
	InitTimer_v_in();
	
	HAL_TIM_Base_Start_IT(&htim3);		
	
	
	HAL_Delay(10);
	
	Switch_out_rpi(1);	
	
  while (1)
  {
      HAL_IWDG_Refresh(&hiwdg);
  	  v_rpi = GetADC_Value(ADC_CHANNEL_0);
	 	  v_bat = GetADC_Value(ADC_CHANNEL_1);
	  	v_in  = GetADC_Value(ADC_CHANNEL_2);

   	  Switch_ip5328_key(!key_k1.outstate);
			HAL_Delay(10);	 
	}

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  
	if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
	
}

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */
static void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_128;
  hiwdg.Init.Window = 325;
  hiwdg.Init.Reload = 325;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 1000;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 800;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
