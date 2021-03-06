/******************************************************************************
 * Copyright (C) 2018
 * Christopher Morroni and Matthew Haney
 * University of Colorado, Boulder
 *
 * Redistribution, modification, or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Christopher Morroni, Matthew Haney, and the University of
 * Colorado are not liable for any misuse of this material.
 *
 *****************************************************************************/
/**
 * @file main.c
 * @brief Main file for ECEN 5813
 *
 * @author Christopher Morroni
 * @date 01/30/2018
 */

#include <stdint.h>

#ifdef PROJECT1
#include "project1.h"
#endif
#ifdef PROJECT2
#include "project2.h"
#endif
#ifdef PROJECT3
#include "project3.h"
#endif
#ifdef PROJECT4
#include "project4.h"
#endif

int main()
{
#ifdef PROJECT1
  project1();
#endif
#ifdef PROJECT2
  project2();
#endif
#ifdef PROJECT3
  project3();
#endif
#ifdef PROJECT4
  project4();
#endif
  return 0;
}
