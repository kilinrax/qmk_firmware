#RGB_MATRIX_ENABLE = yes
#RGB_MATRIX_DRIVER = IS31FL3731
#DRIVER_COUNT = 2

CONVERT_TO = promicro_rp2040
OLED_ENABLE = yes
OLED_DRIVER = SSD1306   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
MOUSEKEY_ENABLE = yes
SRC += features/caps_word.c
