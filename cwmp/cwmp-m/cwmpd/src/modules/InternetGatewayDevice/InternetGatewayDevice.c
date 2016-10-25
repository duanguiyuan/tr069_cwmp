#include "DeviceInfo/DeviceInfo.c"
#include "ManagementServer/ManagementServer.c"
#include "WANDevice/WANDevice.c"
#include "WANDevice/WANConnectionDevice/WANConnectionDevice.c"
#include "WANDevice/WANConnectionDevice/WANIPConnection.c"



char* cpe_get_igd_device_summary(void * arg, void * pool)
{
    //pool_t * p = (pool_t *)pool;
    return	NULL;
}

char* cpe_get_igd_lan_device_number_of_entries(void * arg, void * pool)
{
    //pool_t * p = (pool_t *)pool;
    return NULL;
}
int cpe_get_igd_FreqPoint(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = cwmp_conf_pool_get(pool, "lteinfo:freqpoint");
    return	FAULT_CODE_OK;
}

int cpe_get_igd_Band(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = cwmp_conf_pool_get(pool, "lteinfo:band");
    return	FAULT_CODE_OK;
}

int cpe_get_igd_CellId(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = cwmp_conf_pool_get(pool, "lteinfo:cellId");
    return	FAULT_CODE_OK;
}
int cpe_get_igd_PhysicsCellId(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = cwmp_conf_pool_get(pool, "lteinfo:phycellId");
    return	FAULT_CODE_OK;
}
int cpe_get_igd_RSRP(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = cwmp_conf_pool_get(pool, "lteinfo:rsrp");
    return	FAULT_CODE_OK;
}

int cpe_get_igd_RSRQ(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = cwmp_conf_pool_get(pool, "lteinfo:rsrq");
    return	FAULT_CODE_OK;
}

int cpe_get_igd_SINR(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
    FUNCTION_TRACE();
    *value = cwmp_conf_pool_get(pool, "lteinfo:sinr");
    return	FAULT_CODE_OK;
}

int cpe_get_igd_UpstreamTotalByte(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
	char buf[32]={0};
    FUNCTION_TRACE();
	cwmp_conf_popen_get("ifconfig usb0|grep 'RX bytes'|awk '{print $2}'|awk -F ':' '{print $2}'",buf,sizeof(buf));
	*value=PSTRDUP(buf);
   // *value = cwmp_conf_pool_get(pool, "lteinfo:upstream");
    return	FAULT_CODE_OK;
}

int cpe_get_igd_DownstreamTotalByte(cwmp_t * cwmp, const char * name, char ** value, pool_t * pool)
{
   	char buf[32]={0};
 	FUNCTION_TRACE();
	cwmp_conf_popen_get("ifconfig usb0|grep 'RX bytes'|awk '{print $6}'|awk -F ':' '{print $2}'",buf,sizeof(buf));
	*value=PSTRDUP(buf);
    return	FAULT_CODE_OK;
}