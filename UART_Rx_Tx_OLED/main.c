/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to receive and transmit data through UART and display same on LCD.  

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
    Copyright (C) 2012  ExploreEmbedded

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/
#include "lcd.h"
#include "uart.h"
#include "lpc17xx.h"
#include "delay.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * 
 */
 struct formDisplayString{
	 int _screen;
	 int _hour;
	 int _min;
	 int _battery;
	 char* _songs[5];
	 char* _currentlyPlaying;
	 int _durationMin;
	 int _durationSec;
 };
 /*
 char* convChar(int i){
	 char* c;
	 char k;
	 sprintf(k, "%d", i);
	 return c;
 }*/
 char* parseString(struct formDisplayString *fd){
	 char temp[20];
	 char* t;
	 char* finalString ;
	 sprintf(temp, "%d", fd->_screen);
	 t = temp;
	 strcpy(finalString, "screen:");
	 strcat(finalString, temp); 
	 
	 strcat(finalString, ";time:");
	 sprintf(temp, "%d", fd->_hour);
	 strcat(finalString, temp);
	 strcat(finalString, ":");
	 sprintf(temp, "%d", fd->_min);
	 strcat(finalString, temp);
	 strcat(finalString, ";battery:");
	 sprintf(temp, "%d", fd->_battery);
	 strcat(finalString, temp);
	 strcat(finalString, ";");
	 strcat(finalString, fd->_songs[0]);
	 strcat(finalString, ",");
	 strcat(finalString, fd->_songs[1]);
	 strcat(finalString, ",");	 
	 strcat(finalString, fd->_songs[2]);
	 strcat(finalString, ",");
	 strcat(finalString, fd->_songs[3]);
	 strcat(finalString, ",");	 
	 strcat(finalString, fd->_songs[4]);
	 strcat(finalString, ";currentlyplaying:");
	 strcat(finalString, fd->_currentlyPlaying);
	 strcat(finalString, ";duration:");
	 sprintf(temp, "%d", fd->_durationMin);
	 strcat(finalString, temp);
	 strcat(finalString, ":");
	 sprintf(temp, "%d", fd->_durationSec);
	 strcat(finalString, temp);
	 strcat(finalString, ";#\n");
	 
	 return finalString;
 }
 
 char* param_calc(int screen, int battery, char* songs,
										char* currently_playing, int hour, int min, int durationMin, int durationSec){
	char* finalString;
  struct formDisplayString fds;
	fds._battery = battery;
	fds._durationMin = durationMin;
	fds._durationSec = durationSec;
	fds._hour = hour;
	fds._min = min;
	fds._screen = screen;
	fds._currentlyPlaying = currently_playing;
	fds._songs[0] = &songs[0];
	fds._songs[1] = &songs[1];
	fds._songs[2] = &songs[2];
	fds._songs[3] = &songs[3];
	fds._songs[4] = &songs[4];
	
	finalString = parseString(&fds);
	return finalString;
	}
 
 

int main() 
{
	  struct formDisplayString str;
    //char ch;
	char* transmittedString;	
	char* formString = "screen:1;time:2:15;battery:42;inkiya ke papa,s2,s3,s4,s5;currentlyplaying:Better;duration:4:15;playing:paused;cursorpos:1;#\n";
		SystemInit();
		UART0_Init(4800);
		UART3_Init(4800);
		
//		str._screen = 1;
//		str._battery = 42;
//		str._hour = 2;
//		str._min = 15;
//		str._songs[0] = "s1";
//		str._songs[1] = "s2";
//		str._songs[2] = "s3";
//		str._songs[3] = "s4";
//		str._songs[4] = "s5";
//		str._currentlyPlaying = "s1";
//	  str._durationMin = 4;
//	  str._durationSec = 15;
		
		//transmittedString = param_calc(1, 45, {"Song 1", "Song 2", "Song 3", "Song 4"}, "Song 2", 4, 43, 10, 32);
    while(1)
    {
			//if(UART0_RxChar()){
				//UART0_TxString(transmittedString);
				UART3_TxString(formString);
			 //UART0_TxString(parseString(&str));
       //UART3_TxString(parseString(&str));
			//}
			 DELAY_ms(1000);
    }
    
    
}

