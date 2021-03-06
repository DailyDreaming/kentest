/* coloredExon.c was originally generated by the autoSql program, which also 
 * generated coloredExon.h and coloredExon.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "coloredExon.h"


struct coloredExon *coloredExonLoad(char **row)
/* Load a coloredExon from row fetched with select * from coloredExon
 * from database.  Dispose of this with coloredExonFree(). */
{
struct coloredExon *ret;

AllocVar(ret);
ret->blockCount = sqlSigned(row[9]);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->thickStart = sqlUnsigned(row[6]);
ret->thickEnd = sqlUnsigned(row[7]);
ret->reserved = sqlUnsigned(row[8]);
{
int sizeOne;
sqlSignedDynamicArray(row[10], &ret->blockSizes, &sizeOne);
assert(sizeOne == ret->blockCount);
}
{
int sizeOne;
sqlSignedDynamicArray(row[11], &ret->chromStarts, &sizeOne);
assert(sizeOne == ret->blockCount);
}
{
int sizeOne;
sqlStringDynamicArray(row[12], &ret->colors, &sizeOne);
assert(sizeOne == ret->blockCount);
}
return ret;
}

struct coloredExon *coloredExonLoadAll(char *fileName) 
/* Load all coloredExon from a whitespace-separated file.
 * Dispose of this with coloredExonFreeList(). */
{
struct coloredExon *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[13];

while (lineFileRow(lf, row))
    {
    el = coloredExonLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct coloredExon *coloredExonLoadAllByChar(char *fileName, char chopper) 
/* Load all coloredExon from a chopper separated file.
 * Dispose of this with coloredExonFreeList(). */
{
struct coloredExon *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[13];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = coloredExonLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct coloredExon *coloredExonCommaIn(char **pS, struct coloredExon *ret)
/* Create a coloredExon out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new coloredExon */
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
ret->thickStart = sqlUnsignedComma(&s);
ret->thickEnd = sqlUnsignedComma(&s);
ret->reserved = sqlUnsignedComma(&s);
ret->blockCount = sqlSignedComma(&s);
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->blockSizes, ret->blockCount);
for (i=0; i<ret->blockCount; ++i)
    {
    ret->blockSizes[i] = sqlSignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->chromStarts, ret->blockCount);
for (i=0; i<ret->blockCount; ++i)
    {
    ret->chromStarts[i] = sqlSignedComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
{
int i;
s = sqlEatChar(s, '{');
AllocArray(ret->colors, ret->blockCount);
for (i=0; i<ret->blockCount; ++i)
    {
    ret->colors[i] = sqlStringComma(&s);
    }
s = sqlEatChar(s, '}');
s = sqlEatChar(s, ',');
}
*pS = s;
return ret;
}

void coloredExonFree(struct coloredExon **pEl)
/* Free a single dynamically allocated coloredExon such as created
 * with coloredExonLoad(). */
{
struct coloredExon *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->blockSizes);
freeMem(el->chromStarts);
/* All strings in colors are allocated at once, so only need to free first. */
if (el->colors != NULL)
    freeMem(el->colors[0]);
freeMem(el->colors);
freez(pEl);
}

void coloredExonFreeList(struct coloredExon **pList)
/* Free a list of dynamically allocated coloredExon's */
{
struct coloredExon *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    coloredExonFree(&el);
    }
*pList = NULL;
}

void coloredExonOutput(struct coloredExon *el, FILE *f, char sep, char lastSep) 
/* Print out coloredExon.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%u", el->thickStart);
fputc(sep,f);
fprintf(f, "%u", el->thickEnd);
fputc(sep,f);
fprintf(f, "%u", el->reserved);
fputc(sep,f);
fprintf(f, "%d", el->blockCount);
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->blockCount; ++i)
    {
    fprintf(f, "%d", el->blockSizes[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->blockCount; ++i)
    {
    fprintf(f, "%d", el->chromStarts[i]);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(sep,f);
{
int i;
if (sep == ',') fputc('{',f);
for (i=0; i<el->blockCount; ++i)
    {
    if (sep == ',') fputc('"',f);
    fprintf(f, "%s", el->colors[i]);
    if (sep == ',') fputc('"',f);
    fputc(',', f);
    }
if (sep == ',') fputc('}',f);
}
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

