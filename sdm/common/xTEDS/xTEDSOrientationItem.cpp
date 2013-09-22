#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "xTEDSOrientationItem.h"
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSOrientationItem::xTEDSOrientationItem():m_strAxis(NULL),m_strAngle(NULL),m_strUnits(NULL)
{
}

xTEDSOrientationItem::~xTEDSOrientationItem()
{
	if (m_strAngle != NULL) free(m_strAngle);
	if (m_strAxis != NULL) free(m_strAxis);
	if (m_strUnits != NULL) free(m_strUnits);
}

void xTEDSOrientationItem::SetAxis(const char* NewAxis)
{
	if (NewAxis == NULL) return;
	if (m_strAxis != NULL) free(m_strAxis);
	m_strAxis = strdup(NewAxis);
}

void xTEDSOrientationItem::SetAngle(const char* NewAngle)
{
	if (NewAngle == NULL) return;
	if (m_strAngle != NULL) free(m_strAngle);
	m_strAngle = strdup(NewAngle);
}

void xTEDSOrientationItem::SetUnits(const char* NewUnits)
{
	if (NewUnits == NULL) return;
	if (m_strUnits != NULL) free(m_strUnits);
	m_strUnits = strdup(NewUnits);
}

void xTEDSOrientationItem::SetOrientation(const orientation* NewOrientation)
{
	if (NewOrientation == NULL) return;
	SetAxis(NewOrientation->axis_value);
	SetAngle(NewOrientation->angle_value);
	SetUnits(NewOrientation->units_value);
}

void xTEDSOrientationItem::VarInfoRequest(char* InfoBufferOut, size_t BufferLength) const
{
	const int MAX_BUF_SIZE = 512;
	char Buf[MAX_BUF_SIZE];
	
	if (m_strAxis == NULL || m_strAngle == NULL || m_strUnits == NULL)
		return ;
	
	snprintf(Buf, sizeof(Buf), "<Orientation axis=\"%s\" angle=\"%s\" units=\"%s\" />", m_strAxis, m_strAngle, m_strUnits);
	
	strncat(InfoBufferOut, Buf, BufferLength - 1);
}
