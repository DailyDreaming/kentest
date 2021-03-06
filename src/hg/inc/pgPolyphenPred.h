/* pgPolyphenPred.h was originally generated by the autoSql program, which also 
 * generated pgPolyphenPred.c and pgPolyphenPred.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2010 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef PGPOLYPHENPRED_H
#define PGPOLYPHENPRED_H

#define PGPOLYPHENPRED_NUM_COLS 7

struct pgPolyphenPred
/* polyphen predictions for pgSnp tracks */
    {
    struct pgPolyphenPred *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome */
    unsigned *chromStart;	/* Start position in chrom */
    unsigned *chromEnd;	/* End position in chrom */
    char *prediction;	/* polyphens prediction, damaging, benign,... */
    char *basedOn;	/* prediction basis */
    char *geneName;	/* gene name */
    char *aaChange;	/* amino acid change */
    };

void pgPolyphenPredStaticLoadWithNull(char **row, struct pgPolyphenPred *ret);
/* Load a row from pgPolyphenPred table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct pgPolyphenPred *pgPolyphenPredLoadWithNull(char **row);
/* Load a pgPolyphenPred from row fetched with select * from pgPolyphenPred
 * from database.  Dispose of this with pgPolyphenPredFree(). */

struct pgPolyphenPred *pgPolyphenPredLoadAll(char *fileName);
/* Load all pgPolyphenPred from whitespace-separated file.
 * Dispose of this with pgPolyphenPredFreeList(). */

struct pgPolyphenPred *pgPolyphenPredLoadAllByChar(char *fileName, char chopper);
/* Load all pgPolyphenPred from chopper separated file.
 * Dispose of this with pgPolyphenPredFreeList(). */

#define pgPolyphenPredLoadAllByTab(a) pgPolyphenPredLoadAllByChar(a, '\t');
/* Load all pgPolyphenPred from tab separated file.
 * Dispose of this with pgPolyphenPredFreeList(). */

struct pgPolyphenPred *pgPolyphenPredCommaIn(char **pS, struct pgPolyphenPred *ret);
/* Create a pgPolyphenPred out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new pgPolyphenPred */

void pgPolyphenPredFree(struct pgPolyphenPred **pEl);
/* Free a single dynamically allocated pgPolyphenPred such as created
 * with pgPolyphenPredLoad(). */

void pgPolyphenPredFreeList(struct pgPolyphenPred **pList);
/* Free a list of dynamically allocated pgPolyphenPred's */

void pgPolyphenPredOutput(struct pgPolyphenPred *el, FILE *f, char sep, char lastSep);
/* Print out pgPolyphenPred.  Separate fields with sep. Follow last field with lastSep. */

#define pgPolyphenPredTabOut(el,f) pgPolyphenPredOutput(el,f,'\t','\n');
/* Print out pgPolyphenPred as a line in a tab-separated file. */

#define pgPolyphenPredCommaOut(el,f) pgPolyphenPredOutput(el,f,',',',');
/* Print out pgPolyphenPred as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */
#include "pgSnp.h"

void printPgPolyphenPred (char *db, char *tableName, struct pgSnp *item);
/* print the predictions for an hgc item click for a pgSnp track */


#endif /* PGPOLYPHENPRED_H */


