#include <cmath>
#include <iostream>

using namespace std;

unsigned long long karatsuba_multiplication(long long number1,
                                            long long number2);

int main()

{
  unsigned long long number1, number2, result;
  cout << "Enter a first number: ";
  cin >> number1;
  cout << "Enter a second number: ";
  cin >> number2;

  result = karatsuba_multiplication(number1, number2);
  cout << result << std::endl;

  return 0;
}

unsigned long long karatsuba_multiplication(long long number1,
                                            long long number2) {
  if (number1 < 10 || number2 < 10) {
    return number1 * number2;
  }

  unsigned long long a, b, c, d;

  unsigned long long size =
      max(to_string(number1).length(), to_string(number2).length());

  size = size % 2 ? size / 2 : (size + 1) / 2;

  b = number1 % (unsigned long long)pow(10, size);
  a = (number1 - b) / pow(10, size);

  d = number2 % (unsigned long long)pow(10, size);
  c = (number2 - d) / pow(10, size);

  unsigned long long z2 = karatsuba_multiplication(a, c);
  unsigned long long z0 = karatsuba_multiplication(b, d);
  unsigned long long z1 = karatsuba_multiplication((a + b), (c + d)) - z2 - z0;

  return z2 * pow(pow(10, size), 2) + z1 * pow(10, size) + z0;
}
