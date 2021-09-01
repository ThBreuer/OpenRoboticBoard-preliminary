//*******************************************************************
/*!
\file   ...
\author Thomas Breuer
\date   ...
\brief  Configuration file
*/

//*******************************************************************
#include "BT_RN4678.h"

//*******************************************************************
cSystem sys;

cHwPinConfig::MAP cHwPinConfig::table[] =
{
  // UART 3 (Bluetooth)
  USART3_TX_PD_8,
  USART3_RX_PD_9,
  USART3_CTS_PD_11,
  USART3_RTS_PD_12,

  //UART 2 SensorPort 1
  USART2_TX_PD_5,
  USART2_RX_PD_6,

  //UART 5 SensorPort 2
  UART5_TX_PC_12,
  UART5_RX_PD_2,

  //UART 4 SensorPort 3
  UART4_TX_PC_10,
  UART4_RX_PC_11,

  //UART 1 SensorPort 4
  USART1_TX_PA_9,
  USART1_RX_PA_10,

  // Timer (Encoder-1)
  TIM5_CH1_PA_0,
  TIM5_CH2_PA_1,

  // Timer (Encoder-2)
  TIM4_CH1_PB_6,
  TIM4_CH2_PB_7,

  // Timer (Encoder-3)
  TIM3_CH1_PA_6,
  TIM3_CH2_PA_7,

  // Timer (Encoder-4)
  TIM1_CH1_PE_9,
  TIM1_CH2_PE_11,

  // Timer (PWM)
  TIM8_CH1_PC_6,
  TIM8_CH2_PC_7,
  TIM8_CH3_PC_8,
  TIM8_CH4_PC_9,

  TIM9_CH1_PE_5,
  TIM9_CH2_PE_6,
  //TIM12_CH1_PB_14,
  //TIM12_CH2_PB_15,

  // ADC
  ADC12_IN14_PC_4,   // Vcc-Messung

  ADC123_IN10_PC_0,    // Analog-1
  ADC123_IN11_PC_1,    // Analog-2
  ADC123_IN12_PC_2,    // Analog-3
  ADC123_IN13_PC_3,  // Analog-4

  ADC12_IN4_PA_4,    // Analog-2-1
  ADC12_IN5_PA_5,    // Analog-2-2
  ADC12_IN8_PB_0,    // Analog-2-3
  ADC12_IN9_PB_1,  // Analog-2-4

  // USB
  //  OTG_FS_ID_PA_10,
  OTG_FS_DM_PA_11,
  OTG_FS_DP_PA_12,

  END_OF_TABLE
};

// UART
//-----
cHwUART_Ext      btx  ( cHwUART_N::USART_3, cHwUART_N::BR_115200
                                         |cHwUART_N::CTS
                                         |cHwUART_N::RTS, 255, 255 );  // Bluetooth module on board

cHwUART_Ext      uart1 ( cHwUART_N::USART_2, cHwUART::BR_2400, 100, 100 );
cHwUART_Ext      uart2 ( cHwUART_N::UART_5, cHwUART::BR_2400, 100, 100 );
cHwUART_Ext      uart3 ( cHwUART_N::UART_4,  cHwUART::BR_2400, 100, 100 );
cHwUART_Ext      uart4 ( cHwUART_N::USART_1, cHwUART::BR_2400, 100, 100 );

// Ports
//------
cHwPort_N        portA ( cHwPort_N::PA );
cHwPort_N        portB ( cHwPort_N::PB );
cHwPort_N        portC ( cHwPort_N::PC );
cHwPort_N        portD ( cHwPort_N::PD );
cHwPort_N        portE ( cHwPort_N::PE );

// UART Bluetooth
cHwPort::Pin     BT_Wakeup( portD, 3 );
cHwPort::Pin     BT_RST_N ( portD, 4 );
cHwPort::Pin     BT_Status( portC, 5 );

// Timer
//------
cHwTimer_N       tim1  ( cHwTimer_N::TIM_1,   100 );
cHwTimer_N       tim8  ( cHwTimer_N::TIM_8,    50 );
cHwTimer_N       tim10 ( cHwTimer_N::TIM_10,   30000 );
//cHwTimer_N       tim11 ( cHwTimer_N::TIM_11,   50 );
cHwTimer_N       tim9  ( cHwTimer_N::TIM_9,   16000 );
cHwTimer_N       timer ( cHwTimer_N::TIM_2,  1000 );

// ADC
//----
cHwADC_0         adc   ( &timer );

// Motor-Enable
//-------------
cDevDigital         enable( portA, 3, cDevDigital::Out, 1 );

// Motor-PWM
//----------
cDevAnalogOutPWM    pwm_A( tim8, cHwTimer::NORMAL, 1, 1000.0, 0.0 );
cDevAnalogOutPWM    pwm_B( tim8, cHwTimer::NORMAL, 0, 1000.0, 0.0 );
cDevAnalogOutPWM    pwm_C( tim8, cHwTimer::NORMAL, 2, 1000.0, 0.0 );
cDevAnalogOutPWM    pwm_D( tim8, cHwTimer::NORMAL, 3, 1000.0, 0.0 );

// Modellbau-Servo-PWM
//--------------------
cDevAnalogOutPWM    pwm_ModellServo1( tim9, cHwTimer::NORMAL, 1, 16.0, 0.0 );
cDevAnalogOutPWM    pwm_ModellServo2( tim9, cHwTimer::NORMAL, 0, 16.0, 0.0 );


// Motor-CW/CCW
//-------------
cDevDigital         cw_A ( portE, 15, cDevDigital::Out, 0 );
cDevDigital         ccw_A( portE, 14, cDevDigital::Out, 0 );
cDevDigital         cw_B ( portB, 10, cDevDigital::Out, 0 );
cDevDigital         ccw_B( portB, 11, cDevDigital::Out, 0 );
cDevDigital         cw_C ( portE,  7, cDevDigital::Out, 0 );
cDevDigital         ccw_C( portE,  8, cDevDigital::Out, 0 );
cDevDigital         cw_D ( portD, 13, cDevDigital::Out, 0 );
cDevDigital         ccw_D( portD, 14, cDevDigital::Out, 0 );

// Motor-Encoder
//--------------
cHwEncoder_N     enc_A ( cHwEncoder_N::TIM_5, cHwEncoder_N::NORMAL );
cHwEncoder_N     enc_B ( cHwEncoder_N::TIM_4, cHwEncoder_N::NORMAL );
cHwEncoder_N     enc_C ( cHwEncoder_N::TIM_3, cHwEncoder_N::NORMAL );
cHwEncoder_N     enc_D ( cHwEncoder_N::TIM_1, cHwEncoder_N::NORMAL );

// Motor
//------
cDevMotorDirection mot1( cw_A, ccw_A, pwm_A );
cDevMotorDirection mot2( cw_B, ccw_B, pwm_B );
cDevMotorDirection mot3( cw_C, ccw_C, pwm_C );
cDevMotorDirection mot4( cw_D, ccw_D, pwm_D );


// Digital-Eingang
cHwPort::Pin     digitalA_1   ( portD,  5 );   // S1.5, SCL
cHwPort::Pin     digitalB_1   ( portD,  6 );   // S1.6, SDA, ExtInt
cHwPort::Pin     digitalC_1   ( portA,  4 );   // S1.2
cHwPort::Pin     digitalD_1   ( portC,  0 );   // S1.1
cHwPort::Pin     digitalH_1   ( portD, 15 );   // S1.1-HS

cHwPort::Pin     digitalA_2   ( portC, 12 );   // S2.5, SCL
cHwPort::Pin     digitalB_2   ( portD,  2 );   // S2.6, SDA, ExtInt
cHwPort::Pin     digitalC_2   ( portA,  5 );   // S2.2
cHwPort::Pin     digitalD_2   ( portC,  1 );   // S1.1
cHwPort::Pin     digitalH_2   ( portD,  1 );   // S2.1-HS

cHwPort::Pin     digitalA_3   ( portC, 10 );   // S3.5, SCL
cHwPort::Pin     digitalB_3   ( portC, 11 );   // S3.6, SDA, ExtInt
cHwPort::Pin     digitalC_3   ( portB,  0 );   // S3.2
cHwPort::Pin     digitalD_3   ( portC,  2 );   // S1.1
cHwPort::Pin     digitalH_3   ( portA,  8 );   // S3.1-HS

cHwPort::Pin     digitalA_4   ( portA,  9 );   // S4.5, SCL
cHwPort::Pin     digitalB_4   ( portA, 10 );   // S4.6, SDA, ExtInt
cHwPort::Pin     digitalC_4   ( portB,  1 );   // S4.2
cHwPort::Pin     digitalD_4   ( portC,  3 );   // S1.1
cHwPort::Pin     digitalH_4   ( portD,  0 );   // S4.1-HS

cHwExtInt_N      extInt1( cHwExtInt_N::PD, 6);
cHwExtInt_N      extInt2( cHwExtInt_N::PD, 2);
cHwExtInt_N      extInt3( cHwExtInt_N::PC,11);
cHwExtInt_N      extInt4( cHwExtInt_N::PA,10);

// Digital-Eingang Extra
cDevDigital         taster2(portE,0, cDevDigital::InPU,  1);
cDevDigital         taster1(portE,1, cDevDigital::InPU,  1);

// Versorgungsspannung
cDevAnalogInADC     Vcc ( adc, 14, (133.0f/33*33), 0.0f );   // Uref = 33/10 V; R1=100k, R2=33k

// Analog-Eingang
cDevAnalogInADC     adc1( adc, 10, 3.3f, 0.0f );   // S1.1
cDevAnalogInADC     adc2( adc, 11, 3.3f, 0.0f );   // S2.1
cDevAnalogInADC     adc3( adc, 12, 3.3f, 0.0f );   // S3.1
cDevAnalogInADC     adc4( adc, 13, 3.3f, 0.0f );   // S4.1

// Analog-Eingang
cDevAnalogInADC     adc21( adc, 4, 3.3f, 0.0f );   // S1.2
cDevAnalogInADC     adc22( adc, 5, 3.3f, 0.0f );   // S2.2
cDevAnalogInADC     adc24( adc, 8, 3.3f, 0.0f );   // S3.2
cDevAnalogInADC     adc23( adc, 9, 3.3f, 0.0f );   // S4.2


// User
//-----
cDevDigital      btnUsr1(portE, 12, cDevDigital::InPU,  1 );
cDevDigital      btnUsr2(portE, 13, cDevDigital::InPU,  1 );
cDevDigital      ledUsr1(portE,  2, cDevDigital::OutOD, 1 );
cDevDigital      ledUsr2(portE,  3, cDevDigital::OutOD, 1 );

// Power-LED
cDevDigital          ledPwr (portE,  4, cDevDigital::OutOD, 1 );
cDevDigitalIndicator pwrIndicator(ledPwr, timer );


// Task-Timer
//-----------
cTaskHandler     taskHandler( &timer );

//
//-----------
cHwMemory_Flash  mem0( cHwMemory_Flash::SECTOR_8 );
cHwMemory_Flash  mem1( cHwMemory_Flash::SECTOR_9 );

cHwMemory_Flash  mem2( cHwMemory_Flash::SECTOR_10 );
cHwMemory_Flash  mem3_1( cHwMemory_Flash::SECTOR_11 );
cHwMemory_RAM    mem3_2;

cHwUSBdesc_0     desc;
cHwUSB_0         usb( desc );

BT_RN4678 btmodul(btx,BT_RST_N,BT_Wakeup,BT_Status);
Bluetooth &btm = btmodul;
cHwUART &bt = btmodul.uart;

//EOF
