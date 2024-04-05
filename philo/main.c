

#include "philo.h"

int main(int ac, char **av)
{
    t_input *input;
    char    **nums;

    nums = validate(ac-1, av);
    if (!nums)
        return (0);
    input = malloc (sizeof(t_input));
    if (!input)
    {
        //free nums;
        //print error: no space
        return (0);
    }
    

}