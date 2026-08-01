idf_component_register(
SRCS "blinky.c"
INCLUDE_DIRS "."
REQUIRES led_strip 
REQUIRES esp_driver_gpio
)
