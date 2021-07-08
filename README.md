# OpenRoboticBoard
**An open source PCB to control simple robots**

The board integrates the control electronics required to operate a robot. Sensors and actuators can be connected directly.

* **Power supply:**
  * The board is supplied with a 7.5V voltage (battery or LiPo).

* **Sensor connections:**
  * 4 ports for connecting sensors, each with a 5V power supply as well as 4 additional signal lines that can be used either as analog input (2x), digital IO (4x), UART or I2C interface. Alternatively, RJ-12 or 6-pin PCB header connector can be soldered in as a plug connection.
  * 2 ports for connecting a push button (binary input)

* **Actuator connections:**
  * 4 ports for connecting DC motors, each with a power output (H-bridge) as well as a power supply and digital input for an encoder.
  * 2 ports for connecting servo actuators

* **Bus connections:**
  * 1 port as I2C bus connection with power supply (5V)
  * 1 port as SPI bus connection with power supply (5V)

* **Communication:**
  * Bluetooth module
  * USB micro

* **Software download:**
  * USB boot loader
  * Debug interface

* **User interface:**
  * 2 push buttons
  * 3 LEDs
  * 1 reset button
  * 1 main switch
