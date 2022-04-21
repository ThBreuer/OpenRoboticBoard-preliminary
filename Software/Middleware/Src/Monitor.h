//*******************************************************************
/*!
\file   Monitor.h
\author Thomas Breuer
\date
\brief  Ermöglicht Textausgabe und Tasteneingabe über ORB-Monitor
*/

//*******************************************************************
#ifndef _MONITOR_H
#define _MONITOR_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Text-Ausgabe und Tasten-Eingabe

*/
class Monitor
{
  public:
    //---------------------------------------------------------------
    /*! Tasten-Code des ORB-Monitors
    */
    typedef enum
    {
      Keine_Taste = 0, //!< Es ist keine Taste gedrückt

      Taste_A1  =  1,
      Taste_A2  =  2,
      Taste_A3  =  3,
      Taste_A4  =  4,
      Taste_A5  =  5,
      Taste_A6  =  6,
      Taste_A7  =  7,
      Taste_A8  =  8,

      Taste_B1  =  9,
      Taste_B2  = 10,
      Taste_B3  = 11,

      Taste_B4  = 12,
      Taste_B5  = 13,
      Taste_B6  = 14,

      Taste_B7  = 15,
      Taste_B8  = 16,
      Taste_B9  = 17,

      Taste_B10 = 18,
      Taste_B11 = 19,
      Taste_B12 = 20,

      Taste_C1  = 21,

    } Taste_enum;

  private:
    //---------------------------------------------------------------
    BYTE  lastEvent;
    ORB  &orb;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Monitor-Objekt, dass mit dem ORB-Monitor zur
        Textausgabe und Tasteneingabe kommuniziert
    */
    Monitor( void )
    : orb( *orbPtr )
    {
      clear();
    }

    //---------------------------------------------------------------
    /*! Löscht die Textausgabe auf dem ORB-Monitor
    */
    void clear( void )
    {
      lastEvent = 0;

      print(1,"");
      print(2,"");
      print(3,"");
      print(4,"");
    }

    //---------------------------------------------------------------
    /*! Gibt eine Textzeile auf dem Display (ORB-Monitor) aus

        Diese Methode wird entsprechend der C-Funktion <code>printf</code>
        aufgerufen. Abweichend dazu gibt line die Display-Zeile an
        \param line Display-Zeile der Textausgabe (1,...)
        \param format Format der Textausgabe, entsprechend printf() (Ansi-C)
    */
    void print( BYTE line, const char *format, ...)
    {
      if( 1 <= line && line <= 4 )
      {
        va_list argzeiger;
        va_start ( argzeiger, format );

        orb.setMonitorText( line-1, format, argzeiger );

        va_end(argzeiger);
      }
    }

    //---------------------------------------------------------------
    /*! Liefert den Tastencode der aktuell betätigten Taste
        des ORB-Monitors
        \return Tastencode
    */
    BYTE getKeyState( void )
    {
      return( orb.getMonitorKey() );
    }

    //---------------------------------------------------------------
    /*! Prüft, ob sich ein Tastendruck <b>geändert</b> hat und liefert
        den Tastencode des ORB-Monitors
        \return Tastencode, falls seit dem letztem Aufruf dieser Methode
        eine Taste neu gedrückt wurde.
        0, falls keine Taste gedrückt ist oder keine Änderung vorliegt
    */
    BYTE getKeyEvent( void )
    {
      BYTE event = orb.getMonitorKey() ;
       if( event != lastEvent )
       {
         lastEvent = event;
         return( lastEvent );
       }
       return( 0 );
    }
};
#endif
