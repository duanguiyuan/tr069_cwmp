#include "cwmp/model.h"
#include "data_model.h"
#include "cwmp_module.h"
#include "InternetGatewayDevice/InternetGatewayDevice.c"

model_func_t ModelFunction[] =
{
	{"TRF_Get_FrequencyPoint", cpe_get_igd_FreqPoint},
	{"TRF_Get_X_Band", cpe_get_igd_Band},
	{"TRF_Get_CellId", cpe_get_igd_CellId},
	{"TRF_Get_PhysicsCellId", cpe_get_igd_PhysicsCellId},
	{"TRF_Get_X_CMCC_RSRP", cpe_get_igd_RSRP},
	{"TRF_Get_RSRQ", cpe_get_igd_RSRQ},
	{"TRF_Get_SINR", cpe_get_igd_SINR},
	{"TRF_Get_UpstreamTotalByte", cpe_get_igd_UpstreamTotalByte},
	{"TRF_Get_DownstreamTotalByte", cpe_get_igd_DownstreamTotalByte},
	
    {"cpe_get_igd_di_manufacturer", cpe_get_igd_di_manufacturer},
    {"cpe_get_igd_di_manufactureroui", cpe_get_igd_di_manufactureroui},
    {"cpe_get_igd_di_productclass", cpe_get_igd_di_productclass},
    {"cpe_get_igd_di_serialnumber", cpe_get_igd_di_serialnumber},
    {"cpe_get_igd_di_specversion", cpe_get_igd_di_specversion},
    {"cpe_get_igd_di_hardwareversion", cpe_get_igd_di_hardwareversion},
    {"cpe_get_igd_di_softwareversion", cpe_get_igd_di_softwareversion},
    {"cpe_get_igd_di_provisioningcode", cpe_get_igd_di_provisioningcode},

    {"cpe_get_igd_ms_username", cpe_get_igd_ms_username},
    {"cpe_get_igd_ms_password", cpe_get_igd_ms_password},
    {"cpe_get_igd_ms_connectionrequesturl", cpe_get_igd_ms_connectionrequesturl},
    {"cpe_get_igd_ms_connectionrequestusername", cpe_get_igd_ms_connectionrequestusername},
    {"cpe_get_igd_ms_connectionrequestpassword", cpe_get_igd_ms_connectionrequestpassword},
    {"cpe_set_igd_ms_connectionrequestusername", cpe_set_igd_ms_connectionrequestusername},
    {"cpe_set_igd_ms_connectionrequestpassword", cpe_set_igd_ms_connectionrequestpassword},

	{"cpe_get_igd_ms_periodicInformEnable", cpe_get_igd_ms_periodicInformEnable},
	{"cpe_get_igd_ms_PeriodicInformInterval", cpe_get_igd_ms_PeriodicInformInterval},
	{"cpe_get_igd_ms_PeriodicInformTime", cpe_get_igd_ms_PeriodicInformTime},

	{"cpe_set_igd_ms_periodicInformEnable", cpe_set_igd_ms_periodicInformEnable},
	{"cpe_set_igd_ms_PeriodicInformInterval", cpe_set_igd_ms_PeriodicInformInterval},
	{"cpe_set_igd_ms_PeriodicInformTime", cpe_set_igd_ms_PeriodicInformTime},
	
	{"cpe_refresh_igd_wandevice", cpe_refresh_igd_wandevice},
    {"cpe_refresh_igd_wanconnectiondevice", cpe_refresh_igd_wanconnectiondevice},
    {"cpe_refresh_igd_wanipconnection", cpe_refresh_igd_wanipconnection},

	/*add by duanguiyuan 20160909*/
	{"cpe_get_igd_wanipconnection_ExternalIPAddress", cpe_get_igd_wanipconnection_ExternalIPAddress},

};

int get_index_after_paramname(parameter_node_t * param, const char * tag_name)
{
    parameter_node_t * parent;
    parameter_node_t * tmp;
    for(parent=param->parent, tmp = param; parent; tmp = parent, parent = parent->parent)
    {
        if(TRstrcmp(parent->name, tag_name) == 0)
        {
             if(is_digit(tmp->name) == 0)
             {
                return TRatoi(tmp->name);   
             }
        }        
    }
    return -1;
}


void cwmp_model_load(cwmp_t * cwmp, const char * xmlfile)
{  

    cwmp_model_load_xml(cwmp, xmlfile, ModelFunction, sizeof(ModelFunction)/sizeof(model_func_t));
}


