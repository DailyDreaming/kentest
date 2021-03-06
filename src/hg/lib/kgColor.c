/* kgColor.c was originally generated by the autoSql program, which also 
 * generated kgColor.h and kgColor.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "kgColor.h"


void kgColorStaticLoad(char **row, struct kgColor *ret)
/* Load a row from kgColor table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->kgID = row[0];
ret->r = sqlUnsigned(row[1]);
ret->g = sqlUnsigned(row[2]);
ret->b = sqlUnsigned(row[3]);
}

struct kgColor *kgColorLoad(char **row)
/* Load a kgColor from row fetched with select * from kgColor
 * from database.  Dispose of this with kgColorFree(). */
{
struct kgColor *ret;

AllocVar(ret);
ret->kgID = cloneString(row[0]);
ret->r = sqlUnsigned(row[1]);
ret->g = sqlUnsigned(row[2]);
ret->b = sqlUnsigned(row[3]);
return ret;
}

struct kgColor *kgColorLoadAll(char *fileName) 
/* Load all kgColor from a whitespace-separated file.
 * Dispose of this with kgColorFreeList(). */
{
struct kgColor *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = kgColorLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct kgColor *kgColorLoadAllByChar(char *fileName, char chopper) 
/* Load all kgColor from a chopper separated file.
 * Dispose of this with kgColorFreeList(). */
{
struct kgColor *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = kgColorLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct kgColor *kgColorCommaIn(char **pS, struct kgColor *ret)
/* Create a kgColor out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new kgColor */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->kgID = sqlStringComma(&s);
ret->r = sqlUnsignedComma(&s);
ret->g = sqlUnsignedComma(&s);
ret->b = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void kgColorFree(struct kgColor **pEl)
/* Free a single dynamically allocated kgColor such as created
 * with kgColorLoad(). */
{
struct kgColor *el;

if ((el = *pEl) == NULL) return;
freeMem(el->kgID);
freez(pEl);
}

void kgColorFreeList(struct kgColor **pList)
/* Free a list of dynamically allocated kgColor's */
{
struct kgColor *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    kgColorFree(&el);
    }
*pList = NULL;
}

void kgColorOutput(struct kgColor *el, FILE *f, char sep, char lastSep) 
/* Print out kgColor.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->kgID);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->r);
fputc(sep,f);
fprintf(f, "%u", el->g);
fputc(sep,f);
fprintf(f, "%u", el->b);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

