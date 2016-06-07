/* ----------------------------------------------

ISAAC.h

ISAAC is a  cryptographically secure pseudorandom number generator, a `CSPRNG`
This is a portable class version for quick implementation.
!! - Please read the CAVEAT.EMPTOR 

(c) Robert J. Jenkins Jr., March 1996, Public Domain

-------------------------------------------------- */
//	Tuesday, June 07, 2016
//	05:22:26 PM

typedef  unsigned long int  ub4;

class ISAACgen {
// Data
public:
    ub4 randrsl[256];
    ub4 mm[256];
    ub4 randcnt;
    ub4 aa;
    ub4 bb;
    ub4 cc;

// Functionality
public:
        ISAACgen();
        ~ISAACgen();
        void        UpdateStateTable( void );
        void        Initialize(int flag);
        void        SeedArray( ub4 * uSeed );
        void        SeedConst( ub4  ucSeed );
        uint32_t    Invoke( void );
        void        Security( void );

inline  void        mix(ub4 &a,ub4 &b, ub4 &c, ub4 &d,
                        ub4 &e,ub4 &f, ub4 &g, ub4 &h);
};


// * //

inline void ISAACgen
::mix(ub4 &a,ub4 &b, ub4 &c, ub4 &d,
      ub4 &e,ub4 &f, ub4 &g, ub4 &h)
{
   a^=b<<11; d+=a; b+=c;
   b^=c>>2;  e+=b; c+=d;
   c^=d<<8;  f+=c; d+=e;
   d^=e>>16; g+=d; e+=f;
   e^=f<<10; h+=e; f+=g;
   f^=g>>4;  a+=f; g+=h;
   g^=h<<8;  b+=g; h+=a;
   h^=a>>9;  c+=h; a+=b;
}


