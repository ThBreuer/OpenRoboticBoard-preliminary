//*******************************************************************
/*!
\file   Timer.h
\author Thomas Breuer
\date
\brief  Zeitmessung und Timeout
*/

//*******************************************************************
#ifndef _TIMER_H
#define _TIMER_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Zeitmessung und Timeout

    Mit Objekte dieser Klasse können Zeitmessungen, Timeouts ud
    Wartezeiten realisiert werden.
    <UL>
    <LI><b>Zeitmessung</b>

    Die Zeitmessung liefert die Zeit, die seit dem Erzeugen des
    Objektes bzw. nach einem Reset des Objektes vergangen ist.

    \see get() und reset()

    <LI><b>Timeout</b>

    Nach dem Starten der Timeout-Funktion liefert Timer::timeout() einmalig <code>true</code> zurück, wenn die Laufzeit überschritten wurde.
    In diesem Falle wird der Timer zurückgesetzt und neu gestartet.

    \see start(), stop() und timeout()

    <LI><b>Wartezeit</b>
    </UL>
    Alle Zeiten werden in ms (Millisekunden) angegeben
*/
class Timer : public Value<DWORD>
{
  private:
    //---------------------------------------------------------------
    DWORD  timeoutTime;
    bool   isRunning;
    DWORD  startTime;
    ORB   &orb;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Timer-Objekt
        \param time Laufzeit für Timeout (optional).
        Wenn time > 0 übergeben wird, wird der Timer automatisch getartet.
    */
    Timer( DWORD time = 0 )
    : orb( *orbPtr )
    {
      timeoutTime = 0;
      reset();
      start( time );
    }

    //---------------------------------------------------------------
    /*! Liefert Laufzeit seit dem Erzeugen des Objektes bzw. seit dem
        letztem Reset
        \return Laufzeit (ms)
    */
    virtual DWORD get( void )
    {
      return( orb.getTime() - startTime );
    }

    //---------------------------------------------------------------
    /*! Setzt Zeitmessung zurück.

        Das Zurücksetzen betrifft auch die Timeout-Funktion
    */
    virtual void reset( void )
    {
      startTime = orb.getTime();
    }

    //---------------------------------------------------------------
    /*! Startet die Timeout-Funktion
        \param time Laufzeit der Timeout-Funktion (Einheit:ms, optional).
        Die Laufzeit <code>time</code> gibt an, nach welcher Zeit die
        Methode <code>timeout()</code> einmalig <code>true</code>
        zurückliefert.
        Fall <code>time</code> nicht angegeben wird, wird die vorherige
        Laufzeit übernommen
    */
    virtual void start( DWORD time = 0 )
    {
      reset();
      if( time > 0 )
      {
        timeoutTime = time;
      }
      isRunning = (timeoutTime > 0);
    }

    //---------------------------------------------------------------
    /*! Stoppt die Timeout-Funktion.
        Nachdem die Timeout-Funktion gestoppt wurde, liefert
        <code>timeout()</code> auch nach Ablauf der Timeoutzeit
        <code>false</code> zurück.
    */
    virtual void stop( void )
    {
      isRunning = false;
    }

    //---------------------------------------------------------------
    /*! Liefert bei laufender Timeout-Funktion genau dann <code>true</code>
        zurück, wenn die Laufzeit überschritten wurde. Die Timeout-Funktion
        wird neu gestartet.
        \return Timeout aufgetreten
    */
    virtual bool timeout( void )
    {
      if( isRunning )
      {
        if( get() >= timeoutTime )
        {
          start();
          return( true );
        }
      }
      return( false );
    }

    //---------------------------------------------------------------
    /*! Das aktuelle Programm wird für die angegebene Zeit
        vollständig unterbrochen.
        \param time Unterbrechungsdauer (ms)
    */
    virtual void wait( DWORD time )
    {
      orb.wait( time );
    }
};
#endif
