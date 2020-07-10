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

/********************************** Headers ***********************************/

/************************** Definition of Libraries ***************************/

#include <math.h>


/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "mcc_generated_files/system.h"
#include "communicate.h"
#include "filter.h"

/*********************** Definition of Public Functions ***********************/

/*FN****************************************************************************
*
*   float receive_float( char *array, int len, int entero )
*
*   Purpose: These function is used for converter array in float 
*            number
*
*   Parameters: 
*       - array:  array with numbers in ASCII
*       - len:    length of array
*       - entero: number of integer, the point is after this number
*
*   Origin:  Own design
*
*   Plan:    Simple function that does not need a plan description
*
*   Return:  Float number
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   May 28/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

float 
receive_float( char *array, int len, int entero )
{
int i = 0, exponent = 0;
float my_number = 0.0;
    
for( i = 0; i < len; i++ ){ 
    exponent = (i < entero) ? (entero-i-1) : ((-i) + (entero-1));
    my_number += (float)( array[i] - 48.0 ) * pow( 10.0, exponent );
}

return my_number;

} /* receive_float */


/*FN****************************************************************************
*
*   void send_float( float number, char *array )
*
*   Purpose: These function is used for converter float number in
*            ascii number
*
*   Parameters: 
*       - number: float number
*       - array:  array with numbers in ascii
*
*   Origin:  Own design
*
*   Plan:    Simple function that does not need a plan description
*
*   Return:  Nothing
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   May 28/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

void
send_float( float number, char *array )
{
int i = 0, temp = 0;

array[0] = ( number > 0.0 ) ? '+': '-';    
for( i = 0; i < 3; i++ ){ 
    temp = (int)(number / pow( 10.0, 2-i )) % 10;
    array[i+1] = (char)temp; 
    temp = (int)(number / pow( 10.0, -i-1 )) % 10;
    array[3+i+1] = (char)temp; 
}

} /* send_float */


/*FN****************************************************************************
*
*   float Get_V( uint8_t channel )
*
*   Parameter: 
*     - channel: Channel used
*
*   Purpose: These function is used for get V value after codification
*
*   Origin:  Own design
*
*   Plan:    1. Verify the channel of measure
*            2. Get the value of ADC for Voltage measure
*            3. Convert the ADC value to Volts [V] 
*
*   Return:  float
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 05/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

float
Get_V( uint8_t channel_voltage )
{
float Voltage = 0;

Max_v = ( channel_voltage == 1 ) ? MAX_V_CH1: MAX_V_CH2;
Voltage = ( (float)(Max_v) * (float)(V_ADC) ) / (float)(4096);

return Voltage;

} /* Get_V */


/*FN****************************************************************************
*
*   float Get_I()
*
*   Purpose: These function is used for get I value after codification
*
*   Origin:  Own design
*
*   Plan:    1. Get the value of ADC for Current measure
*            2. Convert the ADC value to Amperes [A] 
*
*   Return:  float
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 05/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

float
Get_I()
{
float Current = 0;
Current = ( (float)(MAX_I) * (float)(I_ADC) ) / (float)(4096);

return Current;

} /* Get_I */


/*FN****************************************************************************
*
*   float Get_T()
*
*   Purpose: These function is used for get T value after codification
*
*   Origin:  Own design
*
*   Plan:    1. Get the value of digital sensor (I2C) for Temperature measure
*            2. Convert the value to Celcius grades [°C] 
*
*   Return:  float
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 05/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

float
Get_T()
{
float Temperature = 0;    

Temperature = -46.85 + ( 175.72 * ((float)T_I2C / (float)65535) );

return Temperature;

} /* Get_T */


/*FN****************************************************************************
*
*   void Send_Data( float value_to_send, uint8_t ID )
*
*   Purpose: These function is used for send data with UART 
*
*   Origin:  Own design
*
*   Plan:    1. Convert data to send in ASCII vector
*            2. Create vector to send, with date
*            3. Send vector with all data
*            4. Raise flag to indicate if communication was ended
*
*   Return:  None
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 08/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/
void
Send_Data( float value_to_send, uint8_t ID )
{
char float_to_vect[7];
char vect_to_send[12];
uint8_t i = 0;

/*   1  ----------------- CONVERT DATA IN ASCII VECTOR ---------------------- */

send_float( value_to_send, float_to_vect );

/*   2  --------------- CREATE VECTOR TO SEND WITH DATE --------------------- */

for( i = 0; i < length( float_to_vect ); i++){
  vect_to_send[i] = float_to_vect[i];
}

vect_to_send[7] = ( char )current_Date.tm_mday;  // Get day of month [0-31]
vect_to_send[8] = ( char )current_Date.tm_mon;   // Get month [1-12]
vect_to_send[9] = ( char )current_Date.tm_hour;  // Get hour [1-12] PM format
vect_to_send[10] = ( char )current_Date.tm_min;  // Get minutes [1-60] 
vect_to_send[11] = ( char )current_Date.tm_sec;  // Get seconds [1-60]

/*   3  -------------------------- SEND DATA -------------------------------- */

for( i = 0; i < length( vect_to_send ); i++){
  if( UART1_IsTxReady() ){ 
    UART1_Write( vect_to_send[i] );
  }
}

/*   4  -------------------------- RAISE FLAGS ------------------------------ */

if( ID == 1 ){
  V_Was_Sent = 1;
} 
else if( ID == 2 ){
  I_Was_Sent = 1;
} else {
  T_Was_Sent = 1;
}

} /* Send_Data */


/*FN****************************************************************************
*
*   void Read_Data_In_Memory( void )
*
*   Purpose: These function is used for send with UART the data in memory
*
*   Origin:  Own design
*
*   Plan:    Simple plan, don't need explain it
*
*   Return:  None
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 05/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

void
Read_Data_In_Memory()
{

uint16_t address;
uint8_t  pData[11];
uint16_t nCount;

I2C1_MESSAGE_STATUS status;
uint8_t   writeBuffer[3];
uint16_t  counter, nCount;
uint8_t   *pD;

address = (base_register_table) - 11;
nCount = 11;
pD = pData;

for( counter = 0; counter < nCount; counter++ ){

  // build the write buffer first
  // starting address of the EEPROM memory
  writeBuffer[0] = 0xFF & (address >> 8);         // high address
  writeBuffer[1] = (uint8_t)(address);            // low address

  // write one byte to EEPROM (2 is the count of bytes to write)
  I2C1_MasterWrite( writeBuffer, 2, MEM_24LC128_ADDRESS, &status );

  // write one byte to EEPROM (2 is the count of bytes to write)
  I2C1_MasterRead( pD, 1, MEM_24LC128_ADDRESS, &status );
  
  pD++;
  address++;

  if( UART1_IsTxReady() ){ 
    UART1_Write( *pD );
  }

} /* for */

M_Was_Sent = 1;

} /* Read_Data_In_Memory */


/*FN****************************************************************************
*
*   void communicate()
*
*   Purpose: These function is used for communicate microcontroller
*            with PC, with serial protocol
*
*   Origin:  Own design
*
*   Plan:    See FSM attached and/or table in end of this code.
*
*   Return:  Nothing
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   May 28/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

void
communicate( float *Coeff )
{

/*----------------------------  Intern variables  ----------------------------*/
                       
typedef enum {                     
    INIT_ST,            /*     STATE 0     */
    COMMAND_ST,         /*     STATE 1     */
    SETUP_ST,           /*     STATE 2     */
    SIGN_SETUP_IIR_ST,  /*     STATE 3     */
    SETUP_IIR_ST,       /*     STATE 4     */
    DATA_ST,            /*     STATE 5     */
    VOLTAGE_ST,         /*     STATE 6     */
    CURRENT_ST,         /*     STATE 7     */
    TEMPERATURE_ST,     /*     STATE 8     */
    VOLTAGE_CH_ST       /*     STATE 9     */
} STATE_T;

typedef struct {
    char INIT_WORD;
    char SETUP_COM;
    char DATA_COM;
    char FILTER_MODULE;
    char POSITIVE;
    char NEGATIVE;
    char V_DATA;
    char I_DATA;
    char T_DATA;
    char CH1_V;
    char CH2_V;
    char END_COM;
} WORDS;

       float temp = 0.0;
static char  i = 0, ii = 0;
static float sign = 0.0;
static char  one_coeff[COEFF_DECIMALS];

/*----------------------  Initialize intern variables  -----------------------*/

static WORDS dictionary = { 
    .INIT_WORD = '#', 
    .SETUP_COM = 'C',
    .DATA_COM  = 'D',
    .FILTER_MODULE = 'F',
    .POSITIVE = '+',
    .NEGATIVE = '-',
    .V_DATA = 'V',
    .I_DATA = 'I',
    .T_DATA = 'T',
    .CH1_V = '1',
    .CH2_V = '2',
    .END_COM   = 'E'
};

static STATE_T state = INIT_ST;

/*----------------------------------------------------------------------------*/

if( 1 ){
    switch( state ){
        case INIT_ST:
            if( Incoming_Byte == dictionary.INIT_WORD ){
                state = COMMAND_ST;
            } else {
                state = INIT_ST;
            }
        break;
/*----------------------------------------------------------------------------*/
        case COMMAND_ST:

/*                  +=========+===========================+                   */
/*                  | Command |         Function          |                   */
/*                  +=========+===========================+                   */
/*                  |   'C'   |    Configurate modules    |                   */
/*                  +=========+===========================+                   */
/*                  |   'D'   |       Data request        |                   */
/*                  +=========+===========================+                   */
                        
            if( Incoming_Byte == dictionary.SETUP_COM ){          
                state = SETUP_ST;
            } 
            else if( Incoming_Byte == dictionary.DATA_COM ){
                state = DATA_ST;
            } else {
                state = INIT_ST;
            }
        break;
/*----------------------------------------------------------------------------*/
        case SETUP_ST:
            
/*                  +=========+===========================+                   */
/*                  | Command |         Function          |                   */
/*                  +=========+===========================+                   */
/*                  |   'F'   | Setup filter coefficients |                   */
/*                  +=========+===========================+                   */

            if( Incoming_Byte == dictionary.FILTER_MODULE ){
                state = SIGN_SETUP_IIR_ST;
            } else {
                state = INIT_ST;
            } 
          
        break;
/*----------------------------------------------------------------------------*/
        case SIGN_SETUP_IIR_ST:

/*                         +=====+=====+=====+=======+                        */
/*                         | '#' | 'C' | 'F' |  +/-  |                        */
/*                         +=====+=====+=====+=======+                        */

            if( Incoming_Byte == dictionary.POSITIVE ){
                sign = 1.0;
                state = SETUP_IIR_ST;
            } 
            else if( Incoming_Byte == dictionary.NEGATIVE ){
                sign = -1.0;
                state = SETUP_IIR_ST;
            } else {
                state = INIT_ST;
            }
          
        break;
/*----------------------------------------------------------------------------*/
        case SETUP_IIR_ST:

/*                      +=====+=====+=====+=======+=====+                     */
/*                      | '#' | 'C' | 'F' |  +/-  | ... |                     */
/*                      +=====+=====+=====+=======+=====+                     */

            one_coeff[i++] = Incoming_Byte;

            if( Incoming_Byte == dictionary.END_COM || i == COEFF_DECIMALS ){
                temp =  receive_float( one_coeff, length(one_coeff), 1 );
                Coeff[ii++] =  sign * temp;
                ii = ( ii == COEFF_ARRAY_LEN ) ? 0: ii;
                i = 0;
                sign = 0.0;
                state = INIT_ST;
            } else {
                state = SETUP_IIR_ST;
            } 
          
        break;
/*----------------------------------------------------------------------------*/
        case DATA_ST:

/*                  +=========+===========================+                   */
/*                  | Request |         Function          |                   */
/*                  +=========+===========================+                   */
/*                  |   'V'   |   Voltage data request    |                   */
/*                  +=========+===========================+                   */
/*                  |   'I'   |   Current data request    |                   */
/*                  +=========+===========================+                   */
/*                  |   'T'   | Temperature data request  |                   */
/*                  +=========+===========================+                   */

            if( Incoming_Byte == dictionary.V_DATA ){
                state = VOLTAGE_ST;
            } 
            else if( Incoming_Byte == dictionary.I_DATA ){
                state = CURRENT_ST;
            }
            else if( Incoming_Byte == dictionary.T_DATA ){
                state = TEMPERATURE_ST;
            } else {
                state = INIT_ST;
            }
          
        break;
/*----------------------------------------------------------------------------*/
        case VOLTAGE_CH_ST:

/*                         +=====+=====+=====+=======+                        */
/*                         | '#' | 'D' | 'V' |  1/2  |                        */
/*                         +=====+=====+=====+=======+                        */

            if( Incoming_Byte == dictionary.CH1_V ){
                CH = 1;
                state = VOLTAGE_ST;
            }
            else if( Incoming_Byte == dictionary.CH2_V ){
                CH = 2;
                state = VOLTAGE_ST;
            } else {
                state = INIT_ST;
            } 
          
        break;
/*----------------------------------------------------------------------------*/
        case VOLTAGE_ST:

            V_Was_Sent = 0;
            if( statusRTC == true ){
              V = Get_V( CH );           
              Vrms = IIR( V );           
              Send_Data( Vrms, 1 );         
            }

            if( V_Was_Sent == 1 ){
                state = INIT_ST;
            } else {
                state = VOLTAGE_ST;
            } 
          
        break;

/*----------------------------------------------------------------------------*/
        case CURRENT_ST:

/*                             +=====+=====+=====+                            */
/*                             | '#' | 'D' | 'I' |                            */
/*                             +=====+=====+=====+                            */

            I_Was_Sent == 0;
            if( statusRTC == true ){
              I = Get_I();           
              Irms = IIR( I );           
              Send_Data( Irms, 2 );         
            }

            if( I_Was_Sent == 1 ){
                state = INIT_ST;
            } else {
                state = CURRENT_ST;
            } 
          
        break;
/*----------------------------------------------------------------------------*/
        case TEMPERATURE_ST:

/*                             +=====+=====+=====+                            */
/*                             | '#' | 'D' | 'T' |                            */
/*                             +=====+=====+=====+                            */

            T_Was_Sent == 0;
            if( statusRTC == true ){
              T = Get_T();           
              Trms = IIR( T );           
              Send_Data( Trms, 3 );         
            }

            if( T_Was_Sent == 1 ){
                state = INIT_ST;
            } else {
                state = TEMPERATURE_ST;
            } 
          
        break;
    } /* switch */
} /* if */
} /* communicate */

/*******************************************************************************

+=============================================================================+
|                         MOVACT COMMUNICATION PROTOCOL                       |
+=========+===========+==========+====================================+=======+
|  START  |  COMMAND  |  MODULE  |               DATA                 |  END  |
+=========+===========+==========+=====+===+=====================+====+=======+
|         |     C     |     F    | +/- | 1 |        . . .        | 11 |       |
|         +===========+==========+=====+===+==+==================+====+       |
|         |           |           V           |          1/2          |       |
|    #    |           +=======================+=======================+   E   |
|         |     D     |                       I                       |       |
|         |           +===============================================+       |
|         |           |                       T                       |       |
+=========+===========+===============================================+=======+

*******************************************************************************/