#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int 
main(int argc,char *argv[])
{
    int i=0,j=0,k=0,l=0,m=0;
    char buf[MAXARG];
    char block[MAXARG];
    char *p = buf;
    char *split[MAXARG];

    for(i=1;i<argc;i++){
        split[j++] = argv[i];
    }

    while ((k=read(0,block,sizeof(block)))>0)   //该行有内容
    {
        /* code */
        for(l = 0;l<k;l++)
        {
            if(block[l] == '\n')  //该行结束
            {
                buf[m] = 0;
                m = 0;   //一行结束，m恢复为0，方便下次buf记录
                split[j++] = p;      //记录一行中的最后一块字符串
                p = buf;       //p指针从buf的开始段开始记录
                split[j] = 0;  //exec接收的最后一个参数必须为0
                j = argc - 1;
                if (strcmp(split[j],"ctrl-d") == 0)   //如果碰到ctrl-d则退出
                {
                    exit();
                }
                
                if(fork() == 0)
                {
                    exec(argv[1],split);
                }
                wait();

            }
            else if(block[l] == ' ')
            {
                buf[m++] = 0;
                split[j++] = p;  //记录一行命令中的一块字符串
                p = &buf[m];   //p指针重新开始记录以buf[m]开始的字符
            }
            else 
            {
                buf[m++] = block[l];
            } 
        }
    }
    exit();
    
}