/* transRegCode.h was originally generated by the autoSql program, which also 
 * generated transRegCode.c and transRegCode.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2004 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef TRANSREGCODE_H
#define TRANSREGCODE_H

#define TRANSREGCODE_NUM_COLS 7

struct transRegCode
/* Transcription factor binding sites from CHIP/CHIP experiments and conservation */
    {
    struct transRegCode *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome binding site is on */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of transcription factore */
    unsigned score;	/* Score from 0 to 1000 */
    char *chipEvidence;	/* Evidence strength from CHIP/CHIP assay */
    unsigned consSpecies;	/* Number of species conserved in */
    };

void transRegCodeStaticLoad(char **row, struct transRegCode *ret);
/* Load a row from transRegCode table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct transRegCode *transRegCodeLoad(char **row);
/* Load a transRegCode from row fetched with select * from transRegCode
 * from database.  Dispose of this with transRegCodeFree(). */

struct transRegCode *transRegCodeLoadAll(char *fileName);
/* Load all transRegCode from whitespace-separated file.
 * Dispose of this with transRegCodeFreeList(). */

struct transRegCode *transRegCodeLoadAllByChar(char *fileName, char chopper);
/* Load all transRegCode from chopper separated file.
 * Dispose of this with transRegCodeFreeList(). */

#define transRegCodeLoadAllByTab(a) transRegCodeLoadAllByChar(a, '\t');
/* Load all transRegCode from tab separated file.
 * Dispose of this with transRegCodeFreeList(). */

struct transRegCode *transRegCodeCommaIn(char **pS, struct transRegCode *ret);
/* Create a transRegCode out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new transRegCode */

void transRegCodeFree(struct transRegCode **pEl);
/* Free a single dynamically allocated transRegCode such as created
 * with transRegCodeLoad(). */

void transRegCodeFreeList(struct transRegCode **pList);
/* Free a list of dynamically allocated transRegCode's */

void transRegCodeOutput(struct transRegCode *el, FILE *f, char sep, char lastSep);
/* Print out transRegCode.  Separate fields with sep. Follow last field with lastSep. */

#define transRegCodeTabOut(el,f) transRegCodeOutput(el,f,'\t','\n');
/* Print out transRegCode as a line in a tab-separated file. */

#define transRegCodeCommaOut(el,f) transRegCodeOutput(el,f,',',',');
/* Print out transRegCode as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* TRANSREGCODE_H */

