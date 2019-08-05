#pragma once
#include <exception>
#include <string>
#include <sstream>
#include "CPPBitReader.h"
template<typename T>
struct ParseException : public std::exception
{
protected:
	const CPPBitReader<T>& bitReader;
	ParseException(const CPPBitReader<T>& br);
public:
	const char* what() const throw();
};

template<typename T>
struct GeneralParseException : public ParseException<T>
{
protected:
	std::string message;
public:
	GeneralParseException(const std::string message, const CPPBitReader<T>& br);
	const char* what() const throw() override;
};

struct PropertyDoesNotExistException : public std::exception
{
protected:
	std::string propertyName;
public:
	PropertyDoesNotExistException(const std::string propertyName_);
	const char* what() const throw();
};

struct InvalidVersionException : public std::exception
{
protected:
	uint32_t engineVersion;
	uint32_t licenseeVersion;
	uint32_t netVersion;
public:
	InvalidVersionException(const uint32_t engine, const uint32_t licensee, const uint32_t net);
	const char* what() const throw();
};

template<typename T>
struct AttributeParseException : public ParseException<T>
{
protected:
	std::string failedAttribute;
public:
	AttributeParseException(const std::string attribute, const CPPBitReader<T>& br);
	const char* what() const throw() override;
};

template<typename T>
inline ParseException<T>::ParseException(const CPPBitReader<T>& br) : bitReader(br)
{
}

template<typename T>
const char* ParseException<T>::what() const throw()
{
	std::stringstream ss;
	auto absPos = (bitReader.t_position * sizeof(T) * 8) + bitReader.bit_position;
	ss << "T_POS=" << bitReader.t_position << ", BIT_POS=" << bitReader.bit_position << ", ABS=" << absPos << "/" << bitReader.size;
	ss << ". Version(" << bitReader.owner->header.engineVersion << ", " << bitReader.owner->header.licenseeVersion << ", " << bitReader.owner->header.netVersion << ")";
	return ss.str().c_str();
}

template<typename T>
inline AttributeParseException<T>::AttributeParseException(const std::string attribute, const CPPBitReader<T>& br) : ParseException<T>(br), failedAttribute(attribute)
{
}

template<typename T>
inline const char* AttributeParseException<T>::what() const throw()
{
	std::stringstream ss;
	ss << "Failed to parse attribute \"" << failedAttribute << "\". ";
	ss << ParseException<T>::what();
	return ss.str().c_str();
}

template<typename T>
inline GeneralParseException<T>::GeneralParseException(const std::string message_, const CPPBitReader<T>& br) : ParseException<T>(br), message(message_)
{
}

template<typename T>
inline const char * GeneralParseException<T>::what() const throw()
{
	std::stringstream ss;
	ss << message << " ";
	ss << ParseException<T>::what();
	return ss.str().c_str();;
}