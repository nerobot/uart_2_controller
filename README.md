# uart_2_controller

Module to control the uart_2 module. 

The controller is at a higher level than the uart_2_driver. The driver module contains the HAL and will be specific to the PIC in use, while this control module is at a higher level. As a result, it should be possible to use this module on all PIC24 devices (and possibly PIC16 devices, but this has not been tested).

## Notes


## Installation


## Usage


## Testing

All functionality is tested using Ceedling. Ceedling will need to be installed prior to being called.

```
ceedling
```

## History

### 11th September 2019

* millis_integration branch created for testing timeouts on reading strings

