//*******************************************************************
/*!
\file   SensorI2C.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "Module/RTOS.h"

//*******************************************************************
#include "SensorI2C.h"

//*******************************************************************
//
// SensorI2C
//
//*******************************************************************
//-------------------------------------------------------------------
SensorI2C::SensorI2C( Sensor::Context &context )

: Sensor( context ),
  scl( context.digitalA ),
  sda( context.digitalB ),

  i2c( scl, sda, cHwI2Cmaster::CR_400kHz ),
  //  i2c2(context.digitalD,context.digitalC,cHwI2Cmaster::CR_400kHz),

  NXTultraschall( *this ),
  TCS3472       ( *this ),
  VL53L0X       ( *this )

{
  strategyPtr = NULL;
}

//-------------------------------------------------------------------
void SensorI2C::start( void )
{
  report.reset( cConfigToORB::Data::SensorConfig::I2C );

  scl.setMode( cHwPort::OutOD );
  sda.setMode( cHwPort::OutOD );

  scl.set( );
  sda.set( );
}

//-------------------------------------------------------------------
void SensorI2C::stop( void )
{
  if( strategyPtr )
  {
    strategyPtr->stop();
  }
  scl.set();
  sda.set();

  scl.setMode( cHwPort::InPU );
  sda.setMode( cHwPort::InPU );
}

//-------------------------------------------------------------------
void SensorI2C::update( void )
{
  if( strategyPtr )
  {
    strategyPtr->update();
  }
}

//-------------------------------------------------------------------
bool SensorI2C::configMode( BYTE mode, WORD optionIn )
{
  switch( mode )
  {
    case 0:  strategyPtr = &NXTultraschall;   break;
    case 1:  strategyPtr = &TCS3472;          break;
    case 2:  strategyPtr = &VL53L0X;          break;
    default: strategyPtr = NULL;              break;
  }

  if( strategyPtr )
  {
    strategyPtr->start( optionIn );
  }
  return true;
}

//EOF
