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
*                                  Jul - 2020                                  *
*                                                                              *
*******************************************************************************/

/********************************** Headers ***********************************/

/************************** Definition of Libraries ***************************/

#include "mcc_generated_files/system.h"
#include "communicate.h"
#include "filter.h"

/********************* Declaration of symbolic constants **********************/

#define THIRTY_SECONDS 30   
#define FIVE_MINUTES 300  

#define SHT21_ADDRESS 0x80        // slave device address - sensor SHT21
#define MEM_24LC128_ADDRESS 0xA0  // slave device address - memory 24LC128


/********************** Declaration of Global variable ************************/

/* --------------------------------- System --------------------------------- */
uint16_t base_register_table = 0;
float V, I, T;
float Vrms, Irms, Trms; 

/* ---------------------------------- Time ---------------------------------- */
int five_minutes_counter = 0;
int thirty_seconds_counter = 0;

/* ----------------------------------- ADC ---------------------------------- */
uint16_t V_ADC,
uint16_t I_ADC;
uint16_t sl0ResultBuffer[2];   // Retorno de medidas de ADC [0] V - [1] I
uint8_t tableregindex;
uint8_t slsize;

/* --------------------------- Timer 1 y Timer 2 ---------------------------- */
bool statusTimer1;
bool statusTimer2;

/* ----------------------------------- RTC ---------------------------------- */
bool statusRTC;
struct tm current_Date;

/* ------------------------------- SHT21 - I2C ------------------------------ */
uint16_t T_I2C;


/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

void ADC_Setup( void );
void Read_ADC_When_Timer_Elapsed( void );
void Read_I2C_SHT21_After_30_seconds( void );
void Get_Date( void );
void Write_Data_In_Memory_After_5_Minutes( void );


/************************* Definition of Main Function ************************/

/*FN****************************************************************************
*
*   int main( void )
*
*   Purpose: Main function
*
*   Origin:  Own design
*
*   Plan:    1. Initialize device and peripheral
*            2. While loop:
*                 - Read ADC (Voltage and Current) with fs = 3 kHz
*                 - Read Temperature of SHT21 every 30 s
*                 - Read Date of RTC every 1 s
*                 - Read UART Incoming data 
*                 - Execute MOVACT FSM 
*                 - Write all data in memory every 5 minutes 
*
*   Return:  None
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 09/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

int 
main(void)
{

/*   1  ---------------- INITIALIZE DEVICE AND PERIPHERAL ------------------- */

  SYSTEM_Initialize();
  ADC_Setup();
  TMR1_Start();
  TMR2_Start();

/*   2  -------------------------- WHILE LOOP ------------------------------- */

  while(1){

    Read_ADC_When_Timer1_Elapsed();
    Read_I2C_SHT21_After_30_seconds();
    Get_Date();
    if( UART1_IsRxReady() ){
      Incoming_Byte = UART1_Read();
    }
    communicate( RMS.Coeff );
    Write_Data_In_Memory_After_5_Minutes();

  } /* while */
} /* main */


/*********************** Definition of Public Functions ***********************/

/*FN****************************************************************************
*
*   void ADC_Setup( void )
*
*   Purpose: Configure ADC channels and control parameters
*
*   Origin:  Example of MCC (See padc1.h)
*
*   Plan:    Simple plan, it don't need explain it.
*
*   Return:  None
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 09/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

void 
ADC_Setup( void )
{

  PADC1_SAMPLELISTCONFIG slconfig;
  uint8_t adcChannel1 = 1; // AN7  Voltage channel
  uint8_t adcChannel2 = 7; // AN2  Current channel

  tableregindex = 0;
  slsize = 2;              // Single list size

  //Disable sample list
  PADC1_SampleList0Disable();

  PADC1_SetADCChannel( tableregindex, adcChannel1, false ); // Voltage channel
  PADC1_SetADCChannel( tableregindex, adcChannel2, false ); // Current channel

  // set up values for sample list
  slconfig.trigger_src =0; //manual
  slconfig.chargetime =5;
  slconfig.autoscan = true;
  slconfig.slsize = 2;
  //set the values for sample list and enable the list
  PADC1_SampleList0Setup(&slconfig);
  PADC1_SampleList0ManualConversionStart();

} /* ADC_Setup */


/*FN****************************************************************************
*
*   void Read_ADC_When_Timer_Elapsed( void )
*
*   Purpose: Read ADC values of coltage and current, this reading is make
*            every 333 us (3 kHz, frequency sampling) controlled for TIMER 1
*
*   Origin:  Own design
*
*   Plan:    1. Check if Timer 1 elapsed
*            2. Get ADC values of voltage and current
*
*   Return:  None
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 09/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

void 
Read_ADC_When_Timer_Elapsed( void )
{
  if( (statusTimer1 = TMR1_GetElapsedThenClear()) == true){
    if( PADC1_SampleList1ConversionResultBufferGet( sl0ResultBuffer, 
                                                      tableregindex, 
                                                              slsize ){
      V_ADC = sl0ResultBuffer[0];
      I_ADC = sl0ResultBuffer[1];
    }
  }
} /* Read_ADC_When_Timer_Elapsed */


/*FN****************************************************************************
*
*   void Read_I2C_SHT21_After_30_seconds( void )
*
*   Purpose: Read SHT1 temperature value, this reading is make every 30 s, 
*            controlled for thirty_second_counter (software timer) based on
*            timer of 1 s (TIMER 2)
*
*   Origin:  Own design
*
*   Plan:    See communication with sensor (In datasheet)
*
*   Return:  None
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 09/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

void
Read_I2C_SHT21_After_30_seconds( void )
{
  const uint8t TempHoldCmd = 0xE3; // // Trigger T measurement - hold master 
  I2C1_MESSAGE_STATUS status;
  uint8_t writeBuffer[2];
  uint8_t pD[2];

  if( thirty_seconds_counter == THIRTY_SECONDS ){
    thirty_seconds_counter = 0;

    // build the write buffer first
    writeBuffer[0] = TempHoldCmd; 

    // write one byte to SHT21
    I2C1_MasterWrite( writeBuffer, 1, SHT21_ADDRESS, &status);

    if (status == I2C1_MESSAGE_COMPLETE){
        // write one byte (to read) to SHT21
        I2C1_MasterRead( pD, 2, SHT21_ADDRESS, &status);
    } 
  } /* if */

  T_I2C = ( ( pD[0] << 8 ) | pD[1] ) & ~(0x0003);

} /* Read_I2C_SHT21_After_30_seconds */


/*FN****************************************************************************
*
*   void Get_Date( void )
*
*   Purpose: Read RTC value, this reading is make every 1 s, controlled 
*            for TIMER 2, the date and hour is returned in "current_Date"
*            it's a tm struct. Do two "software timers" based in TIMER 2
*            of 1 second 
*
*   Origin:  Own design
*
*   Plan:    Simple plan, it don't need explain it
*
*   Return:  None
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 09/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

void 
Get_Date( void )
{
  if( (statusTimer2 = TMR2_GetElapsedThenClear()) == true ){
    statusRTC = ( RTCC_TimeGet( &current_Date ) ) ? 1: 0;
    thirty_seconds_counter++;
    five_minutes_counter++;
  }
} /* Get_Date */



/*FN****************************************************************************
*
*   void Write_Data_In_Memory_After_5_Minutes( void )
*
*   Purpose: Write voltage, current, temperature, date and hour every 5 minutes 
*            controlled for five_minutes_counter (software timer) based on
*            timer of 1 s (TIMER 2)
*
*   Origin:  Own design
*
*   Plan:    See communication with sensor (In datasheet)
*
*   Return:  None
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jul 09/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

void
Write_Data_In_Memory_After_5_Minutes( void )
{
  uint8_t V_MSB, V_LSB,
          I_MSB, I_LSB,
          T_MSB, T_LSB,
          day, month, hour, min, sec; 

  if( five_minutes_counter == FIVE_MINUTES ){

    V_MSB = ( 0xFF & (V_ADC >> 8) );       // V_ADC MSB 
    V_LSB = ( 0xFF & V_ADC );              // V_ADC LSB
    I_MSB = ( 0xFF & (I_ADC >> 8) );       // I_ADC MSB
    I_LSB = ( 0xFF & I_ADC );              // I_ADC LSB
    T_MSB = ( 0xFF & (T_I2C >> 8) );       // T_I2C MSB
    T_LSB = ( 0xFF & T_I2C );              // T_I2C LSB
    day   = ( char )current_Date.tm_mday;  // Get day of month [0-31]
    month = ( char )current_Date.tm_mon;   // Get month [1-12]
    hour  = ( char )current_Date.tm_hour;  // Get hour [1-12] PM format
    min   = ( char )current_Date.tm_min;   // Get minutes [1-60] 
    sec   = ( char )current_Date.tm_sec;   // Get seconds [1-60]

    base_register_table = 0; 

    // write to an EEPROM Device
    uint16_t dataAddress;
    uint8_t  sourceData[16] = { V_MSB, V_LSB, I_MSB, I_MSB, T_MSB, T_LSB,
                                day, month, hour, min, sec }; 

    uint8_t   *pData;
    uint16_t  nCount;
    uint8_t   writeBuffer[3];
    uint8_t   *pD;
    uint16_t  counter;

    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;

    dataAddress = base_register_table;      // starting EEPROM address 
    pD = sourceData;                        // initialize the source of the data
    nCount = 11;                            // number of bytes to write

    for (counter = 0; counter < nCount; counter++){

      // build the write buffer first
      // starting address of the EEPROM memory
      writeBuffer[0] = 0XFF & (dataAddress >> 8);         // high address
      writeBuffer[1] = (uint8_t)(dataAddress);            // low address

      // data to be written
      writeBuffer[2] = *pD++;

      // write one byte to EEPROM (3 is the number of bytes to write)
      I2C1_MasterWrite(  writeBuffer, 3, MEM_24LC128_ADDRESS, &status);
      dataAddress++;

    } /* for */
  } /* if */
} /* Write_Data_In_Memory_After_5_Minutes */