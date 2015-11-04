#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

using namespace std;

#include <exception>

class FileNotFoundException : public exception
{
	virtual const char* what() const throw()
	{
		return "File not found!";
	}
}

#endif