/// @file options.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Program options parser.
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

#include "config.h"
#include "intl.h"
#include "logger.h"
#include "options.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/program_options/errors.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

namespace po = boost::program_options;

/// @brief Stores data for a program option.
/// Used as a dynamic container for boost::program_options (po).
class Option {
public:
	/// @brief Constructs a new Option object.
	/// @param long_name Long-format option name.
	/// @param description Describes the functionality of the option.
	/// @param short_name Short-format option name.
	Option(const char* long_name, const char* description,
		const char* short_name = "")
		: long_name{long_name}, description{description},
		short_name{short_name}
	{
	}

	/// @brief Gets the full name of the option to add to a description.
	/// Uses the format 'LONG' or 'LONG,SHORT' for use with
	/// po::options_description::add_options.
	/// @return Full name (internal data).
	const char* name() noexcept;

	/// @brief Gets the number of occurrences of the option in a variables
	/// map.
	/// Used with a notified variables map containing parsed option data.
	/// @param vm Variables map of long-format option names to values.
	/// @return Number of occurrences.
	size_t count(po::variables_map vm) const noexcept
	{
		return vm.count(long_name);
	}

	const char* long_name;
	const char* description;
	const char* short_name;

private:
	std::string internal_name;
};

/// @brief Stores data for a positional program option.
/// Used as a dynamic container for boost::program_options.
/// @tparam T Value type.
template<typename T>
class PositionalOption {
public:
	/// @brief Constructs a new PositionalOption object.
	/// Stores option data for use with po.
	/// @param name
	PositionalOption(const char* name, int max_count = 1)
		: internal_name{name}, max_count{max_count}
	{
	}

	/// @brief Gets the identifier of the option.
	/// @return Name (internal data).
	const char* name() const noexcept
	{
		return internal_name.c_str();
	}

	/// @return Maximum allowed number of occurences for the option.
	int get_max_count() const noexcept
	{
		return max_count;
	}

	/// @brief Gets the number of occurrences of the option in a variables
	/// map.
	/// Used with a notified variables map containing parsed option data.
	/// @param vm Variables map of long-format option names to values.
	/// @return Number of occurrences.
	size_t count(po::variables_map vm) const noexcept
	{
		return vm.count(internal_name);
	}

	/// @brief Gets the value of the option from a variables map.
	/// Used with a notified variables map containing parsed option data.
	/// @param vm Variables map of long-format option names to values.
	/// @return Value.
	T value(po::variables_map vm) const
		noexcept
	{
		return vm[internal_name].as<T>();
	}

private:
	std::string internal_name;
	int max_count;
};

const char* Option::name() noexcept
{
	if (std::strlen(short_name) > 0) {
		std::stringstream ss;
		ss << long_name << "," << short_name;
		internal_name = ss.str();
		return internal_name.c_str();
	} else {
		return long_name;
	}
}

namespace options {
	Option output_name(
		_("output-name"),
		_("name to prefix output header and source files with"),
		_("o")
	);
	Option output_dir(
		_("output-dir"),
		_("directory to output header and source files into"),
		_("d")
	);
	Option help(
		_("help"),
		_("display this help and exit"),
		_("h")
	);
	Option version(
		_("version"),
		_("display version information and exit"),
		_("V")
	);
	PositionalOption<std::string> input_file(
		_("input-file")
	);
}

/// @brief Displays version information.
/// Prints version, copyright, and author information to stdout.
void show_version() noexcept
{
    	std::cout << _("CalcTyper ") << config::version_major << "." << config::version_minor << std::endl
        	<< _("Copyright (c) ") << config::version_year << _(" The CalcType Authors.") << std::endl
              	<< _("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.") << std::endl
              	<< _("This is free software: you are free to change and redistribute it.") << std::endl
              	<< _("There is NO WARRANTY, to the extent permitted by law.") << std::endl
              	<< std::endl
              	<< _("Written by tswilliamson, Peter Marheine, and Natalie Wiggins.") << std::endl;
}

int parse_options(int argc, char* argv[]) noexcept
{
	if (argc < 1)
		return EXIT_FAILURE;

	Logger::Source log = Logger::source;

	FontConfig font_config;

	std::stringstream caption;
	caption << _("Usage: ") << argv[0] << _(" [OPTION]... [INPUT]") << std::endl
		<< _("Generate fonts for the CalcType rendering library.") << std::endl
		<< _("INPUT denotes the path to a BMFont file to process.") << std::endl
		<< std::endl
		<< _("Mandatory arguments to long options are mandatory for short options too");

	// Declare supported options.
	po::options_description desc(caption.str());
	desc.add_options()
		(options::output_name.name(),
			po::value<std::string>(&font_config.output_name),
			options::output_name.description)
		(options::output_dir.name(),
			po::value<std::string>(&font_config.output_dir),
			options::output_dir.description)
		(options::input_file.name(),
			po::value<std::string>(&font_config.input_file))
		(options::help.name(), options::help.description)
		(options::version.name(), options::version.description);

	// Declare supported positional options.
	po::positional_options_description p_desc;
	p_desc.add(options::input_file.name(),
		options::input_file.get_max_count());

	// Process options.
	try {
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv)
			.options(desc).positional(p_desc).run(), vm);
		po::notify(vm);

		if (options::help.count(vm)) {
			std::cout << desc << std::endl;
			return EXIT_SUCCESS;
		} else if (options::version.count(vm)) {
			show_version();
			return EXIT_SUCCESS;
		}
	} catch (po::unknown_option& e) {
		BOOST_LOG_SEV(log, LogLevel::fatal)
			<< argv[0] << _(": unrecognized option '") << e.get_option_name() << _("'") << std::endl
			<< _("Try '") << argv[0] << _(" --help' for more information.") << std::endl;
		return EXIT_FAILURE;
	}

	// TODO(Natalie): Process font.
	if (font_config.input_file.size() < 1) {
		BOOST_LOG_SEV(log, LogLevel::fatal)
			<< argv[0] << _(": no input file specified") << std::endl
			<< _("Try '") << argv[0] << _(" --help' for more information.") << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
