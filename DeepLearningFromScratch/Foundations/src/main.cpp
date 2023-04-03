#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
   os << '[';
   for (auto it = v.begin(); it != v.end(); ++it)
   {
      if (it != v.begin())
         os << ", ";

      os << *it;
   }
   os << ']';
   return os;
}

template <typename T>
void square(std::vector<T>& v)
{
   for (auto& element : v)
   {
      element = std::pow(element, 2);
   }
}

template <typename T>
void leakyRelu(std::vector<T>& v)
{
   for (auto& element : v)
   {
      element = std::max(static_cast<T>(0.2 * element), element);
   }
}

int main()
{
   std::vector<int> v = { 1, -25, 3, 4 };
   //square(v);
   std::cout << v << std::endl;
   leakyRelu(v);
   std::cout << v << std::endl;
   return 0;
}