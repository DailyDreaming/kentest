/* fbTables.c was originally generated by the autoSql program, which also 
 * generated fbTables.h and fbTables.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "fbTables.h"


void fbGeneStaticLoad(char **row, struct fbGene *ret)
/* Load a row from fbGene table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->geneId = row[0];
ret->geneSym = row[1];
ret->geneName = row[2];
}

struct fbGene *fbGeneLoad(char **row)
/* Load a fbGene from row fetched with select * from fbGene
 * from database.  Dispose of this with fbGeneFree(). */
{
struct fbGene *ret;

AllocVar(ret);
ret->geneId = cloneString(row[0]);
ret->geneSym = cloneString(row[1]);
ret->geneName = cloneString(row[2]);
return ret;
}

struct fbGene *fbGeneLoadAll(char *fileName) 
/* Load all fbGene from a whitespace-separated file.
 * Dispose of this with fbGeneFreeList(). */
{
struct fbGene *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = fbGeneLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbGene *fbGeneLoadAllByChar(char *fileName, char chopper) 
/* Load all fbGene from a chopper separated file.
 * Dispose of this with fbGeneFreeList(). */
{
struct fbGene *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = fbGeneLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbGene *fbGeneCommaIn(char **pS, struct fbGene *ret)
/* Create a fbGene out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbGene */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->geneId = sqlStringComma(&s);
ret->geneSym = sqlStringComma(&s);
ret->geneName = sqlStringComma(&s);
*pS = s;
return ret;
}

void fbGeneFree(struct fbGene **pEl)
/* Free a single dynamically allocated fbGene such as created
 * with fbGeneLoad(). */
{
struct fbGene *el;

if ((el = *pEl) == NULL) return;
freeMem(el->geneId);
freeMem(el->geneSym);
freeMem(el->geneName);
freez(pEl);
}

void fbGeneFreeList(struct fbGene **pList)
/* Free a list of dynamically allocated fbGene's */
{
struct fbGene *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    fbGeneFree(&el);
    }
*pList = NULL;
}

void fbGeneOutput(struct fbGene *el, FILE *f, char sep, char lastSep) 
/* Print out fbGene.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneSym);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneName);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void fbTranscriptStaticLoad(char **row, struct fbTranscript *ret)
/* Load a row from fbTranscript table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->geneId = row[0];
ret->transcriptId = row[1];
}

struct fbTranscript *fbTranscriptLoad(char **row)
/* Load a fbTranscript from row fetched with select * from fbTranscript
 * from database.  Dispose of this with fbTranscriptFree(). */
{
struct fbTranscript *ret;

AllocVar(ret);
ret->geneId = cloneString(row[0]);
ret->transcriptId = cloneString(row[1]);
return ret;
}

struct fbTranscript *fbTranscriptLoadAll(char *fileName) 
/* Load all fbTranscript from a whitespace-separated file.
 * Dispose of this with fbTranscriptFreeList(). */
{
struct fbTranscript *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileRow(lf, row))
    {
    el = fbTranscriptLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbTranscript *fbTranscriptLoadAllByChar(char *fileName, char chopper) 
/* Load all fbTranscript from a chopper separated file.
 * Dispose of this with fbTranscriptFreeList(). */
{
struct fbTranscript *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = fbTranscriptLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbTranscript *fbTranscriptCommaIn(char **pS, struct fbTranscript *ret)
/* Create a fbTranscript out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbTranscript */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->geneId = sqlStringComma(&s);
ret->transcriptId = sqlStringComma(&s);
*pS = s;
return ret;
}

void fbTranscriptFree(struct fbTranscript **pEl)
/* Free a single dynamically allocated fbTranscript such as created
 * with fbTranscriptLoad(). */
{
struct fbTranscript *el;

if ((el = *pEl) == NULL) return;
freeMem(el->geneId);
freeMem(el->transcriptId);
freez(pEl);
}

void fbTranscriptFreeList(struct fbTranscript **pList)
/* Free a list of dynamically allocated fbTranscript's */
{
struct fbTranscript *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    fbTranscriptFree(&el);
    }
*pList = NULL;
}

void fbTranscriptOutput(struct fbTranscript *el, FILE *f, char sep, char lastSep) 
/* Print out fbTranscript.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->transcriptId);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void fbSynonymStaticLoad(char **row, struct fbSynonym *ret)
/* Load a row from fbSynonym table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->geneId = row[0];
ret->name = row[1];
}

struct fbSynonym *fbSynonymLoad(char **row)
/* Load a fbSynonym from row fetched with select * from fbSynonym
 * from database.  Dispose of this with fbSynonymFree(). */
{
struct fbSynonym *ret;

AllocVar(ret);
ret->geneId = cloneString(row[0]);
ret->name = cloneString(row[1]);
return ret;
}

struct fbSynonym *fbSynonymLoadAll(char *fileName) 
/* Load all fbSynonym from a whitespace-separated file.
 * Dispose of this with fbSynonymFreeList(). */
{
struct fbSynonym *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileRow(lf, row))
    {
    el = fbSynonymLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbSynonym *fbSynonymLoadAllByChar(char *fileName, char chopper) 
/* Load all fbSynonym from a chopper separated file.
 * Dispose of this with fbSynonymFreeList(). */
{
struct fbSynonym *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = fbSynonymLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbSynonym *fbSynonymCommaIn(char **pS, struct fbSynonym *ret)
/* Create a fbSynonym out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbSynonym */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->geneId = sqlStringComma(&s);
ret->name = sqlStringComma(&s);
*pS = s;
return ret;
}

void fbSynonymFree(struct fbSynonym **pEl)
/* Free a single dynamically allocated fbSynonym such as created
 * with fbSynonymLoad(). */
{
struct fbSynonym *el;

if ((el = *pEl) == NULL) return;
freeMem(el->geneId);
freeMem(el->name);
freez(pEl);
}

void fbSynonymFreeList(struct fbSynonym **pList)
/* Free a list of dynamically allocated fbSynonym's */
{
struct fbSynonym *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    fbSynonymFree(&el);
    }
*pList = NULL;
}

void fbSynonymOutput(struct fbSynonym *el, FILE *f, char sep, char lastSep) 
/* Print out fbSynonym.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void fbAlleleStaticLoad(char **row, struct fbAllele *ret)
/* Load a row from fbAllele table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlSigned(row[0]);
ret->geneId = row[1];
ret->name = row[2];
}

struct fbAllele *fbAlleleLoad(char **row)
/* Load a fbAllele from row fetched with select * from fbAllele
 * from database.  Dispose of this with fbAlleleFree(). */
{
struct fbAllele *ret;

AllocVar(ret);
ret->id = sqlSigned(row[0]);
ret->geneId = cloneString(row[1]);
ret->name = cloneString(row[2]);
return ret;
}

struct fbAllele *fbAlleleLoadAll(char *fileName) 
/* Load all fbAllele from a whitespace-separated file.
 * Dispose of this with fbAlleleFreeList(). */
{
struct fbAllele *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = fbAlleleLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbAllele *fbAlleleLoadAllByChar(char *fileName, char chopper) 
/* Load all fbAllele from a chopper separated file.
 * Dispose of this with fbAlleleFreeList(). */
{
struct fbAllele *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = fbAlleleLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbAllele *fbAlleleCommaIn(char **pS, struct fbAllele *ret)
/* Create a fbAllele out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbAllele */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlSignedComma(&s);
ret->geneId = sqlStringComma(&s);
ret->name = sqlStringComma(&s);
*pS = s;
return ret;
}

void fbAlleleFree(struct fbAllele **pEl)
/* Free a single dynamically allocated fbAllele such as created
 * with fbAlleleLoad(). */
{
struct fbAllele *el;

if ((el = *pEl) == NULL) return;
freeMem(el->geneId);
freeMem(el->name);
freez(pEl);
}

void fbAlleleFreeList(struct fbAllele **pList)
/* Free a list of dynamically allocated fbAllele's */
{
struct fbAllele *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    fbAlleleFree(&el);
    }
*pList = NULL;
}

void fbAlleleOutput(struct fbAllele *el, FILE *f, char sep, char lastSep) 
/* Print out fbAllele.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%d", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void fbRefStaticLoad(char **row, struct fbRef *ret)
/* Load a row from fbRef table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlSigned(row[0]);
ret->text = row[1];
}

struct fbRef *fbRefLoad(char **row)
/* Load a fbRef from row fetched with select * from fbRef
 * from database.  Dispose of this with fbRefFree(). */
{
struct fbRef *ret;

AllocVar(ret);
ret->id = sqlSigned(row[0]);
ret->text = cloneString(row[1]);
return ret;
}

struct fbRef *fbRefLoadAll(char *fileName) 
/* Load all fbRef from a whitespace-separated file.
 * Dispose of this with fbRefFreeList(). */
{
struct fbRef *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileRow(lf, row))
    {
    el = fbRefLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbRef *fbRefLoadAllByChar(char *fileName, char chopper) 
/* Load all fbRef from a chopper separated file.
 * Dispose of this with fbRefFreeList(). */
{
struct fbRef *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[2];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = fbRefLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbRef *fbRefCommaIn(char **pS, struct fbRef *ret)
/* Create a fbRef out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbRef */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlSignedComma(&s);
ret->text = sqlStringComma(&s);
*pS = s;
return ret;
}

void fbRefFree(struct fbRef **pEl)
/* Free a single dynamically allocated fbRef such as created
 * with fbRefLoad(). */
{
struct fbRef *el;

if ((el = *pEl) == NULL) return;
freeMem(el->text);
freez(pEl);
}

void fbRefFreeList(struct fbRef **pList)
/* Free a list of dynamically allocated fbRef's */
{
struct fbRef *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    fbRefFree(&el);
    }
*pList = NULL;
}

void fbRefOutput(struct fbRef *el, FILE *f, char sep, char lastSep) 
/* Print out fbRef.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%d", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->text);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void fbRoleStaticLoad(char **row, struct fbRole *ret)
/* Load a row from fbRole table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->geneId = row[0];
ret->fbAllele = sqlSigned(row[1]);
ret->fbRef = sqlSigned(row[2]);
ret->text = row[3];
}

struct fbRole *fbRoleLoad(char **row)
/* Load a fbRole from row fetched with select * from fbRole
 * from database.  Dispose of this with fbRoleFree(). */
{
struct fbRole *ret;

AllocVar(ret);
ret->geneId = cloneString(row[0]);
ret->fbAllele = sqlSigned(row[1]);
ret->fbRef = sqlSigned(row[2]);
ret->text = cloneString(row[3]);
return ret;
}

struct fbRole *fbRoleLoadAll(char *fileName) 
/* Load all fbRole from a whitespace-separated file.
 * Dispose of this with fbRoleFreeList(). */
{
struct fbRole *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = fbRoleLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbRole *fbRoleLoadAllByChar(char *fileName, char chopper) 
/* Load all fbRole from a chopper separated file.
 * Dispose of this with fbRoleFreeList(). */
{
struct fbRole *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = fbRoleLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbRole *fbRoleCommaIn(char **pS, struct fbRole *ret)
/* Create a fbRole out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbRole */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->geneId = sqlStringComma(&s);
ret->fbAllele = sqlSignedComma(&s);
ret->fbRef = sqlSignedComma(&s);
ret->text = sqlStringComma(&s);
*pS = s;
return ret;
}

void fbRoleFree(struct fbRole **pEl)
/* Free a single dynamically allocated fbRole such as created
 * with fbRoleLoad(). */
{
struct fbRole *el;

if ((el = *pEl) == NULL) return;
freeMem(el->geneId);
freeMem(el->text);
freez(pEl);
}

void fbRoleFreeList(struct fbRole **pList)
/* Free a list of dynamically allocated fbRole's */
{
struct fbRole *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    fbRoleFree(&el);
    }
*pList = NULL;
}

void fbRoleOutput(struct fbRole *el, FILE *f, char sep, char lastSep) 
/* Print out fbRole.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->fbAllele);
fputc(sep,f);
fprintf(f, "%d", el->fbRef);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->text);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void fbPhenotypeStaticLoad(char **row, struct fbPhenotype *ret)
/* Load a row from fbPhenotype table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->geneId = row[0];
ret->fbAllele = sqlSigned(row[1]);
ret->fbRef = sqlSigned(row[2]);
ret->text = row[3];
}

struct fbPhenotype *fbPhenotypeLoad(char **row)
/* Load a fbPhenotype from row fetched with select * from fbPhenotype
 * from database.  Dispose of this with fbPhenotypeFree(). */
{
struct fbPhenotype *ret;

AllocVar(ret);
ret->geneId = cloneString(row[0]);
ret->fbAllele = sqlSigned(row[1]);
ret->fbRef = sqlSigned(row[2]);
ret->text = cloneString(row[3]);
return ret;
}

struct fbPhenotype *fbPhenotypeLoadAll(char *fileName) 
/* Load all fbPhenotype from a whitespace-separated file.
 * Dispose of this with fbPhenotypeFreeList(). */
{
struct fbPhenotype *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = fbPhenotypeLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbPhenotype *fbPhenotypeLoadAllByChar(char *fileName, char chopper) 
/* Load all fbPhenotype from a chopper separated file.
 * Dispose of this with fbPhenotypeFreeList(). */
{
struct fbPhenotype *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = fbPhenotypeLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbPhenotype *fbPhenotypeCommaIn(char **pS, struct fbPhenotype *ret)
/* Create a fbPhenotype out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbPhenotype */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->geneId = sqlStringComma(&s);
ret->fbAllele = sqlSignedComma(&s);
ret->fbRef = sqlSignedComma(&s);
ret->text = sqlStringComma(&s);
*pS = s;
return ret;
}

void fbPhenotypeFree(struct fbPhenotype **pEl)
/* Free a single dynamically allocated fbPhenotype such as created
 * with fbPhenotypeLoad(). */
{
struct fbPhenotype *el;

if ((el = *pEl) == NULL) return;
freeMem(el->geneId);
freeMem(el->text);
freez(pEl);
}

void fbPhenotypeFreeList(struct fbPhenotype **pList)
/* Free a list of dynamically allocated fbPhenotype's */
{
struct fbPhenotype *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    fbPhenotypeFree(&el);
    }
*pList = NULL;
}

void fbPhenotypeOutput(struct fbPhenotype *el, FILE *f, char sep, char lastSep) 
/* Print out fbPhenotype.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%d", el->fbAllele);
fputc(sep,f);
fprintf(f, "%d", el->fbRef);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->text);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void fbGoStaticLoad(char **row, struct fbGo *ret)
/* Load a row from fbGo table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->geneId = row[0];
ret->goId = row[1];
ret->aspect = row[2];
}

struct fbGo *fbGoLoad(char **row)
/* Load a fbGo from row fetched with select * from fbGo
 * from database.  Dispose of this with fbGoFree(). */
{
struct fbGo *ret;

AllocVar(ret);
ret->geneId = cloneString(row[0]);
ret->goId = cloneString(row[1]);
ret->aspect = cloneString(row[2]);
return ret;
}

struct fbGo *fbGoLoadAll(char *fileName) 
/* Load all fbGo from a whitespace-separated file.
 * Dispose of this with fbGoFreeList(). */
{
struct fbGo *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = fbGoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbGo *fbGoLoadAllByChar(char *fileName, char chopper) 
/* Load all fbGo from a chopper separated file.
 * Dispose of this with fbGoFreeList(). */
{
struct fbGo *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = fbGoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct fbGo *fbGoCommaIn(char **pS, struct fbGo *ret)
/* Create a fbGo out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new fbGo */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->geneId = sqlStringComma(&s);
ret->goId = sqlStringComma(&s);
ret->aspect = sqlStringComma(&s);
*pS = s;
return ret;
}

void fbGoFree(struct fbGo **pEl)
/* Free a single dynamically allocated fbGo such as created
 * with fbGoLoad(). */
{
struct fbGo *el;

if ((el = *pEl) == NULL) return;
freeMem(el->geneId);
freeMem(el->goId);
freeMem(el->aspect);
freez(pEl);
}

void fbGoFreeList(struct fbGo **pList)
/* Free a list of dynamically allocated fbGo's */
{
struct fbGo *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    fbGoFree(&el);
    }
*pList = NULL;
}

void fbGoOutput(struct fbGo *el, FILE *f, char sep, char lastSep) 
/* Print out fbGo.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->goId);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->aspect);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

