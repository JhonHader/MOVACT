/* Ruler 1         2         3         4         5         6         7        */

/*******************************************************************************
*                                                                              *
*          /$$$$$$$$  /$$$$$$  /$$     /$$$$$$$$  /$$$$$$$$  /$$$$$$$          *
*         | $$_____/ |_  $$_/ | $$    |__  $$__/ | $$_____/ | $$__  $$         *
*         | $$         | $$   | $$       | $$    | $$       | $$  \ $$         *
*         | $$$$$      | $$   | $$       | $$    | $$$$$    | $$$$$$$/         *
*         | $$__/      | $$   | $$       | $$    | $$__/    | $$__  $$         *
*         | $$         | $$   | $$       | $$    | $$       | $$  \ $$         *
*         | $$        /$$$$$$ | $$$$$$$$ | $$    | $$$$$$$$ | $$  | $$         *
*         |__/       |______/ |________/ |__/    |________/ |__/  |__/         *
*                                                                              *
*     /$$$$$$$$  /$$$$$$  /$$$$$$$              /$$$$$$  /$$$$$$  /$$$$$$$     *
*    | $$_____/ |_  $$_/ | $$__  $$            |_  $$_/ |_  $$_/ | $$__  $$    *
*    | $$         | $$   | $$  \ $$              | $$     | $$   | $$  \ $$    *
*    | $$$$$      | $$   | $$$$$$$/   /$$$$$$    | $$     | $$   | $$$$$$$/    *
*    | $$__/      | $$   | $$__  $$  |______/    | $$     | $$   | $$__  $$    *
*    | $$         | $$   | $$  \ $$              | $$     | $$   | $$  \ $$    *
*    | $$        /$$$$$$ | $$  | $$             /$$$$$$  /$$$$$$ | $$  | $$    *
*    |__/       |______/ |__/  |__/            |______/ |______/ |__/  |__/    *
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
*                                  Jun - 2020                                  *
*                                                                              *
*******************************************************************************/

/********************************** Headers ***********************************/

/* ------------------------ Inclusion of Own Headers ------------------------ */

#include "filter.h"


/*********************** Definition of Public Functions ***********************/

/*FN****************************************************************************
*
*   float IIR( int input )
*
*   Purpose: These function is IIR filter 4 order, Direct Form II
*
*   Parameters: 
*       - input: Input to filter
*
*   Origin:  Own design
*
*   Plan:    1. IIR order 2, Direct Form II
*            2. IIR order 2, Direct Form II
*
*   Return:  Float
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jun 01/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

float 
IIR( float input )
{
static float v[3], w[3];  
float x_i = 0, y = 0, y1 = 0;

x_i = (float)input;  

/* -------------------------------- SECTION 1 ------------------------------- */
x_i  = x_i*IIR_coeff[0];
v[0] = x_i - IIR_coeff[1]*v[1] - IIR_coeff[2]*v[2];
y1   = v[0] + IIR_coeff[3]*v[1] + IIR_coeff[4]*v[2];
v[2] = v[1];
v[1] = v[0];

/* -------------------------------- SECTION 2 ------------------------------- */
y1   = y1*IIR_coeff[5];
w[0] = y1 - IIR_coeff[6]*w[1] - IIR_coeff[7]*w[2];
y    = w[0] + IIR_coeff[8]*w[1] + IIR_coeff[9]*w[2];
w[2] = w[1];
w[1] = w[0];
  
return y; 

} /* IIR */


/*FN****************************************************************************
*
*   int Coeff_Ready( void )
*
*   Purpose: These function is for verify all coefficients was setup
*
*   Origin:  Own design
*
*   Plan:    Simple function that does not need a plan description
*
*   Return:  boolean
*
*   Register of Revisions:
*
*   DATE       RESPONSIBLE    COMMENT
*   -----------------------------------------------------------------------
*   Jun 01/20  J.H.Fernandez  Initial implementation
*
*******************************************************************************/

int 
Coeff_Ready( void )
{
int verify = 0;

verify = ( RMS.Coeff[COEFF_ARRAY_LEN-1] != 0 ) ? 1: 0;
return verify;

} /* Coeff_Ready */