//! \file keypad_tiva.c
//! \brief Functions for reading keypad.
//! \author Nguyen Trong Phuong (aka trongphuongpro)
//! \date 2020 April 8

#include "keypad.h"

#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>

static PortPin_t *rows;
static PortPin_t *columns;
static uint8_t number_of_rows;
static uint8_t number_of_columns;


uint8_t keymap[4][3] = {{'1', '2', '3'},
                        {'4', '5', '6'},
                        {'7', '8', '9'},
                        {'*', '0', '#'}};


void keypad_init(uint8_t n_row, uint8_t n_col) {
    number_of_columns = n_col;
    number_of_rows = n_row;
}


void keypad_setRows__(PortPin_t *array_of_rows) {
    rows = array_of_rows;

    // config rows as input
    for (uint8_t i = 0; i < number_of_rows; i++) {
        GPIOPinTypeGPIOInput(rows[i].base, rows[i].pin);
        GPIOPadConfigSet(rows[i].base, 
                        rows[i].pin, 
                        /* just place holder */ GPIO_STRENGTH_2MA,
                        /* weak pull-down resistor */ GPIO_PIN_TYPE_STD_WPD);
    }
}


void keypad_setColumns__(PortPin_t *array_of_cols) {
    columns = array_of_cols;

    // config columns as output
    for (uint8_t i = 0; i < number_of_columns; i++) {
        GPIOPinTypeGPIOOutput(columns[i].base, columns[i].pin);
        GPIOPinWrite(columns[i].base, columns[i].pin, 0);

    }
}


uint8_t keypad_read() {
    for (uint8_t col = 0; col < number_of_columns; col++) {
        GPIOPinWrite(columns[col].base, columns[col].pin, columns[col].pin);

        for (uint8_t row = 0; row < number_of_rows; row++) {
            uint8_t value = GPIOPinRead(rows[row].base, rows[row].pin);

            if (value) {
                // wait until this key is released
                // avoid multi-press
                while (GPIOPinRead(rows[row].base, rows[row].pin));
                return keymap[row][col];
            }
        }

        GPIOPinWrite(columns[col].base, columns[col].pin, 0);
    }

    return 0;
}