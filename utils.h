#pragma once

template<int N1>
void concat_str(char (&str1)[N1], const char *str2)
{
    int size = 0;
    for (; str1[size] != 0; size++) // looking for the end of str1
    {
    }

    int j = 0;
    int k = size;
    for (; str2[j] != 0 && k < N1; k++)
    {
        str1[k] = str2[j];
        j++;
    }
    str1[k] = 0;
}