#include <msp430.h>
#include "libTimer.h"
#include "led.h"

int main(void) {
  P1DIR |= LEDS; // Set LED pins as outputs
  P1OUT &= ~LEDS; // Ensure all LEDs are initially turned off

  configureClocks(); // Setup master oscillator, CPU & peripheral clocks
  enableWDTInterrupts(); // Enable periodic interrupt
  
  or_sr(0x18); // CPU off, GIE on
}

// Global state variables
int greenBlinkLimit = 5; // Duty cycle for green LED
int redBlinkLimit = 5; // Duty cycle for red LED
int greenBlinkCount = 0; // Counter for green LED
int redBlinkCount = 0; // Counter for red LED
int secondCount = 0; // Counter for seconds

void __interrupt_vec(WDT_VECTOR) WDT() {
  // Handle green LED blinking
  greenBlinkCount++;
  if (greenBlinkCount >= greenBlinkLimit) {
    greenBlinkCount = 0;
    P1OUT ^= LED_GREEN; // Toggle green LED
  }
  
  // Handle red LED blinking
  redBlinkCount++;
  if (redBlinkCount >= redBlinkLimit) {
    redBlinkCount = 0;
    P1OUT ^= LED_RED; // Toggle red LED
  }
  
  // Increment second counter
  secondCount++;
  
  // Modify blink duty cycle once each second
  if (secondCount >= 250) {
    secondCount = 0;
    
    // Change the blink duty cycle for green LED (dim-to-bright)
    greenBlinkLimit++;
    if (greenBlinkLimit > 10) // Maximum duty cycle
      greenBlinkLimit = 5; // Reset to dim
  
    // Change the blink duty cycle for red LED (bright-to-dim)
    redBlinkLimit--;
    if (redBlinkLimit < 0) // Minimum duty cycle
      redBlinkLimit = 5; // Reset to bright
  }
}


