/* 
 * CS:APP Data Lab 
 * 
 * <zhjwpku@gmail.com>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x)|(~y));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  int r_shift = n << 3;
  int mask = 0xff;
  return (x >> r_shift) & mask;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int minus_n = (~n) + 1;
  // shift twice to adapt shift by 32 doing nothing
  int mask = ~(((~0) << (31 + minus_n)) << 1);
  return (x >> n) & mask;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /* solution 1: two many operators */
  //int MASK1 = 0x55 | 0x55 << 8 | 0x55 << 16 | 0x55 << 24;
  //int MASK2 = 0xaa | 0xaa << 8 | 0xaa << 16 | 0xaa << 24;
  //int MASK3 = 0x33 | 0x33 << 8 | 0x33 << 16 | 0x33 << 24;
  //int MASK4 = 0xcc | 0xcc << 8 | 0xcc << 16 | 0xcc << 24;
  //int MASK5 = 0x0f | 0x0f << 8 | 0x0f << 16 | 0x0f << 24;

  //x = (x & MASK1) + ((x & MASK2) >> 1);
  //x = (x & MASK3) + ((x & MASK4) >> 2);
  //x = (x + (x >> 4)) & MASK5;
  //x = (x + (x >> 8));
  //x = (x + (x >> 16)) & 0xff;

  /* solution 2: exactly 40 operators */
  int MASK1 = 0x55 | 0x55 << 8;
  int MASK2 = 0xaa | 0xaa << 8;
  int MASK3 = 0x33 | 0x33 << 8;
  int MASK4 = 0xcc | 0xcc << 8;
  int MASK6 = 0xff | 0xff << 8;

  int l = x & MASK6;
  int h = (x >> 16) & MASK6;  

  h = (h & MASK1) + ((h & MASK2) >> 1);
  h = (h & MASK3) + ((h & MASK4) >> 2);

  l = (l & MASK1) + ((l & MASK2) >> 1);
  l = (l & MASK3) + ((l & MASK4) >> 2);
  h = l + h;

  return (h & 0x0f) + ((h >> 4) & 0x0f) + ((h >> 8) & 0x0f) + ((h >> 12) & 0x0f);
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return (~((x | (~x + 1)) >> 31)) & 0x01;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int c = 32 + (~n + 1);
  int mask = (x << c) >> c;
  return !(x ^ mask);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  //int bias= (x >> 31) & ((1 << n) - 1);  // bias = 2^n - 1
  int bias=(x >> 31) & ((0x1 << n) + ~0);  // turn -1 to + ~0
  return (x + bias) >> n;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return !((x >> 31) & 0x1) & !!x;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int tmp = !!((x + ~y) >> 31);
  x = x >> 31;
  y = y >> 31;
  return (!!x | !y) & ((!!x & !y) | tmp);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int ret = 0;
  ret = (!!(x >> 16)) << 4;    // binary
  ret += (!!(x >> (ret + 8)) << 3);
  ret += (!!(x >> (ret + 4)) << 2);
  ret += (!!(x >> (ret + 2)) << 1);
  ret += (!!(x >> (ret + 1)) << 0);
  return ret;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  if (((uf << 1) ^ 0xffffffff) < 0x00ffffff) {  // This is NaN
    return uf;
  }
  return uf ^ (0x80000000);
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  int exp = 0;
  int sign = x & 0x80000000;
  int n = -1;
  int tmp = 0;
  int cp = 0;
  int cp2 = 0;

  if (x == 0x80000000) {
    return 0xcf000000;	// -2^31 sign = 1, E = bias + 31 = 158
  }
  if (x == 0) {
    return 0;
  }
  /* because x is integer, we don't consider denormalized value */
  if (sign) {
    x = -x;	// this also remove the sign bit
  }

  tmp = x;
  while (tmp) {
    tmp >>= 1;
    n ++;
  }

  x = x - (0x1 << n);
  if (n < 24) {
    x = x << (23 - n);
  } else {
    tmp = x >> (n - 23);
    cp2 = 0x1 << (n - 24);
    cp = x & ((cp2 << 1) - 1);
    if (cp < cp2) {
      x = tmp;
    } else {
      if (tmp == 0x7fffff) {
        x = 0;
        n++;
      } else {
        if (cp == cp2) {
          x = ((tmp) & 0x1) + tmp;	
        } else {
          x = tmp + 1;
        }
      }
    }
  }

  exp = (127 + n) << 23;
  return sign | exp | x;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  int sign = uf & 0x80000000;
  int exp = uf & 0x7f800000;
  int frac = uf & 0x7fffff;

  if (exp >> 23 == 0x0) {	// denornalized
    return sign | uf << 1;
  }

  if (exp >> 23 == 0xff) {	// infinity and NaN
    return uf;
  }

  if ((exp >> 23) + 1 == 0xff) {	// normal but overflow
    return sign | 0x7f800000;
  }

  return sign | (((exp >> 23) + 1) << 23) | frac;	// normal
  return 2;
}
