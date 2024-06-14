#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_putstr_fd(char const *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	size;
	char	*nstr;

	if (!s1)
		return (strdup(s2));
	if (!s2)
		return (strdup(s1));
	size = strlen(s1) + strlen(s2);
	nstr = malloc(sizeof(char) * (size + 1));
	if (!nstr)
		return (NULL);
	i = -1;
	while (s1[++i])
		nstr[i] = s1[i];
	j = 0;
	while (s2[j])
		nstr[i++] = s2[j++];
	nstr[i] = '\0';
	return (nstr);
}

int		main(int ac, char **av)
{
	if (ac != 7)
	{
		printf("Usage: ./gen <map_name> <map_width> <map_height> <player_dir> <player_x> <player_y>\n");
		exit(1);
	}
	size_t	width = atoll(av[2]);
	size_t	height = atoll(av[3]);
	size_t	p_x = atoll(av[5]);
	size_t	p_y = atoll(av[6]);
	char	p_dir = av[4][0];
	char	*str = calloc(sizeof(char), (width + 2));

	char	*file = ft_strjoin("maps/", av[1]);
	int		fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		exit(1);

	ft_putstr_fd("NO ./textures/v2_north.xpm\nSO ./textures/v2_south.xpm\nWE ./textures/v2_west.xpm\nEA ./textures/v2_east.xpm\nF tex\nC tex\n", fd);
	size_t	i = 0;
	size_t	j = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i == p_y && j == p_x)
				str[j] = p_dir;
			else if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
				str[j] = '1';
			else
				str[j] = '0';
			j++;
		}
		if (i != height - 1)
			str[j++] = '\n';
		str[j] = 0;
		ft_putstr_fd(str, fd);
		i++;
	}
	free(str);
	free(file);
	close(fd);
}