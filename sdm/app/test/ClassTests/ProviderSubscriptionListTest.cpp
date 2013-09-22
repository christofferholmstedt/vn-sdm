#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define DEBUG_SUB_LIST	1
#include "../../../dm/ProviderSubscriptionList.h"
#include "../../../common/message/SDMComponent_ID.h"
#include "../../../common/message/SDMMessage_ID.h"

int main(int argc, char** argv)
{
	const int SIZE_IDS = 10;
	SDMComponent_ID pids[SIZE_IDS];
	SDMComponent_ID sids[SIZE_IDS];
	SDMMessage_ID mids[SIZE_IDS];
	
	for (int i = 0; i < SIZE_IDS; i++)
	{
		pids[i].setSensorID(i + 10);
		sids[i].setSensorID(i);
		mids[i].setMessage(i);
	}
	
	ProviderSubscriptionList list;
	
	for (int i = 0; i < SIZE_IDS; i++)
		list.Add(pids[i], sids[i], mids[i]);
	
	printf("Adding one subscriber to all providers\n\n");
	// Add one subscriber to all providers
	for (int i = 0; i < SIZE_IDS; i++)
		list.Add(pids[i], sids[0], mids[i]);
	
	printf("Adding one provider to all subscribers\n\n");
	// Add one provider to all subscribers
	for (int i = 0; i < SIZE_IDS; i++)
		list.Add(pids[0], sids[i], mids[i]);
	
	printf("Removing the one subscriber\n\n");
	list.SubscriberFinish(sids[0]);
	
	printf("Removing the one provider\n\n");
	list.ProviderFinish(pids[0]);
	
	
	return 0;
}
