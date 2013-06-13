struct ergebnis {
	char result[128];
};

program TIMEPROG {
	version TIME_VERSION {
	ergebnis TIMEFUNC(void) = 1;
	ergebnis DATEFUNC(void) = 2;
	ergebnis WDAYFUNC(void) = 3;
	} = 1; 
} = 0xAFFE0F00;

