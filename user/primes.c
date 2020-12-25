#include "kernel/types.h"
#include "user/user.h"

void prime()
{
    int fp[2];
    int p;
    int n;

    if(read(0,&p,sizeof(p)))
    {
        printf("prime %d\n", p);   //打印第一个数，即素数
        pipe(fp);
        if(fork() == 0)
        {
            close(1);
            dup(fp[1]);
            close(fp[0]);
            close(fp[1]);
            // printf("divide q before\n");
            while(read(0,&n,sizeof(n)))
            {
                if(n % p != 0)
                {
                    write(1,&n,sizeof(n));
                }
            }
            //printf("divide q after\n");
            
        }
        else
        {
            close(0);
            dup(fp[0]);
            close(fp[0]);
            close(fp[1]);
            prime();  //递归
            //printf("digui11111111111\n");
           
        }

    }
}

int 
main()
{
    int fp[2];
    pipe(fp);
    int i;

    if(fork() == 0)
    {
        close(1);
        dup(fp[1]);
        close(fp[0]);
        close(fp[1]);
        for(i=2;i<36;i++)
        {
            write(1,&i,sizeof(i));
        }
        
    }
    else
    {
        close(0);
        dup(fp[0]);
        close(fp[0]);
        close(fp[1]);
        prime();
       
    }
    
    exit();
}