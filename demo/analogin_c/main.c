/*
 * libmanyuc - Turn leds on in C example
 * Copyright (C) 2012 - Margarita Manterola Rivero
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#include "libmanyuc.h"
#include <stdio.h>
#include <stdlib.h>

/* This example reads two sensors, using the ADC3 and ADC4.
   To do that, the pins in P9 and P10 have to be turned on.
   The output read is sent through the serial port and the
   pins P20 and P30 are turned on or off according to the value. */

int main(void) {

#ifdef DEBUG
    Serial_t port = Serial_Init(0, 9600);
    char cadena[10];
#endif

    uint32_t p = AnalogIn_Get(ADC4);
    uint32_t q = AnalogIn_Get(ADC3);

    Pin_t sensor1 = Pin_Get(P9);
    Pin_t sensor2 = Pin_Get(P10);

    Pin_t light1 = Pin_Get(P20);
    Pin_t light2 = Pin_Get(P30);

    Pin_Output(sensor1);
    Pin_Output(sensor2);
    Pin_Output(light1);
    Pin_Output(light2);

    Pin_On(sensor1);
    Pin_On(sensor2);

    while (1) {
        uint16_t s1 = AnalogIn_Read(p);

#ifdef DEBUG
        // Send the value through the serial port
        snprintf(cadena, 10, "%d\r\n", s1);
        Serial_Put_Bytes(port, cadena, 6, BLOCKING);
#endif

        // Turn light on
        if (s1 < 2000) {
            Pin_On(light1);
        } else {
            Pin_Off(light1);
        }

        wait(0.001);
        uint16_t s2 = AnalogIn_Read(q);

#ifdef DEBUG
        // Send the value through the serial port
        snprintf(cadena, 10, "%d\r\n", s2);
        Serial_Put_Bytes(port, cadena, 6, BLOCKING);
#endif

        if (s2 < 2000) {
            Pin_On(light2);
        } else {
            Pin_Off(light2);
        }
        wait(0.1);
    }
}
// vim:expandtab:smartindent:tabstop=4:softtabstop=4:shiftwidth=4:
