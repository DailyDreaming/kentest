/* dnaProbe.h was originally generated by the autoSql program, which also 
 * generated dnaProbe.c and dnaProbe.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef DNAPROBE_H
#define DNAPROBE_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

struct dnaProbe
/* data about a dna probe used for microarrays */
    {
    struct dnaProbe *next;  /* Next in singly linked list. */
    char *name;	/* name of the dna probe */
    char *dna;	/* sequence of probe, {a,t,g,c} */
    int size;	/* size of sequence */
    char *chrom;	/* chromosome that sequence is from */
    int start;	/* start position in chromosome */
    int end;	/* end position in chromosome */
    char strand[4];	/* strand that probe is on */
    int tpDist;	/* distance of from three prime end */
    float tm;	/* extimated binding tm */
    float pGC;	/* percentage of bases that are g's and c's */
    int affyHeur;	/* 1 if oligo passes affyMetrix heuristic, 0 otherwise */
    float secStruct;	/* gibbs free energy of secondary structure, higher is better */
    int blatScore;	/* blat score of the second greatest region of homology */
    float comparison;	/* weighted average of other scores used for comparison */
    };

void dnaProbeStaticLoad(char **row, struct dnaProbe *ret);
/* Load a row from dnaProbe table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct dnaProbe *dnaProbeLoad(char **row);
/* Load a dnaProbe from row fetched with select * from dnaProbe
 * from database.  Dispose of this with dnaProbeFree(). */

struct dnaProbe *dnaProbeLoadAll(char *fileName);
/* Load all dnaProbe from a tab-separated file.
 * Dispose of this with dnaProbeFreeList(). */

struct dnaProbe *dnaProbeLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all dnaProbe from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with dnaProbeFreeList(). */

void dnaProbeSaveToDb(struct sqlConnection *conn, struct dnaProbe *el, char *tableName, int updateSize);
/* Save dnaProbe as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */

struct dnaProbe *dnaProbeCommaIn(char **pS, struct dnaProbe *ret);
/* Create a dnaProbe out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new dnaProbe */

void dnaProbeFree(struct dnaProbe **pEl);
/* Free a single dynamically allocated dnaProbe such as created
 * with dnaProbeLoad(). */

void dnaProbeFreeList(struct dnaProbe **pList);
/* Free a list of dynamically allocated dnaProbe's */

void dnaProbeOutput(struct dnaProbe *el, FILE *f, char sep, char lastSep);
/* Print out dnaProbe.  Separate fields with sep. Follow last field with lastSep. */

#define dnaProbeTabOut(el,f) dnaProbeOutput(el,f,'\t','\n');
/* Print out dnaProbe as a line in a tab-separated file. */

#define dnaProbeCommaOut(el,f) dnaProbeOutput(el,f,',',',');
/* Print out dnaProbe as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* DNAPROBE_H */

