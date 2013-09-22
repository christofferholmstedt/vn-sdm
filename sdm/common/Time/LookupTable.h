#ifndef _LOOKUP_TABLE_H_
#define _LOOKUP_TABLE_H_
#include "../sdmLib.h"
#include <pthread.h>

#define MAX_TABLE_ITEMS	5
#define KEY_EMPTY	-1

struct Item
{
	int Key;
	unsigned int Value;
	pthread_t ThreadID;
	Item(): Key(KEY_EMPTY), Value(0), ThreadID() {}
};

class SDMLIB_API LookupTable
{
public:
	LookupTable();
	unsigned int GetValueFromKey(int Key);
	int GetKeyFromValue(unsigned int Value);
	int AddValue(unsigned int Value);
	unsigned int RemoveKeyGetValue(int Key);
	int RemoveValueGetKey(unsigned int Value);
	void UpdateValue(int Key, unsigned int NewValue);
	bool UpdateThreadIDFromKey(int Key, pthread_t ThreadID);
	bool UpdateThreadIDFromValue(unsigned int Value, pthread_t ThreadID);
	bool GetThreadIDFromKey(int Key, pthread_t *ThreadIDOut);
private:
	Item TableItems[MAX_TABLE_ITEMS];
	int CurKey;
};

#endif
