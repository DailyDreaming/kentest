/* stsInfo2.h was originally generated by the autoSql program, which also 
 * generated stsInfo2.c and stsInfo2.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2002 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef STSINFO2_H
#define STSINFO2_H

struct stsInfo2
/* Constant STS marker information - revision */
    {
    struct stsInfo2 *next;  /* Next in singly linked list. */
    unsigned identNo;	/* UCSC identification number */
    char *name;	/* Official UCSC name */
    unsigned gbCount;	/* Number of related GenBank accessions */
    char **genbank;	/* Related GeneBank accessions */
    unsigned gdbCount;	/* Number of related GDB identifiers */
    char **gdb;	/* Related GDB identifies */
    unsigned nameCount;	/* Number of alias names */
    char **otherNames;	/* Alias names */
    unsigned dbSTSid;	/* ID number in UniSTS or dbSTS */
    unsigned otherDbstsCount;	/* Number of related dbSTS IDs */
    unsigned *otherDbSTS;	/* Related dbSTS IDs */
    char *leftPrimer;	/* 5' primer sequence */
    char *rightPrimer;	/* 3' primer sequence */
    char *distance;	/* Length of STS sequence */
    char *organism;	/* Organism for which STS discovered */
    unsigned sequence;	/* Whether the full sequence is available (1) or not (0) for STS */
    unsigned otherUCSCcount;	/* Number of related active UCSC ids */
    unsigned *otherUCSC;	/* Related active UCSC ids */
    unsigned mergeUCSCcount;	/* Number of merged inactive UCSC ids */
    unsigned *mergeUCSC;	/* Related merged inactive UCSC ids */
    char *genethonName;	/* Name in Genethon map */
    char *genethonChr;	/* Chromosome in Genethon map */
    float genethonPos;	/* Position in Genethon map */
    float genethonLOD;	/* LOD score in Genethon map */
    char *marshfieldName;	/* Name in Marshfield map */
    char *marshfieldChr;	/* Chromosome in Marshfield map */
    float marshfieldPos;	/* Position in Marshfield map */
    float marshfieldLOD;	/* LOD score in Marshfield map */
    char *wiyacName;	/* Name in WI YAC map */
    char *wiyacChr;	/* Chromosome in WI YAC map */
    float wiyacPos;	/* Position in WI YAC map */
    float wiyacLOD;	/* LOD score in WI YAC map */
    char *wirhName;	/* Name in WI RH map */
    char *wirhChr;	/* Chromosome in WI RH map */
    float wirhPos;	/* Position in WI RH map */
    float wirhLOD;	/* LOD score in WI RH map */
    char *gm99gb4Name;	/* Name in GeneMap99 GB4 map */
    char *gm99gb4Chr;	/* Chromosome in GeneMap99 GB4 map */
    float gm99gb4Pos;	/* Position in GeneMap99 GB4 map */
    float gm99gb4LOD;	/* LOD score in GeneMap99 GB4 map */
    char *gm99g3Name;	/* Name in GeneMap99 G3 map */
    char *gm99g3Chr;	/* Chromosome in GeneMap99 G3 map */
    float gm99g3Pos;	/* Position in GeneMap99 G3 map */
    float gm99g3LOD;	/* LOD score in GenMap99 G3 map */
    char *tngName;	/* Name in Stanford TNG map */
    char *tngChr;	/* Chromosome in Stanford TNG map */
    float tngPos;	/* Position in Stanford TNG map */
    float tngLOD;	/* LOD score in Stanford TNG map */
    char *decodeName;	/* Name in deCODE map */
    char *decodeChr;	/* Chromosome in deCODE TNG map */
    float decodePos;	/* Position in deCODE TNG map */
    float decodeLOD;	/* LOD score in deCODE TNG map */
    };

struct stsInfo2 *stsInfo2Load(char **row);
/* Load a stsInfo2 from row fetched with select * from stsInfo2
 * from database.  Dispose of this with stsInfo2Free(). */

struct stsInfo2 *stsInfo2LoadAll(char *fileName);
/* Load all stsInfo2 from a tab-separated file.
 * Dispose of this with stsInfo2FreeList(). */

struct stsInfo2 *stsInfo2LoadWhere(struct sqlConnection *conn, char *table, char *where);
/* Load all stsInfo2 from table that satisfy where clause. The
 * where clause may be NULL in which case whole table is loaded
 * Dispose of this with stsInfo2FreeList(). */

struct stsInfo2 *stsInfo2CommaIn(char **pS, struct stsInfo2 *ret);
/* Create a stsInfo2 out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new stsInfo2 */

void stsInfo2Free(struct stsInfo2 **pEl);
/* Free a single dynamically allocated stsInfo2 such as created
 * with stsInfo2Load(). */

void stsInfo2FreeList(struct stsInfo2 **pList);
/* Free a list of dynamically allocated stsInfo2's */

void stsInfo2Output(struct stsInfo2 *el, FILE *f, char sep, char lastSep);
/* Print out stsInfo2.  Separate fields with sep. Follow last field with lastSep. */

#define stsInfo2TabOut(el,f) stsInfo2Output(el,f,'\t','\n');
/* Print out stsInfo2 as a line in a tab-separated file. */

#define stsInfo2CommaOut(el,f) stsInfo2Output(el,f,',',',');
/* Print out stsInfo2 as a comma separated list including final comma. */

#endif /* STSINFO2_H */

