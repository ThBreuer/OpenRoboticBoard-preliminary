//*******************************************************************
/*!
\file   Drive.h
\author Thomas Breuer
\date
\brief  Steuerung eines Roboter-Fahrwerks mit zwei Motoren (Differential-Drive)
*/

//*******************************************************************
#ifndef _DRIVE_H
#define _DRIVE_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

//*******************************************************************
/*! \brief Fahrbewegungen eines Roboters (Differential-Drive) mit
    Motoren steuern

  <UL>
  <LI>Geschwindigkeit in mm/s</LI>
  <LI>Strecke in mm</LI>
  <LI>Winkel in Grad</LI>
  <LI>Positive Werte: Bewegung nach vorne bzw. rechts</LI>
  <LI>Negative Werte: Bewegung nach hinten bzw. links</LI>
  </UL>

*/
class Drive
{
  public:
    //---------------------------------------------------------------
    /*! \brief Bewegungsmessung eines Roboters

        Zur Bewegungsmessung werden die Daten der Encoder-Motoren benötigt
    */
    class Distance
    {
      public:
        //***********************************************************
        class cStrecke : public Value<int>
        {
          private:
            int offset;
            Drive &robo;
            cStrecke( Drive &r) : robo(r) { reset(); }
            void reset() { offset = robo.distance();}
          public:
            virtual int get()  { return(robo.distance() - offset ); }
          friend class Distance;
        };

        //***********************************************************
        class cWinkel : public Value<int>
        {
          private:
            int offset;
            Drive &robo;
            cWinkel( Drive &r) : robo(r) { reset(); }
            void reset() { offset = robo.winkel();}
          public:
            virtual int get()  { return(robo.winkel() - offset ); }
          friend class Distance;
        };

        //-----------------------------------------------------------
        /*! Erzeugt ein Objekt zur Distanzmessung. Zur Messung
            unterschiedlicher Distanzen können auch mehrere Objekte
            erzeugt und gleichzeitig verwendet werden
            \param roboter Ein Roboter-Objekt, dessen Bewegungen
            gemessen werden sollen
        */
        Distance( Drive &roboter )
        : winkel ( roboter ),
          strecke( roboter )
        {
          reset();
        }

        //-----------------------------------------------------------
        /*! Setzt Distanzmessung zurück
        */
        void reset( void )
        {
          strecke.reset();
          winkel.reset();
        }

        //-----------------------------------------------------------
        cWinkel  winkel;  //!< Liefert den Drehwinkel (in Grad) seit letztem Reset der Messung
        cStrecke strecke; //!< Liefert Strecke (in mm) seit letztem Reset der Messung
    };

  private:
    //---------------------------------------------------------------
    float vmax;
    float faktorMM2Tics;
    float faktorWinkel2Diff;

    Motor &mLi;
    Motor &mRe;

    int dLi;
    int dRe;

    ORB  &orb;

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Drive-Objekt
        \param motorLinks Objekt für den linken Motor
        \param motorRechts Objekt für den rechten Motor
        \param vmax Maximale Geschwindigkeit während der Positionierung
        \param radDurchmesser Durchmesser der Antriebsräder
        \param radAbstand Abstand der Räder (rechts-links)
    */
    Drive( Motor  &motorLinks,
           Motor  &motorRechts,
           int     vmax,
           int     radDurchmesser,
           int     radAbstand )
    : mLi( motorLinks  ),
      mRe( motorRechts ),
      orb( *orbPtr     )
    {
      this->vmax = (float)vmax;

      // abgeleitete Groessen:
      faktorMM2Tics     = 1000.0f/(M_PI*(float)radDurchmesser);
      faktorWinkel2Diff = (float)radAbstand*M_PI/360.0f;

      dLi = mLi.getPos();
      dRe = mRe.getPos();
    }

  private:
    //---------------------------------------------------------------
    virtual void fahre( int li, int re )
    {
      mLi.setSpeed( 0 );
      mRe.setSpeed( 0 );

      orb.wait( 200 );

      int targetLi = mLi.getPos() + li;
      int targetRe = mRe.getPos() + re;

      // Passe Geschwindigkeit der beiden Raeder so an,
      // dass diese gleichzeitig ihr Ziel erreichen
      float dges  = (fabs((float)li) + fabs((float)re));

      mLi.setPosition(  vmax * (float)li/dges, targetLi );
      mRe.setPosition(  vmax * (float)re/dges, targetRe );

      orb.wait( 200 );

      while(   fabs( (float)mLi.getPos() - targetLi ) > 1
            || fabs( (float)mRe.getPos() - targetRe ) > 1 )
      {
      }

      orb.wait( 200 );
    }

  public:
    //---------------------------------------------------------------
    /*! Fahre die angegeben Strecke

        Die Funktion blockiert solange, bis das Fahrziel erreicht wurde
        \param distance Länge der zurückzulegenden Strecke
    */
    virtual void strecke( float distance )
    {
      distance = faktorMM2Tics*distance; // Umrechnung mm in Grad

      fahre( distance, distance );
    }

    //---------------------------------------------------------------
    /*! Fahre einen Bogen

       Die Funktion blockiert solange, bis das Fahrziel erreicht wurde
       \param distance Länge des Bogens
       \param angle Winkel, um den sich die Fahrtrichtung ändern soll
    */
    virtual void bogen( float distance, float angle )
    {
      float li = distance + faktorWinkel2Diff*angle;
      float re = distance - faktorWinkel2Diff*angle;

      fahre( faktorMM2Tics*li, faktorMM2Tics*re );
    }

    //---------------------------------------------------------------
    /*! Fahre mit konstanter <b>Geschwindigkeit</b>
        \param li Geschwindigkeit linker Motor
        \param re Geschwindigkeit rechter Motor
    */
    virtual void speed( float li, float re )
    {
      mLi.setSpeed( faktorMM2Tics*li );
      mRe.setSpeed( faktorMM2Tics*re );
    }

    //---------------------------------------------------------------
    /*! Fahre mit konstanter <b>Leistung</b>
        \param li Geschwindigkeit linker Motor
        \param re Geschwindigkeit rechter Motor
    */
    virtual void power( float li, float re )
    {
      mLi.setPower( li );
      mRe.setPower( re );
    }

    //---------------------------------------------------------------
    /*! Bremse den Roboter (Kurzschlussbremse)
    */
    virtual void brake( void )
    {
      mLi.brake();
      mRe.brake();
    }

    //---------------------------------------------------------------

  private:
    //---------------------------------------------------------------
    virtual void distanceReset( void )
    {
      dLi = mLi.getPos();
      dRe = mRe.getPos();
    }

    //---------------------------------------------------------------
    virtual int distance( void )
    {
      int li = mLi.getPos()-dLi;
      int re = mRe.getPos()-dRe;

      return( 0.5*(li + re)/faktorMM2Tics+0.5 );
    }

    //---------------------------------------------------------------
    virtual int winkel( void )
    {
      int li = mLi.getPos()-dLi;
      int re = mRe.getPos()-dRe;

      return( (int)(0.5*(li - re)/(faktorMM2Tics*faktorWinkel2Diff)+0.5) );
    }
};
#endif
