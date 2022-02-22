/* wgEncodeGencodePubMed.h was originally generated by the autoSql program, which also 
 * generated wgEncodeGencodePubMed.c and wgEncodeGencodePubMed.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef WGENCODEGENCODEPUBMED_H
#define WGENCODEGENCODEPUBMED_H

#define WGENCODEGENCODEPUBMED_NUM_COLS 2

struct wgEncodeGencodePubMed
/* Gencode metadata table of PubMed identifier of published experimental data associated with Gencode Genes */
    {
    struct wgEncodeGencodePubMed *next;  /* Next in singly linked list. */
    char *transcriptId;	/* GENCODE transcript identifier */
    int pubMedId;	/* PubMed identifier of supporting literature */
    };

void wgEncodeGencodePubMedStaticLoad(char **row, struct wgEncodeGencodePubMed *ret);
/* Load a row from wgEncodeGencodePubMed table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct wgEncodeGencodePubMed *wgEncodeGencodePubMedLoad(char **row);
/* Load a wgEncodeGencodePubMed from row fetched with select * from wgEncodeGencodePubMed
 * from database.  Dispose of this with wgEncodeGencodePubMedFree(). */

struct wgEncodeGencodePubMed *wgEncodeGencodePubMedLoadAll(char *fileName);
/* Load all wgEncodeGencodePubMed from whitespace-separated file.
 * Dispose of this with wgEncodeGencodePubMedFreeList(). */

struct wgEncodeGencodePubMed *wgEncodeGencodePubMedLoadAllByChar(char *fileName, char chopper);
/* Load all wgEncodeGencodePubMed from chopper separated file.
 * Dispose of this with wgEncodeGencodePubMedFreeList(). */

#define wgEncodeGencodePubMedLoadAllByTab(a) wgEncodeGencodePubMedLoadAllByChar(a, '\t');
/* Load all wgEncodeGencodePubMed from tab separated file.
 * Dispose of this with wgEncodeGencodePubMedFreeList(). */

struct wgEncodeGencodePubMed *wgEncodeGencodePubMedCommaIn(char **pS, struct wgEncodeGencodePubMed *ret);
/* Create a wgEncodeGencodePubMed out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new wgEncodeGencodePubMed */

void wgEncodeGencodePubMedFree(struct wgEncodeGencodePubMed **pEl);
/* Free a single dynamically allocated wgEncodeGencodePubMed such as created
 * with wgEncodeGencodePubMedLoad(). */

void wgEncodeGencodePubMedFreeList(struct wgEncodeGencodePubMed **pList);
/* Free a list of dynamically allocated wgEncodeGencodePubMed's */

void wgEncodeGencodePubMedOutput(struct wgEncodeGencodePubMed *el, FILE *f, char sep, char lastSep);
/* Print out wgEncodeGencodePubMed.  Separate fields with sep. Follow last field with lastSep. */

#define wgEncodeGencodePubMedTabOut(el,f) wgEncodeGencodePubMedOutput(el,f,'\t','\n');
/* Print out wgEncodeGencodePubMed as a line in a tab-separated file. */

#define wgEncodeGencodePubMedCommaOut(el,f) wgEncodeGencodePubMedOutput(el,f,',',',');
/* Print out wgEncodeGencodePubMed as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* WGENCODEGENCODEPUBMED_H */

