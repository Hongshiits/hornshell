/*
** file name CException.h
*/
#ifndef _CEXCEPTION_H_
#define _CEXCEPTION_H_
#include <setjmp.h>
#include <stdlib.h>
#include <stdarg.h>
#include <execinfo.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
typedef struct Except_frame
{
    jmp_buf env;
    int flag;
    void clear()
    {
       flag = 0;
       bzero(env,sizeof(env));
    }
    bool isDef()
    {
       return flag;
    }
    Except_frame()
    {
      clear();
    }
}Except_frame;
extern Except_frame* except_stack;
extern void errorDump();
extern void recvSignal(int sig);
Except_frame* except_stack = new Except_frame;
void errorDump()
{
    const int maxLevel = 200;
    void* buffer[maxLevel];
    int level = backtrace(buffer, maxLevel);
    const int SIZE_T = 1024;
    char cmd[SIZE_T] = "addr2line -C -f -e ";
    char* prog = cmd + strlen(cmd);
    readlink("/proc/self/exe", prog, sizeof(cmd) - (prog-cmd)-1);
    FILE* fp = popen(cmd, "w");
    if (!fp)
    {
        perror("popen");
        return;
    }
    for (int i = 0; i < level; ++i)
    {
        fprintf(fp, "%p\n", buffer[i]);
    }
    fclose(fp);
}
 
void recvSignal(int sig)
{
    printf("received signal %d !!!\n",sig);
    errorDump();
    siglongjmp(except_stack->env,1);
}
#define TRY \
    except_stack->flag = sigsetjmp(except_stack->env,1);\
    if(!except_stack->isDef()) \
    { \
      signal(SIGSEGV,recvSignal); \
      //printf("start use TRY\n");
#define END_TRY \
    }\
    else\
    {\
      except_stack->clear();\
    }\
    //printf("stop use TRY\n");
#define RETURN_NULL \
    } \
    else \
    { \
      except_stack->clear();\
    }\
    return NULL;
#define RETURN_PARAM  { \
      except_stack->clear();\
    }\
    return x;
#define EXIT_ZERO \
    }\
    else \
    { \
      except_stack->clear();\
    }\
    exit(0);
#endif
//————————————————
//版权声明：本文为CSDN博主「归来已是客」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/work_msh/article/details/8470277