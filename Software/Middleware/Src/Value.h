//*******************************************************************
/*!
\file   Value.h
\author Thomas Breuer
\date
\brief
*/

//*******************************************************************
#ifndef _VALUE_H
#define _VALUE_H

//*******************************************************************
/*! brief Basisklasse für Messwerte

*/
template <class T> class Value
{
  protected:
    //---------------------------------------------------------------
    virtual T get( void ) = 0;

  public:
    //---------------------------------------------------------------
    /*! Liefert Laufzeit, siehe <code>get()</code>

        Diese Methode ergänzt die get()-Methode um Typkonvertierung,
        s.d. der Objektname direkt verwendet werden kann.<br>
        Beispiele:
        <UL>
        <LI><code> monitor.print( 1, "Zeit:%d", <b>(int)myValueObject</b> );</code></LI>
        <LI><code> if( <b>myValueObject</b> > 50 )</code></LI>
        </UL>
    */
    operator T( void )
    {
      return( get() );
    }
};

#endif // _VALUE_H

