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

    long long findLargestPrimeFactor(long long num) {
      // NOT MEMORY SAFE. WILL BLOW UP PC.
      // TODO: clean up as we go.
      
      // Used to iterate through natural numbers with the Sieve of Eratosthenes
      // and mark them as non-prime candidates. 
      struct NumberMarkPair {
        long long number;
        bool is_marked; // true mark means NOT prime
      };
      std::vector<NumberMarkPair> naturalNumberMarkPairs = {};
      std::vector<long long> primeNumbers = {2};
      // The first prime number is 2. We are going to populate our vector
      // with the natural numbers including the max, because that could be 
      // a prime factor. 
      for (long long naturalNumber = 2; naturalNumber <= num; naturalNumber++)
      {
        // false means no mark yet.
        naturalNumberMarkPairs.push_back({naturalNumber, false});
      }
      long long length = naturalNumberMarkPairs.size();
      bool calculatingPrimes = true;
      // `p` is the next prime number, used to check if numbers are composite
      // if they are a multiple of it. 
      long long p = 2;
      while (calculatingPrimes) {
        // Since we started with 2, we have to shift the starting indecie over
        // by that amount. We start at 2p, because we don't want to mark "1p".
        for (long long i = 2 * p - 2; i < length; i += p) {
          naturalNumberMarkPairs[i].is_marked = true;
        }
        // If this stays false after looking for the next prime number, that
        // means there are none left in the sequence. 
        bool foundNewP = false;
        // We start checking for the next unmarked prime number right after p.
        // remeber the value of p is at indecie p - 2, so the value of p + 1,
        // is actually p - 1. Hope that makes sense. 
        for (long long i = p - 1; i < length; i++) {
          if (naturalNumberMarkPairs[i].is_marked == false) {
            // When we find the next prime number, we can add it to our list of
            // primes, note that we DID find one this time through, set it as
            // the new p, and stop looking. 
            foundNewP = true;
            primeNumbers.push_back(naturalNumberMarkPairs[i].number);
            p = naturalNumberMarkPairs[i].number;
            break;
          }
        }
        if (foundNewP != true) calculatingPrimes = false; 
      }
      // Debug
      //for (int n : primeNumbers) {
      //  std::cout << n << "\n";
      //}
      // Calculate the largest prime factor
      long long largestPrimeFactor = 0;
      for (long long primeNumber : primeNumbers) {
        if (num % primeNumber == 0) largestPrimeFactor = primeNumber;
      }
      return largestPrimeFactor;
    }
};

int main() {
  
  Computer computer;
  std::cout << computer.findLargestPrimeFactor(600851475143);

  return 0;

}



