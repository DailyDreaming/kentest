/* pbStamp.c was originally generated by the autoSql program, which also 
 * generated pbStamp.h and pbStamp.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "pbStamp.h"


void pbStampStaticLoad(char **row, struct pbStamp *ret)
/* Load a row from pbStamp table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

strcpy(ret->stampName, row[0]);
strcpy(ret->stampTable, row[1]);
strcpy(ret->stampTitle, row[2]);
ret->len = sqlSigned(row[3]);
ret->xmin = atof(row[4]);
ret->xmax = atof(row[5]);
ret->ymin = atof(row[6]);
ret->ymax = atof(row[7]);
ret->stampDesc = row[8];
}

struct pbStamp *pbStampLoad(char **row)
/* Load a pbStamp from row fetched with select * from pbStamp
 * from database.  Dispose of this with pbStampFree(). */
{
struct pbStamp *ret;

AllocVar(ret);
strcpy(ret->stampName, row[0]);
strcpy(ret->stampTable, row[1]);
strcpy(ret->stampTitle, row[2]);
ret->len = sqlSigned(row[3]);
ret->xmin = atof(row[4]);
ret->xmax = atof(row[5]);
ret->ymin = atof(row[6]);
ret->ymax = atof(row[7]);
ret->stampDesc = cloneString(row[8]);
return ret;
}

struct pbStamp *pbStampLoadAll(char *fileName) 
/* Load all pbStamp from a whitespace-separated file.
 * Dispose of this with pbStampFreeList(). */
{
struct pbStamp *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileRow(lf, row))
    {
    el = pbStampLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct pbStamp *pbStampLoadAllByChar(char *fileName, char chopper) 
/* Load all pbStamp from a chopper separated file.
 * Dispose of this with pbStampFreeList(). */
{
struct pbStamp *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[9];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = pbStampLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct pbStamp *pbStampCommaIn(char **pS, struct pbStamp *ret)
/* Create a pbStamp out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new pbStamp */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
sqlFixedStringComma(&s, ret->stampName, sizeof(ret->stampName));
sqlFixedStringComma(&s, ret->stampTable, sizeof(ret->stampTable));
sqlFixedStringComma(&s, ret->stampTitle, sizeof(ret->stampTitle));
ret->len = sqlSignedComma(&s);
ret->xmin = sqlFloatComma(&s);
ret->xmax = sqlFloatComma(&s);
ret->ymin = sqlFloatComma(&s);
ret->ymax = sqlFloatComma(&s);
ret->stampDesc = sqlStringComma(&s);
*pS = s;
return ret;
}

void pbStampFree(struct pbStamp **pEl)
/* Free a single dynamically allocated pbStamp such as created
 * with pbStampLoad(). */
{
struct pbStamp *el;

if ((el = *pEl) == NULL) return;
freeMem(el->stampDesc);
freez(pEl);
}

void pbStampFreeList(struct pbStamp **pList)
/* Free a list of dynamically allocated pbStamp's */
{
struct pbStamp *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    pbStampFree(&el);
    }
*pList = NULL;
}

void pbStampOutput(struct pbStamp *el, FILE *f, char sep, char lastSep) 
/* Print out pbStamp.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->stampName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->stampTable);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->stampTitle);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->len);
fputc(sep,f);
fprintf(f, "%f", el->xmin);
fputc(sep,f);
fprintf(f, "%f", el->xmax);
fputc(sep,f);
fprintf(f, "%f", el->ymin);
fputc(sep,f);
fprintf(f, "%f", el->ymax);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->stampDesc);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

