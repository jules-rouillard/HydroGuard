/*
  C Library for ESP8266 Wifi module with PIC microcontrollers
  Copyright (C) 2020 Jose Guerra <joseguerracarmenate@gmail.com> 
  
  This library is free software: you can redistribute it and/or modify
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
 * @file:   esp8266.c
 * @author: Jose Guerra Carmenate
 *
 * Created on March 29, 2020, 11:10 AM
 */
#include "mcc_generated_files/system/system.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "esp8266.h"



bool esp8266_ready2read()
{
    return UART1_IsRxReady();   
}
//**Function to get one byte of date from UART**//
char esp8266_getchar()   
{
    /**
    if(OERR) // check for Error 
    {
        CREN = 0; //If error -> Reset 
        CREN = 1; //If error -> Reset 
    }
    */
    while(!PIE4bits.U1RXIE); // hold the program till RX buffer is free
                  //repera RX ficar livre
        
    return U1RXB; //receive the value and send it to main function
                  //pega o valor recebido e emcaminha para função main
}


//**Function to send one byte of date to UART **//
void esp8266_putchar(char c)  //Encaminha um bute de dados para UART
{
    while(!PIE4bits.U1TXIE);  // hold the program till TX buffer is free
                    //espera o transmissor ficar livre
    
     U1TXB = c; //Load the transmitter buffer with the received value
                //carrega o transmissor com o valor recebido bt
}
//_____________End of function________________//

/******************************************************************************/
/**************************  Sections: Macros    ******************************/
/******************************************************************************/




/**
 * Esta macro espera (durante 'timeout_var' milisegundos) a que halla almenos 
 * un caracter disponible en el buffer de lectura. Al terminar la ejecucion 
 * de la macro 'timeout_var' se encuentra decrementada en la cantidad de
 * milisegundos que fue  necesario esperar.
 * 
 * @param timeout_var es una variable (no puede ser un literal) que se ira'
 * decrementando a cada milisegundo.
 * 
 */
#define WAIT_FOR_CHAR( timeout_var )                \
    while( !esp8266_ready2read() && timeout_var ){  \
      timeout_var--;                                \
      __delay_ms(1);                                \
    }                                               \

#ifndef min
#define min( x, y ) (((x)<(y))?(x):(y))
#endif
/******************************************************************************/
/**************************  Sections: Constants ******************************/
/******************************************************************************/

/**
 * Listado con los comandos AT disponibles. Estos comandos se tienen que 
 * corresponder con los enum ESP8266_CMD delarados en esp8266.h
 */
const char * const AT_command[] = {
  // Basic AT
  "AT",
  "AT+RST",
  "AT+GMR",
  "AT+GSLP",
  "ATE",
  "AT+RESTORE",
  "AT+UART_CUR",
  "AT+UART_DEF",
  "AT+SLEEP",
  "AT+RFPOWER",
  "AT+RFVDD",
  
  // Wifi AT
  "AT+CWMODE_CUR",
  "AT+CWMODE_DEF",
  "AT+CWJAP_CUR",
  "AT+CWJAP_DEF",
  "AT+CWLAPOPT",
  "AT+CWLAP",
  "AT+CWQAP",
  "AT+CWSAP_CUR",
  "AT+CWSAP_DEF",
  "AT+CWLIF",
  "AT+CWDHCP_CUR",
  "AT+CWDHCP_DEF",
  "AT+CWDHCPS_CUR",
  "AT+CWDHCPS_DEF",
  "AT+CWAUTOCONN",
  "AT+CIPSTAMAC_CUR",
  "AT+CIPSTAMAC_DEF",
  "AT+CIPAPMAC_CUR",
  "AT+CIPAPMAC_DEF",
  "AT+CIPSTA_CUR",
  "AT+CIPSTA_DEF",
  "AT+CIPAP_CUR",
  "AT+CIPAP_DEF",
  "AT+CWSTARTSMART",
  "AT+CWSTOPSMART",
  "AT+CWSTARTDISCOVER",
  "AT+CWSTOPDISCOVER",
  "AT+WPS",
  "AT+MDNS",
  //TCP AT
  "AT+CIPSTATUS",
  "AT+CIPDOMAIN",
  "AT+CIPSTART",
  "AT+CIPSSLSIZE",
  "AT+CIPSEND",
  "AT+CIPSENDEX",
  "AT+CIPSENDBUF",
  "AT+CIPBUFSTATUS",
  "AT+CIPCHECKSEQ",
  "AT+CIPBUFRESET",
  "AT+CIPCLOSE",
  "AT+CIFSR",
  "AT+CIPMUX",
  "AT+CIPSERVER",
  "AT+CIPMODE",
  "AT+SAVETRANSLINK",
  "AT+CIPSTO",
  "AT+PING",
  "AT+CIUPDATE",
  "AT+CIPDINFO",
};

#if 0
const char * const BASIC_AT[] = {
  "AT",
  "AT+RST",
  "AT+GMR",
  "AT+GSLP",
  "ATE",
  "AT+RESTORE",
  "AT+UART_CUR",
  "AT+UART_DEF",
  "AT+SLEEP",
  "AT+RFPOWER",
  "AT+RFVDD"
};

const char * const WIFI_AT[] = {
  "AT+CWMODE_CUR",
  "AT+CWMODE_DEF",
  "AT+CWJAP_CUR",
  "AT+CWJAP_DEF",
  "AT+CWLAPOPT",
  "AT+CWLAP",
  "AT+CWQAP",
  "AT+CWSAP_CUR",
  "AT+CWSAP_DEF",
  "AT+CWLIF",
  "AT+CWDHCP_CUR",
  "AT+CWDHCP_DEF",
  "AT+CWDHCPS_CUR",
  "AT+CWDHCPS_DEF",
  "AT+CWAUTOCONN",
  "AT+CIPSTAMAC_CUR",
  "AT+CIPSTAMAC_DEF",
  "AT+CIPAPMAC_CUR",
  "AT+CIPAPMAC_DEF",
  "AT+CIPSTA_CUR",
  "AT+CIPSTA_DEF",
  "AT+CIPAP_CUR",
  "AT+CIPAP_DEF",
  "AT+CWSTARTSMART",
  "AT+CWSTOPSMART",
  "AT+CWSTARTDISCOVER",
  "AT+CWSTOPDISCOVER",
  "AT+WPS",
  "AT+MDNS",
};

const char * const TCP_AT[] = {
  "AT+CIPSTATUS",
  "AT+CIPDOMAIN",
  "AT+CIPSTART",
  "AT+CIPSSLSIZE",
  "AT+CIPSEND",
  "AT+CIPSENDEX",
  "AT+CIPSENDBUF",
  "AT+CIPBUFSTATUS",
  "AT+CIPCHECKSEQ",
  "AT+CIPBUFRESET",
  "AT+CIPCLOSE",
  "AT+CIFSR",
  "AT+CIPMUX",
  "AT+CIPSERVER",
  "AT+CIPMODE",
  "AT+SAVETRANSLINK",
  "AT+CIPSTO",
  "AT+PING",
  "AT+CIUPDATE",
  "AT+CIPDINFO",
};
#endif
/**
 * Parametros para el comando CWMODE.
 */
const char * const CWMODE_param[] = {
  "=1",
  "=2",
  "=3"
};

/**
 * Respuestas de los comandos AT.
 * Este arreglo tiene que corresponderse con el enum ESP8266_RESPONSE
 */
const char * const RESPONSE[] = {
  "OK",
  "ready",
  "FAIL",
  "NOCHANGE",
  "LINKED",
  "UNLINK",
  "ERROR",
  "",
  "TIMEOUT"
};

const char ENDL[] = "\r\n";


/******************************************************************************/
/************************ Section: Auxiliar Vars ******************************/
/******************************************************************************/

static char aux[17+20];

__bit buffer_clear;     ///< Es puesto en estado alto cuando se ejecuta la rutina `clearBuffer`

static uint16_t availableData;  ///< Datos disponibles para leer provenientes de una comunicacio'n
                                ///< (TCP o UPD). Es actualizado en la ejecucio'n de la rutina
                                ///< `ESP8266_AvailableData`. 

/******************************************************************************/
/*************** Section: Low-Level functions Implementation ******************/
/******************************************************************************/


/**
 * @addtogroup low_level_functions Low-Level functions Implementation
 * @{
 */

/**
 * @brief Envia una cadena de caracteres al mo'dulo ESP8266.
 * 
 * Para enviar la cadena de caracteres se realizan llamadas suscesivas
 * a la rutina esp8266_putchar.
 * 
 * @param[in] str - cadena de caracteres a enviar.
 * @return la cantidad de caracteres enviados
 */
int16_t esp8266_puts( const char *str ){
  int16_t cnt = 0;
  
  while( *str ){
  
    esp8266_putchar( *str++ );
    cnt++;
  }
  return cnt;
}

/**
 * @brief Envia un comando AT al mo'dulo ESP8266
 * 
 * @param[in] cmd - Comando AT a enviar. Ver enum ESP8266_CMD para comandos disponibles.
 * @param[in] param - cadena de caracteres con los parametros
 * del comando.
 * 
 * @example
 * <code>
 * esp8266_sendCommand( CMD_SLEEP, "=10" );
 * </code>
 * 
 */
static void esp8266_sendCommand( ESP8266_CMD cmd, const char* param ){
  esp8266_puts( AT_command[cmd] );
  esp8266_puts( param );
  esp8266_puts( ENDL );
}

/**
 * @brief Comprueba la llegada de una respuesta durante un tiempo `timeout`.
 * 
 * @param[out] output - si este puntero es distinto de null los bytes leidos seran 
 * almacenados aqui.
 * @param[in] timeout - tiempo en milisegundos a esperar por la respuesta.
 * @return La respuesta encontrada. Ver enum `ESP8266_RESPONSE` para ma's detalles
 */
static ESP8266_RESPONSE esp8266_readResponse( char *output, uint16_t timeout ){
  
  uint8_t idx[ESP8266_RESPONSE_QUANTITY], 
          cur_idx;
  const char *p;
  char c;

  for( uint8_t i = 0; i < ESP8266_RESPONSE_QUANTITY; i++ )
    idx[i] = 0;
  
  do{
    WAIT_FOR_CHAR(timeout);
    
    if( timeout == 0 )
      return ESP8266_RESPONSE_TIMEOUT; // no response found
    
    c = esp8266_getchar();
    if( output != NULL ){
      *output = c;
      output++;
      *output = '\0';
    }
    
    for( uint8_t i = 0; i < ESP8266_RESPONSE_QUANTITY; i++ ){
      cur_idx = idx[i];
      p = RESPONSE[i];
      
      if( p[cur_idx] == c ){
        cur_idx++;
      }
      else{
        cur_idx = 0;
      }
      
      if( p[cur_idx] == '\0' )
        return i;
      
      idx[i] = cur_idx;
      
    }//for
  
  }while( 1 );
  
  return ESP8266_RESPONSE_TIMEOUT; // no response found
}

/**
 * @brief Recibe caracteres del mo'dulo ESP8266 hasta que encuentre una de las dos candenas.
 * 
 * @param[out] recv - puntero a una cadena de caracteres donde se almacenaran los caracteres recibidos.
 * Si no se requiere almacenar los caracteres debe ser utilizado el valo NULL.
 * @param[in] until1 - cadena de texto #1 para comparar con la entrada.  
 * @param[in] until2 - cadena de texto #2 para comparar con la entrada.  
 * 
 * @return
 *  - 1 : String 1 encontrado
 *  - 2 : String 2 encontrado
 */
static uint8_t esp8266_readUntil( char *recv, const char *until1, const char *until2, int16_t timeout ){
  char c;
  uint8_t index1 = 0, 
          index2 = 0;
  *recv = '\0';
  
  if( until2 == NULL || *until2 == '\0' )  // asi no tengo q comprobarlo dentro del bucle
    until2 = until1;
  
  do{
    WAIT_FOR_CHAR(timeout);
    
    if( timeout <= 0 )
      return ESP8266_RESPONSE_TIMEOUT;
    c = esp8266_getchar();
    
    if( recv != NULL ){
      *recv = c;
      recv++;
      *recv = '\0';
    }
    
    index1 = ((c == until1[index1])? index1+1 : 0);
    
    if( until1[index1] == '\0' )
      return 1;
    
    index2 = ((c == until2[index2])? index2+1 : 0);
    
    if( until2[index2] == '\0' )
      return 2;
    
  }while(1);
  
  return ESP8266_RESPONSE_TIMEOUT;
}

/**
 * @brief Limpia el buffer de recepcion (No implementado en el controlador de esp8266)
 * 
 */
static void clearBuffer(void){
  buffer_clear = 1;
  while( esp8266_ready2read() )
    esp8266_getchar();
}


/** @}*/

/******************************************************************************/
/******************* Section: API functions Implementation ********************/
/******************************************************************************/

uint8_t ESP8266_Initialize( WIFI_MODE mode ){
  ESP8266_RESPONSE response;
  
  clearBuffer();
  // Esperar hasta que el mo'dulo Responda
  while( !ESP8266_CheckCommunication() );
  
  __delay_ms(10);
  clearBuffer();
  //reiniciar
  esp8266_sendCommand( CMD_RST, "" );
  
  // Esperar el "OK" por el comando
  response = esp8266_readResponse(NULL, 3000);
  if( response != ESP8266_RESPONSE_OK )
    return response;
  
  // Esperar el "ready" por el reinicio
  response = esp8266_readResponse(NULL, 7000);
  if( response != ESP8266_RESPONSE_READY )
    return response;

  // Limpiar buffer de recepcio'n.
  clearBuffer();
  
  // Apagar el Eco de los comandos
  esp8266_sendCommand( CMD_ATE, "0" ); 
  response = esp8266_readResponse(NULL, 3000);
  if( response != ESP8266_RESPONSE_OK )
    return response;
  
  // Configurar el modo Wifi
  response = ESP8266_SetWifiMode( mode );
  if( response != ESP8266_RESPONSE_OK )
    return response;
 
  // Habilitar el uso de multiples conexiones
  response = ESP8266_EnableMultipleConnections( true );
  if( response != ESP8266_RESPONSE_OK )
    return response;
#if 0
  if( (mode & WIFI_MODE_SOFTAP) && (ap != NULL) ){
    response = ESP8266_SetSoftApSettings( ap );
    if( response != ESP8266_RESPONSE_OK )
      return response;
  }
  if( (mode & WIFI_MODE_STATION) && (stat != NULL) ){
    response = ESP8266_SetStationSettings( stat );
    if( response != ESP8266_RESPONSE_OK )
      return response;
    
  }
#endif
  return ESP8266_RESPONSE_OK;
}

uint8_t ESP8266_SetSoftApSettings( softAp_setting_t *ap_config ){
  ESP8266_RESPONSE resp;
  
  resp = ESP8266_SetSoftApMacAddress( &(ap_config->mac) );
  if( resp != ESP8266_RESPONSE_OK )
    return resp;

  resp = ESP8266_SetSoftApWifiSettings( ap_config->wifi );
  if( resp != ESP8266_RESPONSE_OK )
    return resp;
    
  resp = ESP8266_SetSoftApIpRange( &(ap_config->startIP), &(ap_config->endIP), ap_config->dhcp_lease_time );
  if( resp != ESP8266_RESPONSE_OK )
    return resp;
  
  resp = ESP8266_EnableDHCP( WIFI_MODE_SOFTAP, ap_config->dhcp_enable );
  if( resp != ESP8266_RESPONSE_OK )
    return resp;
  
  return ESP8266_RESPONSE_OK;
}

uint8_t ESP8266_SetStationSettings( station_setting_t *stat_config ){
  ESP8266_RESPONSE resp;
  
  //putch( 'A' );
  resp = ESP8266_SetStationMacAddress( &(stat_config->mac) );
  //putch( 'B' );
  if( resp != ESP8266_RESPONSE_OK )
    return resp;
  //putch( 'C' );
  if( stat_config->dhcp_enable ){
    resp = ESP8266_EnableDHCP( WIFI_MODE_STATION, true );
  }
  else{
    resp = ESP8266_EnableDHCP( WIFI_MODE_STATION, false );
    if( resp != ESP8266_RESPONSE_OK )
      return resp;
    
    resp = ESP8266_SetStationIP( &(stat_config->ip), NULL, NULL );
  }
  if( resp != ESP8266_RESPONSE_OK )
    return resp;
  
  return ESP8266_RESPONSE_OK;
}

const char* ESP8266_CodeToString( ESP8266_RESPONSE code ){
  
  return RESPONSE[code];

}

bool ESP8266_CheckCommunication(void){
  esp8266_sendCommand( CMD_AT, "" );
  uint8_t response = esp8266_readResponse(NULL, 1000);
  
  return (response == ESP8266_RESPONSE_OK);
 }

bool ESP8266_Reset(void){
  esp8266_sendCommand( CMD_RST, "" );
  return (esp8266_readResponse(NULL, 3000) == ESP8266_RESPONSE_READY);
}

ESP8266_RESPONSE ESP8266_SetWifiMode(WIFI_MODE mode){
  esp8266_sendCommand( CMD_CWMODE_CUR, CWMODE_param[mode-1] );
  return esp8266_readResponse( NULL, 3000 );  
}

WIFI_MODE ESP8266_GetWifiMode(void){
  esp8266_sendCommand( CMD_CWMODE_CUR, "?" );
  
  uint8_t response = esp8266_readUntil( NULL, "+CWMODE_CUR:", "", 1000 );
  if( response == ESP8266_RESPONSE_TIMEOUT )
    return WIFI_MODE_UNKNOWN;
  
  char c = esp8266_getchar();     // obtener el modo de operacion
  response = esp8266_readResponse( NULL, 1000 );

  
  if( response != ESP8266_RESPONSE_OK ) // el OK debe ser enviado
    return WIFI_MODE_UNKNOWN;
  
  return (c-'0');
}

AP_CONN_RET ESP8266_ConnectToAP( const char* ssid, const char* pwd, const char* bssid ){
  uint8_t res;
  AP_CONN_RET ret;
  clearBuffer();
  esp8266_puts( AT_command[CMD_CWJAP_CUR] );
  esp8266_puts( "=\"" );
  
  esp8266_puts( ssid );   // ssid de  la wifi.
  esp8266_puts("\",\"");  // cerrar comillas; poner coma; abrir comillas.
  esp8266_puts( pwd );    // password de la wifi.
  esp8266_puts( "\"" );   // cerrar comillas.
  if( bssid != NULL && *bssid != '\0' ){
    esp8266_puts(",\"");
    esp8266_puts( bssid );    // MAC de la wifi
    esp8266_putchar('\"');
  }
  
  esp8266_puts( ENDL );   // \r\n
  
  char buff[30];
  //LCD_Clear();
  res = esp8266_readUntil(buff, "+CWJAP:", RESPONSE[ESP8266_RESPONSE_OK], 15000 );
  //LCD_PrintString( buff );
  
  if( res == 1 ){      // +CWJAP
    ret = esp8266_getchar() - '0';
    res = esp8266_readUntil( NULL, RESPONSE[ESP8266_RESPONSE_FAIL],"" , 2000 );
    if( res == 1 ){
      return (AP_CONN_RET)(res);
    }
  }
  else if( res == 2 ){ // OK
    return AP_CONN_OK;
  }
  
  return AP_CONN_TIMEOUT; // ESP8266_RESPONSE_TIMEOUT
}

uint8_t ESP8266_DisconnectFromAP(void){
  esp8266_sendCommand( CMD_CWQAP, "" );
  
  return esp8266_readResponse( NULL, 1000 );
}

ESP8266_RESPONSE ESP8266_SetSoftApWifiSettings( wifi_setting_t *cfg ){
  esp8266_puts( AT_command[CMD_CWSAP_CUR] );
  //DEBUG = true;
  esp8266_puts( "=\"" );
  esp8266_puts( cfg->ssid );                          // ssid
  esp8266_puts( "\",\"" );                            // comillas, coma, comillas
  esp8266_puts(cfg->pwd);                             // password
  esp8266_puts("\",");                                // comillas, coma
  esp8266_putchar( (char)(cfg->wifi_channel + '0') ); // canal
  esp8266_putchar( (char)',' );                       // coma
  esp8266_putchar( (char)(cfg->ecn + '0') );          // protocolo de seguridad
  esp8266_putchar( ',' );                             // coma
  esp8266_putchar( (cfg->max_stations) + '0' );           // cant. de conexiones
  esp8266_putchar( ',' );                             // coma
  esp8266_putchar( ((cfg->ssid_hidden)?1:0)+'0' );    // broadcast
  esp8266_puts( ENDL );                               // \r\n
  
  return esp8266_readResponse( NULL, 15000 );
}

ESP8266_RESPONSE ESP8266_GetSoftApWifiSettings( wifi_setting_t *cfg ){
  char c;

  if( cfg == NULL )
    return -1;
  esp8266_sendCommand( CMD_CWSAP_CUR, "?" );
  uint8_t resp = esp8266_readUntil( NULL, RESPONSE[ESP8266_RESPONSE_ERROR], "+CWSAP_CUR:", 3000 );
  
  if( resp == 1 )
    return ESP8266_RESPONSE_ERROR;
  
  // Leer ssid
  esp8266_getchar(); // desechar comillas(") de apertura
  
  esp8266_readUntil( cfg->ssid, "\"", NULL, 1000 ); // leer hasta las comillas de cierre
  
  cfg->ssid[ strlen(cfg->ssid)-1 ] = '\0'; // eliminar comilla final

  esp8266_getchar();  // desechar coma (,)
  
  /// Leer Password
  esp8266_getchar(); // desechar comilla (") de apertura
  
  esp8266_readUntil( cfg->pwd, "\"", NULL, 1000 ); // leer hasta las comillas de cierre
  cfg->pwd[ strlen(cfg->pwd)-1 ] = '\0'; // eliminar comilla final

  // Leer canal
  esp8266_getchar();  // desechar coma (,)

  cfg->wifi_channel = esp8266_getchar() - '0';
  if( (c = esp8266_getchar()) != ',' ){
    cfg->wifi_channel *= 10;
    cfg->wifi_channel += c-'0';
    esp8266_getchar();  // desechar coma (,)
  }
  
  // Leer protocolo de Seguridad
  
  cfg->ecn = (uint8_t)(esp8266_getchar() - '0');
  
  // Leer cantidad ma'xima de conexiones permitidas
  esp8266_getchar();  // desechar coma (,)
  
  cfg->max_stations = esp8266_getchar() - '0';

  // Leer broadcast de ssid
  esp8266_getchar();  // desechar coma (,)
  
  cfg->ssid_hidden = (esp8266_getchar()=='1')?true:false;
  
  return esp8266_readResponse( NULL, 2000 );
}

int8_t ESP8266_GetConnectedStation( int8_t station_number, station_t* station ){
  uint8_t res = 0; 
  int8_t ret = -1;
  int8_t len;
  if( station == NULL )
    return -1;
  station->ip.all = 0x00000000;
  station->mac.block[0] = 0x00;
  station->mac.block[1] = 0x00;
  station->mac.block[2] = 0x00;
  station->mac.block[3] = 0x00;
  station->mac.block[4] = 0x00;
  station->mac.block[5] = 0x00;
  if( station_number > 3 )
    return -1;
  
  clearBuffer();
  esp8266_sendCommand( CMD_CWLIF, "" );
  
  while( (res != 2) && (res != ESP8266_RESPONSE_TIMEOUT) ){
    res = esp8266_readUntil( aux , ENDL, RESPONSE[ESP8266_RESPONSE_OK], 2000 ); // lo almaceno
//    LCD_PrintChar( '0'+res );
    if( res == 1 ){
      len = 10;
      while( len >= 0 && aux[len] != '\0' )  // si los primeros caracteres son distintos de '\0'
        len--;
      if( len == -1 )                // es valido
        ret++;
    }
    if( ret == station_number )
      break;
  } //while
  
  if( res == ESP8266_RESPONSE_TIMEOUT )
    return ESP8266_RESPONSE_TIMEOUT;
  
  if( res != 2 ) // leer lo que falte (si falta)
    res = esp8266_readUntil( NULL , RESPONSE[ESP8266_RESPONSE_OK], NULL, 2000 );

  if( res == 1 ){ // ESP8266_RESPONSE_OK recibido
    if(ret == station_number){
      station->ip = str2ipv4( aux );
      station->mac = str2mac( strstr( aux, "," ) );
      return 0;
    }
    else
      return ++ret;
  }
  else
    return -1;
}

ESP8266_RESPONSE ESP8266_EnableDHCP( WIFI_MODE mode_to_set, bool en ){
  clearBuffer();
  
  switch( mode_to_set ){
    case WIFI_MODE_STATION:
      esp8266_sendCommand( CMD_CWDHCP_CUR, (en)?"=1,1":"=1,0" );
      break;
    case WIFI_MODE_SOFTAP:
      esp8266_sendCommand( CMD_CWDHCP_CUR, (en)?"=0,1":"=0,0" );
      break;
    case WIFI_MODE_SOFTAP_AND_STATION:
      esp8266_sendCommand( CMD_CWDHCP_CUR, (en)?"=2,1":"=2,0" );
      break;
    default:
      break;
  }
  return esp8266_readResponse(NULL, 2000);
  
}

int16_t ESP8266_GetIpRange( ipv4_address_t *startIP, ipv4_address_t *endIP ){
  int16_t lease_time = 0;
  uint8_t resp;
  clearBuffer();
  esp8266_sendCommand( CMD_CWDHCPS_CUR, "?" );
  
  if (esp8266_readUntil( NULL, "+CWDHCPS_CUR:", NULL, 2000 ) == ESP8266_RESPONSE_TIMEOUT )
    return -ESP8266_RESPONSE_TIMEOUT;
  
  while( (resp = esp8266_getchar()) != ',' ){
    lease_time *= 10;
    lease_time += resp - '0';
  }
  
  if( esp8266_readUntil( aux, ENDL, NULL, 2000 ) == ESP8266_RESPONSE_TIMEOUT)
    return -ESP8266_RESPONSE_TIMEOUT;
  
  *startIP = str2ipv4( aux );
  
  *endIP = str2ipv4( strstr(aux, ",") );
  
  resp = esp8266_readResponse( NULL, 2000 );
  if( resp != ESP8266_RESPONSE_OK )
    return -resp;

  return lease_time;
  
}

ESP8266_RESPONSE ESP8266_SetSoftApIpRange(ipv4_address_t* startIP, ipv4_address_t* endIP, int16_t lease){
  esp8266_puts( AT_command[CMD_CWDHCPS_CUR] );
  esp8266_putchar( '=' );
  if( startIP == NULL ){
    esp8266_putchar('0');
  }
  else{
    esp8266_putchar('1');
    //lease time
    sprintf( aux, ",%d,\"", lease );
    esp8266_puts( aux );
    
    //start IP
    ip2str( startIP, aux );
    esp8266_puts( aux );
    
    //end IP
    esp8266_puts( "\",\"" );
    ip2str( endIP, aux );
    esp8266_puts( aux );
    esp8266_putchar( '"' );
    
  }

  esp8266_puts( ENDL);
  
  return esp8266_readResponse(NULL,5000);
}

ESP8266_RESPONSE ESP8266_AutoConnect( bool auto_connect ){
  esp8266_sendCommand( CMD_CWAUTOCONN, auto_connect?"1":"0" );
  
  return esp8266_readResponse( NULL, 2000 );
  
}

ESP8266_RESPONSE ESP8266_GetStationMacAddress( mac_address_t* mac ){
  uint8_t resp;

  clearBuffer();
  esp8266_sendCommand( CMD_CIPSTAMAC_DEF, "?" );
  
  resp = esp8266_readUntil( NULL, "+CIPSTAMAC_DEF:", RESPONSE[ESP8266_RESPONSE_ERROR], 3000);
  if( resp == 2 ){
    return ESP8266_RESPONSE_ERROR;
  }
  else if (resp == ESP8266_RESPONSE_TIMEOUT ){
    return ESP8266_RESPONSE_TIMEOUT;
  }
  
  resp = esp8266_readResponse( aux, 3000 );
  
  if( resp == ESP8266_RESPONSE_TIMEOUT ){
    return ESP8266_RESPONSE_TIMEOUT;
  }
  *mac = str2mac( aux );
  
  return resp;
}

ESP8266_RESPONSE ESP8266_SetStationMacAddress( mac_address_t* mac ){
  clearBuffer();
  
  mac_address_t old;
  
  /*ESP8266_GetStationMacAddress(&old);
  
  if( (old.low_4bytes == mac->low_4bytes) &&
      (old.high_2bytes == mac->high_2bytes) )
    return ESP8266_RESPONSE_OK;
  */
  aux[0] = '=';
  aux[1] = '"';
  mac2str( mac, aux+2 );
  aux[MAC_STRING_LENGTH+2] = '"';
  aux[MAC_STRING_LENGTH+3] = '\0';
  //LCD_PrintString( aux);
  esp8266_sendCommand( CMD_CIPSTAMAC_DEF, aux );
  
  return esp8266_readResponse( NULL, 2000 );
}

ESP8266_RESPONSE ESP8266_GetSoftApMacAddress( mac_address_t* ap_mac ){
  
  clearBuffer();
  
  esp8266_sendCommand( CMD_CIPAPMAC_DEF, "?" );
  
  if( esp8266_readUntil(NULL, "+CIPAPMAC_DEF:", NULL, 2000) == ESP8266_RESPONSE_TIMEOUT )
    return ESP8266_RESPONSE_TIMEOUT;
  
  if( esp8266_readUntil( aux, ENDL, NULL, 2000 ) == ESP8266_RESPONSE_TIMEOUT ){
    return ESP8266_RESPONSE_TIMEOUT;
  }
  
  *ap_mac = str2mac( aux );
  
  return esp8266_readResponse(NULL, 2000);
}

ESP8266_RESPONSE ESP8266_SetSoftApMacAddress( mac_address_t* mac ){
  clearBuffer();
  
  mac_address_t old;
  
  ESP8266_GetSoftApMacAddress(&old);
  
  if( (old.low_4bytes == mac->low_4bytes) &&
      (old.high_2bytes == mac->high_2bytes) )
    return ESP8266_RESPONSE_OK;

  
  aux[0] = '=';
  aux[1] = '"';
  mac2str( mac, aux+2 );
  aux[MAC_STRING_LENGTH+2] = '"';
  aux[MAC_STRING_LENGTH+3] = '\0';
  //LCD_PrintString( aux);
  esp8266_sendCommand( CMD_CIPAPMAC_DEF, aux );
  
  return esp8266_readResponse( NULL, 2000 );
}

ESP8266_RESPONSE ESP8266_SetStationIP( ipv4_address_t *ip, ipv4_address_t* gateway, ipv4_address_t* mask){
  clearBuffer();
  esp8266_puts( AT_command[CMD_CIPSTA_CUR] );
  esp8266_putchar( '=' );
  esp8266_putchar( '"' );
  esp8266_puts( ip2str( ip, aux ) );
  if( gateway == NULL ){
    esp8266_putchar('"');
  }
  else{
    esp8266_puts( "\",\"" );
    esp8266_puts( ip2str( gateway, aux ) );
    esp8266_puts( "\",\"" );
    esp8266_puts( ip2str( mask, aux ) );
    esp8266_putchar('"');
  }
  esp8266_puts( ENDL );
  
  return esp8266_readResponse(NULL, 5000);
  
}

ESP8266_RESPONSE ESP8266_GetStationIP( ipv4_address_t *ip ){
  clearBuffer();
  
  esp8266_sendCommand( CMD_CIPSTA_CUR, "?" );
  
  if( esp8266_readUntil(NULL, "+CIPSTA_CUR:ip:", NULL, 2000) == ESP8266_RESPONSE_TIMEOUT ){
    return ESP8266_RESPONSE_TIMEOUT;
  }

  if( esp8266_readUntil( aux, ENDL, NULL, 2000 ) == ESP8266_RESPONSE_TIMEOUT ){
    return ESP8266_RESPONSE_TIMEOUT;
  }
  
  *ip = str2ipv4( aux );
  
  
  return esp8266_readResponse( NULL, 2000 );
}

ESP8266_RESPONSE ESP8266_SetSoftApIP( ipv4_address_t *ip, ipv4_address_t* gateway, ipv4_address_t* mask){
  clearBuffer();
  esp8266_puts( AT_command[CMD_CIPAP_CUR] );
  esp8266_putchar( '=' );
  esp8266_putchar( '"' );
  esp8266_puts( ip2str( ip, aux ) );
  if( gateway == NULL ){
    esp8266_putchar('"');
  }
  else{
    esp8266_puts( "\",\"" );
    esp8266_puts( ip2str( gateway, aux ) );
    esp8266_puts( "\",\"" );
    esp8266_puts( ip2str( mask, aux ) );
    esp8266_putchar('"');
  }
  esp8266_puts( ENDL );
  
  return esp8266_readResponse(NULL, 5000);
}

ESP8266_RESPONSE ESP8266_GetSoftApIP( ipv4_address_t *ip){
  clearBuffer();
  
  esp8266_sendCommand( CMD_CIPAP_CUR, "?" );
  
  if( esp8266_readUntil(NULL, "+CIPAP_CUR:", NULL, 2000) == ESP8266_RESPONSE_TIMEOUT ){
    return ESP8266_RESPONSE_TIMEOUT;
  }

  if( esp8266_readUntil( aux, ENDL, NULL, 2000 ) == ESP8266_RESPONSE_TIMEOUT ){
    return ESP8266_RESPONSE_TIMEOUT;
  }
  
  *ip = str2ipv4( aux );
  
  return esp8266_readResponse( NULL, 2000 );

}

LINK_STATUS ESP8266_OpenConnection( int8_t link_id, TRANSPORT_PROTOCOL conn_type, const char *server, uint16_t port ){
  clearBuffer();
  sprintf( aux, "=%d,\"", link_id );
  
  esp8266_puts( AT_command[CMD_CIPSTART] ); // comando
  esp8266_puts( aux );  // = <link id>,"
  
  switch(conn_type){
    case TRANSPORT_PROTOCOL_TCP:
      esp8266_puts( "TCP\"" );    // TCP"
      break;
    case TRANSPORT_PROTOCOL_UDP:
      esp8266_puts("UDP\"");      // UDP"
      break;
    case TRANSPORT_PROTOCOL_SSL:
      esp8266_puts("SSL\"");      // SSL"
      break;
    default:
      return -1;
  }
  esp8266_putchar( ',' );         // ,
  esp8266_putchar( '"' );         // "
  esp8266_puts( server );         // ip address or url   
  
  sprintf( aux, "\",%d", port );
  esp8266_puts( aux );            // port
  esp8266_puts( ENDL );

  ESP8266_RESPONSE r = esp8266_readResponse( aux, 5000 );
  
  switch(r){
    case ESP8266_RESPONSE_OK:
      return LINK_STATUS_CONNECTED;

    case ESP8266_RESPONSE_ERROR:
      if( strstr( aux, "ALREADY" ) != NULL ){
        return LINK_STATUS_ALREADY_CONNECTED;
      }
      else{
        return LINK_STATUS_CLOSED;
      }
    default:
      return LINK_STATUS_ERROR;
  }
    
}

uint8_t ESP8266_SendDataPack( int8_t link_id,  const uint8_t *data, uint16_t n ){

  clearBuffer();
  
  if( link_id >= 0 )
    sprintf( aux, "=%d,%d", link_id, n ); // multiple connection
  else
    sprintf( aux, "=%d",n );              // single connection
  
  esp8266_sendCommand( CMD_CIPSEND, aux );
  
  uint8_t r = esp8266_readUntil( NULL, ">", NULL, 2000 );
  if( r != 1 )
    return ESP8266_RESPONSE_TIMEOUT;
  
  while( n-- ){
    esp8266_putchar( *data );
    data++;
  }
  
  return esp8266_readResponse( NULL, 3000 );
  
}

uint16_t ESP8266_AvailableData( int8_t *link_id, uint16_t timeout ){
  // no clear Buffer
  uint16_t num_of_bytes = 0;
  uint8_t c;
  
  if( esp8266_readUntil( NULL, "+IPD,", NULL, timeout ) != 1){ // no data available
    *link_id = -1;
    return 0x00;
  }
  
  *link_id = esp8266_getchar() - '0'; // link id
  
  esp8266_getchar();                  // desechar ','
  
  c = esp8266_getchar();              // leer la cantidad
  while( c != ':' ){                  // de bytes de informacio'n
    num_of_bytes *= 10;               // que siguen.
    num_of_bytes += (c-'0');
    c = esp8266_getchar();
  }
  availableData = num_of_bytes;
  return num_of_bytes;
}

uint16_t ESP8266_ReadData( uint8_t *incomming_data, uint16_t num_of_bytes ){
  uint16_t timeout = 3000; // 3 segundo
  int8_t link;
  
  if( availableData == 0 ){
    ESP8266_AvailableData( &link, 3000 );
  }
  
  num_of_bytes = min( availableData, num_of_bytes );
  
  for( ; num_of_bytes && timeout; availableData--, num_of_bytes-- ){
    WAIT_FOR_CHAR(timeout);
    
    if( incomming_data != NULL ){
      *incomming_data = esp8266_getchar();
      incomming_data++;
    }
  }
  
  if( availableData == 0 ){
    clearBuffer();
  }
  return availableData;
}

ESP8266_RESPONSE ESP8266_CloseConnection( int8_t link_id ){
  clearBuffer();
  sprintf( aux, "=%d", link_id );
  
  esp8266_sendCommand( CMD_CIPCLOSE, aux );
  
  return esp8266_readResponse(NULL, 2000);  
}

ESP8266_RESPONSE ESP8266_EnableMultipleConnections( bool enable ){
  esp8266_sendCommand( CMD_CIPMUX, enable?("=1"):("=0") );
  return esp8266_readResponse(NULL, 2000);
}

ESP8266_RESPONSE ESP8266_StartTCPServer( uint16_t port ){
  ESP8266_RESPONSE resp;
  
  resp = ESP8266_EnableMultipleConnections(true);
  if( resp != ESP8266_RESPONSE_OK )
    return resp;
  
  sprintf( aux, "=1,%d", port );
  
  esp8266_sendCommand( CMD_CIPSERVER, aux );
  
  return esp8266_readResponse( NULL, 2000 );
}

ESP8266_RESPONSE ESP8266_StopTCPServer(void){  
  esp8266_sendCommand( CMD_CIPSERVER, "=0" );
  
  return esp8266_readResponse( NULL, 2000 );  
}

int16_t ESP8266_GetTCPServerTimeout( void ){
  char c;
  int16_t ret = 0;
  esp8266_sendCommand( CMD_CIPSTO, "?" );
  
  c = esp8266_readUntil( NULL, "+CIPSTO:", NULL, 2000 );
  if( c != 1 )
    return -1;
  
  c = esp8266_getchar();
  
  while( ('0' <= c) && (c <= '9') ){
    ret *= 10;
    ret += (c-'0');
    c = esp8266_getchar();
  }
  
  c = esp8266_readResponse(NULL, 2000);
  if( c != ESP8266_RESPONSE_OK )
    return -1;
  
  return ret;
}

ESP8266_RESPONSE ESP8266_SetTCPServerTimeout( int16_t time ){
  sprintf( aux, "=%d", time );
  
  esp8266_sendCommand( CMD_CIPSTO, aux );
  
  return esp8266_readResponse( NULL, 2000 );
  
}

int16_t ESP8266_Ping( const char *ip_or_address ){
  int16_t ret;
  esp8266_sendCommand( CMD_PING, ip_or_address );
  
  ret = esp8266_readUntil(aux, ENDL, NULL, 5000);
  
  ret = atoi( aux );
  
  if( esp8266_readUntil(NULL, RESPONSE[ESP8266_RESPONSE_OK], NULL, 1000) != 1 )
    return -1;
  
  return ret;
}