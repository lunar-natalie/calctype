/// @file calctype_platform.h
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Platform-specific rendering utilities.
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

#include "calctype.h"

/// @return Pointer to start of video memory.
unsigned char *calctype_get_vram(void);

/// @return Default number of monospaced glyphs per inch on the display.
unsigned int calctype_get_default_pitch(void);

/// @brief Writes a font glyph into video memory.
/// @param metadata
/// @param x x-coordinate.
/// @param y y-coordinate.
/// @param color
/// @param vram Start of video memory.
/// @param pitch Number of monospaced glyphs per inch.
void calctype_draw_glyph(struct CalcTypeGlyphMetadata *glyph, unsigned int x,
	unsigned int y, unsigned short color, unsigned char *vram,
	unsigned int pitch);
