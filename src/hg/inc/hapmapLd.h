/* hapmapLd.h was originally generated by the autoSql program, which also 
 * generated hapmapLd.c and hapmapLd.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef HAPMAPLD_H
#define HAPMAPLD_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

#define HAPMAPLD_NUM_COLS 8

struct hapmapLd
/* Linkage Disequilibrium values from the HapMap project */
    {
    struct hapmapLd *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome */
    unsigned chromStart;	/* chromStart for reference marker */
    unsigned chromEnd;	/* chromEnd for last marker in list */
    char *name;	/* rsId at chromStart */
    unsigned score;	/* Number of markers with LD values */
    char *dprime;	/* Encoded lists of D' values */
    char *rsquared;	/* Encoded lists of r^2 values */
    char *lod;	/* Encoded lists of LOD values */
    };

void hapmapLdStaticLoad(char **row, struct hapmapLd *ret);
/* Load a row from hapmapLd table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct hapmapLd *hapmapLdLoad(char **row);
/* Load a hapmapLd from row fetched with select * from hapmapLd
 * from database.  Dispose of this with hapmapLdFree(). */

struct hapmapLd *hapmapLdLoadAll(char *fileName);
/* Load all hapmapLd from whitespace-separated file.
 * Dispose of this with hapmapLdFreeList(). */

struct hapmapLd *hapmapLdLoadAllByChar(char *fileName, char chopper);
/* Load all hapmapLd from chopper separated file.
 * Dispose of this with hapmapLdFreeList(). */

#define hapmapLdLoadAllByTab(a) hapmapLdLoadAllByChar(a, '\t');
/* Load all hapmapLd from tab separated file.
 * Dispose of this with hapmapLdFreeList(). */

struct hapmapLd *hapmapLdLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all hapmapLd from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with hapmapLdFreeList(). */

void hapmapLdSaveToDb(struct sqlConnection *conn, struct hapmapLd *el, char *tableName, int updateSize);
/* Save hapmapLd as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */

struct hapmapLd *hapmapLdCommaIn(char **pS, struct hapmapLd *ret);
/* Create a hapmapLd out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new hapmapLd */

void hapmapLdFree(struct hapmapLd **pEl);
/* Free a single dynamically allocated hapmapLd such as created
 * with hapmapLdLoad(). */

void hapmapLdFreeList(struct hapmapLd **pList);
/* Free a list of dynamically allocated hapmapLd's */

void hapmapLdOutput(struct hapmapLd *el, FILE *f, char sep, char lastSep);
/* Print out hapmapLd.  Separate fields with sep. Follow last field with lastSep. */

#define hapmapLdTabOut(el,f) hapmapLdOutput(el,f,'\t','\n');
/* Print out hapmapLd as a line in a tab-separated file. */

#define hapmapLdCommaOut(el,f) hapmapLdOutput(el,f,',',',');
/* Print out hapmapLd as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* HAPMAPLD_H */

