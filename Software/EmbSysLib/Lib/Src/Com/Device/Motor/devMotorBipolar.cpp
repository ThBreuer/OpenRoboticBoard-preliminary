//*******************************************************************
/*!
\file   devMotorBipolar.cpp
\author Thomas Breuer
\date   22.02.2019

This file is released under the MIT License.
*/

//*******************************************************************
//
// cDevMotorBipolar
//
//*******************************************************************
//-------------------------------------------------------------------
cDevMotorBipolar::cDevMotorBipolar( cDevAnalogOut  &plusIn,
                                    cDevAnalogOut  &minusIn )
: plus ( plusIn  ),
  minus( minusIn )
{
}

//-------------------------------------------------------------------
void cDevMotorBipolar::run( float speed )
{
  plus  = +speed;
  minus = -speed;
}

//-----------------------------------------------------------------
void cDevMotorBipolar::brake( void )
{
  plus  = +(float)maxPwr;
  minus = +(float)maxPwr;
}

//EOF
