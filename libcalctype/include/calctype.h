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

/// @brief Main font data structure.
struct CalcTypeFont {
	// Height of the font line, in pixels.
	unsigned int height;

	// y-offset of the font line, in pixels.
	unsigned int base;

	// Width of each glyph, in sub-pixels.
	unsigned int width;

	// Glyph data and metadata. Data is encoded in RGB bytes of 3:4:1 for
	// each pixel. Metadata is stored in the format of
	// struct CalcTypeGlyphMetadata.
	const unsigned char *data;

	// Offset of the metadata of each glyph in the font data, minus 32.
	// 0xFFFF if unavailable.
	unsigned short metadata_offset[224];
};

/// @brief Font glyph metadata.
struct CalcTypeGlyphMetadata {
	// x-offset, in sub-pixels.
	signed char x_offset;

	// y-offset, in pixels.
	signed char y_offset;

	// Offset to add to the x-coordinate for the next glyph.
	unsigned char x_advance;

	// Width, in pixels.
	unsigned char width;

	// Height, in pixels.
	unsigned char height;

	// Internal helper pointer for glyph data.
	unsigned char data[1];
};

#ifdef __cplusplus
extern "C"
#endif
/// @brief Gets the displayed width of a string using the given font.
/// @param font
/// @param text
/// @return Width, in pixels.
unsigned int calctype_get_text_width(const struct CalcTypeFont *font,
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
/// @param vram Start of video memory. Use 0 to specify platform defaults.
/// @param pitch Number of monospaced glyphs per inch. Use 0 to specify platform
/// defaults.
void calctype_draw(const struct CalcTypeFont *font, const char *text,
	unsigned int x, unsigned int y, unsigned short color,
	unsigned char *vram, unsigned int pitch);
