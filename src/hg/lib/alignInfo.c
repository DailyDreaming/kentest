/* alignInfo.c was originally generated by the autoSql program, which also 
 * generated alignInfo.h and alignInfo.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "alignInfo.h"


void alignInfoStaticLoad(char **row, struct alignInfo *ret)
/* Load a row from alignInfo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->hasmatch = sqlUnsigned(row[6]);
ret->orgn = row[7];
ret->alignChrom = row[8];
ret->alignChromStart = sqlUnsigned(row[9]);
ret->alignChromEnd = sqlUnsigned(row[10]);
}

struct alignInfo *alignInfoLoad(char **row)
/* Load a alignInfo from row fetched with select * from alignInfo
 * from database.  Dispose of this with alignInfoFree(). */
{
struct alignInfo *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->hasmatch = sqlUnsigned(row[6]);
ret->orgn = cloneString(row[7]);
ret->alignChrom = cloneString(row[8]);
ret->alignChromStart = sqlUnsigned(row[9]);
ret->alignChromEnd = sqlUnsigned(row[10]);
return ret;
}

struct alignInfo *alignInfoLoadAll(char *fileName) 
/* Load all alignInfo from a whitespace-separated file.
 * Dispose of this with alignInfoFreeList(). */
{
struct alignInfo *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[11];

while (lineFileRow(lf, row))
    {
    el = alignInfoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct alignInfo *alignInfoLoadAllByChar(char *fileName, char chopper) 
/* Load all alignInfo from a chopper separated file.
 * Dispose of this with alignInfoFreeList(). */
{
struct alignInfo *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[11];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = alignInfoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct alignInfo *alignInfoCommaIn(char **pS, struct alignInfo *ret)
/* Create a alignInfo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new alignInfo */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->hasmatch = sqlUnsignedComma(&s);
ret->orgn = sqlStringComma(&s);
ret->alignChrom = sqlStringComma(&s);
ret->alignChromStart = sqlUnsignedComma(&s);
ret->alignChromEnd = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void alignInfoFree(struct alignInfo **pEl)
/* Free a single dynamically allocated alignInfo such as created
 * with alignInfoLoad(). */
{
struct alignInfo *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->orgn);
freeMem(el->alignChrom);
freez(pEl);
}

void alignInfoFreeList(struct alignInfo **pList)
/* Free a list of dynamically allocated alignInfo's */
{
struct alignInfo *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    alignInfoFree(&el);
    }
*pList = NULL;
}

void alignInfoOutput(struct alignInfo *el, FILE *f, char sep, char lastSep) 
/* Print out alignInfo.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->score);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->hasmatch);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->orgn);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->alignChrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->alignChromStart);
fputc(sep,f);
fprintf(f, "%u", el->alignChromEnd);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

