/// @file calctype.c
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

#include "platform.h"
#include <calctype.h>

unsigned int calctype_get_text_width(const struct CalcTypeFont *font,
	const char *text)
{
	// TODO(Natalie): Improve width calculation for multiline draws
	// (if (*text < 32 && (*text == '\n'))).
	unsigned int subpixel_width = 0;
	while (*text) {
		if (*text == 32) {
			subpixel_width += font->width;
		} else {
			unsigned short metadata_offset =
				font->metadata_offset[((int) *text) - 32];

			if (metadata_offset != 0xFFFF)
				subpixel_width += (
					(struct CalcTypeGlyphMetadata *)
					(font->data + metadata_offset)
					)->x_advance;
		}

		++text;
	}

	return subpixel_width / 3;
}

void calctype_draw(const struct CalcTypeFont *font, const char *text,
	unsigned int x, unsigned int y, unsigned short color,
	unsigned char *vram, unsigned int pitch)
{
	if (vram == 0)
		vram = calctype_get_vram();

	if (pitch == 0)
		pitch = calctype_get_default_pitch();

	unsigned int sub_x = x * 3;
	unsigned int start_x = sub_x;
	unsigned int max_x = pitch * 3;

	while (*text && sub_x < max_x)
	{
		if (*text == 32) {
			sub_x += font->width;
		} else if (*text < 32 && *text == '\n') {
			sub_x = start_x;
			y += font->height;
		} else {
			unsigned short metadata_offset =
				font->metadata_offset[((int) *text) - 32];

			if (metadata_offset != 0xFFFF) {
				struct CalcTypeGlyphMetadata *glyph =
					(struct CalcTypeGlyphMetadata *)
					(font->data + metadata_offset);

				calctype_draw_glyph(glyph,
					(sub_x + glyph->x_offset) / 3,
					y + glyph->y_offset,
					color,
					vram,
					pitch);

				sub_x += glyph->x_advance;
			}
		}

		++text;
	}
}
