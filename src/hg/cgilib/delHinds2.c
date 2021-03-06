/* delHinds2.c was originally generated by the autoSql program, which also 
 * generated delHinds2.h and delHinds2.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "delHinds2.h"


void delHinds2StaticLoad(char **row, struct delHinds2 *ret)
/* Load a row from delHinds2 table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->frequency = sqlFloat(row[4]);
}

struct delHinds2 *delHinds2Load(char **row)
/* Load a delHinds2 from row fetched with select * from delHinds2
 * from database.  Dispose of this with delHinds2Free(). */
{
struct delHinds2 *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->frequency = sqlFloat(row[4]);
return ret;
}

struct delHinds2 *delHinds2LoadAll(char *fileName) 
/* Load all delHinds2 from a whitespace-separated file.
 * Dispose of this with delHinds2FreeList(). */
{
struct delHinds2 *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = delHinds2Load(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct delHinds2 *delHinds2LoadAllByChar(char *fileName, char chopper) 
/* Load all delHinds2 from a chopper separated file.
 * Dispose of this with delHinds2FreeList(). */
{
struct delHinds2 *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = delHinds2Load(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct delHinds2 *delHinds2CommaIn(char **pS, struct delHinds2 *ret)
/* Create a delHinds2 out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new delHinds2 */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->frequency = sqlFloatComma(&s);
*pS = s;
return ret;
}

void delHinds2Free(struct delHinds2 **pEl)
/* Free a single dynamically allocated delHinds2 such as created
 * with delHinds2Load(). */
{
struct delHinds2 *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freez(pEl);
}

void delHinds2FreeList(struct delHinds2 **pList)
/* Free a list of dynamically allocated delHinds2's */
{
struct delHinds2 *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    delHinds2Free(&el);
    }
*pList = NULL;
}

void delHinds2Output(struct delHinds2 *el, FILE *f, char sep, char lastSep) 
/* Print out delHinds2.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%g", el->frequency);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

