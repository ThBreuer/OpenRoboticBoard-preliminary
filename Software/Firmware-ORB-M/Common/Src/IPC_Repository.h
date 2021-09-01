#ifndef _IPC_REPOSITORY_H
#define _IPC_REPOSITORY_H



//*******************************************************************
class cIPC_Repository : public cISC
{
  public:
    cIPC_Repository( cHwUART_Serial &uartIn, cUSB &usbIn, cNetUDP &tcpIn,cNetAddr<4> serverAddr, int port ) //= 20001 )
    : cISC(cCRC::FAST),
      uart( uartIn),
      usb(usbIn),
      udp(tcpIn),
      ipcUart(uart),
      ipcUsb( usb, 0),
      ipcUDP( udp, serverAddr, port, cCRC::SMALL )
    {
      ipc = NULL;
      port = 0;
    }

    void setNoPort()
    {
      port = 0;
      close();

    }

    void setUart()
    {
      ipcUart.list = list;
      uart.open();
      ipc = &ipcUart;
      port = 1;
      usb.close();
      ipcUDP.close();
    }

    void setUsb()
    {
      ipcUsb.list = list;
      usb.open(0x0023,0x1000,0);
      ipc = &ipcUsb;
      port = 2;
      //usb.close();
      ipcUDP.close();
      uart.close();
    }

    void setNet()
    {
      ipcUDP.list = list;
      ipcUDP.open();
      ipc = &ipcUDP;
      port = 3;
      usb.close();
      uart.close();
    }

    void update()
    {
      if( ipc )
      {
          ipc->update();
          ipc->update();
//printf("update\n");
      }

    }

    void writeStream(BYTE id, BYTE *data, BYTE size, WORD crc)
    {
      if( ipc )
        ipc->writeStream(id, data, size, crc );
    }

    BYTE open()
    {
        close();
      switch( port )
      {
        case 1: uart.open();                break;
        case 2: usb.open (0x0023,0x1000,0); break;
        case 3: ipcUDP.open();break;
      }
      return(0);
    }

    BYTE isOpen()
    {
      switch( port )
      {
        case 1: return( uart.isOpen() );
        case 2: return( usb.isOpen() );
        case 3: return( ipcUDP.isOpen() );
      }
      return( false );
    }

     void close()
    {
      if( uart.isOpen() )
        uart.close();
      if( usb.isOpen() )
        usb.close();
      if( ipcUDP.isOpen() )
        ipcUDP.close();
    }

    cHwUART_Serial &uart;
    cUSB    &usb;
    cNetUDP &udp;
    cISC_UART ipcUart;
    cISC_USBhost  ipcUsb;
    cISC_UDP      ipcUDP;

    cISC     *ipc;

    BYTE     port;
};

#endif
