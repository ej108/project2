#if !defined( UTILITY_HPP )
#define UTILITY_HPP

#include <stdexcept>
#include <string>

void throw_error( char const str[] );

void throw_error( std::string const& str );

#endif