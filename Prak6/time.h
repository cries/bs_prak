#include <rpc/rpc.h>

struct ergebnis {
	char result[128];
};
typedef struct ergebnis ergebnis;
bool_t xdr_ergebnis();


#define TIMEPROG ((u_long)0xAFFE0F00)
#define TIME_VERSION ((u_long)1)
#define TIMEFUNC ((u_long)1)
extern ergebnis *timefunc_1();
#define DATEFUNC ((u_long)2)
extern ergebnis *datefunc_1();
#define WDAYFUNC ((u_long)3)
extern ergebnis *wdayfunc_1();

