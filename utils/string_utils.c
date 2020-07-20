/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** string_utils
*/

#include "string_utils.h"
#include <stdlib.h>

int my_strlen(char const *str)
{
    int len = 0;

    for (; str && str[len]; len++);
    return (len);
}

char *my_strcat(char **str)
{
    int len = 0;
    int count = 0;
    char *res;
    int res_i = 0;

    for (; str && str[count]; count++)
        len += my_strlen(str[count]);
    res = malloc(sizeof(char) * (len + 1));
    if (res == NULL)
        return (NULL);
    for (int i = 0; i < count; i++)
        for (int j = 0; str[i][j]; j++)
            res[res_i++] = str[i][j];
    res[res_i] = 0;
    return (res);
}

int my_streq(char const *a, char const *b)
{
    int len_a = my_strlen(a);
    int len_b = my_strlen(b);

    if (a == NULL || b == NULL)
        return (0);
    if (len_a != len_b)
        return (0);
    for (int i = 0; i < len_a; i++)
        if (a[i] != b[i])
            return (0);
    return (1);
}

char *my_strdup(char const *str)
{
    int len = my_strlen(str);
    char *res;

    if (str == NULL)
        return (NULL);
    res = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
        res[i] = str[i];
    res[len] = 0;
    return (res);
}
