//*******************************************************************
/*!
\file   EncoderServo.h
\author Thomas Breuer
\date
\brief  Encoder-Motor als Servo steuern
*/

//*******************************************************************
#ifndef _ENCODER_SERVO_H
#define _ENCODER_SERVO_H

//*******************************************************************
#include "Common/Src/ORB.h"
#include "math.h"

//*******************************************************************
/*! \brief Encoder-Motor als Servo steuern

    Mit einem Objekt dieser Klasse lässt sich ein Encoder-Motor wie
    ein Servo steuern.

    Der Winkel wird in Grad (Vollkreis = 360°) angegeben.
*/
class EncoderServo : public Value<int>
{
  private:
    //---------------------------------------------------------------
    int    offset;
    ORB  &orb;
    Motor &motor;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Servo-Objekt

        Die aktuelle Position des Motors wird als Null-Position übernommen
        \param motor Motor-Objekt, das als Servo verwendet werden soll
    */
    EncoderServo( Motor &motor )
    : orb  ( *orbPtr ),
      motor(  motor )
    {
      offset = motor.getPos();
      halt();
    }

    //---------------------------------------------------------------
    /*! Übernimmt die aktuelle Position als neue Null-Position
    */
    void reset( void )
    {
      offset = motor.getPos();
    }

    //---------------------------------------------------------------
    /*! Stellt den Servo auf den angegebenen Winkel ein

        Diese Funktion blockiert nicht
        \param angle Stellwinkel
        \param speed Geschwindigkeit, mit der der Stellwinkel
        angefahren wird (optional)
    */
    virtual void set( short angle, short speed = 1000 )
    {
      motor.setPosition( speed, (1000.0/360.0)*angle + offset );
    }

    //---------------------------------------------------------------
    /*! Stellt den Servo auf den angegebenen Winkel und <b>wartet</b>,
        bis dieser erreicht wurde
        \param angle Stellwinkel
        \param speed Geschwindigkeit, mit der der Stellwinkel
        angefahren wird (optional)
    */
    virtual void moveTo( short angle, short speed = 1000 )
    {
      orb.wait( 500 );

      int target = (1000.0/360.0)*angle + offset;

      motor.setPosition( speed, target );

      while( fabs((float)(motor.getPos() - target)) > 2);

      orb.wait( 500 );
    }

    //---------------------------------------------------------------
    /*! Schaltet Servomotor aus
    */
    virtual void halt( void )
    {
      motor.setPower( 0 );
    }

    //---------------------------------------------------------------
    /*! Schalte Servomotor in den Brems-Modus (Kurzschlussbremse)
    */
    virtual void brake( void )
    {
      motor.brake();
    }

    //---------------------------------------------------------------
    /*! Gibt den aktuellen Stellwinkel zurück
        \return Stellwinkel (in Grad)
    */
    virtual int get( void )
    {
      return( 0.36*(motor.getPos() - offset) );
    }
};
#endif
