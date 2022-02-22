/* tRNAs.c was originally generated by the autoSql program, which also 
 * generated tRNAs.h and tRNAs.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "tRNAs.h"


void tRNAsStaticLoad(char **row, struct tRNAs *ret)
/* Load a row from tRNAs table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->aa = row[6];
ret->ac = row[7];
ret->intron = row[8];
ret->trnaScore = sqlFloat(row[9]);
ret->genomeUrl = row[10];
ret->trnaUrl = row[11];
}

struct tRNAs *tRNAsLoad(char **row)
/* Load a tRNAs from row fetched with select * from tRNAs
 * from database.  Dispose of this with tRNAsFree(). */
{
struct tRNAs *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->aa = cloneString(row[6]);
ret->ac = cloneString(row[7]);
ret->intron = cloneString(row[8]);
ret->trnaScore = sqlFloat(row[9]);
ret->genomeUrl = cloneString(row[10]);
ret->trnaUrl = cloneString(row[11]);
return ret;
}

struct tRNAs *tRNAsLoadAll(char *fileName) 
/* Load all tRNAs from a whitespace-separated file.
 * Dispose of this with tRNAsFreeList(). */
{
struct tRNAs *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[12];

while (lineFileRow(lf, row))
    {
    el = tRNAsLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct tRNAs *tRNAsLoadAllByChar(char *fileName, char chopper) 
/* Load all tRNAs from a chopper separated file.
 * Dispose of this with tRNAsFreeList(). */
{
struct tRNAs *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[12];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = tRNAsLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct tRNAs *tRNAsCommaIn(char **pS, struct tRNAs *ret)
/* Create a tRNAs out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new tRNAs */
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
ret->aa = sqlStringComma(&s);
ret->ac = sqlStringComma(&s);
ret->intron = sqlStringComma(&s);
ret->trnaScore = sqlFloatComma(&s);
ret->genomeUrl = sqlStringComma(&s);
ret->trnaUrl = sqlStringComma(&s);
*pS = s;
return ret;
}

void tRNAsFree(struct tRNAs **pEl)
/* Free a single dynamically allocated tRNAs such as created
 * with tRNAsLoad(). */
{
struct tRNAs *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->aa);
freeMem(el->ac);
freeMem(el->intron);
freeMem(el->genomeUrl);
freeMem(el->trnaUrl);
freez(pEl);
}

void tRNAsFreeList(struct tRNAs **pList)
/* Free a list of dynamically allocated tRNAs's */
{
struct tRNAs *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    tRNAsFree(&el);
    }
*pList = NULL;
}

void tRNAsOutput(struct tRNAs *el, FILE *f, char sep, char lastSep) 
/* Print out tRNAs.  Separate fields with sep. Follow last field with lastSep. */
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
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->aa);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ac);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->intron);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%g", el->trnaScore);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->genomeUrl);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->trnaUrl);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

