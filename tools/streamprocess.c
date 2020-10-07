#include <UNIX64/cinterface>
extern TLint4	TL_TLI_TLIARC;

extern void TL_TLI_TLIFA ();

extern void TL_TLX_TLXGE ();

extern void TL_TLX_TLXDT ();

extern void TL_TLX_TLXTM ();

extern void TL_TLX_TLXCL ();

extern void TL_TLX_TLXSC ();

extern void time ();

extern void TL_TLX_TLXSYS ();

extern TLint4 getpid ();

extern void TL_TLI_TLIFS ();

extern void TL_TLK_TLKUEXIT ();
extern TLnat4	TL_TLK_TLKTIME;
extern TLnat4	TL_TLK_TLKEPOCH;

extern void TL_TLK_TLKUDMPA ();

extern void TL_TLK_TLKCINI ();
extern TLboolean	TL_TLK_TLKCLKON;
extern TLnat4	TL_TLK_TLKHZ;
extern TLnat4	TL_TLK_TLKCRESO;
extern TLnat4	TL_TLK_TLKTIME;
extern TLnat4	TL_TLK_TLKEPOCH;

extern void TL_TLK_TLKPSID ();

extern TLnat4 TL_TLK_TLKPGID ();

extern void TL_TLK_TLKRSETP ();
static TLstring	command;
static TLint4	unique;
static TLstring	tempinfile;
static TLstring	tempoutfile;
static TLstring	line;
void TProg () {
    {
	TLstring	__x61;
	{
	    TLstring	__x60;
	    TL_TLI_TLIFA((TLint4) 1, __x60);
	    if ((strcmp(__x60, "") == 0) || ((TL_TLI_TLIFA((TLint4) 2, __x61), strcmp(__x61, "") != 0))) {
		TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, "Usage:  streamprocess.x normalizing_command < system_functions.xml > system_functions-normalized.xml", (TLint2) 0);
		TL_TLI_TLIPK ((TLint2) 0);
		TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
	    };
	};
    };
    {
	TLstring	__x62;
	TL_TLI_TLIFA((TLint4) 1, __x62);
	TLSTRASS(4095, command, __x62);
    };
    unique = getpid();
    {
	TLstring	__x65;
	TL_TLS_TLSVIS((TLint4) unique, (TLint4) 1, (TLint4) 10, __x65);
	{
	    TLstring	__x64;
	    TL_TLS_TLSCAT("/tmp/nicad", __x65, __x64);
	    {
		TLstring	__x63;
		TL_TLS_TLSCAT(__x64, ".in", __x63);
		TLSTRASS(4095, tempinfile, __x63);
	    };
	};
    };
    {
	TLstring	__x68;
	TL_TLS_TLSVIS((TLint4) unique, (TLint4) 1, (TLint4) 10, __x68);
	{
	    TLstring	__x67;
	    TL_TLS_TLSCAT("/tmp/nicad", __x68, __x67);
	    {
		TLstring	__x66;
		TL_TLS_TLSCAT(__x67, ".out", __x66);
		TLSTRASS(4095, tempoutfile, __x66);
	    };
	};
    };
    TL_TLI_TLISSI ();
    TL_TLI_TLIGSS((TLint4) 4095, line, (TLint2) -2);
    for(;;) {
	TLint4	tf;
	TLint4	nlines;

	extern TLint4 system ();
	TLint4	rc;
	TLstring	commandline;
	if (TL_TLI_TLIEOF((TLint4) -2)) {
	    break;
	};
	if (TL_TLS_TLSIND(line, "<source") != 1) {
	    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	    TL_TLI_TLIPS ((TLint4) 0, "*** Error: synchronization error on potential clones file", (TLint2) 0);
	    TL_TLI_TLIPK ((TLint2) 0);
	    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
	};
	TL_TLI_TLIOF ((TLnat2) 4, tempinfile, &tf);
	if (tf == 0) {
	    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	    TL_TLI_TLIPS ((TLint4) 0, "*** Error: can\'t create temp file ", (TLint2) 0);
	    TL_TLI_TLIPK ((TLint2) 0);
	    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
	};
	nlines = 0;
	{
	    register TLint4	i;
	    for (i = 1; i <= 100; i++) {
		TL_TLI_TLISS ((TLint4) tf, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, line, (TLint2) tf);
		TL_TLI_TLIPK ((TLint2) tf);
		for(;;) {
		    for(;;) {
			TL_TLI_TLISSI ();
			TL_TLI_TLIGSS((TLint4) 4095, line, (TLint2) -2);
			nlines += 1;
			if (TL_TLI_TLIEOF((TLint4) -2) || (TL_TLS_TLSLEN(line) < 4095)) {
			    break;
			};
			TL_TLI_TLISS ((TLint4) tf, (TLint2) 2);
			TL_TLI_TLIPS ((TLint4) 0, line, (TLint2) tf);
		    };
		    if (TL_TLI_TLIEOF((TLint4) -2) || (TL_TLS_TLSIND(line, "</source>") == 1)) {
			break;
		    };
		    TL_TLI_TLISS ((TLint4) tf, (TLint2) 2);
		    TL_TLI_TLIPS ((TLint4) 0, line, (TLint2) tf);
		    TL_TLI_TLIPK ((TLint2) tf);
		};
		TL_TLI_TLISS ((TLint4) tf, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, line, (TLint2) tf);
		TL_TLI_TLIPK ((TLint2) tf);
		if (TL_TLS_TLSIND(line, "</source>") != 1) {
		    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		    TL_TLI_TLIPS ((TLint4) 0, "*** Error: synchronization error on potential clones file", (TLint2) 0);
		    TL_TLI_TLIPK ((TLint2) 0);
		    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
		};
		if (TL_TLI_TLIEOF((TLint4) -2)) {
		    break;
		};
		TL_TLI_TLISSI ();
		TL_TLI_TLIGSS((TLint4) 4095, line, (TLint2) -2);
		if (nlines > 10000) {
		    break;
		};
	    };
	};
	TL_TLI_TLICL ((TLint4) tf);
	rc = 0;
	{
	    TLstring	__x70;
	    TL_TLS_TLSCAT(command, " < ", __x70);
	    {
		TLstring	__x69;
		TL_TLS_TLSCAT(__x70, tempinfile, __x69);
		TLSTRASS(4095, commandline, __x69);
	    };
	};
	rc = system(commandline);
	if (rc != 0) {
	    {
		TLstring	__x71;
		TL_TLS_TLSCAT("*** Error: command failed: ", commandline, __x71);
		TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, __x71, (TLint2) 0);
		TL_TLI_TLIPK ((TLint2) 0);
	    };
	    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
	};
    };
}
