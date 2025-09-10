#include <iostream>
#include <vector>

class Computer {
  public:
    int sumOfMultiples(int factors[], int max) {
      /*
      If we list all the natural numbers below 10
      that are multiples of 3 or 5, we get 3, 5, 6, and 9.
      The sum of these multiples is 23.

      sumOfMultiples() finds the sum of all multiples of numbers defined in 
      `factors` in the natural numbers less than the `max`
      */
      int sum = 0;
      int length = sizeof(factors) / sizeof(factors[0]);
      for (int num = 0; num < max; num++) {
        // check against the multiples
        for (int i = 0; i < length; i++) {
          if (num % factors[i] == 0) {
            sum += num;
            // avoid double counting numbers that are multiples of many factors
            break;
          }
        }
      }
      return sum;
    }

    int sumEvenFibonacciNumbers(int max) {
      /*
      Provides the sum of all even fibonacci numbers below the `max`.
      */
      
      // We only care about the last two fibonacci numbers in the sequence,
      // no need to store the rest.
      int twoPrior = 0;
      int onePrior = 1;
      int current = 0;

      int sum = 0;
      while (current <= max) {
        // Check if even
        if (current % 2 == 0) {
          sum += current;
        }
        twoPrior = onePrior;
        onePrior = current;
        current = twoPrior + onePrior;
      }
      return sum;
    }
};

int main() {
  
  Computer computer;
  std::cout << computer.sumEvenFibonacciNumbers(4000000);

  

}



