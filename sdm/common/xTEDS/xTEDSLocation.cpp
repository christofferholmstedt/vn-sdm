#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "xTEDSLocation.h"
#include "../message_defs.h"
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSLocation::xTEDSLocation():m_strX(NULL),m_strY(NULL),m_strZ(NULL),m_strUnits(NULL)
{
}

xTEDSLocation::~xTEDSLocation()
{
	if (m_strX != NULL) free(m_strX);
	if (m_strY != NULL) free(m_strY);
	if (m_strZ != NULL) free(m_strZ);
	if (m_strUnits != NULL) free(m_strUnits);
}

void xTEDSLocation::setX(const char *xStr)
{
	if (xStr == NULL) return;
	if (m_strX != NULL) free(m_strX);
	m_strX = strdup(xStr);
}

void xTEDSLocation::setY(const char *yStr)
{
	if (yStr == NULL) return;
	if (m_strY != NULL) free(m_strY);
	m_strY = strdup(yStr);
}

void xTEDSLocation::setZ(const char *zStr)
{
	if (zStr == NULL) return;
	if (m_strZ != NULL) free(m_strZ);
	m_strZ = strdup(zStr);
}

void xTEDSLocation::setUnits(const char *unitsStr)
{
	if (unitsStr == NULL) return;
	if (m_strUnits != NULL) free(m_strUnits);
	m_strUnits = strdup(unitsStr);
}

void xTEDSLocation::setLocation(const location *loc)
{
	if (loc == NULL) return;
	setX(loc->x_value);
	setY(loc->y_value);
	setZ(loc->z_value);
	setUnits(loc->units);
}

void xTEDSLocation::setLocation(const char *x, const char *y, const char *z, const char *units)
{
	setX(x);
	setY(y);
	setZ(z);
	setUnits(units);
}

void xTEDSLocation::VarInfoRequest( char* InfoBufferOut, size_t BufferSize )
{
	char Buf[MSG_DEF_SIZE];
	
	snprintf(Buf, sizeof(Buf), "<Location x=\"%s\" y=\"%s\" z=\"%s\" units=\"%s\" />", m_strX, m_strY, m_strZ, m_strUnits);
	
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}
