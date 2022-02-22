/* dbDb.c was originally generated by the autoSql program, which also 
 * generated dbDb.h and dbDb.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2004, 2016 The Regents of the University of California
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "dbDb.h"



char *dbDbCommaSepFieldNames = "name,description,nibPath,organism,defaultPos,active,orderKey,genome,scientificName,htmlPath,hgNearOk,hgPbOk,sourceName,taxId";

void dbDbStaticLoad(char **row, struct dbDb *ret)
/* Load a row from dbDb table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->description = row[1];
ret->nibPath = row[2];
ret->organism = row[3];
ret->defaultPos = row[4];
ret->active = sqlSigned(row[5]);
ret->orderKey = sqlSigned(row[6]);
ret->genome = row[7];
ret->scientificName = row[8];
ret->htmlPath = row[9];
ret->hgNearOk = sqlSigned(row[10]);
ret->hgPbOk = sqlSigned(row[11]);
ret->sourceName = row[12];
ret->taxId = sqlSigned(row[13]);
}

struct dbDb *dbDbLoad(char **row)
/* Load a dbDb from row fetched with select * from dbDb
 * from database.  Dispose of this with dbDbFree(). */
{
struct dbDb *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->description = cloneString(row[1]);
ret->nibPath = cloneString(row[2]);
ret->organism = cloneString(row[3]);
ret->defaultPos = cloneString(row[4]);
ret->active = sqlSigned(row[5]);
ret->orderKey = sqlSigned(row[6]);
ret->genome = cloneString(row[7]);
ret->scientificName = cloneString(row[8]);
ret->htmlPath = cloneString(row[9]);
ret->hgNearOk = sqlSigned(row[10]);
ret->hgPbOk = sqlSigned(row[11]);
ret->sourceName = cloneString(row[12]);
ret->taxId = sqlSigned(row[13]);
return ret;
}

struct dbDb *dbDbLoadAll(char *fileName) 
/* Load all dbDb from a whitespace-separated file.
 * Dispose of this with dbDbFreeList(). */
{
struct dbDb *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[14];

while (lineFileRow(lf, row))
    {
    el = dbDbLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct dbDb *dbDbLoadAllByChar(char *fileName, char chopper) 
/* Load all dbDb from a chopper separated file.
 * Dispose of this with dbDbFreeList(). */
{
struct dbDb *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[14];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = dbDbLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct dbDb *dbDbCommaIn(char **pS, struct dbDb *ret)
/* Create a dbDb out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new dbDb */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->description = sqlStringComma(&s);
ret->nibPath = sqlStringComma(&s);
ret->organism = sqlStringComma(&s);
ret->defaultPos = sqlStringComma(&s);
ret->active = sqlSignedComma(&s);
ret->orderKey = sqlSignedComma(&s);
ret->genome = sqlStringComma(&s);
ret->scientificName = sqlStringComma(&s);
ret->htmlPath = sqlStringComma(&s);
ret->hgNearOk = sqlSignedComma(&s);
ret->hgPbOk = sqlSignedComma(&s);
ret->sourceName = sqlStringComma(&s);
ret->taxId = sqlSignedComma(&s);
*pS = s;
return ret;
}

void dbDbFree(struct dbDb **pEl)
/* Free a single dynamically allocated dbDb such as created
 * with dbDbLoad(). */
{
struct dbDb *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->description);
freeMem(el->nibPath);
freeMem(el->organism);
freeMem(el->defaultPos);
freeMem(el->genome);
freeMem(el->scientificName);
freeMem(el->htmlPath);
freeMem(el->sourceName);
freez(pEl);
}

void dbDbFreeList(struct dbDb **pList)
/* Free a list of dynamically allocated dbDb's */
{
struct dbDb *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    dbDbFree(&el);
    }
*pList = NULL;
}

void dbDbOutput(struct dbDb *el, FILE *f, char sep, char lastSep) 
/* Print out dbDb.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->description);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->nibPath);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->organism);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->defaultPos);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->active);
fputc(sep,f);
fprintf(f, "%d", el->orderKey);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->genome);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->scientificName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->htmlPath);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->hgNearOk);
fputc(sep,f);
fprintf(f, "%d", el->hgPbOk);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->sourceName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->taxId);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

