#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <oci.h>  
 
int main(int argc,char** argv)  
{  
	int nRet;  
	OCIEnv*      phOCIEnv;    //OCI环境句柄  
	OCIError*    phOCIErr;    //OCI错误句柄  
	OCISvcCtx*   phOCIConn;   //OCI数据库服务连接句柄  
 
	char acDBName[20],acUserName[20],acPwd[20];  
 
	//初始化OCI应用环境  
	nRet = OCIInitialize((ub4)OCI_DEFAULT,(dvoid*)0,(dvoid* (*)(dvoid*,size_t))0,
			(dvoid* (*)(dvoid*,dvoid*,size_t))0,(void (*)(dvoid*,dvoid*))0);  
	if(nRet)  
	{  
		printf("OCIInitialize() Failed: %d\n",(int)OCI_ERROR);  
		return (int)OCI_ERROR;  
	}  
 
	//初始化OCI环境句柄(由系统来负责分配OCI环境句柄)  
	nRet = OCIEnvInit(&phOCIEnv,(ub4)OCI_DEFAULT,(size_t)0,(dvoid**)0);  
	if(nRet)  
	{  
		printf("OCIEnvInit() Failed: %d\n",(int)OCI_ERROR);  
		return (int)OCI_ERROR;  
	}  
 
	//在OCI应用环境中依据OCI环境句柄来分配OCI的错误报告句柄  
	nRet = OCIHandleAlloc((dvoid*)phOCIEnv,(dvoid**)&phOCIErr,
		    (ub4)OCI_HTYPE_ERROR,(size_t)0,(dvoid**)0);  
	if(nRet)  
	{  
		printf("OCIHandleAlloc() Failed: %d\n",(int)OCI_ERROR);  
		return (int)OCI_ERROR;  
	}  
 
	//建立与Oracle的连接  
	memset(acDBName,0,sizeof(acDBName));  
	memset(acUserName,0,sizeof(acUserName));  
	memset(acPwd,0,sizeof(acPwd));  
 
	strcpy(acDBName,"simplegw");  
	strcpy(acUserName,"simplegw");  
	strcpy(acPwd,"simplegw");  
 
	//连接数据库  
	nRet = OCILogon(phOCIEnv,phOCIErr,&phOCIConn,(text*)acUserName,
		    strlen(acUserName),(text*)acPwd,strlen(acPwd),
	    (OraText*)acDBName,strlen(acDBName));  
	if(nRet)  
	{  
		printf("Connection Failed: %d\n\n",nRet);  
		exit(1);  
	}  
	printf("Connection OK: %d\n",nRet);  
	printf("执行一些SQL语句和数据库操作命令 ......\n\n");  







 
	//断开与数据库的连接  
	nRet = OCILogoff(phOCIConn,phOCIErr);  
	if(nRet)  
	{  
		printf("OCILogoff() Failed.\n\n");  
	}
	else 
	{  
		printf("Connecttion closed.\n\n");  
	}  
	//连接已经断开,把连接句柄置为空  
	phOCIConn = NULL;  
 
	//销毁OCI应用环境与相关的句柄  
	if(phOCIErr)  
	{  
		OCIHandleFree((dvoid*)phOCIErr,OCI_HTYPE_ERROR);  
		printf("OCI错误报告句柄已经释放.\n\n");  
	}  
 
	if(phOCIEnv)  
	{  
		OCIHandleFree((dvoid*)phOCIEnv,(ub4)OCI_HTYPE_ENV);  
		printf("OCI环境句柄已经释放.\n\n");  
	}  
	printf("OCI环境释放结束.\n\n");  
	return 0;  
} 



