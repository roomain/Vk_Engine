#pragma once
#include <exception>
#include <source_location>
#include <string>
#include <format>

inline std::string errorMessage(const std::source_location&& loc, const std::string& message)
{
	return std::format("{} {}: {}", loc.file_name(), loc.line(), message);
}

#define SDL_CHECK(error_code) \
if(error_code != 0) \
	throw std::runtime_error(errorMessage(std::source_location::current(), SDL_GetError()));