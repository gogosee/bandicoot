#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oci.h>

int VerifyConnection(text *database, text *username, text *password);

int CheckError(OCIError *errhp, sword status, text *errbuf, size_t errbufsize, sb4 *errcode);
void cleanup(OCIEnv *envhp, OCIError *errhp, OCISession *authp, OCIServer *srvhp, OCISvcCtx *svchp);

int VerifyConnection(text *database, text *username, text *password)
{
sword status = 0;
text errbuff512;
size_t errbuffsize = sizeof(errbuff);
sb4 errorcode = 0;
sb4 *errcode = &errorcode;
OCIEnv *envhp = (OCIEnv *) 0;
OCIError *errhp = (OCIError *) 0;
OCISession *authp = (OCISession *) 0;
OCIServer *srvhp = (OCIServer *) 0;
OCISvcCtx *svchp = (OCISvcCtx *) 0;

fprintf(stderr, "\n=== VerifyConnection function ===\n");

printf("Initialize...\n");
status = OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0,
(dvoid * (*)(dvoid *, size_t)) 0,
(dvoid * (*)(dvoid *, dvoid *, size_t))0,
(dvoid (*)(dvoid *, dvoid *)) 0 );
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

printf("EnvInit...\n");
status = OCIEnvInit( (OCIEnv **) &envhp, OCI_DEFAULT, (size_t) 0,
(dvoid **) 0 );
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

printf("HandleAlloc Error...\n");
status = OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &errhp, OCI_HTYPE_ERROR,
(size_t) 0, (dvoid **) 0);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

/* server contexts */
printf("HandleAlloc Server...\n");
status = OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &srvhp, OCI_HTYPE_SERVER,
(size_t) 0, (dvoid **) 0);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

printf("HandleAlloc Service Context...\n");
status = OCIHandleAlloc( (dvoid *) envhp, (dvoid **) &svchp, OCI_HTYPE_SVCCTX,
(size_t) 0, (dvoid **) 0);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

printf("ServerAttach...\n");
status = OCIServerAttach( srvhp, errhp, (text *)database, strlen((char *)database), 0);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

/* set attribute server context in the service context */
printf("AttrSet ServiceContext Server...\n");
status = OCIAttrSet( (dvoid *) svchp, OCI_HTYPE_SVCCTX, (dvoid *)srvhp,
(ub4) 0, OCI_ATTR_SERVER, (OCIError *) errhp);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

printf("HandleAlloc Session...\n");
status = OCIHandleAlloc((dvoid *) envhp, (dvoid **)&authp,
(ub4) OCI_HTYPE_SESSION, (size_t) 0, (dvoid **) 0);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

printf("AttrSet Session Username...\n");
status = OCIAttrSet((dvoid *) authp, (ub4) OCI_HTYPE_SESSION,
(dvoid *) username, (ub4) strlen((char *)username),
(ub4) OCI_ATTR_USERNAME, errhp);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}
printf("AttrSet Session Password...\n");
status = OCIAttrSet((dvoid *) authp, (ub4) OCI_HTYPE_SESSION,
(dvoid *) password, (ub4) strlen((char *)password),
(ub4) OCI_ATTR_PASSWORD, errhp);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

printf("SessionBegin...\n");
status = OCISessionBegin ( svchp, errhp, authp, OCI_CRED_RDBMS,
(ub4) OCI_DEFAULT);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

printf("AttrSet ServiceContext Session...\n");
status = OCIAttrSet((dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX,
(dvoid *) authp, (ub4) 0,
(ub4) OCI_ATTR_SESSION, errhp);
if (CheckError(errhp, status, errbuff, errbuffsize, errcode)) {
cleanup(envhp, errhp, authp, srvhp, svchp);
return 0;
}

/* connected successfully
*/

printf("\nConnected Successfully.\n");

cleanup(envhp, errhp, authp, srvhp, svchp);

envhp = (OCIEnv *) 0;
errhp = (OCIError *) 0;
authp = (OCISession *) 0;
srvhp = (OCIServer *) 0;
svchp = (OCISvcCtx *) 0;

return 1; /* return success */
}
int CheckError(OCIError *errhp, sword status, text *errbuf, size_t errbufsize, sb4 *errcode)
{
switch (status)
{
case OCI_SUCCESS:
/*printf("\tOCI_SUCCESS\n");*/
return 0;
case OCI_SUCCESS_WITH_INFO:
/* OCI_SUCCESSS_WITH_INFO status is considered a Warning instead of an Error */
printf("\tError - OCI_SUCCESS_WITH_INFO\n");
if (errhp) 
{
OCIErrorGet((dvoid *)errhp, (ub4) 1, (text *) NULL, &errcode,
errbuf, (ub4) errbufsize, OCI_HTYPE_ERROR);
printf("\t\tError - %.*s\n", errbufsize, errbuf);
printf("\t\tError Code: %d\n", errcode);
}
break;
case OCI_NEED_DATA:
printf("\tError - OCI_NEED_DATA\n");
break;
case OCI_NO_DATA:
printf("\tError - OCI_NODATA\n");
break;
case OCI_ERROR:
printf("\tError - OCI_ERROR.\n");
if (errhp) 
{
OCIErrorGet((dvoid *)errhp, (ub4) 1, (text *) NULL, &errcode,
errbuf, (ub4) errbufsize, OCI_HTYPE_ERROR);
printf("\t\tError - %.*s\n", errbufsize, errbuf);
printf("\t\tError Code: %d\n", errcode);
}
break;
case OCI_INVALID_HANDLE:
printf("\tError - OCI_INVALID_HANDLE\n");
break;
case OCI_STILL_EXECUTING:
printf("\tError - OCI_STILL_EXECUTE\n");
break;
case OCI_CONTINUE:
printf("\tError - OCI_CONTINUE\n");
break;
default:
printf("\tError - default\n");
break;
}

return 1;
}

void cleanup(OCIEnv *envhp, OCIError *errhp, OCISession *authp, OCIServer *srvhp, OCISvcCtx *svchp)
{
sword status = 0;

printf("\nCleanup.\n");

if(svchp && errhp && authp)
status = OCISessionEnd(svchp, errhp, authp, (ub4) 0);
if(srvhp && errhp)
status = OCIServerDetach(srvhp, errhp, (ub4) OCI_DEFAULT);

if (authp)
status = OCIHandleFree((dvoid *) authp, (ub4) OCI_HTYPE_SESSION);

if (srvhp)
status = OCIHandleFree((dvoid *) srvhp, (ub4) OCI_HTYPE_SERVER);

if (svchp)
status = OCIHandleFree((dvoid *) svchp, (ub4) OCI_HTYPE_SVCCTX);

if (errhp)
status = OCIHandleFree((dvoid *) errhp, (ub4) OCI_HTYPE_ERROR);

if (envhp)
status = OCIHandleFree((dvoid *) envhp, (ub4) OCI_HTYPE_ENV);

envhp = (OCIEnv *) 0;
errhp = (OCIError *) 0;
authp = (OCISession *) 0;
srvhp = (OCIServer *) 0;
svchp = (OCISvcCtx *) 0;
}

int main(int argc, char *argv[])
{
int result = 0;

char *database = "TESTDB";
char *username = "SCOTT";
char *oldpassword = "TIGER";
char *newpassword = "FROG";

result = VerifyConnection((text *)database, (text *)username, (text *)oldpassword);
if (result == 1)
printf("*** Connection Good ***\n");
else 
printf("*** Connection Bad ***\n");

return 0;
}


