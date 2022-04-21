//*******************************************************************
/*!
\file   Sensor.h
\author Thomas Breuer
\date
\brief  Sensoren konfigurieren, kalibrieren und auslesen
*/

//*******************************************************************
#ifndef _SENSOR_H
#define _SENSOR_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Sensoren konfigurieren, kalibrieren und auslesen

    Ein Objekt dieser Klasse erlaubt die Verwendung von Sensoren
*/
class Sensor : public Value<int>
{
  public:
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

    //---------------------------------------------------------------
    /*! Sensortyp und Sensormode
    */
    typedef enum
    {
      NONE    = 0,                   //!< kein Sensor angeschlossen
      EV3_FARBSENSOR_HELLIGKEIT = 1, //!< EV3 Farbsensor im Modus "Helligkeit"
      EV3_FARBSENSOR_FARBE = 3,      //!< EV3 Farbsensor im Modus "Farbwert"
      NXT_ULTRASCHALL = 9,           //!< NXT-Ultraschallsensor
      ANALOG_ON  = 10,               //!< Analogsensor, z.B. NXT-Lichtsensor (LED <b>ein</b>geschaltet)
      ANALOG_OFF  = 11,              //!< Analogsensor, z.B. NXT-Lichtsensor (LED <b>aus</b>geschaltet)
	MB_ULTRASCHALL = 12,            //!< Makeblock Ultraschallsensor, SRF05
	TCS3472_COLOR      = 13,
      VL53L0X_DISTANCE = 14,          //!< Laser Abstandssensor
      EV3_GYRO_ANGLE = 15,      //!< EV3
      EV3_GYRO_RATE = 16,      //!< EV3

    } SensorType_type;

  protected:
    //---------------------------------------------------------------
    ORB  &orb;

    BYTE port;
    BYTE mode;

    float gain;
    float offset;

    Memory::Item kalib0;
    Memory::Item kalib1;

    BYTE numOfCh;
    BYTE maxNumOfCh;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Objekt

        Es werden auch die zuletzt gespeicherten Kalibrationsdaten
        abgerufen
        \param port Sensor-Port S1 bis S4
        \param mode Sensortyp und Sensormode (EV3)
    */
    Sensor( SensorPort_type port, BYTE mode )
    : orb( *orbPtr ),
      kalib0(0x1000 + port*0x10               ),
      kalib1(0x1000 + port*0x10 + sizeof(int) )
    {
      this->port = port;
      numOfCh = 0;
      maxNumOfCh = 1;

      init(mode );
    }

    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Objekt

        Es werden auch die zuletzt gespeicherten Kalibrationsdaten
        abgerufen
        \param port Sensor-Port S1 bis S4
        \param mode Sensortyp und Sensormode (EV3)
    */
    Sensor( Sensor &s )
    : orb( *orbPtr ),
      kalib0(0x1000 + port*0x10               ),
      kalib1(0x1000 + port*0x10 + sizeof(int) )
    {
      this->port   = s.port;
      this->gain   = s.gain;
      this->offset = s.offset;
      this->mode    = s.mode;
      this->numOfCh = s.numOfCh;
      this->maxNumOfCh = s.maxNumOfCh;
      if( numOfCh < maxNumOfCh)
      {
          numOfCh++;
      }

      init(mode );
    }

  private:
    //---------------------------------------------------------------
    void init(unsigned char modeIn)
    {
      mode = modeIn;

      gain   = (kalib0!=kalib1)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;

      switch( mode )
      {
        default:
            maxNumOfCh = 1;
          orb.configSensor( port, ORB::ANALOG, 0, 0 );
          break;

        case EV3_FARBSENSOR_HELLIGKEIT:
            maxNumOfCh = 1;
          orb.configSensor( port, ORB::UART, 0, 0 );
          break;

        case EV3_FARBSENSOR_FARBE:
            maxNumOfCh = 1;
          orb.configSensor( port, ORB::UART, 2, 0 );
          break;

        case NXT_ULTRASCHALL:
            maxNumOfCh = 1;
          orb.configSensor( port, ORB::I2C, 0, 0 );
				  gain = 10.0;
				offset = 0.0;
          break;

        case ANALOG_OFF:
            maxNumOfCh = 1;
          orb.configSensor( port, ORB::ANALOG, 0, 0 );
          break;

        case ANALOG_ON:
            maxNumOfCh = 1;
          orb.configSensor( port, ORB::ANALOG, 1, 0 );
          break;

        case MB_ULTRASCHALL:
            maxNumOfCh = 1;
					//  30 : 420
				  // 200 : 830
//          orb.configSensor( port, ORB::TOF, 0, 0 );
//				  gain   = (200.0-30.0)/(830.0-420.0);
//          offset = 420-30/gain;
          orb.configSensor( port, ORB::TOF, 0, 0 );
				  gain   = 0.170;  // v=2x/t => x = (0.5*0.340mm/µs)*t
          offset = 30; // = 5mm/0.17
          break;

        case TCS3472_COLOR:
            maxNumOfCh = 1;
          orb.configSensor( port, ORB::I2C, 1, 0 );
				  gain = 1.0;
				offset = 0.0;

        break;

        case VL53L0X_DISTANCE:
            maxNumOfCh = 2;
          orb.configSensor( port, ORB::I2C, 2, numOfCh );
				  gain = 1.0;
				offset = 0.0;
          break;


      }
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
      kalib1 = orbPtr->getSensor(port).value[0];
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
      kalib0 = orbPtr->getSensor(port).value[0];
      gain   = (kalib1!=kalib0)?100.0f/(float)(kalib1-kalib0):1.0f;
      offset = kalib0;
    }

    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert
        \return Messwert
    */
    virtual int get()
    {
      switch( mode )
      {
        case TCS3472_COLOR:
            return(orbPtr->getSensor(port).value[0]);

        case VL53L0X_DISTANCE:
            if( numOfCh == 0)
                return(orbPtr->getSensor(port).value[0] & 0xFFFF);
            else
                return ((orbPtr->getSensor(port).value[0]>>16) & 0xFFFF);

        case EV3_FARBSENSOR_FARBE:
          return(orbPtr->getSensor(port).value[0] & 0xFFFF);

        case ANALOG_ON:
        case ANALOG_OFF:
            return(gain*((float)(orbPtr->getSensor(port).value[0]&0xFFF)-offset));

        default:
            return(gain*((float)orbPtr->getSensor(port).value[0]-offset));
      }
    }

};
#endif
