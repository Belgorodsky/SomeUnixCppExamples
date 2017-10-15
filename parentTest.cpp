#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h> 

#include <experimental/filesystem>
#include <string>

int main(int argc, char *argv[])
{
	auto command = std::experimental::filesystem::canonical("/Users/Yarique/childTest");
	std::string stdin_message = 1 < argc ? argv[1] : "test";

	printf("child path: %s\n", command.c_str());

	pid_t pid;

	int stdin_pipe_fds[2];
	int stdout_pipe_fds[2];
	pipe(stdin_pipe_fds);
	pipe(stdout_pipe_fds);

	// write child stdin
	FILE* child_stdin = fdopen(stdin_pipe_fds[1], "w");
	fprintf(child_stdin, "%s", stdin_message.c_str());
	fclose(child_stdin);


	std::string arg = "some";
	// get FILE* to child stdout

		char buf[512] = { 0 };
	FILE *child_out = fdopen(stdout_pipe_fds[0], "r");

	/* child process */
	if ((pid = fork()))
	{

		int stat;

		while (waitpid(pid, &stat, 0) == -1)
		{
			if (errno != EINTR)
			{
				stat = -1;
				break;
			}
		}

		int fd = fileno(child_out);  
		int flags = fcntl(fd, F_GETFL, 0); 
		flags |= O_NONBLOCK; 
		fcntl(fd, F_SETFL, flags); 

		printf("child stdout: ");
		while( 0 < read(fd, buf, sizeof(buf)) )
		{
			printf("%s", buf);
			memset(buf, 0, sizeof(buf));
		}
		printf("\n");
		fclose(child_out);
		return stat;
	}
	else
	{
		// read stdin from message written to stdin_pipe_fds[1]
		close(STDIN_FILENO);
		dup2(stdin_pipe_fds[0], STDIN_FILENO);
		close(stdin_pipe_fds[1]);
		close(stdin_pipe_fds[0]);
			
		// forward stdout to stdout_pipe_fds[1]
		close(STDOUT_FILENO);
		dup2(stdout_pipe_fds[1], STDOUT_FILENO);
		close(stdout_pipe_fds[1]);
		close(stdout_pipe_fds[0]);

		execl(command.c_str(), command.c_str(), arg, nullptr);
		exit(0);
	}

}
