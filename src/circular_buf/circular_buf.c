#include "circular_buf.h"

static uint8_t inc_address(uint8_t address, uint8_t capacity) {
  // TODO: Optimise this. It's messy which is currently not needed.
  uint8_t new_address = 0;
  if ((address + 1) < capacity) {
    new_address = address + 1;
  }
  return new_address;
}

// TODO Optimise index and outdex to be pointers instead of array indices
// TODO See if this can be cleared up a bit, using less parameters (without
// using alloc)
circular_buf_t *circular_buf_create(uint8_t capacity, uint8_t *p_buf_array,
                                    circular_buf_t *p_circular_buf) {
  circular_buf_t *self = p_circular_buf;

  self->buf = p_buf_array;
  self->capacity = capacity;
  self->index = 0;
  self->outdex = 0;
  self->size = 0;

  return self;
}

void circular_buff_destroy(circular_buf_t *self) {
  // DONE Remove commented out lines if no longer being used!
}

uint8_t circular_buf_capacity(circular_buf_t *self) { return self->capacity; }

uint8_t circular_buf_get_index(circular_buf_t *self) { return self->index; }

uint8_t circular_buf_get_outdex(circular_buf_t *self) { return self->outdex; }

uint8_t circular_buf_size(circular_buf_t *self) { return self->size; }

uint8_t circular_buf_add(circular_buf_t *self, uint8_t c) {
  if (false == circular_buf_is_full(self)) {
    self->buf[self->index] = c;
    self->index = inc_address(self->index, self->capacity);
    self->size++;
    return 1;
  }
  return 0;
}

uint8_t circular_buf_get(circular_buf_t *self) {
  if (circular_buf_is_empty(self)) {
    return 0;
  }
  uint8_t c = self->buf[self->outdex];
  self->outdex = inc_address(self->outdex, self->capacity);
  self->size--;
  return c;
}

bool circular_buf_is_empty(circular_buf_t *self) {
  // TODO: See if I can remove the comment below
  // if (self->index == self->outdex)
  if (self->size == 0) {
    return true;
  }
  return false;
}

bool circular_buf_is_full(circular_buf_t *self) {
  // TODO: See if I can remove this comment below
  // if (inc_address(self->index, self->capacity) == self->outdex)
  if (self->size == self->capacity) {
    return true;
  }
  return false;
}