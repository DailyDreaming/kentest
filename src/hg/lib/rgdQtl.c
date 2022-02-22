/* rgdQtl.c was originally generated by the autoSql program, which also 
 * generated rgdQtl.h and rgdQtl.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "rgdQtl.h"


void rgdQtlStaticLoad(char **row, struct rgdQtl *ret)
/* Load a row from rgdQtl table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->bin = sqlSigned(row[0]);
ret->chrom = row[1];
ret->chromStart = sqlUnsigned(row[2]);
ret->chromEnd = sqlUnsigned(row[3]);
ret->name = row[4];
}

struct rgdQtl *rgdQtlLoad(char **row)
/* Load a rgdQtl from row fetched with select * from rgdQtl
 * from database.  Dispose of this with rgdQtlFree(). */
{
struct rgdQtl *ret;

AllocVar(ret);
ret->bin = sqlSigned(row[0]);
ret->chrom = cloneString(row[1]);
ret->chromStart = sqlUnsigned(row[2]);
ret->chromEnd = sqlUnsigned(row[3]);
ret->name = cloneString(row[4]);
return ret;
}

struct rgdQtl *rgdQtlLoadAll(char *fileName) 
/* Load all rgdQtl from a whitespace-separated file.
 * Dispose of this with rgdQtlFreeList(). */
{
struct rgdQtl *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = rgdQtlLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct rgdQtl *rgdQtlLoadAllByChar(char *fileName, char chopper) 
/* Load all rgdQtl from a chopper separated file.
 * Dispose of this with rgdQtlFreeList(). */
{
struct rgdQtl *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = rgdQtlLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct rgdQtl *rgdQtlCommaIn(char **pS, struct rgdQtl *ret)
/* Create a rgdQtl out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rgdQtl */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->bin = sqlSignedComma(&s);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
*pS = s;
return ret;
}

void rgdQtlFree(struct rgdQtl **pEl)
/* Free a single dynamically allocated rgdQtl such as created
 * with rgdQtlLoad(). */
{
struct rgdQtl *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freez(pEl);
}

void rgdQtlFreeList(struct rgdQtl **pList)
/* Free a list of dynamically allocated rgdQtl's */
{
struct rgdQtl *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    rgdQtlFree(&el);
    }
*pList = NULL;
}

void rgdQtlOutput(struct rgdQtl *el, FILE *f, char sep, char lastSep) 
/* Print out rgdQtl.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%d", el->bin);
fputc(sep,f);
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
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

