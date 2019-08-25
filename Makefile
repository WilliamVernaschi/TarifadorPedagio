# MPLAB IDE generated this makefile for use with GNU make.
# Project: pulse.mcp
# Date: Sat Aug 24 18:34:53 2019

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

pulse.cof : pulse.o
	$(LD) /p18F4550 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "pulse.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"pulse.cof" /M"pulse.map" /W

pulse.o : pulse.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/delays.h lcd.h pulse.c ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f4550.h ../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18cxxx.h
	$(CC) -p=18F4550 "pulse.c" -fo="pulse.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "pulse.o" "pulse.cof" "pulse.hex"

