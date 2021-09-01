//*******************************************************************
/*!
\file   lib.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.03.2016

This file is released under the MIT License.

\brief  Library main include file
*/

//*******************************************************************
#ifndef _LIB_H
#define _LIB_H

//*******************************************************************
//
//*******************************************************************

#include "MCU.h"
#include "MCU/System.h"

//*******************************************************************
// Hardware
//*******************************************************************


//*******************************************************************
// Peripheral
////*******************************************************************
//#include "Peripheral/Peripheral.h"

//*******************************************************************
// Std
//*******************************************************************
#include "Com/Std/Std.h"
#include "Com/Std/StaticArray.h"
#include "Com/Std/CRC.h"
#include "Com/Std/List.h"
#include "Com/Std/Fifo.h"
#include "Com/Std/SharedMem.h"
#include "Com/Std/Whiteboard.h"
#include "Com/Std/DataPointer.h"
#include "Com/Std/Timer.h"

//*******************************************************************
// Device
//*******************************************************************
//*******************************************************************
// Device/Analog
//*******************************************************************
#include "Com/Device/Analog/devAnalogInADC.h"
#include "Com/Device/Analog/devAnalogOutDAC.h"
#include "Com/Device/Analog/devAnalogOutPWM.h"

//*******************************************************************
// Device/Digital
//*******************************************************************
#include "Com/Device/Digital/devDigital.h"
#include "Com/Device/Digital/devDigitalIndicator.h"

//*******************************************************************
// DEVICE/MEMORY
//*******************************************************************
#include "Com/Device/Memory/devMemory.h"
#include "Com/Device/Memory/devMemoryFlash.h"

//*******************************************************************
// DEVICE/MOTOR
//*******************************************************************
#include "Com/Device/Motor/devMotor.h"
#include "Com/Device/Motor/devMotorDirection.h"
#include "Com/Device/Motor/devMotorBipolar.h"

//*******************************************************************
// Device/TextIO
//*******************************************************************
#include "Com/Device/TextIO/devTextIO_UART.h"

//*******************************************************************
// Task
//*******************************************************************
#include "Com/Task/TaskHandler.h"

#endif
