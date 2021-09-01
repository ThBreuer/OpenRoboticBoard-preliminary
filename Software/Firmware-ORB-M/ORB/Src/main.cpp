//*******************************************************************
/*!
\file   main.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/RTOS.h"
#include "Module/ISC.h"
#include "Module/USB/USBinterfClassVSC.h"
#include "Module/Download.h"
#include "config.h"

#include "Properties.h"
#include "MotorTask.h"
#include "ServoTask.h"
#include "SensorTask.h"
#include "Settings.h"
#include "Monitor.h"
#include "UserInterface.h"
#include "Remote.h"

//*******************************************************************
cRTOS_RR< NUM_OF_SENSOR_PORTS+1 > rtos( 200/*us*/ );

Sensor::Context sContext[ NUM_OF_SENSOR_PORTS ]
  = { Sensor::Context( adc1, adc21, digitalA_1, digitalB_1, digitalC_1, digitalD_1, digitalH_1 ),
      Sensor::Context( adc2, adc22, digitalA_2, digitalB_2, digitalC_2, digitalD_2, digitalH_2 ),
      Sensor::Context( adc3, adc23, digitalA_3, digitalB_3, digitalC_3, digitalD_3, digitalH_3 ),
      Sensor::Context( adc4, adc24, digitalA_4, digitalB_4, digitalC_4, digitalD_4, digitalH_4 ) };

SensorTask sTask[ NUM_OF_SENSOR_PORTS ]
  = { SensorTask( rtos, sContext[0], uart1, tim10, extInt1 ),
      SensorTask( rtos, sContext[1], uart2, tim10, extInt2 ),
      SensorTask( rtos, sContext[2], uart3, tim10, extInt3 ),
      SensorTask( rtos, sContext[3], uart4, tim10, extInt4 ) };

MotorTask mTask[ NUM_OF_MOTOR_PORTS ]
  = { MotorTask( taskHandler, mot1, enc_A ),
      MotorTask( taskHandler, mot2, enc_B ),
      MotorTask( taskHandler, mot3, enc_C ),
      MotorTask( taskHandler, mot4, enc_D ) };

ServoTask servoTask[ NUM_OF_SERVO_PORTS ]
  = { ServoTask( taskHandler, pwm_ModellServo1 ),
      ServoTask( taskHandler, pwm_ModellServo2 ) };

Monitor   monitor;

Settings  settings( mem2 );

//*******************************************************************
cISC_UART        ipcBT ( bt );
cISC_USBdevice   ipcUSB( usb, 0/*interfId*/);

//*******************************************************************
AppTask        app      ( rtos                                     );
UserInterface  ui       ( taskHandler, app,      settings          );
Control        ctrl     ( taskHandler, ui                          );
Remote         remoteBT ( ipcBT,       ui, ctrl, settings, monitor );
Remote         remoteUSB( ipcUSB,      ui, ctrl, settings, monitor );

//*******************************************************************
int main( void )
{
  usb.start();

  while(1)
  {
    ui.       update();
    ctrl.     update();
    remoteBT. update();
    remoteUSB.update();
  }
}
