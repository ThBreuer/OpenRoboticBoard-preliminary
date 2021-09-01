////*******************************************************************
//#include "Module/RTOS.h"
//#include "config.h"

//#include "lib.h"
#include "Common/Src/ORBlocal.h"
int Main( BYTE para, cORBlocal &orb ); //, IO::Data *ptr);

//extern IO io;

int foo( BYTE para, cORBlocal &orb ) //, IO::Data *ioDataIn, int x)
{
  int y = -1;
  //io.ptr = ioDataIn;
 // if( ioDataIn != NULL )
    y = Main(para, orb); //, ioDataIn);
  return(y);
}

// GCC only:
//int main()
//{
//}

//EOF
//const int x1 __attribute__((at( 0x8080000))) = 0x1234; /* RO */
//
#if defined _KEIL
const unsigned x2 __attribute__((at( 0x8080000))) = (unsigned )foo; /* RO */
#elif defined _GCC
  int __attribute__((section(".startAppSection"))) x2 = (unsigned )foo; /* RO */
#endif
