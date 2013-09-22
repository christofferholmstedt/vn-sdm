#include "LookupTable.h"

LookupTable::LookupTable(): CurKey(1)
{
}

unsigned int LookupTable::GetValueFromKey(int Key)
{
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
	{
		if (TableItems[i].Key == Key)
			return TableItems[i].Value;
	}
	return 0;
}

int LookupTable::GetKeyFromValue(unsigned int Value)
{
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
	{
		if (TableItems[i].Value == Value)
			return TableItems[i].Key;
	}
	return -1;
}

int LookupTable::AddValue(unsigned int Value)
{
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
		if (TableItems[i].Key == KEY_EMPTY)
		{
			TableItems[i].Key = CurKey++;
			TableItems[i].Value = Value;
			return TableItems[i].Key;
		}
	return -1;
}

unsigned int LookupTable::RemoveKeyGetValue(int Key)
{
	unsigned int Result;
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
		if (TableItems[i].Key == Key)
		{
			TableItems[i].Key = KEY_EMPTY;
			Result = TableItems[i].Value;
			TableItems[i].Value = 0;
			return Result;
		}
	return 0;
}

int LookupTable::RemoveValueGetKey(unsigned int Value)
{
	int Result;
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
		if (TableItems[i].Value == Value)
		{
			Result = TableItems[i].Key;
			TableItems[i].Key = KEY_EMPTY;
			TableItems[i].Value = 0;
			return Result;
		}
	return 0;
}


void LookupTable::UpdateValue(int Key, unsigned int NewValue)
{
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
		if (TableItems[i].Key == Key)
		{
			TableItems[i].Value = NewValue;
			return ;
		}
}

bool LookupTable::UpdateThreadIDFromKey(int Key, pthread_t ThreadID)
{
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
	{
		if (TableItems[i].Key == Key)
		{
			TableItems[i].ThreadID = ThreadID;
			return true;
		}
	}
	return false;
}

bool LookupTable::UpdateThreadIDFromValue(unsigned int Value, pthread_t ThreadID)
{
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
	{
		if (TableItems[i].Value == Value)
		{
			TableItems[i].ThreadID = ThreadID;
			return true;
		}
	}
	return false;
}

bool LookupTable::GetThreadIDFromKey(int Key, pthread_t *ThreadIDOut)
{
	for (int i = 0; i < MAX_TABLE_ITEMS; i++)
	{
		if (TableItems[i].Key == Key)
		{
			*ThreadIDOut = TableItems[i].ThreadID;
			return true;
		}
	}
	return false;
}
