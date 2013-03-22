#include "utility.hpp"

void throw_error( char const str[] ) {
	throw std::runtime_error( str );
}

void throw_error( std::string const& str ) {
	throw std::runtime_error( str );
}