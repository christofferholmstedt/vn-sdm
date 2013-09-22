#include "SecTime.h"
#include "unistd.h"
#include "stdio.h"

SecTime::SecTime(): Sec(0), USec(0)
{
}

SecTime::SecTime(long Seconds, long USeconds): Sec(Seconds), USec(USeconds)
{
}

SecTime::SecTime(const SecTime &right): Sec(right.Sec), USec(right.USec)
{
}
/*
 *  Assignment operator, simply copies the seconds and useconds value to the target object.
 */
SecTime& SecTime::operator=(const SecTime &right)
{
	Sec = right.Sec;
	USec = right.USec;
	return *this;
}
/*
 *  Equals operator, checks to see if the time values are the same.
 */
bool SecTime::operator==(const SecTime &right) const
{
	if (Sec == right.Sec && USec == right.USec)
		return true;
	return false;
}
/*
 *  Less than operator, checks to see if the current object is less than the right object.
 */
bool SecTime::operator < (const SecTime& right) const
{
	if (Sec < right.Sec)
		return true;
	if (Sec == right.Sec && USec < right.USec)
		return true;
	return false;
}
/*
 * Greater than operator, checks to see if the current object is greater than the right object.
 */
bool SecTime::operator > (const SecTime& right) const
{
	if (Sec > right.Sec)
		return true;
	if (Sec == right.Sec && USec > right.USec)
		return true;
	return false;
}
/*
 * Less than equals operator, checks to see if the current object is less or equal to the right object.
 */
bool SecTime::operator <= (const SecTime& right) const
{
	if (Sec < right.Sec )
		return true;
	if ( Sec == right.Sec && USec <= right.USec)
		return true;
	return false;
}
/*
 * Greater than equals operator, checks to see if the current object is greater than or equal to the right object.
 */
bool SecTime::operator >= (const SecTime& right) const
{
	if (Sec > right.Sec )
		return true;
	if ( Sec == right.Sec && USec >= right.USec)
		return true;
	return false;
}
/*
 *  Addition operator, performs an addition of the two objects, accounting for useconds overflow.
 */
const SecTime SecTime::operator + (const SecTime &right) const
{
	SecTime Result;
	Result.SetSeconds(Sec + right.GetSeconds());
	if (USec + right.GetUSeconds() >= USEC_MAX_VALUE)
	{
		Result.SetSeconds(Result.GetSeconds()+1);
		Result.SetUSeconds(USec + right.GetUSeconds() - USEC_MAX_VALUE);
	}
	else
		Result.SetUSeconds (USec + right.GetUSeconds());
	return Result;
}
/*
 *  Subtraction operator, performs a subtraction of the two objects, accounting for useconds carry.
 */
const SecTime SecTime::operator - (const SecTime &right) const
{
	SecTime Result;
	Result.SetSeconds(Sec - right.GetSeconds());
	if (USec- right.GetUSeconds() < 0)
	{
		Result.SetSeconds(Result.GetSeconds()-1);
		Result.SetUSeconds(USEC_MAX_VALUE + USec - right.GetUSeconds());	
	}
	else
		Result.SetUSeconds (USec - right.GetUSeconds());
	return Result;
}
/*
 *  Subtraction operator, performs a subtraction-assign of the two objects, accounting for useconds carry.
 */
SecTime& SecTime::operator -= (const SecTime &right)
{
	Sec -= right.GetSeconds();
	long rhsUSec = right.GetUSeconds();
	if (USec - rhsUSec < 0)
	{
		Sec--;
		USec = USEC_MAX_VALUE + USec - rhsUSec;	
	}
	else
		USec =  USec - rhsUSec;
	return *this;
}
/*
*  Formats as a string. If negative, useconds is corrected
*/
const char* SecTime::ToString(char *str, int len ) const
{
	if ( len < 19 )
	{
		str[0] = 0;
		return str;
	}

	long dSec = Sec;
	long dUsec = USec;
	if ( dSec < 0 )
	{
		dSec++;
		if ( dSec == 0)
		{
			*str++ = '-';
			len--;
		}
		dUsec = 1000000 - dUsec;
	}
	snprintf(str,len,"%ld.%06ld",dSec,dUsec);
	return str;
}
