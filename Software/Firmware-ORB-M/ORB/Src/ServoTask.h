//*******************************************************************
/*!
\file   ServoTask.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _SERVO_TASK_H
#define _SERVO_TASK_H

//*******************************************************************
#include "lib.h"

//*******************************************************************
/*!
\class ServoTask
\brief
*/
class ServoTask: public cTaskHandler::Task
{
  public:
    //---------------------------------------------------------------
    ServoTask( cTaskHandler       &taskHandler,
               cDevAnalogOutPWM   &pwmIn );

    //---------------------------------------------------------------
    // speedIn: Geschwindigkeit = 0=aus,...,100=max, unit:10steps/s
    // posIn:   Servoposition   = 0,..,100
    //
    virtual void set( BYTE speedIn, BYTE posIn );

  private:
    //---------------------------------------------------------------
    virtual void update( void );

  private:
    //---------------------------------------------------------------
    cDevAnalogOutPWM    &pwm;
    cTaskHandler::Timer  timer;

    float         pos;
    float         posDelta;
    float         posSoll;
    bool          running;
    volatile bool valid;

};
#endif
