
#include <stdio.h>

/// @brief skips spaces or numbers
/// @param av the argument
/// @param spaces flag, if 1 skips spaces, if 0 skips everything but spaces
/// @param i the index it starts from
/// @param check_num flag, checkes if the character sent is a number or not
int	skip(char *av, int spaces, int i, int check_num)
{
	if (spaces)
	{
		while (av[i] == ' ' || (av[i] >= 9 && av[i] <= 13) && av[i] != '\0')
			i++;
	}
	else
	{
		while (av[i] != ' ' && !(av[i] >= 9 && av[i] <= 13) && av[i] != '\0')
		{
			if (check_num)
			{
				if (!validate_num(av[i]))
                {
                    printf("%s\n",av);
                    printf("i equal %d\n", i);
                    printf("char is %c\n", av[i]);
					return (-1);
                }
			}
			i++;
		}
	}
	return (i);
}

//counts number of arguments in a string. (useful in general)
int	arg_ctr(char *av)
{
	int	i;
	int	ctr;

	ctr = 0;
	i = 0;
	while (av[i] != '\0')
	{
		i = skip(av, 1, i, 0);
		if (av[i] != '\0')
			ctr++;
		i = skip(av, 0, i, 1);
		if (i == -1)
			return (-1);
	}
    printf("ctr is %d\n", ctr);
	return (ctr);
}
