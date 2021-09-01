//*******************************************************************
/*!
\file   SensorAnalog.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"

//*******************************************************************
#include "SensorAnalog.h"

//*******************************************************************
//
// SensorAnalog
//
//*******************************************************************
//-------------------------------------------------------------------
SensorAnalog::SensorAnalog( Sensor::Context &context )

  : Sensor( context )
{
}

//-------------------------------------------------------------------
void SensorAnalog::start( void )
{

  report.reset( cConfigToORB::Data::SensorConfig::ANALOG );


  context.digitalA.set();
  context.digitalB.set();

/// TODO: Pin-Config aus option uebernehmen
  context.digitalA.setMode( cHwPort::InPU  );

  // vorläufig:
  context.digitalA.setMode( cHwPort::OutPP );

  context.digitalB.setMode( cHwPort::InPU  );

  context.adc1.enable();
  context.adc2.enable();

}

//-------------------------------------------------------------------
void SensorAnalog::stop( void )
{
  context.digitalA.setMode( cHwPort::InPU );
  context.digitalA.set();
}

//-------------------------------------------------------------------
void SensorAnalog::update( void )
{
  WORD analog1 = context.adc1.getRaw()>>4;
  WORD analog2 = context.adc2.getRaw()>>4;
  WORD pin5    = context.digitalA.get();
  WORD pin6    = context.digitalB.get();

  report.rep.value[0] =   ((DWORD)(analog1 & 0x0FFF)     )
                        | ((DWORD)(analog2 & 0x0FFF) <<12)
                        | ((DWORD)(pin6    & 0x0001) <<24)
                        | ((DWORD)(pin5    & 0x0001) <<25);
  report.setValid();

}

//-------------------------------------------------------------------
bool SensorAnalog::configMode( BYTE mode, WORD option )
{

  setPinMode( context.digitalC, option>> 0 );  //pin 1
  setPinMode( context.digitalD, option>> 4 );  //pin 2
  setPinMode( context.digitalA, option>> 8 );  //pin 5
  setPinMode( context.digitalB, option>>12 );  //pin 6

  return true;
}

//-------------------------------------------------------------------
 void SensorAnalog::setPinMode( cHwPort::Pin &pin, BYTE mode )
{
  switch( mode & 0x07 )
  {
    case 0:  pin.setMode( cHwPort::In   ); break;
    case 1:  pin.setMode( cHwPort::InPU ); break;
    case 2:  pin.setMode( cHwPort::InPD ); break;
    case 3:  /*analog ? */                 break;
    case 4:  pin.setMode( cHwPort::OutOD); break;
    case 5:  pin.setMode( cHwPort::OutPU); break;
    case 6:  pin.setMode( cHwPort::OutPP); break;
    case 7:  /* ? */                       break;
    default:                               break;
  }

  pin.set( mode&0x08 );
}


//EOF
