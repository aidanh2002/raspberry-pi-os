/* Lesson 1 greeting and echo loop, adapted to use the PL011 driver. */
#include "uart.h"                          // Use the PL011 interface instead of Mini UART.

void kernel_main(void)                    // Enter here after the original startup code.
{                                         // Begin the kernel entry function.
    uart_init();                          // Initialize PL011 UART0 and its GPIO pins.
    uart_send_string("Hello, world!\r\n");  // Preserve the original Lesson 1 greeting.
    uart_send_string("Lesson 1 Exercise 2: PL011 UART0, 8N1\r\n"); // Identify this exercise.
    uart_send_string("Type characters to test receive and transmit.\r\n"); // Explain echo test.

    while (1) {                           // Keep the bare-metal kernel running.
        uart_send(uart_recv());            // Receive a character and echo it back.
    }                                     // Repeat the serial echo loop.
}                                         // End the kernel entry function.
