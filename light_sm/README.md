# Light State Machine
The goal of this project was to interact with the pico's state machines. It lights up four LEDs connected to a breadboard.

## Implementation
* light_sm.pio
    * Pio Assembler program to turn on and off a pin given an input to osr
* light_sm.c
    * Configures GPIO pins to PIO0
    * Configures PIO0 and loads the light_sm.pio program into memory
    * Configures PIO0's four state machines and turns them on
    * Sends bits through the TX FIFO registers to the state machines
    * Also blinks the board's LED every .5 seconds

* LED Logic
    * Wait 200 ms
    * LED 1 turns on
    * Wait 200 ms
    * LED 2 turns on
    * Wait 3000 ms
    * LED 3 turns on
    * Wait 200 ms
    * LED 4 turns on
    * Wait 200 ms
    * Turn off all LEDs

* Physical Setup
    * Contents: 
        * 4x LED
        * 4x Resistors
        * 9x Wires
    * Layout
        * GPIO 1 -> 1k Resistor -> LED -> Ground (pin 38)
        * GPIO 2 -> 1k Resistor -> LED -> Ground (pin 38)
        * GPIO 3 -> 1k Resistor -> LED -> Ground (pin 38)
        * GPIO 4 -> 1k Resistor -> LED -> Ground (pin 38)
        * Note: Why a 1k ohm resistor? No clue! Just guessing here.


