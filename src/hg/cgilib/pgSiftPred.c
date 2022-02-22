/* pgSiftPred.c was originally generated by the autoSql program, which also 
 * generated pgSiftPred.h and pgSiftPred.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "hdb.h"
#include "pgSiftPred.h"


void pgSiftPredStaticLoadWithNull(char **row, struct pgSiftPred *ret)
/* Load a row from pgSiftPred table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
if (row[1] != NULL)
    {
    ret->chromStart = needMem(sizeof(*(ret->chromStart)));
    *(ret->chromStart) = sqlUnsigned(row[1]);
    }
else
    {
    ret->chromStart = NULL;
    }
if (row[2] != NULL)
    {
    ret->chromEnd = needMem(sizeof(*(ret->chromEnd)));
    *(ret->chromEnd) = sqlUnsigned(row[2]);
    }
else
    {
    ret->chromEnd = NULL;
    }
ret->prediction = row[3];
ret->geneId = row[4];
ret->geneName = row[5];
ret->geneDesc = row[6];
ret->protFamDesc = row[7];
ret->omimDisease = row[8];
ret->aveAlleleFreq = row[9];
ret->ceuAlleleFreq = row[10];
}

struct pgSiftPred *pgSiftPredLoadWithNull(char **row)
/* Load a pgSiftPred from row fetched with select * from pgSiftPred
 * from database.  Dispose of this with pgSiftPredFree(). */
{
struct pgSiftPred *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
if (row[1] != NULL)
    {
    ret->chromStart = needMem(sizeof(*(ret->chromStart)));
    *(ret->chromStart) = sqlUnsigned(row[1]);
    }
else
    {
    ret->chromStart = NULL;
    }
if (row[2] != NULL)
    {
    ret->chromEnd = needMem(sizeof(*(ret->chromEnd)));
    *(ret->chromEnd) = sqlUnsigned(row[2]);
    }
else
    {
    ret->chromEnd = NULL;
    }
ret->prediction = cloneString(row[3]);
ret->geneId = cloneString(row[4]);
ret->geneName = cloneString(row[5]);
ret->geneDesc = cloneString(row[6]);
ret->protFamDesc = cloneString(row[7]);
ret->omimDisease = cloneString(row[8]);
ret->aveAlleleFreq = cloneString(row[9]);
ret->ceuAlleleFreq = cloneString(row[10]);
return ret;
}

struct pgSiftPred *pgSiftPredLoadAll(char *fileName) 
/* Load all pgSiftPred from a whitespace-separated file.
 * Dispose of this with pgSiftPredFreeList(). */
{
struct pgSiftPred *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[11];

while (lineFileRow(lf, row))
    {
    el = pgSiftPredLoadWithNull(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct pgSiftPred *pgSiftPredLoadAllByChar(char *fileName, char chopper) 
/* Load all pgSiftPred from a chopper separated file.
 * Dispose of this with pgSiftPredFreeList(). */
{
struct pgSiftPred *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[11];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = pgSiftPredLoadWithNull(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct pgSiftPred *pgSiftPredCommaIn(char **pS, struct pgSiftPred *ret)
/* Create a pgSiftPred out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new pgSiftPred */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = needMem(sizeof(unsigned));
*(ret->chromStart) = sqlUnsignedComma(&s);
ret->chromEnd = needMem(sizeof(unsigned));
*(ret->chromEnd) = sqlUnsignedComma(&s);
ret->prediction = sqlStringComma(&s);
ret->geneId = sqlStringComma(&s);
ret->geneName = sqlStringComma(&s);
ret->geneDesc = sqlStringComma(&s);
ret->protFamDesc = sqlStringComma(&s);
ret->omimDisease = sqlStringComma(&s);
ret->aveAlleleFreq = sqlStringComma(&s);
ret->ceuAlleleFreq = sqlStringComma(&s);
*pS = s;
return ret;
}

void pgSiftPredFree(struct pgSiftPred **pEl)
/* Free a single dynamically allocated pgSiftPred such as created
 * with pgSiftPredLoad(). */
{
struct pgSiftPred *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->prediction);
freeMem(el->geneId);
freeMem(el->geneName);
freeMem(el->geneDesc);
freeMem(el->protFamDesc);
freeMem(el->omimDisease);
freeMem(el->aveAlleleFreq);
freeMem(el->ceuAlleleFreq);
freez(pEl);
}

void pgSiftPredFreeList(struct pgSiftPred **pList)
/* Free a list of dynamically allocated pgSiftPred's */
{
struct pgSiftPred *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    pgSiftPredFree(&el);
    }
*pList = NULL;
}

void pgSiftPredOutput(struct pgSiftPred *el, FILE *f, char sep, char lastSep) 
/* Print out pgSiftPred.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", *(el->chromStart));
fputc(sep,f);
fprintf(f, "%u", *(el->chromEnd));
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->prediction);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneName);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneDesc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->protFamDesc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->omimDisease);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->aveAlleleFreq);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->ceuAlleleFreq);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

void printPgSiftPred (char *db, char *tableName, struct pgSnp *item)
/* print the predictions for an hgc item click for a pgSnp track */
{
struct pgSiftPred *el;
struct sqlResult *sr;
char **row;
char query[512];
struct sqlConnection *conn = hAllocConn(db);

sqlSafef(query, sizeof(query), "select * from %s where chrom = '%s' and chromStart = %d and chromEnd = %d",
    tableName, item->chrom, item->chromStart, item->chromEnd);
sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = pgSiftPredLoadWithNull(row);
    printf("<br><b>SIFT prediction</b>: %s\n", el->prediction);
    printf("<ul>");
    if (el->geneId != NULL && differentString(el->geneId, ""))
        printf("<li>Gene ID: %s</li>\n", el->geneId);
    if (el->geneName != NULL && differentString(el->geneName, ""))
        printf("<li>Gene name: %s</li>\n", el->geneName);
    if (el->geneDesc != NULL && differentString(el->geneDesc, ""))
        printf("<li>Gene description: %s</li>\n", el->geneDesc);
    if (el->protFamDesc != NULL && differentString(el->protFamDesc, ""))
        printf("<li>Protein family description: %s</li>\n", el->protFamDesc);
    if (el->omimDisease != NULL && differentString(el->omimDisease, ""))
        printf("<li>OMIM disease: %s</li>\n", el->omimDisease);
    if (el->aveAlleleFreq != NULL && differentString(el->aveAlleleFreq, ""))
        printf("<li>Average allele frequency: %s</li>\n", el->aveAlleleFreq);
    if (el->ceuAlleleFreq != NULL && differentString(el->ceuAlleleFreq, ""))
	printf("<li>CEU allele frequency: %s</li>\n", el->ceuAlleleFreq);
    printf("</ul>\n");
    }
}
