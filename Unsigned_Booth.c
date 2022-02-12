/*
 * BOOTH's ALGORITHM to Multiply two Unsigned Integers
 *
 * @author: ABHISHEK
 * @github: https://github.com/abhishek-bits
 * 
 * Shell command to execute: gcc Unsigned_Booth.c -lm
 */

#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAX 100

unsigned int multiply(unsigned int, unsigned int);
unsigned int max(unsigned int, unsigned int);
unsigned int int_to_binary(unsigned int from, char *bin);
unsigned int binary_to_int(char *a, char *q, unsigned int lim);
unsigned int full_adder(char *, char *, unsigned int lim, unsigned int carry);
char right_shift(char *, char bit_lead, unsigned int lim);
void algo_booth(char *m, char *q, char *a, unsigned int lim);
void add_leading_zeroes(char *, unsigned int offset);
void strrev(char *, unsigned int lim);

int main() {

    unsigned int opr1, opr2;
    
    printf("Enter two unsigned integers: ");
    scanf("%d %d", &opr1, &opr2);

    printf("%d * %d = %d\n", opr1, opr2, multiply(opr1, opr2));

    return 0;
}

/* multiply the two given unsigned integers */
unsigned int multiply(unsigned int opr1, unsigned int opr2) {

    char m[MAX] = { 0 };  /* Multiplicand */
    char q[MAX] = { 0 };  /* Multiplier */
    char a[MAX] = { 0 };  /* Accumulator */

    int len_m = int_to_binary(opr1, m);
    int len_q = int_to_binary(opr2, q);

    unsigned int n = max(len_m, len_q);

    if(len_m < n) {
        add_leading_zeroes(m, n - len_m);
    }
    if(len_q < n) {
        add_leading_zeroes(q, n - len_q);
    }
    add_leading_zeroes(a, n);

    //printf("m: %s\nq: %s\na: %s\n", m, q, a);

    algo_booth(m, q, a, n);

    return binary_to_int(a, q, n);
}

/* Booth's algorithm for Unsigned Integer Multiplication */
void algo_booth(char *m, char *q, char *a, unsigned int n) {
    int lsb = n - 1;
    for(int step = 1; step <= n; step++) {
        int carry = 0;
        /* if LSB is 1 then ADD the accumulator and the multiplicand */
        if(q[lsb] == '1') {
            carry = full_adder(a, m, n, carry);
        }
        /* right shift both accumulator and the multiplier */
        char bit_throw = right_shift(a, carry == 0 ? '0' : '1', n);
        right_shift(q, bit_throw, n);
        
        //printf("a: %s, q: %s\n", a, q);
    }
}

/*
 * Sequential Full Adder Implementation
 * Ref: https://www.sciencedirect.com/topics/computer-science/full-adder
 * 
 * add the two binary strings and return the carry-out
 */
unsigned int full_adder(char *a, char *m, unsigned int lim, unsigned int carry) {
    for(int i = lim - 1; i >= 0; i--) {
        int x = a[i] - '0';
        int y = m[i] - '0';
        int xor = x ^ y;
        int sum = carry ^ xor;
        carry = (x & y) | (carry & xor);
        a[i] = sum == 0 ? '0' : '1';
    }
    return carry;
}

/* right shift the binary sequence and return the bit thrown */
char right_shift(char *bin, char bit_lead, unsigned int n) {
    char bit_throw = bin[n - 1];    /* bit thrown during right-shift */
    for(int i = n - 1; i > 0; i--) {
        bin[i] = bin[i - 1];
    }
    bin[0] = bit_lead;
    return bit_throw;
}

/* 
 * return the result of the multiplication
 * higher order bits stored in accumulator register (a)
 * lower order bits stored in multiplier register (q)
 */
unsigned int binary_to_int(char *a, char *q, unsigned int n) {
    unsigned int num = 0, exp = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(q[i] == '1') {
            num += pow(2, exp);
        }
        exp++;
    }
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] == '1') {
            num += pow(2, exp);
        }
        exp++;
    }
    return num;
}

/* add leading zeroes to the given string */
void add_leading_zeroes(char *str, unsigned int offset) {
    int n = strlen(str);
    for(int i = n - 1; i >= 0; i--) {   /* shift the currently existing bits */
        str[i + offset] = str[i];
    }
    for(int i = 0; i < offset; i++) {   /* add leading zeroes */
        str[i] = '0';
    }
}

/* return the maximum value between the two integers */
unsigned int max(unsigned int a, unsigned int b) {
    return a > b ? a : b;
}

/* return the binary equivalent of the given number in decimal */
unsigned int int_to_binary(unsigned int from, char *to) {
    unsigned int i = 0;
    while(from > 0) {
        if((from & 1) == 1) {
            to[i++] = '1';
        } else {
            to[i++] = '0';
        }
        from >>= 1;
    }
    strrev(to, i);
    return i;
}

/* reverse the string upto the given limit */
void strrev(char *str, unsigned int lim) {
    int i = 0, j = lim - 1;
    while(i < j) {
        char t = str[i];
        str[i] = str[j];
        str[j] = t;
        i++;
        j--;
    }
}
