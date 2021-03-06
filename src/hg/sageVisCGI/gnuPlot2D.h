/* gnuPlot2D.h was originally generated by the autoSql program, which also 
 * generated gnuPlot2D.c and gnuPlot2D.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2005 The Regents of the University of California 
 * See kent/LICENSE or http://genome.ucsc.edu/license/ for licensing information. */



/**
  \page gnuPlot2D.doxp gnuPlot2D Doc page
  \section gnuPlot2D gnuPlot2D module
   <p>gnuPlot2D - a set of functions and associated datatypes to make
   using gnuplot easier.
   The package is dependent on the gnuplot_i library for gnuplot 
    written by N.Devillard <nDevil@eso.org>. N.Devillard's web site
   is <a href ="http://www.eso.org/~ndevilla/gnuplot/">here.</a>

   \sa gnuPlot2D.h
*/ 



#ifndef GNUPLOT2D_H
#define GNUPLOT2D_H

#include "gnuplot_i.h"
#include "common.h"

struct graphPoint2D
/* Generic pair of coordinates to use for graphing data */
    {
    struct graphPoint2D *next;  /* Next in singly linked list. */
    float x;	/* Value on the x-axis */
    float y;	/* Value on the y-axis */
    float xDelta;	/* Standard deviation on x-axis */
    float yDelta;	/* Standard deviation on y-axis */
    char *name;	/* name and/or id of data point for machines */
    char *hName;	/* name for humans of data point */
    char *groupName;	/* Super set that this data point belongs to */
    char *other;	/* other associated information, i.e. url */
    };

void graphPoint2DStaticLoad(char **row, struct graphPoint2D *ret);
/* Load a row from graphPoint2D table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct graphPoint2D *graphPoint2DLoad(char **row);
/* Load a graphPoint2D from row fetched with select * from graphPoint2D
 * from database.  Dispose of this with graphPoint2DFree(). */

struct graphPoint2D *graphPoint2DLoadAll(char *fileName);
/* Load all graphPoint2D from a tab-separated file.
 * Dispose of this with graphPoint2DFreeList(). */

struct graphPoint2D *graphPoint2DCommaIn(char **pS, struct graphPoint2D *ret);
/* Create a graphPoint2D out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new graphPoint2D */

void graphPoint2DFree(struct graphPoint2D **pEl);
/* Free a single dynamically allocated graphPoint2D such as created
 * with graphPoint2DLoad(). */

void graphPoint2DFreeList(struct graphPoint2D **pList);
/* Free a list of dynamically allocated graphPoint2D's */

void graphPoint2DOutput(struct graphPoint2D *el, FILE *f, char sep, char lastSep);
/* Print out graphPoint2D.  Separate fields with sep. Follow last field with lastSep. */

#define graphPoint2DTabOut(el,f) graphPoint2DOutput(el,f,'\t','\n');
/* Print out graphPoint2D as a line in a tab-separated file. */

#define graphPoint2DCommaOut(el,f) graphPoint2DOutput(el,f,',',',');
/* Print out graphPoint2D as a comma separated list including final comma. */

struct gnuPlot2D
/* Strutures and routines to ease creating plots from c using gnuPlot. */
{
    struct gnuPlot2D *next;  /* Next in singly linked list. */
    int numPlots;	/* Number of plots, i.e. different lines. */
    int numFiles;	/* Number of temp files opened. */
    int maxPlots;
    int maxFunctions;
    struct graphPoint2D **gpList;	/* List of graphPoint2Ds. */
    char *fileName;	/* Name of file with plot in it. */
    char *directory;	/* Name of directory to place temporary plots and files in. */
    char **tempFiles;	/* Names of temporary Files created. */
    char *imageFormat;	/* file format of plot to be created, i.e. eps, png, jpeg. */
    char **styles;	/* Style for each plot, i.e. color, linespoints, etc. */
    char ** functions;	/* are there functions to plot? 1 if true, 0 otherwise */
    int numFunctions;	/* Number of functions to plot if there are some */
    char **functionStyles;	/* Styles for the functions */
    int grid;	/* Set a grid on the plot if 1, no grid otherwise. */
    int xtics;	/* Set the xtics 1 if xtics, 0 otherwise. */
    int ytics;	/* set the ytics 1 if ytics, 0 otherwise. */
    char *xTicFormat;	/* Set the format of the xtics. */
    char *yTicFormat;	/* Set the format of the ytics. */
    int xErrorBars;	/* If 1 error bars on x axis, otherwise not */
    int yErrorBars;	/* If 1 error bars on y axis, otherwise not */
    int xDataLabels;	/* Label xtics with data names if 1, otherwise let gnuplot do it. */
    int yDataLabels;	/* Label ytics with data names if 1, otherwise let gnuplot do it. */
    int xlogAxis;	/* Make x-axis log scaled if 1, otherwise normal scaling. */
    int ylogAxis;	/* Make y-axis log scaled if 1, otherwise normal scaling. */
    float yMin;	/* minimum value on y axis. */
    float yMax;	/* maximum value on y axis. */
    float xMin;	/* minimum value on x axis. */
    float xMax;	/* maximum value on x axis. */
    char *title;	/* Title of the plot. */
    char *xlabel;	/* Label on x-axis. */
    char *ylabel;	/* Label on y-axis. */
    char *legend;	/* Legend instructions. */
    char *other;	/* Other things to be written to plot. */
    };

struct gnuPlot2D *gnuPlot2DLoad(char **row);
/* Load a gnuPlot2D from row fetched with select * from gnuPlot2D
 * from database.  Dispose of this with gnuPlot2DFree(). */

struct gnuPlot2D *gnuPlot2DLoadAll(char *fileName);
/* Load all gnuPlot2D from a tab-separated file.
 * Dispose of this with gnuPlot2DFreeList(). */

struct gnuPlot2D *gnuPlot2DCommaIn(char **pS, struct gnuPlot2D *ret);
/* Create a gnuPlot2D out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gnuPlot2D */

void gnuPlot2DFree(struct gnuPlot2D **pEl);
/* Free a single dynamically allocated gnuPlot2D such as created
 * with gnuPlot2DLoad(). */

void gnuPlot2DFreeList(struct gnuPlot2D **pList);
/* Free a list of dynamically allocated gnuPlot2D's */

void gnuPlot2DOutput(struct gnuPlot2D *el, FILE *f, char sep, char lastSep);
/* Print out gnuPlot2D.  Separate fields with sep. Follow last field with lastSep. */

#define gnuPlot2DTabOut(el,f) gnuPlot2DOutput(el,f,'\t','\n');
/* Print out gnuPlot2D as a line in a tab-separated file. */

#define gnuPlot2DCommaOut(el,f) gnuPlot2DOutput(el,f,',',',');
/* Print out gnuPlot2D as a comma separated list including final comma. */

/* --------------------- End AutoSql Generated Code ----------------- */


/**
 * Creates a gnuPlot2D struct with default settings,
 *  still needs data.
 *  @return gnuPlot2D initialized struct
*/
struct gnuPlot2D *createGnuPlot2D();

/**
 *   gptGenerateCmd - takes a gnuPlot2D struct and generates a string
 *  containg output to generate plot in gnuplot according to the
 *  information contained. Will errAbort if problems are
 *  encountered. On sucess returns the absolute pathname of the plot or
 *  NULL if plot is displayed in xwindow.  
 *  @param struct gnuPlot2D -contains data to plot 
 *  @return char *cmd - sequence of instructions to create desired plot
 *  remember to free this.
 */
char *gptGenerateCmd(struct gnuPlot2D *pd);

/**
 * gptQuickPlotXY - quick and dirty way to generate an xy plot
 */
void gptQuickPlotXY(char *title, char *fileName, 
		    char *fileFormat, double *x, double *y, int numPoints);

/**
 * gptPlotFromCmd - this function takes a string generated from gptGenerateCmd() 
 * and generates the actual plot described by it.
 * @param string - cmd, a string containing the commands necessary to
 * generated a gnuplot. Basically a memory version of the batch file
 * which could be used to generate gnuplot from command line
 */
void gptPlotFromCmd(char *cmd);

/**
 * gptAddGraphPointList - adds a list of graphPoint2Ds as another
 * thing to plot when gnuplot commands are generated.
 * @param struct gnuPlot2D - the struct to add graphPoint2D to.
 * @param struct graphPoint2D - list of data to add
 * @param char * style to plot the new data with if NULL, default to linespoints
 */
void gptAddGraphPointList(struct gnuPlot2D *gPlot, 
			  struct graphPoint2D *gpList,
			  char *newStyle);

/**
 * gptRemoveTempFiles - removes temp files created. 
 */
void gptRemoveTempFiles(struct gnuPlot2D *gPlot);


#endif /* GNUPLOT2D_H */

