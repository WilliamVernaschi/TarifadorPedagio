# MPLAB IDE generated this makefile for use with GNU make.
# Project: PEDAGIO.mcp
# Date: Sat Nov 30 07:36:05 2019

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

PEDAGIO.cof : PEDAGIO.o
	$(LD) /p18F4550 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "PEDAGIO.o" /u_CRUNTIME /o"PEDAGIO.cof" /M"PEDAGIO.map" /W

PEDAGIO.o : PEDAGIO.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/delays.h lcd.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/timers.h PEDAGIO.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f4550.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18cxxx.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/pconfig.h
	$(CC) -p=18F4550 "PEDAGIO.c" -fo="PEDAGIO.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "PEDAGIO.o" "PEDAGIO.cof" "PEDAGIO.hex"

