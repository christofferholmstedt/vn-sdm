/*calculates a check sum for SDM messages
inspired by "A Painless Guide to CRC Error Detection Algorithms
at http://www.geocities.com/SiliconValley/Pines/8659/crc/htm
accessed 5APR2005*/

#include "crcmodel.h"
#include <string.h>
#include <stdio.h>

/*return the checksum of given message*/
int checksum(char* msg,int len)
{
	int i;
	cm_t model;
	p_cm_t p_cm;
	p_cm = &model;

	/*CRC-32*/
	p_cm->cm_width = 32;
	p_cm->cm_poly  = 0x04C11DB7;
	p_cm->cm_init  = 0xFFFFFFFF;
	p_cm->cm_refin = TRUE;
	p_cm->cm_refot = TRUE;
	p_cm->cm_xorot = 0xFFFFFFFF;

	cm_ini(p_cm);
	for(i=0;i<len;i++)
		cm_nxt(p_cm,msg[i]);

	return cm_crc(p_cm);
}

/*check msg to see if it is vaild*/
int valid(char* msg,int len)
{
	int c_sum ;
	int c_sum_given;
	c_sum = checksum(msg,len-4);
	memcpy (&c_sum_given,msg+len-4,4); /*grab checksum*/
	/*printf("Expecting %x. Rec'd %x\n",c_sum_given,c_sum);*/
	if (c_sum==c_sum_given)
		return TRUE; /*message is valid*/
	/*printf("Invalid checksum");*/
	return FALSE;
}
