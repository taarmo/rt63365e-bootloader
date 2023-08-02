#include "../PureDOOM.h"
#include "../../../src/utils.h"
#include "../../../src/regdef.h"
#include "../../../src/lcd.h"
#include "../../../src/uart.h"
#include "../../../src/spi.h"

u32 time_init = 0;
#define WIDTH 320
#define HEIGHT 200
#define SCALE 1

// Resolution of the SDL window
#define FULL_WIDTH (WIDTH * SCALE)
#define FULL_HEIGHT (int)(HEIGHT * 1.2 * SCALE) // 1.2x higher than DOOM's height. Original game was

void send_midi_msg(uint32_t midi_msg) {}

static uint16_t rgb888torgb565(unsigned char *rgb888Pixel)
{
	unsigned char red   = rgb888Pixel[0];
	unsigned char green = rgb888Pixel[1];
	unsigned char blue  = rgb888Pixel[2];
	return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);

}

void play_doom() {
	static u16 framebuffer[200][320];
	//u32 mouse_motion_x = 0;
	//u32 mouse_motion_y = 0;

	memset(framebuffer, 0xffff, sizeof(framebuffer));
	mfc0(time_init, C0_COUNT, 0);
	//adjust_clk_spi(0x1);
	init_lcd();
	setRotation(3);

	doom_set_default_int("key_up",          DOOM_KEY_W);
	doom_set_default_int("key_down",        DOOM_KEY_S);
	doom_set_default_int("key_strafeleft",  DOOM_KEY_A);
	doom_set_default_int("key_straferight", DOOM_KEY_D);
	doom_set_default_int("key_use",         DOOM_KEY_E);
	doom_set_default_int("mouse_move",      0); // Mouse will not move forward
	doom_set_resolution(WIDTH, HEIGHT);
	// Initialize doom
	doom_init(0, (char *)"", DOOM_FLAG_MENU_DARKEN_BG);
	
	while (1) {
		//u16* buffer = doom_get_sound_buffer();
		//u32 midi_msg;
		//while ((midi_msg = doom_tick_midi()) != 0) send_midi_msg(midi_msg);
		//doom_mouse_move(mouse_motion_x * 4, mouse_motion_y * 4);
		doom_update();
		unsigned char* src = doom_get_framebuffer(3);
		static unsigned char* prev_src;
		for (s16 y = 0; y < 200; ++y) {
			for (s16 x = 0; x < 320; x++) {
				u16 px = rgb888torgb565(src);
				if (framebuffer[y][x] != px) {
					drawPixel(x, y, px);
					framebuffer[y][x] = px;
				}
				src+=3;
			}
		}
	}
	
}

