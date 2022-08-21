/// @file calctype.h
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Typeface and imaging library for color graphic calculators.
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

#pragma once

#include <fxcg/display.h>

/// @brief Main font data structure.
struct CalcTypeFont {
	// Height of the font line in pixels.
	unsigned int height;

	// y-offset of the font line.
	unsigned int base;

	// Width of each character in sub-pixels.
	unsigned int width;

	// Character data.
	const unsigned char *data;

	// Offset between each char in the character data, minus 32. 0xFFFF if
	// not available.
	unsigned short data_offset[224];
};

#ifdef __cplusplus
extern "C"
#endif
/// @brief Gets the displayed width of a string using the given font.
/// @param font
/// @param text
/// @return Width in pixels.
unsigned int calctype_get_text_width(const struct CalcTypeFont &font,
	const char *text);

#ifdef __cplusplus
extern "C"
#endif
/// @brief Writes text into video memory.
/// @param font
/// @param text
/// @param x x-coordinate of first character.
/// @param y y-coordinate of first character.
/// @param color
/// @param vram Start of video memory. Use 0 to specify device defaults.
/// @param pitch Use 0 to specify device defaults.
void calctype_draw(const struct CalcTypeFont &font, const char *text,
	unsigned int x, unsigned int y, color_t color, color_t *vram,
	unsigned int pitch);
