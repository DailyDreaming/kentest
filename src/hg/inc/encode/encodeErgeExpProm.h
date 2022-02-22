/* encodeErgeExpProm.h was originally generated by the autoSql program, which also 
 * generated encodeErgeExpProm.c and encodeErgeExpProm.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2008 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef ENCODEERGEEXPPROM_H
#define ENCODEERGEEXPPROM_H

#define ENCODEERGEEXPPROM_NUM_COLS 14

struct encodeErgeExpProm
/* ENCODE experimental data from dbERGEII */
    {
    struct encodeErgeExpProm *next;  /* Next in singly linked list. */
    char *chrom;	/* Human chromosome */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of read - up to 255 characters */
    unsigned score;	/* Score from 0-1000.  1000 is best */
    char strand[2];	/* Value should be + or - */
    unsigned thickStart;	/* Start of where display should be thick (start codon) */
    unsigned thickEnd;	/* End of where display should be thick (stop codon) */
    unsigned reserved;	/* Always zero for now */
    unsigned blockCount;	/* Number of separate blocks (regions without gaps) */
    unsigned *blockSizes;	/* Comma separated list of block sizes */
    unsigned *chromStarts;	/* Start position of each block in relative to chromStart */
    char *Id;	/* dbERGEII Id */
    char *color;	/* RGB color values */
    };

struct encodeErgeExpProm *encodeErgeExpPromLoad(char **row);
/* Load a encodeErgeExpProm from row fetched with select * from encodeErgeExpProm
 * from database.  Dispose of this with encodeErgeExpPromFree(). */

struct encodeErgeExpProm *encodeErgeExpPromLoadAll(char *fileName);
/* Load all encodeErgeExpProm from whitespace-separated file.
 * Dispose of this with encodeErgeExpPromFreeList(). */

struct encodeErgeExpProm *encodeErgeExpPromLoadAllByChar(char *fileName, char chopper);
/* Load all encodeErgeExpProm from chopper separated file.
 * Dispose of this with encodeErgeExpPromFreeList(). */

#define encodeErgeExpPromLoadAllByTab(a) encodeErgeExpPromLoadAllByChar(a, '\t');
/* Load all encodeErgeExpProm from tab separated file.
 * Dispose of this with encodeErgeExpPromFreeList(). */

struct encodeErgeExpProm *encodeErgeExpPromCommaIn(char **pS, struct encodeErgeExpProm *ret);
/* Create a encodeErgeExpProm out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new encodeErgeExpProm */

void encodeErgeExpPromFree(struct encodeErgeExpProm **pEl);
/* Free a single dynamically allocated encodeErgeExpProm such as created
 * with encodeErgeExpPromLoad(). */

void encodeErgeExpPromFreeList(struct encodeErgeExpProm **pList);
/* Free a list of dynamically allocated encodeErgeExpProm's */

void encodeErgeExpPromOutput(struct encodeErgeExpProm *el, FILE *f, char sep, char lastSep);
/* Print out encodeErgeExpProm.  Separate fields with sep. Follow last field with lastSep. */

#define encodeErgeExpPromTabOut(el,f) encodeErgeExpPromOutput(el,f,'\t','\n');
/* Print out encodeErgeExpProm as a line in a tab-separated file. */

#define encodeErgeExpPromCommaOut(el,f) encodeErgeExpPromOutput(el,f,',',',');
/* Print out encodeErgeExpProm as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* ENCODEERGEEXPPROM_H */

