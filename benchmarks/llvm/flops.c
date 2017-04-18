/*--------------------- Start flops.c source code ----------------------*/

/*****************************/
/*          flops.c          */
/* Version 2.0,  18 Dec 1992 */
/*         Al Aburto         */
/*      aburto@nosc.mil      */
/*****************************/

/*
   Flops.c is a 'c' program which attempts to estimate your systems
   floating-point 'MFLOPS' rating for the FADD, FSUB, FMUL, and FDIV
   operations based on specific 'instruction mixes' (discussed below).
   The program provides an estimate of PEAK MFLOPS performance by making
   maximal use of register variables with minimal interaction with main
   memory. The execution loops are all small so that they will fit in
   any cache. Flops.c can be used along with Linpack and the Livermore
   kernels (which exersize memory much more extensively) to gain further
   insight into the limits of system performance. The flops.c execution
   modules also include various percent weightings of FDIV's (from 0% to
   25% FDIV's) so that the range of performance can be obtained when
   using FDIV's. FDIV's, being computationally more intensive than
   FADD's or FMUL's, can impact performance considerably on some systems.
   
   Flops.c consists of 8 independent modules (routines) which, except for
   module 2, conduct numerical integration of various functions. Module
   2, estimates the value of pi based upon the Maclaurin series expansion
   of atan(1). MFLOPS ratings are provided for each module, but the
   programs overall results are summerized by the MFLOPS(1), MFLOPS(2),
   MFLOPS(3), and MFLOPS(4) outputs.

   The MFLOPS(1) result is identical to the result provided by all
   previous versions of flops.c. It is based only upon the results from
   modules 2 and 3. Two problems surfaced in using MFLOPS(1). First, it
   was difficult to completely 'vectorize' the result due to the 
   recurrence of the 's' variable in module 2. This problem is addressed
   in the MFLOPS(2) result which does not use module 2, but maintains
   nearly the same weighting of FDIV's (9.2%) as in MFLOPS(1) (9.6%).
   The second problem with MFLOPS(1) centers around the percentage of
   FDIV's (9.6%) which was viewed as too high for an important class of
   problems. This concern is addressed in the MFLOPS(3) result where NO
   FDIV's are conducted at all. 
   
   The number of floating-point instructions per iteration (loop) is
   given below for each module executed:

   MODULE   FADD   FSUB   FMUL   FDIV   TOTAL  Comment
     1        7      0      6      1      14   7.1%  FDIV's
     2        3      2      1      1       7   difficult to vectorize.
     3        6      2      9      0      17   0.0%  FDIV's
     4        7      0      8      0      15   0.0%  FDIV's
     5       13      0     15      1      29   3.4%  FDIV's
     6       13      0     16      0      29   0.0%  FDIV's
     7        3      3      3      3      12   25.0% FDIV's
     8       13      0     17      0      30   0.0%  FDIV's
   
   A*2+3     21     12     14      5      52   A=5, MFLOPS(1), Same as
	   40.4%  23.1%  26.9%  9.6%          previous versions of the
						flops.c program. Includes
						only Modules 2 and 3, does
						9.6% FDIV's, and is not
						easily vectorizable.
   
   1+3+4     58     14     66     14     152   A=4, MFLOPS(2), New output
   +5+6+    38.2%  9.2%   43.4%  9.2%          does not include Module 2,
   A*7                                         but does 9.2% FDIV's.
   
   1+3+4     62      5     74      5     146   A=0, MFLOPS(3), New output
   +5+6+    42.9%  3.4%   50.7%  3.4%          does not include Module 2,
   7+8                                         but does 3.4% FDIV's.

   3+4+6     39      2     50      0      91   A=0, MFLOPS(4), New output
   +8       42.9%  2.2%   54.9%  0.0%          does not include Module 2,
						and does NO FDIV's.

   NOTE: Various timer routines are included as indicated below. The
	timer routines, with some comments, are attached at the end 
	of the main program.

   NOTE: Please do not remove any of the printouts.

   EXAMPLE COMPILATION:
   UNIX based systems
       cc -DUNIX -O flops.c -o flops
       cc -DUNIX -DROPT flops.c -o flops 
       cc -DUNIX -fast -O4 flops.c -o flops 
       .
       .
       .
     etc.

   Al Aburto
   aburto@nosc.mil
*/

/***************************************************************/
/* Timer options. You MUST uncomment one of the options below  */
/* or compile, for example, with the '-DUNIX' option.          */
/***************************************************************/
/* #define Amiga       */
/* #define UNIX        */
/* #define UNIX_Old    */
/* #define VMS         */
/* #define BORLAND_C   */
/* #define MSC         */
/* #define MAC         */
/* #define IPSC        */
/* #define FORTRAN_SEC */
#define GTODay
/* #define CTimer      */
/* #define UXPM        */
/* #define MAC_TMgr    */
/* #define PARIX       */
/* #define POSIX       */
/* #define WIN32       */
/* #define POSIX1      */
/***********************/

#include <stdio.h>
#include <math.h>
			    /* 'Uncomment' the line below to run   */
			    /* with 'register double' variables    */
			    /* defined, or compile with the        */
			    /* '-DROPT' option. Don't need this if */
			    /* registers used automatically, but   */
			    /* you might want to try it anyway.    */
/* #define ROPT */

double nulltime, TimeArray[3];   /* Variables needed for 'dtime()'.     */
double TLimit;                   /* Threshold to determine Number of    */
				 /* Loops to run. Fixed at 15.0 seconds.*/

double T[36];                    /* Global Array used to hold timing    */
				 /* results and other information.      */

double sa,sb,sc,sd,one,two,three;
double four,five,piref,piprg;
double scale,pierr;

double A0 = 1.0;
double A1 = -0.1666666666671334;
double A2 = 0.833333333809067E-2;
double A3 = 0.198412715551283E-3;
double A4 = 0.27557589750762E-5;
double A5 = 0.2507059876207E-7;
double A6 = 0.164105986683E-9;

double B0 = 1.0;
double B1 = -0.4999999999982;
double B2 = 0.4166666664651E-1;
double B3 = -0.1388888805755E-2;
double B4 = 0.24801428034E-4;
double B5 = -0.2754213324E-6;
double B6 = 0.20189405E-8;

double C0 = 1.0;
double C1 = 0.99999999668;
double C2 = 0.49999995173;
double C3 = 0.16666704243;
double C4 = 0.4166685027E-1;
double C5 = 0.832672635E-2;
double C6 = 0.140836136E-2;
double C7 = 0.17358267E-3;
double C8 = 0.3931683E-4;

double D1 = 0.3999999946405E-1;
double D2 = 0.96E-3;
double D3 = 0.1233153E-5;

double E2 = 0.48E-3;
double E3 = 0.411051E-6;

int dtime();

/*****************************************************/
/* Various timer routines.                           */
/* Al Aburto, aburto@nosc.mil, 18 Feb 1997           */
/*                                                   */
/* dtime(p) outputs the elapsed time seconds in p[1] */
/* from a call of dtime(p) to the next call of       */
/* dtime(p).  Use CAUTION as some of these routines  */
/* will mess up when timing across the hour mark!!!  */
/*                                                   */
/* For timing I use the 'user' time whenever         */
/* possible. Using 'user+sys' time is a separate     */
/* issue.                                            */
/*                                                   */
/* Example Usage:                                    */
/* [Timer options added here]                        */
/* double RunTime, TimeArray[3];                     */
/* main()                                            */
/* {                                                 */
/* dtime(TimeArray);                                 */ 
/* [routine to time]                                 */
/* dtime(TimeArray);                                 */
/* RunTime = TimeArray[1];                           */
/* }                                                 */
/* [Timer code added here]                           */
/*****************************************************/

/******************************/
/* Timer code.                */
/******************************/

/*******************/
/*  Amiga dtime()  */
/*******************/
#ifdef Amiga
#include <ctype.h>
#define HZ 50

dtime(p)
double p[];
{
 double q;

 struct tt {
	long  days;
	long  minutes;
	long  ticks;
 } tt;

 q = p[2];

 DateStamp(&tt);

 p[2] = ( (double)(tt.ticks + (tt.minutes * 60L * 50L)) ) / (double)HZ;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/*****************************************************/
/*  UNIX dtime(). This is the preferred UNIX timer.  */
/*  Provided by: Markku Kolkka, mk59200@cc.tut.fi    */
/*  HP-UX Addition by: Bo Thide', bt@irfu.se         */
/*****************************************************/
#ifdef UNIX
#include <sys/time.h>
#include <sys/resource.h>

#ifdef hpux
#include <sys/syscall.h>
#define getrusage(a,b) syscall(SYS_getrusage,a,b)
#endif

struct rusage rusage;

dtime(p)
double p[];
{
 double q;

 q = p[2];

 getrusage(RUSAGE_SELF,&rusage);

 p[2] = (double)(rusage.ru_utime.tv_sec);
 p[2] = p[2] + (double)(rusage.ru_utime.tv_usec) * 1.0e-06;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/***************************************************/
/*  UNIX_Old dtime(). This is the old UNIX timer.  */
/*  Use only if absolutely necessary as HZ may be  */
/*  ill defined on your system.                    */
/***************************************************/
#ifdef UNIX_Old
#include <sys/types.h>
#include <sys/times.h>
#include <sys/param.h>

#ifndef HZ
#define HZ 60
#endif

struct tms tms;

dtime(p)
double p[];
{
 double q;

 q = p[2];

 times(&tms);

 p[2] = (double)(tms.tms_utime) / (double)HZ;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/*********************************************************/
/*  VMS dtime() for VMS systems.                         */
/*  Provided by: RAMO@uvphys.phys.UVic.CA                */
/*  Some people have run into problems with this timer.  */
/*********************************************************/
#ifdef VMS
#include time

#ifndef HZ
#define HZ 100
#endif

struct tbuffer_t
      {
       int proc_user_time;
       int proc_system_time;
       int child_user_time;
       int child_system_time;
      };

struct tbuffer_t tms;

dtime(p)
double p[];
{
 double q;

 q = p[2];

 times(&tms);

 p[2] = (double)(tms.proc_user_time) / (double)HZ;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/******************************/
/*  BORLAND C dtime() for DOS */
/******************************/
#ifdef BORLAND_C
#include <ctype.h>
#include <dos.h>
#include <time.h>

#define HZ 100
struct time tnow;

dtime(p)
double p[];
{
 double q;

 q = p[2];

 gettime(&tnow);

 p[2] = 60.0 * (double)(tnow.ti_min);
 p[2] = p[2] + (double)(tnow.ti_sec);
 p[2] = p[2] + (double)(tnow.ti_hund)/(double)HZ;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/**************************************/
/*  Microsoft C (MSC) dtime() for DOS */
/**************************************/
#ifdef MSC
#include <time.h>
#include <ctype.h>

#define HZ CLOCKS_PER_SEC
clock_t tnow;

dtime(p)
double p[];
{
 double q;

 q = p[2];

 tnow = clock();

 p[2] = (double)tnow / (double)HZ;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/*************************************/
/*  Macintosh (MAC) Think C dtime()  */
/*************************************/
#ifdef MAC
#include <time.h>

#define HZ 60

dtime(p)
double p[];
{
 double q;

 q = p[2];

 p[2] = (double)clock() / (double)HZ;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/************************************************************/
/*  iPSC/860 (IPSC) dtime() for i860.                       */
/*  Provided by: Dan Yergeau, yergeau@gloworm.Stanford.EDU  */
/************************************************************/
#ifdef IPSC
extern double dclock();

dtime(p)
double p[];
{
  double q;

  q = p[2];

  p[2] = dclock();
  p[1] = p[2] - q;
	
  return 0;
}
#endif

/**************************************************/
/*  FORTRAN dtime() for Cray type systems.        */
/*  This is the preferred timer for Cray systems. */
/**************************************************/
#ifdef FORTRAN_SEC

fortran double second();

dtime(p)
double p[];
{
 double q,v;

 q = p[2];

 second(&v);
 p[2] = v;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/***********************************************************/
/*  UNICOS C dtime() for Cray UNICOS systems.  Don't use   */
/*  unless absolutely necessary as returned time includes  */
/*  'user+system' time.  Provided by: R. Mike Dority,      */
/*  dority@craysea.cray.com                                */
/***********************************************************/
#ifdef CTimer
#include <time.h>

dtime(p)
double p[];
{
 double    q;
 clock_t   clock(void);

 q = p[2];

 p[2] = (double)clock() / (double)CLOCKS_PER_SEC;
 p[1] = p[2] - q;

 return 0;
}
#endif

/********************************************/
/* Another UNIX timer using gettimeofday(). */
/* However, getrusage() is preferred.       */
/********************************************/
#if defined(GTODay) && !defined(__MINGW32__)
#include <sys/time.h>

struct timeval tnow;

dtime(p)
double p[];
{
 double q;

 q = p[2];

 gettimeofday(&tnow,NULL);
 p[2] = (double)tnow.tv_sec + (double)tnow.tv_usec * 1.0e-6;
 p[1] = p[2] - q;

 return 0;
}
#endif

/*****************************************************/
/*  Fujitsu UXP/M timer.                             */
/*  Provided by: Mathew Lim, ANUSF, M.Lim@anu.edu.au */
/*****************************************************/
#ifdef UXPM
#include <sys/types.h>
#include <sys/timesu.h>
struct tmsu rusage;

dtime(p)
double p[];
{
 double q;

 q = p[2];

 timesu(&rusage);

 p[2] = (double)(rusage.tms_utime) * 1.0e-06;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/**********************************************/
/*    Macintosh (MAC_TMgr) Think C dtime()    */
/*   requires Think C Language Extensions or  */
/*    #include <MacHeaders> in the prefix     */
/*  provided by Francis H Schiffer 3rd (fhs)  */
/*         skipschiffer@genie.geis.com        */
/**********************************************/
#ifdef MAC_TMgr
#include <Time.h>
#include <stdlib.h>

static TMTask   mgrTimer;
static Boolean  mgrInited = FALSE;
static double   mgrClock;

#define RMV_TIMER RmvTime( (QElemPtr)&mgrTimer )
#define MAX_TIME  1800000000L
/* MAX_TIME limits time between calls to */
/* dtime( ) to no more than 30 minutes   */
/* this limitation could be removed by   */
/* creating a completion routine to sum  */
/* 30 minute segments (fhs 1994 feb 9)   */

static void     Remove_timer( )
{
 RMV_TIMER;
 mgrInited = FALSE;
}

int     dtime( p )
double p[];
{
 if ( mgrInited ) {
    RMV_TIMER;
    mgrClock += (MAX_TIME + mgrTimer.tmCount)*1.0e-6;
    } else {
    if ( _atexit( &Remove_timer ) == 0 ) mgrInited = TRUE;
    mgrClock = 0.0;
   }
	
 p[1] = mgrClock - p[2];
 p[2] = mgrClock;
 if ( mgrInited ) {
    mgrTimer.tmAddr = NULL;
    mgrTimer.tmCount = 0;
    mgrTimer.tmWakeUp = 0;
    mgrTimer.tmReserved = 0;
    InsTime( (QElemPtr)&mgrTimer );
    PrimeTime( (QElemPtr)&mgrTimer, -MAX_TIME );
   }
 return( 0 );
}
#endif

/***********************************************************/
/*  Parsytec GCel timer.                                   */
/*  Provided by: Georg Wambach, gw@informatik.uni-koeln.de */
/***********************************************************/
#ifdef PARIX
#include <sys/time.h>

dtime(p)
double p[];
{
 double q;

 q = p[2];
 p[2] = (double) (TimeNowHigh()) / (double) CLK_TCK_HIGH;
 p[1] = p[2] - q;

 return 0;
}
#endif

/************************************************/
/*  Sun Solaris POSIX dtime() routine           */
/*  Provided by: Case Larsen, CTLarsen@lbl.gov  */
/************************************************/
#ifdef POSIX
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/rusage.h>

#ifdef __hpux
#include <sys/syscall.h>
#define getrusage(a,b) syscall(SYS_getrusage,a,b)
#endif

struct rusage rusage;

dtime(p)
double p[];
{
 double q;

 q = p[2];

 getrusage(RUSAGE_SELF,&rusage);

 p[2] = (double)(rusage.ru_utime.tv_sec);
 p[2] = p[2] + (double)(rusage.ru_utime.tv_nsec) * 1.0e-09;
 p[1] = p[2] - q;
	
 return 0;
}
#endif

/****************************************************/
/*  Windows NT (32 bit) dtime() routine             */
/*  Provided by: Piers Haken, piersh@microsoft.com  */
/****************************************************/
#ifdef WIN32
#include <windows.h>

dtime(p)
double p[];
{
 double q;

 q = p[2];

 p[2] = (double)GetTickCount() * 1.0e-03;
 p[1] = p[2] - q;

 return 0;
}
#endif

/*****************************************************/
/* Time according to POSIX.1  -  <J.Pelan@qub.ac.uk> */
/* Ref: "POSIX Programmer's Guide"  O'Reilly & Assoc.*/
/*****************************************************/
#ifdef POSIX1
#define _POSIX_SOURCE 1
#include <unistd.h>
#include <limits.h>
#include <sys/times.h>

struct tms tms;

dtime(p)
double p[];
{
 double q;
 times(&tms);
 q = p[2];
 p[2] = (double)tms.tms_utime / (double)CLK_TCK;
 p[1] = p[2] - q;
 return 0;
}
#endif

/*------ End flops.c code, say good night Jan! (Sep 1992) ------*/
