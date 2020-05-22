/* 测试是否能够自动恢复被中断的系统调用 */
/*  这里客户端输入 ctrl+d 后关闭到server的连接
    然后ser这里的子进程退出,自动发送SIGCHLD到父进程来回收子进程,
    这里会中断下accept的系统调用,linux下能够自动恢复
    --配合的客户端程序为tcpcli01
*/

#include	"unp.h"


void
sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		printf("child %d terminated\n", pid);
	}
	return;
}


int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	int on=1;
	if((setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)
	{
		perror("setsockopt failed");
		exit(EXIT_FAILURE);
	}

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);
    signal(SIGCHLD,sig_chld);       // linux下这个系统调用被中断会恢复,accept不会出错
    // Signal(SIGCHLD,sig_chld);   //两个进程都可收到这个信号,但是这里只有父进程会,
    //                             //他会回收子进程,然后中断accept

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		connfd = Accept(listenfd, (SA *) &cliaddr, &clilen);

		if ( (childpid = Fork()) == 0) {	/* child process */
			Close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process the request */
			exit(0);
		}
		Close(connfd);			/* parent closes connected socket */
	}
}
