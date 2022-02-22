/* pslSelfJobs - make condor submission file to do
 * self jobs. */
#include "common.h"
#include "portable.h"
#include "obscure.h"
#include "linefile.h"


void usage()
/* Print usage instructions and exit. */
{
errAbort(
   "pslSelfJobs - make Condor submission file to do\n"
   "psLayout jobs within bacs in a contig.\n"
   "usage:\n"
   "   pslSelfJobs ooDir output.con finish.csh logDir");
}

void makeSelfJob(FILE *out, char *ooDir, char *chrom, 
	char *contig, char *logDir)
/* Add one self job to Condor output file. */
{
fprintf(out, "initialdir\t= %s/%s/%s\n", ooDir, chrom, contig);
fprintf(out, 
	"arguments\t= geno.lst geno.lst asm /var/tmp/hg/h/10.ooc self.psl\n");
fprintf(out, "log\t= %s/%s_%s.log\n", logDir, chrom, contig);
fprintf(out, "output\t= %s/%s_%s.out\n", logDir, chrom, contig);
fprintf(out, "error\t= %s/%s_%s.err\n", logDir, chrom, contig);
fprintf(out, "queue 1\n");
fprintf(out, "\n");
}

int countLines(char *fileName)
/* Count number of lines in file. */
{
struct lineFile *lf = lineFileOpen(fileName, TRUE);
int lineCount = 0, lineSize;
char *line;
while (lineFileNext(lf, &line, &lineSize))
    ++lineCount;
lineFileClose(&lf);
return lineCount;
}

struct ctgInfo
/* Info on one contig. */
    {
    struct ctgInfo *next;       /* Next in list. */
    char *chrom;                /* Name of chromosme. */
    char *contig;               /* Name of contig. */
    int cloneCount;		/* Number of clones. */
    };

int ctgInfoCmp(const void *va, const void *vb)
/* Compare two ctgInfo to sort by clone count - most first . */
{
const struct ctgInfo *a = *((struct ctgInfo **)va);
const struct ctgInfo *b = *((struct ctgInfo **)vb);
return b->cloneCount - a->cloneCount;
}

struct ctgInfo *getCtgInfo(char *ooDir, char *chrom, char *contig)
/* Get contig info on dir. */
{
struct ctgInfo *ci;
char fileName[512];
AllocVar(ci);
ci->chrom = chrom;
ci->contig = contig;
sprintf(fileName, "%s/%s/%s/%s", ooDir, chrom, contig, "geno.lst");
ci->cloneCount = countLines(fileName);
return ci;
}

void writeConHead(FILE *out, char *ooDir)
/* Write out header to condor file. */
{
fprintf(out, "# Condor submit file to create self alignments to %s\n", ooDir);
fprintf(out, "# Generated by  pslSelfJobs\n\n");
fprintf(out, "universe\t= vanilla\n");
fprintf(out, "notification\t= error\n");
fprintf(out, "requirements\t= memory > 250\n");
fprintf(out, "executable\t= /cse/guests/kent/bin/i386/psLayout\n");
fprintf(out, "\n");
}

enum {squareSize = 75};	/* "Ideal" job is 75x75 clones. */

void makeCompoundJob(FILE *sh, FILE *con, struct ctgInfo *ci, char *ooDir, char *logDir)
/* Handle a job that needs to be broken up. */
{
char tempDir[512];
char contigDir[512];
char fileName[512];
char *gBuf, **genoAll;
int genoCount;
int segCount = 0;
int endSeg;
int i = 0;
int segSize;
char *tdName = "tmpSlf";

sprintf(contigDir, "%s/%s/%s", ooDir, ci->chrom, ci->contig);
sprintf(fileName, "%s/%s", contigDir, "geno.lst");
readAllWords(fileName, &genoAll, &genoCount, &gBuf);
sprintf(tempDir, "%s/%s", contigDir, tdName);
mkdir(tempDir, 0777);

segSize = (squareSize*squareSize)/genoCount + 10;
if (segSize >= (genoCount+1)/2)
    segSize = (genoCount+1)/2;

while (i < genoCount)
    {
    FILE *f;
    ++segCount;

    /* Create genoN.lst file for this segment. */
    sprintf(fileName, "%s/geno%02d.lst", tempDir, segCount);
    f = mustOpen(fileName, "w");
    endSeg = i+segSize;
    if (endSeg > genoCount) 
    	endSeg = genoCount;
    for (;i<endSeg; ++i)
	fprintf(f, "%s\n", genoAll[i]);
    fclose(f);

    /* Write out condor submission bits. */
    fprintf(con, "initialdir\t= %s\n", contigDir);
    fprintf(con, "log\t= %s/%s_%s_%02d.log\n", logDir, ci->chrom, ci->contig, segCount);
    fprintf(con, "output\t= %s/%s_%s_%02d.out\n", logDir, ci->chrom, ci->contig, segCount);
    fprintf(con, "error\t= %s/%s_%s_%02d.err\n", logDir, ci->chrom, ci->contig, segCount);
    fprintf(con, "arguments\t= %s/geno%02d.lst geno.lst genomic /var/tmp/hg/h/10.ooc %s/self%02d.psl\n",
    	tdName, segCount, tdName, segCount);
    fprintf(con, "queue 1\n");
    fprintf(con, "\n");
    }

/* Write out finish up shell script */
fprintf(sh, "echo finishing %s\n", tempDir);
fprintf(sh, "pslSort dirs %s/self.psl %s %s\n", contigDir, tempDir, tempDir);
// fprintf(sh, "rm -r %s", tempDir);
fprintf(sh, "\n");

freeMem(gBuf);
freeMem(genoAll);
}


void pslSelfJobs(char *ooDir, char *conFile, char *finishCsh, char *logDir)
/* Scan ooDir and make up a condor file to produce
 * any missing self.psl files. */
{
struct slName *chromDir, *chrom;
struct slName *contigDir, *contig;
char fileName[512];
struct ctgInfo *ciList = NULL, *ci;
FILE *out = mustOpen(conFile, "w");
FILE *finish = mustOpen(finishCsh, "w");
char *chromName;
int len;

if (mkdir(logDir, 0775) < 0)
    {
    if (errno != EEXIST)
	{
	perror("");
	errAbort("Couldn't make log directory %s", logDir);
	}
    }

writeConHead(out, ooDir);
fprintf(out, 
	"arguments\t= geno.lst geno.lst genomic /var/tmp/hg/h/10.ooc self.psl");
fprintf(out, "\n");

chromDir = listDir(ooDir, "*");
for (chrom = chromDir; chrom != NULL; chrom = chrom->next)
    {
    chromName = chrom->name;
    len = strlen(chromName);
    if (len > 2) 
    	continue;
    sprintf(fileName, "%s/%s", ooDir, chromName);
    contigDir = listDir(fileName, "*");
    for (contig = contigDir; contig != NULL; contig = contig->next)
	{
	ci = getCtgInfo(ooDir, chrom->name, contig->name);
	slAddHead(&ciList, ci);
	}
    }

slSort(&ciList, ctgInfoCmp);
for (ci = ciList; ci != NULL; ci = ci->next)
    {
    sprintf(fileName, "%s/%s/%s/geno.lst",
	ooDir, ci->chrom, ci->contig);
    if (fileExists(fileName))
	{
	if (ci->cloneCount <= squareSize)
	    makeSelfJob(out, ooDir, ci->chrom, ci->contig, logDir);
	else
	    makeCompoundJob(finish, out, ci, ooDir, logDir);
	}
    }
fclose(out);
}

int main(int argc, char *argv[])
/* Process command line. */
{
if (argc != 5)
    usage();
pslSelfJobs(argv[1], argv[2], argv[3], argv[4]);
}
