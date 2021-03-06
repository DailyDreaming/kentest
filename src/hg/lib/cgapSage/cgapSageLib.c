/* cgapSageLib.c was originally generated by the autoSql program, which also 
 * generated cgapSageLib.h and cgapSageLib.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2011 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "cgapSage/cgapSageLib.h"


/* definitions for sex column */
static char *values_sex[] = {"male", "female", NULL};
static struct hash *valhash_sex = NULL;

void cgapSageLibStaticLoad(char **row, struct cgapSageLib *ret)
/* Load a row from cgapSageLib table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->libId = sqlUnsigned(row[0]);
ret->oldLibName = row[1];
ret->newLibName = row[2];
ret->totalTags = sqlUnsigned(row[3]);
ret->totalTagsNoLinker = sqlUnsigned(row[4]);
ret->uniqueTags = sqlUnsigned(row[5]);
ret->quality = sqlUnsigned(row[6]);
ret->tissue = row[7];
ret->tissuePrep = row[8];
ret->cellType = row[9];
ret->keywords = row[10];
ret->age = row[11];
ret->sex = sqlSetParse(row[12], values_sex, &valhash_sex);
ret->mutations = row[13];
ret->otherInfo = row[14];
ret->tagEnzyme = row[15];
ret->anchorEnzyme = row[16];
ret->cellSupplier = row[17];
ret->libProducer = row[18];
ret->laboratory = row[19];
ret->refs = row[20];
}

struct cgapSageLib *cgapSageLibLoad(char **row)
/* Load a cgapSageLib from row fetched with select * from cgapSageLib
 * from database.  Dispose of this with cgapSageLibFree(). */
{
struct cgapSageLib *ret;

AllocVar(ret);
ret->libId = sqlUnsigned(row[0]);
ret->oldLibName = cloneString(row[1]);
ret->newLibName = cloneString(row[2]);
ret->totalTags = sqlUnsigned(row[3]);
ret->totalTagsNoLinker = sqlUnsigned(row[4]);
ret->uniqueTags = sqlUnsigned(row[5]);
ret->quality = sqlUnsigned(row[6]);
ret->tissue = cloneString(row[7]);
ret->tissuePrep = cloneString(row[8]);
ret->cellType = cloneString(row[9]);
ret->keywords = cloneString(row[10]);
ret->age = cloneString(row[11]);
ret->sex = sqlSetParse(row[12], values_sex, &valhash_sex);
ret->mutations = cloneString(row[13]);
ret->otherInfo = cloneString(row[14]);
ret->tagEnzyme = cloneString(row[15]);
ret->anchorEnzyme = cloneString(row[16]);
ret->cellSupplier = cloneString(row[17]);
ret->libProducer = cloneString(row[18]);
ret->laboratory = cloneString(row[19]);
ret->refs = cloneString(row[20]);
return ret;
}

struct cgapSageLib *cgapSageLibLoadAll(char *fileName) 
/* Load all cgapSageLib from a whitespace-separated file.
 * Dispose of this with cgapSageLibFreeList(). */
{
struct cgapSageLib *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[21];

while (lineFileRow(lf, row))
    {
    el = cgapSageLibLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct cgapSageLib *cgapSageLibLoadAllByChar(char *fileName, char chopper) 
/* Load all cgapSageLib from a chopper separated file.
 * Dispose of this with cgapSageLibFreeList(). */
{
struct cgapSageLib *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[21];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = cgapSageLibLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct cgapSageLib *cgapSageLibLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all cgapSageLib from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with cgapSageLibFreeList(). */
{
struct cgapSageLib *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = cgapSageLibLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

struct cgapSageLib *cgapSageLibCommaIn(char **pS, struct cgapSageLib *ret)
/* Create a cgapSageLib out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new cgapSageLib */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->libId = sqlUnsignedComma(&s);
ret->oldLibName = sqlStringComma(&s);
ret->newLibName = sqlStringComma(&s);
ret->totalTags = sqlUnsignedComma(&s);
ret->totalTagsNoLinker = sqlUnsignedComma(&s);
ret->uniqueTags = sqlUnsignedComma(&s);
ret->quality = sqlUnsignedComma(&s);
ret->tissue = sqlStringComma(&s);
ret->tissuePrep = sqlStringComma(&s);
ret->cellType = sqlStringComma(&s);
ret->keywords = sqlStringComma(&s);
ret->age = sqlStringComma(&s);
ret->sex = sqlSetComma(&s, values_sex, &valhash_sex);
ret->mutations = sqlStringComma(&s);
ret->otherInfo = sqlStringComma(&s);
ret->tagEnzyme = sqlStringComma(&s);
ret->anchorEnzyme = sqlStringComma(&s);
ret->cellSupplier = sqlStringComma(&s);
ret->libProducer = sqlStringComma(&s);
ret->laboratory = sqlStringComma(&s);
ret->refs = sqlStringComma(&s);
*pS = s;
return ret;
}

void cgapSageLibFree(struct cgapSageLib **pEl)
/* Free a single dynamically allocated cgapSageLib such as created
 * with cgapSageLibLoad(). */
{
struct cgapSageLib *el;

if ((el = *pEl) == NULL) return;
freeMem(el->oldLibName);
freeMem(el->newLibName);
freeMem(el->tissue);
freeMem(el->tissuePrep);
freeMem(el->cellType);
freeMem(el->keywords);
freeMem(el->age);
freeMem(el->mutations);
freeMem(el->otherInfo);
freeMem(el->tagEnzyme);
freeMem(el->anchorEnzyme);
freeMem(el->cellSupplier);
freeMem(el->libProducer);
freeMem(el->laboratory);
freeMem(el->refs);
freez(pEl);
}

void cgapSageLibFreeList(struct cgapSageLib **pList)
/* Free a list of dynamically allocated cgapSageLib's */
{
struct cgapSageLib *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    cgapSageLibFree(&el);
    }
*pList = NULL;
}

void cgapSageLibOutput(struct cgapSageLib *el, FILE *f, char sep, char lastSep) 
/* Print out cgapSageLib.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->libId);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->oldLibName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->newLibName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->totalTags);
fputc(sep,f);
fprintf(f, "%u", el->totalTagsNoLinker);
fputc(sep,f);
fprintf(f, "%u", el->uniqueTags);
fputc(sep,f);
fprintf(f, "%u", el->quality);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->tissue);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->tissuePrep);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->cellType);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->keywords);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->age);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
sqlSetPrint(f, el->sex, values_sex);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->mutations);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->otherInfo);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->tagEnzyme);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->anchorEnzyme);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->cellSupplier);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->libProducer);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->laboratory);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->refs);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

struct hash *getTotTagsHash(struct cgapSageLib *libs)
/* Read in the library file and hash up the total tags. */
{
struct hash *totTagsHash = newHash(9);
struct cgapSageLib *lib;
for (lib = libs; lib != NULL; lib = lib->next)
    {
    char buf[16];
    safef(buf, sizeof(buf), "%d", lib->libId);
    hashAddInt(totTagsHash, buf, (int)lib->totalTags);
    }
return totTagsHash;
}

struct hash *getTotTagsHashFromFile(char *libFile)
/* Load a file then call getTotTagsHash. */
{
struct cgapSageLib *libs = cgapSageLibLoadAll(libFile);
struct hash *libTotHash = getTotTagsHash(libs);
cgapSageLibFreeList(&libs);
return libTotHash;
}

