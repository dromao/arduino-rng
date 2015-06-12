Arduino True Random Number Generator
----

Originally developed by Rob Seward. I have extended the code in order to provide the following extra features:

- Support for a second PN juntion noise generator
- Support for the watchdog timer jitter-based noise generator provided by the Entropy library
- New raw byte output mode
- Continuous calibration
- Support for a second serial interface for logging messages
- Send log messages, such as baseline values, mode of operation, etc, over the second serial interface

The following modes of operation are supported:

- Single PN junction
- Dual PN junction
- Jitter
- Single PN junction + Jitter
- Dual PN Junction + Jitter

Dependencies:

Entropy library: https://sites.google.com/site/astudyofentropy/project-definition/timer-jitter-entropy-sources/entropy-library

Original instructions below:

Instructions for constructing the circuit can be found here: http://robseward.com/misc/RNG2/

### Eagle Files

These are **UNTESTED**. (I designed the PCB but never got around to building it. If you make one, please let me know of any mistakes – or better yet make a pull request!)
