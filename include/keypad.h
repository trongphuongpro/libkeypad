//! \file keypad.h
//! \brief Functions for reading keypad.
//! \author Nguyen Trong Phuong (aka trongphuongpro)
//! \date 2020 April 8


#ifndef __KEYPAD__
#define __KEYPAD__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "utils_tiva.h"

void keypad_init(uint8_t n_row, uint8_t n_col);
uint8_t keypad_read();
void keypad_setRows__(PortPin_t *array_of_rows);
void keypad_setColumns__(PortPin_t *array_of_cols);

#define keypad_setRows(...)     keypad_setRows__((PortPin_t[]){__VA_ARGS__})
#define keypad_setColumns(...)  keypad_setColumns__((PortPin_t[]){__VA_ARGS__})


#ifdef __cplusplus
}
#endif

#endif /* __KEYPAD__ */