# Board
This directory contains the code to blink the LED light on the Rasberry PI Pico. It's the pico's version of hello world :)

## Implementation
This project has three different functions that make the board LED blink:
* blink_easy()
    * Blink the LED using the pico SDK 
* blink_gpio()
    * Blink the LED controlling the GPIO memory address (OEOVER and OUTOVER) 
* blink_sio()
    * Blink the LED via SIO (single-cycle IO) by connecting GPIO pin 25 (LED) and controlling it through the SIO address segment

## Photos
#### Pin 25 set to low (500ms)
<img width="496" height="234" alt="Pico Light Off" src="https://github.com/user-attachments/assets/5df88c52-6b48-46d2-9a42-206c224cb98d" />

#### Pin 25 set to high (500ms)
<img width="480" height="203" alt="Pico Light On" src="https://github.com/user-attachments/assets/e7654a58-a84e-43fe-a32c-aa139f8eb601" />
