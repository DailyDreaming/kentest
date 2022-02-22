/* affyOffset.h was originally generated by the autoSql program, which also 
 * generated affyOffset.c and affyOffset.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2002 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef AFFYOFFSET_H
#define AFFYOFFSET_H

struct affyOffset
/* File format giving offset of Affymetrix probe sets into contigs. */
    {
    struct affyOffset *next;  /* Next in singly linked list. */
    char *piece;	/* Name of 'piece' of genome, something like ctg21fin1piece100 */
    unsigned tStart;	/* Start of 'piece' in contig. */
    };

void affyOffsetStaticLoad(char **row, struct affyOffset *ret);
/* Load a row from affyOffset table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct affyOffset *affyOffsetLoad(char **row);
/* Load a affyOffset from row fetched with select * from affyOffset
 * from database.  Dispose of this with affyOffsetFree(). */

struct affyOffset *affyOffsetLoadAll(char *fileName);
/* Load all affyOffset from a tab-separated file.
 * Dispose of this with affyOffsetFreeList(). */

struct affyOffset *affyOffsetCommaIn(char **pS, struct affyOffset *ret);
/* Create a affyOffset out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new affyOffset */

void affyOffsetFree(struct affyOffset **pEl);
/* Free a single dynamically allocated affyOffset such as created
 * with affyOffsetLoad(). */

void affyOffsetFreeList(struct affyOffset **pList);
/* Free a list of dynamically allocated affyOffset's */

void affyOffsetOutput(struct affyOffset *el, FILE *f, char sep, char lastSep);
/* Print out affyOffset.  Separate fields with sep. Follow last field with lastSep. */

#define affyOffsetTabOut(el,f) affyOffsetOutput(el,f,'\t','\n');
/* Print out affyOffset as a line in a tab-separated file. */

#define affyOffsetCommaOut(el,f) affyOffsetOutput(el,f,',',',');
/* Print out affyOffset as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* AFFYOFFSET_H */

