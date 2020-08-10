# BinaryPalindrome

# Problem Statement
The task here is to determine the number of binary palindromes in the given range [a,b].
A binary palindrome is a number whose binary representation is reading the same either in reverse or in forward direction.
eg: 5(decimal)  --> 101 (Binary) 
Here on reading the number 5 in binary format, remains same in forward and reverse direction. Hence it is a binary Palindrome.
Also the leading zeroes are not considered for evaluation. 
a and b are two unsigned integers and their range is from ( 0 to 2^32 -1 ).

# Approach: Solution

* A predefined Eight bit reverse table is used in order to reverse the original 32bit number. 

* After reversing, the first set bit from LSB is identified.

* Then the number of zeroes prior to the first set bit from LSB is removed.

* Finally the resulting number is subtracted with the original number.

* If difference is zero ,the number is palindrome else not.

Note: Using this approach the execution time reduces for bigger range between a and b.

