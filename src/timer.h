////////////////////////////////////////////////////////////////////////////////
//
// mock header file for timer.h
//
//  It is assumed that the timer is already set up and initialised.
//
//  Only required functions are included as needed.

#ifndef _TIMER_H
#define _TIMER_H

/**
 * @brief   Returns the number of milliseconds that have passed since the program 
 *          has started.
 * @note    Will roll-over after 49.7 days.
 */
uint32_t millis(void);

#endif

