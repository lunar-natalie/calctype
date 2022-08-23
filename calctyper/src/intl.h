/// @file intl.h
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Internationalization utility.
/// @version 0.1
/// @date 2022-08-23
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

#include <libintl.h>

/// @brief Shorthand for gettext.
/// Looks up MSGID in the current default message catalog for the current
/// LC_MESSAGES locale. If not found, returns MSGID itself (the default text).
#define _(s) gettext(s)
