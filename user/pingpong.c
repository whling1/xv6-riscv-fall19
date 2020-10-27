#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    int parent_fd[2],child_fd[2];
    char buf[64];
    
    //创建管道函数
    pipe(parent_fd);
    pipe(child_fd);

    if(fork() == 0)  //进入子程序
    {
        close(parent_fd[1]);  //关闭父程序写端
        close(child_fd[0]);   //关闭子程序读端
        write(child_fd[1],"pong",4);
        read(parent_fd[0],buf,sizeof(buf));
        printf("%d: received %s\n",getpid(),buf);
    }
    else   //父程序
    {
        close(parent_fd[0]);  //关闭父程序读端
        close(child_fd[1]);  //关闭子程序写端
        write(parent_fd[1],"ping",4);
        read(child_fd[0],buf,sizeof(buf));
        printf("%d: received %s\n",getpid(),buf);
    }
    exit();
}

