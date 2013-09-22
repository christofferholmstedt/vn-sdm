#include "SDMBadIndexException.h"

SDMBadIndexException::SDMBadIndexException(const char* strMessage)
 : SDMException(strMessage)
{}

SDMBadIndexException::~SDMBadIndexException()
{
}

const char* SDMBadIndexException::Message() const
{
	return SDMException::Message();
}
