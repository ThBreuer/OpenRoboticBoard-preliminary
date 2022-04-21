//*******************************************************************
/*!
\file   ModelServo.h
\author Thomas Breuer
\date
\brief  Modellbau-Servo steuern
*/

//*******************************************************************
#ifndef _MODEL_SERVO_H
#define _MODEL_SERVO_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Modellbau-Servo steuern

    Mit einem Objekt dieser Klasse lässt sich ein Modellbau-Servo steuern.

    Der Winkel wird in Grad (Vollkreis = 360°) angegeben.

    \warning Die Methoden sind noch nicht vollständig implementiert

*/
class ModelServo
{
  public:
    //---------------------------------------------------------------
    /*! Port für den Anschluss des Servos
    */
    typedef enum
    {
      S1 = 0,
      S2 = 1
    } ServoPort_type;

  private:
    //---------------------------------------------------------------
    BYTE   port;
    float  gain;
    ORB  &orb;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt eine ModelServo-Objekt

        Der Servo wird mit dem Standard-Steuersignal angesteuert, der
        daraus resutierende Stellwinkel hängt vom Servotyp ab.
        \param port Servo-Port S1 oder S2
        \param maxAngle Maximaler Stellwinkel des Servos
    */
    ModelServo( ServoPort_type port,
                short          maxAngle = 0
               )
    : orb( *orbPtr )
    {
      this-> port = port;
      gain = (maxAngle>0)?100.0/maxAngle:1.0;
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
      // TODO: speed bereich prüfen und umrechnen
      orb.setModelServo( port, speed/10, gain*angle );
    }

    //---------------------------------------------------------------
    /*! Schaltet Servomotor aus
    */
    virtual void halt( void )
    {
      // TODO: Implementierung fehlt
      //orb.setModelServo( port, 0, 0 );
    }
};
#endif
