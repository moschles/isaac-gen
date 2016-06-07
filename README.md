# isaac-gen
ISAAC is a cryptographically-secure random number generator. This repository includes a warning abouts its security. 
See CAVEAT.EMPTOR

ISAAC is a  cryptographically secure pseudorandom number generator, a `CSPRNG`
This is a portable class version for quick implementation.
!! - Please read the CAVEAT.EMPTOR 

class ISAACgen {} is initialized with a an array of 256 words, each of 32b. Thereafter, it produces a 32b word at each invocation.
