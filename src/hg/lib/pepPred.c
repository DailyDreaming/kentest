/* pepPred.c was originally generated by the autoSql program, which also 
 * generated pepPred.h and pepPred.sql.  This module links the database and the RAM 
 * representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */

#include "common.h"
#include "jksql.h"
#include "pepPred.h"


void pepPredStaticLoad(char **row, struct pepPred *ret)
/* Load a row from pepPred table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->name = row[0];
ret->seq = row[1];
}

struct pepPred *pepPredLoad(char **row)
/* Load a pepPred from row fetched with select * from pepPred
 * from database.  Dispose of this with pepPredFree(). */
{
struct pepPred *ret;

AllocVar(ret);
ret->name = cloneString(row[0]);
ret->seq = cloneString(row[1]);
return ret;
}

struct pepPred *pepPredCommaIn(char **pS, struct pepPred *ret)
/* Create a pepPred out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new pepPred */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->name = sqlStringComma(&s);
ret->seq = sqlStringComma(&s);
*pS = s;
return ret;
}

void pepPredFree(struct pepPred **pEl)
/* Free a single dynamically allocated pepPred such as created
 * with pepPredLoad(). */
{
struct pepPred *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->seq);
freez(pEl);
}

void pepPredFreeList(struct pepPred **pList)
/* Free a list of dynamically allocated pepPred's */
{
struct pepPred *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    pepPredFree(&el);
    }
*pList = NULL;
}

void pepPredOutput(struct pepPred *el, FILE *f, char sep, char lastSep) 
/* Print out pepPred.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->seq);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

