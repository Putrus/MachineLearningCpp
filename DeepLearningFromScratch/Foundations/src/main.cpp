#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xview.hpp>


int main()
{
   std::vector<double> arr{ 5.0, 6.0, 7.0 };
   xt::xarray<double> arr2{ 5.0, 6.0, 7.0 };

   auto s = xt::ones<double>({ 4,  4 });
   arr2 *= 5;
   std::cout << arr2 << std::endl;
   std::cout << s << std::endl;
   return 0;
}