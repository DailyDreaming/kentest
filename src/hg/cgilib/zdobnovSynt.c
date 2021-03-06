/* zdobnovSynt.c was originally generated by the autoSql program, which also 
 * generated zdobnovSynt.h and zdobnovSynt.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "zdobnovSynt.h"


struct zdobnovSynt *zdobnovSyntLoad(char **row)
/* Load a zdobnovSynt from row fetched with select * from zdobnovSynt
 * from database.  Dispose of this with zdobnovSyntFree(). */
{
struct zdobnovSynt *ret;
int sizeOne;

AllocVar(ret);
ret->blockCount = sqlSigned(row[9]);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
strcpy(ret->strand, row[5]);
ret->thickStart = sqlUnsigned(row[6]);
ret->thickEnd = sqlUnsigned(row[7]);
ret->reserved = sqlUnsigned(row[8]);
sqlSignedDynamicArray(row[10], &ret->blockSizes, &sizeOne);
assert(sizeOne == ret->blockCount);
sqlSignedDynamicArray(row[11], &ret->chromStarts, &sizeOne);
assert(sizeOne == ret->blockCount);
sqlStringDynamicArray(row[12], &ret->geneNames, &sizeOne);
assert(sizeOne == ret->blockCount);
return ret;
}

struct zdobnovSynt *zdobnovSyntLoadAll(char *fileName) 
/* Load all zdobnovSynt from a whitespace-separated file.
 * Dispose of this with zdobnovSyntFreeList(). */
{
struct zdobnovSynt *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[13];

while (lineFileRow(lf, row))
    {
    el = zdobnovSyntLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct zdobnovSynt *zdobnovSyntLoadAllByChar(char *fileName, char chopper) 
/* Load all zdobnovSynt from a chopper separated file.
 * Dispose of this with zdobnovSyntFreeList(). */
{
struct zdobnovSynt *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[13];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = zdobnovSyntLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct zdobnovSynt *zdobnovSyntCommaIn(char **pS, struct zdobnovSynt *ret)
/* Create a zdobnovSynt out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new zdobnovSynt */
{
char *s = *pS;
int i;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->thickStart = sqlUnsignedComma(&s);
ret->thickEnd = sqlUnsignedComma(&s);
ret->reserved = sqlUnsignedComma(&s);
ret->blockCount = sqlSignedComma(&s);
s = sqlEatChar(s, '{');
AllocArray(ret->blockSizes, ret->blockCount);
for (i=0; i<ret->blockCount; ++i)
    {
    ret->blockSizes[i] = sqlSignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
s = sqlEatChar(s, '{');
AllocArray(ret->chromStarts, ret->blockCount);
for (i=0; i<ret->blockCount; ++i)
    {
    ret->chromStarts[i] = sqlSignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
s = sqlEatChar(s, '{');
AllocArray(ret->geneNames, ret->blockCount);
for (i=0; i<ret->blockCount; ++i)
    {
    ret->geneNames[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
*pS = s;
return ret;
}

void zdobnovSyntFree(struct zdobnovSynt **pEl)
/* Free a single dynamically allocated zdobnovSynt such as created
 * with zdobnovSyntLoad(). */
{
struct zdobnovSynt *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->blockSizes);
freeMem(el->chromStarts);
/* All strings in geneNames are allocated at once, so only need to free first. */
if (el->geneNames != NULL)
    freeMem(el->geneNames[0]);
freeMem(el->geneNames);
freez(pEl);
}

void zdobnovSyntFreeList(struct zdobnovSynt **pList)
/* Free a list of dynamically allocated zdobnovSynt's */
{
struct zdobnovSynt *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    zdobnovSyntFree(&el);
    }
*pList = NULL;
}

void zdobnovSyntOutput(struct zdobnovSynt *el, FILE *f, char sep, char lastSep) 
/* Print out zdobnovSynt.  Separate fields with sep. Follow last field with lastSep. */
{
int i;
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
fprintf(f, "%u", el->thickStart);
fputc(sep,f);
fprintf(f, "%u", el->thickEnd);
fputc(sep,f);
fprintf(f, "%u", el->reserved);
fputc(sep,f);
fprintf(f, "%d", el->blockCount);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->blockCount; ++i)
    {
    fprintf(f, "%d", el->blockSizes[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->blockCount; ++i)
    {
    fprintf(f, "%d", el->chromStarts[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(sep,f);
if (sep == ',') fputc('{',f);
for (i=0; i<el->blockCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->geneNames[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

