/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: Jules Rouillard
 *  * Base of  Jose Guerra Carmenateµ
 * https://github.com/joseguerra3000/esp8266-for-PIC/tree/master
 * Comments:
 * Revision history: 
 */
#ifndef _ESP8266_H
#define	_ESP8266_H

#include <stdint.h>
#include <stdbool.h>

#include "esp8266_types.h"

/**
 * @brief
 * Comandos AT disponibles para el modulo ESP8266
 */
typedef enum{
  
  CMD_AT, ///< It's used to test the setup function of your wireless WiFi module.
          
  CMD_RST, ///< It's used to restart the module.
          
  /*
    * 
    * 
    * Response:
    * @code
    * |AT version info| information about AT version
    * |SDK version info| information about SDK version
    * |compile time| time of the bin was compiled
    * 
    * OK
    * @endcode
    */
  CMD_GMR, ///< Is used to check the version of AT commands and SDK
  
  CMD_GSLP, ///< Used to invoke the deep-sleep mode of the module.
  
  CMD_ATE, ///< This command ATE is an AT trigger command echo

  CMD_RESTORE, ///< This command is used to reset all parameters saved in flash, restore the factory default settings of the module

  CMD_UART_CUR, ///< This command sets the current UART configuration; it does not write to the flash. Hence there is no change in the default baudrate.

  CMD_UART_DEF, ///< This command sets the UART configuration and save it to flash. 
          
  CMD_SLEEP, ///< This command sets ESP8266 sleep mode. It can only be used in station mode, default to be modem-sleep mode.

  CMD_RFPOWER, ///< This command sets the maximum value of ESP8266 RF TX power, it is not precise.     

  CMD_RFVDD, ///< This command sets ESP8266 RF TX power according to VDD33.

  CMD_CWMODE_CUR,

  CMD_CWMODE_DEF,

  CMD_CWJAP_CUR, ///< Connect to AP, won't save to Flash

  CMD_CWJAP_DEF, ///< Connect to AP and save AP info to flash.
 
  CMD_CWLAPOPT, ///< This command is to set the configuration for command AT+CWLAP

  CMD_CWLAP, ///<    Lists available APs

  CMD_CWQAP, ///< Disconnect from AP

  CMD_CWSAP_CUR, ///< Set configuration of softAP mode, won?t save to Flash

  CMD_CWSAP_DEF, ///<  Set configuration of softAP mode, save to Flash

  CMD_CWLIF, ///<  This command is used to get the IP of stations that are connected to ESP8266 softAP.

  CMD_CWDHCP_CUR, ///<  Enable/Disable DHCP, won?t save to flash

  CMD_CWDHCP_DEF,///< Enable/Disable DHCP and save to Flash

  CMD_CWDHCPS_CUR, ///< Set the IP address allocated by ESP8266 soft-AP DHCP, cannot save to flash
  
  CMD_CWDHCPS_DEF, ///< Set the IP address allocated by ESP8266 soft-AP DHCP, save to flash

  CMD_CWAUTOCONN, ///< Auto connect to AP or not

  CMD_CIPSTAMAC_CUR,  ///< Set MAC address of station

  CMD_CIPSTAMAC_DEF, ///< Set MAC address of station, save as default

  CMD_CIPAPMAC_CUR, ///< Set MAC address of softAP

  CMD_CIPAPMAC_DEF, ///< Set MAC address of softAP and save as default

  CMD_CIPSTA_CUR,  ///< Set IP address of station

  CMD_CIPSTA_DEF,  ///< Set IP address of station and save as default

  CMD_CIPAP_CUR,   ///< Set IP address of softAP.

  CMD_CIPAP_DEF,  ///< Set IP address of softAP.

  CMD_CWSTARTSMART,

  CMD_CWSTOPSMART,

  CMD_CWSTARTDISCOVER,

  CMD_CWSTOPDISCOVER,

  CMD_WPS, ///< Set WPS function

  CMD_MDNS, ///< Set MDNS function

  CMD_CIPSTATUS, ///< Check network connection status

  CMD_CIPDOMAIN, ///<  DNS function

  CMD_CIPSTART,

  CMD_CIPSSLSIZE,

  CMD_CIPSEND,

  CMD_CIPSENDEX,

  CMD_CIPSENDBUF,

  CMD_CIPBUFSTATUS,

  CMD_CIPCHECKSEQ,

  CMD_CIPBUFRESET,

  CMD_CIPCLOSE,

  CMD_CIFSR,

  CMD_CIPMUX,         ///< Enable multiple connections

  CMD_CIPSERVER,      ///< Configure as TCP server

  CMD_CIPMODE,        ///< Set transfer mode

  CMD_SAVETRANSLINK,  ///< Save transparent transmission link to Flash

  CMD_CIPSTO,         ///< Set TCP server timeout

  CMD_PING,           ///< Function Ping

  CMD_CIUPDATE,       ///< Update through network

  CMD_CIPDINFO,       ///< Show remote IP and port with "+IPD"

} ESP8266_CMD;


#ifdef	__cplusplus
extern "C" {
#endif
  
  ////////////////// Basic Routines //////////////
  
/**
 * @brief This routine initializes the ESP8266 module
 * 
 * This routine initializes the ESP8266 module for the indicated WiFi mode.
 * 
 * @param[in] mode Allows setting the operating mode of the ESP8266 module.
 * See \ref WIFI_MODE for more details.
 * 
 * @return An unsigned 8-bit integer (`uint8_t`) indicating the result
 * of the operation:
 * -
 */
  uint8_t ESP8266_Initialize( WIFI_MODE mode );
  
  
  uint8_t ESP8266_SetSoftApSettings( softAp_setting_t *ap_config );
  
  uint8_t ESP8266_SetStationSettings( station_setting_t *stat_config );
  
/**
 * @brief Checks the communication between the MCU and the ESP8266 module.
 * 
 * To check the communication, it sends the "AT" command and verifies that the
 * response received is "OK". If no response is received or it is different,
 * it returns \b false.
 * 
 * @return
 *    - \b true: "OK" received
 *    - \b false: "OK" not received
 */

  bool ESP8266_CheckCommunication(void);                                        // implemented

  /**
 * @brief Allows obtaining a string with the meaning of a value from the
 * `ESP8266_RESPONSE` enum used as a parameter.
 * 
 * @param[in] code A value from the \ref ESP8266_RESPONSE enum.
 * 
 * @return A `const char*` that points to a string with the meaning of the code
 * passed as a parameter.
 * 
 * \b Example
 * @code
 * printf( ESP8266_CodeToString( ESP8266_SetWifiMode(WIFI_MODE_SOFTAP) ) );
 * @endcode
 */
  const char* ESP8266_CodeToString( ESP8266_RESPONSE code );                    // implemented
  
/**
 * @brief Restarts the ESP8266 module.
 * 
 * To restart the module, the AT+RST command is sent and the reception
 * of the 'ready' message is verified.
 * 
 * @return 
 *  - \b true: successfully restarted
 *  - \b false: response not received
 */
  bool ESP8266_Reset(void);                                                     // implemented
  
  ///////////   WIFI Related Routines  ////////////////
  
/**
 * @brief Allows setting the operating mode of the ESP8266 module as:
 * Station, SoftAP, or both simultaneously.
 * 
 * @param[in] mode Operating mode. See enum \ref WIFI_MODE for more details.
 * @return 
 *    - ESP8266_RESPONSE_OK: Operation successful;
 *    - ESP8266_RESPONSE_TIMEOUT: Response not received
 */
  ESP8266_RESPONSE ESP8266_SetWifiMode(WIFI_MODE mode);                         // implemented
  
  /**
   * @brief Permite conocer el modo en que esta' operando el mo'dulo.
   * 
   * @return Un valor del enum \ref WIFI_MODE indicando el modo de 
   * operacio'n actual. `WIFI_MODE_UNKNOWN` sera' retornado en caso de que no
   * se reciba respuesta.
   */
  WIFI_MODE ESP8266_GetWifiMode(void);                                          // implemented
  
  /**
   * @brief Esta rutina intenta conectar al mo'dulo ESP8266 a una red wifi.
   * 
   * Para esto se especifica el ssid, la contrasenna y el bssid indicados.
   * En caso de no ser necesario el bssid se utilizara' el valor NULL. 
   * 
   * @param[in] ssid SSID del AP wifi al que se pretende conectar
   * @param[in] pwd Contrasenna de la red wifi.
   * @param[in] bssid Direccio'n MAC del AP wifi. Si no es necesaria utilizar el
   * valor NULL.
   * 
   * @pre El modulo ESP8266 tiene que tener activo el modo estacio'n (modo
   * `WIFI_MODE_STATION` o `WIFI_MODE_SOFTAP_AND_STATION`)
   * 
   * @return Resultado de la operacio'n. Ver enum \ref AP_CONN_RET en el archivo 
   * esp8266_types.h para ma's detalles.
   */
  AP_CONN_RET ESP8266_ConnectToAP( const char* ssid, const char* pwd, const char* bssid ); // implemented (station)
    
  /*
   * @todo uint8_t ESP8266_SetConfigurationForListingAP( bool sort, uint8_t what_show );
   */
  
  // adasd
  
  /*
   * @todo uint8_t ESP8266_ListAvailableAPs(char* ssid, mac_address_t, int8_t channel);  //incomplete (station)
  */
  
  //asd 
  
  /**
   * @brief Desconecta el mo'dulo operando como cliente del AP al que esta' conectado.
   * 
   * @pre El mo'dulo debe estar en modo `WIFI_STATION` o 
   * `WIFI_MODE_SOFTAP_AND_STATION` y estar conectado a un
   * Access Point.
   * 
   * @return  
   *  - ESP8266_RESPONSE_OK: En caso exitoso
   *  - ESP8266_RESPONSE_TIMEOUT: Respuesta no recibida
   */
  uint8_t ESP8266_DisconnectFromAP(void);                                       // implemented (station)
  
  
  /**
   * @brief Permite obtener la configuracio'n actual de la wifi del modo
   * SoftAP en el mo'dulo ESP8266.
   * 
   * @param[out] cfg Direccio'n de memoria del `softAP_setting_t` en el que
   * se almacenara' la configuracio'n.
   * 
   * @pre El mo'dulo ESP8266 tiene que tener el modo softAp activo (Modo
   * `WIFI_MODE_SOFTAP` o `WIFI_MODE_SOFTAP_AND_STATION`).
   * 
   * @return Un valor del enum \ref ESP8266_RESPONSE 
   * (Ver \ref ESP8266_RESPONSE para mas detalles) 
   */
  ESP8266_RESPONSE ESP8266_GetSoftApWifiSettings( wifi_setting_t *cfg );              // implemented (SoftAP)
  
  /**
   * @brief Esta rutina establece la configuracio'n de la wifi mo'dulo ESP8266
   * para su modo SoftAp.
   * 
   * @param[in] cfg Direccio'n de memoria de la configuracio'n para el modo 
   * SoftAp. Revisar la estructura \ref wifi_setting_t para ma's detalles.
   * 
   * @pre El mo'dulo ESP8266 tiene que tener el modo softAp activo (Modo
   * `WIFI_MODE_SOFTAP` o `WIFI_MODE_SOFTAP_AND_STATION`).
   * 
   * @note La contrasen~a tiene que tener 8 o ma's caracteres.
   * 
   * @return Un valor del enum \ref ESP8266_Response.
   */
  ESP8266_RESPONSE ESP8266_SetSoftApWifiSettings( wifi_setting_t *cfg );     // implemented (SoftAP)
  
  
  /**
   * @brief Permite obtener las estaciones conectadas al mo'dulo ESP8266 operando
   * en modo SoftAP.
   * 
   * Si el para'metro `station_number` es 0 o menor que cero simplemente se retorna
   * la cantidad de estaciones almacenadas. En caso contrario en `station`
   * se guardara'n los datos referentes a la estacio'n nu'mero `station_number`.
   * 
   * @param[in] station_number el nu'mero de orden de la estacio'n conectada que se 
   * desea almacenar en `station`. Debe estar en el reango: [0-3]. 
   * @param[out] station Puntero a la estuctura tipo `station_t` en la que se
   * almacenara' la informacio'n. En caso de que el `station_number` no sea
   * de una estacio'n valida se obtendra' ip: 0.0.0.0 y mac: 00:00:00:00:00:00 
   * 
   * @note Si `station_number` es menor que cero la funcio'n no
   * almacenara' informacio'n.
   * 
   * @return 
   *   - >0: La cantidad de estaciones disponibles o el nu'mero de la estacio'n almacenada.
   *   - <0: Error en la comunicacio'n con el mo'dulo ESP8266
   *   - 0:Informacio'n de la estacio'n almacenada en `station`.
   * 
   * \b Ejemplo
   * <code>
   * station_t stat; //contiene las direcciones ip y mac
   * ESP8266_GetConnectedStation(0, &stat); // obtener la estacio'n #1 (estacio'n 0)
   * </code>
   * 
   *         
   */
  int8_t ESP8266_GetConnectedStation( int8_t station_number, station_t *station ); // incompleta (SoftAP)
  
  /// @TODO: uint8_t ESP8266_IsDHCPEnable( void );
  
  /**
   * @brief Esta rutina permite activar/desactivar el uso de DHCP.
   * 
   * La rutina permite activar/desactivar el uso de DHCP para los modos
   * de operacio'n de forma independiente o en conjunto. Para esto se utiiliza
   * el comando `AT+CWDHCP_CUR`.
   * 
   * @param[in] mode_to_set Define el modo de operacio'n (Station o SoftAp) al
   * que se le activara' el DHCP.
   *  
   * @param[in] en Defiine la configuracio'n del DHCP:
   *  - \b true: Activar DHCP
   *  - \b false: Desactivar DHCP
   * @return 
   */
  ESP8266_RESPONSE ESP8266_EnableDHCP( WIFI_MODE mode_to_set, bool en );                 // implemented (Ambos)
  
  /**
   * @brief Permite obtener el rango de direcciones IP asi' como el `lease time`
   * de DHCP del modo SoftAP.
   * 
   * @param[out] startIP Direccio'n de memoria del inicio del rango IP que 
   * otorga el DHCP del mo'dulo en modo SoftAP.
   * 
   * @param[out] endIP Direccio'n de memoria del final del rango IP que 
   * otorga el DHCP del mo'dulo en modo SoftAP.
   * 
   * @return 
   *  - \b >0: Lease time en minutos
   *  - \b <0: Error ocurrido. El Co'digo de error debe ser determinado 
   * utilizando el valor positivo.
   * 
   * \b Ejemplo
   * <code>
   * int lease = ESP8266_GetSoftApIpRange( &sIp, &eIp );
   * 
   * if( lease < 0 ){ // error
   *    // handle error with -lease
   * }
   * </code>
   */
  int16_t ESP8266_GetSoftApIpRange(ipv4_address_t* startIP, ipv4_address_t* endIP); // implemented
  
  /**
   * @brief Permite especificar el rango de direcciones IP que el mo'dulo (operando en
   * SoftAP) puede ofrecer, asi' como el lease time.
   * 
   * @param[in] startIP Direccio'n de memoria del ipv4_address_t donde se
   * almacenara' la IP inicial del rango a establecer para el DHCP.
   * 
   * @param[in] endIP Direccio'n de memoria del ipv4_address_t donde se 
   * almacenara' la IP final del rango a establecer para el DHCP.
   * 
   * @param[in] lease_time
   * 
   * @return Ver enum \ref ESP8266_RESPONSE.
   * 
   * \b Ejemplo
   * @code
   * ipv4_address_t ip_s = {
   *  .n1 = 192,
   *  .n2 = 168,
   *  .n3 = 0,
   *  .n4 = 2,
   * };
   * ipv4_address_t ip_e = {
   *  .n1 = 192,
   *  .n2 = 168,
   *  .n3 = 0,
   *  .n4 = 10,
   * };
   * if ( ESP8266_SetSoftApIpRange( &ip_s, &ip_e, 20 ) != ESP8266_RESPONSE_OK ){
   *    // handel error.
   * }
   * @endcode
   * 
   */
  ESP8266_RESPONSE ESP8266_SetSoftApIpRange(ipv4_address_t* startIP, ipv4_address_t* endIP, int16_t lease_time); // implemented 
  
  /**
   * @brief Esta rutina permite activar/desactivar la autoconexio'n.
   * 
   * Esta funcio'n configura la autoconexio'n del modo Station (Estacio'n) del
   * mo'dulo ESP8266 a la red wifi. Si esta es activada cuando el modulo es 
   * energizado automaticamente intenta conectarse a la red wifi establecida.
   * 
   * @param[in] auto_connect Booleano que indica si se activa o no el modo de
   * autoconexio'n:
   *    - \b true: Activar autoconexio'n.
   *    - \b false: Desactivar autoconexio'n.
   * 
   * @return Un valor del enum \ref ESP8266_RESPONSE:
   *    - \ref ESP8266_RESPONSE_OK: Operacio'n realizada con exito.
   *    - \ref ESP8266_RESPONSE_ERROR: Error en la operacio'n
   *    - \ref ESP8266_RESPONSE_TIMEOUT: Tiempo de espera por respuesta excedido
   */
  ESP8266_RESPONSE ESP8266_AutoConnect( bool auto_connect );                    // implemented
  
  /**
   * @brief Permite obtener la direccio'n MAC del modo estacio'n del mo'dulo ESP8266.
   * 
   * @param[out] mac Direccion de memoria del `mac_address_t` donde se
   * almacenara' la direccio'n MAC del modo estacio'n.
   * 
   * @return Ver enum ESP8266_RESPONSE.
   * 
   * \b Ejemplo:
   * @code
   * mac_address_t my_mac;
   * ESP8266_GetStationMacAddress( &mac );
   * @endcode
   */
  ESP8266_RESPONSE ESP8266_GetStationMacAddress( mac_address_t* mac);           // implemented

  /**
   * @brief Permite establecer la MAC del dispositivo para el modo Station.
   * 
   * @param[in] mac Direccio'n de memoria del `mac_address_t` donde esta'
   * el valor MAC a utilizar.
   * 
   * @return Ver enum \ref ESP8266_RESPONSE en el archivo esp8266_types.h
   */
  ESP8266_RESPONSE ESP8266_SetStationMacAddress( mac_address_t* mac );          // implemented
  
  /**
   * @brief Permite obtener la MAC del mo'dulo ESP8266 para el modo SoftAP.
   * 
   * @param[out] ap_mac Direccio'n de memoria del `mac_address_t` donde se 
   * almacenara' la MAC.
   * 
   * @return Ver enum \ref ESP8266_RESPONSE en el archivo esp8266_types.h
   */
  ESP8266_RESPONSE ESP8266_GetSoftApMacAddress( mac_address_t* ap_mac );        // implemented

  /**
   * @brief Permite establecer la MAC del dispositivo para el modo SoftAP.
   * 
   * @param[in] mac Direccio'n de memoria del `mac_address_t` donde esta'
   * el valor MAC a utilizar.
   * 
   * @return Ver enum \ref ESP8266_RESPONSE en el archivo esp8266_types.h
   */
  ESP8266_RESPONSE ESP8266_SetSoftApMacAddress( mac_address_t* ap_mac );        // implemented
  
  /**
   * @brief Permite establecer un IP estatico para el modo Station del mo'dulo
   * ESP8266.
   * 
   * @param ip Direccio'n de memoria del `ipv4_address_t` con el IP a asignar 
   * al modo Station
   * 
   * @param gateway Direccio'n de memoria del `ipv4_address_t` con la puerta de enlace (en caso
   * de no ser necesario se puede utilizar el valor NULL)
   * 
   * @param mask Direccio'n de memoria del `ipv4_address_t` con la mascara de red (en caso
   * de no ser necesario se puede utilizar el valor NULL)
   * 
   * @pre El mo'dulo ESP8266 tiene que tener el modo Station activo y estar
   * conectado a una red wifi.
   * 
   * @return Ver enum \ref ESP8266_RESPONSE en el archivo esp8266_types.h
   */
  ESP8266_RESPONSE ESP8266_SetStationIP( ipv4_address_t *ip, ipv4_address_t* gateway, ipv4_address_t* mask); // implemented
  
  /**
   * @brief Permite obtener el IP del modo Station del mo'dulo ESP8266.
   * 
   * @param ip Direccio'n de memoria del `ipv4_address_t` donde se almacenara' el IP.
   * 
   * @pre El modo Station tiene que estar activo y el ESP8266 conectado
   * a una red wifi.
   * 
   * @return Ver enum \ref ESP8266_RESPONSE en el archivo esp8266_types.h
   */
  ESP8266_RESPONSE ESP8266_GetStationIP( ipv4_address_t *ip );                  // implemented
  
  /**
   * @brief Permite especificar la direccio'n IP del mo'dulo ESP8266 en
   * modo SoftAP. 
   * 
   * @param ip Direccio'n IP del mo'dulo ESP8266 en modo SoftAP
   * 
   * @param gateway Direccio'n IP de la puerta de enlace (puede tener el valor
   * NULL en caso de no ser necesaria)
   * 
   * @param mask Puntero a `ipv4_address_t` con la mascara de red (en caso 
   * de no ser necesario se puede utilizar el valor NULL)
   * 
   * @pre el modulo tiene que tener el modo SoftAP activo.
   * 
   * @return Ver enum ESP8266_RESPONSE en el archivo esp8266_types.h
   */
  ESP8266_RESPONSE ESP8266_SetSoftApIP( ipv4_address_t *ip, ipv4_address_t* gateway, ipv4_address_t* mask); // implemented

  /**
   * @brief Permite obtener la direccio'n IP del mo'dulo ESP8266 en
   * modo SoftAP. 
   * 
   * @param[out] ip puntero a `ipv4_address_t` donde se 
   * almacenara' la direccio'n IP del mo'dulo ESP8266 en modo SoftAP
   * 
   * @pre El modulo tiene que tener el modo SoftAP activo
   * 
   * @return Ver enum ESP8266_RESPONSE en el archivo esp8266_types.h
   */
  ESP8266_RESPONSE ESP8266_GetSoftApIP( ipv4_address_t *ip);                    // implemented
  
//  @todo: uint8_t ESP8266_SetWPS( bool enable );                                        // pending
  
//  @todo: uint8_t ESP8266_GetWPS( void );                                               // pending
  
//  uint8_t ESP8266_EnableMDNS( char* host_name, char* server_name, uint16_t port );// pending
  
//  uint8_t ESP8266_DisableMDNS(void);                                            // pending
  
  
//  uint8_t ESP8266_GetNetworkConnectionStatus(); // review this command: AT+CIPSTATUS
  
  // uint8_t ESP8266_SetDNS( char *domain_name );
  
  /**
   * @brief Establece una conexio'n (`link_id`) entre un servidor (`server`) y el mo'dulo ESP8266
   * utilizando el protocolo (`conn_type`) y puerto (`port`) especificados.
   * 
   * @param[in] link_id Entero en el rango [0-4] que especifica
   * la conexio'n a utilizar.
   * 
   * @param[in] conn_type Especifica que protocolo utilizar para la conexio'n.
   * Ver \ref TRANSPORT_PROTOCOL para ma's detalles.
   * 
   * @param[in] server String con la direccio'n del servidor.
   * Puede utilizarse una direccio'n IP o una url.
   * 
   * @param[in] port Puerto de escucha del servidor remoto.
   * 
   * @return Un valor del enum \ref LINK_STATUS con el estado de la conexio'n especificada
   * (Ver enum \ref LINK_STATUS en esp8266_types para ma's detalles):
   *    - LINK_STATUS_CONNECTED: Conexio'n establecida
   *    - LINK_STATUS_CLOSED: Conexio'n terminada
   *    - LINK_STATUS_ALREADY_CONNECTED: Conexio'n en uso
   *    - LINK_STATUS_ERROR: Error en la conexio'n
   */
  LINK_STATUS ESP8266_OpenConnection( int8_t link_id, TRANSPORT_PROTOCOL conn_type, const char *server, uint16_t port );
  
  /**
   * @brief Permite enviar datos mediante un enlace previamente establecido
   * 
   * @param[in] link_id Entero en el rango [0-4] que especifica
   * la conexio'n a utilizar.
   * @param[in] data Arreglo de bytes con las datos a enviar
   * @param[in] n Cantidad de bytes a enviar.
   * 
   * @return Un entero que indica el resultado de la operacio'n:
   *      - ESP8266_RESPONSE_OK: Datos enviados con exito
   *      - ESP8266_RESPONSE_ERROR: Error en el envio de datos
   * 
   * @pre La funcio'n \ref ESP8266_OpenConnection debe haber sido ejecutada
   * exitosamente.
   */
  uint8_t ESP8266_SendDataPack( int8_t link_id,  const uint8_t *data, uint16_t n );
  
  /**
   * @brief Comprueba la llegada de datos provenientes de otro dispositivo 
   * mediante alguna conexio'n previamente establecida.
   * 
   * Esta rutina espera un tiempo (`timeout`) por la llegada de un paquete
   * proveniente de otro dispositivo mediante una conexio'n previamente establecida.
   * Si no hay datos disponibles la funcio'n retornara' \b 0, en caso contrario
   * retorna la cantidad de bytes disponibles y `link_id` toma el valor de la
   * conexio'n empleada. 
   * 
   * @param[out] link_id Puntero a entero que especifica la conexio'n 
   * de donde provienen los datos. Si no existen datos `link_id` sera' 
   * igual a -1.
   * 
   * @param[in] timeout Tiempo (en ms) a esperar por datos entrantes.
   * 
   * @return uint16_t indicando la cantidad de bytes disponibles:
   *      - 0   : no hay datos disponibles.
   *      - != 0: cantidad de bytes disponibles.
   *
   */
  uint16_t ESP8266_AvailableData( int8_t *link_id, uint16_t timeout );
  
  /**
   * @brief Lee los bytes enviados desde otro dispositivo.
   * 
   * Esta funcio'n permite obtener los datos enviados mediante un enlace
   * previamente establecido con la funcio'n \ref ESP8266_OpenConnection(). 
   * La funcio'n \ref ESP8266_AvailableData() debe ser ejecutada antes de esta 
   * rutina para conocer los bytes disponibles y el identificador de enlace.
   *
   * @param[out] incomming_data Arreglo en el que se almacenara'n los bytes.
   * 
   * @param[in] num_of_bytes cantidad ma'xima de bytes a leer.
   * 
   * @return La cantidad de bytes restantes que pueden ser leidos.
   * 
   */
  uint16_t ESP8266_ReadData( uint8_t *incomming_data, uint16_t num_of_bytes );
  
  /**
   * @brief Cierra una conexio'n previamente establecida.
   * 
   * Esta rutina cierra una conexio'n previamente establecida (mediante la 
   * rutina \ref ESP8266_OpenConnection()).
   * 
   * @param[in] link_id Entero en el rango [0-4] que especifica
   * la conexio'n a utilizar.
   * @return Un valor del enum \ref ESP8266_RESPONSE:
   * - ESP8266_RESPONSE_OK: Conexio'n cerrada con exito.
   * - ESP8266_RESPONSE_ERROR: La conexion ya estaba cerrada.
   * - ESP8266_RESPONSE_TIMEOUT: Tiempo de espera por respuesta excedido.
   */
  ESP8266_RESPONSE ESP8266_CloseConnection( int8_t link_id );
  
  //uint8_t ESP8266_CloseAllConnection( void ); // Send link_id=5
  
  /**
   * @brief Esta rutina habilita o deshabilita el uso de multiples conexiones.
   * 
   * @param[in] enable Valor booleano que determina el uso o no de multiples conexiones:
   *    - \b true: Habilitar el uso de multiples conexiones
   *    - \b false: Deshabilitar el uso de multiples conexiones
   * 
   * @return Un valor del enum \ref ESP8266_RESPONSE:
   * - ESP8266_RESPONSE_OK: Operacio'n realizada con exito.
   * - ESP8266_RESPONSE_ERROR: Error en la operacio'n
   * - ESP8266_RESPONSE_TIMEOUT: Tiempo de espera por respuesta excedido
   * 
   * @note Para deshabilitar el uso de conexiones multiples es necesario
   * detener el servidor TCP del mo'dulo ESP8266.
   */
  ESP8266_RESPONSE ESP8266_EnableMultipleConnections( bool enable );
  
  /**
   * @brief Inicia el Servidor TCP del mo'dulo ESP8266
   * 
   * Esta rutina inicia el servidor TCP del mo'dulo ESP8266 y habilita el uso
   * de conexiones multiples (ya que es necesario)
   * 
   * @param[in] port Puerto de escucha para el servidor TCP del mo'dulo ESP8266.
   * 
   * @return Un valor del enum \ref ESP8266_RESPONSE:
   * - ESP8266_RESPONSE_OK: Operacio'n realizada con exito.
   * - ESP8266_RESPONSE_ERROR: Error en la operacio'n
   * - ESP8266_RESPONSE_TIMEOUT: Tiempo de espera por respuesta excedido
   */
  ESP8266_RESPONSE ESP8266_StartTCPServer( uint16_t port );
  
  /**
   * @brief Detiene el servidor TCP del mo'dulo ESP8266
   * 
   * Esta rutina detiene el servidor TCP del mo'dulo ESP8266.
   * 
   * @return Un valor del enum \ref ESP8266_RESPONSE:
   * - ESP8266_RESPONSE_OK: Operacio'n realizada con exito.
   * - ESP8266_RESPONSE_ERROR: Error en la operacio'n
   * - ESP8266_RESPONSE_TIMEOUT: Tiempo de espera por respuesta excedido
   */
  ESP8266_RESPONSE ESP8266_StopTCPServer(void);
  
  /**
   * @brief Permite obtener el tiempo de desconexio'n del servidor TCP.
   * 
   * @return Un entero de 16 bit:
   *      - \b <0: Error
   *      - \b >0: Tiempo de desconexio'n
   * 
   * @note Si un cliente TCP no envia datos durante un tiempo mayor
   * al tiempo de desconexio'n el servidor TCP lo desconectara'.
   */
  int16_t ESP8266_GetTCPServerTimeout( void );
  
  /**
   * @brief Permite establecer el tiempo de desconexio'n del servidor TCP
   * 
   * @param[in] time Entero en el rango [0-7200] que indica el tiempo de 
   * desconexio'n en segundos.
   * 
   * @return Un valor del enum \ref ESP8266_RESPONSE:
   * - ESP8266_RESPONSE_OK: Operacio'n realizada con exito.
   * - ESP8266_RESPONSE_ERROR: Error en la operacio'n
   * - ESP8266_RESPONSE_TIMEOUT: Tiempo de espera por respuesta excedido
   * 
   * @note Si un cliente TCP no envia datos durante un tiempo equivalente
   * al tiempo de desconexio'n el servidor TCP lo desconectara'.  
   * 
   * @note Si el tiempo de desconexio'n es igual a cero el servidor
   * nunca desconectara' los clientes (no recomendado).
   */
  ESP8266_RESPONSE ESP8266_SetTCPServerTimeout( int16_t time );
  
  /**
   * @brief Permite realizar "ping" a una direccio'n IP o un dominio
   * especifico.
   * 
   * @param[in] ip_or_address Direccio'n IP o dominio.
   * Ej: "10.42.0.2", "www.google.com"
   * 
   * @return Entero de 16 bits:
   *      - \b <0 Ping no retornado
   *      - \b >0 Tiempo de respuesta del ping
   */
  int16_t ESP8266_Ping( const char *ip_or_address );
  
  /**
   * @brief Comprueba si existe al menos un byte para leer en el
   * buffer de recepcio'n.
   * 
   * La implementacio'n de esta funcio'n debe verificar la existencia de
   * datos listos para ser leidos con la funcio'n \ref esp8266_getchar();
   * 
   * @return bool que indica la existencia o no de datos enel buffer de 
   * recepcio'n.
   *      - \b true: Datos disponibles
   *      - \b false: Buffer de recepcio'n vacio
   * 
   * @note Esta funcio'n tiene que ser implementada por el usuario.
   */
  bool esp8266_ready2read(void);
  
  /**
   * @brief Esta rutina lee un byte enviado por el mo'dulo ESP8266.
   *  
   * @return Un caracter enviado por el mo'dulo ESP8266.
   * 
   * @note Esta funcio'n tiene que ser implementada por el usuario.
   */
  char esp8266_getchar(void);
    
  /* Write functions */
  
  /**
   * @brief Envia un caracter al mo'dulo ESP8266.
   * 
   * @param[in] c Caracter a enviar.
   * 
   * @note Esta funcio'n tiene que ser implementada por el usuario. 
   */
    void esp8266_putchar(char c);
  
  /**
   * @brief Envia una cadena de caracteres al mo'dulo ESP8266. 
   * 
   * La cadena a enviar tiene que estar terminada por el caracter nulo ('\0').
   * El caracter nulo no sera' enviado.
   * 
   * @param[in] str Cadena de caracteres a enviar.
   * 
   * @return La cantidad de caracteres enviados.
   */
  int16_t esp8266_puts( const char* str );

#ifdef	__cplusplus
}
#endif

#endif	/* ESP8266_H */