/* rhMapZfishInfo.c was originally generated by the autoSql program, which also 
 * generated rhMapZfishInfo.h and rhMapZfishInfo.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "rhMapZfishInfo.h"


void rhMapZfishInfoStaticLoad(char **row, struct rhMapZfishInfo *ret)
/* Load a row from rhMapZfishInfo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->zfinId = row[1];
ret->linkageGp = row[2];
ret->position = sqlUnsigned(row[3]);
ret->distance = sqlUnsigned(row[4]);
ret->markerType = row[5];
ret->source = row[6];
ret->mapSite = row[7];
ret->leftPrimer = row[8];
ret->rightPrimer = row[9];
}

struct rhMapZfishInfo *rhMapZfishInfoLoad(char **row)
/* Load a rhMapZfishInfo from row fetched with select * from rhMapZfishInfo
 * from database.  Dispose of this with rhMapZfishInfoFree(). */
{
struct rhMapZfishInfo *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->zfinId = cloneString(row[1]);
ret->linkageGp = cloneString(row[2]);
ret->position = sqlUnsigned(row[3]);
ret->distance = sqlUnsigned(row[4]);
ret->markerType = cloneString(row[5]);
ret->source = cloneString(row[6]);
ret->mapSite = cloneString(row[7]);
ret->leftPrimer = cloneString(row[8]);
ret->rightPrimer = cloneString(row[9]);
return ret;
}

struct rhMapZfishInfo *rhMapZfishInfoLoadAll(char *fileName) 
/* Load all rhMapZfishInfo from a whitespace-separated file.
 * Dispose of this with rhMapZfishInfoFreeList(). */
{
struct rhMapZfishInfo *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[10];

while (lineFileRow(lf, row))
    {
    el = rhMapZfishInfoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct rhMapZfishInfo *rhMapZfishInfoLoadAllByChar(char *fileName, char chopper) 
/* Load all rhMapZfishInfo from a chopper separated file.
 * Dispose of this with rhMapZfishInfoFreeList(). */
{
struct rhMapZfishInfo *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[10];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = rhMapZfishInfoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct rhMapZfishInfo *rhMapZfishInfoCommaIn(char **pS, struct rhMapZfishInfo *ret)
/* Create a rhMapZfishInfo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rhMapZfishInfo */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->zfinId = sqlStringComma(&s);
ret->linkageGp = sqlStringComma(&s);
ret->position = sqlUnsignedComma(&s);
ret->distance = sqlUnsignedComma(&s);
ret->markerType = sqlStringComma(&s);
ret->source = sqlStringComma(&s);
ret->mapSite = sqlStringComma(&s);
ret->leftPrimer = sqlStringComma(&s);
ret->rightPrimer = sqlStringComma(&s);
*pS = s;
return ret;
}

void rhMapZfishInfoFree(struct rhMapZfishInfo **pEl)
/* Free a single dynamically allocated rhMapZfishInfo such as created
 * with rhMapZfishInfoLoad(). */
{
struct rhMapZfishInfo *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->zfinId);
freeMem(el->linkageGp);
freeMem(el->markerType);
freeMem(el->source);
freeMem(el->mapSite);
freeMem(el->leftPrimer);
freeMem(el->rightPrimer);
freez(pEl);
}

void rhMapZfishInfoFreeList(struct rhMapZfishInfo **pList)
/* Free a list of dynamically allocated rhMapZfishInfo's */
{
struct rhMapZfishInfo *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    rhMapZfishInfoFree(&el);
    }
*pList = NULL;
}

void rhMapZfishInfoOutput(struct rhMapZfishInfo *el, FILE *f, char sep, char lastSep) 
/* Print out rhMapZfishInfo.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->zfinId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->linkageGp);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->position);
fputc(sep,f);
fprintf(f, "%u", el->distance);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->markerType);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->source);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->mapSite);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->leftPrimer);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->rightPrimer);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

