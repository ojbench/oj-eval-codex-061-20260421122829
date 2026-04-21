#include <iostream>
#include "complex.hpp"
using namespace sjtu;
int main(){
  complex z0; complex z1=1; complex z2(2,3); complex z3(z2);
  std::cout << int(z0==complex(0,0)) << "\n";
  std::cout << (z2) << "\n";
  std::cout << (~z2) << "\n";
  std::cout << (-z2) << "\n";
  complex a(1,2), b(3,4);
  std::cout << (a+b) << "\n";
  std::cout << (a-b) << "\n";
  std::cout << (a*b) << "\n";
  std::cout << (a/b) << "\n";
  complex c(-1e-7, 1e-7);
  std::cout << (c?1:0) << "\n"; // should be false -> 0
  try { complex zero; a/=zero; } catch(const std::exception &e){ std::cout << e.what() << "\n"; }
}
