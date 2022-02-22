/* pPair.h was originally generated by the autoSql program, which also 
 * generated pPair.c and pPair.sql.  This header links the database and the RAM 
 * representation of objects. */

#ifndef PPAIR_H
#define PPAIR_H

struct pPairInfo
/* Info on a plasmid pair */
    {
    struct pPairInfo *next;  /* Next in singly linked list. */
    char *fRead;	/* Forward read */
    char *rRead;	/* Reverse read */
    char *clone;	/* Clone name */
    int minSize;	/* Minimum insert size */
    int maxSize;	/* Maximum insert size */
    };

void pPairInfoStaticLoad(char **row, struct pPairInfo *ret);
/* Load a row from pPairInfo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct pPairInfo *pPairInfoLoad(char **row);
/* Load a pPairInfo from row fetched with select * from pPairInfo
 * from database.  Dispose of this with pPairInfoFree(). */

struct pPairInfo *pPairInfoCommaIn(char **pS, struct pPairInfo *ret);
/* Create a pPairInfo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new pPairInfo */

void pPairInfoFree(struct pPairInfo **pEl);
/* Free a single dynamically allocated pPairInfo such as created
 * with pPairInfoLoad(). */

void pPairInfoFreeList(struct pPairInfo **pList);
/* Free a list of dynamically allocated pPairInfo's */

void pPairInfoOutput(struct pPairInfo *el, FILE *f, char sep, char lastSep);
/* Print out pPairInfo.  Separate fields with sep. Follow last field with lastSep. */

#define pPairInfoTabOut(el,f) pPairInfoOutput(el,f,'\t','\n');
/* Print out pPairInfo as a line in a tab-separated file. */

#define pPairInfoCommaOut(el,f) pPairInfoOutput(el,f,',',',');
/* Print out pPairInfo as a comma separated list including final comma. */

#endif /* PPAIR_H */

