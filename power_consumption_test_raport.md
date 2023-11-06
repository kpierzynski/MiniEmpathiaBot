part | voltage | current | notes
-- | -- | -- | -- 
ws2812b x8 | 5V | 0.092A | R (255)
ws2812b x8 | 5V | 0.046A | R (127)
ws2818b x8 | 5V | 0.092A | G (255)
ws2812b x8 | 5V | 0.046A | G (127)
ws2818b x8 | 5V | 0.092A | B (255)
ws2818b x8 | 5V | 0.046A | B (127)
ws2818b x8 | 5V | 0.183A | RG (255)
ws2818b x8 | 5V | 0.183A | RB (255)
ws2818b x8 | 5V | 0.184A | GB (255)
ws2818b x8 | 5V | 0.273A | RGB (255)
ws2818b x8 | 5V | 0.136A | RGB (127)
ws2818b x8 | 5V | 0.068A | RGB (63) (too bright to look at)
ws2818b x8 | 5V | 0.034A | RGB (31) (clearly visible from distance)
ws2818b x8 | 5V | 0.016A | RGB (15) (might be too dim, depends on external light)
| | | | |
n20 motor | 5V | 0.140A +- 0.020A | free running
n20 motor | 5V | 0.370A +- 0.050A | trying a bit to stall with hand
n20 motor | 5V | 0.800A +- 0.100A | trying to stall hard
| | | | |
Rpi Zero 2 W + Camera v3 | 5V | 0.121A | Legacy 64bit Lite Raspbian + idle + connected SSH
Rpi Zero 2 W + Camera v3 | 5V | 0.279A +- 0.020A | Legacy 64bit Lite Raspbian + stream camera video over tcp
Rpi Zero 2 W + Camera v3 | 5V | 0.412A +- 0.020A | Legacy 64bit Lite Raspbian + stream camera vide over tcp + load core with python3 sum loop
Rpi Zero 2 W + Camera v3 | 5V | 0.656A +- 0.020A | Legacy 64bit Lite Raspbian + load all 4 cores
Rpi Zero 2 W + Camera v3 | 5V | peak: 0.857A, typical: 0.450A - 0.650A | Legacy 64bit Raspbian (+desktop) + openCV ArUco detection
Rpi Zero 2 W + Camera v3 | 5V | 0.050A | shutdown
| | | | |
VL53L0X | 3.3V | 0.021A | high accuracy mode (25ms between readings)
VL53L0X | 3.3V | 0.018A | continous mode (25ms between readings)
VL53L0X | 3.3V | 0.005A | high speed mode (25ms between readings)
| | | | |
NUCLEO L152RE dev board | 5V | 0.058A | whole nucleo with 10Hz blink program on HAL
| | | | |
Motor encoder | 3.3V | 0.003A | -
| | | | |
U3V70A | 3.0V | 0.00056A | standby step up current
U3V70A | 3.3V | 0.0005A | standby step up current
U3V70A | 3.7V | 0.00045A | standby step up current
U3V70A | 4.2V | 0.00039A | standby step up current
| | | | |
RPI + 2 motors + WS2812B | 3V (on step up) | 2.6A - 2.8A  (to step up) | RPI all cores stressed, WS2812B RGB 127, 2 motors constantly spinnig with rapid direction change
