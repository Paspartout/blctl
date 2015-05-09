/* configs for amient light sensor */
#define am_sensor_path "/sys/devices/platform/applesmc.768/light"
static const int max_am_value = 255;

/* configs for backlight device */
#define backlight_path "/sys/class/backlight/acpi_video0"

/* you usually don't have to modify the following two defines */
#define bl_max_br_path backlight_path "/max_brightness"
#define bl_br_path backlight_path "/brightness"

/* defines the desired minimum brightness(brightness boost) in percent */
static const int min_brightness = 30;

/* update rate in seconds */
static const int update_rate = 1;
