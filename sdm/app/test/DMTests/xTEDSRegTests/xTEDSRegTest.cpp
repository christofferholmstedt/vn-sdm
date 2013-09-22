#include "ActivityAgent.h"
#include "ActivityManager.h"
#include "AdcoleDigitalSS.h"
#include "ADCSController.h"
#include "AnglAccelToTorque.h"
#include "Battery.h"
#include "BIT.h"
#include "ChargeBatteries.h"
#include "CSSAssy.h"
#include "DigitalSS.h"
#include "DownlinkController.h"
#include "GPS_Full.h"
#include "GPS.h"
#include "IDS.h"
#include "iMESA.h"
#include "IRU.h"
#include "MagTorqueRod.h"
#include "OOCE.h"
#include "PowerController.h"
#include "RoboHub.h"
#include "RoboHub_lean.h"
#include "RWheelAssy.h"
#include "RWheelSingle.h"
#include "SolarArray.h"
#include "StarCamera.h"
#include "Targeting.h"
#include "TelemetryHandler.h"
#include "ThreeAxisMagnetometer.h"
#include "Thruster.h"
#include "VehicleService.h"

#include "../../../../common/message/SDMxTEDS.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int SLEEP_VAL = 50000;

int main (int argc, char** argv)
{
	SDMInit(argc, argv);
	
	SDMxTEDS xTEDSMsg;
	
	strcpy(xTEDSMsg.xTEDS, _STRING_ACTIVITYAGENT_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_ACTIVITYMANAGER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_ADCOLE_NRL_DIGITAL_SUN_SENSOR_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_ADCSCONTROLLER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_TORQUECONTROL_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_BATTERY_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_EXAMPLE_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_CHARGEBATTERIES_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_COARSE_SUN_SENSOR_ASSEMBLY_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_ADCOLENRLDIGITALSUNSENSOR_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_DOWNLINKCONTROLLER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_FULLGPSRECEIVER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_BASICGPSRECEIVER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_INTELLIGENTDATASTORE_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_IMESA_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_LN200S_IRU_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_BASICMAGNETICTORQUEROD_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_OOCE_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_POWERCONTROLLER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_ROBOHUB_8_PORT_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_REACTIONWHEELASSEMBLY_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_SINGLE_REACTION_WHEEL_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_SOLARARRAY_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_TERMAHE5ASSTARTRACKER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_TARGETINGCONTROL_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_TELEMETRYHANDLER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_THREE_AXIS_MAGNETOMETER_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	//strcpy(xTEDSMsg.xTEDS, _STRING_MONOPROPELLANTTHRUSTER_XTEDS);
	//xTEDSMsg.Send();
	//usleep(SLEEP_VAL);
	
	strcpy(xTEDSMsg.xTEDS, _STRING_VEHICLEINFORMATIONSERVICE_XTEDS);
	xTEDSMsg.Send();
	usleep(SLEEP_VAL);
	
	return 0;
}
