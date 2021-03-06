/* imageClone.h was originally generated by the autoSql program, which also 
 * generated imageClone.c and imageClone.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2002 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef IMAGECLONE_H
#define IMAGECLONE_H

struct imageClone
/* for use with image consortium's cumulative_plate files at: ftp://image.llnl.gov/image/outgoing */
    {
    struct imageClone *next;  /* Next in singly linked list. */
    unsigned id;	/* IMAGE cloneID */
    char *library;	/* Clone collection (LLAM for amp-resistant libraries, LLCM, for chloramphenicol-resistant libraries, LLKM for kanamycin-resistant libraries.  No rearray locations are given.) */
    unsigned plateNum;	/* Plate number */
    char *row;	/* Row */
    unsigned column;	/* Column */
    unsigned libId;	/* IMAGE library ID */
    char *organism;	/* Species */
    int numGenbank;	/* number of genbank records */
    char **genbankIds;	/* Genbank accession number(s) */
    };

struct imageClone *imageCloneLoad(char **row);
/* Load a imageClone from row fetched with select * from imageClone
 * from database.  Dispose of this with imageCloneFree(). */

struct imageClone *imageCloneLoadAll(char *fileName);
/* Load all imageClone from a tab-separated file.
 * Dispose of this with imageCloneFreeList(). */

struct imageClone *imageCloneCommaIn(char **pS, struct imageClone *ret);
/* Create a imageClone out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new imageClone */

void imageCloneFree(struct imageClone **pEl);
/* Free a single dynamically allocated imageClone such as created
 * with imageCloneLoad(). */

void imageCloneFreeList(struct imageClone **pList);
/* Free a list of dynamically allocated imageClone's */

void imageCloneOutput(struct imageClone *el, FILE *f, char sep, char lastSep);
/* Print out imageClone.  Separate fields with sep. Follow last field with lastSep. */

#define imageCloneTabOut(el,f) imageCloneOutput(el,f,'\t','\n');
/* Print out imageClone as a line in a tab-separated file. */

#define imageCloneCommaOut(el,f) imageCloneOutput(el,f,',',',');
/* Print out imageClone as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* IMAGECLONE_H */

