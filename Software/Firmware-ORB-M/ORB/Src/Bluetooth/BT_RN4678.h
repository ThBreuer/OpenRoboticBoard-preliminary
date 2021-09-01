//*******************************************************************
/*!
\file   BT_RN4678.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   03.02.2021
*/

#include "Bluetooth/Bluetooth.h"

//*******************************************************************
/*!
\class
\brief
*/
class BT_RN4678 : public Bluetooth
{
  public:
    //---------------------------------------------------------------
    BT_RN4678( cHwUART_Ext  &_uart,
               cHwPort::Pin &_rst,
               cHwPort::Pin &_wakeup,
               cHwPort::Pin &_status )
    : Bluetooth(_uart), rst(_rst), wakeup(_wakeup), status(_status)
    {
      rst.set(0); // Reset
      wakeup.set(1); // no wakeup

      rst.setMode   ( cHwPort::OutOD );
      wakeup.setMode( cHwPort::OD    );
      status.setMode( cHwPort::InFL  );

      cSystem::delayMilliSec(1);
      rst.set(1);
      cSystem::delayMilliSec(100);

      ////uart.setBaudrate(115200);
      //    send("$$$\r");
      //    waitForAckn("CMD>");
      //    send("SU,03\r");
      //    waitForAckn("AOK");
      //    send("GU\r");
      //    waitForAckn("AOK");
      //    send("R,1\r");
      //    //uart.setBaudrate(115200);
    }

    //---------------------------------------------------------------
    bool waitForAckn(const char *str)
    {
      BYTE c;
      char buf[8];
      BYTE pos = 0;
      unsigned timeout = 100000;

      while( pos < 7 && timeout-- )
      {
        cSystem::delayMicroSec(1);
        if( uart.get(&c) )
        {
          if( strcmp(str,buf) == 0 )
          {
            return( true );
          }
          buf[pos++] = c;
          buf[pos  ] = 0;
        }
      }
      return( false );
    }

    //---------------------------------------------------------------
    void config(const char *name)
    {
      char str[32];
      sprintf(str,"SN,%-16.16s\r", name);



      // TODO: capture error event
      send("$$$\r");   // enter command mode
      waitForAckn("CMD>");
      send("SG,2\r");  // set BT classic only
      waitForAckn("AOK");
      send(str);       // set name
      waitForAckn("AOK");
      send("R,1\r");   // reboot
    }

  private:
    //---------------------------------------------------------------
    cHwPort::Pin &rst;    // Pin 21: Module Reset (internal pull-up). Apply a pulse of at least 63 ns.
    cHwPort::Pin &wakeup; // Pin  9: Wake-up from Sleep mode (active-low) (internal pull-up)
    cHwPort::Pin &status; // Pin 12  P1_5, Status Indication pin. Indicates the current connection status.
                          //         High: Powered On and not connected
                          //         Low: Connected to peer device

};
