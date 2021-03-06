/* tfbsConsMap.h was originally generated by the autoSql program, which also 
 * generated tfbsConsMap.c and tfbsConsMap.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef TFBSCONSMAP_H
#define TFBSCONSMAP_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

#define TFBSCONSMAP_NUM_COLS 2

struct tfbsConsMap
/* tfbsConsMap Data */
    {
    struct tfbsConsMap *next;  /* Next in singly linked list. */
    char *id;	/* TRANSFAC id */
    char *ac;	/* gene-regulation.com AC */
    };

void tfbsConsMapStaticLoad(char **row, struct tfbsConsMap *ret);
/* Load a row from tfbsConsMap table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct tfbsConsMap *tfbsConsMapLoad(char **row);
/* Load a tfbsConsMap from row fetched with select * from tfbsConsMap
 * from database.  Dispose of this with tfbsConsMapFree(). */

struct tfbsConsMap *tfbsConsMapLoadAll(char *fileName);
/* Load all tfbsConsMap from whitespace-separated file.
 * Dispose of this with tfbsConsMapFreeList(). */

struct tfbsConsMap *tfbsConsMapLoadAllByChar(char *fileName, char chopper);
/* Load all tfbsConsMap from chopper separated file.
 * Dispose of this with tfbsConsMapFreeList(). */

#define tfbsConsMapLoadAllByTab(a) tfbsConsMapLoadAllByChar(a, '\t');
/* Load all tfbsConsMap from tab separated file.
 * Dispose of this with tfbsConsMapFreeList(). */

struct tfbsConsMap *tfbsConsMapLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all tfbsConsMap from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with tfbsConsMapFreeList(). */

void tfbsConsMapSaveToDb(struct sqlConnection *conn, struct tfbsConsMap *el, char *tableName, int updateSize);
/* Save tfbsConsMap as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */

struct tfbsConsMap *tfbsConsMapCommaIn(char **pS, struct tfbsConsMap *ret);
/* Create a tfbsConsMap out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new tfbsConsMap */

void tfbsConsMapFree(struct tfbsConsMap **pEl);
/* Free a single dynamically allocated tfbsConsMap such as created
 * with tfbsConsMapLoad(). */

void tfbsConsMapFreeList(struct tfbsConsMap **pList);
/* Free a list of dynamically allocated tfbsConsMap's */

void tfbsConsMapOutput(struct tfbsConsMap *el, FILE *f, char sep, char lastSep);
/* Print out tfbsConsMap.  Separate fields with sep. Follow last field with lastSep. */

#define tfbsConsMapTabOut(el,f) tfbsConsMapOutput(el,f,'\t','\n');
/* Print out tfbsConsMap as a line in a tab-separated file. */

#define tfbsConsMapCommaOut(el,f) tfbsConsMapOutput(el,f,',',',');
/* Print out tfbsConsMap as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* TFBSCONSMAP_H */

