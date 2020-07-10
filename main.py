''' Ruler 1         2         3         4         5         6         7        '

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
*****************************************************************************'''

import warnings
import serial
import serial.tools.list_ports
import time
import math
import numpy as np
import csv

################################################################################
def abrirPuertoArduino(timeout=2,defaultport=0,baudrate=115200,sleep=2):
    arduino_ports = [ 
    p.device 
    for p in serial.tools.list_ports.comports() 
     if 'Arduino' in str(p.description)+str(p.manufacturer) 
     ]# si no entiende esta lineas pitonica ver: https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions 
    if not arduino_ports:
        raise IOError("No se encontraron arduinos")
        exit()#algo extremo, pero funciona al cerrar la aplicacion
    if len(arduino_ports) > 1:
        warnings.warn('Se encontraron multiples arduinos Usando el '+str(defaultport))
    print(arduino_ports[defaultport])
    ser = serial.Serial(port=arduino_ports[defaultport],baudrate=baudrate,timeout=timeout)# Ver https://pyserial.readthedocs.io/en/latest/pyserial_api.html
    time.sleep (sleep)#esperando por el serial
    return ser

################################################################################
def enviarYrecibirbytes(ser,datos):
    if isinstance(datos, list):
        print("Enviando lista")
        byteList=bytearray(datos)
        for bits in byteList:
            
            ser.write(bytes([bits])) #es necesario hacer de nuevo bytes([bits]) o se puede usar solo bits
            rx=ser.read(1) #tiene echo activado por lo que espera el dato que se envia
            print("enviando "+str(bits)+" Recibiendo: ",rx)
    else:
        print("No soportado")

################################################################################
def cerrarPuerto(ser):
    if ser.isOpen():
        ser.close()
    else:
        warnings.warn('Ya estaba cerrado el puerto',ser)

################################################################################
def datosEnColaRx(ser):
    return ser.in_waiting()

################################################################################
def coeff_to_array( coeficientes, decimales = 6 ):

    for i in range(len(coeficientes)):
        l = list()
        sign = '+' if (coeficientes[i] > 0) else '-' 
        l.append(sign)
        for j in range(decimales+1):    
            x = int(abs(coeficientes[i]) / pow(10,-j)) % 10
            l.append(x) 
        m.append(l)
        del l

    return m

################################################################################
def receive_float( array, cifras = 3 ):

    my_number = 0 
    for i in range(len(array)):
        exponent = (cifras-i-1) if ( i < cifras ) else ( (-i) + (cifras-1) ) 
        my_number += int(array[i]) * pow( 10, exponent );

    return my_number

################################################################################
if __name__ == "__main__":
