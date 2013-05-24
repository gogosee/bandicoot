#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <oci.h>  
 
int main(int argc,char** argv)  
{  
	int nRet;  
	OCIEnv*      phOCIEnv;    //OCI�������  
	OCIError*    phOCIErr;    //OCI������  
	OCISvcCtx*   phOCIConn;   //OCI���ݿ�������Ӿ��  
 
	char acDBName[20],acUserName[20],acPwd[20];  
 
	//��ʼ��OCIӦ�û���  
	nRet = OCIInitialize((ub4)OCI_DEFAULT,(dvoid*)0,(dvoid* (*)(dvoid*,size_t))0,
			(dvoid* (*)(dvoid*,dvoid*,size_t))0,(void (*)(dvoid*,dvoid*))0);  
	if(nRet)  
	{  
		printf("OCIInitialize() Failed: %d\n",(int)OCI_ERROR);  
		return (int)OCI_ERROR;  
	}  
 
	//��ʼ��OCI�������(��ϵͳ���������OCI�������)  
	nRet = OCIEnvInit(&phOCIEnv,(ub4)OCI_DEFAULT,(size_t)0,(dvoid**)0);  
	if(nRet)  
	{  
		printf("OCIEnvInit() Failed: %d\n",(int)OCI_ERROR);  
		return (int)OCI_ERROR;  
	}  
 
	//��OCIӦ�û���������OCI�������������OCI�Ĵ��󱨸���  
	nRet = OCIHandleAlloc((dvoid*)phOCIEnv,(dvoid**)&phOCIErr,
		    (ub4)OCI_HTYPE_ERROR,(size_t)0,(dvoid**)0);  
	if(nRet)  
	{  
		printf("OCIHandleAlloc() Failed: %d\n",(int)OCI_ERROR);  
		return (int)OCI_ERROR;  
	}  
 
	//������Oracle������  
	memset(acDBName,0,sizeof(acDBName));  
	memset(acUserName,0,sizeof(acUserName));  
	memset(acPwd,0,sizeof(acPwd));  
 
	strcpy(acDBName,"simplegw");  
	strcpy(acUserName,"simplegw");  
	strcpy(acPwd,"simplegw");  
 
	//�������ݿ�  
	nRet = OCILogon(phOCIEnv,phOCIErr,&phOCIConn,(text*)acUserName,
		    strlen(acUserName),(text*)acPwd,strlen(acPwd),
	    (OraText*)acDBName,strlen(acDBName));  
	if(nRet)  
	{  
		printf("Connection Failed: %d\n\n",nRet);  
		exit(1);  
	}  
	printf("Connection OK: %d\n",nRet);  
	printf("ִ��һЩSQL�������ݿ�������� ......\n\n");  







 
	//�Ͽ������ݿ������  
	nRet = OCILogoff(phOCIConn,phOCIErr);  
	if(nRet)  
	{  
		printf("OCILogoff() Failed.\n\n");  
	}
	else 
	{  
		printf("Connecttion closed.\n\n");  
	}  
	//�����Ѿ��Ͽ�,�����Ӿ����Ϊ��  
	phOCIConn = NULL;  
 
	//����OCIӦ�û�������صľ��  
	if(phOCIErr)  
	{  
		OCIHandleFree((dvoid*)phOCIErr,OCI_HTYPE_ERROR);  
		printf("OCI���󱨸����Ѿ��ͷ�.\n\n");  
	}  
 
	if(phOCIEnv)  
	{  
		OCIHandleFree((dvoid*)phOCIEnv,(ub4)OCI_HTYPE_ENV);  
		printf("OCI��������Ѿ��ͷ�.\n\n");  
	}  
	printf("OCI�����ͷŽ���.\n\n");  
	return 0;  
} 



