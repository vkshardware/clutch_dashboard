This is a custom firmware for UPS 52Pi board. UPS for Raspberry Pi 4 B.

FEATURES (optimized for automotive application):

NO real-time clock, no I2C link used.
LOW idle current consumption (about 2.3 ma) - standby time approx 1.5 months without charging.
Simple shutdown line to Raspbery Pi (used 8 pin of RPi4)


FUNCTIONAL LOGIC:

When input (USB type C) voltage decrease trip level, after ~1 sec UPS send to RPi shutdown signal.
After it occured, MCU waits 5 seconds (RPi4 shutdown time) and power off 5V converter TPS61088.

When input voltage supplied, wakes up charger IP5328P and MCU turns on Raspberry Pi (load time 50 second). In any case MCU halt RPi4 safely.



MCU STM32F030F4P6
Environment: KEIL uVision 5 (used ARM compiler 6 version)


Programming interface: DEBUG 4-pin connector on the board


**************************
IMPORTANT
**************************

In outbox state UPS 52Pi has very high idle current (approx. 15 ma) and discharge 18650 batteries quickly.
To decrease current cosumption recommended sold out two INA219 chips and RTC DS1307.
Idle current in this case is 2.3 ma.
