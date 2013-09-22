#include "SDMRegexException.h"

SDMRegexException::SDMRegexException(const char* ExceptionMessage)
	: SDMException(ExceptionMessage)
{}

SDMRegexException::~SDMRegexException()
{}

const char* SDMRegexException::Message() const
{
	return SDMException::Message();
}
