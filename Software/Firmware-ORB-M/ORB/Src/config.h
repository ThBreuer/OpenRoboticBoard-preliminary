//*******************************************************************
/*!
\file   config.h
\author Thomas Breuer
\date   02.02.2021
\brief  Configuration file
*/

//*******************************************************************
#include "descriptor.cpp"

//*******************************************************************
#if (BOARD_MAIN == 1 )

  #error "Board hardware not supported"

#elif (BOARD_MAIN == 2 && BOARD_SUB == 1)

  #include "config_Board_02_01.h"

#elif (BOARD_MAIN == 2 && BOARD_SUB == 2)

  #include "config_Board_02_02.h"

#elif (BOARD_MAIN == 2 && BOARD_SUB == 3)

  #include "config_Board_02_03.h"

#else

  #error "Board hardware version not defined"

#endif

//EOF
