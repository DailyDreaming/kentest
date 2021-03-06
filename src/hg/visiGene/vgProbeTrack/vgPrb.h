/* vgPrb.h was originally generated by the autoSql program, which also 
 * generated vgPrb.c and vgPrb.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2013 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef VGPRB_H
#define VGPRB_H

#ifndef JKSQL_H
#include "jksql.h"
#endif

#define VGPRB_NUM_COLS 10

struct vgPrb
/* Permanent Probes defining vgPrb_ id */
    {
    struct vgPrb *next;  /* Next in singly linked list. */
    int id;	/* ID of probeExt */
    char *type;	/* Type of probe  - probe,primersMrna,primersGenome,fPrimer,bac,acc,gene */
    char *seq;	/* Probe sequence, if any */
    char *tName;	/* mRNA Accession or a chromosome, if any */
    int tStart;	/* Start of target, if any  */
    int tEnd;	/* End of target, if any */
    char tStrand[2];	/* + or if reverse-complemented then - */
    char *db;	/* assembly/source used to define this sequence originally */
    int taxon;	/* taxon+seq for unique identity */
    char *state;	/* use for multiple passes? e.g. new,isPcr,seq,etc */
    };

void vgPrbStaticLoad(char **row, struct vgPrb *ret);
/* Load a row from vgPrb table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct vgPrb *vgPrbLoad(char **row);
/* Load a vgPrb from row fetched with select * from vgPrb
 * from database.  Dispose of this with vgPrbFree(). */

struct vgPrb *vgPrbLoadAll(char *fileName);
/* Load all vgPrb from whitespace-separated file.
 * Dispose of this with vgPrbFreeList(). */

struct vgPrb *vgPrbLoadAllByChar(char *fileName, char chopper);
/* Load all vgPrb from chopper separated file.
 * Dispose of this with vgPrbFreeList(). */

#define vgPrbLoadAllByTab(a) vgPrbLoadAllByChar(a, '\t');
/* Load all vgPrb from tab separated file.
 * Dispose of this with vgPrbFreeList(). */

struct vgPrb *vgPrbLoadByQuery(struct sqlConnection *conn, char *query);
/* Load all vgPrb from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with vgPrbFreeList(). */

void vgPrbSaveToDb(struct sqlConnection *conn, struct vgPrb *el, char *tableName, int updateSize);
/* Save vgPrb as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */

struct vgPrb *vgPrbCommaIn(char **pS, struct vgPrb *ret);
/* Create a vgPrb out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new vgPrb */

void vgPrbFree(struct vgPrb **pEl);
/* Free a single dynamically allocated vgPrb such as created
 * with vgPrbLoad(). */

void vgPrbFreeList(struct vgPrb **pList);
/* Free a list of dynamically allocated vgPrb's */

void vgPrbOutput(struct vgPrb *el, FILE *f, char sep, char lastSep);
/* Print out vgPrb.  Separate fields with sep. Follow last field with lastSep. */

#define vgPrbTabOut(el,f) vgPrbOutput(el,f,'\t','\n');
/* Print out vgPrb as a line in a tab-separated file. */

#define vgPrbCommaOut(el,f) vgPrbOutput(el,f,',',',');
/* Print out vgPrb as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* VGPRB_H */

