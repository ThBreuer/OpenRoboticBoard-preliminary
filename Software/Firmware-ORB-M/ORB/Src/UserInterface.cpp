//*******************************************************************
/*!
\file   UserInterface.cpp
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

//*******************************************************************
#include "lib.h"
#include "UserInterface.h"

//*******************************************************************
extern cDevDigital      ledUsr1;
extern cDevDigital      ledUsr2;
extern cDevDigital      btnUsr1;
extern cDevDigital      btnUsr2;

extern cDevDigitalIndicator pwrIndicator;

//*******************************************************************
//
// UserInterface
//
//*******************************************************************
//-------------------------------------------------------------------
UserInterface::UserInterface( cTaskHandler &taskHandler,
                              AppTask      &app,
                              Settings     &settings )

: btnTimer( taskHandler, 20/*ms*/)
 ,settings(settings)
 ,app     ( app )

{
}

//-------------------------------------------------------------------
void UserInterface::update()
{
  if( btnTimer.timeout() )
  {
    if( btnUsr1.getEvent() == cDevDigital::ACTIVATED )
    {
      if( app.isActive() )  stopApp();
      else                  startApp(0);
    }
    else if( btnUsr2.getEvent() == cDevDigital::ACTIVATED )
    {
      if( app.isActive() )  stopApp();
      else                  startApp(1);
    }
  }

  if( !app.isActive() )
  {
     ledUsr1.clr();
     ledUsr2.clr();
  }
}

//-------------------------------------------------------------------
void UserInterface::startApp( BYTE param )
{
  if( !app.isActive())
  {
    if( param )
      ledUsr2.set();
    else
      ledUsr1.set();
    app.Start(param);
  }
}

//-------------------------------------------------------------------
void UserInterface::stopApp()
{
  if( app.isActive())
    app.Stop();
}

//-------------------------------------------------------------------
bool UserInterface::isAppActive()
{
  return( app.isActive() );
}

//-------------------------------------------------------------------
void UserInterface::setMonitorEvent( BYTE event )
{
  app.MonitorEvent = event;
}

//-------------------------------------------------------------------
void UserInterface::setVcc( BYTE Vcc )
{
  if     ( Vcc > settings.getVccLevelOK()  )  pwrIndicator.blink(1000,100, 30);
  else if( Vcc > settings.getVccLevelLow() )  pwrIndicator.blink(1000, 80, 50);
  else                                        pwrIndicator.blink( 250, 50,100);
}
//EOF
