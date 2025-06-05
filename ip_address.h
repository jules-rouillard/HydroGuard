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
 * @file ip_address.h
 * 
 * @author Jose' Guerra Carmenate
 *
 * @brief adasda
 * 
 * Created on April 10, 2020, 2:56 PM
 */

#ifndef _IP_ADDRESS_H
#define	_IP_ADDRESS_H
#include <stdint.h>

#define NO_IP (ipv4_address_t){0x00000000}


/**
 * @brief Direccio'n IPv4
 * 
 * Este tipo de dato define una direccio'n IPv4 (almacena los 4 bytes).
 * Los bytes se almacenan de forma tal que las representaciones seri'an:
 *  - `values[0].values[1].values[2].values[3]`
 *  - `n1.n2.n3.n4`
 */
typedef union{
  
    uint8_t values[4];      ///< Permite recorrer secuencialmente los bytes
                            ///< de la direccio'n IP
    struct{ 
      uint8_t n1,           ///< Primer byte de la direccio'n IP (x._._._)
              n2,           ///< Segundo byte de la direccio'n IP (_.x._._)
              n3,           ///< Tercer byte de la direccio'n IP (_._.x._)
              n4;           ///< Cuarto byte de la direccio'n IP (_._._.x)
    };
    uint32_t all;           ///< Permite asignar la direccio'n IP en un solo
                            ///< valor. U'til para realizar comparaciones y 
                            ///< asignaciones.

} ipv4_address_t;



#ifdef	__cplusplus
extern "C" {
#endif

  /**
   * @brief Convierte un string a ipv4_address_t.
   * 
   * Esta funcio'n recibe un string que represente una direccio'n IPv4 y
   * retorna la direccio'n como ipv4_address_t. El string puede contener
   * caracteres invalidos antes y/o despues de la direccio'n IP. Por ejemplo
   * los string `"my ip: 10.2.73.1"`, `"ip: <192.168.1.24>"` y `"8.8.8.8"` son 
   * resueltos satisfactoriamente. 
   * Al contrario `"10.2.3."`, `"10 23.3.20"` y `"ip: 10.3d.1.1"` no son 
   * resueltos.
   * 
   * @param[in] str String con la direccio'n IP.
   * 
   * @return ipv4_address_t con la direccio'n IP presente en `str` o con 
   * valor todo cero si la direccio'n en `str` no es valida.
   * 
   * \b Ejemplo:
   * @code
   * char a[] = "10.2.23.62";
   * 
   * ipv4_address_t ip = str2ipv4( a );
   * @endcode
   * 
   */
  ipv4_address_t str2ipv4( const char *str );
  
  /**
   * @brief Convierte una variable ipv4_address_t en string.
   * 
   * Esta funcio'n permite obtener a partir de una variable
   * ipv4_address_t la representacio'n en un string de la misma. 
   * 
   * @param[in] ip Puntero al valor IPv4 a convertir.
   * @param[out] str String donde se almacenara' la direccio'n generada.
   * 
   * @return Puntero a `str`.
   * 
   * \b Ejemplo:
   * @code
   * ipv4_address_t my_ip= {
   *   .n1 = 10,
   *   .n2 = 2,
   *   .n3 = 0,
   *   .n4 = 5,
   * };
   * char s[20];
   * ip2str( &my_ip, s );
   * // valor de s: "10.2.0.5"
   * @endcode
   */
  char* ip2str( ipv4_address_t *ip, char *str );


#ifdef	__cplusplus
}
#endif

#endif	/* IP_ADDRESS_H */