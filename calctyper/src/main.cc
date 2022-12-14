/// @file main.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Entry point to CalcTyper, the font generator for CalcType.
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

#include "logger.h"
#include "options.h"

#include <clocale>

#include <libintl.h>

int main(int argc, char* argv[])
{
	// Initialize internationalization.
	std::setlocale(LC_ALL, "");
	textdomain("calctyper");

	// Initialize the log interface.
	Logger::init();

	// Perform procedures based on options.
	return parse_options(argc, argv);
}
