/* kgMapName.h was originally generated by the autoSql program, which also 
 * generated kgMapName.c and kgMapName.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2004 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef KGMAPNAME_H
#define KGMAPNAME_H

#define KGMAPNAME_NUM_COLS 2

struct kgMapName
/* Maps kg pep names to common name */
    {
    struct kgMapName *next;  /* Next in singly linked list. */
    char *kgPepId;	/* pep ID */
    char *geneName;	/* gene name */
    };

void kgMapNameStaticLoad(char **row, struct kgMapName *ret);
/* Load a row from kgMapName table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct kgMapName *kgMapNameLoad(char **row);
/* Load a kgMapName from row fetched with select * from kgMapName
 * from database.  Dispose of this with kgMapNameFree(). */

struct kgMapName *kgMapNameLoadAll(char *fileName);
/* Load all kgMapName from whitespace-separated file.
 * Dispose of this with kgMapNameFreeList(). */

struct kgMapName *kgMapNameLoadAllByChar(char *fileName, char chopper);
/* Load all kgMapName from chopper separated file.
 * Dispose of this with kgMapNameFreeList(). */

#define kgMapNameLoadAllByTab(a) kgMapNameLoadAllByChar(a, '\t');
/* Load all kgMapName from tab separated file.
 * Dispose of this with kgMapNameFreeList(). */

struct kgMapName *kgMapNameCommaIn(char **pS, struct kgMapName *ret);
/* Create a kgMapName out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new kgMapName */

void kgMapNameFree(struct kgMapName **pEl);
/* Free a single dynamically allocated kgMapName such as created
 * with kgMapNameLoad(). */

void kgMapNameFreeList(struct kgMapName **pList);
/* Free a list of dynamically allocated kgMapName's */

void kgMapNameOutput(struct kgMapName *el, FILE *f, char sep, char lastSep);
/* Print out kgMapName.  Separate fields with sep. Follow last field with lastSep. */

#define kgMapNameTabOut(el,f) kgMapNameOutput(el,f,'\t','\n');
/* Print out kgMapName as a line in a tab-separated file. */

#define kgMapNameCommaOut(el,f) kgMapNameOutput(el,f,',',',');
/* Print out kgMapName as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* KGMAPNAME_H */

