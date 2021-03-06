/* kgProtAlias.h was originally generated by the autoSql program, which also 
 * generated kgProtAlias.c and kgProtAlias.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2003 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef KGPROTALIAS_H
#define KGPROTALIAS_H

#define KGPROTALIAS_NUM_COLS 3

struct kgProtAlias
/* Link together a Known Gene ID and a protein alias */
    {
    struct kgProtAlias *next;  /* Next in singly linked list. */
    char *kgID;	/* Known Gene ID */
    char *displayID;	/* protein display ID */
    char *alias;	/* a protein alias */
    };

void kgProtAliasStaticLoad(char **row, struct kgProtAlias *ret);
/* Load a row from kgProtAlias table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct kgProtAlias *kgProtAliasLoad(char **row);
/* Load a kgProtAlias from row fetched with select * from kgProtAlias
 * from database.  Dispose of this with kgProtAliasFree(). */

struct kgProtAlias *kgProtAliasLoadAll(char *fileName);
/* Load all kgProtAlias from whitespace-separated file.
 * Dispose of this with kgProtAliasFreeList(). */

struct kgProtAlias *kgProtAliasLoadAllByChar(char *fileName, char chopper);
/* Load all kgProtAlias from chopper separated file.
 * Dispose of this with kgProtAliasFreeList(). */

#define kgProtAliasLoadAllByTab(a) kgProtAliasLoadAllByChar(a, '\t');
/* Load all kgProtAlias from tab separated file.
 * Dispose of this with kgProtAliasFreeList(). */

struct kgProtAlias *kgProtAliasCommaIn(char **pS, struct kgProtAlias *ret);
/* Create a kgProtAlias out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new kgProtAlias */

void kgProtAliasFree(struct kgProtAlias **pEl);
/* Free a single dynamically allocated kgProtAlias such as created
 * with kgProtAliasLoad(). */

void kgProtAliasFreeList(struct kgProtAlias **pList);
/* Free a list of dynamically allocated kgProtAlias's */

void kgProtAliasOutput(struct kgProtAlias *el, FILE *f, char sep, char lastSep);
/* Print out kgProtAlias.  Separate fields with sep. Follow last field with lastSep. */

#define kgProtAliasTabOut(el,f) kgProtAliasOutput(el,f,'\t','\n');
/* Print out kgProtAlias as a line in a tab-separated file. */

#define kgProtAliasCommaOut(el,f) kgProtAliasOutput(el,f,',',',');
/* Print out kgProtAlias as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* KGPROTALIAS_H */

