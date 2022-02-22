/* snpFasta.h was originally generated by the autoSql program, which also 
 * generated snpFasta.c and snpFasta.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2006 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef SNPFASTA_H
#define SNPFASTA_H

#define SNPFASTA_NUM_COLS 7

struct snpFasta
/* Polymorphism data from dbSnp rs_fasta files */
    {
    struct snpFasta *next;  /* Next in singly linked list. */
    char *rsId;	/* Reference SNP identifier */
    char *chrom;	/* Chromosome (can be 'multi') */
    char *molType;	/* Sample type from exemplar ss */
    char *class;	/* Single, in-del, heterozygous, microsatelite, named, etc. */
    char *observed;	/* The sequences of the observed alleles from rs-fasta files */
    char *leftFlank;	/* Left flanking sequence */
    char *rightFlank;	/* Right flanking sequence */
    };

void snpFastaStaticLoad(char **row, struct snpFasta *ret);
/* Load a row from snpFasta table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct snpFasta *snpFastaLoad(char **row);
/* Load a snpFasta from row fetched with select * from snpFasta
 * from database.  Dispose of this with snpFastaFree(). */

struct snpFasta *snpFastaLoadAll(char *fileName);
/* Load all snpFasta from whitespace-separated file.
 * Dispose of this with snpFastaFreeList(). */

struct snpFasta *snpFastaLoadAllByChar(char *fileName, char chopper);
/* Load all snpFasta from chopper separated file.
 * Dispose of this with snpFastaFreeList(). */

#define snpFastaLoadAllByTab(a) snpFastaLoadAllByChar(a, '\t');
/* Load all snpFasta from tab separated file.
 * Dispose of this with snpFastaFreeList(). */

struct snpFasta *snpFastaCommaIn(char **pS, struct snpFasta *ret);
/* Create a snpFasta out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new snpFasta */

void snpFastaFree(struct snpFasta **pEl);
/* Free a single dynamically allocated snpFasta such as created
 * with snpFastaLoad(). */

void snpFastaFreeList(struct snpFasta **pList);
/* Free a list of dynamically allocated snpFasta's */

void snpFastaOutput(struct snpFasta *el, FILE *f, char sep, char lastSep);
/* Print out snpFasta.  Separate fields with sep. Follow last field with lastSep. */

#define snpFastaTabOut(el,f) snpFastaOutput(el,f,'\t','\n');
/* Print out snpFasta as a line in a tab-separated file. */

#define snpFastaCommaOut(el,f) snpFastaOutput(el,f,',',',');
/* Print out snpFasta as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* SNPFASTA_H */

void snpFastaTableCreate(struct sqlConnection *conn);

