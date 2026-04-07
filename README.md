# Pico Projects: :parking::heavy_exclamation_mark::copyright::o:
This repo contains all of the pico projects I have worked on. My goal is to make embedded programming a hobby because I'm interested in bare metal c programming. Also, with AI on the rise, this is my way of keeping skills fresh.

## Libraries
I have added a library called baremetalc that will be used for implementations of code used across projects. An example is milli_wait() and micro_wait(). These are functions I created in place of the SDK's sleep functions.
Although I'm interested in baremetal c programming, I do include the pico sdk during the cmake process to pull in the default runtime behaviors (ie: _exit)

## Projects
When I have completed a project, I will list it here with a description of what it does.
* **Board**
    * SDK, GPIO, and SIO control of the board's LED
