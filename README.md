# uart_2_controller

Module to control the uart_2 module. 

The controller is at a higher level than the uart_2_driver. The driver module contains the HAL and will be specific to the PIC in use, while this control module is at a higher level. As a result, it should be possible to use this module on all PIC24 devices (and possibly PIC16 devices, but this has not been tested).

## Notes


## Installation


## Usage

### Using the circular buffer

The circular buffer can be used to allow non-blocking tx and rx. The circular buffers are set up during init, and there capacity is set in the TX_BUF_SIZE and RX_BUF_SIZE.

To send a string to tx, add all the chars to the tx cir buf (the call will need doing for each char). Then, at regular intervals, call update_tx to send the next char to the tx_reg. update_tx will check if there is space in the tx_reg and if there is anything to send.

```c
char string_to_send[] = "Hello World.\n";
uint8_t string_size = 13;
uint8_t i = 0;

for (i = 0; i < string_size; i++)
{
    uart_2_controller_add_char_to_cir_buf(string_to_send[i]);
}

// The following will be called at regular intervals elsewhere in the code
update_tx();
```

To receive data via the circular buffer, update_rx will need to be called at regular intervals. This will update the rx cir buf when there is data in the rx_reg and there is space in the rx cir buf. rx_buf_size and read_cir_buf_char can then be used to get the data from the cir buf.

```c
// The following will be called at regular intervals. It is possible that data will be lost if the function is not called often enough, depending on the size of the FIFO buffer on the PIC.
update_rx();

// The following will be called when the data is required.
char recieved_string[32];
uint8_t string_size = 0;
string_size = uart_2_controller_rx_buf_size();

for (i = 0; i < string_size; i++)
{
    recieved_string[i] = uart_2_controller_read_cir_buf_char();
}
```

## Testing

All functionality is tested using Ceedling. Ceedling will need to be installed prior to being called.

```
ceedling
```

## History

### 11th September 2019

* millis_integration branch created for testing timeouts on reading strings

### 11th December 2019

The module has now been updated to include a circular buffer for both tx and rx. This means that it is now possible to have tx and rx running async without blocking. It does not run with any kind of interrupt, so the functions will need to be run at regular intervals to make sure that rx and tx are updated as needed.

The circular buffers are created during init. The rx circular buffer will be updated during update_rx, and will need reading as needed. The tx circular buffer will need data manually sending to it and will send the data to tx_reg when update_tx is called.




