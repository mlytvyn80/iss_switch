##################################################################################
# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann
#
# Adapted and extended by Mykhailo Lytvyn 
##################################################################################

cmake_minimum_required(VERSION 2.8)

# Disable in-source build
# this means you will not able to build project in the directory with source files
#set(CMAKE_DISABLE_SOURCE_CHANGES ON)
#set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(ISS_switch C)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Compiler options: include debug symbols, optimize for size, be strict and display 
# all warnings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Os -Wall -pedantic -Wextra")

### TOOLCHAIN SETUP AREA #########################################################
# Set any variables used in the toolchain prior project() call. In that
# case they are already set and used.
##################################################################################

##################################################################################
# tools to be used for programming the AVR
##################################################################################
set(AVR_UPLOADTOOL avrdude)
set(AVR_UPLOADTOOL_PORT usb)
set(AVR_PROGRAMMER usbasp)
set(AVR_UPLOAD_BAUDRATE 115200)
set(AVR_UPLOADTOOL_OPTIONS "")

#set(WITH_MCU OFF)
#set(WITH_MCU OFF CACHE BOOL "Add the mCU type to the target file name." FORCE)

##################################################################################
# AVR and fuses needs to be set
##################################################################################
set(AVR_MCU "atmega328p")
set(AVR_H_FUSE "D9")
set(AVR_L_FUSE "6F")
set(AVR_E_FUSE "FF")

##################################################################################
# needs to be defined for AVR toolchain
##################################################################################
set(AVR_MCU_SPEED "1200000UL")

### END TOOLCHAIN SETUP AREA #####################################################

find_package(Generic-AVR-GCC  REQUIRED)

##################################################################################
# name your project
##################################################################################

set(CMAKE_BUILD_TYPE Release)

##################################################################################
# set command line arguments for compiler
##################################################################################
add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
add_definitions("-Werror")
# http://gcc.gnu.org/onlinedocs/gcc-4.8.2/gcc/Alternate-Keywords.html#Alternate-Keywords
# [...]-pedantic and other options cause warnings for many GNU C extensions. You can prevent such warnings within
# one expression by writing __extension__ before the expression. __extension__ has no effect aside from this.[...]
add_definitions("-pedantic")
add_definitions("-pedantic-errors")
add_definitions("-funsigned-char")
add_definitions("-funsigned-bitfields")
add_definitions("-ffunction-sections")
add_definitions("-c")
add_definitions("-std=gnu99")

##################################################################################
# add AVR executable - (<executable-name> <sources> <headers>)
##################################################################################
set(ISS_SWITCH_SOURCES src/hal.h
                       src/rc5.c
                       src/timer.c
                       src/main.c)

add_avr_executable(
   iss_switch 
   ${ISS_SWITCH_SOURCES}
)

#set_target_properties(io_selector.elf PROPERTIES LINKER_LANGUAGE C)
##################################################################################
# add AVR library
##################################################################################
#add_avr_library(
#   <library-name>
#   <sources> <headers>
#)

##################################################################################
# link library to executable
# NOTE: It needs to be the elf target.
##################################################################################
# target_link_libraries(<executable-name>-${AVR_MCU}.elf <library-name>-${AVR_MCU})
# OR easier
#target_link_libraries(<executable-name> <library-name> <some-external-libary>)
