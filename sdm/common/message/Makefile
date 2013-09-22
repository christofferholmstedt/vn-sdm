#SDM message classes

include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

SDMClasses = SDMAck SDMCancel SDMCancelxTEDS SDMCode SDMCommand SDMConsume SDMComponent_ID SDMData SDMDeletesub SDMDMLeader SDMElection SDMError SDMHeartbeat SDMKill SDMmessage SDMMessage_ID SDMPostTask SDMReady SDMRegInfo SDMRegPM SDMReqCode SDMReqReg SDMReqxTEDS SDMSearch SDMSearchReply SDMSerreqst SDMService SDMSubreqst SDMTask SDMTaskError SDMTaskFinished SDMTat SDMVarInfo SDMVarReq SDMxTEDS SDMxTEDSInfo SDMHello SDMRegister SDMID

.PHONY: all clean distclean

all:	$(addsuffix .o,$(SDMClasses))

%.o:	%.cpp %.h
	$(CXX) $(CXXFLAGS) $(MESSAGELOGGINGFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean:	clean
