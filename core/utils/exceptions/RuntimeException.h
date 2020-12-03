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

namespace PlayerLink{namespace Core{
	/**
	 * @author Ash Jaimal
	 * @breif 
	*/
	class RuntimeException : public std::exception {
	private: 
		std::string runtimeMessage;
	public:
		RuntimeException(const std::string& message) throw();
		~RuntimeException() throw();
		const char* what() const throw();
	};
}}












#endif