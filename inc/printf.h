/*
** EPITECH PROJECT, 2017
** 
** File description:
** printf
*/

#ifndef _PRINTF_H_
	#define _PRINTF_H_

	#include <unistd.h>
	#include <stdio.h>
	#include <stdarg.h>

#define IS_NUM(c) ((c >= '0' && c <= '9') ? 1 : 0)

typedef void (*p_fmt)(void *);
typedef struct s_fmt t_fmt;

struct s_fmt
{
		char fmt;
		void (*f)(void *);
};

int my_atoi(char *s);
void my_itoa(int n, int base);
void my_ulltoa(unsigned long long n, int base);
void print_char(void *p);
void print_hex(void *p);
void print_ptr(void *p);
void print_string(void *p);
void print_digit(void *p);
void print_octal(void *p);
int my_printf(const char *fmt, ...);

#endif
