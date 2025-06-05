/*
  Copyright (C) 2020 Jose Guerra <joseguerracarmenate@gmail.com>
  
  This file is part of "C library for ESP8266 Wifi module with PIC microcontroller".
  
  "C library for ESP8266 Wifi module with PIC microcontroller" 
  is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
/* 
 * @file   ip_address.c
 * @author: jose
 *
 * @brief asdsa
 * Created on April 10, 2020, 2:56 PM
 */
#include "ip_address.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#ifdef isdigit
#undef isdigit
#endif

#define isdigit(x) ('0' <= (x) && (x) <= '9')


ipv4_address_t str2ipv4( const char *str ){
  ipv4_address_t ip;
  while( *str && !isdigit(*str) ) // quitar basura inicial
    str++;
  uint8_t i = 0, v = 0;
  
  while( true ){
    if( isdigit(*str) ){  // digit
      v *= 10;
      v += (*str) - '0';
    }
    else if( *str == '.' ){ // dot
      ip.values[i] = v;
      v = 0;
      i++;
    }
    else{                   // wrong char
      if( i != 3 )
        ip.all = 0x00;      // invalid ip
      else
        ip.values[i] = v;
      break;
    }
    str++;
  }
  
  return ip;
}

char* ip2str( ipv4_address_t *ip, char *str ){
  sprintf( str, "%d.%d.%d.%d", ip->values[0],ip->values[1],ip->values[2],ip->values[3] );
  return str;
}