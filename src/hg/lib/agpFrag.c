/* agpFrag.c was originally generated by the autoSql program, which also 
 * generated agpFrag.h and agpFrag.sql.  This module links the database and the RAM 
 * representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "jksql.h"
#include "agpFrag.h"
#include "linefile.h"


void agpFragStaticLoad(char **row, struct agpFrag *ret)
/* Load a row from agpFrag table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{
ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->ix = sqlSigned(row[3]);
strcpy(ret->type, row[4]);
ret->frag = row[5];
ret->fragStart = sqlSigned(row[6]);
ret->fragEnd = sqlUnsigned(row[7]);
strcpy(ret->strand, row[8]);
}

struct agpFrag *agpFragLoad(char **row)
/* Load a agpFrag from row fetched with select * from agpFrag
 * from database.  Dispose of this with agpFragFree(). */
{
struct agpFrag *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->ix = sqlSigned(row[3]);
strcpy(ret->type, row[4]);
ret->frag = cloneString(row[5]);
ret->fragStart = sqlUnsigned(row[6]);
ret->fragEnd = sqlUnsigned(row[7]);
strcpy(ret->strand, row[8]);
return ret;
}

struct agpFrag *agpFragCommaIn(char **pS, struct agpFrag *ret)
/* Create a agpFrag out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new agpFrag */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->ix = sqlSignedComma(&s);
sqlFixedStringComma(&s, ret->type, sizeof(ret->type));
ret->frag = sqlStringComma(&s);
ret->fragStart = sqlUnsignedComma(&s);
ret->fragEnd = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
*pS = s;
return ret;
}

void agpFragFree(struct agpFrag **pEl)
/* Free a single dynamically allocated agpFrag such as created
 * with agpFragLoad(). */
{
struct agpFrag *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->frag);
freez(pEl);
}

void agpFragFreeList(struct agpFrag **pList)
/* Free a list of dynamically allocated agpFrag's */
{
struct agpFrag *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    agpFragFree(&el);
    }
*pList = NULL;
}

void agpFragOutput(struct agpFrag *el, FILE *f, char sep, char lastSep) 
/* Print out agpFrag.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart+1);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
fprintf(f, "%d", el->ix);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->type);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->frag);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->fragStart+1);
fputc(sep,f);
fprintf(f, "%u", el->fragEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

struct agpFrag *agpFragLoadAll(char *fileName) 
/* Load all agpFrag from a tab-separated file.
 * Dispose of this with agpFragFreeList(). */
{
struct agpFrag *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileRow(lf, row))
    {
    el = agpFragLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

/* ---------------------- End autoSql generated code. ---------------------- */

struct agpFrag *agpFragLoadAllNotGaps(char *fileName) 
/* Load all agpFrag from a tab-separated file.
 * Dispose of this with agpFragFreeList(). */
{
struct agpFrag *list = NULL, *el=NULL;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *words[32];
int wordCount = 0;

/* Check to make sure there is something in the file. */
wordCount = lineFileChop(lf, words);
if (wordCount == 0)
    errAbort("%s appears to be empty", fileName);
lineFileClose(&lf);

lf = lineFileOpen(fileName, TRUE);
while ((wordCount = lineFileChop(lf, words)) > 0)
    {
    if (wordCount < 5)
	errAbort("Short line %d of %s", lf->lineIx, lf->fileName);
    if(words[4][0] == 'N' || words[4][0] == 'U')
	continue;
    el = agpFragLoad(words);
/* There is a strange thing about agp files, Jim's load functions subtract 1 off
   the chromStart and fragStart but if you're loading off of files from the
   database they have already had 1 subtracted off so I'm going to add it back
   here. */
    el->chromStart++;  
    el->fragStart++;
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}
