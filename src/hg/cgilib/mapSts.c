/* mapSts.c was originally generated by the autoSql program, which also 
 * generated mapSts.h and mapSts.sql.  This module links the database and the RAM 
 * representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "jksql.h"
#include "mapSts.h"


void mapStsStaticLoad(char **row, struct mapSts *ret)
/* Load a row from mapSts table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->score = sqlUnsigned(row[4]);
ret->identNo = sqlUnsigned(row[5]);
ret->rhChrom = row[6];
ret->distance = atof(row[7]);
ret->ctgAcc = row[8];
ret->otherAcc = row[9];
}

struct mapSts *mapStsLoad(char **row)
/* Load a mapSts from row fetched with select * from mapSts
 * from database.  Dispose of this with mapStsFree(). */
{
struct mapSts *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->score = sqlUnsigned(row[4]);
ret->identNo = sqlUnsigned(row[5]);
ret->rhChrom = cloneString(row[6]);
ret->distance = atof(row[7]);
ret->ctgAcc = cloneString(row[8]);
ret->otherAcc = cloneString(row[9]);
return ret;
}

struct mapSts *mapStsCommaIn(char **pS, struct mapSts *ret)
/* Create a mapSts out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new mapSts */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
ret->identNo = sqlUnsignedComma(&s);
ret->rhChrom = sqlStringComma(&s);
ret->distance = sqlSignedComma(&s);
ret->ctgAcc = sqlStringComma(&s);
ret->otherAcc = sqlStringComma(&s);
*pS = s;
return ret;
}

void mapStsFree(struct mapSts **pEl)
/* Free a single dynamically allocated mapSts such as created
 * with mapStsLoad(). */
{
struct mapSts *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->rhChrom);
freeMem(el->ctgAcc);
freeMem(el->otherAcc);
freez(pEl);
}

void mapStsFreeList(struct mapSts **pList)
/* Free a list of dynamically allocated mapSts's */
{
struct mapSts *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    mapStsFree(&el);
    }
*pList = NULL;
}

void mapStsOutput(struct mapSts *el, FILE *f, char sep, char lastSep) 
/* Print out mapSts.  Separate fields with sep. Follow last field with lastSep. */
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
fprintf(f, "%u", el->identNo);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->rhChrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%f", el->distance);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ctgAcc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->otherAcc);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

