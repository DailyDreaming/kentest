/* jaxOrtholog.h was originally generated by the autoSql program, which also 
 * generated jaxOrtholog.c and jaxOrtholog.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2007 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef JAXORTHOLOG_H
#define JAXORTHOLOG_H

struct jaxOrtholog
/* Jackson Lab Mouse Orthologs */
    {
    struct jaxOrtholog *next;  /* Next in singly linked list. */
    char *humanSymbol;	/* Human HUGO symbol */
    char *humanBand;	/* Human chromosomal location */
    char *mgiId;	/* Mouse database id */
    char *mouseSymbol;	/* Mouse human symbol */
    char *mouseChr;	/* Mouse chromosome */
    char *mouseCm;	/* Mouse genetic map positionin centimorgans */
    char *mouseBand;	/* Mouse chromosome band if any */
    };

void jaxOrthologStaticLoad(char **row, struct jaxOrtholog *ret);
/* Load a row from jaxOrtholog table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct jaxOrtholog *jaxOrthologLoad(char **row);
/* Load a jaxOrtholog from row fetched with select * from jaxOrtholog
 * from database.  Dispose of this with jaxOrthologFree(). */

struct jaxOrtholog *jaxOrthologLoadAll(char *fileName);
/* Load all jaxOrtholog from a tab-separated file.
 * Dispose of this with jaxOrthologFreeList(). */

struct jaxOrtholog *jaxOrthologLoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all jaxOrtholog from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with jaxOrthologFreeList(). */

struct jaxOrtholog *jaxOrthologCommaIn(char **pS, struct jaxOrtholog *ret);
/* Create a jaxOrtholog out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new jaxOrtholog */

void jaxOrthologFree(struct jaxOrtholog **pEl);
/* Free a single dynamically allocated jaxOrtholog such as created
 * with jaxOrthologLoad(). */

void jaxOrthologFreeList(struct jaxOrtholog **pList);
/* Free a list of dynamically allocated jaxOrtholog's */

void jaxOrthologOutput(struct jaxOrtholog *el, FILE *f, char sep, char lastSep);
/* Print out jaxOrtholog.  Separate fields with sep. Follow last field with lastSep. */

#define jaxOrthologTabOut(el,f) jaxOrthologOutput(el,f,'\t','\n');
/* Print out jaxOrtholog as a line in a tab-separated file. */

#define jaxOrthologCommaOut(el,f) jaxOrthologOutput(el,f,',',',');
/* Print out jaxOrtholog as a comma separated list including final comma. */

#endif /* JAXORTHOLOG_H */

