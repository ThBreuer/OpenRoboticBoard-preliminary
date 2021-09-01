//*******************************************************************
/*!
\file   Control.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#ifndef _CONTROL_H
#define _CONTROL_H

//*******************************************************************
#include "lib.h"
#include "UserInterface.h"
#include "ORBlocal.h"
#include "MotorTask.h"
#include "SensorTask.h"

//*******************************************************************
/*!
\class Control
\brief
*/
class Control
{
  public:
    //---------------------------------------------------------------
    Control( cTaskHandler &taskHandler, UserInterface &ui );

    //---------------------------------------------------------------
    void update();

    //---------------------------------------------------------------
    void trigger();

    //---------------------------------------------------------------
    BYTE getVcc();

  private:
    //---------------------------------------------------------------
    UserInterface  &ui;

    cTaskHandler::Timer outputTimer;
    cTaskHandler::Timer VccTimer;

    float VccFilter;
};

#endif
