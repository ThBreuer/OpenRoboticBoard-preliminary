//*******************************************************************
/*!
\file   Sensor.h
\author Thomas Breuer
\date
\brief  Sensorwerte der zusätzlichen Digitaleingänge erfassen
*/

//*******************************************************************
#ifndef _SENSOR_DIGITAL_H
#define _SENSOR_DIGITAL_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Sensorwerte der zusätzlichen Digitaleingänge erfassen

    Ein Objekt dieser Klasse erlaubt das Einlesen der Digitaleingänge
*/
class SensorDigital : public Value<int>
{
  public:
    //---------------------------------------------------------------
    /*! Digital-Port
    */
    typedef enum
    {
      D1 = 0, //!< Digitalport 1
      D2 = 1  //!< Digitalport 2
    } SensorPort_type;

  private:
    //---------------------------------------------------------------
    BYTE  port;
    ORB  &orb;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Objekt
        \param port Digitalport D1, D2
    */
    SensorDigital( SensorPort_type port )
    : orb( *orbPtr )
    {
      this->port = port;
    }

  public:
    //---------------------------------------------------------------
    /*! Liefert Zustand des Digitalports
        \return Messwert (0,1)
    */
    virtual int get( void )
    {
      return( orbPtr->getSensorDigital( port ) );
    }

};
#endif
