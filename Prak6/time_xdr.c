#include <rpc/rpc.h>
#include "time.h"


bool_t
xdr_ergebnis(xdrs, objp)
	XDR *xdrs;
	ergebnis *objp;
{
	if (!xdr_vector(xdrs, (char *)objp->result, 128, sizeof(char), xdr_char)) {
		return (FALSE);
	}
	return (TRUE);
}


