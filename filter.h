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

#ifndef FILTER_H
#define FILTER_H


/********************* Declaration of symbolic constants **********************/

#define ORDER_IIR 4
#define COEFF_ARRAY_LEN 5*(ORDER_IIR/2)   


/************************* Declaration of data type ***************************/

/*-----------------------  Data type for IIR filter  -------------------------*/

typedef struct IIR_T IIR_T;
struct IIR_T {
    float Coeff[COEFF_ARRAY_LEN];
};

/********************** Declaration of Global variable ************************/

IIR RMS;      // IIR filter to get RMS values

/************************** Prototypes of Functions ***************************/

/* ---------------------------- Public Functions ---------------------------- */

int   Coeff_Ready( void );
float IIR( float input );

#endif /* FILTER_H */
