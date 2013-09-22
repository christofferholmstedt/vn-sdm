#ifndef _SEC_TIME_H_
#define _SEC_TIME_H_
#include "../sdmLib.h"

#define USEC_MAX_VALUE  1000000

//This class is meant to provide abstraction for doing arithmetic operations on time values
//that have both seconds and useconds components. 
class SDMLIB_API SecTime
{
public:
	SecTime();
	SecTime(long Seconds, long USeconds);
	SecTime(const SecTime& right);
	SecTime& operator =(const SecTime& right);
	bool operator==(const SecTime& right) const;
	bool operator < (const SecTime& right) const;
	bool operator > (const SecTime& right) const;
	bool operator <= (const SecTime& right) const;
	bool operator >= (const SecTime& right) const;
	const SecTime operator + (const SecTime &right) const;
	const SecTime operator - (const SecTime &right) const;
	SecTime& operator -= (const SecTime &right);
	
	void SetSeconds(long S) { Sec = S; }
	void SetUSeconds(long Us) { USec = Us; }
	long GetSeconds() const { return Sec; }
	long GetUSeconds() const { return USec; }
	void Clear() { Sec = 0; USec = 0; }
	const char* ToString(char *str, int len ) const;
private:
	long Sec; // Number of seconds since Jan 6, 1980 00:00:00
	long USec;
};

#endif
