/************************************************************************
 * Id: cfg.c                                                            *
 *                                                                      *
 * TR069 Project:  A TR069 library in C                                 *
 * Copyright (C) 2013-2014  netcwmp.netcwmp group                                *
 *                                                                      *
 *                                                                      *
 * Email: netcwmp ( & ) gmail dot com                                *
 *                                                                      *
 ***********************************************************************/

#include <cwmp/cwmp.h>
#include <cwmp/pool.h>
#include <cwmp/log.h>
#include <cwmp/cfg.h>
#include <ini.h>
 #include <linux/kernel.h>     /* 包含sysinfo结构体信息*/  


typedef struct conf_t conf_t;

struct conf_t {
        char * filename;
        FILE * fd;
};


static conf_t	* cwmp_conf_handle = NULL;

int cwmp_conf_open(const char * filename)
{
    FUNCTION_TRACE();
    cwmp_conf_handle = malloc(sizeof(cwmp_conf_handle));
    if (!cwmp_conf_handle)
    {
        cwmp_log_error("conf malloc faild.\n");
        return CWMP_ERROR;
    }
    cwmp_conf_handle->filename = TRstrdup(filename);
    return CWMP_OK;
}

void cwmp_conf_split(char * name, char **s , char **k)
{
    *s = strchr(name, ':');
    if(*s == NULL)
    {
        k = &name;
        *s = "cwmp";
    }
    else
    {
        *s[0] = 0;
        *k = *s+1;
        *s = name;
    }
}

int cwmp_conf_get(const char * key, char *value)
{
    char * s, *k;
    char name[INI_BUFFERSIZE] = {0};
    //char value[INI_BUFFERSIZE] = {0};
    FUNCTION_TRACE();
    if(key == NULL)
    {
        return -1;
    }
    TRstrncpy(name, key, INI_BUFFERSIZE);
    cwmp_conf_split(name, &s, &k);

    ini_gets(s,k,NULL,value,INI_BUFFERSIZE, cwmp_conf_handle->filename);
    return 0;
}

int cwmp_conf_set(const char * key, const char * value)
{
    char * s, *k;
    char name[INI_BUFFERSIZE] = {0};
    FUNCTION_TRACE();
    if(key == NULL)
    {
        return CWMP_ERROR;
    }
    TRstrncpy(name, key, INI_BUFFERSIZE);
    cwmp_conf_split(name, &s, &k);

    return ini_puts(s, k, value, cwmp_conf_handle->filename);
}

char * cwmp_conf_pool_get(pool_t * pool, const char * key)
{
    char * s, *k;
    char name[INI_BUFFERSIZE] = {0};
    char value[INI_BUFFERSIZE] = {0};
    //FUNCTION_TRACE();
    if(key == NULL)
    {
        return NULL;
    }
    TRstrncpy(name, key, INI_BUFFERSIZE);

    cwmp_conf_split(name, &s, &k);

    ini_gets(s,k,NULL,value,INI_BUFFERSIZE, cwmp_conf_handle->filename);

    return pool_pstrdup(pool, value);
}

int cwmp_conf_get_int(const char * key)
{
    char * s, *k;
    char name[INI_BUFFERSIZE] = {0};

    FUNCTION_TRACE();
    if(key == NULL)
    {
        return 0;
    }
    TRstrncpy(name, key, INI_BUFFERSIZE);
    cwmp_conf_split(name, &s, &k);

    return (int)ini_getl(s,k,0,cwmp_conf_handle->filename);
}

int cwmp_conf_popen_get(char *pacCmd, char *pacInfo, int uiLength)
{
    FILE *pstFp = NULL;
    
    if (NULL == pacCmd || NULL == pacInfo)
    {
        return CWMP_ERROR;
    }

    pstFp = popen(pacCmd, "r");
    if (NULL == pstFp)
    {
        return CWMP_ERROR;
    }

    if (fgets(pacInfo, uiLength, pstFp))
    {
        pacInfo[strlen(pacInfo) - 1] = '\0';
        pclose(pstFp);
    }
    else
    {
        pclose(pstFp);
    }
    
    return CWMP_OK;
}
long cwmp_conf_uptime_get(void)
{
 	long pulUptime = 0;
    struct sysinfo stSysInfo = {0};

    /* 调用系统函数获取开机时间 */
    if(0 != sysinfo(&stSysInfo))
    {
		return CWMP_ERROR;
    }
    pulUptime= stSysInfo.uptime;
	return pulUptime;
}

