//*******************************************************************
/*!
\file   Sensor.h
\author Thomas Breuer
\date
\brief  Zusätzliche Messwerte zu einem Sensor-Port erfasssen
*/

//*******************************************************************
#ifndef _SENSOR_EXTRA_H
#define _SENSOR_EXTRA_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Erfassen zusätzlicher Messwerte (analog/digital) zu einem Sensor-Port

    Unabhängig von der Konfiguration eines Sensor-Ports (siehe Sensor)
    können die Zustände der Port-Pins digital (Pin 2, 5 und 6) bzw.
    der Analogeingang erfasst werden.

    Für jeden dieser Kanäle kann ein Objekt dieser Klasse erstellt werden.
*/
class SensorExtra : public Value<int>
{
  public:
    //---------------------------------------------------------------
    /*! Sensor-Typ: Beschreibt hier, welcher Kanal (digitaler Pin/Analogeingang)
        erfasst werden soll.
    */
    typedef enum
    {
      ANALOG  = 0, //!< Analogkanal
      ANALOG_B  = 1, //!< Analogkanal
      DIGITAL_A,   //!< Digitaler Pin 6
      DIGITAL_B,   //!< Digitaler Pin 5
    } SensorType_type;

    //---------------------------------------------------------------
    /*! Sensor-Port
    */
    typedef enum
    {
      S1 = 0, //!< Sensorport 1
      S2,     //!< Sensorport 2
      S3,     //!< Sensorport 3
      S4      //!< Sensorport 4
    } SensorPort_type;

  private:
    //---------------------------------------------------------------
    BYTE port;
    BYTE mode;

    ORB  &orb;

	 float gain;
    float offset;
	
	Memory::Item kalib0;
    Memory::Item kalib1;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein SonsorExtra-Objekt

        \param port Sensor-Port S1 bis S4
        \param mode Sensortyp (ANALOG, DIGITAL_A,...,_C)
    */
    SensorExtra( SensorPort_type port, BYTE mode )
    : orb( *orbPtr ),
      kalib0(0x1000 + port*0x10+(mode+1)*0x100               ),
      kalib1(0x1000 + port*0x10+(mode+1)*0x100 + sizeof(int) )
    {
      this->port = port;
      this->mode = mode;
			
			init(mode);
    }

		private:
    //---------------------------------------------------------------
    void init(unsigned char modeIn)
    {
      mode = modeIn;

      gain   = (kalib0!=kalib1)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
    }

		  public:
    //---------------------------------------------------------------
    /*! Kalibration des Sensors (nur ANALOG), s.d. aktueller Sensorwert
        als "100" ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void kalibHundert()
    {
      kalib1 = orbPtr->getSensorValueExt(port,mode)&0xFFF;
      gain   = (kalib1!=kalib0)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
    }

    //---------------------------------------------------------------
    /*! Kalibration des Sensors (nur ANALOG), s.d. aktueller Sensorwert
        als "0" ausgegeben wird.

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void kalibNull()
    {
      kalib0 = orbPtr->getSensorValueExt(port,mode)&0xFFF;
      gain   = (kalib1!=kalib0)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
    }


  public:
    //---------------------------------------------------------------
    /*! Liefert Sensorwert für den konfigurierten Mode
        \return Sensorwert
    */
    virtual int get( void )
    {
      switch( mode )
      {
        case ANALOG:    return( gain*((float)(orbPtr->getSensorValueExt(port,0)&0xFFF)-offset)  );
        case ANALOG_B:  return( gain*((float)(orbPtr->getSensorValueExt(port,1)&0xFFF)-offset)  );
        case DIGITAL_A: return( (orbPtr->getSensorValueExt(port,2)&(1<<14)) != 0 );
        case DIGITAL_B: return( (orbPtr->getSensorValueExt(port,3)&(1<<13)) != 0 );
        default:        return( 0 );
      }
    }

};
#endif
