/* fbTables.h was originally generated by the autoSql program, which also 
 * generated fbTables.c and fbTables.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2004 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef FBTABLES_H
#define FBTABLES_H

#define FBGENE_NUM_COLS 3

struct fbGene
/* Links FlyBase IDs, gene symbols and gene names */
    {
    struct fbGene *next;  /* Next in singly linked list. */
    char *geneId;	/* FlyBase ID */
    char *geneSym;	/* Short gene symbol */
    char *geneName;	/* Gene name - up to a couple of words */
    };

void fbGeneStaticLoad(char **row, struct fbGene *ret);
/* Load a row from fbGene table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct fbGene *fbGeneLoad(char **row);
/* Load a fbGene from row fetched with select * from fbGene
 * from database.  Dispose of this with fbGeneFree(). */

struct fbGene *fbGeneLoadAll(char *fileName);
/* Load all fbGene from whitespace-separated file.
 * Dispose of this with fbGeneFreeList(). */

struct fbGene *fbGeneLoadAllByChar(char *fileName, char chopper);
/* Load all fbGene from chopper separated file.
 * Dispose of this with fbGeneFreeList(). */

#define fbGeneLoadAllByTab(a) fbGeneLoadAllByChar(a, '\t');
/* Load all fbGene from tab separated file.
 * Dispose of this with fbGeneFreeList(). */

struct fbGene *fbGeneCommaIn(char **pS, struct fbGene *ret);
/* Create a fbGene out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbGene */

void fbGeneFree(struct fbGene **pEl);
/* Free a single dynamically allocated fbGene such as created
 * with fbGeneLoad(). */

void fbGeneFreeList(struct fbGene **pList);
/* Free a list of dynamically allocated fbGene's */

void fbGeneOutput(struct fbGene *el, FILE *f, char sep, char lastSep);
/* Print out fbGene.  Separate fields with sep. Follow last field with lastSep. */

#define fbGeneTabOut(el,f) fbGeneOutput(el,f,'\t','\n');
/* Print out fbGene as a line in a tab-separated file. */

#define fbGeneCommaOut(el,f) fbGeneOutput(el,f,',',',');
/* Print out fbGene as a comma separated list including final comma. */

#define FBTRANSCRIPT_NUM_COLS 2

struct fbTranscript
/* Links FlyBase gene IDs and BDGP transcript IDs */
    {
    struct fbTranscript *next;  /* Next in singly linked list. */
    char *geneId;	/* FlyBase Gene ID */
    char *transcriptId;	/* BDGP Transcript ID */
    };

void fbTranscriptStaticLoad(char **row, struct fbTranscript *ret);
/* Load a row from fbTranscript table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct fbTranscript *fbTranscriptLoad(char **row);
/* Load a fbTranscript from row fetched with select * from fbTranscript
 * from database.  Dispose of this with fbTranscriptFree(). */

struct fbTranscript *fbTranscriptLoadAll(char *fileName);
/* Load all fbTranscript from whitespace-separated file.
 * Dispose of this with fbTranscriptFreeList(). */

struct fbTranscript *fbTranscriptLoadAllByChar(char *fileName, char chopper);
/* Load all fbTranscript from chopper separated file.
 * Dispose of this with fbTranscriptFreeList(). */

#define fbTranscriptLoadAllByTab(a) fbTranscriptLoadAllByChar(a, '\t');
/* Load all fbTranscript from tab separated file.
 * Dispose of this with fbTranscriptFreeList(). */

struct fbTranscript *fbTranscriptCommaIn(char **pS, struct fbTranscript *ret);
/* Create a fbTranscript out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbTranscript */

void fbTranscriptFree(struct fbTranscript **pEl);
/* Free a single dynamically allocated fbTranscript such as created
 * with fbTranscriptLoad(). */

void fbTranscriptFreeList(struct fbTranscript **pList);
/* Free a list of dynamically allocated fbTranscript's */

void fbTranscriptOutput(struct fbTranscript *el, FILE *f, char sep, char lastSep);
/* Print out fbTranscript.  Separate fields with sep. Follow last field with lastSep. */

#define fbTranscriptTabOut(el,f) fbTranscriptOutput(el,f,'\t','\n');
/* Print out fbTranscript as a line in a tab-separated file. */

#define fbTranscriptCommaOut(el,f) fbTranscriptOutput(el,f,',',',');
/* Print out fbTranscript as a comma separated list including final comma. */

#define FBSYNONYM_NUM_COLS 2

struct fbSynonym
/* Links all the names we call a gene to it's flybase ID */
    {
    struct fbSynonym *next;  /* Next in singly linked list. */
    char *geneId;	/* FlyBase ID */
    char *name;	/* A name (synonym or real) */
    };

void fbSynonymStaticLoad(char **row, struct fbSynonym *ret);
/* Load a row from fbSynonym table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct fbSynonym *fbSynonymLoad(char **row);
/* Load a fbSynonym from row fetched with select * from fbSynonym
 * from database.  Dispose of this with fbSynonymFree(). */

struct fbSynonym *fbSynonymLoadAll(char *fileName);
/* Load all fbSynonym from whitespace-separated file.
 * Dispose of this with fbSynonymFreeList(). */

struct fbSynonym *fbSynonymLoadAllByChar(char *fileName, char chopper);
/* Load all fbSynonym from chopper separated file.
 * Dispose of this with fbSynonymFreeList(). */

#define fbSynonymLoadAllByTab(a) fbSynonymLoadAllByChar(a, '\t');
/* Load all fbSynonym from tab separated file.
 * Dispose of this with fbSynonymFreeList(). */

struct fbSynonym *fbSynonymCommaIn(char **pS, struct fbSynonym *ret);
/* Create a fbSynonym out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbSynonym */

void fbSynonymFree(struct fbSynonym **pEl);
/* Free a single dynamically allocated fbSynonym such as created
 * with fbSynonymLoad(). */

void fbSynonymFreeList(struct fbSynonym **pList);
/* Free a list of dynamically allocated fbSynonym's */

void fbSynonymOutput(struct fbSynonym *el, FILE *f, char sep, char lastSep);
/* Print out fbSynonym.  Separate fields with sep. Follow last field with lastSep. */

#define fbSynonymTabOut(el,f) fbSynonymOutput(el,f,'\t','\n');
/* Print out fbSynonym as a line in a tab-separated file. */

#define fbSynonymCommaOut(el,f) fbSynonymOutput(el,f,',',',');
/* Print out fbSynonym as a comma separated list including final comma. */

#define FBALLELE_NUM_COLS 3

struct fbAllele
/* The alleles of a gene */
    {
    struct fbAllele *next;  /* Next in singly linked list. */
    int id;	/* Allele ID */
    char *geneId;	/* Flybase ID of gene */
    char *name;	/* Allele name */
    };

void fbAlleleStaticLoad(char **row, struct fbAllele *ret);
/* Load a row from fbAllele table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct fbAllele *fbAlleleLoad(char **row);
/* Load a fbAllele from row fetched with select * from fbAllele
 * from database.  Dispose of this with fbAlleleFree(). */

struct fbAllele *fbAlleleLoadAll(char *fileName);
/* Load all fbAllele from whitespace-separated file.
 * Dispose of this with fbAlleleFreeList(). */

struct fbAllele *fbAlleleLoadAllByChar(char *fileName, char chopper);
/* Load all fbAllele from chopper separated file.
 * Dispose of this with fbAlleleFreeList(). */

#define fbAlleleLoadAllByTab(a) fbAlleleLoadAllByChar(a, '\t');
/* Load all fbAllele from tab separated file.
 * Dispose of this with fbAlleleFreeList(). */

struct fbAllele *fbAlleleCommaIn(char **pS, struct fbAllele *ret);
/* Create a fbAllele out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbAllele */

void fbAlleleFree(struct fbAllele **pEl);
/* Free a single dynamically allocated fbAllele such as created
 * with fbAlleleLoad(). */

void fbAlleleFreeList(struct fbAllele **pList);
/* Free a list of dynamically allocated fbAllele's */

void fbAlleleOutput(struct fbAllele *el, FILE *f, char sep, char lastSep);
/* Print out fbAllele.  Separate fields with sep. Follow last field with lastSep. */

#define fbAlleleTabOut(el,f) fbAlleleOutput(el,f,'\t','\n');
/* Print out fbAllele as a line in a tab-separated file. */

#define fbAlleleCommaOut(el,f) fbAlleleOutput(el,f,',',',');
/* Print out fbAllele as a comma separated list including final comma. */

#define FBREF_NUM_COLS 2

struct fbRef
/* A literature or sometimes database reference */
    {
    struct fbRef *next;  /* Next in singly linked list. */
    int id;	/* Reference ID */
    char *text;	/* Usually begins with flybase ref ID, but not always */
    };

void fbRefStaticLoad(char **row, struct fbRef *ret);
/* Load a row from fbRef table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct fbRef *fbRefLoad(char **row);
/* Load a fbRef from row fetched with select * from fbRef
 * from database.  Dispose of this with fbRefFree(). */

struct fbRef *fbRefLoadAll(char *fileName);
/* Load all fbRef from whitespace-separated file.
 * Dispose of this with fbRefFreeList(). */

struct fbRef *fbRefLoadAllByChar(char *fileName, char chopper);
/* Load all fbRef from chopper separated file.
 * Dispose of this with fbRefFreeList(). */

#define fbRefLoadAllByTab(a) fbRefLoadAllByChar(a, '\t');
/* Load all fbRef from tab separated file.
 * Dispose of this with fbRefFreeList(). */

struct fbRef *fbRefCommaIn(char **pS, struct fbRef *ret);
/* Create a fbRef out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbRef */

void fbRefFree(struct fbRef **pEl);
/* Free a single dynamically allocated fbRef such as created
 * with fbRefLoad(). */

void fbRefFreeList(struct fbRef **pList);
/* Free a list of dynamically allocated fbRef's */

void fbRefOutput(struct fbRef *el, FILE *f, char sep, char lastSep);
/* Print out fbRef.  Separate fields with sep. Follow last field with lastSep. */

#define fbRefTabOut(el,f) fbRefOutput(el,f,'\t','\n');
/* Print out fbRef as a line in a tab-separated file. */

#define fbRefCommaOut(el,f) fbRefOutput(el,f,',',',');
/* Print out fbRef as a comma separated list including final comma. */

#define FBROLE_NUM_COLS 4

struct fbRole
/* Role of gene in wildType */
    {
    struct fbRole *next;  /* Next in singly linked list. */
    char *geneId;	/* Flybase Gene ID */
    int fbAllele;	/* ID in fbAllele table or 0 if not allele-specific */
    int fbRef;	/* ID in fbRef table */
    char *text;	/* Descriptive text */
    };

void fbRoleStaticLoad(char **row, struct fbRole *ret);
/* Load a row from fbRole table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct fbRole *fbRoleLoad(char **row);
/* Load a fbRole from row fetched with select * from fbRole
 * from database.  Dispose of this with fbRoleFree(). */

struct fbRole *fbRoleLoadAll(char *fileName);
/* Load all fbRole from whitespace-separated file.
 * Dispose of this with fbRoleFreeList(). */

struct fbRole *fbRoleLoadAllByChar(char *fileName, char chopper);
/* Load all fbRole from chopper separated file.
 * Dispose of this with fbRoleFreeList(). */

#define fbRoleLoadAllByTab(a) fbRoleLoadAllByChar(a, '\t');
/* Load all fbRole from tab separated file.
 * Dispose of this with fbRoleFreeList(). */

struct fbRole *fbRoleCommaIn(char **pS, struct fbRole *ret);
/* Create a fbRole out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbRole */

void fbRoleFree(struct fbRole **pEl);
/* Free a single dynamically allocated fbRole such as created
 * with fbRoleLoad(). */

void fbRoleFreeList(struct fbRole **pList);
/* Free a list of dynamically allocated fbRole's */

void fbRoleOutput(struct fbRole *el, FILE *f, char sep, char lastSep);
/* Print out fbRole.  Separate fields with sep. Follow last field with lastSep. */

#define fbRoleTabOut(el,f) fbRoleOutput(el,f,'\t','\n');
/* Print out fbRole as a line in a tab-separated file. */

#define fbRoleCommaOut(el,f) fbRoleOutput(el,f,',',',');
/* Print out fbRole as a comma separated list including final comma. */

#define FBPHENOTYPE_NUM_COLS 4

struct fbPhenotype
/* Observed phenotype in mutant.  Sometimes contains gene function info */
    {
    struct fbPhenotype *next;  /* Next in singly linked list. */
    char *geneId;	/* Flybase Gene ID */
    int fbAllele;	/* ID in fbAllele table or 0 if not allele-specific */
    int fbRef;	/* ID in fbRef table */
    char *text;	/* Descriptive text */
    };

void fbPhenotypeStaticLoad(char **row, struct fbPhenotype *ret);
/* Load a row from fbPhenotype table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct fbPhenotype *fbPhenotypeLoad(char **row);
/* Load a fbPhenotype from row fetched with select * from fbPhenotype
 * from database.  Dispose of this with fbPhenotypeFree(). */

struct fbPhenotype *fbPhenotypeLoadAll(char *fileName);
/* Load all fbPhenotype from whitespace-separated file.
 * Dispose of this with fbPhenotypeFreeList(). */

struct fbPhenotype *fbPhenotypeLoadAllByChar(char *fileName, char chopper);
/* Load all fbPhenotype from chopper separated file.
 * Dispose of this with fbPhenotypeFreeList(). */

#define fbPhenotypeLoadAllByTab(a) fbPhenotypeLoadAllByChar(a, '\t');
/* Load all fbPhenotype from tab separated file.
 * Dispose of this with fbPhenotypeFreeList(). */

struct fbPhenotype *fbPhenotypeCommaIn(char **pS, struct fbPhenotype *ret);
/* Create a fbPhenotype out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbPhenotype */

void fbPhenotypeFree(struct fbPhenotype **pEl);
/* Free a single dynamically allocated fbPhenotype such as created
 * with fbPhenotypeLoad(). */

void fbPhenotypeFreeList(struct fbPhenotype **pList);
/* Free a list of dynamically allocated fbPhenotype's */

void fbPhenotypeOutput(struct fbPhenotype *el, FILE *f, char sep, char lastSep);
/* Print out fbPhenotype.  Separate fields with sep. Follow last field with lastSep. */

#define fbPhenotypeTabOut(el,f) fbPhenotypeOutput(el,f,'\t','\n');
/* Print out fbPhenotype as a line in a tab-separated file. */

#define fbPhenotypeCommaOut(el,f) fbPhenotypeOutput(el,f,',',',');
/* Print out fbPhenotype as a comma separated list including final comma. */

#define FBGO_NUM_COLS 3

struct fbGo
/* Links FlyBase gene IDs and GO IDs/aspects */
    {
    struct fbGo *next;  /* Next in singly linked list. */
    char *geneId;	/* Flybase Gene ID */
    char *goId;	/* GO ID */
    char *aspect;	/* P (process), F (function) or C (cellular component) */
    };

void fbGoStaticLoad(char **row, struct fbGo *ret);
/* Load a row from fbGo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct fbGo *fbGoLoad(char **row);
/* Load a fbGo from row fetched with select * from fbGo
 * from database.  Dispose of this with fbGoFree(). */

struct fbGo *fbGoLoadAll(char *fileName);
/* Load all fbGo from whitespace-separated file.
 * Dispose of this with fbGoFreeList(). */

struct fbGo *fbGoLoadAllByChar(char *fileName, char chopper);
/* Load all fbGo from chopper separated file.
 * Dispose of this with fbGoFreeList(). */

#define fbGoLoadAllByTab(a) fbGoLoadAllByChar(a, '\t');
/* Load all fbGo from tab separated file.
 * Dispose of this with fbGoFreeList(). */

struct fbGo *fbGoCommaIn(char **pS, struct fbGo *ret);
/* Create a fbGo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbGo */

void fbGoFree(struct fbGo **pEl);
/* Free a single dynamically allocated fbGo such as created
 * with fbGoLoad(). */

void fbGoFreeList(struct fbGo **pList);
/* Free a list of dynamically allocated fbGo's */

void fbGoOutput(struct fbGo *el, FILE *f, char sep, char lastSep);
/* Print out fbGo.  Separate fields with sep. Follow last field with lastSep. */

#define fbGoTabOut(el,f) fbGoOutput(el,f,'\t','\n');
/* Print out fbGo as a line in a tab-separated file. */

#define fbGoCommaOut(el,f) fbGoOutput(el,f,',',',');
/* Print out fbGo as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* FBTABLES_H */

