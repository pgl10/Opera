// factor.cpp

#include "factor.hpp"

// Des divisions successives pour chercher un éventuel facteur premier de n plus petit que 1000.
bool divisions(Integer& n, int& d) {
    int primes[170] = {
       2,      3,      5,      7,     11,    13,    17,    19,    23,    29,
      31,     37,     41,     43,     47,    53,    59,    61,    67,    71,
      73,     79,     83,     89,     97,   101,   103,   107,   109,   113,
     127,    131,    137,    139,    149,   151,   157,   163,   167,   173,
     179,    181,    191,    193,    197,   199,   211,   223,   227,   229,
     233,    239,    241,    251,    257,   263,   269,   271,   277,   281,
     283,    293,    307,    311,    313,   317,   331,   337,   347,   349,
     353,    359,    367,    373,    379,   383,   389,   397,   401,   409,
     419,    421,    431,    433,    439,   443,   449,   457,   461,   463,
     467,    479,    487,    491,    499,   503,   509,   521,   523,   541,
     547,    557,    563,    569,    571,   577,   587,   593,   599,   601,
     607,    613,    617,    619,    631,   641,   643,   647,   653,   659,
     661,    673,    677,    683,    691,   701,   709,   719,   727,   733,
     739,    743,    751,    757,    761,   769,   773,   787,   797,   809,
     811,    821,    823,    827,    829,   839,   853,   857,   859,   863,
     877,    881,    883,    887,    907,   911,   919,   929,   937,   941,
     947,    953,    967,    971,    977,   983,   991,   997,  1009,  1013};
    int i = 0;
    while(primes[i] < 1009) {
        if(n%primes[i] == 0) {
            d = primes[i];
            return true;
        }
        ++i;
    }
    return false;
}

// Algorithme rho de Pollard avec f(x)=(x^2)+a 
Integer get_prime(Integer n, int a, Integer x) {
   Integer  y, q, g;
   y = x; 
   do {
      x = ((x*x)+a)%n; 
      y = ((y*y)+a)%n; 
      y = ((y*y)+a)%n; 
      if(y > x) q = (y-x)%n;
      else q = (x-y)%n;
      g = gcd(n, q); 
      if(g > 1 && g < n) { 
         // g est un diviseur de n
         while(!isprime(g)) g = get_factor(g);
         return g; 
      } 
   }while(x != y);
   return 0;
}

// Calcul d'un facteur premier de n
Integer get_factor(Integer n) {
   if(n < 0) n = -n;
   if(n < 2) return 0;
   if(isprime(n)) return n;
   int d;
   if(divisions(n, d)) {
      Integer f = d;
      return f;
   }
   // on choisit : f(x) = (x^2) + c
   // avec c = 1 ou 3 ou ... ou 13
   // à partir de x0 = 2
   Integer p, x = 2;
   int a = 1, i = 0;
   do {
      p = get_prime(n, a+i, x);
      if(p > 0) return p;
      i = i+2;
   }while(i < 13);
   // en cas d'échec
   return 0;
}
