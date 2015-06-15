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
map_brightness(int br, int max_br)
{
	const int min_br = (int) floor(((double)min_brightness/100.0 * (double)max_br));
	const double factor = ((double)max_br/(double)(max_am_value));
	int calc_val = (int) floor( factor * br ) + min_br;

	if (calc_val > max_br)
		calc_val = max_br;

	return calc_val;
}

static int
read_max_brightness()
{
	int max_br = 0;
	FILE *f = fopen(bl_max_br_path, "r");

	if (f == NULL)
		err("can't open screen brightness file to write");
	if (fscanf(f, "%d", &max_br) < 1)
		err("can't write new brightness");

	fclose(f);
	return max_br;
}

static void
set_backlight(int br)
{
	FILE *f = fopen(bl_br_path, "w");
	if (f == NULL)
		err("can't open screen brightness file to write");
	if (fprintf(f, "%d", br) < 1)
		err("can't write new brightness");
	fclose(f);
}

int
main(void)
{
	int amb_light = 0;
	int new_br = 0;
	int old_br = 0;
	const int max_br = read_max_brightness();

	for (;;) {
		amb_light = read_ambient_light();

		new_br = map_brightness(amb_light, max_br);
		
		if (new_br != old_br) {
			set_backlight(new_br);
			old_br = new_br;
		}

		sleep(1);
	}
	return 0;
}
