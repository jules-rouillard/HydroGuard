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
/**
 * @file  mac_address.c
 * @author Jose' Guerra Carmenate
 * 
 * @email joseguerracarmenate@gmail.com
 *
 * Created on April 18, 2020, 10:34 PM
 */

#include "mac_address.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef isdigit
#undef isdigit
#endif

#define isdigit(x) ('0' <= (x) && (x) <= '9')

mac_address_t str2mac( const char *str ){
  mac_address_t ret;
  if( str == NULL )
    return ret;
  
  while( *str && !isxdigit(*str) ) // quitar basura inicial
    str++;
  
  uint8_t i = 0, v = 0;
  
  while( true ){
    if( isxdigit(*str) ){
      v <<= 4; // v *= 16
      if( isdigit(*str) ){
        v += (*str) - '0';
      }
      else{
        v += tolower(*str) - 'a' + 10;
      }
    }
    else if( *str == ':' ){
      ret.block[i] = v;
      v = 0;
      i++;      
    }
    else{
      ret.block[i] = v;
      break;
    }
    str++;
  }
  
  return ret;
}

char* mac2str( mac_address_t *mac,  char *str ){
  sprintf( str, "%02x:%02x:%02x:%02x:%02x:%02x", mac->n1,mac->n2,mac->n3,mac->n4,mac->n5,mac->n6 );
  return str;
}