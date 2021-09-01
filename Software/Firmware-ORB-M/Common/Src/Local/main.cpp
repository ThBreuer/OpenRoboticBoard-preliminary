//*******************************************************************
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "Common/Src/ORBlocal.h"

cORBlocal *orbPtr;

//*******************************************************************
class cApplicationBase
{
public:
  virtual void run(BYTE para) = 0;

};

//*******************************************************************
#include "Value.h"
#include "Memory.h"
#include "Timer.h"

#include "Motor.h"
#include "DoppelMotor.h"

#include "Sensor.h"
#include "SensorColorTCS3472.h"
#include "SensorDigital.h"
#include "SensorExtra.h"
#include "EncoderServo.h"

#include "ModelServo.h"

#include "Drive.h"
#include "Monitor.h"

#include "Application.h"



//*******************************************************************
int Main( BYTE para, cORBlocal &orb ) //,  IO::Data *ptr)
{
	orbPtr = &orb;


	Memory::clean();
  cApplication app;

  app.run( para );

  return(0);

}
//*******************************************************************
