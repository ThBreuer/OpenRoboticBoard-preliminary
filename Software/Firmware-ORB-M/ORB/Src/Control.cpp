//*******************************************************************
/*!
\file   Control.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Control.h"

//*******************************************************************
extern MotorTask        mTask    [ NUM_OF_MOTOR_PORTS ];
extern ServoTask        servoTask[ NUM_OF_SERVO_PORTS ];
extern cDevAnalogInADC  Vcc;

//*******************************************************************
//
// Control
//
//*******************************************************************
//-------------------------------------------------------------------
Control::Control( cTaskHandler  &taskHandler,
                  UserInterface &ui )

: ui( ui )
 ,outputTimer( taskHandler, 1000 /*ms*/)
 ,VccTimer   ( taskHandler,   10 /*ms*/)

{
  VccFilter = 100;
}

//---------------------------------------------------------------
void Control::update()
{
  //---------------------------------------------------------------
  if( VccTimer.timeout() )
  {
    VccFilter = 0.05f*(float)Vcc + 0.95f*VccFilter;
    ui.setVcc( VccFilter );
  }

  //-------------------------------------------------------------
  if( outputTimer.timeout() )
  {
      //-------------------------------------------------------------
      if( !ui.isAppActive() )
      {
        // stop all motors
        for( int i=0; i<NUM_OF_MOTOR_PORTS; i++ )
        {
          mTask[i].set( 0, 0, 0 );
        }

        // stop all servos
        for( int i=0; i<NUM_OF_SERVO_PORTS; i++ )
        {
          servoTask[i].set( 0, 0 );
        }
      }
  }
}

//---------------------------------------------------------------
void Control::trigger()
{
  outputTimer.start();
}

//---------------------------------------------------------------
BYTE Control::getVcc()
{
  return( VccFilter );
}

//EOF
