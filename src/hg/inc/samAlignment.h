/* samAlignment.h was originally generated by the autoSql program, which also
 * generated samAlignment.c and samAlignment.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef SAMALIGNMENT_H
#define SAMALIGNMENT_H

#include "asParse.h"

#define SAMALIGNMENT_NUM_COLS 12

struct samAlignment
/* The fields of a SAM short read alignment, the text version of BAM. */
    {
    struct samAlignment *next;  /* Next in singly linked list. */
    char *qName;	/* Query template name - name of a read */
    unsigned short flag;	/* Flags.  0x10 set for reverse complement.  See SAM docs for others. */
    char *rName;	/* Reference sequence name (often a chromosome) */
    unsigned pos;	/* 1 based position */
    unsigned char mapQ;	/* Mapping quality 0-255, 255 is best */
    char *cigar;	/* CIGAR encoded alignment string. */
    char *rNext;	/* Ref sequence for next (mate) read. '=' if same as rName, '*' if no mate */
    int pNext;	/* Position (1-based) of next (mate) sequence. May be -1 or 0 if no mate */
    int tLen;	/* Size of DNA template for mated pairs.  -size for one of mate pairs */
    char *seq;	/* Query template sequence */
    char *qual;	/* ASCII of Phred-scaled base QUALity+33.  Just '*' if no quality scores */
    char *tagTypeVals;	/* Tab-delimited list of tag:type:value optional extra fields */
    };

void samAlignmentStaticLoad(char **row, struct samAlignment *ret);
/* Load a row from samAlignment table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct samAlignment *samAlignmentLoad(char **row);
/* Load a samAlignment from row fetched with select * from samAlignment
 * from database.  Dispose of this with samAlignmentFree(). */

struct samAlignment *samAlignmentLoadAll(char *fileName);
/* Load all samAlignment from whitespace-separated file.
 * Dispose of this with samAlignmentFreeList(). */

struct samAlignment *samAlignmentLoadAllByChar(char *fileName, char chopper);
/* Load all samAlignment from chopper separated file.
 * Dispose of this with samAlignmentFreeList(). */

#define samAlignmentLoadAllByTab(a) samAlignmentLoadAllByChar(a, '\t');
/* Load all samAlignment from tab separated file.
 * Dispose of this with samAlignmentFreeList(). */

struct samAlignment *samAlignmentCommaIn(char **pS, struct samAlignment *ret);
/* Create a samAlignment out of a comma separated string.
 * This will fill in ret if non-null, otherwise will
 * return a new samAlignment */

void samAlignmentFree(struct samAlignment **pEl);
/* Free a single dynamically allocated samAlignment such as created
 * with samAlignmentLoad(). */

void samAlignmentFreeList(struct samAlignment **pList);
/* Free a list of dynamically allocated samAlignment's */

void samAlignmentOutput(struct samAlignment *el, FILE *f, char sep, char lastSep);
/* Print out samAlignment.  Separate fields with sep. Follow last field with lastSep. */

#define samAlignmentTabOut(el,f) samAlignmentOutput(el,f,'\t','\n');
/* Print out samAlignment as a line in a tab-separated file. */

#define samAlignmentCommaOut(el,f) samAlignmentOutput(el,f,',',',');
/* Print out samAlignment as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

struct asObject *samAsObj();
// Return asObject describing fields of SAM/BAM
#define bamAsObj() samAsObj()

#endif /* SAMALIGNMENT_H */

