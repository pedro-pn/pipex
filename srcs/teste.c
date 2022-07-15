#include "pipex.h"
#include "fcntl.h"

int main(void)
{
	char *com[] = {"/usr/bin/grep", "Gatinhos", NULL};
	int	fd[2];
	int id;
	char y[200];
	char buff[1];
	int i;

	pipe(fd);
	i = 0;
	id = fork();
	if (id == 0)
	{
		int new_fd = open("teste", O_RDONLY);
		close(fd[0]);
		dup2(fd[1], 1);
		dup2(new_fd, 0);
		close(new_fd);
		close(fd[1]);
		execve(com[0], com, NULL);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		while (read(fd[0], &buff, sizeof(*y)) > 0)
		{
			y[i] = *buff;
			i++;
		}
	//	y[14] = 0;
		ft_printf("%s", y);
	}
	return (0);
}