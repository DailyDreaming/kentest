/* peptideMapping.h was originally generated by the autoSql program, which also 
 * generated peptideMapping.c and peptideMapping.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef PEPTIDEMAPPING_H
#define PEPTIDEMAPPING_H

#define PEPTIDEMAPPING_NUM_COLS 10

struct peptideMapping
/* Format for genomic mappings of mass spec proteogenomic hits */
    {
    struct peptideMapping *next;  /* Next in singly linked list. */
    char *chrom;	/* Reference sequence chromosome or scaffold */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Peptide sequence of the hit */
    unsigned score;	/* Log e-value scaled to a score of 0 (worst) to 1000 (best) */
    char strand[2];	/* + or - */
    float rawScore;	/* Raw score for this hit, as estimated through HMM analysis */
    char *spectrumId;	/* Non-unique identifier for the spectrum file */
    unsigned peptideRank;	/* Rank of this hit, for peptides with multiple genomic hits */
    unsigned peptideRepeatCount;	/* Indicates how many times this same hit was observed */
    };

void peptideMappingStaticLoad(char **row, struct peptideMapping *ret);
/* Load a row from peptideMapping table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct peptideMapping *peptideMappingLoad(char **row);
/* Load a peptideMapping from row fetched with select * from peptideMapping
 * from database.  Dispose of this with peptideMappingFree(). */

struct peptideMapping *peptideMappingLoadAll(char *fileName);
/* Load all peptideMapping from whitespace-separated file.
 * Dispose of this with peptideMappingFreeList(). */

struct peptideMapping *peptideMappingLoadAllByChar(char *fileName, char chopper);
/* Load all peptideMapping from chopper separated file.
 * Dispose of this with peptideMappingFreeList(). */

#define peptideMappingLoadAllByTab(a) peptideMappingLoadAllByChar(a, '\t');
/* Load all peptideMapping from tab separated file.
 * Dispose of this with peptideMappingFreeList(). */

struct peptideMapping *peptideMappingCommaIn(char **pS, struct peptideMapping *ret);
/* Create a peptideMapping out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new peptideMapping */

void peptideMappingFree(struct peptideMapping **pEl);
/* Free a single dynamically allocated peptideMapping such as created
 * with peptideMappingLoad(). */

void peptideMappingFreeList(struct peptideMapping **pList);
/* Free a list of dynamically allocated peptideMapping's */

void peptideMappingOutput(struct peptideMapping *el, FILE *f, char sep, char lastSep);
/* Print out peptideMapping.  Separate fields with sep. Follow last field with lastSep. */

#define peptideMappingTabOut(el,f) peptideMappingOutput(el,f,'\t','\n');
/* Print out peptideMapping as a line in a tab-separated file. */

#define peptideMappingCommaOut(el,f) peptideMappingOutput(el,f,',',',');
/* Print out peptideMapping as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* PEPTIDEMAPPING_H */

