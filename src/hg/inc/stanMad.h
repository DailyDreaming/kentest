/* stanMad.h was originally generated by the autoSql program, which also 
 * generated stanMad.c and stanMad.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2002 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef STANMAD_H
#define STANMAD_H

struct stanMad
/* stanford's microarray database output */
    {
    struct stanMad *next;  /* Next in singly linked list. */
    char *exp;	/* Name of the experiment based on the array id. */
    char *name;	/* Name of the gene or sample that is at a given position. */
    char *type;	/* Indicates whether an element is a control or cDNA. */
    int ch1i;	/* The average total signal for each spot for Cy3 */
    int ch1b;	/* The local background calculated for each spot for Cy3 */
    int ch1d;	/* The difference between the total and background for each element. */
    int ch2i;	/* The average total signal for each spot for Cy5. */
    int ch2b;	/* The local background calculated for each spot for Cy5 */
    int ch2d;	/* The difference between the total and background for each element. */
    int ch2in;	/* The average total signal for each spot for Cy5 normalized so that the average log ratio of all well measured spots is equal to 0. */
    int ch2bn;	/* The local background calculated for each spot for Cy5 normalized so that the average log ratio of all well measured spots is equal to 0. */
    int ch2dn;	/* The difference between the total and background for each element normalized so that the average log ratio of all well measured spots is equal to 0. */
    float rat1;	/* CH1D/CH2D */
    float rat2;	/* CH2D/CH1D */
    float rat1n;	/* CH1D/CH2DN */
    float rat2n;	/* CH2DN/CH1D */
    float mrat;	/* unknown */
    float crt1;	/* and CRT2 Unused. */
    float crt2;	/* unused */
    float regr;	/* The ratio estimated by the slope of the line fit to the distribution of pixels in each spot. */
    float corr;	/* The correlation of the signal at each pixel of a spot in CH1 to CH2. */
    float edge;	/* unnknown */
    int fing;	/* unknown */
    int grid;	/* unknown */
    int arow;	/* unknown */
    int row;	/* unknown */
    int acol;	/* unknown */
    int col;	/* unknown */
    int plat;	/* The plate ID from which a sample was printed. */
    char *prow;	/* The plate row from which a sample was printed. */
    int pcol;	/* The plate column from which a sample was printed. */
    int flag;	/* A user defined field which identifies spots which are visually of low quality. The value 0 is good all other values represent poor quality spots. */
    int clid;	/* The Identification number of the printed cDNA clone. These are mostly IMAGE clones. It is recommended to verify the clone identity by GenBank lookup using the EST accession number (see above) */
    int spot;	/* The spot number on the array. */
    int left;	/* The left coordinate of the spot on the scanned Microarray Image */
    int top;	/* The top coordinate of the spot. */
    int right;	/* The right coordinate of the spot. */
    int bot;	/* The bottom coordinate of the spot. */
    char *acc5;	/* The 5' GenBank accession number for an EST generated from the printed cDNA clone (This is the most stable handle for retrieving up to date information about this cDNA clone) */
    char *acc3;	/* The 3' GenBank accession number for an EST generated from the printed cDNA clone (This is the most stable handle for retrieving up to date information about this cDNA clone) */
    };

void stanMadStaticLoad(char **row, struct stanMad *ret);
/* Load a row from stanMad table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct stanMad *stanMadLoad(char **row);
/* Load a stanMad from row fetched with select * from stanMad
 * from database.  Dispose of this with stanMadFree(). */

struct stanMad *stanMadLoadAll(char *fileName);
/* Load all stanMad from a tab-separated file.
 * Dispose of this with stanMadFreeList(). */

struct stanMad *stanMadCommaIn(char **pS, struct stanMad *ret);
/* Create a stanMad out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new stanMad */

void stanMadFree(struct stanMad **pEl);
/* Free a single dynamically allocated stanMad such as created
 * with stanMadLoad(). */

void stanMadFreeList(struct stanMad **pList);
/* Free a list of dynamically allocated stanMad's */

void stanMadOutput(struct stanMad *el, FILE *f, char sep, char lastSep);
/* Print out stanMad.  Separate fields with sep. Follow last field with lastSep. */

#define stanMadTabOut(el,f) stanMadOutput(el,f,'\t','\n');
/* Print out stanMad as a line in a tab-separated file. */

#define stanMadCommaOut(el,f) stanMadOutput(el,f,',',',');
/* Print out stanMad as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* STANMAD_H */

