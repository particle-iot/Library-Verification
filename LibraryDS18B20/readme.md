
## Library verification for DS18B20.
The purpose of this test is to verify the current DS18B20 temperature library from our community. This provides confidence to our Particle customers that the library can be used in their project.

This verification process performs unit-testing and testing on actual Particle devices.

## Bill of Materials to perform the verification
* Electron/Photon/Core.
* DS18b20 or DS1822 one-wire temperature sensor.
* Breadboard.
* Resistors of values between 1K to 10K.
* microUSB cable.
* Particle WEB IDE or DEV
* `Particle-cli` had been installed on computer.

## Library version list
* unit-test library `0.1.3`
* ds18b20 library `0.1.03`
* onewire library `1.4.1`

## Verify process
  1. Setup the hardware system based on the `ds18b20.fzz` diagram file. You may need to install Fritzing from [this website](http://fritzing.org/download/).
  2. Create a project in WEB IDE or Particle DEV and add the `libraryTest_DS18B20.ino` file into that project.
  3. Add the `UNIT-TEST` and `DS18B20` library before compiling the firmware.
  4. Once compiled successfully, flash the firmware to your Particle device.
  5. Make sure that the device is connected to your computer and it can be recognized as a serial port.
  6. run `particle serial monitor` from terminal.
  7. After the serial port has been recognized, type in `t` to start the verification test.
  8. Follow the test instruction and run the test.
  
  
  
  




