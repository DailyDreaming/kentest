/* refCluster.h was originally generated by the autoSql program, which also 
 * generated refCluster.c and refCluster.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2007 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#ifndef REFCLUSTER_H
#define REFCLUSTER_H

#define REFCLUSTER_NUM_COLS 7

struct refCluster
/* A cluster of overlapping refSeq. */
    {
    struct refCluster *next;  /* Next in singly linked list. */
    char *chrom;	/* Chromosome */
    int chromStart;	/* Chromosome start position */
    int chromEnd;	/* Chromosome end position */
    char *name;	/* Cluster name */
    char strand[2];	/* Strand. */
    int refCount;	/* Number in cluster */
    char **refArray;	/* Array of accessions */
    };

struct refCluster *refClusterLoad(char **row);
/* Load a refCluster from row fetched with select * from refCluster
 * from database.  Dispose of this with refClusterFree(). */

struct refCluster *refClusterLoadAll(char *fileName);
/* Load all refCluster from whitespace-separated file.
 * Dispose of this with refClusterFreeList(). */

struct refCluster *refClusterLoadAllByChar(char *fileName, char chopper);
/* Load all refCluster from chopper separated file.
 * Dispose of this with refClusterFreeList(). */

#define refClusterLoadAllByTab(a) refClusterLoadAllByChar(a, '\t');
/* Load all refCluster from tab separated file.
 * Dispose of this with refClusterFreeList(). */

struct refCluster *refClusterCommaIn(char **pS, struct refCluster *ret);
/* Create a refCluster out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new refCluster */

void refClusterFree(struct refCluster **pEl);
/* Free a single dynamically allocated refCluster such as created
 * with refClusterLoad(). */

void refClusterFreeList(struct refCluster **pList);
/* Free a list of dynamically allocated refCluster's */

void refClusterOutput(struct refCluster *el, FILE *f, char sep, char lastSep);
/* Print out refCluster.  Separate fields with sep. Follow last field with lastSep. */

#define refClusterTabOut(el,f) refClusterOutput(el,f,'\t','\n');
/* Print out refCluster as a line in a tab-separated file. */

#define refClusterCommaOut(el,f) refClusterOutput(el,f,',',',');
/* Print out refCluster as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* REFCLUSTER_H */

