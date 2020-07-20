/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_puts
*/

#include "my_puts.h"
#include "string_utils.h"
#include <unistd.h>

int my_putstr(char const *str)
{
    int len = my_strlen(str);

    write(1, str, len);
    return (len);
}

int my_puterr(char const *str)
{
    int len = my_strlen(str);

    write(2, str, len);
    return (len);
}

int my_puterr2(char const *a, char const *b)
{
    int lena = my_strlen(a);
    int lenb = my_strlen(b);

    write(2, a, lena);
    write(2, b, lenb);
    return (lena + lenb);
}