#include "Utility.hpp"

invalid_param::invalid_param(const char *arg) :
	what_str {arg}
{
}

const char *invalid_param::what() const throw()
{
	return what_str;
}
