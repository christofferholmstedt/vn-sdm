//Parse.cpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "Parse.h"
#include "DM.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
//  ParseDeviceName takes the xted and finds the device name in the xted
//	buf - char pointer to a buffer containing the xted
//	sensor_buf - char pointer to a buffer to put the device name into
//      level - the level to print statements
//
//	returns whether this is a DEVICE or APPLICATION, -1 if not found
//
///////////////////////////////////////////////////////////////////////////////////////////
int ParseDeviceName(char* strSource, char* strReturnName, unsigned int uiReturnNameSize, int iDebug)
{
	const char* STR_DEVICE = "Device";
	const char* STR_APPLICATION = "Application";
	size_t iTagStart = 0, iTagEnd = 0;
	bool bFound = false, bCorrectTag = false;
	char* curPos = NULL;
	int prevPos = 0;
	const size_t SOURCE_LENGTH = strlen(strSource);
	bool bTryDevice = true;
	
	while (!bFound)
	{
		if (bTryDevice)	// Check for Device
			curPos = strstr(strSource + prevPos, STR_DEVICE);
		else		// Check for Application
			curPos = strstr(strSource + prevPos, STR_APPLICATION);

		if (curPos == NULL)
		{
			if (bTryDevice)
			{
				// Try application instead
				bTryDevice = false;
				prevPos = 0;
				continue;
			}
			else
				return -1;
		}
		else
		{
			prevPos = curPos - strSource + 1;
			// Find the opening < tag, if we encounter anything other than " ", we have not matched
			for (iTagStart = curPos - strSource - 1; iTagStart > 0; iTagStart--)
			{
				// Success
				if (strSource[iTagStart] == '<')
				{
					bCorrectTag = true;
					break;
				}
				// Match failure, try the next
				else if (strSource[iTagStart] != ' ')
				{
					bCorrectTag = false;
					break;
				}
			}
			if (!bCorrectTag)
				continue;
			
			// Find the closing > tag, if we encounter any other "<", we have not matched
			for (iTagEnd = iTagStart + 1; iTagEnd < SOURCE_LENGTH; iTagEnd++)
			{
				// Success
				if (strSource[iTagEnd] == '>')
				{
					bCorrectTag = true;
					break;
				}
				// Match failure, try the next
				else if (strSource[iTagEnd] == '<')
				{
					bCorrectTag = false;
					break;
				}
			}
			if (!bCorrectTag)
				continue;

			if (GetAttribute (&strSource[iTagStart], "name", strReturnName, uiReturnNameSize, iDebug) != 0)
				continue;

			// Attribute sucessfully found
			if (bTryDevice)
				return DEVICE;
			else
				return APPLICATION;
		}
	}
	return -1;	
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//  GetAttributes looks through the item_def to find the attribute listed
//  strSource - a char* containing the message to look through
//  strAttribute - a char* containing the attribute to look for
//  strReturnValue - a char* array to store the attribute value of attribute
//  uiAttributeSize - the size of the attribute_value array
//  iDebug - the level to print at
//
//	returns zero if the attribute was successfully found, -1 if not found or error
//
///////////////////////////////////////////////////////////////////////////////////////////
int GetAttribute(const char* strSource, const char* strAttribute, char* strReturnValue, unsigned int uiAttributeSize, int iDebug)
{
	unsigned int i = 0, attrstart = 0, attrend = 1;
	// flag == 1 means the attribute name has been found within the tag
	// flag == 2 means the attribute value has been found
	int flag = 0;
	int numQuotes = 0;

	if (strSource == NULL || strAttribute == NULL || strReturnValue == NULL || uiAttributeSize == 0)
		return -1;
	
	const size_t ATTR_LENGTH = strlen(strAttribute);
	const size_t SOURCE_LENGTH = strlen(strSource);
	for(i = 0; i < SOURCE_LENGTH; i++)
	{
		//The number of quote marks must be even to assure we're matching an XML attribute and not within a string literal
		if (strSource[i] == '"')
			numQuotes++;
		//Only match the attribute name if the number of quotes is even (can't be within string literal)
		if(strncmp(&strSource[i], strAttribute, ATTR_LENGTH) == 0 && numQuotes%2 == 0)
		{
			flag = 1;	//Found the start of the attribute name
			attrstart = i + ATTR_LENGTH;
		}
		else if (strSource[i] == '"' && flag == 1)
		{
			flag = 2;	//Found the start of the attribute value
			attrstart = i + 1;
		}
		else if (strSource[i] == '"' && i > attrstart && flag == 2)	//Found close of attribute value
		{
			attrend = i;
			if (attrend < attrstart)	//Don't allow integer wrap if something went wrong
				return -1;
			if (attrend - attrstart > uiAttributeSize)
				return -1;
			else
			{
				strncpy(strReturnValue, &strSource[attrstart], attrend - attrstart);
				strReturnValue[attrend - attrstart] = '\0';
			}
			return 0;
		}
		// Don't pass this XML element, if so, return
		if (strSource[i] == '>')
			return  -1;
	}
	return -1;
}
#ifdef BUILD_FOR_XTEDS_MERGING
/*
	Description:
		Merges the information gotten from the sdm.config file with the xTEDS

	Input:
		xTED - the xTEDS to be merged
		config - the information from the sdm.config file
		level - the debug level to print messages on

	Output:
		-1 - the merge did not succeed
		0 - the merge was sucessful

	Changed:
		None

*/
int MergeConfigxTED(char *xTED, int xTEDBufLength, char *config, int level)
{
	int success = -1;
	char* device = "Device";
	int flag = 0;
	char* spahub = "spaUHub";
	int length = 0;
	int templength = 0;
	int j = 0;
	int offset = 0;
	int d = 0;
	int CurLength = 0, TempLength = 0;
	
	for(int i = 0; i < (int)strlen(xTED); i++)
	{
		//Find the start of the DEVICE tag
		if(strncmp(&xTED[i],device,strlen(device)) == 0)
		{
			flag = 1;	//Start of device tag found
			if(level >= 4)
			{
				printf("Found the start of the Device tag\n");
			}
		}
		//Find an ending or the element spaUHub
		if((strncmp(&xTED[i],"/>",2) == 0 || strncmp(&xTED[i],">",1) == 0 || strncmp(&xTED[i],spahub,strlen(spahub)) == 0) && flag == 1)
		{
		      	//Simple case <DEVICE ... />
			if(strncmp(&xTED[i],"/>",2) == 0)
				length = 2;
			//spaUHub case only for robohubs that are partially merged before runtime <DEVICE ... spaUHub="..."...>
			else if(strncmp(&xTED[i],spahub,strlen(spahub)) == 0)
			{
				templength = i;
				i += strlen(spahub)+2;
				while(xTED[i]!='>')
					i++;
				length = i - templength + 1;
				i = templength;
			}
			//<DEVICE ...>...</DEVICE>
			else
			{
				//Find start of next opening tag
				while(xTED[i+length]!='<')
					length++;
				//If this is a closing tag it will be </DEVICE>
				//This case for no tags between <Device..> and </Device>
				if(xTED[i+length+1]=='/')
				{
					while(xTED[i+length]!='>')
						length++;
					length++;
				}
				else
				{
					//Find the end of the <DEVICE...> tag in the config info
					while(strncmp(&config[j],"/>",2) != 0 && strncmp(&config[j],">",1) != 0)
					{
						j++;
					}
					//If DEVICE tag closes with /> then this is a simple merge
					if(strncmp(&config[j],"/>",2) == 0)
					{
						offset = -2;
						while(config[j-offset]!=0)
						{
							offset--;
						}
						length = 0;
					}
					else
					{
						//Find the start of the next tag in the config info
						while(config[j+offset]!='<')
							offset++;
						if(config[j+offset+1]=='/')
						{
							while(config[j+offset]!='>')
								offset++;
							offset++;
							offset = 0 - offset;
						}
						else
						{
							CurLength = strlen(&xTED[i+1]);
							char *temp = (char*)malloc(CurLength+1);
							//copy everything after > to end of xTEDS into temp
							strcpy(temp,&xTED[i+1]);
							xTED[i] = ' ';
							
							//copy config info up to end to DEVICE ending >
							if (CurLength + j+1 < xTEDBufLength)
							{
								strncpy(&xTED[i+1],config,j+1);
								CurLength += j+2;
							}
							
							i += j + 2;
							//Find any other elements that might be between the opening and closing of DEVICE
							while(strncmp(&temp[d],"</Device>",9) != 0)
								d++;
							
							//Copy the elements found, most likely will just be QUALIFIER tags
							if (CurLength + d < xTEDBufLength)
							{
								strncpy(&xTED[i],temp,d);
								CurLength += d;
							}
							i += d;
							while(config[j] != '<')
								j++;
							
							//copy the rest of the config info
							TempLength = strlen(&config[j]);
							if (CurLength + TempLength < xTEDBufLength)
							{
								strcpy(&xTED[i],&config[j]);
								CurLength += TempLength;
							}
							
							while(strncmp(&xTED[i],"</Device>",9) != 0)
								i++;
							i += 9;
							
							//copy the last of the xTEDS back in
							strncpy(&xTED[i],&temp[d+9],xTEDBufLength - CurLength);
							free(temp);
							success = 0;
							if(level >= 3)
								printf("New merged xTEDS is:\n %s\n",xTED);
							return success;
						}
					}
				}
			}
			// Merge the simple case
			CurLength = strlen(&xTED[i+length]);
			char *temp = (char*)malloc(CurLength+1);
			
			// Save the original xTEDS just after the <Device ... />
			strcpy(temp,&xTED[i+length]);
			xTED[i] = ' ';
			
			// Merge in the config information
			TempLength = strlen(config);
			if (CurLength + TempLength < xTEDBufLength)
			{
				strcpy(&xTED[i+1],config);
				CurLength += TempLength;
			}
			
			// Copy back in the previously saved xTEDS info
			strncpy(&xTED[i+strlen(config)+1+offset],temp, xTEDBufLength - CurLength);
			free(temp);
			success = 0;
			if(level >= 3)
				printf("New merged xTEDS is:\n %s\n",xTED);
			return success;
		}
	}
	return success;

}
#endif // #ifdef BUILD_FOR_XTEDS_MERGING
/*
	Description:
		Find the hub path corresponding with the device and save the result in HubPathOut.

	Input:
		DevicePath - The path of the ASIM device whose robust hub to find
		HubPathOutLen - The size of HubPathOut
	Output:
		HubPathOut - The buffer into which to fill the address of the hub
		return bool - True if found, false if not found or error
	Changed:
		None
*/
bool FindDevicesHubPath (const char *DevicePath, char *HubPathOut, unsigned int HubPathOutLen, int DebugLevel)
{
	if (DevicePath == NULL || HubPathOut == NULL)
		return false;
	
	char FileBuf[65536];
	char ReturnPath[128];
	int FileFd = open(SDM_CONFIG_FILE_NAME, O_RDONLY);
	int FileLength = -1;
	
	if (FileFd < 0)
	{
		if (DebugLevel >= 2)
			printf("Could not open file %s to find corresponding hub.\n",SDM_CONFIG_FILE_NAME);
		return false;
	}
	
	// Read the file contents
	if ((FileLength = read(FileFd, FileBuf, sizeof(FileBuf)-2)) < 0)
	{
		close(FileFd);
		return false;
	}
	else
		close(FileFd);
	FileBuf[FileLength] = '\0';
	
	// If there are multiple instances of DevicePath (there shouldn't be), try them all for a match
	bool IsPortMatched = false;
	char* NextStartingPosition = NULL;
	while (!IsPortMatched)
	{
		// Find the occurance of the DevicePath in the config file
		char* DevicePathLocation = NULL;
		// If we have already found an instance of DevicePath in the config file, but not the correct one,
		// try again at the last checked position
		if (NextStartingPosition == NULL)
			DevicePathLocation = strstr(FileBuf, DevicePath);
		else
			DevicePathLocation = strstr(NextStartingPosition, DevicePath);
		
		if (DevicePathLocation == NULL)
		{
			if (DebugLevel >= 3)
				printf("Could not find hub path for spaUPort %s in configuration file.\n",DevicePath);
			return false;
		}
		char* DeviceTag = DevicePathLocation;
		
		// Get a pointer to the starting of this "<Device..." tag
		while (DeviceTag != FileBuf && strncmp(DeviceTag, "<Device", 7)!=0)
			DeviceTag--;
		
		// Make sure the spaUPort value matches this DevicePath
		if (GetAttribute(DeviceTag, "spaUPort", ReturnPath, sizeof(ReturnPath), DebugLevel) == 0)
		{
			if (DebugLevel >= 3)
				printf("spaUPort value could not be retrieved for sensor path %s.\n",DevicePath);
			// See if there is another instance of DevicePath in the file
			NextStartingPosition = DevicePathLocation+1;
			continue;
		}
		if (strcmp(ReturnPath, DevicePath) != 0)
		{
			if (DebugLevel >= 3)
				printf("spaUPort value (%s) does not match sensor path (%s).",ReturnPath, DevicePath);
			// See if there is another instance of DevicePath in the file
			NextStartingPosition = DevicePathLocation+1;
			continue;
		}
		
		// Pull out the spaUHub
		if (GetAttribute(DeviceTag, "spaUHub", HubPathOut, HubPathOutLen, DebugLevel) == 0)
		{
			if (DebugLevel >= 3)
				printf("Could not find the SpaUHub value.\n");
			// If the spaUPort matched, but we couldn't get the spaUHub, return -- the spaUPort is a unique value
			// in the config file, we can be sure that it can't be retrieved
			return false;
		}
		// This point is success
		IsPortMatched = true;
	}
	return true;
}

/*
	Description:
		Find configuration information for an xTEDS from the sdm.config file

	Input:
		type - the type of device this is
		info - a pointer to a memory location where the config info can be stored
		hub - the hub number
		port - the port number
		level - the level to print debug message on

	Output:
		-1 - unable to find any config info for xTEDS
		0 - found config info

	Changed:
		None

*/
int FindConfigInfo(char *type, char* info, char* hub, char* port, int level)
{
	int fd = 0;
	char file[65536];
	int value = 0;
	char *xTEDClose = "</xTEDS>";
	size_t start = 0;
	size_t end = -1;
	int found = 0;
	int usingPort = 0;
	int length = 0;
	int flag = 0;
	int portUsed = 1;
	int hubUsed = 1;
	char *spaHub = "SPA_U_hub";
	char *camelspaHub = "spaUHub";
	char *spaPort = "SPA_U_port";
	char *camelspaPort = "spaUPort";
	int started = 0;

	memset(file,0,sizeof(file));
	if(strcmp(type,"Application")==0)
		return -1;
	if(strcmp(type, "Device") != 0)
		return -1;
	if(hub == NULL && strcmp(type,"Device") == 0)
	{
		if(level >= 3)
			printf("hub is NULL\n");
		return -1;
	}
	else if(port == NULL)
		found = 2;
	else if(port[0] == '\0')
		found = 2;
	else
	{
		found = 3;
		usingPort = 1;
	}
	if(level >= 4)
	{
		printf("Found is %d while looking for spahub: %s spaport: %s\n",found,hub,port);
	}

	fd = open(SDM_CONFIG_FILE_NAME,O_RDONLY);
	if(fd == -1)
	{
		perror("Config file was unable to be opened! ");
		return -1;
	}
	value = read(fd,file,65535);
	if(level >= 2)
		printf("Read %d bytes from file %s\n",value,SDM_CONFIG_FILE_NAME);
	close(fd);
	if (value > 0)
	  file[value] = '\0';
  else
    file[0] = '\0';

	for(size_t i = 0; i < (int)strlen(file); i++)
	{
		if(strncmp(&file[i],type,strlen(type)) == 0 && started != 1)
		{
			start = i + strlen(type) + 1;
			flag = 1;
			started = 1;
		}
		if(strncmp(&file[i],spaHub,strlen(spaHub)) == 0 || strncmp(&file[i],camelspaHub,strlen(camelspaHub)) == 0)
		{
			hubUsed = 0;
			if(strncmp(&file[i],spaHub,strlen(spaHub)) == 0)
				i += strlen(spaHub) + 2;
			else
				i += strlen(camelspaHub) + 2;
			if(level >= 4)
			{
				printf("Found SPA_U_hub qualifier with next char: %c%c%c%c flag: %d hubUsed: %d\n",file[i],file[i+1],file[i+2],file[i+3],flag,hubUsed);
			}
		}
		if(strncmp(&file[i],spaPort,strlen(spaPort)) == 0 || strncmp(&file[i],camelspaPort,strlen(camelspaPort)) == 0)
		{
			portUsed = 0;
			if(strncmp(&file[i],spaPort,strlen(spaPort)) == 0)
				i += strlen(spaPort) + 2;
			else
				i += strlen(camelspaPort) + 2;
			if(usingPort == 0)
			{
				portUsed = 1;
				hubUsed = 1;
				found = 2;
				if(level >= 4)
				{
					printf("Found SPA_U_port qualifier, but current search is not using it, therefore this is not a match.\n");
				}
			}
			else
			{
				if(level >= 4)
				{
					printf("Found SPA_U_port qualifier\n");
				}
			}	
		}
		if(strncmp(&file[i],hub,strlen(hub)) == 0 && flag == 1 && hubUsed != 1)
		{
			found--;
			hubUsed = 1;
			if(level >= 4)
			{
				printf("Found SPA_U_hub value\n");
			}
		}
		if(port != NULL)
		{
			if(strncmp(&file[i],port,strlen(port)) == 0 && usingPort == 1 && flag == 1 && portUsed != 1)
			{
				found--;
				portUsed = 1;
				if(level >= 4)
				{
					printf("Found SPA_U_port value\n");
				}
			}
		}
		if(strncmp(&file[i],xTEDClose,strlen(xTEDClose)) == 0 && found == 1)
		{
			end = i;
		}
		if(strncmp(&file[i],"\"",1) == 0)
		{
			hubUsed = 1;
			portUsed = 1;
			
		}
		if(strncmp(&file[i],xTEDClose,strlen(xTEDClose)) == 0 && found != 1)
		{
			if(port == NULL)
				found = 2;
			else if(port[0] == '\0')
				found = 2;
			else
			{
				found = 3;
				portUsed = 0;
			}
			hubUsed = 0;
			started = 0;
			if(level >= 4)
			{
				printf("Resetting values after end of tag found\n");
			}
		}
		if(strncmp(&file[i],">",1) == 0)
		{
			flag = 0;
		}
		if(end > start)
		{
			length = end - start;
			memcpy(info,&file[start],length);
			info[length] = '\0';
			return 0;
		}
	}
	return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////
//
//  ParseItemName looks through the item name sent for any possible regex char and returns
//   a value specifying wether or not any were found
//  item - a char* that the item name will be stored in
//  level - the debug level at which to print
//
//	returns the REQTYPE_REGEX if any found otherwise 0
//
///////////////////////////////////////////////////////////////////////////////////////////

int ParseItemName(char *item, int level)
{
	int found = 0;
	const size_t ITEM_LENGTH = strlen(item);
	for(unsigned int i = 0; i < ITEM_LENGTH; i++)
	{
		if(item[i] == '*' || item[i] == '.' || item[i] == '[' || item[i] == ']' || item[i] == '{' || item[i] == '}' || item[i] == '(' ||  item[i] == ')' || item[i] == '\\' || item[i] == '+' || item[i] == '?' || item[i] == '|' || item[i] == '^' || item[i] == '$')
		{
			//A regular expressions character was found, return that type
		  	found = REQTYPE_REGEX;
			break;
		}
	}
	return found;
}

/*
	Description:
		Get the spaHub value from the xTEDS

	Input:
		buf - the xTEDS
		hub - a pointer to store the spaHub value in
		level - the level to print debug messages on

	Output:
		-1 - unable to get the spaHub value
		0 - successfully got the spaHub value

	Changed:
		None

*/
int GetSPAHub(char* buf, char* hub, int level)
{
	int devstart = 0,devend,num;
	char *spahub = "SPA_U_hub";
	char *camelspahub = "spaUHub";
	char *device;
	char name[128];
	int type = -1;
	unsigned int i = 0;
	unsigned int count = 0;
	size_t length = strlen(buf);

	device = NULL;
	if(buf[0] == '\0')
		return type;
	while(i < length)
	{
		devstart = 0;
		devend = 0;
		for(i = count; i < length; i++)
		{
			if(strncmp(&buf[i],spahub,strlen(spahub))== 0 || strncmp(&buf[i],camelspahub,strlen(camelspahub))== 0)
			{
				devstart = i - 1;
				if(level >= 4)
					printf("devstart is %d\n",devstart);
				type = 0;
			}
			if(devstart > 0 && strncmp(&buf[i],">",1) == 0)
			{
				devend = i + 1;
				if(level >= 4)
					printf("devend is %d\n",devend);
				device = (char*)malloc(1+devend-devstart);
        if (device == NULL)
          return -1;
				memcpy(device,&buf[devstart],devend-devstart);
				device[devend-devstart] = '\0';
				if(level >= 4)
					printf("SPA_U_HUB chunk is %s\n",device);
				break;
			}
			if(i+1 == strlen(buf))
				return -1;
		}
		num = GetAttribute(device,spahub,name,sizeof(name),level);
    if (device != NULL)
		  free(device);
		if(num < 1)
		{
			return -1;
		}
		else
		{
			memcpy(hub,name,strlen(name)+1);
			break;
		}
	}
	return type;
}
