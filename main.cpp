#include <iostream>
#include <iomanip>

using namespace std;

#include "ISAAC.h"

void ArrayOut( ISAACgen & prng ,  uint32_t * pringout , int wos );
void ConsoleStream( uint32_t * ulip , int cs );
void FuncTestISAAC(  const char * notes , ISAACgen & prng , ub4 * seeda , int wos );


void ArrayOut( ISAACgen & prng ,  uint32_t * pringout , int wos )
{
	int n;
	for(n=0;n<wos;n++){
		pringout[n] = prng.Invoke();
	}
}

void ConsoleStream( uint32_t * ulip , int cs )
{
	int n;
	
	for(n=0;n<cs;n++){
		if( (n%8) == 0 ) cout << endl;
		cout << std::hex << std::setw(8) << std::setfill('0');
		cout << (ulip[n]);
		if( (cs-n) > 1 ) cout << ",";
	}
	
	cout << endl;
	cout << std::dec;
}

void FuncTestISAAC(  const char * notes , ISAACgen & prng , ub4 * seeda , int wos )
{
	int i;
	uint32_t * pringout;
	 //.
	pringout = new uint32_t[wos];
	
	prng.SeedArray( seeda );
	ArrayOut( prng , pringout , wos );
	cout << notes;
	ConsoleStream(   pringout , wos );
	
	delete [] pringout;
}
 
// ////////////////////////// //
//     MAIN ENTRY POINT       //
// ////////////////////////// //
int main(int argc, char** argv) 
{
	int n;	
	ISAACgen  allzeroRNG;
	ISAACgen  allonesRNG;
	ISAACgen  integersRNG;
	ub4		  genseed_one[256];
	ub4		  genseed_zer[256];
	ub4		  genseed_suc[256];
	  //.
	  
	for( n=0; n<256;n++){
		genseed_one[n] = (ub4)0xFFFFFFFF;
		genseed_zer[n] = (ub4)0x00;
		genseed_suc[n] = (ub4)n + (ub4)0xABCD0000;
	}
	
	
	FuncTestISAAC(  "_____ ISAAC seeded with all zeroes. First 24 outputs. ____" , allzeroRNG , genseed_zer , 24 );
	cout << endl;
	FuncTestISAAC(  "_____ ISAAC seeded with all ones. First 24 outputs. ____" , allonesRNG , genseed_one , 24 );
	cout << endl;
	FuncTestISAAC(  "_____ ISAAC seeded with successive integers. First 24 outputs. ____" , integersRNG , genseed_suc , 24 );
	cout << endl;
    
	return 0;
}



