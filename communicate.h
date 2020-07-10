/* Ruler 1         2         3         4         5         6         7        */

/*******************************************************************************
*                                                                              *
*     /$$      /$$   /$$$$$$   /$$    /$$   /$$$$$$    /$$$$$$   /$$$$$$$$     *
*    | $$$    /$$$  /$$__  $$ | $$   | $$  /$$__  $$  /$$__  $$ |__  $$__/     *
*    | $$$$  /$$$$ | $$  \ $$ | $$   | $$ | $$  \ $$ | $$  \__/    | $$        *
*    | $$ $$/$$ $$ | $$  | $$ |  $$ / $$/ | $$$$$$$$ | $$          | $$        *
*    | $$  $$$| $$ | $$  | $$  \  $$ $$/  | $$__  $$ | $$          | $$        *
*    | $$\  $ | $$ | $$  | $$   \  $$$/   | $$  | $$ | $$    $$    | $$        *
*    | $$ \/  | $$ |  $$$$$$/    \  $/    | $$  | $$ |  $$$$$$/    | $$        *
*    |__/     |__/  \______/      \_/     |__/  |__/  \______/     |__/        *
*                                                                              *
*         /$$$$$$   /$$$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$   /$$              *
*        /$$__  $$ | $$_____/ | $$__  $$ |_  $$_/  /$$__  $$ | $$              *
*       | $$  \__/ | $$       | $$  \ $$   | $$   | $$  \ $$ | $$              *
*       |  $$$$$$  | $$$$$    | $$$$$$$/   | $$   | $$$$$$$$ | $$              *
*        \____  $$ | $$__/    | $$__  $$   | $$   | $$__  $$ | $$              *
*        /$$  \ $$ | $$       | $$  \ $$   | $$   | $$  | $$ | $$              *
*       |  $$$$$$/ | $$$$$$$$ | $$  | $$  /$$$$$$ | $$  | $$ | $$$$$$$$        *
*        \______/  |________/ |__/  |__/ |______/ |__/  |__/ |________/        *
*                                                                              *
*                                                                              *
*                  Developed by:                                               *
*                                                                              *
*                            Jhon Hader Fernandez                              *
*                     - jhon_fernandez@javeriana.edu.co                        *
*                                                                              *
*                            Laura Katherine Henao                             *
*                        - laurahenao@javeriana.edu.co                         *
*                                                                              *
*                           Juan Sebastian Palacios                            *
*                      - palacios_juan@javeriana.edu.co                        *
*                                                                              *
*                                                                              *
*                       Pontificia Universidad Javeriana                       *
*                            Bogota DC - Colombia                              *
*                                  May - 2020                                  *
*                                                                              *
*******************************************************************************/

#ifndef COMMUNICATE_H
#define COMMUNICATE_H

/**************************** Definition of Macros ****************************/

/*MC****************************************************************************
*
*   length( array_pointer )
*
*   Purpose:   Return length of array.
*
*   Register of Revisions (Debugging Process):
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   May 28/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

#define length( array_pointer )\
(uint8_t)( sizeof(array_pointer)/sizeof(array_pointer[0]) )


/************************* Declaration of data type ***************************/

/*-------------------  Data type for registers: 1 byte  ----------------------*/

typedef unsigned char uint8_t;


/********************* Declaration of symbolic constants **********************/

#define COEFF_DECIMALS 11  // Total coefficients of 4th order IIR filter


/********************** Declaration of Global variable ************************/

uint8_t Incoming_Byte;     // Reading buffer
uint8_t CH;                // Channel of voltaje

uint8_t V_Was_Sent = 0,    // Flag to indicate Voltage was sent 
        I_Was_Sent = 0,    // Flag to indicate Current was sent
        T_Was_Sent = 0;    // Flag to indicate Temperature was sent

uint8_t MAX_V_CH1;         /* Maximum value of measure of voltage 
                              channel 1 (Hardware) --> Theoricaly 180Vp */ 
uint8_t MAX_V_CH2;         /* Maximum value of measure of voltage 
                              channel 2 (Hardware) --> Theoricaly 20Vp */
uint8_t MAX_I;             /* Maximum value of measure of current
                              Theoricaly 10Ip */
uint8_t MAX_T;             /* Maximum rates of measure of temperature
                              Theoricaly -40°C - 100°C */


/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

float receive_float( char *array, int len, int entero );
void  send_float( float number, char *array );
float Get_V( uint8_t channel_voltage );
float Get_I( void );
float Get_T( void );
void  Send_Data( float value_to_send, uint8_t ID );
void  Read_Data_In_Memory( void );
void  communicate( float *Coeff );

#endif /* COMMUNICATE_H */