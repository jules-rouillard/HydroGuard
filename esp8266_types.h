/*
  C Library for ESP8266 Wifi module with PIC microcontrollers
  Copyright (C) 2020 Jose Guerra <joseguerracarmenate@gmail.com> 
  
  This file is part of "C library for ESP8266 Wifi module with PIC microcontrollers".
  
  "C library for ESP8266 Wifi module with PIC microcontrollers" 
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
 * @file  esp8266_types.h
 * @author Jose Guerra Carmenate
 *
 * Created on March 28, 2020, 2:35 AM
 */

#ifndef _ESP8266_TYPES_H
#define	_ESP8266_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "ip_address.h"
#include "mac_address.h"

#define SSID_LENGTH_MAX 20    ///< Ma'xima cantidad de caracteres que puede tener el ssid
#define PASSWORD_LENGTH_MAX 20///< Ma'xima cantidad de caracteres que puede tener la contasen~a

/**
 * @brief Definicio'n de los modos de operacio'n Wifi del mo'dulo ESP8266.
 * 
 * Los valores de este enum definen cada uno de los posibles modos de operacio'n
 * del mo'dulo ESP8266. 
 * 
 * @note El valor `WIFI_MODE_UNKNOWN` no debe ser utilizado con la rutina
 *  \ref ESP8266_SetWifiMode().
 * 
 */
typedef enum{
  WIFI_MODE_STATION             = 0x01, ///< Modo Estacio'n (Station mode) activo
  WIFI_MODE_SOFTAP              = 0x02, ///< Modo SoftAP activo
  WIFI_MODE_SOFTAP_AND_STATION  = 0x03, ///< Modos SoftAP y Estacio'n (Station) activos
  WIFI_MODE_UNKNOWN             = 0x04, ///< ERROR Obteniendo el modo WIFI ( Este valor
                                        ///< sera' retornado por la funcio'n \ref ESP8266_GetWifiMode()
                                        ///< en caso de no poder determinar el modo de operacion)
} WIFI_MODE;


/**
 * @brief Definicio'n de los resultados ante un intento de conexio'n a un 
 * Punto de Acceso Wifi (Wifi Access Point).
 * 
 */
typedef enum{
  AP_CONN_OK                  = 0x00, ///< Intento de conexio'n con AP exitoso
  AP_CONN_CONNECTING_TIMEOUT  = 0x01, ///< Tiempo de espera de conexio'n excedido
  AP_CONN_WRONG_PASSWORD      = 0x02, ///< Contrasenna incorrecta
  AP_CONN_AP_NOT_FOUND        = 0x03, ///< AP no encontrado
  AP_CONN_CONNECT_FAIL        = 0x04, ///< Fallo de conexio'n
  AP_CONN_TIMEOUT             = 0x05, ///< Tiempo de espera de respuesta (del bus UART) excedido
                                      ///<  equivalente (pero no igual) a \ref ESP8266_RESPONSE_TIMEOUT.
                                      ///<  Este resultado tambie'n puede deberse a que el modo
                                      ///<  Estacio'n (Station) no este' activo.
} AP_CONN_RET;


typedef enum{
  LIST_AP_ECN = 0x01,         ///< Show Secure protocol
  LIST_AP_SSID = 0x02,        ///< SSID of AP
  LIST_AP_RSSI = 0x04,        ///< RSSI of AP
  LIST_AP_MAC = 0x08,         ///< MAC Address of AP
  LIST_AP_CHANNEL = 0x10,     ///< channel
  LIST_AP_FREQ_OFFSET = 0x20, ///< Frequency offset of AP (KHz)
  LIST_AP_FREQ_CALIB = 0x40,  ///< calibration for frequency offset
} LIST_AP_CFG;

/**
 * @brief Define los tipos de seguridad para redes Wifi.
 * 
 * Este enum contiene las definiciones de los protocolos
 * de seguridad para redes Wifi que son soportados por el
 * mo'dulo ESP8266.
 */
typedef enum{
  AP_ECN_OPEN         = 0x00, ///< OPEN Network (Sin contrasenna)
  AP_ECN_WEP          = 0x01, ///< WEP security 
  AP_ECN_WPA_PSK      = 0x02, ///< WPA security 
  AP_ECN_WPA2_PSK     = 0x03, ///< WPA2 security (Alta seguridad)
  AP_ECN_WPA_WPA2_PSK = 0x04, ///< WPA, WPA2 security
} AP_ECN;

/**
 * @brief Protocolos de transporte disponibles para las conexiones.
 * 
 * Este enum define los protocolos de comunicacio'n soportados por el 
 * mo'dulo ESP8266.
 */
typedef enum{
  TRANSPORT_PROTOCOL_TCP,   ///< TCP (Transmission Control Protocol)
  TRANSPORT_PROTOCOL_UDP,   ///< UDP (User Datagram Protocol)
  TRANSPORT_PROTOCOL_SSL,   ///< SSL (Secure Socket Layer)
} TRANSPORT_PROTOCOL;


typedef struct {
  bool hasData:1;
  char channel;
  char *msg;
} wifi_message_t;


typedef struct{
  char channel;
  bool connected:1;
} wifi_connection_t;

/**
 * @brief Para'metros para la red wifi creada con el modo SoftAP.
 * 
 * Esta estructura (`struct`) permite almacenar todos los para'metros
 * necesarios para la configuracion del AP creado por el mo'dulo en
 * modo SoftAP.
 * 
 * \b Ejemplo
 * <code>
 * wifi_setting_t softAp = { 
 *        "My WiFi",            // wifi ssid  
 *        "password1234",       // wifi password
 *        5,                    // wifi channel 
 *        AP_ECN_WPA2_PSK,      // security
 *        4,                    // max connections
 *        false };              // hidde ssid
 * 
 * // configurar modo SoftAP
 * ESP8266_SetSoftApConfiguration( &softAp );
 * </code>
 */
typedef struct{
  char ssid[SSID_LENGTH_MAX];               ///< SSID de la Wifi.
  char pwd[PASSWORD_LENGTH_MAX];            ///< Password de la Wifi.
  uint8_t wifi_channel;                     ///< Canal wifi a utilizar.
  AP_ECN ecn;                               ///< Protocolo de seguridad.
  uint8_t max_stations:3;                   ///< Ma'xima cantidad de estaciones.
                                            ///< conectadas al ESP8266 en modo SoftAP.
  uint8_t ssid_hidden:1;                    ///< Ocultar SSID:
                                            ///<   - \b 0: broadcast ssid 
                                            ///<   - \b 1: do not broadcast
} wifi_setting_t;

/**
 * @brief Para'metros para configurar el modo SoftAP del ESP8266
 * 
 */
typedef struct{
  wifi_setting_t *wifi;                     ///< Configuracio'n de red wifi creada con el modo SoftAP
  bool dhcp_enable;                         ///< Habiliar DHCP del modo SoftAP: 
                                            ///<    - \b true: Habilita
                                            ///<    - \b false: Deshabilita
  
  uint16_t dhcp_lease_time;                 ///< DHCP lease time
  ipv4_address_t startIP;                   ///< Valor inicial del rango ip para DHCP
  ipv4_address_t endIP;                     ///< Valor final del rango ip para DHCP
  mac_address_t mac;
} softAp_setting_t;

/**
 * @brief Para'metros para configurar el modo Station del ESP8266
 */
typedef struct{
  ipv4_address_t ip;  ///< Direccio'n IP del dispositivo
  mac_address_t mac;  ///< Direccio'n MAC del dispositivo
  bool dhcp_enable;   ///< Habilitar obtencion de IP por DHCP
} station_setting_t;

/**
 * @brief Esta estructura permite definir un dispositivo (estacio'n)
 * conectada al mo'dulo ESP8266 en modo SoftAP.
 */
typedef struct{
  ipv4_address_t ip;  ///< Direccio'n IP del dispositivo
  mac_address_t mac;  ///< Direccio'n MAC del dispositivo
} station_t;

/**
 * @brief Conjunto de respuestas retornadas por varias de las rutinas
 * pertenecientes a este mo'dulo.
 * 
 * Este enum agrupa las respuestas proporcionadas por los comandos AT y
 * las rutinas implementadas en este controlador.
 */
typedef enum{
  ESP8266_RESPONSE_OK        = 0x00,  ///< \b Mensaje: "OK" <br>
                                      ///< \b Motivo: Operacio'n Exitosa
          
  ESP8266_RESPONSE_READY,             ///< \b Mensaje: "ready" <br>
                                      ///< \b Motivo: Reinicio del mo'dulo
          
  ESP8266_RESPONSE_FAIL,              ///< \b Mensaje: "FAIL" <br>
                                      ///< \b Motivo: Fallo al realizar la accio'n
          
  ESP8266_RESPONSE_NOCHANGE,          ///< "NOCHANGE"
          
  ESP8266_RESPONSE_LINKED,            ///< \b Mensaje: "LINKED"<br>
                                      ///< \b Motivo: Conectado
          
  ESP8266_RESPONSE_UNLINK,            ///< \b Mensaje: "UNLINK"
          
  ESP8266_RESPONSE_ERROR,             ///< \b Mensaje: "ERROR"<br>
                                      ///< \b Motivo: Operacion Incorrecta.
          
  ESP8266_RESPONSE_QUANTITY,          ///< Cantidad de elementos validos (no utilizar)
  ESP8266_RESPONSE_TIMEOUT,           ///< Tiempo limite superado
} ESP8266_RESPONSE;

/**
 * @brief Definiciones referidas al estado de las conexiones.
 * 
 * Estos valores son retornados por la funcio'n \ref ESP8266_OpenConnection()
 */
typedef enum{
  LINK_STATUS_CONNECTED,            ///< Conexio'n establecida
  LINK_STATUS_CLOSED,               ///< Conexio'n terminada
  LINK_STATUS_ALREADY_CONNECTED,    ///< Conexio'n en uso
  LINK_STATUS_ERROR,                ///< Error en la conexio'n
} LINK_STATUS;


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ESP8266_TYPES_H */