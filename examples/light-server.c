/*
 * Example UPnP device/service, implementing the BinaryLight device and
 * SwitchPower services to emulate a light switch.
 *
 * The user interface is as minimal as possible so that the GUPnP concepts and
 * best practises are more apparent.  For a better implementation of
 * BinaryLight, see gupnp-tools.
 *
 * This example code is in the public domain.
 */

#include <libgupnp/gupnp.h>
#include <stdlib.h>
#include <gmodule.h>
#include <locale.h>

static gboolean status;
static gboolean quiet;

static GOptionEntry entries[] =
{
  { "quiet", 'q', 0, G_OPTION_ARG_NONE, &quiet, "Turn off output", NULL },
  { NULL }
};





char networkstatus[500] = "1";
char pairingstatus[500] = "Connecting";
char aplist[500] = "Page:1/1/2$alberto_678|11|65|WPA2PSK/AES,xfinitywifi|11|65|OPEN/NONE,";
char networklist[500] = "Page:1/1/3$10|ATT9bSX2cb|1|39|WPA2PSK/AES|11|alberto_678|11|70|WPA2PSK/AES|11|xfinitywifi|11|65|OPEN/NONE|";
char utc[500] = "0";
char timezone1[500] = "0";
char dst[500] = "0";
char homesettingsversion[500] = "2";
char energyperunitcost[500] = "111";
char currency[500] = "1";
char binarystate[500] = "8";
char duration[500] = "0";
char endaction[500] = "0";
char udn[500] = "0";
char mode[500] = "0";
char time1[500] = "0";
char level[500] = "0";
char option[500] = "0";
char reset[500] = "0";
char friendlyname[500] = "WeMo Insight 2";
char homeid[500] = "7444278";
char deviceid[500] = "5b9820b368ef79fd";
char smartdevinfo[500] = "http://10.0.0.158:49154/smartDev.txt";
char macaddr[500] = "149182B3A4D0";
char serialno[500] = "231624K120011C";
char pluginudn[500] = "uuid:Insight-1_0-231624K120011C";
char deviceicon[500] = "0";
char statelist[500] = "0";
char url[500] = "http://10.0.0.158:49154/icon.jpg";
char ruleoverridestatus[500] = "0";
char wdfile[500] = "Sending";
char signalstrength[500] = "63";
char serverenvironment[500] = "";
char turnserverenvironment[500] = "";
char serverenvironmenttype[500] = "0";
char iconversion[500] = "1";
char ruledata[500] = "-1|8|0|uuid:Insight-1_0-231624K120011C";
char manualtoggle[500] = "0";
char enableupload[500] = "0";
char countdownendtime[500] = "0";
char devicecurrenttime[500] = "0";
char homeinfo[500] = "0|7444278|wnJatQB+5EuXhdTnZnPI81BHGPglmgH0BMZrJWqCHjTtvw+j7mUGD3XGGakouy6GRHe9HxouwO7op21SFpyhIQ==|";
char logurl[500] = "http://10.0.0.158:49154/PluginLogs.txt";
char firmwareversion[500] = "FirmwareVersion:WeMo_WW_2.00.10966.PVT-OWRT-InsightV2|SkuNo:Plugin Device";
char firmwareupdatestatus[500] = "0";
char withunsignedimage[500] = "0";
char rulesdbpath[500] = "http://10.0.0.158:49154/rules.db";
char rulesdbversion[500] = "0";
char mon[500] = "";
char tues[500] = "";
char wed[500] = "";
char thurs[500] = "";
char fri[500] = "";
char sat[500] = "";
char sun[500] = "";
char ruleid[500] = "0";
char rulemsg[500] = "0";
char rulefreq[500] = "0";
char devicelist[500] = "0";
char devicecount[500] = "0";
char ruledbpath[500] = "0";
char ruledbversion[500] = "0";
char processdb[500] = "0";
char ruledbbody[500] = "0";
char errorinfo[500] = "0";
char extmetainfo[500] = "1|0|1|0|3:6:7|4|1511080104|7444278|1|Insight|2|111|1|8000|1|4";
char metainfo[500] = "149182B3A4D0|231624K120011C|Plugin Device|WeMo_WW_2.00.10966.PVT-OWRT-InsightV2|WeMo.Insight.11C|Insight";

char resultcode[500] = "0";
char description[500] = "0";
char smartuniqueid[500] = "0";
char smartdevicedescription[500] = "0";
char pluginprivatekey[500] = "0";
char smartprivatekey[500] = "0";
char numsmartdev[500] = "0";
char arpmac[500] = "0";
char deviceinformation[500] = "149182B3A4D0|WeMo_WW_2.00.10966.PVT-OWRT-InsightV2|1|49154|8|WeMo Insight";
char countdowntime[500] = "0";
char information[500] = "<Device><DeviceInformation><firmwareVersion>WeMo_WW_2.00.10966.PVT-OWRT-InsightV2</firmwareVersion><iconVersion>1</iconVersion><iconPort>49154</iconPort><macAddress>149182B3A4D0</macAddress><binaryState>8</binaryState><hwVersion>v2</hwVersion><deviceCurrentTime>1511080104</deviceCurrentTime><productName>Insight</productName><FriendlyName>WeMo Insight</FriendlyName><currentFWUpdateState>4</currentFWUpdateState><CountdownEndTime>0</CountdownEndTime></DeviceInformation></Device>";
char configurestate[500] = "0";
char bridgelist[500] = "0";
char mac[500] = "0";
char ssid[500] = "0";
char auth[500] = "0";
char password[500] = "0";
char encrypt[500] = "0";
char channel[500] = "0";
char timesync[500] = "0";
char instantpower[500] = "0";
char todaykwh[500] = "0";
char insightinfo[500] = "0";
char insightparams[500] = "0";
char todayontime[500] = "0";
char insbysince[500] = "0";
char onfor[500] = "0";
char todaysbytime[500] = "0";
char powerthreshold[500] = "8000";
char emailaddress[500] = "0";
char dataexporttype[500] = "0";
char lastdataexportts[500] = "0";
char registrationdata[500] = "";
char statuscode[500] = "RETRY";
char registrationstatus[500] = "F";
char manufacturedata[500] = "<?xml version=\"1.0\" encoding=\"utf-8\"?><ManufactureData><CountryCode></CountryCode><FirmwareVersion>WeMo_WW_2.00.10966.PVT-OWRT-InsightV2</FirmwareVersion><APMacAddress>14:91:82:B3:A4:D0</APMacAddress><STAMacAddress>14:91:82:B3:A4:D1</STAMacAddress><SSID>WeMo.Insight.11C</SSID><TargetCountry>US</TargetCountry><SerialNumber>231624K120011C</SerialNumber><PowerMeter><vRMS>124.128</vRMS><iRMS>0.020</iRMS><Watts>0.000</Watts><PF>0.000</PF><Freq>59.079</Freq><IntTemp>5.312</IntTemp><ExtTemp>0.000</ExtTemp></PowerMeter><USB></USB></ManufactureData>";





G_BEGIN_DECLS
G_MODULE_EXPORT void set_target_cb (GUPnPService *service,
                                    GUPnPServiceAction *action,
                                    gpointer user_data);
G_MODULE_EXPORT void get_target_cb (GUPnPService *service,
                                    GUPnPServiceAction *action,
                                    gpointer user_data);
G_MODULE_EXPORT void get_status_cb (GUPnPService *service,
                                    GUPnPServiceAction *action,
                                    gpointer user_data);
G_MODULE_EXPORT void query_target_cb (GUPnPService *service, char *variable,
                                      GValue *value, gpointer user_data);
G_MODULE_EXPORT void query_status_cb (GUPnPService *service, char *variable,
                                      GValue *value, gpointer user_data);



//////// Belkin WeMo Switch Start ///////////////////////////
G_MODULE_EXPORT void GetApList_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetNetworkList_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void ConnectHomeNetwork_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetNetworkStatus_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void CloseSetup_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void StopPair_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void TimeSync_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetTime_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetBinaryState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void UpdateInsightHomeSettings_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetInsightHomeSettings_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetInsightHomeSettings_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetLogLevelOption_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetFriendlyName_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void ReSetup_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetHomeId_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetHomeId_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetHomeInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetDeviceId_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetDeviceId_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetMacAddr_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetSerialNo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetPluginUDN_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetSmartDevInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void ShareHWInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void ChangeFriendlyName_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetSmartDevInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetRuleOverrideStatus_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetDeviceIcon_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetIconURL_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetLogFileURL_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void ChangeDeviceIcon_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetBinaryState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetMultiState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetCrockpotState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetCrockpotState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetWatchdogFile_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetSignalStrength_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetServerEnvironment_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetServerEnvironment_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetIconVersion_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetSimulatedRuleData_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void NotifyManualToggle_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void ControlCloudUpload_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void UpdateFirmware_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetFirmwareVersion_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void UpdateWeeklyCalendar_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void EditWeeklycalendar_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetRulesDBPath_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetRulesDBVersion_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetRulesDBVersion_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetRuleID_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void DeleteRuleID_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SimulatedRuleData_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void FetchRules_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void StoreRules_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetMetaInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetExtMetaInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void RemoteAccess_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetDeviceInformation_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetInformation_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void OpenInstaAP_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void CloseInstaAP_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetConfigureState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void InstaConnectHomeNetwork_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void UpdateBridgeList_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetRouterInformation_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void InstaRemoteAccess_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetPower_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetTodayKWH_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetAutoPowerThreshold_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetPowerThreshold_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void SetPowerThreshold_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void ResetPowerThreshold_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetInsightInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetInsightParams_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetONFor_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetInSBYSince_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetTodayONTime_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetTodaySBYTime_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void ScheduleDataExport_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetDataExportInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void PairAndRegister_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetRegistrationData_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetRegistrationStatus_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
G_MODULE_EXPORT void GetManufactureData_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data);
//////// Belkin WeMo Switch Start ///////////////////////////
G_END_DECLS
/*
 * Action handlers
 */

/* SetTarget */
G_MODULE_EXPORT void
set_target_cb (GUPnPService          *service,
               GUPnPServiceAction    *action,
               G_GNUC_UNUSED gpointer user_data)
{
  gboolean target;

  /* Get the new target value */
  gupnp_service_action_get (action,
                            "newTargetValue", G_TYPE_BOOLEAN, &target,
                            NULL);

  /* If the new target doesn't match the current status, change the status and
     emit a notification that the status has changed. */
  if (target != status) {
    status = target;
    gupnp_service_notify (service,
                          "Status", G_TYPE_BOOLEAN, status,
                          NULL);

    if (!quiet)
    {
      g_print ("The light is now %s.\n", status ? "on" : "off");
    }
  }

  /* Return success to the client */
  gupnp_service_action_return (action);
}

/* GetTarget */
G_MODULE_EXPORT void
get_target_cb (G_GNUC_UNUSED GUPnPService *service,
               GUPnPServiceAction         *action,
               G_GNUC_UNUSED gpointer      user_data)
{
  gupnp_service_action_set (action,
                            "RetTargetValue", G_TYPE_BOOLEAN, status,
                            NULL);
  gupnp_service_action_return (action);
}

/* GetStatus */
G_MODULE_EXPORT void
get_status_cb (G_GNUC_UNUSED GUPnPService *service,
               GUPnPServiceAction         *action,
               G_GNUC_UNUSED gpointer      user_data)
{
  gupnp_service_action_set (action,
                            "ResultStatus", G_TYPE_BOOLEAN, status,
                            NULL);
  gupnp_service_action_return (action);
}

/*
 * State Variable query handlers
 */

/* Target */
G_MODULE_EXPORT void
query_target_cb (G_GNUC_UNUSED GUPnPService *service,
                 G_GNUC_UNUSED char         *variable,
                 GValue                     *value,
                 G_GNUC_UNUSED gpointer      user_data)
{
  g_value_init (value, G_TYPE_BOOLEAN);
  g_value_set_boolean (value, status);
}

/* Status */
G_MODULE_EXPORT void
query_status_cb (G_GNUC_UNUSED GUPnPService *service,
                 G_GNUC_UNUSED char         *variable,
                 GValue                     *value,
                 G_GNUC_UNUSED gpointer      user_data)
{
  g_value_init (value, G_TYPE_BOOLEAN);
  g_value_set_boolean (value, status);
}


//////////////// Belkin WeMo Switch Action Starts ///////////////////////
G_MODULE_EXPORT void GetApList_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetApList_cb received\n");
gupnp_service_action_set (action, "ApList", G_TYPE_STRING, aplist, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetNetworkList_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetNetworkList_cb received\n");
gupnp_service_action_set (action, "NetworkList", G_TYPE_STRING, networklist, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void ConnectHomeNetwork_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("ConnectHomeNetwork_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetNetworkStatus_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetNetworkStatus_cb received\n");
gupnp_service_action_set (action, "NetworkStatus", G_TYPE_STRING, networkstatus, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void CloseSetup_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("CloseSetup_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void StopPair_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("StopPair_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void TimeSync_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("TimeSync_cb received\n");
gupnp_service_action_get (action, "UTC", G_TYPE_STRING, utc, NULL);
gupnp_service_action_get (action, "TimeZone", G_TYPE_STRING, timezone, NULL);
gupnp_service_action_get (action, "dst", G_TYPE_STRING, dst, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetTime_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetTime_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetBinaryState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetBinaryState_cb received\n");
g_print("%s\n", binarystate);
gupnp_service_action_get (action, "BinaryState", G_TYPE_STRING, binarystate, NULL);
gupnp_service_action_get (action, "Duration", G_TYPE_STRING, duration, NULL);
gupnp_service_action_get (action, "EndAction", G_TYPE_STRING, endaction, NULL);
gupnp_service_action_get (action, "UDN", G_TYPE_STRING, udn, NULL);
gupnp_service_action_set (action, "CountdownEndTime", G_TYPE_STRING, countdownendtime, NULL);
gupnp_service_action_set (action, "deviceCurrentTime", G_TYPE_STRING, devicecurrenttime, NULL);
g_print("%s\n", binarystate);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void UpdateInsightHomeSettings_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("UpdateInsightHomeSettings_cb received\n");
gupnp_service_action_get (action, "EnergyPerUnitCost", G_TYPE_STRING, energyperunitcost, NULL);
gupnp_service_action_get (action, "Currency", G_TYPE_STRING, currency, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetInsightHomeSettings_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetInsightHomeSettings_cb received\n");
gupnp_service_action_get (action, "EnergyPerUnitCost", G_TYPE_STRING, energyperunitcost, NULL);
gupnp_service_action_get (action, "Currency", G_TYPE_STRING, currency, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetInsightHomeSettings_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetInsightHomeSettings_cb received\n");
gupnp_service_action_set (action, "HomeSettingsVersion", G_TYPE_STRING, homesettingsversion, NULL);
gupnp_service_action_set (action, "EnergyPerUnitCost", G_TYPE_STRING, energyperunitcost, NULL);
gupnp_service_action_set (action, "Currency", G_TYPE_STRING, currency, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetLogLevelOption_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetLogLevelOption_cb received\n");
gupnp_service_action_get (action, "Level", G_TYPE_STRING, level, NULL);
gupnp_service_action_get (action, "Option", G_TYPE_STRING, option, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetFriendlyName_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetFriendlyName_cb received\n");
gupnp_service_action_get (action, "FriendlyName", G_TYPE_STRING, friendlyname, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void ReSetup_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("ReSetup_cb received\n");
gupnp_service_action_get (action, "Reset", G_TYPE_STRING, reset, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetHomeId_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetHomeId_cb received\n");
gupnp_service_action_get (action, "HomeId", G_TYPE_STRING, homeid, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetHomeId_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetHomeId_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetHomeInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetHomeInfo_cb received\n");
gupnp_service_action_set (action, "GetHomeInfo", G_TYPE_STRING, homeinfo, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetDeviceId_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetDeviceId_cb received\n");
gupnp_service_action_get (action, "SetDeviceId", G_TYPE_STRING, deviceid, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetDeviceId_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetDeviceId_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetMacAddr_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetMacAddr_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetSerialNo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetSerialNo_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetPluginUDN_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetPluginUDN_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetSmartDevInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetSmartDevInfo_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void ShareHWInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("ShareHWInfo_cb received\n");
gupnp_service_action_get (action, "Udn", G_TYPE_STRING, udn, NULL);
gupnp_service_action_get (action, "HomeId", G_TYPE_STRING, homeid, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void ChangeFriendlyName_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("ChangeFriendlyName_cb received\n");
gupnp_service_action_get (action, "FriendlyName", G_TYPE_STRING, friendlyname, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetSmartDevInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetSmartDevInfo_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetRuleOverrideStatus_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetRuleOverrideStatus_cb received\n");
gupnp_service_action_get (action, "RuleOverrideStatus", G_TYPE_STRING, ruleoverridestatus, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetDeviceIcon_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetDeviceIcon_cb received\n");
gupnp_service_action_get (action, "DeviceIcon", G_TYPE_STRING, deviceicon, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetIconURL_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetIconURL_cb received\n");
gupnp_service_action_set (action, "URL", G_TYPE_STRING, url, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetLogFileURL_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetLogFileURL_cb received\n");
gupnp_service_action_set (action, "LOGURL", G_TYPE_STRING, logurl, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void ChangeDeviceIcon_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("ChangeDeviceIcon_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetBinaryState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetBinaryState_cb received\n");
gupnp_service_action_set (action, "BinaryState", G_TYPE_STRING, binarystate, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetMultiState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetMultiState_cb received\n");
gupnp_service_action_get (action, "state", G_TYPE_STRING, statelist, NULL);
gupnp_service_action_get (action, "state", G_TYPE_STRING, statelist, NULL);
gupnp_service_action_get (action, "state", G_TYPE_STRING, statelist, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetCrockpotState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetCrockpotState_cb received\n");
gupnp_service_action_get (action, "mode", G_TYPE_STRING, mode, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetCrockpotState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetCrockpotState_cb received\n");
gupnp_service_action_set (action, "mode", G_TYPE_STRING, mode, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetWatchdogFile_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetWatchdogFile_cb received\n");
gupnp_service_action_set (action, "WDFile", G_TYPE_STRING, wdfile, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetSignalStrength_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetSignalStrength_cb received\n");
gupnp_service_action_get (action, "SignalStrength", G_TYPE_STRING, signalstrength, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetServerEnvironment_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetServerEnvironment_cb received\n");
gupnp_service_action_get (action, "ServerEnvironment", G_TYPE_STRING, serverenvironment, NULL);
gupnp_service_action_get (action, "TurnServerEnvironment", G_TYPE_STRING, turnserverenvironment, NULL);
gupnp_service_action_get (action, "ServerEnvironmentType", G_TYPE_STRING, serverenvironmenttype, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetServerEnvironment_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetServerEnvironment_cb received\n");
gupnp_service_action_set (action, "ServerEnvironment", G_TYPE_STRING, serverenvironment, NULL);
gupnp_service_action_set (action, "TurnServerEnvironment", G_TYPE_STRING, turnserverenvironment, NULL);
gupnp_service_action_set (action, "ServerEnvironmentType", G_TYPE_STRING, serverenvironmenttype, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetIconVersion_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetIconVersion_cb received\n");
gupnp_service_action_set (action, "IconVersion", G_TYPE_STRING, iconversion, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetSimulatedRuleData_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetSimulatedRuleData_cb received\n");
gupnp_service_action_set (action, "GetSimulatedRuleData", G_TYPE_STRING, ruledata, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void NotifyManualToggle_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("NotifyManualToggle_cb received\n");
gupnp_service_action_set (action, "NotifyManualToggle", G_TYPE_STRING, manualtoggle, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void ControlCloudUpload_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("ControlCloudUpload_cb received\n");
gupnp_service_action_get (action, "EnableUpload", G_TYPE_STRING, enableupload, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void UpdateFirmware_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("UpdateFirmware_cb received\n");
gupnp_service_action_get (action, "WithUnsignedImage", G_TYPE_STRING, withunsignedimage, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetFirmwareVersion_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetFirmwareVersion_cb received\n");
gupnp_service_action_set (action, "FirmwareVersion", G_TYPE_STRING, firmwareversion, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void UpdateWeeklyCalendar_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("UpdateWeeklyCalendar_cb received\n");
gupnp_service_action_get (action, "Mon", G_TYPE_STRING, mon, NULL);
gupnp_service_action_get (action, "Tues", G_TYPE_STRING, tues, NULL);
gupnp_service_action_get (action, "Wed", G_TYPE_STRING, wed, NULL);
gupnp_service_action_get (action, "Thurs", G_TYPE_STRING, thurs, NULL);
gupnp_service_action_get (action, "Fri", G_TYPE_STRING, fri, NULL);
gupnp_service_action_get (action, "Sat", G_TYPE_STRING, sat, NULL);
gupnp_service_action_get (action, "Sun", G_TYPE_STRING, sun, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void EditWeeklycalendar_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("EditWeeklycalendar_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetRulesDBPath_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetRulesDBPath_cb received\n");
gupnp_service_action_set (action, "RulesDBPath", G_TYPE_STRING, rulesdbpath, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetRulesDBVersion_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetRulesDBVersion_cb received\n");
gupnp_service_action_get (action, "RulesDBVersion", G_TYPE_STRING, rulesdbversion, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetRulesDBVersion_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetRulesDBVersion_cb received\n");
gupnp_service_action_set (action, "RulesDBVersion", G_TYPE_STRING, rulesdbversion, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetRuleID_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetRuleID_cb received\n");
gupnp_service_action_get (action, "RuleID", G_TYPE_STRING, ruleid, NULL);
gupnp_service_action_get (action, "RuleMsg", G_TYPE_STRING, rulemsg, NULL);
gupnp_service_action_get (action, "RuleFreq", G_TYPE_STRING, rulefreq, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void DeleteRuleID_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("DeleteRuleID_cb received\n");
gupnp_service_action_get (action, "RuleID", G_TYPE_STRING, ruleid, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SimulatedRuleData_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SimulatedRuleData_cb received\n");
gupnp_service_action_get (action, "DeviceList", G_TYPE_STRING, devicelist, NULL);
gupnp_service_action_get (action, "DeviceCount", G_TYPE_STRING, devicecount, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void FetchRules_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("FetchRules_cb received\n");
gupnp_service_action_set (action, "ruleDbPath", G_TYPE_STRING, ruledbpath, NULL);
gupnp_service_action_set (action, "ruleDbVersion", G_TYPE_STRING, ruledbversion, NULL);
gupnp_service_action_set (action, "errorInfo", G_TYPE_STRING, errorinfo, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void StoreRules_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("StoreRules_cb received\n");
gupnp_service_action_get (action, "ruleDbVersion", G_TYPE_STRING, ruledbversion, NULL);
gupnp_service_action_get (action, "processDb", G_TYPE_STRING, processdb, NULL);
gupnp_service_action_get (action, "ruleDbBody", G_TYPE_STRING, ruledbbody, NULL);
gupnp_service_action_set (action, "errorInfo", G_TYPE_STRING, errorinfo, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetMetaInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetMetaInfo_cb received\n");
gupnp_service_action_set (action, "MetaInfo", G_TYPE_STRING, metainfo, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetExtMetaInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetExtMetaInfo_cb received\n");
gupnp_service_action_set (action, "ExtMetaInfo", G_TYPE_STRING, extmetainfo, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void RemoteAccess_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("RemoteAccess_cb received\n");
gupnp_service_action_get (action, "HomeId", G_TYPE_STRING, homeid, NULL);
gupnp_service_action_get (action, "pluginprivateKey", G_TYPE_STRING, pluginprivatekey, NULL);
gupnp_service_action_get (action, "smartprivateKey", G_TYPE_STRING, smartprivatekey, NULL);
gupnp_service_action_get (action, "smartUniqueId", G_TYPE_STRING, smartuniqueid, NULL);
gupnp_service_action_get (action, "numSmartDev", G_TYPE_STRING, numsmartdev, NULL);
gupnp_service_action_set (action, "ArpMac", G_TYPE_STRING, arpmac, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetDeviceInformation_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetDeviceInformation_cb received\n");
gupnp_service_action_set (action, "DeviceInformation", G_TYPE_STRING, deviceinformation, NULL);
gupnp_service_action_set (action, "CountdownTime", G_TYPE_STRING, countdowntime, NULL);
gupnp_service_action_set (action, "TimeSync", G_TYPE_STRING, timesync, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetInformation_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetInformation_cb received\n");
gupnp_service_action_set (action, "Information", G_TYPE_STRING, information, NULL);
gupnp_service_action_set (action, "TimeSync", G_TYPE_STRING, timesync, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void OpenInstaAP_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("OpenInstaAP_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void CloseInstaAP_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("CloseInstaAP_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetConfigureState_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetConfigureState_cb received\n");
gupnp_service_action_set (action, "ConfigureState", G_TYPE_STRING, configurestate, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void InstaConnectHomeNetwork_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("InstaConnectHomeNetwork_cb received\n");
gupnp_service_action_get (action, "ssid", G_TYPE_STRING, ssid, NULL);
gupnp_service_action_get (action, "auth", G_TYPE_STRING, auth, NULL);
gupnp_service_action_get (action, "password", G_TYPE_STRING, password, NULL);
gupnp_service_action_get (action, "encrypt", G_TYPE_STRING, encrypt, NULL);
gupnp_service_action_get (action, "channel", G_TYPE_STRING, channel, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void UpdateBridgeList_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("UpdateBridgeList_cb received\n");
gupnp_service_action_get (action, "BridgeList", G_TYPE_STRING, bridgelist, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetRouterInformation_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetRouterInformation_cb received\n");
gupnp_service_action_set (action, "mac", G_TYPE_STRING, mac, NULL);
gupnp_service_action_set (action, "ssid", G_TYPE_STRING, ssid, NULL);
gupnp_service_action_set (action, "auth", G_TYPE_STRING, auth, NULL);
gupnp_service_action_set (action, "password", G_TYPE_STRING, password, NULL);
gupnp_service_action_set (action, "encrypt", G_TYPE_STRING, encrypt, NULL);
gupnp_service_action_set (action, "channel", G_TYPE_STRING, channel, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void InstaRemoteAccess_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("InstaRemoteAccess_cb received\n");
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetPower_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetPower_cb received\n");
gupnp_service_action_set (action, "InstantPower", G_TYPE_STRING, instantpower, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetTodayKWH_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetTodayKWH_cb received\n");
gupnp_service_action_set (action, "TodayKWH", G_TYPE_STRING, todaykwh, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetAutoPowerThreshold_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetAutoPowerThreshold_cb received\n");
gupnp_service_action_get (action, "PowerThreshold", G_TYPE_STRING, powerthreshold, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetPowerThreshold_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetPowerThreshold_cb received\n");
gupnp_service_action_set (action, "PowerThreshold", G_TYPE_STRING, powerthreshold, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void SetPowerThreshold_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("SetPowerThreshold_cb received\n");
gupnp_service_action_get (action, "PowerThreshold", G_TYPE_STRING, powerthreshold, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void ResetPowerThreshold_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("ResetPowerThreshold_cb received\n");
gupnp_service_action_get (action, "PowerThreshold", G_TYPE_STRING, powerthreshold, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetInsightInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetInsightInfo_cb received\n");
gupnp_service_action_set (action, "InsightInfo", G_TYPE_STRING, insightinfo, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetInsightParams_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetInsightParams_cb received\n");
gupnp_service_action_set (action, "InsightParams", G_TYPE_STRING, insightparams, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetONFor_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetONFor_cb received\n");
gupnp_service_action_set (action, "ONFor", G_TYPE_STRING, onfor, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetInSBYSince_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetInSBYSince_cb received\n");
gupnp_service_action_set (action, "InSBYSince", G_TYPE_STRING, insbysince, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetTodayONTime_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetTodayONTime_cb received\n");
gupnp_service_action_set (action, "TodayONTime", G_TYPE_STRING, todayontime, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetTodaySBYTime_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetTodaySBYTime_cb received\n");
gupnp_service_action_set (action, "TodaySBYTime", G_TYPE_STRING, todaysbytime, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void ScheduleDataExport_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("ScheduleDataExport_cb received\n");
gupnp_service_action_get (action, "EmailAddress", G_TYPE_STRING, emailaddress, NULL);
gupnp_service_action_get (action, "DataExportType", G_TYPE_STRING, dataexporttype, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetDataExportInfo_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetDataExportInfo_cb received\n");
gupnp_service_action_set (action, "LastDataExportTS", G_TYPE_STRING, lastdataexportts, NULL);
gupnp_service_action_set (action, "DataExportType", G_TYPE_STRING, dataexporttype, NULL);
gupnp_service_action_set (action, "EmailAddress", G_TYPE_STRING, emailaddress, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void PairAndRegister_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("PairAndRegister_cb received\n");
gupnp_service_action_get (action, "RegistrationData", G_TYPE_STRING, registrationdata, NULL);
gupnp_service_action_set (action, "PairingStatus", G_TYPE_STRING, pairingstatus, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetRegistrationData_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetRegistrationData_cb received\n");
gupnp_service_action_set (action, "RegistrationData", G_TYPE_STRING, registrationdata, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetRegistrationStatus_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetRegistrationStatus_cb received\n");
gupnp_service_action_set (action, "RegistrationStatus", G_TYPE_STRING, registrationstatus, NULL);
gupnp_service_action_set (action, "StatusCode", G_TYPE_STRING, statuscode, NULL);
    gupnp_service_action_return (action);
}

G_MODULE_EXPORT void GetManufactureData_cb(GUPnPService *service, GUPnPServiceAction *action, G_GNUC_UNUSED gpointer user_data) {
    g_print("GetManufactureData_cb received\n");
gupnp_service_action_set (action, "ManufactureData", G_TYPE_STRING, manufacturedata, NULL);
    gupnp_service_action_return (action);
}


//////////////// Belkin WeMo Switch Action Starts ///////////////////////


int
main (G_GNUC_UNUSED int argc, G_GNUC_UNUSED char **argv)
{
  GOptionContext *optionContext;
  GMainLoop *main_loop;
  GError *error = NULL;
  GUPnPContext *context;
  GUPnPRootDevice *belkindevice;

  GUPnPServiceInfo *setupserviceService;
GUPnPServiceInfo *timesyncserviceService;
GUPnPServiceInfo *eventserviceService;
GUPnPServiceInfo *firmwareupdateService;
GUPnPServiceInfo *rulesserviceService;
GUPnPServiceInfo *metainfoserviceService;
GUPnPServiceInfo *remoteaccessService;
GUPnPServiceInfo *deviceinfoserviceService;
GUPnPServiceInfo *insightserviceService;
GUPnPServiceInfo *smartsetupService;
GUPnPServiceInfo *manufactureService;

setlocale(LC_ALL, "en_US.utf8");

GString *gs = g_string_new("abc");
g_print("%s\n", gs->str);


  
  optionContext = g_option_context_new (NULL);
  g_option_context_add_main_entries (optionContext, entries, NULL);
  if (!g_option_context_parse (optionContext, &argc, &argv, &error))
  {
    g_print ("option parsing failed: %s\n", error->message);
    exit (1);
  }

  /* By default the light is off */
  status = FALSE;
  if (!quiet)
  {
    g_print ("The light is now %s.\n", status ? "on" : "off");
  }

  /* Create the UPnP context */
  context = gupnp_context_new (NULL, 0, &error);
  if (error) {
    g_printerr ("Error creating the GUPnP context: %s\n",
		error->message);
    g_error_free (error);

    return EXIT_FAILURE;
  }


  //////// Belkin WeMo Switch Start ///////////////////////////
  belkindevice = gupnp_root_device_new (context, "setup.xml", ".", &error);
  if (error != NULL) {
    g_printerr ("Error creating the GUPnP root device: %s\n",
                error->message);

    g_error_free (error);

    return EXIT_FAILURE;
  }
  gupnp_root_device_set_available (belkindevice, TRUE);


setupserviceService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:WiFiSetup:1");
timesyncserviceService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:timesync:1");
eventserviceService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:basicevent:1");
firmwareupdateService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:firmwareupdate:1");
rulesserviceService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:rules:1");
metainfoserviceService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:metainfo:1");
remoteaccessService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:remoteaccess:1");
deviceinfoserviceService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:deviceinfo:1");
insightserviceService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:insight:1");
smartsetupService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:smartsetup:1");
manufactureService = gupnp_device_info_get_service(GUPNP_DEVICE_INFO (belkindevice), "urn:Belkin:service:manufacture:1");
  if (!eventserviceService) {
    g_printerr("Cannot get basiceventservice\n");
  }


g_signal_connect(GUPNP_SERVICE(setupserviceService), "action-invoked::GetApList", G_CALLBACK(GetApList_cb), NULL);
g_signal_connect(GUPNP_SERVICE(setupserviceService), "action-invoked::GetNetworkList", G_CALLBACK(GetNetworkList_cb), NULL);
g_signal_connect(GUPNP_SERVICE(setupserviceService), "action-invoked::ConnectHomeNetwork", G_CALLBACK(ConnectHomeNetwork_cb), NULL);
g_signal_connect(GUPNP_SERVICE(setupserviceService), "action-invoked::GetNetworkStatus", G_CALLBACK(GetNetworkStatus_cb), NULL);
g_signal_connect(GUPNP_SERVICE(setupserviceService), "action-invoked::CloseSetup", G_CALLBACK(CloseSetup_cb), NULL);
g_signal_connect(GUPNP_SERVICE(setupserviceService), "action-invoked::StopPair", G_CALLBACK(StopPair_cb), NULL);
g_signal_connect(GUPNP_SERVICE(timesyncserviceService), "action-invoked::TimeSync", G_CALLBACK(TimeSync_cb), NULL);
g_signal_connect(GUPNP_SERVICE(timesyncserviceService), "action-invoked::GetTime", G_CALLBACK(GetTime_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetBinaryState", G_CALLBACK(SetBinaryState_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::UpdateInsightHomeSettings", G_CALLBACK(UpdateInsightHomeSettings_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetInsightHomeSettings", G_CALLBACK(SetInsightHomeSettings_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetInsightHomeSettings", G_CALLBACK(GetInsightHomeSettings_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetLogLevelOption", G_CALLBACK(SetLogLevelOption_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetFriendlyName", G_CALLBACK(GetFriendlyName_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::ReSetup", G_CALLBACK(ReSetup_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetHomeId", G_CALLBACK(SetHomeId_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetHomeId", G_CALLBACK(GetHomeId_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetHomeInfo", G_CALLBACK(GetHomeInfo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetDeviceId", G_CALLBACK(SetDeviceId_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetDeviceId", G_CALLBACK(GetDeviceId_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetMacAddr", G_CALLBACK(GetMacAddr_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetSerialNo", G_CALLBACK(GetSerialNo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetPluginUDN", G_CALLBACK(GetPluginUDN_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetSmartDevInfo", G_CALLBACK(GetSmartDevInfo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::ShareHWInfo", G_CALLBACK(ShareHWInfo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::ChangeFriendlyName", G_CALLBACK(ChangeFriendlyName_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetSmartDevInfo", G_CALLBACK(SetSmartDevInfo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetRuleOverrideStatus", G_CALLBACK(GetRuleOverrideStatus_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetDeviceIcon", G_CALLBACK(GetDeviceIcon_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetIconURL", G_CALLBACK(GetIconURL_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetLogFileURL", G_CALLBACK(GetLogFileURL_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::ChangeDeviceIcon", G_CALLBACK(ChangeDeviceIcon_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetBinaryState", G_CALLBACK(GetBinaryState_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetMultiState", G_CALLBACK(SetMultiState_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetCrockpotState", G_CALLBACK(SetCrockpotState_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetCrockpotState", G_CALLBACK(GetCrockpotState_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetWatchdogFile", G_CALLBACK(GetWatchdogFile_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetSignalStrength", G_CALLBACK(GetSignalStrength_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::SetServerEnvironment", G_CALLBACK(SetServerEnvironment_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetServerEnvironment", G_CALLBACK(GetServerEnvironment_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetIconVersion", G_CALLBACK(GetIconVersion_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::GetSimulatedRuleData", G_CALLBACK(GetSimulatedRuleData_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::NotifyManualToggle", G_CALLBACK(NotifyManualToggle_cb), NULL);
g_signal_connect(GUPNP_SERVICE(eventserviceService), "action-invoked::ControlCloudUpload", G_CALLBACK(ControlCloudUpload_cb), NULL);
g_signal_connect(GUPNP_SERVICE(firmwareupdateService), "action-invoked::UpdateFirmware", G_CALLBACK(UpdateFirmware_cb), NULL);
g_signal_connect(GUPNP_SERVICE(firmwareupdateService), "action-invoked::GetFirmwareVersion", G_CALLBACK(GetFirmwareVersion_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::UpdateWeeklyCalendar", G_CALLBACK(UpdateWeeklyCalendar_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::EditWeeklycalendar", G_CALLBACK(EditWeeklycalendar_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::GetRulesDBPath", G_CALLBACK(GetRulesDBPath_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::SetRulesDBVersion", G_CALLBACK(SetRulesDBVersion_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::GetRulesDBVersion", G_CALLBACK(GetRulesDBVersion_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::SetRuleID", G_CALLBACK(SetRuleID_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::DeleteRuleID", G_CALLBACK(DeleteRuleID_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::SimulatedRuleData", G_CALLBACK(SimulatedRuleData_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::FetchRules", G_CALLBACK(FetchRules_cb), NULL);
g_signal_connect(GUPNP_SERVICE(rulesserviceService), "action-invoked::StoreRules", G_CALLBACK(StoreRules_cb), NULL);
g_signal_connect(GUPNP_SERVICE(metainfoserviceService), "action-invoked::GetMetaInfo", G_CALLBACK(GetMetaInfo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(metainfoserviceService), "action-invoked::GetExtMetaInfo", G_CALLBACK(GetExtMetaInfo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(remoteaccessService), "action-invoked::RemoteAccess", G_CALLBACK(RemoteAccess_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::GetDeviceInformation", G_CALLBACK(GetDeviceInformation_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::GetInformation", G_CALLBACK(GetInformation_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::OpenInstaAP", G_CALLBACK(OpenInstaAP_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::CloseInstaAP", G_CALLBACK(CloseInstaAP_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::GetConfigureState", G_CALLBACK(GetConfigureState_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::InstaConnectHomeNetwork", G_CALLBACK(InstaConnectHomeNetwork_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::UpdateBridgeList", G_CALLBACK(UpdateBridgeList_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::GetRouterInformation", G_CALLBACK(GetRouterInformation_cb), NULL);
g_signal_connect(GUPNP_SERVICE(deviceinfoserviceService), "action-invoked::InstaRemoteAccess", G_CALLBACK(InstaRemoteAccess_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetPower", G_CALLBACK(GetPower_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetTodayKWH", G_CALLBACK(GetTodayKWH_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::SetAutoPowerThreshold", G_CALLBACK(SetAutoPowerThreshold_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetPowerThreshold", G_CALLBACK(GetPowerThreshold_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::SetPowerThreshold", G_CALLBACK(SetPowerThreshold_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::ResetPowerThreshold", G_CALLBACK(ResetPowerThreshold_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetInsightInfo", G_CALLBACK(GetInsightInfo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetInsightParams", G_CALLBACK(GetInsightParams_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetONFor", G_CALLBACK(GetONFor_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetInSBYSince", G_CALLBACK(GetInSBYSince_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetTodayONTime", G_CALLBACK(GetTodayONTime_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetTodaySBYTime", G_CALLBACK(GetTodaySBYTime_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::ScheduleDataExport", G_CALLBACK(ScheduleDataExport_cb), NULL);
g_signal_connect(GUPNP_SERVICE(insightserviceService), "action-invoked::GetDataExportInfo", G_CALLBACK(GetDataExportInfo_cb), NULL);
g_signal_connect(GUPNP_SERVICE(smartsetupService), "action-invoked::PairAndRegister", G_CALLBACK(PairAndRegister_cb), NULL);
g_signal_connect(GUPNP_SERVICE(smartsetupService), "action-invoked::GetRegistrationData", G_CALLBACK(GetRegistrationData_cb), NULL);
g_signal_connect(GUPNP_SERVICE(smartsetupService), "action-invoked::GetRegistrationStatus", G_CALLBACK(GetRegistrationStatus_cb), NULL);
g_signal_connect(GUPNP_SERVICE(manufactureService), "action-invoked::GetManufactureData", G_CALLBACK(GetManufactureData_cb), NULL);  //////// Belkin WeMo Switch End ///////////////////////////
  
  /* Run the main loop */
  main_loop = g_main_loop_new (NULL, FALSE);
  g_main_loop_run (main_loop);

  /* Cleanup */
  g_main_loop_unref (main_loop);
//  g_object_unref (service);
  g_object_unref (context);
  
  return EXIT_SUCCESS;
}
