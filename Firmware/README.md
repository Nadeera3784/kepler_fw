# Kepler FW

This is the firmware for the F91 Smart Watch (Kepler). It is designed to run on 
the [TI CC2640](http://www.ti.com/product/CC2640) SoC and is based off the example
project "Simple Peripheral".

## Services and Characteristics
Currently the following services and characteristics are present on the FW.

- `FA35A2F0-7989-11EB-9439-0242AC130002` **Notification Service**
  - `FA35A2F1-7989-11EB-9439-0242AC130002` **Notification Bar** (read, write)
    - A uint8 in that inidicates which notifications to display in the top bar.
  - `FA35A2F2-7989-11EB-9439-0242AC130002` **Incoming Call** (write)
    - A uint8 array representing an incoming call with the contact name.
  - `FA35A2F3-7989-11EB-9439-0242AC130002` **Incoming Text** (write)
    - A uint8 array representing an incoming text with the contact name.
- `FA35B2F0-7989-11EB-9439-0242AC130002` **Clock Service**
  - `FA35B2F1-7989-11EB-9439-0242AC130002` **Time** (read, write)
    - A uint32 that sets the current utc time in seconds.
  - `FA35B2F2-7989-11EB-9439-0242AC130002` **Time Zone** (read, write)
    - A uint16 that sets the current time zone, represented by seconds west of UTC.
  - `FA35B2F3-7989-11EB-9439-0242AC130002` **Time Mode** (read, write)
    - A uint8 that sets the time mode to display either 12hr (0x00) or 24hr (0x01) mode.
  - `FA35B2F4-7989-11EB-9439-0242AC130002` **DST** (read, write)
    - A uint8 that sets daylight savings time (0x00) normal or (0x01) dst.

## Compiling

The project is compiled and tested with [TI's Code Composer
Studio](http://www.ti.com/tool/CCSTUDIO) version 10.1.1.00004. 
You will also need to install, TI's [BLEstack](http://www.ti.com/tool/BLE-STACK) version 2.2.5 

The ARM Compiler used for this project is version 18.1.0.20181119225258 provided by TI.

A great resource on setting up the stack for the first time can be found [HERE](http://software-dl.ti.com/lprf/simplelink_cc2640r2_sdk/1.30.00.25/exports/docs/blestack/ble_sw_dev_guide/html/cc2640/platform.html#installing-blestack).

## Flashing

Flashing the CC2640 SoC can be done with the various XDS emulators,
e.g. XDS100v3. Once connected, use TI's [SmartRF Flash Programmer
2](http://www.ti.com/tool/FLASH-PROGRAMMER) to load the image.

## Resources

I'm sure all this stuff is overwhelming to most. It took me a good chunk of time to understand most of this stuff and I am by no means an expert and still learning.
Here are some of the resources that helped me along the way to understand how to develop with TI's BLE stack.

[Great Starting Point (provided by TI)](http://software-dl.ti.com/lprf/simplelink_cc2640r2_sdk/1.30.00.25/exports/docs/blestack/ble_sw_dev_guide/html/cc2640/get-started/get-started.html)
This document is fat. Lots of info that also links to other resources which are extremely helpful.
- The section within this document titled [Developing a Bluetooth Low Energy Application](http://software-dl.ti.com/lprf/simplelink_cc2640r2_sdk/1.30.00.25/exports/docs/blestack/ble_sw_dev_guide/html/ble-stack/index.html#) was very helpful.

