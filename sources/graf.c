#include "filler.h"
#include <fcntl.h>

int	*getdata(int *yx, char *line)
{
	yx[0] = 0;
	yx[1] = 0;
	while (		*line && yx[1] == 0)
	{
		if (*line >= '0' && *(line) <= '9')
		{
			yx[(yx[0] == 0) ? 0 : 1] = ft_atoi(line);
			while (*line >= '0' && *line <= '9' && yx[1] == 0)
				line++;
		}
		else
			line++;
	}
	return (yx);
}

void	spsel(char *line)
{
	int		i;

	i = 0;
	while(line[i])
	{
		if (line[i] == 'X')
			ft_putstr("\x1b[33;41m");
		if (line[i] == 'x')
			ft_putstr("\x1b[33;101m");
		if (line[i] == 'O')
			ft_putstr("\x1b[36;44m");
		if (line[i] == 'o')
			ft_putstr("\x1b[36;104m");
		if (line[i] == '.')
			ft_putstr("\x1b[97;107m");
		ft_putchar(line[i++]);
		ft_putstr("\x1b[0m");
	}
	ft_printf("\n");
}

int		ptab(char **line, int fd)
{
	int		size_b[2];
	int		i;

	i = 0;
	getdata(size_b, *line);
	if (size_b[0] * size_b[1] > 2500)
	{
		ft_printf("sorry, the map is too big, try a smaller\n");
		return(-1);
	}
	ft_strdel(line);
	get_next_line(fd, line);
	ft_strdel(line);
	while (i++ < size_b[0])
	{
		get_next_line(fd, line);
		spsel((*line) + 4);
		ft_strdel(line);
	}
	return (1);
}

int		readbox(int fd, int usage)
{
	char		*line;

	if (usage == 2)
	{
		if (fd != 2)
			return(ft_printf("usage: ./visual filler.result"));
		ft_printf("Visualizer:\n\ts->start\n\tn->next\n\tr->run\n\tq->quit\n");
		ft_printf("Use the command twice if it doesn't work, i'm not great.\n");
		return (0);
	}
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '=')
			ft_printf("%s\n", line);
		if (ft_strncmp(line, "Plat", 3) == 0)
		{
			if (usage == 0)
				return (ptab(&line, fd));
			else
				ptab(&line, fd);
			ft_putstr("\n\n\n\n");
		}
		if (!line)
			ft_strdel(&line);
	}
	return (close(fd));
}

int		main(int argc, char **argv)
{
	int		fd;
	int		end;
	char	*command;

	if ((end = readbox(argc, 2)) > 0)
		return (0);
	while (get_next_line(0, &command) > 0)
	{
		if (command[0] == 's' && end == 0)
		{
			fd = open(argv[1], O_RDONLY);
				if (fd == -1)
					return (0);
			end = readbox(fd, end);
		}
		if ((command[0] == 'n' || command[0] == 'r') && end != 1)
			ft_printf("No, can't do!\n");
		if ((command[0] == 'n' || command[0] == 'r') && end == 1)
			end = readbox(fd, (command[0] == 'n') ? 0 : 1);
		if (command[0] == 'q' || end == -1)
		{
			ft_strdel(&command);
			return ((end == 1) ? close(fd) : 0);
		}
		ft_strdel(&command);
	}
}
