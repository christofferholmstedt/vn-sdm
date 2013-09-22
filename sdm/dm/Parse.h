//Parse.h

//ReqReg return types
#define REQTYPE_REGEX		2
#define REQTYPE_EMPTYITEM	1
#define REQTYPE_USEITEM		0
		
#define SDM_CONFIG_FILE_NAME	"sdm.config"

//Function prototypes
int ParseDeviceName(char *buf, char *sensor_buf, unsigned int sensor_buflen, int level);
int GetAttribute(const char *item_def, const char *attribute, char *attribute_value, unsigned int attribute_valuelen, int level);
int ParseItemName(char *item, int level);
int MsgIDFrom(char *buf, int mID, int level);
int MergeConfigxTED(char *xTED, int xTEDBufLength, char *config, int level);
int FindConfigInfo(char *type, char* info, char* hub, char* port, int level);
//int GetSpaHubInfo(char *buf, char *info, int level);
int GetSPAHub(char* buf, char* hub, int level);
bool FindDevicesHubPath (const char *DevicePath, char *HubPathOut, unsigned int HubPathOutLen, int DebugLevel);
