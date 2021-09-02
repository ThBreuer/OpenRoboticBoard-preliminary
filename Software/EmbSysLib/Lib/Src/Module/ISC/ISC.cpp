//*******************************************************************
/*!
\file   Module/ISC.cpp
\author Thomas Breuer
\date   11.12.2014, 17.03.2016

This file is released under the MIT License.
*/

//*******************************************************************
#include "lib.h"
#include "Module/ISC.h"

//*******************************************************************
//
// cISC
//
//*******************************************************************
//-------------------------------------------------------------------
cISC::cISC( cCRC::MODE crcMode )

: crc( crcMode )

{
}

//-------------------------------------------------------------------
void cISC::write( BYTE id,
                  BYTE *data,
                  BYTE  size )
{
  crc.reset();
  crc(id);
  crc(0); // reserved
  for(BYTE i=0;i<size;i++)
    crc(data[i]);
  writeStream( id, data, size, crc.get() );
}

//EOF
