#include "../../common/message/SDMAck.h"
#include "../../common/message/SDMCancel.h" 
#include "../../common/message/SDMCancelxTEDS.h"
#include "../../common/message/SDMCode.h" 
#include "../../common/message/SDMCommand.h" 
#include "../../common/message/SDMConsume.h" 
#include "../../common/message/SDMData.h"
#include "../../common/message/SDMDeletesub.h"
#include "../../common/message/SDMDMLeader.h"
#include "../../common/message/SDMElection.h"
#include "../../common/message/SDMError.h" 
#include "../../common/message/SDMHeartbeat.h"
#include "../../common/message/SDMKill.h"
#include "../../common/message/SDMPostTask.h" 
#include "../../common/message/SDMReady.h" 
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMRegPM.h" 
#include "../../common/message/SDMReqCode.h" 
#include "../../common/message/SDMReqReg.h" 
#include "../../common/message/SDMReqxTEDS.h"
#include "../../common/message/SDMSearch.h" 
#include "../../common/message/SDMSearchReply.h" 
#include "../../common/message/SDMSerreqst.h" 
#include "../../common/message/SDMService.h" 
#include "../../common/message/SDMSubreqst.h" 
#include "../../common/message/SDMTask.h" 
#include "../../common/message/SDMTaskFinished.h" 
#include "../../common/message/SDMTat.h" 
#include "../../common/message/SDMVarInfo.h"
#include "../../common/message/SDMVarReq.h"
#include "../../common/message/SDMxTEDS.h" 
#include "../../common/message/SDMxTEDSInfo.h" 
//#include "../../common/message/SDMxTEDSUpdate.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char buf[BUFSIZE];
	int marshalsize = 0;
	int unmarshalsize = 0;

	SDMAck ack;
	marshalsize = ack.Marshal(buf);
	unmarshalsize = ack.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMAck invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMAck marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	SDMCancel cancel;
	marshalsize = cancel.Marshal(buf);
	unmarshalsize = cancel.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMCancel invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMCancel marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	SDMCancelxTEDS cancelxTEDS;
	marshalsize = cancelxTEDS.Marshal(buf);
	unmarshalsize = cancelxTEDS.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMCancelxTEDS invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMCancelxTEDS marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMCode code;
	marshalsize = code.Marshal(buf);
	unmarshalsize = code.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMCode invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMCode marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMCommand command;
	marshalsize = command.Marshal(buf);
	unmarshalsize = command.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMCommand invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMCommand marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMConsume consume;
	marshalsize = consume.Marshal(buf);
	unmarshalsize = consume.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMConsume invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMConsume marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMData data;
	marshalsize = data.Marshal(buf);
	unmarshalsize = data.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMData invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMData marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMDeletesub deletesub;
	marshalsize = deletesub.Marshal(buf);
	unmarshalsize = deletesub.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMDeletesub invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMDeletesub marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	SDMDMLeader leader;
	marshalsize = leader.Marshal(buf);
	unmarshalsize = leader.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMDMLeader invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMDMLeader marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	SDMElection election;
	marshalsize = election.Marshal(buf);
	unmarshalsize = election.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMElection invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMElection marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMError error;
	marshalsize = error.Marshal(buf);
	unmarshalsize = error.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMError invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMError marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	SDMHeartbeat heartbeat;
	marshalsize = heartbeat.Marshal(buf);
	unmarshalsize = heartbeat.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMHeartbeat invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMHeartbeat marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	SDMKill kill;
	marshalsize = kill.Marshal(buf);
	unmarshalsize = kill.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMKill invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMKill marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMPostTask posttask;
	marshalsize = posttask.Marshal(buf);
	unmarshalsize = posttask.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMPostTask invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMPostTask marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMReady ready;
	marshalsize = ready.Marshal(buf);
	unmarshalsize = ready.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMReady invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMReady marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMRegInfo reginfo;
	marshalsize = reginfo.Marshal(buf);
	unmarshalsize = reginfo.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMRegInfo invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMRegInfo marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMRegPM regpm;
	marshalsize = regpm.Marshal(buf);
	unmarshalsize = regpm.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMRegPM invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMRegPM marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMReqCode reqcode;
	marshalsize = reqcode.Marshal(buf);
	unmarshalsize = reqcode.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMReqCode invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMReqCode marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMReqReg reqreg;
	marshalsize = reqreg.Marshal(buf);
	unmarshalsize = reqreg.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMReqReg invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMReqReg marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMReqxTEDS reqxteds;
	marshalsize = reqxteds.Marshal(buf);
	if(marshalsize > 0)
		printf("SDMReqxTEDS no select marshal succeeded when it should fail\n");
	reqxteds.select = 0;
	memset(buf,0,BUFSIZE);
	marshalsize = reqxteds.Marshal(buf);
	unmarshalsize = reqxteds.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMReqxTEDS select=0 invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMReqxTEDS select=0 marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	reqxteds.select = 1;
	marshalsize = reqxteds.Marshal(buf);
	unmarshalsize = reqxteds.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMReqxTEDS select=1 invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMReqxTEDS select=1 marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	reqxteds.select = 2;
	marshalsize = reqxteds.Marshal(buf);
	unmarshalsize = reqxteds.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMReqxTEDS select=2 invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMReqxTEDS select=2 marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	reqxteds.select = 3;
	marshalsize = reqxteds.Marshal(buf);
	unmarshalsize = reqxteds.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMReqxTEDS select=3 invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMReqxTEDS select=3 marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMSearch search;
	marshalsize = search.Marshal(buf);
	unmarshalsize = search.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMSearch invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMSearch marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMSearchReply searchreply;
	marshalsize = searchreply.Marshal(buf);
	unmarshalsize = searchreply.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMSearchReply invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMSearchReply marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMSerreqst serreqst;
	marshalsize = serreqst.Marshal(buf);
	unmarshalsize = serreqst.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMSerreqst invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMSerreqst marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMService service;
	marshalsize = service.Marshal(buf);
	unmarshalsize = service.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMService invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMService marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMSubreqst subreqst;
	marshalsize = subreqst.Marshal(buf);
	unmarshalsize = subreqst.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMSubreqst invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMSubreqst marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMTask task;
	marshalsize = task.Marshal(buf);
	unmarshalsize = task.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMTask invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMTask marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMTaskFinished taskfinished;
	marshalsize = taskfinished.Marshal(buf);
	unmarshalsize = taskfinished.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMTaskFinished invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMTaskFinished marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMTat tat;
	marshalsize = tat.Marshal(buf);
	unmarshalsize = tat.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMTat invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMTat marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	SDMVarInfo varinfo;
	marshalsize = varinfo.Marshal(buf);
	unmarshalsize = varinfo.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMVarInfo invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMVarInfo marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	SDMVarReq varreq;
	marshalsize = varreq.Marshal(buf);
	unmarshalsize = varreq.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMVarReq invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMVarReq marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMxTEDS xteds;
	marshalsize = xteds.Marshal(buf);
	unmarshalsize = xteds.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMxTEDS invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMxTEDS marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);

	SDMxTEDSInfo xtedsinfo;
	marshalsize = xtedsinfo.Marshal(buf);
	unmarshalsize = xtedsinfo.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMxTEDSInfo invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMxTEDSInfo marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);
	
	/*SDMxTEDSUpdate update;
	marshalsize = update.Marshal(buf);
	unmarshalsize = update.Unmarshal(buf);
	if(unmarshalsize == SDM_INVALID_MESSAGE)
		printf("SDMxTEDSUpdate invalid message\n");
	if(marshalsize != unmarshalsize)
		printf("SDMxTEDSUpdate marshal: %d, unmarshal: %d return sizes do not match\n",marshalsize,unmarshalsize);
	memset(buf,0,BUFSIZE);*/
}
