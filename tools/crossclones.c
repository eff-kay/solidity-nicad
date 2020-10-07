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
static TLstring	pc1file;
static TLstring	pc2file;
static TLreal8	threshold;
static TLint4	minclonelines;
static TLint4	maxclonelines;
static TLboolean	showsource;

static void useerr () {
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Usage :  crossclones.x pc1file.xml pc2file.xml [ threshold ] [ minclonesize ] [ maxclonesize ] [ showsource ] > clone-pairs-file.xml", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "  e.g.:  crossclones.x linux_functions.xml freebsd_functions.xml 0.2 > linux_freebsd_functions-crossclones.xml", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "    threshold = difference threshold, 0.0 .. 0.9 (optional, default 0.0 (exact))", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "    minclonesize = minimum clone size (optional, default 5 lines)", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "    maxclonesize = maximum clone size (optional, default 2500 lines, max 20000 lines)", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "    showsource = embed pc source in results (optional, argument present = yes, default no)", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
}

static void getprogramarguments ();
typedef	TLchar	linetable___x254[600000001];
static linetable___x254	linetable_lineText;
static TLint4	linetable_lineTextSize;
typedef	TLint4	linetable___x257[12000000];
static linetable___x257	linetable_lineTable;
static TLint4	linetable_lineTableSize;
typedef	TLnat4	linetable_LN;

static TLnat4 linetable_hash (s)
TLstring	s;
{
    typedef	TLnat1	__x261[256];
    typedef	__x261	nat256;
    register TLnat4	h;
    register TLnat4	j;
    h = TL_TLS_TLSLEN(s);
    if (h > 255) {
	h = 255;
    };
    j = h - 1;
    if (h > 0) {
	{
	    register TLint4	i;
	    TLint4	__x263;
	    __x263 = h >> 1;
	    i = 0;
	    if (i <= __x263) {
		for(;;) {
		    h += ((TLint4) h << 1) + ((* (nat256 *) s)[i]);
		    h += ((TLint4) h << 1) + ((* (nat256 *) s)[j]);
		    j -= 1;
		    if (i == __x263) break;
		    i++;
		}
	    };
	};
    };
    return (h);
    /* NOTREACHED */
}
static TLint4	linetable_secondaryHash;
typedef	TLint4	linetable___x268[10];
static linetable___x268	linetable_primes = 
    {1021, 2027, 4091, 8191, 16381, 32003, 65003, 131009, 262007, 524047};
typedef	TLboolean	linetable___x272[256];
static linetable___x272	linetable_spaceP;

static void linetable_strip (rawline, __x83)
TLstring	rawline;
TLstring	__x83;
{
    TLstring	line;
    TLint4	rawlinelength;
    TLint4	first;
    TLint4	last;
    TLSTRASS(4095, line, rawline);
    rawlinelength = TL_TLS_TLSLEN(rawline);
    first = 1;
    for(;;) {
	{
	    TLchar	__x276[2];
	    if ((first > rawlinelength) || ((TL_TLS_TLSBX(__x276, (TLint4) first, line), !(linetable_spaceP[((TLnat4) TLCVTTOCHR(__x276))])))) {
		break;
	    };
	};
	first += 1;
    };
    last = rawlinelength;
    for(;;) {
	{
	    TLchar	__x277[2];
	    if ((last < first) || ((TL_TLS_TLSBX(__x277, (TLint4) last, line), !(linetable_spaceP[((TLnat4) TLCVTTOCHR(__x277))])))) {
		break;
	    };
	};
	last -= 1;
    };
    {
	TLstring	__x278;
	TL_TLS_TLSBXX(__x278, (TLint4) last, (TLint4) first, line);
	TLSTRASS(4095, line, __x278);
    };
    {
	TLSTRASS(4095, __x83, line);
	return;
    };
    /* NOTREACHED */
}

static linetable_LN linetable_install (line)
TLstring	line;
{
    TLnat4	lineIndex;
    TLnat4	startIndex;
    TLint4	linelength;
    lineIndex = linetable_hash(line);
    if (lineIndex >= 12000000) {
	lineIndex = lineIndex % 12000000;
    };
    startIndex = lineIndex;
    linelength = TL_TLS_TLSLEN(line);
    for(;;) {
	if ((linetable_lineTable[lineIndex]) == 0) {
	    if (((linetable_lineTextSize + linelength) + 1) > 600000000) {
		TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, "*** Error: too much total unique line text ( > ", (TLint2) 0);
		TL_TLI_TLIPI ((TLint4) 0, (TLint4) 600000000, (TLint2) 0);
		TL_TLI_TLIPS ((TLint4) 0, " chars)", (TLint2) 0);
		TL_TLI_TLIPK ((TLint2) 0);
		TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
	    };
	    TLSTRASS(4095, (* (TLstring *) &linetable_lineText[linetable_lineTextSize - 1]), line);
	    linetable_lineTable[lineIndex] = linetable_lineTextSize;
	    linetable_lineTextSize += linelength + 1;
	    linetable_lineTableSize += 1;
	    break;
	};
	if (strcmp((* (TLstring *) &linetable_lineText[(linetable_lineTable[lineIndex]) - 1]), line) == 0) {
	    break;
	};
	lineIndex += linetable_secondaryHash;
	if (lineIndex >= 12000000) {
	    lineIndex = lineIndex % 12000000;
	};
	if (lineIndex == startIndex) {
	    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	    TL_TLI_TLIPS ((TLint4) 0, "*** Error: too many unique lines ( > ", (TLint2) 0);
	    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 12000000, (TLint2) 0);
	    TL_TLI_TLIPS ((TLint4) 0, ")", (TLint2) 0);
	    TL_TLI_TLIPK ((TLint2) 0);
	    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
	};
    };
    return (lineIndex);
    /* NOTREACHED */
}

static void linetable_gettext (lineIndex, __x94)
linetable_LN	lineIndex;
TLstring	__x94;
{
    {
	TLSTRASS(4095, __x94, (* (TLstring *) &linetable_lineText[(linetable_lineTable[lineIndex]) - 1]));
	return;
    };
    /* NOTREACHED */
}

static void linetable_printstats () {
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Used ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) linetable_lineTextSize, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, "/", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 600000000, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " unique line text chars", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, " and ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) linetable_lineTableSize, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, "/", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 12000000, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " unique lines", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
}

static void linetable () {
    linetable_lineTextSize = 1;
    linetable_lineTableSize = 0;
    {
	register TLint4	i;
	for (i = 0; i <= 11999999; i++) {
	    linetable_lineTable[i] = 0;
	};
    };
    TLSTRASS(4095, (* (TLstring *) &linetable_lineText[0]), " ");
    linetable_lineTextSize += 2;
    linetable_lineTable[0] = ((unsigned long long)&(linetable_lineText[1]));
    linetable_lineTableSize = 1;
    linetable_secondaryHash = 11;
    {
	register TLint4	i;
	for (i = 1; i <= 10; i++) {
	    if ((i == 10) || ((linetable_primes[i - 1]) > 12000000)) {
		break;
	    };
	    linetable_secondaryHash = linetable_primes[i - 1];
	};
    };
    {
	register TLint4	c;
	for (c = 0; c <= 255; c++) {
	    linetable_spaceP[c] = 0;
	};
    };
    linetable_spaceP[32] = 1;
    linetable_spaceP[9] = 1;
    linetable_spaceP[12] = 1;
}
struct	PC {
    TLint4	num;
    linetable_LN	info;
    linetable_LN	srcfile;
    TLint4	srcstartline, srcendline;
    TLint4	firstline;
    TLint4	nlines;
    TLint4	nomlines;
    TLint4	sys;
};
typedef	struct PC	__x283[6000000];
static __x283	pcs;
static TLint4	npcs;
static TLint4	firstnewpc;
typedef	linetable_LN	__x284[100000000];
static __x284	lines;
static TLint4	nlines;
struct	CP {
    TLint4	pc1, pc2;
    TLint4	nlines;
    TLint1	similarity;
};
typedef	struct CP	__x285[20000000];
static __x285	clonepairs;
static TLint4	npairs;
static TLint4	ncompares;
static TLint4	nclones;
static TLint4	nfragments;

static void readpcs () {
    TLint4	pcf;
    TL_TLI_TLIOF ((TLnat2) 2, pc1file, &pcf);
    if (pcf == 0) {
	useerr();
    };
    {
	register TLint4	i;
	for (i = 1; i <= 6000000; i++) {
	    TLBIND((*pc), struct PC);
	    TLstring	sourceheader;
	    TLint4	sfindex;
	    TLint4	sfend;
	    TLint4	slindex;
	    TLint4	slend;
	    TLint4	elindex;
	    TLint4	elend;
	    TLint4	nomlines;
	    if ((i % 1000) == 1) {
		TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, ".", (TLint2) 0);
	    };
	    if (TL_TLI_TLIEOF((TLint4) pcf)) {
		break;
	    };
	    npcs += 1;
	    pc = &(pcs[npcs - 1]);
	    (*pc).num = i;
	    (*pc).sys = 1;
	    TL_TLI_TLISS ((TLint4) pcf, (TLint2) 1);
	    TL_TLI_TLIGSS((TLint4) 4095, sourceheader, (TLint2) pcf);
	    (*pc).info = linetable_install(sourceheader);
	    if (TL_TLS_TLSIND(sourceheader, "<source ") != 1) {
		TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, "*** Error: synchronization error on pc file 1", (TLint2) 0);
		TL_TLI_TLIPK ((TLint2) 0);
		TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
	    };
	    sfindex = (TL_TLS_TLSIND(sourceheader, "file=") + TL_TLS_TLSLEN("file=")) + 1;
	    sfend = TL_TLS_TLSIND(sourceheader, " startline=") - 2;
	    {
		TLstring	__x286;
		TL_TLS_TLSBXX(__x286, (TLint4) sfend, (TLint4) sfindex, sourceheader);
		(*pc).srcfile = linetable_install(__x286);
	    };
	    slindex = (TL_TLS_TLSIND(sourceheader, "startline=") + TL_TLS_TLSLEN("startline=")) + 1;
	    slend = TL_TLS_TLSIND(sourceheader, " endline=") - 2;
	    {
		TLstring	__x287;
		TL_TLS_TLSBXX(__x287, (TLint4) slend, (TLint4) slindex, sourceheader);
		(*pc).srcstartline = TL_TLS_TLSVSI(__x287, (TLint4) 10);
	    };
	    elindex = (TL_TLS_TLSIND(sourceheader, "endline=") + TL_TLS_TLSLEN("endline=")) + 1;
	    elend = TL_TLS_TLSLEN(sourceheader) - 2;
	    {
		TLstring	__x288;
		TL_TLS_TLSBXX(__x288, (TLint4) elend, (TLint4) elindex, sourceheader);
		(*pc).srcendline = TL_TLS_TLSVSI(__x288, (TLint4) 10);
	    };
	    (*pc).firstline = nlines;
	    nomlines = 0;
	    for(;;) {
		TLstring	line;
		if (TL_TLI_TLIEOF((TLint4) pcf)) {
		    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		    TL_TLI_TLIPS ((TLint4) 0, "*** Error: synchronization error on pc file", (TLint2) 0);
		    TL_TLI_TLIPK ((TLint2) 0);
		    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
		};
		TL_TLI_TLISS ((TLint4) pcf, (TLint2) 1);
		TL_TLI_TLIGSS((TLint4) 4095, line, (TLint2) pcf);
		if (strcmp(line, "</source>") == 0) {
		    break;
		};
		{
		    TLstring	__x289;
		    linetable_strip(line, __x289);
		    TLSTRASS(4095, line, __x289);
		};
		if (((strcmp(line, "") != 0) && (strcmp(line, "INDENT") != 0)) && (strcmp(line, "DEDENT") != 0)) {
		    nomlines += 1;
		    if (strcmp(line, "}") != 0) {
			nlines += 1;
			if (nlines > 100000000) {
			    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
			    TL_TLI_TLIPS ((TLint4) 0, "*** Error: too many total lines ( > ", (TLint2) 0);
			    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 100000000, (TLint2) 0);
			    TL_TLI_TLIPS ((TLint4) 0, ")", (TLint2) 0);
			    TL_TLI_TLIPK ((TLint2) 0);
			    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
			};
			lines[nlines - 1] = linetable_install(line);
		    };
		};
	    };
	    (*pc).nlines = nlines - ((*pc).firstline);
	    (*pc).nomlines = nomlines;
	    if ((nomlines < minclonelines) || (nomlines > maxclonelines)) {
		(*pc).nlines = 0;
		(*pc).nomlines = 0;
		nlines = (*pc).firstline;
	    };
	};
    };
    if (!TL_TLI_TLIEOF((TLint4) pcf)) {
	TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	TL_TLI_TLIPS ((TLint4) 0, "*** Error: too many potential clones ( > ", (TLint2) 0);
	TL_TLI_TLIPI ((TLint4) 0, (TLint4) 6000000, (TLint2) 0);
	TL_TLI_TLIPS ((TLint4) 0, ")", (TLint2) 0);
	TL_TLI_TLIPK ((TLint2) 0);
    };
    TL_TLI_TLICL ((TLint4) pcf);
}

static void readnewpcs () {
    TLint4	npcf;
    TL_TLI_TLIOF ((TLnat2) 2, pc2file, &npcf);
    if (npcf == 0) {
	useerr();
    };
    {
	register TLint4	i;
	for (i = firstnewpc; i <= 6000000; i++) {
	    TLBIND((*pc), struct PC);
	    TLstring	sourceheader;
	    TLint4	sfindex;
	    TLint4	sfend;
	    TLint4	slindex;
	    TLint4	slend;
	    TLint4	elindex;
	    TLint4	elend;
	    TLint4	nomlines;
	    if ((i % 1000) == 1) {
		TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, ".", (TLint2) 0);
	    };
	    if (TL_TLI_TLIEOF((TLint4) npcf)) {
		break;
	    };
	    npcs += 1;
	    pc = &(pcs[npcs - 1]);
	    (*pc).num = i;
	    (*pc).sys = 2;
	    TL_TLI_TLISS ((TLint4) npcf, (TLint2) 1);
	    TL_TLI_TLIGSS((TLint4) 4095, sourceheader, (TLint2) npcf);
	    (*pc).info = linetable_install(sourceheader);
	    if (TL_TLS_TLSIND(sourceheader, "<source ") != 1) {
		TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, "*** Error: synchronization error on pc file 2", (TLint2) 0);
		TL_TLI_TLIPK ((TLint2) 0);
		TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
	    };
	    sfindex = (TL_TLS_TLSIND(sourceheader, "file=") + TL_TLS_TLSLEN("file=")) + 1;
	    sfend = TL_TLS_TLSIND(sourceheader, " startline=") - 2;
	    {
		TLstring	__x290;
		TL_TLS_TLSBXX(__x290, (TLint4) sfend, (TLint4) sfindex, sourceheader);
		(*pc).srcfile = linetable_install(__x290);
	    };
	    slindex = (TL_TLS_TLSIND(sourceheader, "startline=") + TL_TLS_TLSLEN("startline=")) + 1;
	    slend = TL_TLS_TLSIND(sourceheader, " endline=") - 2;
	    {
		TLstring	__x291;
		TL_TLS_TLSBXX(__x291, (TLint4) slend, (TLint4) slindex, sourceheader);
		(*pc).srcstartline = TL_TLS_TLSVSI(__x291, (TLint4) 10);
	    };
	    elindex = (TL_TLS_TLSIND(sourceheader, "endline=") + TL_TLS_TLSLEN("endline=")) + 1;
	    elend = TL_TLS_TLSLEN(sourceheader) - 2;
	    {
		TLstring	__x292;
		TL_TLS_TLSBXX(__x292, (TLint4) elend, (TLint4) elindex, sourceheader);
		(*pc).srcendline = TL_TLS_TLSVSI(__x292, (TLint4) 10);
	    };
	    (*pc).firstline = nlines;
	    nomlines = 0;
	    for(;;) {
		TLstring	line;
		if (TL_TLI_TLIEOF((TLint4) npcf)) {
		    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		    TL_TLI_TLIPS ((TLint4) 0, "*** Error: synchronization error on pc file", (TLint2) 0);
		    TL_TLI_TLIPK ((TLint2) 0);
		    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
		};
		TL_TLI_TLISS ((TLint4) npcf, (TLint2) 1);
		TL_TLI_TLIGSS((TLint4) 4095, line, (TLint2) npcf);
		if (strcmp(line, "</source>") == 0) {
		    break;
		};
		{
		    TLstring	__x293;
		    linetable_strip(line, __x293);
		    TLSTRASS(4095, line, __x293);
		};
		if (((strcmp(line, "") != 0) && (strcmp(line, "INDENT") != 0)) && (strcmp(line, "DEDENT") != 0)) {
		    nomlines += 1;
		    if (strcmp(line, "}") != 0) {
			nlines += 1;
			if (nlines > 100000000) {
			    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
			    TL_TLI_TLIPS ((TLint4) 0, "*** Error: too many total lines ( > ", (TLint2) 0);
			    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 100000000, (TLint2) 0);
			    TL_TLI_TLIPS ((TLint4) 0, ")", (TLint2) 0);
			    TL_TLI_TLIPK ((TLint2) 0);
			    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
			};
			lines[nlines - 1] = linetable_install(line);
		    };
		};
	    };
	    (*pc).nlines = nlines - ((*pc).firstline);
	    (*pc).nomlines = nomlines;
	    if ((nomlines < minclonelines) || (nomlines > maxclonelines)) {
		(*pc).nlines = 0;
		(*pc).nomlines = 0;
		nlines = (*pc).firstline;
	    };
	};
    };
    if (!TL_TLI_TLIEOF((TLint4) npcf)) {
	TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	TL_TLI_TLIPS ((TLint4) 0, "*** Error: too many potential clones ( > ", (TLint2) 0);
	TL_TLI_TLIPI ((TLint4) 0, (TLint4) 6000000, (TLint2) 0);
	TL_TLI_TLIPS ((TLint4) 0, ")", (TLint2) 0);
	TL_TLI_TLIPK ((TLint2) 0);
    };
    TL_TLI_TLICL ((TLint4) npcf);
}

static void swappcs (i, j)
TLint4	i;
TLint4	j;
{
    struct PC	t;
    TLSTRCTASS(t, pcs[i - 1], struct PC);
    TLSTRCTASS(pcs[i - 1], pcs[j - 1], struct PC);
    TLSTRCTASS(pcs[j - 1], t, struct PC);
}
static TLint4	depth;

static void sortpcs (first, last)
TLint4	first;
TLint4	last;
{
    depth = depth + 1;
    if ((depth % 1000) == 1) {
	TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	TL_TLI_TLIPS ((TLint4) 0, ".", (TLint2) 0);
    };
    if (first < last) {
	TLint4	low;
	TLint4	high;
	TLint4	pivot;
	low = first;
	high = last + 1;
	pivot = low;
	for(;;) {
	    for(;;) {
		high -= 1;
		if (low == high) {
		    break;
		};
		if ((pcs[high - 1].nlines) > (pcs[pivot - 1].nlines)) {
		    break;
		};
	    };
	    if (low == high) {
		break;
	    };
	    for(;;) {
		low += 1;
		if (low == high) {
		    break;
		};
		if ((pcs[pivot - 1].nlines) > (pcs[low - 1].nlines)) {
		    break;
		};
	    };
	    if (low == high) {
		break;
	    };
	    swappcs((TLint4) low, (TLint4) high);
	};
	swappcs((TLint4) high, (TLint4) pivot);
	sortpcs((TLint4) first, (TLint4) (high - 1));
	sortpcs((TLint4) (high + 1), (TLint4) last);
    };
    depth = depth - 1;
}
static TLnat2	*dpmatrix;
static TLint4	__x295;
static TLint4	__x294;

static TLint4 lcs (pc1, pc2, m, n, difflimit)
struct PC	*pc1;
struct PC	*pc2;
TLint4	m;
TLint4	n;
TLint4	difflimit;
{
    {
	register TLint4	i;
	TLint4	__x297;
	__x297 = m;
	i = 0;
	if (i <= __x297) {
	    for(;;) {
		dpmatrix[((0) + __x295 * (i))] = 0;
		if (i == __x297) break;
		i++;
	    }
	};
    };
    {
	register TLint4	j;
	TLint4	__x298;
	__x298 = n;
	j = 0;
	if (j <= __x298) {
	    for(;;) {
		dpmatrix[((j) + __x295 * (0))] = 0;
		if (j == __x298) break;
		j++;
	    }
	};
    };
    {
	register TLint4	i;
	TLint4	__x299;
	__x299 = m;
	i = 1;
	if (i <= __x299) {
	    for(;;) {
		{
		    register TLint4	j;
		    TLint4	__x300;
		    __x300 = n;
		    j = 1;
		    if (j <= __x300) {
			for(;;) {
			    if ((lines[(((*pc1).firstline) + i) - 1]) == (lines[(((*pc2).firstline) + j) - 1])) {
				dpmatrix[((j) + __x295 * (i))] = (dpmatrix[((j - 1) + __x295 * (i - 1))]) + 1;
			    } else {
				if ((dpmatrix[((j) + __x295 * (i - 1))]) >= (dpmatrix[((j - 1) + __x295 * (i))])) {
				    dpmatrix[((j) + __x295 * (i))] = dpmatrix[((j) + __x295 * (i - 1))];
				} else {
				    dpmatrix[((j) + __x295 * (i))] = dpmatrix[((j - 1) + __x295 * (i))];
				};
			    };
			    if (j == __x300) break;
			    j++;
			}
		    };
		};
		if ((i - (dpmatrix[((n) + __x295 * (i))])) > difflimit) {
		    return (0);
		};
		if (i == __x299) break;
		i++;
	    }
	};
    };
    return (dpmatrix[((n) + __x295 * (m))]);
    /* NOTREACHED */
}

static TLboolean exact (pc1, pc2)
struct PC	*pc1;
struct PC	*pc2;
{
    {
	register TLint4	i;
	TLint4	__x301;
	__x301 = (*pc1).nlines;
	i = 1;
	if (i <= __x301) {
	    for(;;) {
		if ((lines[(((*pc1).firstline) + i) - 1]) != (lines[(((*pc2).firstline) + i) - 1])) {
		    return (0);
		};
		if (i == __x301) break;
		i++;
	    }
	};
    };
    return (1);
    /* NOTREACHED */
}

static TLint4 nearmiss (pc1, pc2)
struct PC	*pc1;
struct PC	*pc2;
{
    TLint4	difflimit;
    TLint4	pc1pc2lcs;
    difflimit = TL_TLA_TLA8RD((TLreal8) ((((*pc1).nlines) * threshold) + 0.000001));
    pc1pc2lcs = lcs(&((*pc1)), &((*pc2)), (TLint4) ((*pc1).nlines), (TLint4) ((*pc2).nlines), (TLint4) difflimit);
    if (((((TLreal8) (((*pc1).nlines) - pc1pc2lcs))  / ((TLreal8) ((*pc1).nlines))) <= (threshold + 0.000001)) && ((((TLreal8) (((*pc2).nlines) - pc1pc2lcs))  / ((TLreal8) ((*pc2).nlines))) <= (threshold + 0.000001))) {
	return (TL_TLA_TLA8RD((TLreal8) (((((TLreal8) pc1pc2lcs)  / ((TLreal8) ((*pc1).nlines))) * 100) + 0.000001)));
    } else {
	return (0);
    };
    /* NOTREACHED */
}

static TLint4 clone (pc1, pc2, threshold)
struct PC	*pc1;
struct PC	*pc2;
TLreal8	threshold;
{
    ncompares += 1;
    if ((threshold + 0.000001) < 0.01) {
	if (exact(&((*pc1)), &((*pc2)))) {
	    nclones += 1;
	    nfragments += 1;
	    return (100);
	};
    } else {
	TLint4	sameness;
	sameness = nearmiss(&((*pc1)), &((*pc2)));
	if ((100 - sameness) <= TL_TLA_TLA8RD((TLreal8) ((threshold * 100) + 0.000001))) {
	    nclones += 1;
	    nfragments += 1;
	    return (sameness);
	};
    };
    return (0);
    /* NOTREACHED */
}

static void findclones () {
    {
	register TLint4	i;
	TLint4	__x302;
	__x302 = npcs;
	i = 1;
	if (i <= __x302) {
	    for(;;) {
		if ((i % 1000) == 0) {
		    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		    TL_TLI_TLIPS ((TLint4) 0, ".", (TLint2) 0);
		};
		if ((pcs[i - 1].nlines) != 0) {
		    TLint4	difflimit;
		    difflimit = TL_TLA_TLA8RD((TLreal8) (((pcs[i - 1].nlines) * threshold) + 0.000001));
		    {
			register TLint4	j;
			TLint4	__x303;
			__x303 = npcs;
			j = i + 1;
			if (j <= __x303) {
			    for(;;) {
				if ((pcs[j - 1].nlines) < ((pcs[i - 1].nlines) - difflimit)) {
				    break;
				};
				if ((pcs[j - 1].nlines) != 0) {
				    TLint4	similarity;
				    similarity = clone(&(pcs[i - 1]), &(pcs[j - 1]), (TLreal8) threshold);
				    if ((similarity != 0) && ((pcs[i - 1].sys) != (pcs[j - 1].sys))) {
					TLBIND((*cp), struct CP);
					npairs += 1;
					if (npairs > 20000000) {
					    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
					    TL_TLI_TLIPS ((TLint4) 0, "*** Error: too many clone pairs", (TLint2) 0);
					    TL_TLI_TLIPK ((TLint2) 0);
					    TL_TLE_TLEQUIT ((TLint4) 1, (char *) 0, 0);
					};
					cp = &(clonepairs[npairs - 1]);
					(*cp).pc1 = i;
					(*cp).pc2 = j;
					(*cp).similarity = similarity;
					(*cp).nlines = (((pcs[i - 1].nomlines) + (pcs[j - 1].nomlines)) + 1) / 2;
				    };
				};
				if (j == __x303) break;
				j++;
			    }
			};
		    };
		};
		if (i == __x302) break;
		i++;
	    }
	};
    };
}
typedef	TLint4	__x304[20000000];
static __x304	clonepairmap;

static void swapclonepairmap (i, j)
TLint4	i;
TLint4	j;
{
    TLint4	t;
    t = clonepairmap[i - 1];
    clonepairmap[i - 1] = clonepairmap[j - 1];
    clonepairmap[j - 1] = t;
}
static TLint4	cdepth;

static void sortclonepairmapbyfile (first, last)
TLint4	first;
TLint4	last;
{
    cdepth = cdepth + 1;
    if ((cdepth % 1000) == 1) {
	TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	TL_TLI_TLIPS ((TLint4) 0, ".", (TLint2) 0);
    };
    if (first < last) {
	TLint4	low;
	TLint4	high;
	TLint4	pivot;
	low = first;
	high = last + 1;
	pivot = low;
	for(;;) {
	    for(;;) {
		high -= 1;
		if (low == high) {
		    break;
		};
		if (((pcs[(clonepairs[(clonepairmap[high - 1]) - 1].pc1) - 1].srcfile) > (pcs[(clonepairs[(clonepairmap[pivot - 1]) - 1].pc1) - 1].srcfile)) || (((pcs[(clonepairs[(clonepairmap[high - 1]) - 1].pc1) - 1].srcfile) == (pcs[(clonepairs[(clonepairmap[pivot - 1]) - 1].pc1) - 1].srcfile)) && ((clonepairs[(clonepairmap[high - 1]) - 1].nlines) > (clonepairs[(clonepairmap[pivot - 1]) - 1].nlines)))) {
		    break;
		};
	    };
	    if (low == high) {
		break;
	    };
	    for(;;) {
		low += 1;
		if (low == high) {
		    break;
		};
		if (((pcs[(clonepairs[(clonepairmap[pivot - 1]) - 1].pc1) - 1].srcfile) > (pcs[(clonepairs[(clonepairmap[low - 1]) - 1].pc1) - 1].srcfile)) || (((pcs[(clonepairs[(clonepairmap[pivot - 1]) - 1].pc1) - 1].srcfile) == (pcs[(clonepairs[(clonepairmap[low - 1]) - 1].pc1) - 1].srcfile)) && ((clonepairs[(clonepairmap[pivot - 1]) - 1].nlines) > (clonepairs[(clonepairmap[low - 1]) - 1].nlines)))) {
		    break;
		};
	    };
	    if (low == high) {
		break;
	    };
	    swapclonepairmap((TLint4) low, (TLint4) high);
	};
	swapclonepairmap((TLint4) high, (TLint4) pivot);
	sortclonepairmapbyfile((TLint4) first, (TLint4) (high - 1));
	sortclonepairmapbyfile((TLint4) (high + 1), (TLint4) last);
    };
    cdepth = cdepth - 1;
}

static void pruneembeddedpairs () {
    TLint4	embeddedpairs;
    TLint4	p;
    {
	register TLint4	i;
	TLint4	__x307;
	__x307 = npairs;
	i = 1;
	if (i <= __x307) {
	    for(;;) {
		if (((pcs[(clonepairs[i - 1].pc1) - 1].srcfile) > (pcs[(clonepairs[i - 1].pc2) - 1].srcfile)) || (((pcs[(clonepairs[i - 1].pc1) - 1].srcfile) == (pcs[(clonepairs[i - 1].pc2) - 1].srcfile)) && ((pcs[(clonepairs[i - 1].pc1) - 1].srcstartline) > (pcs[(clonepairs[i - 1].pc2) - 1].srcstartline)))) {
		    TLint4	opc1;
		    opc1 = clonepairs[i - 1].pc1;
		    clonepairs[i - 1].pc1 = clonepairs[i - 1].pc2;
		    clonepairs[i - 1].pc2 = opc1;
		};
		if (i == __x307) break;
		i++;
	    }
	};
    };
    {
	register TLint4	i;
	TLint4	__x308;
	__x308 = npairs;
	i = 1;
	if (i <= __x308) {
	    for(;;) {
		clonepairmap[i - 1] = i;
		if (i == __x308) break;
		i++;
	    }
	};
    };
    sortclonepairmapbyfile((TLint4) 1, (TLint4) npairs);
    embeddedpairs = 0;
    {
	register TLint4	i;
	for (i = npairs; i >= 1; i--) {
	    TLBIND((*pc1), struct PC);
	    TLBIND((*pc2), struct PC);
	    if ((i % 1000) == 1) {
		TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		TL_TLI_TLIPS ((TLint4) 0, ".", (TLint2) 0);
	    };
	    pc1 = &(pcs[(clonepairs[(clonepairmap[i - 1]) - 1].pc1) - 1]);
	    pc2 = &(pcs[(clonepairs[(clonepairmap[i - 1]) - 1].pc2) - 1]);
	    {
		register TLint4	j;
		for (j = i - 1; j >= 1; j--) {
		    TLBIND((*bpc1), struct PC);
		    TLBIND((*bpc2), struct PC);
		    bpc1 = &(pcs[(clonepairs[(clonepairmap[j - 1]) - 1].pc1) - 1]);
		    bpc2 = &(pcs[(clonepairs[(clonepairmap[j - 1]) - 1].pc2) - 1]);
		    if (((*bpc1).srcfile) != ((*pc1).srcfile)) {
			break;
		    };
		    if ((((((*bpc1).srcfile) == ((*pc1).srcfile)) && (((*bpc2).srcfile) == ((*pc2).srcfile))) && ((((*bpc1).srcstartline) <= ((*pc1).srcstartline)) && (((*bpc1).srcendline) >= ((*pc1).srcendline)))) && ((((*bpc2).srcstartline) <= ((*pc2).srcstartline)) && (((*bpc2).srcendline) >= ((*pc2).srcendline)))) {
			embeddedpairs += 1;
			clonepairs[(clonepairmap[i - 1]) - 1].pc1 = 0;
			clonepairs[(clonepairmap[i - 1]) - 1].pc2 = 0;
			break;
		    };
		};
	    };
	};
    };
    npairs -= embeddedpairs;
    p = 1;
    {
	register TLint4	i;
	TLint4	__x309;
	__x309 = npairs;
	i = 1;
	if (i <= __x309) {
	    for(;;) {
		for(;;) {
		    if ((clonepairs[p - 1].pc1) != 0) {
			break;
		    };
		    p += 1;
		};
		TLSTRCTASS(clonepairs[i - 1], clonepairs[p - 1], struct CP);
		p += 1;
		if (i == __x309) break;
		i++;
	    }
	};
    };
}

static void getsysteminfo (pcfile, __x222)
TLstring	pcfile;
TLstring	__x222;
{
    TLint4	slashindex;
    slashindex = TL_TLS_TLSLEN(pcfile);
    for(;;) {
	TLchar	pcfchar;
	{
	    TLchar	__x311[2];
	    TL_TLS_TLSBX(__x311, (TLint4) slashindex, pc1file);
	    pcfchar = (* (TLchar *) __x311);
	};
	if ((slashindex == 0) || (pcfchar == '/')) {
	    break;
	};
	slashindex -= 1;
    };
    {
	{
	    TLstring	__x313;
	    TL_TLS_TLSBXS(__x313, (TLint4) 0, (TLint4) (slashindex + 1), pcfile);
	    TLSTRASS(4095, __x222, __x313);
	};
	return;
    };
    /* NOTREACHED */
}

static void getsystemname (systeminfo, __x227)
TLstring	systeminfo;
TLstring	__x227;
{
    TLint4	usindex;
    usindex = TL_TLS_TLSLEN(systeminfo);
    for(;;) {
	TLchar	sichar;
	{
	    TLchar	__x315[2];
	    TL_TLS_TLSBX(__x315, (TLint4) usindex, systeminfo);
	    sichar = (* (TLchar *) __x315);
	};
	if ((usindex == 2) || (sichar == '_')) {
	    break;
	};
	usindex -= 1;
    };
    {
	{
	    TLstring	__x317;
	    TL_TLS_TLSBXX(__x317, (TLint4) (usindex - 1), (TLint4) 1, systeminfo);
	    TLSTRASS(4095, __x227, __x317);
	};
	return;
    };
    /* NOTREACHED */
}

static void getgranularity (systeminfo, __x232)
TLstring	systeminfo;
TLstring	__x232;
{
    TLint4	usindex;
    usindex = TL_TLS_TLSLEN(systeminfo);
    for(;;) {
	TLchar	sichar;
	{
	    TLchar	__x319[2];
	    TL_TLS_TLSBX(__x319, (TLint4) usindex, systeminfo);
	    sichar = (* (TLchar *) __x319);
	};
	if ((usindex == 2) || (sichar == '_')) {
	    break;
	};
	usindex -= 1;
    };
    {
	{
	    TLstring	__x321;
	    TL_TLS_TLSBXX(__x321, (TLint4) (TL_TLS_TLSIND(systeminfo, ".xml") - 1), (TLint4) (usindex + 1), systeminfo);
	    TLSTRASS(4095, __x232, __x321);
	};
	return;
    };
    /* NOTREACHED */
}

static void showpairs () {
    TLstring	system1info;
    TLstring	system1name;
    TLstring	system2info;
    TLstring	system2name;
    TLstring	granularity;

    extern TLint4 clock ();
    TLint4	cputime;
    {
	TLstring	__x322;
	getsysteminfo(pc1file, __x322);
	TLSTRASS(4095, system1info, __x322);
    };
    {
	TLstring	__x323;
	getsystemname(system1info, __x323);
	TLSTRASS(4095, system1name, __x323);
    };
    {
	TLstring	__x324;
	getsysteminfo(pc2file, __x324);
	TLSTRASS(4095, system2info, __x324);
    };
    {
	TLstring	__x325;
	getsystemname(system2info, __x325);
	TLSTRASS(4095, system2name, __x325);
    };
    {
	TLstring	__x326;
	getgranularity(system1info, __x326);
	TLSTRASS(4095, granularity, __x326);
    };
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "== pc1file", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, pc1file, (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, system1info, (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, system1name, (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, granularity, (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "== pc2file", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, pc2file, (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, system2info, (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, system2name, (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISSO ();
    TL_TLI_TLIPS ((TLint4) 0, "<clones>", (TLint2) -1);
    TL_TLI_TLIPK ((TLint2) -1);
    TL_TLI_TLISSO ();
    TL_TLI_TLIPS ((TLint4) 0, "<systeminfo processor=\"nicad6\" system=\"", (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, system1name, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\" system2=\"", (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, system2name, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\" granularity=\"", (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, granularity, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\" threshold=\"", (TLint2) -1);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) TL_TLA_TLA8RD((TLreal8) ((threshold * 100) + 0.000001)), (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "%\" minlines=\"", (TLint2) -1);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) minclonelines, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\" maxlines=\"", (TLint2) -1);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) maxclonelines, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\"/>", (TLint2) -1);
    TL_TLI_TLIPK ((TLint2) -1);
    TL_TLI_TLISSO ();
    TL_TLI_TLIPS ((TLint4) 0, "<cloneinfo npcs=\"", (TLint2) -1);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) npcs, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\" npairs=\"", (TLint2) -1);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) npairs, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\"/>", (TLint2) -1);
    TL_TLI_TLIPK ((TLint2) -1);
    cputime = clock();
    TL_TLI_TLISSO ();
    TL_TLI_TLIPS ((TLint4) 0, "<runinfo ncompares=\"", (TLint2) -1);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) ncompares, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\" cputime=\"", (TLint2) -1);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) cputime, (TLint2) -1);
    TL_TLI_TLIPS ((TLint4) 0, "\"/>", (TLint2) -1);
    TL_TLI_TLIPK ((TLint2) -1);
    TL_TLI_TLISSO ();
    TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) -1);
    TL_TLI_TLIPK ((TLint2) -1);
    {
	register TLint4	i;
	TLint4	__x327;
	__x327 = npairs;
	i = 1;
	if (i <= __x327) {
	    for(;;) {
		TLBIND((*cp), struct CP);
		TLBIND((*pc1), struct PC);
		TLBIND((*pc2), struct PC);
		if ((i % 1000) == 1) {
		    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
		    TL_TLI_TLIPS ((TLint4) 0, ".", (TLint2) 0);
		};
		cp = &(clonepairs[i - 1]);
		TL_TLI_TLISSO ();
		TL_TLI_TLIPS ((TLint4) 0, "<clone nlines=\"", (TLint2) -1);
		TL_TLI_TLIPI ((TLint4) 0, (TLint4) ((*cp).nlines), (TLint2) -1);
		TL_TLI_TLIPS ((TLint4) 0, "\" similarity=\"", (TLint2) -1);
		TL_TLI_TLIPI ((TLint4) 0, (TLint4) ((*cp).similarity), (TLint2) -1);
		TL_TLI_TLIPS ((TLint4) 0, "\">", (TLint2) -1);
		TL_TLI_TLIPK ((TLint2) -1);
		if ((pcs[((*cp).pc1) - 1].sys) > (pcs[((*cp).pc2) - 1].sys)) {
		    TLint4	temp;
		    temp = (*cp).pc1;
		    (*cp).pc1 = (*cp).pc2;
		    (*cp).pc2 = temp;
		};
		pc1 = &(pcs[((*cp).pc1) - 1]);
		pc2 = &(pcs[((*cp).pc2) - 1]);
		{
		    TLstring	__x329;
		    linetable_gettext((linetable_LN) ((*pc1).info), __x329);
		    {
			TLstring	__x328;
			TL_TLS_TLSBXS(__x328, (TLint4) -1, (TLint4) 1, __x329);
			TL_TLI_TLISSO ();
			TL_TLI_TLIPS ((TLint4) 0, __x328, (TLint2) -1);
			TL_TLI_TLIPS ((TLint4) 0, " pcid=\"", (TLint2) -1);
			TL_TLI_TLIPI ((TLint4) 0, (TLint4) ((*pc1).num), (TLint2) -1);
			TL_TLI_TLIPS ((TLint4) 0, "\">", (TLint2) -1);
		    };
		};
		if (showsource) {
		    TL_TLI_TLISSO ();
		    TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) -1);
		    TL_TLI_TLIPK ((TLint2) -1);
		    {
			register TLint4	k;
			TLint4	__x330;
			__x330 = (*pc1).nlines;
			k = 1;
			if (k <= __x330) {
			    for(;;) {
				{
				    TLstring	__x331;
				    linetable_gettext((linetable_LN) (lines[(((*pc1).firstline) + k) - 1]), __x331);
				    TL_TLI_TLISSO ();
				    TL_TLI_TLIPS ((TLint4) 0, __x331, (TLint2) -1);
				    TL_TLI_TLIPK ((TLint2) -1);
				};
				if (k == __x330) break;
				k++;
			    }
			};
		    };
		};
		TL_TLI_TLISSO ();
		TL_TLI_TLIPS ((TLint4) 0, "</source>", (TLint2) -1);
		TL_TLI_TLIPK ((TLint2) -1);
		{
		    TLstring	__x333;
		    linetable_gettext((linetable_LN) ((*pc2).info), __x333);
		    {
			TLstring	__x332;
			TL_TLS_TLSBXS(__x332, (TLint4) -1, (TLint4) 1, __x333);
			TL_TLI_TLISSO ();
			TL_TLI_TLIPS ((TLint4) 0, __x332, (TLint2) -1);
			TL_TLI_TLIPS ((TLint4) 0, " pcid=\"", (TLint2) -1);
			TL_TLI_TLIPI ((TLint4) 0, (TLint4) ((*pc2).num), (TLint2) -1);
			TL_TLI_TLIPS ((TLint4) 0, "\">", (TLint2) -1);
		    };
		};
		if (showsource) {
		    TL_TLI_TLISSO ();
		    TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) -1);
		    TL_TLI_TLIPK ((TLint2) -1);
		    {
			register TLint4	k;
			TLint4	__x334;
			__x334 = (*pc2).nlines;
			k = 1;
			if (k <= __x334) {
			    for(;;) {
				{
				    TLstring	__x335;
				    linetable_gettext((linetable_LN) (lines[(((*pc2).firstline) + k) - 1]), __x335);
				    TL_TLI_TLISSO ();
				    TL_TLI_TLIPS ((TLint4) 0, __x335, (TLint2) -1);
				    TL_TLI_TLIPK ((TLint2) -1);
				};
				if (k == __x334) break;
				k++;
			    }
			};
		    };
		};
		TL_TLI_TLISSO ();
		TL_TLI_TLIPS ((TLint4) 0, "</source>", (TLint2) -1);
		TL_TLI_TLIPK ((TLint2) -1);
		TL_TLI_TLISSO ();
		TL_TLI_TLIPS ((TLint4) 0, "</clone>", (TLint2) -1);
		TL_TLI_TLIPK ((TLint2) -1);
		TL_TLI_TLISSO ();
		TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) -1);
		TL_TLI_TLIPK ((TLint2) -1);
		if (i == __x327) break;
		i++;
	    }
	};
    };
    TL_TLI_TLISSO ();
    TL_TLI_TLIPS ((TLint4) 0, "</clones>", (TLint2) -1);
    TL_TLI_TLIPK ((TLint2) -1);
}

static void getprogramarguments () {
    if (TL_TLI_TLIARC < 1) {
	useerr();
    };
    {
	TLstring	__x336;
	TL_TLI_TLIFA((TLint4) 1, __x336);
	TLSTRASS(4095, pc1file, __x336);
    };
    {
	TLstring	__x337;
	TL_TLI_TLIFA((TLint4) 2, __x337);
	TLSTRASS(4095, pc2file, __x337);
    };
    if (TL_TLI_TLIARC > 2) {
	{
	    TLstring	__x338;
	    TL_TLI_TLIFA((TLint4) 3, __x338);
	    threshold = TL_TLS_TLSVS8(__x338);
	};
	if ((threshold < 0.0) || (threshold > 1.0)) {
	    useerr();
	};
    };
    if (TL_TLI_TLIARC > 3) {
	{
	    TLstring	__x339;
	    TL_TLI_TLIFA((TLint4) 4, __x339);
	    minclonelines = TL_TLS_TLSVSI(__x339, (TLint4) 10);
	};
	if ((minclonelines < 1) || (minclonelines > 100)) {
	    useerr();
	};
    };
    if (TL_TLI_TLIARC > 4) {
	{
	    TLstring	__x340;
	    TL_TLI_TLIFA((TLint4) 5, __x340);
	    maxclonelines = TL_TLS_TLSVSI(__x340, (TLint4) 10);
	};
	if ((maxclonelines < minclonelines) || (maxclonelines > 20000)) {
	    useerr();
	};
    };
    if (TL_TLI_TLIARC > 5) {
	showsource = 1;
    };
}
static TLint4	oldnpairs;
void TProg () {
    threshold = 0.0;
    minclonelines = 5;
    maxclonelines = 2500;
    showsource = 0;
    getprogramarguments();
    linetable();
    npcs = 0;
    firstnewpc = 0;
    nlines = 0;
    npairs = 0;
    ncompares = 0;
    nclones = 0;
    nfragments = 0;
    depth = 0;
    __x294 = TLDYN(maxclonelines - -1);
    __x295 = TLDYN(maxclonelines - -1);
    TL_TLB_TLBALL((TLint4) __x294 * (__x295 * 2), &dpmatrix);
    cdepth = 0;
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Processing ", (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, pc1file, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " vs ", (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, pc2file, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " with difference threshold ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) TL_TLA_TLA8RD((TLreal8) ((threshold * 100) + 0.000001)), (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, "%, clone size ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) minclonelines, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " .. ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) maxclonelines, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " lines", (TLint2) 0);
    if (showsource) {
	TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	TL_TLI_TLIPS ((TLint4) 0, ", with pc source", (TLint2) 0);
	TL_TLI_TLIPK ((TLint2) 0);
    } else {
	TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
	TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) 0);
	TL_TLI_TLIPK ((TLint2) 0);
    };
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Reading system 1 pcs ", (TLint2) 0);
    readpcs();
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, " done.", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Total ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) npcs, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, "/", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 6000000, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " potential clones of ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) minclonelines, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " lines or more", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Used ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) nlines, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, "/", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 100000000, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " total pc lines", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    linetable_printstats();
    firstnewpc = npcs + 1;
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Reading system 2 pcs ", (TLint2) 0);
    readnewpcs();
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, " done.", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Total ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) npcs, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, "/", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 6000000, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " potential clones of ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) minclonelines, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " lines or more", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Used ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) nlines, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, "/", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) 100000000, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " total pc lines", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    linetable_printstats();
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Sorting pcs ", (TLint2) 0);
    sortpcs((TLint4) 1, (TLint4) npcs);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, " done.", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Finding clones ", (TLint2) 0);
    findclones();
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, " done.", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Total ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) ncompares, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " pc comparisons", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Pruning embedded clone pairs ", (TLint2) 0);
    oldnpairs = npairs;
    pruneembeddedpairs();
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, " done.", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Pruned ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) (oldnpairs - npairs), (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " embedded clone pairs", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Found ", (TLint2) 0);
    TL_TLI_TLIPI ((TLint4) 0, (TLint4) npairs, (TLint2) 0);
    TL_TLI_TLIPS ((TLint4) 0, " clone pairs", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "Generating XML output ", (TLint2) 0);
    showpairs();
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, " done.", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
    TL_TLI_TLISS ((TLint4) 0, (TLint2) 2);
    TL_TLI_TLIPS ((TLint4) 0, "", (TLint2) 0);
    TL_TLI_TLIPK ((TLint2) 0);
}
