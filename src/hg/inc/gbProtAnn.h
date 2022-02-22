/* gbProtAnn.h was originally generated by the autoSql program, which also 
 * generated gbProtAnn.c and gbProtAnn.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2003 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef GBPROTANN_H
#define GBPROTANN_H

struct gbProtAnn
/* Protein Annotations from GenPept mat_peptide fields */
    {
    struct gbProtAnn *next;  /* Next in singly linked list. */
    char *chrom;	/* chromosome */
    unsigned chromStart;	/* Start position in chromosome */
    unsigned chromEnd;	/* End position in chromosome */
    char *name;	/* Name of item */
    char *product;	/* Protein product name */
    char *note;	/* Note (may be empty) */
    char *proteinId;	/* GenBank protein accession(.version) */
    unsigned giId;	/* GenBank db_xref number */
    };

void gbProtAnnStaticLoad(char **row, struct gbProtAnn *ret);
/* Load a row from gbProtAnn table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct gbProtAnn *gbProtAnnLoad(char **row);
/* Load a gbProtAnn from row fetched with select * from gbProtAnn
 * from database.  Dispose of this with gbProtAnnFree(). */

struct gbProtAnn *gbProtAnnLoadAll(char *fileName);
/* Load all gbProtAnn from a tab-separated file.
 * Dispose of this with gbProtAnnFreeList(). */

struct gbProtAnn *gbProtAnnCommaIn(char **pS, struct gbProtAnn *ret);
/* Create a gbProtAnn out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gbProtAnn */

void gbProtAnnFree(struct gbProtAnn **pEl);
/* Free a single dynamically allocated gbProtAnn such as created
 * with gbProtAnnLoad(). */

void gbProtAnnFreeList(struct gbProtAnn **pList);
/* Free a list of dynamically allocated gbProtAnn's */

void gbProtAnnOutput(struct gbProtAnn *el, FILE *f, char sep, char lastSep);
/* Print out gbProtAnn.  Separate fields with sep. Follow last field with lastSep. */

#define gbProtAnnTabOut(el,f) gbProtAnnOutput(el,f,'\t','\n');
/* Print out gbProtAnn as a line in a tab-separated file. */

#define gbProtAnnCommaOut(el,f) gbProtAnnOutput(el,f,',',',');
/* Print out gbProtAnn as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* GBPROTANN_H */

