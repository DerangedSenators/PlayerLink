/*
 * Copyright (C) 2020 Deranged Senators
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef PLAYERLINK_CORE_RUNTIMEEXCEPTION_H
#define PLAYERLINK_CORE_RUNTIMEEXCEPTION_H

#include <string>
#include <exception>
#include <stdexcept>
#include <string_view>
#include <boost/assert.hpp>
#include <boost/assert/source_location.hpp>

namespace PlayerLink{namespace Core{
	/**
	 * @authors Ash Jaimal
	 * @authors Hanzalah Ravat
	 * @brief exception class for Runtime environment, throws exceptions whenver an issue occurs with connectivity or any other runtime related error occurs
	*/
	class RuntimeException : public std::runtime_error {
	private: 
		const char* runtimeMessage;
    protected:

	public:
	    /**
	     * Creates a Runtime Exception
	     * @param message The error message
	     * @param location The Location of the error. This is an optional parameter and is typically taken by default
	     */
	    RuntimeException(const char* message,
                         const boost::source_location &location = BOOST_CURRENT_LOCATION);

		const char* what() const throw();
	};
}}

#endif