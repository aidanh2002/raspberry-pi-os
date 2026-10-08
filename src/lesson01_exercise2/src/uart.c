/* PL011 replacement for the Mini UART interface in Matyukevich's Lesson 1. */
#include "uart.h"                           // UART functions and clock/baud constants.
#include "utils.h"                          // Existing ARM register access and delay.
#include "peripherals/uart.h"               // PL011 register addresses and bit masks.
#include "peripherals/gpio.h"               // Existing GPIO register addresses.

void uart_send(char c)                      // Send one byte through PL011 UART0.
{                                          // Begin the transmit function.
    while (get32(UART0_FR) & UART0_FR_TXFF) {// Wait while the transmit FIFO is full.
    }                                      // Continue when a FIFO slot is available.
    put32(UART0_DR, (unsigned char)c);      // Write the character into the UART.
}                                          // End the transmit function.

char uart_recv(void)                       // Receive one byte through PL011 UART0.
{                                          // Begin the receive function.
    while (get32(UART0_FR) & UART0_FR_RXFE) {// Wait while the receive FIFO is empty.
    }                                      // Continue when a character is available.
    return (char)(get32(UART0_DR) & 0xFFU); // Keep the eight received data bits.
}                                          // End the receive function.

void uart_send_string(const char *str)      // Send a string using the byte function.
{                                          // Begin the string function.
    for (unsigned int i = 0; str[i] != '\0'; i++) { // Stop at the null terminator.
        uart_send(str[i]);                  // Transmit the current character.
    }                                      // Advance to the next character.
}                                          // End the string function.

void uart_init(void)                       // Set up GPIO14/15 and the PL011 UART.
{                                          // Begin the initialization function.
    unsigned int selector;                 // Hold a copy of GPIO function selections.
    unsigned int divisor_times_64;         // Hold the rounded baud divisor in 1/64 units.

    put32(UART0_CR, 0U);                    // Disable the UART before reconfiguration.
    while (get32(UART0_FR) & UART0_FR_BUSY) {// Wait for any current transmission to finish.
    }                                      // Continue once the transmitter is idle.
    put32(UART0_LCRH, 0U);                  // Clear FIFO enable and flush old transmit data.

    selector = get32(GPFSEL1);              // Read GPIO10-19 function settings.
    selector &= ~(7U << 12);               // Clear the GPIO14 function field.
    selector |= (4U << 12);                // Select ALT0: GPIO14 becomes TXD0.
    selector &= ~(7U << 15);               // Clear the GPIO15 function field.
    selector |= (4U << 15);                // Select ALT0: GPIO15 becomes RXD0.
    put32(GPFSEL1, selector);               // Apply both UART pin selections.

    put32(GPPUD, 0U);                      // Select no GPIO pull-up or pull-down.
    delay(150);                            // Allow the pull-control setting to settle.
    put32(GPPUDCLK0, (1U << 14) | (1U << 15)); // Clock that setting into GPIO14/15.
    delay(150);                            // Allow the pin settings to settle.
    put32(GPPUDCLK0, 0U);                  // Finish the GPIO pull-control sequence.

    put32(UART0_IMSC, 0U);                 // Mask interrupts; this driver uses polling.
    put32(UART0_DMACR, 0U);                // Disable DMA; characters are handled by the CPU.
    put32(UART0_ICR, 0x7FFU);              // Clear any pending UART interrupt flags.

    /* round(64 * clock / (16 * baud)) = round(4 * clock / baud). */
    divisor_times_64 = (4U * UART_CLOCK_HZ + UART_BAUD_RATE / 2U)
                       / UART_BAUD_RATE;   // Use integer arithmetic to round the divisor.
    put32(UART0_IBRD, divisor_times_64 / 64U); // Integer divisor: 26 at 115200 baud.
    put32(UART0_FBRD, divisor_times_64 % 64U); // Fractional divisor: 3 at 115200 baud.
    put32(UART0_LCRH, UART0_LCRH_WLEN_8 | UART0_LCRH_FEN); // Set 8N1 and enable FIFOs.
    put32(UART0_CR, UART0_CR_UARTEN | UART0_CR_TXE | UART0_CR_RXE); // Enable UART, TX, RX.
}                                          // End the initialization function.
