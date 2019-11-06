/**
 * @file            circular_buf.h
 * @author          Steven Daglish
 * @brief
 * @version         0.1
 * @date            30 July 2019
 */

// TODO: Check if circular_buf_struct definition can be hidden away in the .c
// file

#ifndef _CIRCULAR_BUF_H
#define _CIRCULAR_BUF_H

#include <stdbool.h>
#include <stdint.h>

typedef struct circular_buf_struct
{
  uint8_t capacity;
  uint8_t index;
  uint8_t outdex;
  uint8_t size;
  uint8_t *buf;
} circular_buf_struct;

typedef struct circular_buf_struct circular_buf_t;

/**
 * @brief   Returns a pointer to a circular buffer.
 *
 * This function is unable to dynamically create the array and circular buffer.
 * Therefore it is necessary for these to already be created and their pointers
 * to be passed in this function.
 *
 * The function will then add the address of the array into the circular
 * buffer's struct for later use.
 *
 * Example:
 * @code
 * const uint8_t buf_size = 8;
 * circular_buf_t circular_buf;
 * circular_buf_t * p__circular_buf = &circular_buf;
 * uint8_t p_buf_array[buf_size];
 *
 * p_circular_buf = circular_buf_create(buf_size, p_buf_array, p_circular_buf);
 * @endcode
 *
 * @param   capacity        Maximum size of the circular buffer (max 256)
 * @param   p_buf_array     Pointer to already created uint8_t array
 * @param   p_circular_buf  Pointer to circular buffer (this pointer will be
 * used to create the circular buffer)
 * @return  circular_buf_t* Pointer to the created circular buffer
 */
circular_buf_t *circular_buf_create(uint8_t capacity, uint8_t *p_buf_array,
                                    circular_buf_t *p_circular_buf);

// DONE Check if there is anything that can be done here, now I'm not using
// alloc
void circular_buff_destroy(circular_buf_t *self);

uint8_t circular_buf_capacity(circular_buf_t *self);

uint8_t circular_buf_get_index(circular_buf_t *self);

uint8_t circular_buf_get_outdex(circular_buf_t *self);

uint8_t circular_buf_add(circular_buf_t *self, uint8_t c);

uint8_t circular_buf_get(circular_buf_t *self);

bool circular_buf_is_empty(circular_buf_t *self);

bool circular_buf_is_full(circular_buf_t *self);

uint8_t circular_buf_size(circular_buf_t *self);

#endif // _CIRCULAR_BUF_H
