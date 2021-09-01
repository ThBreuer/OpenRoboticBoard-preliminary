//*******************************************************************
/*!
\file   lib.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   23.03.2016

This file is released under the MIT License.

\brief Summary of complete library code
*/

//*******************************************************************
#include "lib.h"

//*******************************************************************
// Hardware/MCU
//*******************************************************************
#include "MCU.cpp"

//*******************************************************************
// Hardware
//*******************************************************************
//*******************************************************************
// Com/Hardware
//*******************************************************************
#include "Com/Hardware/Analog/ADC.cpp"
#include "Com/Hardware/Analog/DAC.cpp"
#include "Com/Hardware/Timer/Encoder.cpp"
#include "Com/Hardware/I2C/I2Cmaster.cpp"
#include "Com/Hardware/I2C/I2Cslave.cpp"
#include "Com/Hardware/Memory/Memory.cpp"
#include "Com/Hardware/Port/ExtInt.cpp"
#include "Com/Hardware/Port/Port.cpp"
#include "Com/Hardware/Timer/Timer.cpp"
#include "Com/Hardware/UART/UART.cpp"

//#include "Com/Hardware/USB.cpp"
//-------------------------------------------------------------------
#include "Com/Hardware/USB/USBhardware.cpp"
#include "Com/Hardware/USB/USBctrl.cpp"
#include "Com/Hardware/USB/USBdesc.cpp"
#include "Com/Hardware/USB/USBendpoint.cpp"
#include "Com/Hardware/USB/USBinterf.cpp"

//*******************************************************************
//
//*******************************************************************
//#include "Peripheral/Peripheral.cpp"

//*******************************************************************
// Device
//*******************************************************************
//*******************************************************************
// Device/Analog
//*******************************************************************
#include "Com/Device/Analog/devAnalog.cpp"
#include "Com/Device/Analog/devAnalogIn.cpp"
#include "Com/Device/Analog/devAnalogInADC.cpp"
#include "Com/Device/Analog/devAnalogOut.cpp"
#include "Com/Device/Analog/devAnalogOutDAC.cpp"
#include "Com/Device/Analog/devAnalogOutPWM.cpp"

//*******************************************************************
// Device/Digital
//*******************************************************************
#include "Com/Device/Digital/devDigital.cpp"
#include "Com/Device/Digital/devDigitalIndicator.cpp"

//*******************************************************************
// DEVICE/MEMORY
//*******************************************************************
#include "Com/Device/Memory/devMemory.cpp"

//*******************************************************************
// DEVICE/MOTOR
//*******************************************************************
#include "Com/Device/Motor/devMotor.cpp"
#include "Com/Device/Motor/devMotorDirection.cpp"
#include "Com/Device/Motor/devMotorBipolar.cpp"

//*******************************************************************
// Device/TextIO
//*******************************************************************
#include "Com/Device/TextIO/devTextIO.cpp"
#include "Com/Device/TextIO/devTextIO_UART.cpp"

//*******************************************************************
// STD
//*******************************************************************
#include "Com/Std/Std.cpp"
#include "Com/Std/StaticArray.cpp"
#include "Com/Std/CRC.cpp"
#include "Com/Std/List.cpp"
#include "Com/Std/Fifo.cpp"
#include "Com/Std/DataPointer.cpp"
#include "Com/Std/SharedMem.cpp"
#include "Com/Std/Timer.cpp"

//*******************************************************************
// Task
//*******************************************************************
#include "Com/Task/TaskHandler.cpp"

// EOF
