#include <iostream>
#include <vector>
#include <cmath>
#include <string> 

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
      // Memory safe, but the space complexity of this sieve is absurd--nothing
      // we can do about that except try to implement segmenting..
      // Thankfully, we are not trying to find all primes below `num`, we only
      // have to check up to sqrt(num), if there is still nothing, then `num`
      // itself is prime and that is the lpf.

      // Handles numbers 100s trillions just fine and lightning fast!
      // turns out 7607576777341 is prime, and the lpf of 127607576777341
      // is 718841!
      
      // Used to iterate through natural numbers with the Sieve of Eratosthenes
      // and mark them as non-prime candidates. 
      struct NumberMarkPair {
        long long number;
        bool is_marked; // true mark means NOT prime
      };
      std::vector<NumberMarkPair> naturalNumberMarkPairs = {};
      std::vector<size_t> primeNumbers = {2};
      // When the number you're trying to factor becomes smaller than the next
      // prime you're testing, or if it's less than the square of the current
      // prime, then the remaining number itself is a prime factor.
      // in other words:
      // we only need to check prime factors up to the square root of `num`
      int limit = ceil(std::sqrt(num));
      // The first prime number is 2. We are going to populate our vector
      // with the natural numbers including the max, because that could be 
      // a prime factor. 
      for (long long naturalNumber = 2; naturalNumber <= limit;
           naturalNumber++)
      {
        // false means no mark yet.
        naturalNumberMarkPairs.push_back({naturalNumber, false});
      }
      size_t length = naturalNumberMarkPairs.size();
      bool calculatingPrimes = true;
      // `p` is the next prime number, used to check if numbers are composite
      // if they are a multiple of it. 
      long long p = 2;
      // We test each new p as we find it.
      long long largestPrimeFactor = 0;
      // have to test the initial value of 2, here.
      if (num % p == 0) largestPrimeFactor = p; 
      while (calculatingPrimes) {
        // Since we started with 2, we have to shift the starting indecie over
        // by that amount. We start at 2p, because we don't want to mark "1p".
        for (size_t i = 2 * p - 2; i < length; i += p) {
          naturalNumberMarkPairs[i].is_marked = true;
        }
        // If this stays false after looking for the next prime number, that
        // means there are none left in the sequence. 
        bool foundNewP = false;
        // We start checking for the next unmarked prime number right after p.
        // remeber the value of p is at indecie p - 2, so the value of p + 1,
        // is actually p - 1. Hope that makes sense. 
        for (size_t i = p - 1; i < length; i++) {
          if (naturalNumberMarkPairs[i].is_marked == false) {
            // When we find the next prime number, we can add it to our list of
            // primes, note that we DID find one this time through, set it as
            // the new p, and stop looking. 
            foundNewP = true;
            p = naturalNumberMarkPairs[i].number;
            if (num % p == 0) largestPrimeFactor = p;
            break;
          }
        }
        if (foundNewP != true) calculatingPrimes = false; 
      }
      // Debug
      //for (int n : primeNumbers) {
      //  std::cout << n << "\n";
      //}
      if (largestPrimeFactor == 0) largestPrimeFactor = num;
      return largestPrimeFactor;
    }

    long long findLargestPrimeFactorUsingPseudosquaresPrimeSieve(int limit) {
     
      std::cout << "unimplemented!";
      // https://digitalcommons.butler.edu/cgi/viewcontent.cgi?referer=&httpsredir=1&article=1095&context=facsch_papers
      // I'll try again another time. This is a bit too advanced right now. 
      return 1;
    }

    long long findLargestPalindrome(int n) {
      // Finds the largest palindrome made from the product 
      // of two `n` digit(s) numbers.

      // pretty much only works up to n = 4. n = 5 takes a lot of compute 
      // time. We could seriously reduce this time by synthesizing the
      // palindromes ourselves instead of looking for them. TODO for future.

      // look for palindrome numbers p starting from the highest possible value
      // in that order of magnitude given the amount of digits of the factors.
      // for n = 3, limit = 999 x 999 = 998001
      long long limit = std::pow(std::pow(10, n) - 1, 2);
      // for n - 3, lowerBound = 100 x 100 = 10000
      long long lowerBound = std::pow(std::pow(10, n - 1), 2);
      std::cout << "limit " << limit << std::endl;
      std::cout << "lower bound " << lowerBound << std::endl;
      for (long long p = limit; p > lowerBound; p--) {
        // We check to see if it's a palindrome by reversing it and comparing
        // it to the original. 
        std::string o = std::to_string(p);
        std::string r = std::string(o.rbegin(), o.rend());
        // check all three `n` digit factors up to the sqrt(p).
        if (o == r) {
          for (long long j = std::pow(10, n - 1); j < ceil(std::sqrt(p)); j++)
          {
            // p / j < std::pow(10, n)) means the second divisor is n digits.
            // i.e. both divisors are n digits.
            if (p % j == 0 and p / j < std::pow(10, n)) return p;
          }
        }
      }
    }

    int calcaulateDifferenceBetweenFactorialSum(int n) {
      /*
      Not sure what to name it. In a sequence of numbers `n` long, find the
      difference: (1, 2, 3, ... n)^2 - (1^2, 2^2, 3^2, ... n^2)
      */
      int a = std::pow((n * (n + 1) / 2), 2); // (1, 2, 3, ... n)^2
      int b = 0; // sum of 1^2 .. n^2
      for (int x = 1; x <= n; x++) {
        int y = std::pow(x, 2);
        b += y;
      }
      int c = a - b;
      return c;
    }

    long long findValueOfAdjacentDigits(int numOfDigits, std::string number) {
      /*
      Finds the maximum value that can exist in a number from a n-digit long
      segment if all the digits are multiplied together. 
      */
      long long maxProductFound = 0;
      // Checking all segments of the number that are `numOfDigits` long
      for (size_t i = 0; i <= number.length() - numOfDigits; i++) {
        // the `block` is the segment of digits that is `numOfDigits` long.
        // we multiply all the digits in the block together to find a product.
        std::string block = number.substr(i, numOfDigits);
        // identity property, something to muliplying off of.
        long long blockProduct = 1; 
        // Finds the product of all the digits multiplied
        for (size_t j = 0; j < block.length(); j++) {
         blockProduct *= int(block[j] - '0'); // to correctly convert ASCII
        }
        // Enforces a running tracker of the greatest product found yet.
        if (blockProduct > maxProductFound) maxProductFound = blockProduct;
      }
      return maxProductFound;
    }

    bool isPrime(
      long long number,
      std::vector<long long> priorPrimes)
    {
      /*
      Given all the primes that exist less than a `number`, `priorPrimes`,
      determines if that `number` is prime. 
      */
      bool isPrime = false;
      // Conduct if the number is prime by doing the time test.
      // To be prime, it has to be a multiple of any prime numbers <= it's sqrt 
      for (size_t i = 0; priorPrimes[i] <= std::sqrt(number); i++) {
        // divisible by prime number means not prime -> default isPrime value.
        if (number % priorPrimes[i] == 0) return isPrime;
      }
      // if it passed all the tests..
      isPrime = true;
      return isPrime;
    }

    long long findNthPrimeNumber(int n) {
      /*
      For prime numbers 2,3,5,7,11.. we would say that 11 is the 5th prime
      number in the prime number sequence. This function finds the nth prime
      number in the prime number sequence. e.g. for n=270, the value is 1733.
      */
      // Storing the prime sequence as we go because we need it to run the 
      // prime test.
      std::vector<long long> primes = {2};
      // the next natural number that will be tested to see if it's prime. 
      long long nextNumber = 3; 
      int numOfPrimesFound = 1; // Because we start with 2
      while (true) {
        if (isPrime(nextNumber, primes)) {
          primes.push_back(nextNumber);
          numOfPrimesFound++;
        }
        if (numOfPrimesFound == n) {
          return nextNumber;
        }
        nextNumber++;
      }
    }
};

int main() {
  
  Computer computer;
  std::cout << computer.findNthPrimeNumber(10001);
  return 0;

}



