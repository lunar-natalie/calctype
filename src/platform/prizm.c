/// @file prizm.c
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Platform-specific rendering utilities for the Casio Prizm.
/// @version 0.1
/// @date 2022-08-22
///
/// @copyright Copyright (c) 2022 The CalcType Authors.
/// This program is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include "../platform.h"
#include "calctype.h"

#include <fxcg/display.h>

unsigned char *calctype_get_vram(void)
{
	return (unsigned char *) GetVRAMAddress();
}

unsigned int calctype_get_default_pitch(void)
{
	return LCD_WIDTH_PX;
}

void calctype_draw_glyph(struct CalcTypeGlyphMetadata *glyph, unsigned int x,
	unsigned int y, unsigned short color, unsigned char *vram,
	unsigned int pitch)
{
	unsigned short *dest = (((unsigned short *) vram) + x) + (y * pitch);
	unsigned char *data = glyph->data;
	int increment = pitch - glyph->width;

	// In order for the fast interpolation to work, the inverse of each mask
	// value must also be the inverse of the bit value to prevent color
	// overlap.
	static const unsigned short red_mask[8] = {
		0b0000000000000000,
		0b0011100000000000,
		0b0101100000000000,
		0b0111100000000000,
		0b1000000000000000,
		0b1010000000000000,
		0b1100000000000000,
		0b1111100000000000
	};

	static const unsigned short green_mask[8] = {
		0b0000000000000000,
		0b0000000111100000,
		0b0000001011000000,
		0b0000001111100000,
		0b0000010000000000,
		0b0000010100100000,
		0b0000011000000000,
		0b0000011111100000
	};

	static const unsigned short blue_mask[4] = {
		0b0000000000000000,
		0b0000000000001111,
		0b0000000000010000,
		0b0000000000011111
	};

	for (int gy = 0; gy < glyph->height; ++gy) {
		for (int gx = 0; gx < glyph->width; ++gx, ++dest, ++data) {
			unsigned short screen = *dest;
			unsigned short current_data = data[0];
			unsigned short inv_current_data = ~current_data;

			unsigned short new_data;
			// Mask in draw color.
			new_data = color & red_mask[(current_data & 0xE0) >> 5];
			new_data |= color & green_mask[(current_data & 0x1C) >> 2];
			new_data |= color & blue_mask[current_data & 0x03];
			// Mask out screen color.
			new_data |= screen & red_mask[(inv_current_data & 0xE0) >> 5];
			new_data |= screen & green_mask[(inv_current_data & 0x1C) >> 2];
			new_data |= screen & blue_mask[inv_current_data & 0x03];

			*dest = new_data;
		}

		dest += increment;
	}
}
