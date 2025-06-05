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
 * @file  mac_address.h
 * @author Jose' Guerra Carmenate
 * 
 * @email joseguerracarmenate@gmail.com
 *
 * Created on April 18, 2020, 10:34 PM
 */

#ifndef _MAC_ADDRESS_H
#define	_MAC_ADDRESS_H

#include <stdint.h>

#define MAC_STRING_LENGTH 17

/**
 * @brief Define una direccio'n MAC
 * Este tipo de dato define una direccio'n MAC (almacena los 6 bytes)
 * 
 * Los bytes se almacenan de forma tal que las representaciones seri'an:
 *  - n1:n2:n3:n4:n5:n6
 *  - block[0]:block[1]:block[2]:block[3]:block[4]:block[5]
 * 
 */
typedef union{
    uint8_t block[6];               ///< Permite recorrer secuencialmente los
                                    ///< bytes de la direccio'n MAC
    struct{
      uint8_t n1,                   ///< Primer byte de la direccio'n MAC (xx:__:__:__:__:__)
              n2,                   ///< Segundo byte de la direccio'n MAC (__:xx:__:__:__:__)
              n3,                   ///< Tercer byte de la direccio'n MAC (__:__:xx:__:__:__)
              n4,                   ///< Cuarto byte de la direccio'n MAC (__:__:__:xx:__:__)
              n5,                   ///< Quinto byte de la direccio'n MAC (__:__:__:__:xx:__)
              n6;                   ///< Sexto byte de la direccio'n MAC (__:__:__:__:__:xx)
    };
    struct{
      uint32_t low_4bytes;          ///< Permite acceder a los primero 4 bytes
      uint16_t high_2bytes;         ///< Permite acceder a los u'ltimos 2 bytes
    };
} mac_address_t;


#ifdef	__cplusplus
extern "C" {
#endif


  /**
   * @brief Convierte un string en un mac_address_t.
   * 
   * Esta funcio'n recibe un string que represente una direccio'n MAC y
   * retorna la direccio'n como un mac_address_t. El string puede contener
   * caracteres inva'lidos antes y/o despues de la direccio'n MAC. Por ejemplo
   * los string `"my mac: 12:23:43:61:f3:d1"`, `"ip: 'fa:3d:60:62:12:24'"` y 
   * `"ff:ff:ff:ee:ee:ee"` son resueltos satisfactoriamente.
   * Al contrario `"12:23:43:61:f3:"`, `"12 23:a3:61:f3:d1"` y 
   * `"ip: 12:2343:61:f3:d1"` no son resueltos.
   * 
   * @param[in] str String con la direccio'n MAC.
   * 
   * @return mac_address_t con la direccio'n identificada en el `str`.
   * 
   * \b Ejemplo:
   * @code
   * char s_mac = "12:23:43:61:f3:d1";
   * 
   * mac_address_t mac = str2mac(s_mac);
   * 
   * @endcode
   * 
   */

  mac_address_t str2mac( const char *str );

  
  /**
   * @brief Convierte un mac_address_t en string
   * 
   * Esta funcio'n permite obtener a partir de una variable
   * ipv4_address_t la representacio'n en un string de la misma. 
   * 
   * @param[in] mac Puntero al `mac_address_t` a convertir.
   * 
   * @param[out] str String para almacenar la direccio'n MAC

   *    * @return Puntero a `str`.
   * 
   * \b Ejemplo:
   * @code
   * mac_address_t my_mac = {
   *   .n1 = 0xfe,
   *   .n2 = 0xAA,
   *   .n3 = 0x27,
   *   .n4 = 0x32,
   *   .n5 = 0xff,
   *   .n6 = 0xee,
   * };
   * char s[45];
   * mac2str( &my_mac, s );
   * // valor de s: "fe:aa:27:32:ff:ee"
   * @endcode
   */
  char* mac2str( mac_address_t *mac,  char *str );



#ifdef	__cplusplus
}
#endif

#endif	/* MAC_ADDRESS_H */