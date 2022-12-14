/// @file logger.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Message log handler.
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

#include <iostream>

#include <boost/core/null_deleter.hpp>
#include <boost/log/core.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace b_log = boost::log;

boost::shared_ptr<Logger::Sink> Logger::sink;
Logger::Source Logger::source;

void Logger::init()
{
	sink = boost::make_shared<Sink>();
	boost::shared_ptr<std::ostream> stream{&std::clog,
		boost::null_deleter{}};
	sink->locked_backend()->add_stream(stream);
	b_log::core::get()->add_sink(sink);
}
