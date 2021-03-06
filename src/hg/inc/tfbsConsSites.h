/* tfbsConsSites.h was originally generated by the autoSql program, which also 
 * generated tfbsConsSites.c and tfbsConsSites.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2007 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef TFBSCONSSITES_H
#define TFBSCONSSITES_H

#define TFBSCONSSITES_NUM_COLS 7

struct tfbsConsSites
/* tfbsConsSites Data */
    {
    struct tfbsConsSites *next;  /* Next in singly linked list. */
    char *chrom;	/* Human chromosome */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of item */
    unsigned score;	/* Score from 0-1000 */
    char strand[2];	/* + or - */
    float zScore;	/* zScore */
    };

void tfbsConsSitesStaticLoad(char **row, struct tfbsConsSites *ret);
/* Load a row from tfbsConsSites table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct tfbsConsSites *tfbsConsSitesLoad(char **row);
/* Load a tfbsConsSites from row fetched with select * from tfbsConsSites
 * from database.  Dispose of this with tfbsConsSitesFree(). */

struct tfbsConsSites *tfbsConsSitesLoadAll(char *fileName);
/* Load all tfbsConsSites from whitespace-separated file.
 * Dispose of this with tfbsConsSitesFreeList(). */

struct tfbsConsSites *tfbsConsSitesLoadAllByChar(char *fileName, char chopper);
/* Load all tfbsConsSites from chopper separated file.
 * Dispose of this with tfbsConsSitesFreeList(). */

#define tfbsConsSitesLoadAllByTab(a) tfbsConsSitesLoadAllByChar(a, '\t');
/* Load all tfbsConsSites from tab separated file.
 * Dispose of this with tfbsConsSitesFreeList(). */

struct tfbsConsSites *tfbsConsSitesCommaIn(char **pS, struct tfbsConsSites *ret);
/* Create a tfbsConsSites out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new tfbsConsSites */

void tfbsConsSitesFree(struct tfbsConsSites **pEl);
/* Free a single dynamically allocated tfbsConsSites such as created
 * with tfbsConsSitesLoad(). */

void tfbsConsSitesFreeList(struct tfbsConsSites **pList);
/* Free a list of dynamically allocated tfbsConsSites's */

void tfbsConsSitesOutput(struct tfbsConsSites *el, FILE *f, char sep, char lastSep);
/* Print out tfbsConsSites.  Separate fields with sep. Follow last field with lastSep. */

#define tfbsConsSitesTabOut(el,f) tfbsConsSitesOutput(el,f,'\t','\n');
/* Print out tfbsConsSites as a line in a tab-separated file. */

#define tfbsConsSitesCommaOut(el,f) tfbsConsSitesOutput(el,f,',',',');
/* Print out tfbsConsSites as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

/*	For trackUi cart variable	*/
#define TFBS_SITES_CUTOFF	"tfbsConsSitesCutoff"
#define TFBS_SITES_CUTOFF_DEFAULT	"2.33"
#define TFBS_SITES_CUTOFF_MINIMUM	"1.64"

#endif /* TFBSCONSSITES_H */

