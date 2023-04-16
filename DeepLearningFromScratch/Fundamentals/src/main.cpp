#include <iostream>
#include <vector>

#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>

namespace fundamentals
{
void cmpToStdVec()
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

void axisSum()
{
   std::cout << "Axis sum" << std::endl;
   xt::xarray<double> a = { { 1, 2 }, { 3, 4 } };
   std::cout << "a:" << std::endl << a << std::endl;
   std::cout << "a.sum(axis=0) = xt::sum(a, 0): " << xt::sum(a, 0) << std::endl;
   std::cout << "a.sum(axis=1) = xt::sum(a, 1): " << xt::sum(a, 1) << std::endl;
}

void add1Dto2DArray()
{
   xt::xarray<double> a = { { 1, 2, 3 }, { 4, 5, 6 } };
   xt::xarray<double> b = { { 10, 20, 30 } };
   std::cout << "a:" << std::endl << a << std::endl;
   std::cout << "b: " << b << std::endl;
   std::cout << "a + b: " << std::endl << a + b << std::endl;
}

void derivativeCheck();

void nestedFunctions();

void chainRule();

void chainRuleTwoInputs();
}

xt::xarray<double> square(const xt::xarray<double>& x)
{
   return xt::pow(x, 2);
}

double square(double x)
{
   return std::pow(x, 2);
}

xt::xarray<double> ssqrt(const xt::xarray<double>& x)
{
   return xt::sqrt(x);
}

double ssqrt(double x)
{
   return std::sqrt(x);
}

xt::xarray<double> leakyRelu(const xt::xarray<double>& x)
{
   return xt::maximum(0.2 * x, x);
}

double leakyRelu(double x)
{
   return std::max(0.2 * x, x);
}

xt::xarray<double> deriv(const std::function<xt::xarray<double>(const xt::xarray<double>&)>& func,
   const xt::xarray<double>& input, double delta = 0.0001)
{
   return (func(input + delta) - func(input - delta)) / (2.0 * delta);
}

double deriv(const std::function<double(double)>& func, double input, double delta = 0.0001)
{
   return (func(input + delta) - func(input - delta)) / (2.0 * delta);
}

void fundamentals::derivativeCheck()
{
   std::cout << "Derivative check" << std::endl;
   double x = 16;
   double (*sqrt_ptr)(double) = &ssqrt;
   double dfdx = deriv(sqrt_ptr, x, 0.0001);
   std::cout << "f(x) = std::sqrt(x)" << std::endl;
   std::cout << "f(" << x << ") = " << ssqrt(x) << std::endl;
   std::cout << "f'(" << x << ") = " << dfdx << std::endl;
   double x1 = 17;
   std::cout << "f(" << x1 << " = " << ssqrt(x) + dfdx * (x1 - x) << std::endl;
}

typedef std::vector<std::function<double(double)>> ChainSingle;
typedef std::vector<std::function<xt::xarray<double>(const xt::xarray<double>&)>> Chain;

void fundamentals::nestedFunctions()
{
   std::cout << "Nested functions" << std::endl;
   auto f1 = [](double x)
   {
      //square
      return x * x;
   };

   auto f2 = [](double x)
   {
      return x * 2;
   };
   ChainSingle chain = { f1, f2 };

   std::cout << "f1(x) = x^2" << std::endl;
   std::cout << "f2(x) = 2x" << std::endl;
   int x = 3;
   std::cout << "f1(f2(" << x << ")) = " << f1(f2(x)) << std::endl;
   std::cout << "f2(f1(" << x << ")) = " << f2(f1(x)) << std::endl;
}

xt::xarray<double> sigmoid(const xt::xarray<double>& x)
{
   return 1 / (1 + xt::exp(x));
}

double sigmoid(double x)
{
   return 1 / (1 + std::exp(x));
}

double chainSingleDeriv2(const ChainSingle& chain, double x)
{
   //(f2(f1(x)))' = f2'(f1(x)) * f1'(x)
   if (chain.size() < 2)
   {
      std::cout << "chain.size() < 2" << std::endl;
      return 0.0;
   }
   auto& f1 = chain[0];
   auto& f2 = chain[1];

   //df1/dx
   double f1x = f1(x);

   //du -> input
   //df1/du
   double df1dx = deriv(f1, x);

   //df2/du(f1(x))
   double df2du = deriv(f2, f1(x));

   return df1dx * df2du;
}

xt::xarray<double> chainDeriv2(const Chain& chain, const xt::xarray<double>& x)
{
   //(f2(f1(x)))' = f2'(f1(x)) * f1'(x)
   if (chain.size() < 2)
   {
      std::cout << "chain.size() < 2" << std::endl;
      return 0.0;
   }
   auto& f1 = chain[0];
   auto& f2 = chain[1];

   //df1/dx
   xt::xarray<double> f1x = f1(x);

   //du -> input
   //df1/du
   xt::xarray<double> df1dx = deriv(f1, x);

   //df2/du(f1(x))
   xt::xarray<double> df2du = deriv(f2, f1(x));

   return df1dx * df2du;
}

double chainSingleDeriv3(const ChainSingle& chain, double x)
{
   //(f3(f2(f1(x))))' = f3'(f2(f1(x)) * f2'(f1(x)) * f1'(x)
   if (chain.size() < 3)
   {
      std::cout << "chain.size() < 3" << std::endl;
      return 0.0;
   }
   auto& f1 = chain[0];
   auto& f2 = chain[1];
   auto& f3 = chain[2];

   //df1/dx
   double f1x = f1(x);

   //du -> input

   //df2/du(f1(x))
   double df3du = deriv(f3, f2(f1(x)));
   //df2/du(f1(x))
   double df2du = deriv(f2, f1(x));
   //df1/du
   double df1dx = deriv(f1, x);

   return df1dx * df2du * df3du;
}

void fundamentals::chainRule()
{
   std::cout << "Chain rule" << std::endl;
   std::cout << "Nested functions" << std::endl;
   auto f1 = [](double x)
   {
      //square
      return x * x;
   };

   auto f2 = [](double x)
   {
      return x * 2;
   };
   ChainSingle chain = { f1, f2 };

   double x = 3;
   double (*sqrt_ptr)(double) = &ssqrt;
   double dfdu = chainSingleDeriv2(chain, x);
   std::cout << "f2(f1(x)) = x * x * 2" << std::endl;
   std::cout << "f2(f1(" << x << ")) = " << f2(f1(x)) << std::endl;
   std::cout << "(f2(f1(" << x << "))' = " << dfdu << std::endl;
   double x1 = 4;
   std::cout << "f2(f1(" << x1 << ")) appr. = " << f2(f1(x)) + dfdu * (x1 - x) << std::endl;
   std::cout << "f2(f1(" << x1 << ")) = " << f2(f1(x1)) << std::endl;
}

void fundamentals::chainRuleTwoInputs()
{
   double x = 2;
   double y = 3;
   auto fun = [](double x, double y)
   {
      return x + y;
   };

   //f1 -> square()
   //f2 -> fun()
   std::cout << "square(fun(" << x << ", " << y << ")) = " << square(fun(x, y)) << std::endl;
   double a = fun(x, y);
   double (*square_ptr)(double) = &square;
   double dsda = deriv(square_ptr, a);

   double dadx = deriv(fun, x);
   double dady = deriv(fun, y);
}

int main()
{
   //fundamentals::cmpToStdVec();
   //std::cout << "------------------------------" << std::endl;
   //fundamentals::axisSum();
   //std::cout << "------------------------------" << std::endl;
   //fundamentals::add1Dto2DArray();
   //std::cout << "------------------------------" << std::endl;
   fundamentals::derivativeCheck();
   std::cout << "------------------------------" << std::endl;
   fundamentals::nestedFunctions();
   std::cout << "------------------------------" << std::endl;
   fundamentals::chainRule();
   std::cout << "------------------------------" << std::endl;
   fundamentals::chainRuleTwoInputs();
   return 0;
}