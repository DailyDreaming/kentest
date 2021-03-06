/* Copyright (C) 2011 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */


/* docIdSub.h was originally generated by the autoSql program, which also 
 * generated docIdSub.c and docIdSub.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef DOCIDSUB_H
#define DOCIDSUB_H

#define DOCIDSUB_NUM_COLS 10

struct docIdSub
/* keeps track of files submitted to ENCODE docId system */
    {
    struct docIdSub *next;  /* Next in singly linked list. */
    int ix;	/* auto-increment ID */
    int status;	/* current status: for background process */
    char *assembly;	/* assembly */
    char *submitDate;	/* submission data */
    char *md5sum;	/* md5sum of file */
    char *valReport;	/* validation report */
    char *valVersion;	/* validator version */
    char *metaData;	/* metaData RA */
    char *submitPath;	/* file path in DDF line */
    char *submitter;	/* submitter id */
    };

void docIdSubStaticLoad(char **row, struct docIdSub *ret);
/* Load a row from docIdSub table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct docIdSub *docIdSubLoad(char **row);
/* Load a docIdSub from row fetched with select * from docIdSub
 * from database.  Dispose of this with docIdSubFree(). */

struct docIdSub *docIdSubLoadAll(char *fileName);
/* Load all docIdSub from whitespace-separated file.
 * Dispose of this with docIdSubFreeList(). */

struct docIdSub *docIdSubLoadAllByChar(char *fileName, char chopper);
/* Load all docIdSub from chopper separated file.
 * Dispose of this with docIdSubFreeList(). */

#define docIdSubLoadAllByTab(a) docIdSubLoadAllByChar(a, '\t');
/* Load all docIdSub from tab separated file.
 * Dispose of this with docIdSubFreeList(). */

struct docIdSub *docIdSubCommaIn(char **pS, struct docIdSub *ret);
/* Create a docIdSub out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new docIdSub */

void docIdSubFree(struct docIdSub **pEl);
/* Free a single dynamically allocated docIdSub such as created
 * with docIdSubLoad(). */

void docIdSubFreeList(struct docIdSub **pList);
/* Free a list of dynamically allocated docIdSub's */

void docIdSubOutput(struct docIdSub *el, FILE *f, char sep, char lastSep);
/* Print out docIdSub.  Separate fields with sep. Follow last field with lastSep. */

#define docIdSubTabOut(el,f) docIdSubOutput(el,f,'\t','\n');
/* Print out docIdSub as a line in a tab-separated file. */

#define docIdSubCommaOut(el,f) docIdSubOutput(el,f,',',',');
/* Print out docIdSub as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#define  DEFAULT_DOCID_TABLE "docIdSub"

char *docIdDecorate(char *composite, char *cell, int num);

char *docIdSubmit(struct sqlConnection *conn, char *docIdTable, 
    struct docIdSub *docIdSub, char *docIdDir, char *type);

char *docIdGetPath(char *docId, char *docIdDir, char *suffix, char *submitPath);

boolean fileIsCompressed(char *fileName);

char *docDecorateType(char *type);
#endif /* DOCIDSUB_H */

