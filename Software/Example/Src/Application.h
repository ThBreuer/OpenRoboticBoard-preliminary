/********************************************************************
  Vorlage fuer ORB-Anwendungssoftware
********************************************************************/

//*******************************************************************
class cApplication : public cApplicationBase
{
  private:
    //---------------------------------------------------------------
    Monitor monitor;
    Sensor   sensor;
    Motor   motor;
    Timer   time;
    // insert class member

  public:
    //---------------------------------------------------------------
    cApplication( void )

    : monitor()
    ,sensor( Sensor::S1, Sensor::EV3_FARBSENSOR_FARBE )
    ,motor( Motor::M1, Motor::NORMAL, Motor::LEGO )
      // insert constructor

    {
      monitor.clear();
      // insert code
    }

    //---------------------------------------------------------------
    virtual void run(BYTE para)
    {
      if( para == 0)
      {
        int cnt=0;
        while(1)
        {
          // insert code
          motor.setPower( 200);
          monitor.print(1,"0: Hello world! A");
          monitor.print(2,"Sensor: 0x%08x %d",(int)sensor,(int)sensor);
          monitor.print(3,"Motor: %4d %4d %d",motor.getPower(),motor.getSpeed(),motor.getPos());
          monitor.print(4,"cnt: %d",cnt++);
          time.wait(1000);
        }
      }
      else
      {
        while(1)
        {
//          monitor.print(1,"1: Hello world! A");
//          monitor.print(2,"Key: %d",monitor.getKeyState());
           motor.setPower(500);
          time.wait(100);
          motor.setPower(-500);
          time.wait(100);
        }
      }
    }
};
