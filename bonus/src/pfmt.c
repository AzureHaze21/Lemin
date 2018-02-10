/*
** EPITECH PROJECT, 2017
** lemin
** File description:
** lemin
*/

#include "printf.h"

void print_hex(void *p)
{
	unsigned n = *(unsigned*)p;
	my_ulltoa(n, 16);
}

void print_char(void *p)
{
		write(1, (char*)p, 1);
}

void print_ptr(void *p)
{
		write(1, "0x", 2);
		my_ulltoa((*(unsigned long long*)p), 16);
}

void print_octal(void *p)
{
		my_itoa(*(int *)p, 8);
}
