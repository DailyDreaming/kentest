/* dvXref2.c was originally generated by the autoSql program, which also 
 * generated dvXref2.h and dvXref2.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "dvXref2.h"


void dvXref2StaticLoad(char **row, struct dvXref2 *ret)
/* Load a row from dvXref2 table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->varId = row[0];
ret->extSrc = row[1];
ret->extAcc = row[2];
}

struct dvXref2 *dvXref2Load(char **row)
/* Load a dvXref2 from row fetched with select * from dvXref2
 * from database.  Dispose of this with dvXref2Free(). */
{
struct dvXref2 *ret;

AllocVar(ret);
ret->varId = cloneString(row[0]);
ret->extSrc = cloneString(row[1]);
ret->extAcc = cloneString(row[2]);
return ret;
}

struct dvXref2 *dvXref2LoadAll(char *fileName) 
/* Load all dvXref2 from a whitespace-separated file.
 * Dispose of this with dvXref2FreeList(). */
{
struct dvXref2 *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = dvXref2Load(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct dvXref2 *dvXref2LoadAllByChar(char *fileName, char chopper) 
/* Load all dvXref2 from a chopper separated file.
 * Dispose of this with dvXref2FreeList(). */
{
struct dvXref2 *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = dvXref2Load(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct dvXref2 *dvXref2CommaIn(char **pS, struct dvXref2 *ret)
/* Create a dvXref2 out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new dvXref2 */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->varId = sqlStringComma(&s);
ret->extSrc = sqlStringComma(&s);
ret->extAcc = sqlStringComma(&s);
*pS = s;
return ret;
}

void dvXref2Free(struct dvXref2 **pEl)
/* Free a single dynamically allocated dvXref2 such as created
 * with dvXref2Load(). */
{
struct dvXref2 *el;

if ((el = *pEl) == NULL) return;
freeMem(el->varId);
freeMem(el->extSrc);
freeMem(el->extAcc);
freez(pEl);
}

void dvXref2FreeList(struct dvXref2 **pList)
/* Free a list of dynamically allocated dvXref2's */
{
struct dvXref2 *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    dvXref2Free(&el);
    }
*pList = NULL;
}

void dvXref2Output(struct dvXref2 *el, FILE *f, char sep, char lastSep) 
/* Print out dvXref2.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->varId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->extSrc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->extAcc);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

