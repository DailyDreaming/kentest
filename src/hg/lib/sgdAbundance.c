/* sgdAbundance.c was originally generated by the autoSql program, which also 
 * generated sgdAbundance.h and sgdAbundance.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "sgdAbundance.h"


void sgdAbundanceStaticLoad(char **row, struct sgdAbundance *ret)
/* Load a row from sgdAbundance table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->abundance = atof(row[1]);
ret->error = row[2];
}

struct sgdAbundance *sgdAbundanceLoad(char **row)
/* Load a sgdAbundance from row fetched with select * from sgdAbundance
 * from database.  Dispose of this with sgdAbundanceFree(). */
{
struct sgdAbundance *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->abundance = atof(row[1]);
ret->error = cloneString(row[2]);
return ret;
}

struct sgdAbundance *sgdAbundanceLoadAll(char *fileName) 
/* Load all sgdAbundance from a whitespace-separated file.
 * Dispose of this with sgdAbundanceFreeList(). */
{
struct sgdAbundance *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = sgdAbundanceLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct sgdAbundance *sgdAbundanceLoadAllByChar(char *fileName, char chopper) 
/* Load all sgdAbundance from a chopper separated file.
 * Dispose of this with sgdAbundanceFreeList(). */
{
struct sgdAbundance *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = sgdAbundanceLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct sgdAbundance *sgdAbundanceCommaIn(char **pS, struct sgdAbundance *ret)
/* Create a sgdAbundance out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new sgdAbundance */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->abundance = sqlFloatComma(&s);
ret->error = sqlStringComma(&s);
*pS = s;
return ret;
}

void sgdAbundanceFree(struct sgdAbundance **pEl)
/* Free a single dynamically allocated sgdAbundance such as created
 * with sgdAbundanceLoad(). */
{
struct sgdAbundance *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->error);
freez(pEl);
}

void sgdAbundanceFreeList(struct sgdAbundance **pList)
/* Free a list of dynamically allocated sgdAbundance's */
{
struct sgdAbundance *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    sgdAbundanceFree(&el);
    }
*pList = NULL;
}

void sgdAbundanceOutput(struct sgdAbundance *el, FILE *f, char sep, char lastSep) 
/* Print out sgdAbundance.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->abundance);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->error);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

