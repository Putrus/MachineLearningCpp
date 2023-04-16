#include <iostream>
#include <vector>

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

void cmpVectorXArray()
{
   std::cout << "Compare std::vector vs xt::xarray" << std::endl;

   std::cout << "std::vector<double>" << std::endl;
   std::vector<double> std_a = { 1, 2, 3 };
   std::vector<double> std_b = { 4, 5, 6 };
   auto print_vector = [](const std::vector<double>& v)
   {
      for (const auto& el : v)
      {
         std::cout << el << " ";
      }
      std::cout << std::endl;
   };
   std::cout << "To print vectors I had to create own function" << std::endl;
   std::cout << "a: ";
   print_vector(std_a);
   std::cout << "b: ";
   print_vector(std_b);
   std::cout << "a + b doesn't work" << std::endl;
   std::cout << "a * b doesn't work" << std::endl << std::endl;

   std::cout << "xt::xarray<double>" << std::endl;
   xt::xarray<double> xt_a = { 1, 2, 3 };
   xt::xarray<double> xt_b = { 4, 5, 6 };
   std::cout << "a: " << xt_a << std::endl;
   std::cout << "b: " << xt_b << std::endl;
   std::cout << "a + b: " << xt_a + xt_b << std::endl;
   std::cout << "a * b: " << xt_a * xt_b << std::endl;
}


int main()
{
   cmpVectorXArray();
   return 0;
}