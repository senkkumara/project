#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

using namespace std;

#include <exception>
#include <string>

class MethodNotImplementedException : public exception
{
private:
	std::string _msg;

public:
	MethodNotImplementedException(const std::string method)
		: _msg(std::string("Method '") + method + "' is not implemented!") {}

	virtual const char* what() const throw()
	{
		return _msg.c_str();
	}
};

class FileNotFoundException : public exception
{
	virtual const char* what() const throw()
	{
		return "File not found!";
	}
};

class UnsupportedFileTypeException : public exception
{
private:
	std::string _msg;

public:
	UnsupportedFileTypeException(std::string ext)
		: _msg(std::string("File extension '") + ext + "' is not supported!") {}

	virtual const char* what() const throw()
	{
		return _msg.c_str();
	}
};

class NotConnectedToCreoException : public exception
{
	virtual const char* what() const throw()
	{
		return "Not currently connected to Creo!";
	}
};

class MalformedFileException : public exception
{
private:
	std::string _msg;

public:
	MalformedFileException(std::string filename)
		: _msg(std::string("File '") + filename + "' is malformed") {}

	virtual const char* what() const throw()
	{
		return _msg.c_str();
	}
};

class GeometryBuildException : public exception
{
	virtual const char* what() const throw()
	{
		return "Exception occurred during the build of the geoemtry...";
	}
};

#endif