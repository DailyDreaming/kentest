/* growthCondition.c was originally generated by the autoSql program, which also 
 * generated growthCondition.h and growthCondition.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "growthCondition.h"


void growthConditionStaticLoad(char **row, struct growthCondition *ret)
/* Load a row from growthCondition table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->shortLabel = row[1];
ret->longLabel = row[2];
}

struct growthCondition *growthConditionLoad(char **row)
/* Load a growthCondition from row fetched with select * from growthCondition
 * from database.  Dispose of this with growthConditionFree(). */
{
struct growthCondition *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->shortLabel = cloneString(row[1]);
ret->longLabel = cloneString(row[2]);
return ret;
}

struct growthCondition *growthConditionLoadAll(char *fileName) 
/* Load all growthCondition from a whitespace-separated file.
 * Dispose of this with growthConditionFreeList(). */
{
struct growthCondition *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = growthConditionLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct growthCondition *growthConditionLoadAllByChar(char *fileName, char chopper) 
/* Load all growthCondition from a chopper separated file.
 * Dispose of this with growthConditionFreeList(). */
{
struct growthCondition *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = growthConditionLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct growthCondition *growthConditionCommaIn(char **pS, struct growthCondition *ret)
/* Create a growthCondition out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new growthCondition */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->shortLabel = sqlStringComma(&s);
ret->longLabel = sqlStringComma(&s);
*pS = s;
return ret;
}

void growthConditionFree(struct growthCondition **pEl)
/* Free a single dynamically allocated growthCondition such as created
 * with growthConditionLoad(). */
{
struct growthCondition *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->shortLabel);
freeMem(el->longLabel);
freez(pEl);
}

void growthConditionFreeList(struct growthCondition **pList)
/* Free a list of dynamically allocated growthCondition's */
{
struct growthCondition *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    growthConditionFree(&el);
    }
*pList = NULL;
}

void growthConditionOutput(struct growthCondition *el, FILE *f, char sep, char lastSep) 
/* Print out growthCondition.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->shortLabel);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->longLabel);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

