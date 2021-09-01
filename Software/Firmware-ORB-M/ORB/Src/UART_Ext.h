//*******************************************************************
/*!
\file   UART_Ext.h
\author Thomas Breuer (Bonn-Rhein-Sieg University of Applied Sciences)
\date   12.03.2016
*/

//*******************************************************************
#ifndef _HW_UART_EXT_H
#define _HW_UART_EXT_H

//*******************************************************************
#include "Com/Hardware/UART/UART.h"

//-------------------------------------------------------------------
#if ( system_PCLK_UART != 21000000 )
  #error "system_PCLK_UART not defined or wrong value"
#endif

//*******************************************************************
/*!
\class cHwUART_Ext
\brief
*/
class cHwUART_Ext : public cHwUART_N
{
  public:
    //---------------------------------------------------------------
    cHwUART_Ext( USART_Id id,
                 DWORD    mode,
                 BYTE     sizeRxBuf,
                 BYTE     sizeTxBuf )

    : cHwUART_N::cHwUART_N( id, mode, sizeRxBuf, sizeTxBuf )

    {
      usartId = id;
    }

    //---------------------------------------------------------------
    void setBaudrate(float baudRate)
    {
      if( baudRate > 1500)
      {
        DWORD brr = (WORD)(2.0*system_PCLK_UART / baudRate);
        ptr->BRR  = (brr&0XFFF0) | ((brr>>1)&0x0007);
        ptr->CR1 |= USART_CR1_OVER8;
      }
      else
      {
        DWORD brr = (WORD)(system_PCLK_UART / baudRate);
        ptr->BRR  = brr;
        ptr->CR1 &= ~USART_CR1_OVER8;
      }
    }

    //---------------------------------------------------------------
    void connectToPort()
    {
      // clean FIFO
      BYTE dummy;
      while( get( &dummy ) );

      switch( usartId )
      {
        default:
          //error!
          break;

        case USART_1:
          cHwPinConfig::set( cHwPinConfig::USART1_RX );
          cHwPinConfig::set( cHwPinConfig::USART1_TX );
          break;

        case USART_2:
          cHwPinConfig::set( cHwPinConfig::USART2_RX );
          cHwPinConfig::set( cHwPinConfig::USART2_TX );
          break;

        case USART_3:
          cHwPinConfig::set( cHwPinConfig::USART3_RX );
          cHwPinConfig::set( cHwPinConfig::USART3_TX );
          break;

        case UART_4:
          cHwPinConfig::set( cHwPinConfig::UART4_RX );
          cHwPinConfig::set( cHwPinConfig::UART4_TX );
          break;

        case UART_5:
          cHwPinConfig::set( cHwPinConfig::UART5_RX );
          cHwPinConfig::set( cHwPinConfig::UART5_TX );
          break;

        case USART_6:
          cHwPinConfig::set( cHwPinConfig::USART6_RX );
          cHwPinConfig::set( cHwPinConfig::USART6_TX );
          break;
      }
    }

  private:
    //---------------------------------------------------------------
    USART_Id usartId;

}; //cHwUART_ext

#endif
