#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
    size_t i;
    
    i = 0;
    while (s[i])
        i++;
    return (i);
}
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == ch)
		return ((char *)&s[i]);
	return (NULL);
}
