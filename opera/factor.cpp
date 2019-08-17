#include "factor.hpp"

// Algorithme rho de Pollard avec f(x)=(x^2)+a et x0=x
Integer get_prime(Integer n, int a, Integer x) {
   Integer  y, q, g, s;
   s = x; 
   y = x; 
   do {
      x = ((x*x)+a)%n; 
      y = ((y*y)+a)%n; 
      y = ((y*y)+a)%n; 
      if(y > x) q = (y-x)%n;
      else q = (x-y)%n;
      g = gcd(n, q); 
      if(g > 1 && g < n) { 
         if(isprime(g)) return g; 
         else return get_prime(g, a, s); 
      } 
   }while(x != y);
   return 0;
}

Integer get_factor(Integer n) {
   if (n%2 == 0) return 2; 
   if (n%3 == 0) return 3; 
   if (n%5 == 0) return 5; 
   if (n%7 == 0) return 7;
   // on choisit : f(x) = (x^2) + a 
   // avec a = 1, 3, 5 ou 7 et x0 = 2
   Integer p, x = 2;
   int a = 1, i = 0;
   do {
      p = get_prime(n, a+i, x);
      if(p > 0) return p;
      i = i+2;
   }while(i < 7);
   // en cas d'échec
   return 0;
}
