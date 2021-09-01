//*******************************************************************
/*!
\file   Whiteboard.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   02.02.2021

This file is released under the MIT License.
*/

//*******************************************************************
#ifndef _STD_WHITEBOARD_H
#define _STD_WHITEBOARD_H

//*******************************************************************

//*******************************************************************
/*!
\class cWhiteboard

\brief Shared memory, locked memory read and write.
The shared memory can be used for inter task communication

\example cWhiteboard.cpp
*/
template <class T, BYTE numOfClients> class cWhiteboard
{
  public:

    BYTE last;
    BYTE current;

class Handler
{
  public:
  BYTE idx;
  T *t;
  cWhiteboard &wb;

  Handler( cWhiteboard &wb )
  : wb(wb)
  {
    idx = wb.lockRead();
    t = &wb[idx%(numOfClients+2)];
  }

  ~Handler()
  {
    close();
  }

  T &open()
  {
    if( idx == 0xFF )
    {
      idx = wb.lockRead();
      t = &wb[idx%(numOfClients+2)];
    }
    return( *t );
  }

  void close()
  {
    if( idx != 0xFF )
    {
      wb.unlockRead(idx);
      idx =0xFF;
    }
  }

  T &get()
  {
     return( *t );
  }


};
    //---------------------------------------------------------------
    /*! Create a shared memory. The memory is zero initialized
    */
    cWhiteboard( void )
    {
      memset( &buffer[0], 0, sizeof(T) );
      for(BYTE i=0;i<numOfClients+2;i++)
        locked[i]=false;
      last = 0;
    }

    cWhiteboard( T &t )
    {
      buffer[0] = t;
      for(BYTE i=0;i<numOfClients+2;i++)
        locked[i]=false;
      last = 0;
      current = 0xFF;
    }

    BYTE lockWrite()
    {
      BYTE k = (last+1)%(numOfClients+2);
      while(locked[k])
        k = (k+1)%(numOfClients+2);
      current = k;
      return( current);
    }

    void unlockWrite()
    {
      last = current;
      current = 0xFF;
    }

    BYTE lockRead()
    {
      cSystem::disableInterrupt();
      BYTE l = last;
      locked[l]++;
      cSystem::enableInterrupt();
      return(l);
    }

    void unlockRead(BYTE l)
    {
      l = l%(numOfClients+2);
      cSystem::disableInterrupt();
      if( locked[l] )
        locked[l]--;
      cSystem::enableInterrupt();
    }

    T &operator[](BYTE idx)
    {
      return( buffer[idx%(numOfClients+2)] );
    }

    //---------------------------------------------------------------


    //---------------------------------------------------------------

  private:
    //---------------------------------------------------------------
    T buffer[numOfClients+2];
    BYTE locked[numOfClients+2];

}; //cSharedMem

#endif
