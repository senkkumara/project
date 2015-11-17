#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

using namespace std;

#include <exception>
#include <string>

class FileNotFoundException : public exception
{
	virtual const char* what() const throw()
	{
		return "File not found!";
	}
};

class UnsupportedFileTypeException : public exception
{
	virtual const char* what() const throw()
	{
		return "File type not supported!";
	}
};

class NotConnectedToCreoException : public exception
{
	virtual const char* what() const throw()
	{
		return "No connected to Creo!";
	}
};

#endif