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

part | voltage | current | notes
-- | -- | -- | -- 
n20 | 5V | 0.140A +- 0.020A | free running
n20 | 5V | 0.370A +- 0.050A | trying a bit to stall with hand
n20 | 5V | 0.800A +- 0.100A | trying to stall hard

part | voltage | current | notes
-- | -- | -- | -- 
Rpi Zero 2 W + Camera v3 | 5V | 0.121A | idle + connected SSH
Rpi Zero 2 W + Camera v3 | 5V | 0.279A +- 0.020A | stream camera video over tcp
Rpi Zero 2 W + Camera v3 | 5V | 0.412A +- 0.020A | stream camera vide over tcp + load core with python3 sum loop
Rpi Zero 2 W + Camera v3 | 5V | 0.656A +- 0.020A | load all 4 cores
Rpi Zero 2 W + Camera v3 | 5V | 0.050A | shutdown
