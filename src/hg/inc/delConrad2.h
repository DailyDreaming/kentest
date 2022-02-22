/* delConrad2.h was originally generated by the autoSql program, which also 
 * generated delConrad2.c and delConrad2.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2007 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef DELCONRAD2_H
#define DELCONRAD2_H

#define DELCONRAD2_NUM_COLS 12

struct delConrad2
/* Deletions from Conrad */
    {
    struct delConrad2 *next;  /* Next in singly linked list. */
    char *chrom;	/* Reference sequence chromosome or scaffold */
    unsigned chromStart;	/* Start position in chrom */
    unsigned chromEnd;	/* End position in chrom */
    char *name;	/* Name */
    unsigned score;	/* Always 1000 */
    char strand[2];	/* Always positive */
    unsigned thickStart;	/* Max start (can be different from chromStart) */
    unsigned thickEnd;	/* Max end (can be different from chromEnd) */
    unsigned count1;	/* Count1 */
    unsigned count2;	/* Count2 */
    char *offspring;	/* HapMap identifier */
    char *population;	/* HapMap population */
    };

void delConrad2StaticLoad(char **row, struct delConrad2 *ret);
/* Load a row from delConrad2 table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct delConrad2 *delConrad2Load(char **row);
/* Load a delConrad2 from row fetched with select * from delConrad2
 * from database.  Dispose of this with delConrad2Free(). */

struct delConrad2 *delConrad2LoadAll(char *fileName);
/* Load all delConrad2 from whitespace-separated file.
 * Dispose of this with delConrad2FreeList(). */

struct delConrad2 *delConrad2LoadAllByChar(char *fileName, char chopper);
/* Load all delConrad2 from chopper separated file.
 * Dispose of this with delConrad2FreeList(). */

#define delConrad2LoadAllByTab(a) delConrad2LoadAllByChar(a, '\t');
/* Load all delConrad2 from tab separated file.
 * Dispose of this with delConrad2FreeList(). */

struct delConrad2 *delConrad2CommaIn(char **pS, struct delConrad2 *ret);
/* Create a delConrad2 out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new delConrad2 */

void delConrad2Free(struct delConrad2 **pEl);
/* Free a single dynamically allocated delConrad2 such as created
 * with delConrad2Load(). */

void delConrad2FreeList(struct delConrad2 **pList);
/* Free a list of dynamically allocated delConrad2's */

void delConrad2Output(struct delConrad2 *el, FILE *f, char sep, char lastSep);
/* Print out delConrad2.  Separate fields with sep. Follow last field with lastSep. */

#define delConrad2TabOut(el,f) delConrad2Output(el,f,'\t','\n');
/* Print out delConrad2 as a line in a tab-separated file. */

#define delConrad2CommaOut(el,f) delConrad2Output(el,f,',',',');
/* Print out delConrad2 as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* DELCONRAD2_H */

