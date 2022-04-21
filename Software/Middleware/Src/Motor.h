//*******************************************************************
/*!
\file   Motor.h
\author Thomas Breuer
\date
\brief Steuerung eines Encoder-Motors
*/

//*******************************************************************
#ifndef _MOTOR_H
#define _MOTOR_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Steuerung von Motoren

    Mit einem Objekt dieser Klasse kann ein einzelner Motor gesteuert werde.
    Es sind verschiedene Betriebsarten möglich.
*/
class Motor
{
  public:
    //---------------------------------------------------------------
    /*! Motor-Port
    */
    typedef enum
    {
      M1  = 0x00, //!< Motor Port 1
      M2,         //!< Motor Port 2
      M3,         //!< Motor Port 3
      M4          //!< Motor Port 4
    } Port_type;

    //---------------------------------------------------------------
    /*! Orientierung/Einbaulage des Motors
    */
    typedef enum
    {
      NORMAL = 0,      //!< Normaler Drehsinn des Motors
      REVERSE = 0x80   //!< Invertierter Drehsinn des Motors
    } Orientation_type;

    //---------------------------------------------------------------
    /*! Motortyp
    */
    typedef enum
    {
      LEGO,        //!< LEGO-Motor (NXT, EV3), 720 Tics/Umdrehung
      MAKEBLOCK,   //!< MAKEBLOCK Motor Encoder 180, 1440 Tics/Umdrehung
      FAULHABER    //!< Faulhaber Encodermotor, 88000 Tics/Umdrehung
    } Type_type;

  private:
    //---------------------------------------------------------------
    BYTE   port;
    float  orientation;
    ORB   &orb;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Motor-Objekt
        \param port Motor-Port M1 bis M4
        \param orientation Einbaurichtung des Motors, legt positiven Drehsinn fest
        \param type Motor-Typ (LEGO, Makeblock, Faulhaber)
     */
    Motor( Port_type        port,
           Orientation_type orientation,
           Type_type        type )
    : orb( *orbPtr )
    {
      this->port        = port;
      this->orientation = (orientation==NORMAL)?+1.0:-1.0;

      switch( type )
      {
        case LEGO:      orb.configMotor( port,   72, 25, 30, 30 ); break;
        case MAKEBLOCK: orb.configMotor( port,  144, 50, 50, 30 ); break;
        case FAULHABER: orb.configMotor( port, 8800, 25, 50, 50 ); break;
      }
    }

  public:
    //---------------------------------------------------------------
    /*! Motor bremst (Kurzschlussbremse), s.d. Motor schwergängig ist,
        sich aber nicht eigenständig dreht
    */
    virtual void brake( void )
    {
      orb.setMotor( port, ORB::BRAKE_MODE, 0, 0 );
    }

    //---------------------------------------------------------------
    /*! Stellt die Leistung des Motors ein.
        \param power Leistung 0 (Leerlauf) bis 1000 (Maximum)
    */
    virtual void setPower( short power )
    {
      orb.setMotor( port, ORB::POWER_MODE, orientation*power, 0 );
    }

    //---------------------------------------------------------------
    /*! Stellt die Drehgeschwindigkeit eines Motors ein
        \param speed Drehzahl, 0 (Stillstand), ansonsten beliebiger Wert
        Einheit: 1000 entspricht einer Umdrehung pro Sekunde
    */
    virtual void setSpeed( short speed )
    {
      orb.setMotor( port, ORB::SPEED_MODE, orientation*speed, 0 );
    }

    //---------------------------------------------------------------
    /*! Setzt Zielposition für Positionierung
        \param speed Geschwindigkeit, mit der Ziel erreicht werden soll
        \param position Position, die angefahren werden soll, Einheit: 1000 = 1 Umdrehung.
        Die Position wird absolut angegeben, also seit Start des Controllers
    */
    virtual void setPosition( short speed, int position )
    {
      orb.setMotor( port, ORB::MOVETO_MODE,orientation*speed, orientation*position );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Leistung
        \return Aktuelle Motorleistung, 0 = Leerlauf, 1000 = Maximum
    */
    short getPower()
    {
     
      return( orientation*orb.getMotor(port).pwr );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Drehgeschwindigkeit
        \return Aktuelle Drehgeschwindigkeit, 1000 = 1 Umdrehung po Sekunde
    */
    short getSpeed()
    {
      return( orientation*orb.getMotor(port).speed );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Position des Motors
        \return Aktuelle Position, 1000 = 1 Umdrehung
    */
    int getPos()
    {
      return( orientation*orb.getMotor(port).pos );
    }
};
#endif
