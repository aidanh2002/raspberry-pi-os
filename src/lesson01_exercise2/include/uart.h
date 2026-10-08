#ifndef UART_H                         // Avoid duplicate declarations.
#define UART_H                         // Mark this header as included.

#define UART_CLOCK_HZ 48000000U        // PL011 input clock: 48 MHz.
#define UART_BAUD_RATE 115200U         // Match this rate in the serial terminal.

void uart_init(void);                  // Configure GPIO and the PL011 UART.
char uart_recv(void);                  // Wait for and receive one character.
void uart_send(char c);                // Wait for space and send one character.
void uart_send_string(const char *str);// Send a null-terminated string.

#endif                                // End the header guard.
