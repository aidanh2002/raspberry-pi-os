#ifndef PERIPHERALS_UART_H                   // Avoid duplicate register definitions.
#define PERIPHERALS_UART_H                   // Mark this header as included.

#include "peripherals/base.h"                // Reuse the Pi 3 peripheral base address.

#define UART0_BASE (PBASE + 0x00201000U)      // PL011 UART0 base: 0x3F201000 on Pi 3.
#define UART0_DR (UART0_BASE + 0x00U)        // Transmit/receive data register.
#define UART0_FR (UART0_BASE + 0x18U)        // FIFO and transmitter status flags.
#define UART0_IBRD (UART0_BASE + 0x24U)      // Integer baud-rate divisor.
#define UART0_FBRD (UART0_BASE + 0x28U)      // Fractional baud-rate divisor.
#define UART0_LCRH (UART0_BASE + 0x2CU)      // Frame format and FIFO control.
#define UART0_CR (UART0_BASE + 0x30U)        // UART, transmitter, receiver enables.
#define UART0_IMSC (UART0_BASE + 0x38U)      // Interrupt mask register.
#define UART0_ICR (UART0_BASE + 0x44U)       // Interrupt clear register.
#define UART0_DMACR (UART0_BASE + 0x48U)     // DMA control register.

#define UART0_FR_BUSY (1U << 3)             // Set while transmission is in progress.
#define UART0_FR_RXFE (1U << 4)             // Set when the receive FIFO is empty.
#define UART0_FR_TXFF (1U << 5)             // Set when the transmit FIFO is full.
#define UART0_LCRH_FEN (1U << 4)            // Enable the receive and transmit FIFOs.
#define UART0_LCRH_WLEN_8 (3U << 5)         // Select eight data bits per character.
#define UART0_CR_UARTEN (1U << 0)           // Enable the UART itself.
#define UART0_CR_TXE (1U << 8)              // Enable the transmitter.
#define UART0_CR_RXE (1U << 9)              // Enable the receiver.

#endif                                     // End the header guard.
