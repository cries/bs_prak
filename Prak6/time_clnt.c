#include <rpc/rpc.h>
#include <sys/time.h>
#include "time.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

ergebnis *
timefunc_1(argp, clnt)
	void *argp;
	CLIENT *clnt;
{
	static ergebnis res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, TIMEFUNC, xdr_void, argp, xdr_ergebnis, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


ergebnis *
datefunc_1(argp, clnt)
	void *argp;
	CLIENT *clnt;
{
	static ergebnis res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, DATEFUNC, xdr_void, argp, xdr_ergebnis, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


ergebnis *
wdayfunc_1(argp, clnt)
	void *argp;
	CLIENT *clnt;
{
	static ergebnis res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, WDAYFUNC, xdr_void, argp, xdr_ergebnis, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}

