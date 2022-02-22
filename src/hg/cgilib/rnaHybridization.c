/* rnaHybridization.c was originally generated by the autoSql program, which also 
 * generated rnaHybridization.h and rnaHybridization.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "rnaHybridization.h"


void rnaHybridizationStaticLoad(char **row, struct rnaHybridization *ret)
/* Load a row from rnaHybridization table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->dummy = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->chromTarget = row[6];
ret->chromStartTarget = sqlUnsigned(row[7]);
ret->chromEndTarget = sqlUnsigned(row[8]);
safecpy(ret->strandTarget, sizeof(ret->strandTarget), row[9]);
ret->refSeqTarget = row[10];
ret->aorfTarget = row[11];
ret->igenicsTarget = row[12];
ret->trnaTarget = row[13];
ret->JGITarget = row[14];
ret->patternSeq = row[15];
ret->targetSeq = row[16];
ret->gcContent = sqlFloat(row[17]);
ret->matchLength = sqlUnsigned(row[18]);
ret->targetAnnotation = sqlUnsigned(row[19]);
}

struct rnaHybridization *rnaHybridizationLoad(char **row)
/* Load a rnaHybridization from row fetched with select * from rnaHybridization
 * from database.  Dispose of this with rnaHybridizationFree(). */
{
struct rnaHybridization *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->dummy = sqlUnsigned(row[4]);
safecpy(ret->strand, sizeof(ret->strand), row[5]);
ret->chromTarget = cloneString(row[6]);
ret->chromStartTarget = sqlUnsigned(row[7]);
ret->chromEndTarget = sqlUnsigned(row[8]);
safecpy(ret->strandTarget, sizeof(ret->strandTarget), row[9]);
ret->refSeqTarget = cloneString(row[10]);
ret->aorfTarget = cloneString(row[11]);
ret->igenicsTarget = cloneString(row[12]);
ret->trnaTarget = cloneString(row[13]);
ret->JGITarget = cloneString(row[14]);
ret->patternSeq = cloneString(row[15]);
ret->targetSeq = cloneString(row[16]);
ret->gcContent = sqlFloat(row[17]);
ret->matchLength = sqlUnsigned(row[18]);
ret->targetAnnotation = sqlUnsigned(row[19]);
return ret;
}

struct rnaHybridization *rnaHybridizationLoadAll(char *fileName) 
/* Load all rnaHybridization from a whitespace-separated file.
 * Dispose of this with rnaHybridizationFreeList(). */
{
struct rnaHybridization *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[20];

while (lineFileRow(lf, row))
    {
    el = rnaHybridizationLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct rnaHybridization *rnaHybridizationLoadAllByChar(char *fileName, char chopper) 
/* Load all rnaHybridization from a chopper separated file.
 * Dispose of this with rnaHybridizationFreeList(). */
{
struct rnaHybridization *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[20];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = rnaHybridizationLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct rnaHybridization *rnaHybridizationLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all rnaHybridization from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with rnaHybridizationFreeList(). */
{
struct rnaHybridization *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = rnaHybridizationLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void rnaHybridizationSaveToDb(struct sqlConnection *conn, struct rnaHybridization *el, char *tableName, int updateSize)
/* Save rnaHybridization as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( '%s',%u,%u,'%s',%u,'%s','%s',%u,%u,'%s','%s','%s','%s','%s','%s','%s','%s',%g,%u,%u)", 
	tableName,  el->chrom,  el->chromStart,  el->chromEnd,  el->name,  el->dummy,  el->strand,  el->chromTarget,  el->chromStartTarget,  el->chromEndTarget,  el->strandTarget,  el->refSeqTarget,  el->aorfTarget,  el->igenicsTarget,  el->trnaTarget,  el->JGITarget,  el->patternSeq,  el->targetSeq,  el->gcContent,  el->matchLength,  el->targetAnnotation);
sqlUpdate(conn, update->string);
freeDyString(&update);
}


struct rnaHybridization *rnaHybridizationCommaIn(char **pS, struct rnaHybridization *ret)
/* Create a rnaHybridization out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new rnaHybridization */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->dummy = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->chromTarget = sqlStringComma(&s);
ret->chromStartTarget = sqlUnsignedComma(&s);
ret->chromEndTarget = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strandTarget, sizeof(ret->strandTarget));
ret->refSeqTarget = sqlStringComma(&s);
ret->aorfTarget = sqlStringComma(&s);
ret->igenicsTarget = sqlStringComma(&s);
ret->trnaTarget = sqlStringComma(&s);
ret->JGITarget = sqlStringComma(&s);
ret->patternSeq = sqlStringComma(&s);
ret->targetSeq = sqlStringComma(&s);
ret->gcContent = sqlFloatComma(&s);
ret->matchLength = sqlUnsignedComma(&s);
ret->targetAnnotation = sqlUnsignedComma(&s);
*pS = s;
return ret;
}

void rnaHybridizationFree(struct rnaHybridization **pEl)
/* Free a single dynamically allocated rnaHybridization such as created
 * with rnaHybridizationLoad(). */
{
struct rnaHybridization *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->chromTarget);
freeMem(el->refSeqTarget);
freeMem(el->aorfTarget);
freeMem(el->igenicsTarget);
freeMem(el->trnaTarget);
freeMem(el->JGITarget);
freeMem(el->patternSeq);
freeMem(el->targetSeq);
freez(pEl);
}

void rnaHybridizationFreeList(struct rnaHybridization **pList)
/* Free a list of dynamically allocated rnaHybridization's */
{
struct rnaHybridization *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    rnaHybridizationFree(&el);
    }
*pList = NULL;
}

void rnaHybridizationOutput(struct rnaHybridization *el, FILE *f, char sep, char lastSep) 
/* Print out rnaHybridization.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%u", el->dummy);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chromTarget);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStartTarget);
fputc(sep,f);
fprintf(f, "%u", el->chromEndTarget);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strandTarget);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->refSeqTarget);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->aorfTarget);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->igenicsTarget);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->trnaTarget);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->JGITarget);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->patternSeq);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->targetSeq);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%g", el->gcContent);
fputc(sep,f);
fprintf(f, "%u", el->matchLength);
fputc(sep,f);
fprintf(f, "%u", el->targetAnnotation);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

