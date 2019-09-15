#include "factor.hpp"

// Algorithme rho de Pollard avec f(x)=(x^2)+a et x0=x
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
   if(n == 0) return 0;
   if(n == 1) return 1;
   if(n%2 == 0) return 2; 
   if(n%3 == 0) return 3; 
   if(n%5 == 0) return 5; 
   if(n%7 == 0) return 7;
   if(n%11 == 0) return 11;
   if(n%13 == 0) return 13;
   if(isprime(n)) return n;
   // on choisit : f(x) = (x^2) + c
   // avec x0 = 2 et c = 1, 3, ... , 13
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
