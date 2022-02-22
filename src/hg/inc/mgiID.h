/* mgiID.h was originally generated by the autoSql program, which also 
 * generated mgiID.c and mgiID.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2002 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef MGIID_H
#define MGIID_H

struct MGIid
/* MGI to Locus Link table */
    {
    struct MGIid *next;  /* Next in singly linked list. */
    char LLid[9];	/* Locus Link ID */
    char MGIid[13];	/* MGI ID */
    char symbol[33];	/* symbol */
    };

void MGIidStaticLoad(char **row, struct MGIid *ret);
/* Load a row from MGIid table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct MGIid *MGIidLoad(char **row);
/* Load a MGIid from row fetched with select * from MGIid
 * from database.  Dispose of this with MGIidFree(). */

struct MGIid *MGIidLoadAll(char *fileName);
/* Load all MGIid from a tab-separated file.
 * Dispose of this with MGIidFreeList(). */

struct MGIid *MGIidLoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all MGIid from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with MGIidFreeList(). */

struct MGIid *MGIidCommaIn(char **pS, struct MGIid *ret);
/* Create a MGIid out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new MGIid */

void MGIidFree(struct MGIid **pEl);
/* Free a single dynamically allocated MGIid such as created
 * with MGIidLoad(). */

void MGIidFreeList(struct MGIid **pList);
/* Free a list of dynamically allocated MGIid's */

void MGIidOutput(struct MGIid *el, FILE *f, char sep, char lastSep);
/* Print out MGIid.  Separate fields with sep. Follow last field with lastSep. */

#define MGIidTabOut(el,f) MGIidOutput(el,f,'\t','\n');
/* Print out MGIid as a line in a tab-separated file. */

#define MGIidCommaOut(el,f) MGIidOutput(el,f,',',',');
/* Print out MGIid as a comma separated list including final comma. */

#endif /* MGIID_H */

