//*******************************************************************
/*!
\file   DoppelMotor.h
\author Thomas Breuer
\date
\brief Steuerung eines Encoder-Motors
*/

//*******************************************************************
#ifndef _DOPPEL_MOTOR_H
#define _DOPPEL_MOTOR_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Steuerung von Motoren

    Mit einem Objekt dieser Klasse kann ein einzelner Motor gesteuert werde.
    Es sind verschiedene Betriebsarten möglich.
*/
class DoppelMotor : public Motor
{
  public:
    
  private:
    //---------------------------------------------------------------
    Motor  motor;
	  

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Motor-Objekt
        \param port Motor-Port M1 bis M4
        \param orientation Einbaurichtung des Motors, legt positiven Drehsinn fest
        \param type Motor-Typ (LEGO, Makeblock, Faulhaber)
     */
    DoppelMotor( Port_type        port,
                 Port_type        port2,
                 Orientation_type orientation,
                 Type_type        type )
    : Motor(port,orientation,type), motor( port2,orientation,type)
    {
      
    }

  public:
    //---------------------------------------------------------------
    /*! Motor bremst (Kurzschlussbremse), s.d. Motor schwergängig ist,
        sich aber nicht eigenständig dreht
    */
    virtual void brake( void )
    {
      Motor::brake(); //orb.setMotor( port, ORB::BRAKE_MODE, 0, 0 );
			motor.brake();
    }

    //---------------------------------------------------------------
    /*! Stellt die Leistung des Motors ein.
        \param power Leistung 0 (Leerlauf) bis 1000 (Maximum)
    */
    virtual void setPower( short power )
    {
      Motor::setPower( power );
			motor.setPower( power );
    }

    //---------------------------------------------------------------
    /*! Stellt die Drehgeschwindigkeit eines Motors ein
        \param speed Drehzahl, 0 (Stillstand), ansonsten beliebiger Wert
        Einheit: 1000 entspricht einer Umdrehung pro Sekunde
    */
    virtual void setSpeed( short speed )
    {
      Motor::setSpeed( speed );
			motor.setSpeed( speed );
    }

    //---------------------------------------------------------------
    /*! Setzt Zielposition für Positionierung
        \param speed Geschwindigkeit, mit der Ziel erreicht werden soll
        \param position Position, die angefahren werden soll, Einheit: 1000 = 1 Umdrehung.
        Die Position wird absolut angegeben, also seit Start des Controllers
    */
    virtual void setPosition( short speed, int position )
    {
      Motor::setPosition( speed, position );
			motor.setPosition( speed, position );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Leistung
        \return Aktuelle Motorleistung, 0 = Leerlauf, 1000 = Maximum
    */
    short getPower()
    {
      return( 0.5*(Motor::getPower() + motor.getPower()) );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Drehgeschwindigkeit
        \return Aktuelle Drehgeschwindigkeit, 1000 = 1 Umdrehung po Sekunde
    */
    short getSpeed()
    {
      return( 0.5*(Motor::getSpeed() + motor.getSpeed()) );
    }

    //---------------------------------------------------------------
    /*! Liefert aktuelle Position des Motors
        \return Aktuelle Position, 1000 = 1 Umdrehung
    */
    int getPos()
    {
      return( 0.5*(Motor::getPos()+motor.getPos()) );
    }
};
#endif
