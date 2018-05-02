# Input signal selector switch

Input signal selector (ISS) swith for audio amplifier. 

Note: This git-project provides only the firmware for ISS mmicrocontroller. The hardware design can be found on 
the [easyEDA](https://easyeda.com/mlytvyn/input-selector) webpage.


## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

The project was developed under Linux OS using avr-gcc toolchain and GNU c-library for AVR. 
And hence, all instruction given here is written with respect to this environment. 



### Installing

You can build the microcontroller HEX-file from scratch and than flash it with your favorite program.
Or you can skip buiding firmware and use HEX-file from firmware folder. 

#### 1) Compiling firmware and uploading file using CMake:
The project is based on the CMake build tool and recommended way to build and upload the HEX-file is:


First of all check the CMakeList.txt for the correct settings for your hardware. 
Please check the programmator settings:
```
set(AVR_UPLOADTOOL avrdude)
set(AVR_UPLOADTOOL_PORT usb)
set(AVR_PROGRAMMER usbasp)
set(AVR_UPLOAD_BAUDRATE 115200)
set(AVR_UPLOADTOOL_OPTIONS "")
```

and microcontroller settings:

```
set(AVR_MCU atmega328p)
```
The fuse and AVR_MCU_SPEED (CPU clock of 12 MHz) should not be changed.

Create build directory
```
mkdir iss_switch-build
```

Generate Makefile
```
cd iss_switch-build
cmake <path-to-source-dir>
```

Compile the firmware make utility
```
make
```

Upload firmware to microcontroller:
```
make upload_iss_switch
make upload_eeprom
make set_fuses
```

The list of supported targets can be obtained by issuing:
```
make help
```

#### 2) Flash microcontroller with HEX-file:

You can use yor favorite flashing tool and microsontroller. Here the example 
using [avrdude](https://www.nongnu.org/avrdude/)  and [usbasp](http://www.fischl.de/usbasp/):


```
avrdude -c usbasp -p m328p
```

## Built With

* [AVR libc](https://www.nongnu.org/avr-libc/) - The AVR C Library
* [gcc-avr, gdb-avr](http://www.microchip.com/avr-support/avr-and-arm-toolchains-(c-compilers)) - AVR 8-bit GNU Toolchain
* [CMake](https://cmake.org) - CMake build system
* [cmake-avr](https://github.com/mkleemann/cmake-avr) - CMake toolchain for AVR projects

Additionaly the following software and hardware tools were used:

* [QtCreator](http://doc.qt.io/qtcreator/) - My favorite IDE
* [QtCreator AVR Wizard](https://git.ok1kvk.cz/avr/avr-qtcreator) - AVR project creator for QtCreator
* [AVR Dragon](http://www.microchip.com/DevelopmentTools/ProductDetails.aspx?PartNO=ATAVRDRAGON) - AVR Dragon low cost development tools for 8-bit and 32-bit AVR devices

## Authors

* **Mykhailo Lytvyn**

## License

This project is licensed under the GNU General Public License v3.0  - see the [LICENSE.md](LICENSE.md) file for details.

