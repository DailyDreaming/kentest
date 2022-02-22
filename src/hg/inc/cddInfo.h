/* cddInfo.h was originally generated by the autoSql program, which also 
 * generated cddInfo.c and cddInfo.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2009 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef CDDINFO_H
#define CDDINFO_H

#define CDDINFO_NUM_COLS 11

struct cddInfo
/* Conserved Domain Description */
    {
    struct cddInfo *next;  /* Next in singly linked list. */
    char *chrom;	/* chromosome */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* hit name */
    unsigned score;	/* Score from 900-1000.  1000 is best */
    char strand[2];	/* Value should be + or - */
    char *fullname;	/* standard name */
    char *NCBInum;	/* NCBI Identifier */
    double evalue;	/* Expect value */
    unsigned percentlength;	/* Data source */
    unsigned percentident;	/* Data source */
    };

void cddInfoStaticLoad(char **row, struct cddInfo *ret);
/* Load a row from cddInfo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct cddInfo *cddInfoLoad(char **row);
/* Load a cddInfo from row fetched with select * from cddInfo
 * from database.  Dispose of this with cddInfoFree(). */

struct cddInfo *cddInfoLoadAll(char *fileName);
/* Load all cddInfo from whitespace-separated file.
 * Dispose of this with cddInfoFreeList(). */

struct cddInfo *cddInfoLoadAllByChar(char *fileName, char chopper);
/* Load all cddInfo from chopper separated file.
 * Dispose of this with cddInfoFreeList(). */

#define cddInfoLoadAllByTab(a) cddInfoLoadAllByChar(a, '\t');
/* Load all cddInfo from tab separated file.
 * Dispose of this with cddInfoFreeList(). */

struct cddInfo *cddInfoCommaIn(char **pS, struct cddInfo *ret);
/* Create a cddInfo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new cddInfo */

void cddInfoFree(struct cddInfo **pEl);
/* Free a single dynamically allocated cddInfo such as created
 * with cddInfoLoad(). */

void cddInfoFreeList(struct cddInfo **pList);
/* Free a list of dynamically allocated cddInfo's */

void cddInfoOutput(struct cddInfo *el, FILE *f, char sep, char lastSep);
/* Print out cddInfo.  Separate fields with sep. Follow last field with lastSep. */

#define cddInfoTabOut(el,f) cddInfoOutput(el,f,'\t','\n');
/* Print out cddInfo as a line in a tab-separated file. */

#define cddInfoCommaOut(el,f) cddInfoOutput(el,f,',',',');
/* Print out cddInfo as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* CDDINFO_H */

