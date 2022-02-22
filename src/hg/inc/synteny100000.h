/* synteny100000.h was originally generated by the autoSql program, which also 
 * generated synteny100000.c and synteny100000.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2002 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef SYNTENY100000_H
#define SYNTENY100000_H

struct synteny100000
/* Mouse Synteny from blastz single coverage */
    {
    struct synteny100000 *next;  /* Next in singly linked list. */
    char *chrom;	/* Human Chrom */
    unsigned chromStart;	/* Start on Human */
    unsigned chromEnd;	/* End on Human */
    char *mouseChrom;	/* Mouse Chromosome */
    unsigned score;	/* score always zero */
    char strand[2];	/* + direction matches - opposite */
    };

void synteny100000StaticLoad(char **row, struct synteny100000 *ret);
/* Load a row from synteny100000 table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct synteny100000 *synteny100000Load(char **row);
/* Load a synteny100000 from row fetched with select * from synteny100000
 * from database.  Dispose of this with synteny100000Free(). */

struct synteny100000 *synteny100000LoadAll(char *fileName);
/* Load all synteny100000 from a tab-separated file.
 * Dispose of this with synteny100000FreeList(). */

struct synteny100000 *synteny100000LoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all synteny100000 from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with synteny100000FreeList(). */

struct synteny100000 *synteny100000CommaIn(char **pS, struct synteny100000 *ret);
/* Create a synteny100000 out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new synteny100000 */

void synteny100000Free(struct synteny100000 **pEl);
/* Free a single dynamically allocated synteny100000 such as created
 * with synteny100000Load(). */

void synteny100000FreeList(struct synteny100000 **pList);
/* Free a list of dynamically allocated synteny100000's */

void synteny100000Output(struct synteny100000 *el, FILE *f, char sep, char lastSep);
/* Print out synteny100000.  Separate fields with sep. Follow last field with lastSep. */

#define synteny100000TabOut(el,f) synteny100000Output(el,f,'\t','\n');
/* Print out synteny100000 as a line in a tab-separated file. */

#define synteny100000CommaOut(el,f) synteny100000Output(el,f,',',',');
/* Print out synteny100000 as a comma separated list including final comma. */

#endif /* SYNTENY100000_H */

