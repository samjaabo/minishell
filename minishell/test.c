#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main()
{
	char	*a = "salam";
	char	*b = " hana";
	
	char *c;
	c = ft_strjoin(a, b);
	printf("%s\n", c);
}