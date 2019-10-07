#ifndef _XC_H
#define _XC_H

#include <stdint.h>

#define __extension__

#define U2MODE U2MODE
extern volatile uint16_t U2MODE; // __attribute__((__sfr__));
__extension__ typedef struct tagU2MODEBITS {
    union {
        struct {
            uint16_t STSEL : 1;
            uint16_t PDSEL : 2;
            uint16_t BRGH : 1;
            uint16_t URXINV : 1;
            uint16_t ABAUD : 1;
            uint16_t LPBACK : 1;
            uint16_t WAKE : 1;
            uint16_t UEN : 2;
            uint16_t : 1;
            uint16_t RTSMD : 1;
            uint16_t IREN : 1;
            uint16_t USIDL : 1;
            uint16_t : 1;
            uint16_t UARTEN : 1;
        };
        struct {
            uint16_t : 1;
            uint16_t PDSEL0 : 1;
            uint16_t PDSEL1 : 1;
            uint16_t : 1;
            uint16_t RXINV : 1;
            uint16_t : 3;
            uint16_t UEN0 : 1;
            uint16_t UEN1 : 1;
        };
    };
} U2MODEBITS;
extern volatile U2MODEBITS U2MODEbits; // __attribute__((__sfr__));

#define U2STA U2STA
extern volatile uint16_t U2STA; // __attribute__((__sfr__));
__extension__ typedef struct tagU2STABITS {
    union {
        struct {
            uint16_t URXDA : 1;
            uint16_t OERR : 1;
            uint16_t FERR : 1;
            uint16_t PERR : 1;
            uint16_t RIDLE : 1;
            uint16_t ADDEN : 1;
            uint16_t URXISEL : 2;
            uint16_t TRMT : 1;
            uint16_t UTXBF : 1;
            uint16_t UTXEN : 1;
            uint16_t UTXBRK : 1;
            uint16_t URXEN : 1;
            uint16_t UTXISEL0 : 1;
            uint16_t UTXINV : 1;
            uint16_t UTXISEL1 : 1;
        };
        struct {
            uint16_t : 6;
            uint16_t URXISEL0 : 1;
            uint16_t URXISEL1 : 1;
        };
    };
} U2STABITS;
extern volatile U2STABITS U2STAbits; // __attribute__((__sfr__));

#define U2BRG U2BRG
extern volatile uint16_t U2BRG; // __attribute__((__sfr__)?^^);

#define U2RXREG U2RXREG
extern volatile uint16_t U2RXREG; // __attribute__((__sfr__));

#define U2TXREG U2TXREG
extern volatile uint16_t U2TXREG; // __attribute__((__sfr__));

////////
// Deside if the code below can be removed as it is not used

#define TRISB TRISB
extern volatile uint16_t TRISB; // __attribute__((__sfr__));
typedef struct tagTRISBBITS {
    uint16_t TRISB0 : 1;
    uint16_t TRISB1 : 1;
    uint16_t TRISB2 : 1;
    uint16_t TRISB3 : 1;
    uint16_t TRISB4 : 1;
    uint16_t : 2;
    uint16_t TRISB7 : 1;
    uint16_t TRISB8 : 1;
    uint16_t TRISB9 : 1;
    uint16_t TRISB10 : 1;
} TRISBBITS;
extern volatile TRISBBITS TRISBbits; // __attribute__((__sfr__));

#define LATB LATB
extern volatile uint16_t LATB; // __attribute__((__sfr__));
typedef struct tagLATBBITS {
    uint16_t LATB0 : 1;
    uint16_t LATB1 : 1;
    uint16_t LATB2 : 1;
    uint16_t LATB3 : 1;
    uint16_t LATB4 : 1;
    uint16_t : 2;
    uint16_t LATB7 : 1;
    uint16_t LATB8 : 1;
    uint16_t LATB9 : 1;
    uint16_t LATB10 : 1;
} LATBBITS;
extern volatile LATBBITS LATBbits; // __attribute__;((__sfr__));''',.

#endif // _XC_H
