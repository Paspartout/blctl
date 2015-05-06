/* See LICENSE file for license details. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "config.h"

static int
err(const char *msg)
{
	fprintf(stderr, "error: %s\n", msg);
	exit(1);
}

static int
read_ambient_light()
{
	FILE *f = fopen(am_sensor_path, "r");
	int level = 0;
	int tmp = 0;

	if (f == NULL)
		err("can't open sensor file");
	if (fscanf(f, "(%d,%d)", &level, &tmp) == EOF)
		err("can't scan ambient light level");

	fclose(f);

	return level;
}

static int
map_brightness(int br)
{
	const double factor = ((double)max_br_value/(double)(max_am_value));
	int calc_val = (int) ceil( factor * br ) + min_brightness;
	if(calc_val > max_br_value)
		calc_val = max_br_value;
	return calc_val;
}

void
set_brightness(int br)
{
	FILE *f = fopen(screen_brightness_path, "w");
	if(f == NULL)
		err("can't open screen brightness file to write");
	if (fprintf(f, "%d", br) < 1)
		err("can't write new brightness");
	fclose(f);
}

int
main(int argc, char *argv[])
{
	int amb_light = 0;
	int new_br = 0;

	for (;;) {
		amb_light = read_ambient_light();

		new_br = map_brightness(amb_light);

		set_brightness(new_br);

		sleep(1);
	}
	return 0;
}
