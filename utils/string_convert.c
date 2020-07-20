/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** string_convert
*/

#include "string_convert.h"
#include <stddef.h>

int stoi(char const *str)
{
    int nb = 0;
    int neg = 1;
    int i = 0;

    if (str == NULL)
        return (0);
    for (; str[i] == '-' || str[i] == '+'; i++)
        if (str[i] == '-')
            neg *= -1;
    for (; str[i]; i++)
        if (str[i] >= '0' && str[i] <= '9') {
            nb *= 10;
            nb += str[i] - '0';
        } else
            break;
    return (nb * neg);
}