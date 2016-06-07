/* ----------------------------------------------

ISAAC.cpp

ISAAC is a  cryptographically secure pseudorandom number generator, a `CSPRNG`
This is a portable class version for quick implementation.
!! - Please read the CAVEAT.EMPTOR 

(c) Robert J. Jenkins Jr., March 1996, Public Domain

-------------------------------------------------- */
//	Tuesday, June 07, 2016
//	05:22:26 PM


#include <cstdlib>
#include <stdlib.h>
#include <stdint.h>
#include "ISAAC.h"


#define JPAMODIFICATIONS  JeanPhilippeAumasson


ISAACgen::ISAACgen()
{
    aa=bb=cc=randcnt=0;
}


ISAACgen::~ISAACgen()
{
    Security();
}


void ISAACgen
::UpdateStateTable(void)
{
   register ub4 i,x,y;

   cc = cc + 1;    /* cc just gets incremented once per 256 results */
   bb = bb + cc;   /* then combined with bb */

   for (i=0; i<256; ++i)
   {
     x = mm[i];
     switch (i%4)
     {
     case 0: aa = aa^(aa<<13); break;
     case 1: aa = aa^(aa>>6); break;
     case 2: aa = aa^(aa<<2); break;
     case 3: aa = aa^(aa>>16); break;
     }

#ifdef 	JPAMODIFICATIONS
	// ISAAC+
    // Modifications by Jean-Philippe Aumasson
    aa              = aa    + mm[(i+128) %256];
    mm[i]      = y  = aa^bb + mm[(x>>2)  %256];
    randrsl[i] = bb =     aa^(mm[(y>>10) %256]) + x;
    
#else

	// Jenkins' original formula.
    aa              = aa    + mm[(i+128)%256];
    mm[i]      = y  = aa+bb + mm[(x>>2) %256];
    randrsl[i] = bb =         mm[(y>>10)%256] + x;
#endif

     
   }

}


// * //


void ISAACgen
::Initialize(int flag)
{
   int i;
   ub4 a,b,c,d,e,f,g,h;
   //.
   
   aa=bb=cc=0;    // Taken care of.
   a=b=c=d=e=f=g=h=0x9e3779b9;  /* the golden ratio */

   for (i=0; i<4; ++i)          /* scramble it */
   {
     mix(a,b,c,d,e,f,g,h);
   }

   for (i=0; i<256; i+=8)   /* fill in mm[] with messy stuff */
   {
     if (flag)                  /* use all the information in the seed */
     {
       a+=randrsl[i  ]; b+=randrsl[i+1]; c+=randrsl[i+2]; d+=randrsl[i+3];
       e+=randrsl[i+4]; f+=randrsl[i+5]; g+=randrsl[i+6]; h+=randrsl[i+7];
     }
     mix(a,b,c,d,e,f,g,h);
     mm[i  ]=a; mm[i+1]=b; mm[i+2]=c; mm[i+3]=d;
     mm[i+4]=e; mm[i+5]=f; mm[i+6]=g; mm[i+7]=h;
   }

   if (flag)
   {        /* do a second pass to make all of the seed affect all of mm */
     for (i=0; i<256; i+=8)
     {
       a+=mm[i  ]; b+=mm[i+1]; c+=mm[i+2]; d+=mm[i+3];
       e+=mm[i+4]; f+=mm[i+5]; g+=mm[i+6]; h+=mm[i+7];
       mix(a,b,c,d,e,f,g,h);
       mm[i  ]=a; mm[i+1]=b; mm[i+2]=c; mm[i+3]=d;
       mm[i+4]=e; mm[i+5]=f; mm[i+6]=g; mm[i+7]=h;
     }
   }

   UpdateStateTable();/* fill in the first set of results */
   UpdateStateTable();
   randcnt=0;         /* prepare to use the first set of results */
}


void ISAACgen
::SeedArray( ub4 * uSeed )
{
    int i;

    for (i=0; i<256; ++i)  {
        mm[i]       =(ub4)uSeed[i];
        randrsl[i]  =(ub4)uSeed[i];
    }
    
    Initialize(1);
}


void ISAACgen
::SeedConst( ub4  ucSeed )
{
    int i;

    for (i=0; i<256; ++i)  {
        mm[i]       =(ub4)ucSeed;
        randrsl[i]  =(ub4)ucSeed;
    }

    Initialize(1);
}


uint32_t ISAACgen
::Invoke( void )
{
    ub4 cntloc, reti;
    uint32_t standard;
    //.
    
    reti = randrsl[randcnt];
    randcnt++;
    
    cntloc = randcnt;
    if( cntloc > 255 ) {
        randcnt = 0;
        UpdateStateTable();
    } 
    
    standard = (uint32_t)reti;
    return( standard );
}


void ISAACgen
::Security( void )
{
    ub4 w;
    
    w=0;
    while( w < 256 ) {
        randrsl[w] = (w+19)*17;
        mm[w]   = (w+19)*23;
        w++;
    }
    randcnt = (++w);
    aa = (++w);
    bb = (++w);
    cc = (++w);
}
   
