/* rosChr22Dat.h was originally generated by the autoSql program, which also 
 * generated rosChr22Dat.c and rosChr22Dat.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2005 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef ROSCHR22DAT_H
#define ROSCHR22DAT_H

struct rosChr22Dat
/* Detailed Expression Data Record For Rosetta Chr 22 Data */
    {
    struct rosChr22Dat *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome Name */
    unsigned chromStart;	/* Start in Chromosome */
    unsigned chromEnd;	/* End in Chromosome */
    char *name;	/* human name */
    int probeType;	/* Whether probes came from type 1 array or type 2 */
    int labelType;	/* 1 equals standard labeling, 2 equals reverse labeling */
    char *strand;	/* + or - */
    char *expName;	/* Experiment Name */
    char *fileName;	/* File that data comes from */
    char *exonName;	/* exon identifier from Rosetta */
    char *controlType;	/* true if control gene, false otherwise */
    int probeID;	/* featureNumber */
    float nSigCy3;	/* normalized signal in Cy3 */
    float rSigCy3;	/* raw signal in Cy3 */
    int pixelsCy3;	/* number of pixels in Cy3 */
    float bgrdCy3;	/* background value of Cy3 */
    float nSigCy5;	/* normalized signal in Cy5 */
    float rSigCy5;	/* raw signal in Cy5 */
    int pixelsCy5;	/* number of pixels in Cy5 */
    float bgrdCy5;	/* background value of Cy5 */
    float logRatio;	/* log ratio of hybridization */
    float logError;	/* uncertainty of log ratio in Rosetta error model */
    float xdev;	/* Rosetta's error model value */
    float pval;	/* P-value in Rosetta's Error Model */
    };

void rosChr22DatStaticLoad(char **row, struct rosChr22Dat *ret);
/* Load a row from rosChr22Dat table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct rosChr22Dat *rosChr22DatLoad(char **row);
/* Load a rosChr22Dat from row fetched with select * from rosChr22Dat
 * from database.  Dispose of this with rosChr22DatFree(). */

struct rosChr22Dat *rosChr22DatLoadAll(char *fileName);
/* Load all rosChr22Dat from a tab-separated file.
 * Dispose of this with rosChr22DatFreeList(). */

struct rosChr22Dat *rosChr22DatCommaIn(char **pS, struct rosChr22Dat *ret);
/* Create a rosChr22Dat out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rosChr22Dat */

void rosChr22DatFree(struct rosChr22Dat **pEl);
/* Free a single dynamically allocated rosChr22Dat such as created
 * with rosChr22DatLoad(). */

void rosChr22DatFreeList(struct rosChr22Dat **pList);
/* Free a list of dynamically allocated rosChr22Dat's */

void rosChr22DatOutput(struct rosChr22Dat *el, FILE *f, char sep, char lastSep);
/* Print out rosChr22Dat.  Separate fields with sep. Follow last field with lastSep. */

#define rosChr22DatTabOut(el,f) rosChr22DatOutput(el,f,'\t','\n');
/* Print out rosChr22Dat as a line in a tab-separated file. */

#define rosChr22DatCommaOut(el,f) rosChr22DatOutput(el,f,',',',');
/* Print out rosChr22Dat as a comma separated list including final comma. */

/**
 * rcdInitExpTable - creates hashes to look up experiment names
 * by a number and using an experiment name to get a number. 
 * This is useful for web scripts and calling things by other than their
 * full name.
 */
void rcdInitExpTable();

/**
 * rcdLookUpExpNumber - looks up an experiments representative number
 * using its name. Make sure to call rcdInitExpTable() before calling this
 * function.
 * @param char * name - experiment to look up, i.e. "Pool_vs_Colorectal_Adenocarcinoma"
 * @return int - experiment number, or -1 if not present, or -2 if rcdInitExpTable hasn't been called
 */
int rcdLookUpExpNumber(char *name);

/**
 * rcdLookUpExpName - looks up the name of an experiment using its
 * representative number. Make sure to call rcdInitExpTable() before calling this
 * function.
 * @param int - experiment name to lookup, should be between 0-68
 * @return char * - name of the experiment or NULL if not found. Remember to free when done.
 */
char *rcdLookUpExpName(int expNum);

/**
 * rcdLookUpGeneName - looks up the name of an experiment using its
 * representative number. Make sure to call rcdInitExpTable() before calling this
 * function.
 * @param int - gene name to lookup
 * @return char * - name of the gene or NULL if not found. Remember to free when done.
 */
char *rcdLookUpGeneName(int geneNum);

/**
 * rcdGetNumExp - returns the number of experiments that can be provided
 * by rcdLookUpExpName().
 * @return int - the number of experiments for use like <code>for(i=0;i<rcdGetNumExp;i++)</code>
 */
int rcdGetNumExp();

/**
 * rcdGetNumGenes - returns the number of experiments that can be provided
 * by rcdLookUpGeneName().
 * @return int - the number of experiments for use like <code>for(i=0;i<rcdGetNumGenes();i++)</code>
 */
int rcdGetNumGenes();




#endif /* ROSCHR22DAT_H */

