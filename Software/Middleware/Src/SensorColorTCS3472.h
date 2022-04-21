//*******************************************************************
/*!
\file   SensorColorTCS3472.h
\author Thomas Breuer
\date
\brief  Sensoren konfigurieren, kalibrieren und auslesen
*/

//*******************************************************************
#ifndef _SENSOR_COLOR_TCS3472_H
#define _SENSOR_COLOR_TCS3472_H

//*******************************************************************
#include "Common/Src/ORB.h"

//*******************************************************************
/*! \brief Sensoren konfigurieren, kalibrieren und auslesen

    Ein Objekt dieser Klasse erlaubt die Verwendung von Sensoren
*/
class SensorColorTCS3472 : public Sensor
{
  public:
    //---------------------------------------------------------------
    /*! Sensor-Port
    */
    typedef enum
    {
      RED = 0,   //!<
      GREEN,     //!<
      BLAU,      //!<
      WHITE,     //!<
      GRAY,      //!<
      BLACK      //!<
    } Color_type;

  private:

  public:
    //---------------------------------------------------------------
    /*! Erzeugt ein Sensor-Objekt

        Es werden auch die zuletzt gespeicherten Kalibrationsdaten
        abgerufen
        \param port Sensor-Port S1 bis S4
        \param mode Sensortyp und Sensormode (EV3)
    */
    SensorColorTCS3472( SensorPort_type port )
    : Sensor(port, Sensor::TCS3472_COLOR)
    {

      kalib();
    }

  private:
    //---------------------------------------------------------------
    void init(unsigned char modeIn)
    {
       orb.configSensor( port, ORB::I2C, 1, 0 );
       gain = 1.0;
       offset = 0.0;
    }

  public:
    //---------------------------------------------------------------
    /*! Kalibration des Sensors

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void kalibHundert()
    {

    }

    //---------------------------------------------------------------
    /*! Kalibration des Sensors

        Zum Speichern der Kalibrationsdaten muss <b>nach</b> der
        Kalibration die Methode <code>Memory::store()</code>
        aufgerufen werden
    */
    void kalibNull()
    {

    }

    //---------------------------------------------------------------
    /*! Liefert den Sensor-Messwert
        \return Messwert
    */
    virtual int get()
    {
			return(orbPtr->getSensor(port).value[0]);
    }

    //---------------------------------------------------------------
    /*! Liefert die Farbe
        \return Farbcode
    */
    Color_type getColor()
    {
      update();

      if( S > 20 && V >  8) // Farbe
      {
        if( 300 <= H || H <  60 )
          return( RED );
        if( 60  <= H && H < 180 )
          return( GREEN );
        return( BLAU );
      }
      else
      {
        if( V > 70 )
          return(WHITE);
        if( V > 30 )
          return(GRAY);
        return(BLACK);
      }
    }

    DWORD raw;

    class RGB
    {
    public:

      int R,G,B;
      RGB(DWORD raw = 0)
      {
        *this = raw;
      }

      void operator=(DWORD raw)
      {
        // red:10bit/green:12bit/blue:10bit 
        // rrrr rrrr rrgg gggg gggg ggbb bbbb bbbb
        //            |              |
        //            |              +-- Bit 10
        //            +----------------- Bit 22
        R = (raw >> 20)&0xFFC;
        G = (raw >> 10)&0xFFF;
        B = (raw <<  2)&0xFFC;
      }
    };

    public:

    int R,G,B;
    int H, // Hue, Farbwinkel
        S, // Saturation
        V; // Helligkeit

    float Rv,Gv,Bv;
    RGB offset;

    public:


    float range(float x, float min, float max)
    {
      if( x > max)
        return( max );
      if( x < min )
        return( min );
      return( x );
    }

    void update()
    {
      raw = get();

      RGB rgb(raw);


      R = range(Rv*(rgb.R-offset.R),0.0,2000.0);
      G = range(Gv*(rgb.G-offset.G),0.0,2000.0);
      B = range(Bv*(rgb.B-offset.B),0.0,2000.0);

     // B = 0.7*B;
     // R = 1.2*R;

      int min = 0;
      int max = 0;

      if( R>G && R>B ) // MAX = R
      {
        max = R;
        min = (G<B?G:B);
        H = ( 60.0*(0.0+(float)(G-B)/(max-min)));
      }
      else if(G>R&&G>B) //MAX = G
      {
        max = G;
        min = (R<B?R:B);
        H = ( 60.0*(2.0+(float)(B-R)/(max-min)));
      }
      else if(B>R&&B>G) // MAX = B
      {
        max = B;
        min = (R<G?R:G);
        H = ( 60.0*(4.0+(float)(R-G)/(max-min)));
      }
      else // R = G = B
      {
        max = R;
        min = R;
        H = 0;
      }
      if(H<0)
        H = 360+H;
      else if( H > 360)
        H = H - 360;

      if( max > 0 )
        S = 100.0*(max-min)/max;
      else
        S = 0;
      V = 0.1*max;
    }

    void kalibBlack()
    {
      update();
      kalib0 = (int)raw;

      kalib();


    }

    void kalibWhite()
    {
      update();
      kalib1 = (int)raw;

      kalib();



    }
  private:
    void kalib()
    {
      RGB c((DWORD)kalib1);
      offset = (DWORD)kalib0;

      if( c.R != offset.R )
        Rv = 1000.0/(c.R - offset.R);
      if( c.G != offset.G )
        Gv = 1000.0/(c.G - offset.G);
      if( c.B != offset.B )
        Bv = 1000.0/(c.B - offset.B);

    }

};
#endif
