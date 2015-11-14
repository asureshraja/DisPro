#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "functype.h"
#include "utils.h"
struct job_req{
  int func_type;
  char *module_name;
  char *func_name;
  char *iargs;
};
char *get_ip(char *host);
void execute_function(struct job_req *req);
void send_output(char *);
int split ( char *str, char c, char ***arr);
int split ( char *str, char c, char ***arr)
{
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
            count++;
        p++;
    }

    *arr = (char**) malloc(sizeof(char*) * count);
    if (*arr == NULL)
        exit(1);

    p = str;
    while (*p != '\0')
    {
        if (*p == c)
        {
            (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
            if ((*arr)[i] == NULL)
                exit(1);

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*) malloc( sizeof(char) * token_len );
    if ((*arr)[i] == NULL)
        exit(1);

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0')
    {
        if (*p != c && *p != '\0')
        {
            *t = *p;
            t++;
        }
        else
        {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return count;
}

void * get_function(char * module_name, char * func_name){
  //loading module everytime in a hope that jobs wont come at high velocity
  void * func;void *handle;char *error;
  handle = dlopen (module_name, RTLD_LAZY);
  if (!handle) {
      fputs (dlerror(), stderr);
      exit(1);
  }
  func = dlsym(handle, func_name);
  if ((error = dlerror()) != NULL)  {
      fputs(error, stderr);
      exit(1);
  }
  return func;
}

void send_output(char * output){
  //to write
}

void execute_function(struct job_req *req){
     int functype=req->func_type;char *module_name=req->module_name;char *func_name=req->func_name;char *iargs=req->iargs;
     char** inputs;
     split(iargs, '\r', &inputs);
     printf("%s\n",inputs[0]);printf("%s\n",inputs[1]);
     char *output=malloc(1024);

     switch(functype){
       case VOID_FUNC_VOID:{
                           void* (*func)(void);
                           func=get_function(&module_name[0],&func_name[0]);
                           func();
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_INT: {
                           void* (*func)(int);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(int_from_string(inputs[0]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_INT_CHAR: {
                           void* (*func)(int,char);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(int_from_string(inputs[0]),char_from_string(inputs[1]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_INT_CHARARRAY: {
                           void* (*func)(int,char*);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(int_from_string(inputs[0]),inputs[1]);
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_INT_DOUBLE: {
                           void* (*func)(int,double);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(int_from_string(inputs[0]),double_from_string(inputs[1]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_INT_INT: {
                           void* (*func)(int,int);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(int_from_string(inputs[0]),int_from_string(inputs[1]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_INT_LONG: {
                           void* (*func)(int,long);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(int_from_string(inputs[0]),int_from_string(inputs[1]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_CHAR: {
                           void* (*func)(char);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(char_from_string(inputs[0]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_CHAR_CHAR: {
                           void* (*func)(char,char);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(char_from_string(inputs[0]),char_from_string(inputs[1]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;

       case VOID_FUNC_DOUBLE: {
                           void* (*func)(double);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(double_from_string(inputs[0]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_DOUBLE_CHAR: {
                           void* (*func)(double,char);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(double_from_string(inputs[0]),char_from_string(inputs[1]));
                           strcpy(output,"void");
                           send_output(output);
                           } break;
       case VOID_FUNC_DOUBLE_CHARARRAY: {
                           void* (*func)(double,char*);
                           func=get_function(&module_name[0],&func_name[0]);
                           func(double_from_string(inputs[0]),inputs[1]);
                           strcpy(output,"void");
                           send_output(output);
                           } break;
     case VOID_FUNC_DOUBLE_DOUBLE: {
                         void* (*func)(double,double);
                         func=get_function(&module_name[0],&func_name[0]);
                         func(double_from_string(inputs[0]),double_from_string(inputs[1]));
                         strcpy(output,"void");
                         send_output(output);
                         } break;
     case VOID_FUNC_DOUBLE_LONG: {
                         void* (*func)(double,long);
                         func=get_function(&module_name[0],&func_name[0]);
                         func(double_from_string(inputs[0]),long_from_string(inputs[1]));
                         strcpy(output,"void");
                         send_output(output);
                         } break;

     case VOID_FUNC_LONG: {
                         void* (*func)(long);
                         func=get_function(&module_name[0],&func_name[0]);
                         func(long_from_string(inputs[0]));
                         strcpy(output,"void");
                         send_output(output);
                         } break;
     case VOID_FUNC_LONG_CHAR: {
                         void* (*func)(long,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         func(long_from_string(inputs[0]),char_from_string(inputs[1]));
                         strcpy(output,"void");
                         send_output(output);
                         } break;
     case VOID_FUNC_LONG_CHARARRAY: {
                         void* (*func)(long,char *);
                         func=get_function(&module_name[0],&func_name[0]);
                         func(long_from_string(inputs[0]),inputs[1]);
                         strcpy(output,"void");
                         send_output(output);
                         } break;
     case VOID_FUNC_LONG_LONG: {
                         void* (*func)(long,long);
                         func=get_function(&module_name[0],&func_name[0]);
                         func(long_from_string(inputs[0]),long_from_string(inputs[1]));
                         strcpy(output,"void");
                         send_output(output);
                         } break;
     case VOID_FUNC_CHARARRAY: {
                         void* (*func)(char *);
                         func=get_function(&module_name[0],&func_name[0]);
                         func(inputs[0]);
                         strcpy(output,"void");
                         send_output(output);
                         } break;
     case VOID_FUNC_CHARARRAY_CHARARRAY: {
                         void* (*func)(char *,char *);
                         func=get_function(&module_name[0],&func_name[0]);
                         func(inputs[0],inputs[1]);
                         strcpy(output,"void");
                         send_output(output);
                         } break;
     case INT_FUNC_VOID:{
                          int (*func)(void);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func());
                         send_output(output);
                         } break;
     case INT_FUNC_INT: {
                          int (*func)(int);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(int_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case INT_FUNC_INT_CHAR: {
                          int (*func)(int,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(int_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case INT_FUNC_INT_CHARARRAY: {
                          int (*func)(int,char*);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(int_from_string(inputs[0]),inputs[1]));
                         send_output(output);
                         } break;
     case INT_FUNC_INT_DOUBLE: {
                          int (*func)(int,double);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(int_from_string(inputs[0]),double_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case INT_FUNC_INT_INT: {
                          int (*func)(int,int);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(int_from_string(inputs[0]),int_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case INT_FUNC_INT_LONG: {
                          int (*func)(int,long);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(int_from_string(inputs[0]),int_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case INT_FUNC_CHAR: {
                          int (*func)(char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(char_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case INT_FUNC_CHAR_CHAR: {
                          int (*func)(char,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(char_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;

     case INT_FUNC_DOUBLE: {
                          int (*func)(double);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(double_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case INT_FUNC_DOUBLE_CHAR: {
                          int (*func)(double,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(double_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case INT_FUNC_DOUBLE_CHARARRAY: {
                          int (*func)(double,char*);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_int(func(double_from_string(inputs[0]),inputs[1]));
                         send_output(output);
                         } break;
     case INT_FUNC_DOUBLE_DOUBLE: {
                        int (*func)(double,double);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_int(func(double_from_string(inputs[0]),double_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case INT_FUNC_DOUBLE_LONG: {
                        int (*func)(double,long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_int(func(double_from_string(inputs[0]),long_from_string(inputs[1])));
                       send_output(output);
                       } break;

     case INT_FUNC_LONG: {
                        int (*func)(long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_int(func(long_from_string(inputs[0])));
                       send_output(output);
                       } break;
     case INT_FUNC_LONG_CHAR: {
                        int (*func)(long,char);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_int(func(long_from_string(inputs[0]),char_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case INT_FUNC_LONG_CHARARRAY: {
                        int (*func)(long,char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_int(func(long_from_string(inputs[0]),inputs[1]));
                       send_output(output);
                       } break;
     case INT_FUNC_LONG_LONG: {
                        int (*func)(long,long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_int(func(long_from_string(inputs[0]),long_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case INT_FUNC_CHARARRAY: {
                        int (*func)(char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_int(func(inputs[0]));
                       send_output(output);
                       } break;
     case INT_FUNC_CHARARRAY_CHARARRAY: {
                        int (*func)(char *,char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_int(func(inputs[0],inputs[1]));
                       send_output(output);
                       } break;

     case DOUBLE_FUNC_VOID:{
                         double (*func)(void);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func());
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_INT: {
                         double (*func)(int);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(int_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_INT_CHAR: {
                         double (*func)(int,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(int_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_INT_CHARARRAY: {
                         double (*func)(int,char*);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(int_from_string(inputs[0]),inputs[1]));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_INT_DOUBLE: {
                         double (*func)(int,double);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(int_from_string(inputs[0]),double_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_INT_INT: {
                         double (*func)(int,int);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(int_from_string(inputs[0]),int_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_INT_LONG: {
                         double (*func)(int,long);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(int_from_string(inputs[0]),int_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_CHAR: {
                         double (*func)(char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(char_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_CHAR_CHAR: {
                         double (*func)(char,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(char_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;

     case DOUBLE_FUNC_DOUBLE: {
                         double (*func)(double);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(double_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_DOUBLE_CHAR: {
                         double (*func)(double,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(double_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_DOUBLE_CHARARRAY: {
                         double (*func)(double,char*);
                         func=get_function(&module_name[0],&func_name[0]);
                         output=string_from_double(func(double_from_string(inputs[0]),inputs[1]));
                         send_output(output);
                         } break;
     case DOUBLE_FUNC_DOUBLE_DOUBLE: {
                       double (*func)(double,double);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_double(func(double_from_string(inputs[0]),double_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case DOUBLE_FUNC_DOUBLE_LONG: {
                       double (*func)(double,long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_double(func(double_from_string(inputs[0]),long_from_string(inputs[1])));
                       send_output(output);
                       } break;

     case DOUBLE_FUNC_LONG: {
                       double (*func)(long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_double(func(long_from_string(inputs[0])));
                       send_output(output);
                       } break;
     case DOUBLE_FUNC_LONG_CHAR: {
                       double (*func)(long,char);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_double(func(long_from_string(inputs[0]),char_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case DOUBLE_FUNC_LONG_CHARARRAY: {
                       double (*func)(long,char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_double(func(long_from_string(inputs[0]),inputs[1]));
                       send_output(output);
                       } break;
     case DOUBLE_FUNC_LONG_LONG: {
                       double (*func)(long,long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_double(func(long_from_string(inputs[0]),long_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case DOUBLE_FUNC_CHARARRAY: {
                       double (*func)(char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_double(func(inputs[0]));
                       send_output(output);
                       } break;
     case DOUBLE_FUNC_CHARARRAY_CHARARRAY: {
                       double (*func)(char *,char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output=string_from_double(func(inputs[0],inputs[1]));
                       send_output(output);
                       } break;

     case CHARARRAY_FUNC_VOID:{
                         char* (*func)(void);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func());
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_INT: {
                         char* (*func)(int);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(int_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_INT_CHAR: {
                         char* (*func)(int,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(int_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_INT_CHARARRAY: {
                         char* (*func)(int,char*);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(int_from_string(inputs[0]),inputs[1]));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_INT_DOUBLE: {
                         char* (*func)(int,double);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(int_from_string(inputs[0]),double_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_INT_INT: {
                         char* (*func)(int,int);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(int_from_string(inputs[0]),int_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_INT_LONG: {
                         char* (*func)(int,long);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(int_from_string(inputs[0]),int_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_CHAR: {
                         char* (*func)(char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(char_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_CHAR_CHAR: {
                         char* (*func)(char,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(char_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;

     case CHARARRAY_FUNC_DOUBLE: {
                         char* (*func)(double);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(double_from_string(inputs[0])));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_DOUBLE_CHAR: {
                         char* (*func)(double,char);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(double_from_string(inputs[0]),char_from_string(inputs[1])));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_DOUBLE_CHARARRAY: {
                         char* (*func)(double,char*);
                         func=get_function(&module_name[0],&func_name[0]);
                         output= (char*)(func(double_from_string(inputs[0]),inputs[1]));
                         send_output(output);
                         } break;
     case CHARARRAY_FUNC_DOUBLE_DOUBLE: {
                       char* (*func)(double,double);
                       func=get_function(&module_name[0],&func_name[0]);
                       output= (char*)(func(double_from_string(inputs[0]),double_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case CHARARRAY_FUNC_DOUBLE_LONG: {
                       char* (*func)(double,long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output= (char*)(func(double_from_string(inputs[0]),long_from_string(inputs[1])));
                       send_output(output);
                       } break;

     case CHARARRAY_FUNC_LONG: {
                       char* (*func)(long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output= (char*)(func(long_from_string(inputs[0])));
                       send_output(output);
                       } break;
     case CHARARRAY_FUNC_LONG_CHAR: {
                       char* (*func)(long,char);
                       func=get_function(&module_name[0],&func_name[0]);
                       output= (char*)(func(long_from_string(inputs[0]),char_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case CHARARRAY_FUNC_LONG_CHARARRAY: {
                       char* (*func)(long,char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output= (char*)(func(long_from_string(inputs[0]),inputs[1]));
                       send_output(output);
                       } break;
     case CHARARRAY_FUNC_LONG_LONG: {
                       char* (*func)(long,long);
                       func=get_function(&module_name[0],&func_name[0]);
                       output= (char*)(func(long_from_string(inputs[0]),long_from_string(inputs[1])));
                       send_output(output);
                       } break;
     case CHARARRAY_FUNC_CHARARRAY: {
                       char* (*func)(char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output= (char*)(func(inputs[0]));
                       send_output(output);
                       } break;
     case CHARARRAY_FUNC_CHARARRAY_CHARARRAY: {
                       char* (*func)(char *,char *);
                       func=get_function(&module_name[0],&func_name[0]);
                       output= (char*)(func(inputs[0],inputs[1]));
                       send_output(output);
                       } break;


     }//end of switch

//dont written ptrs from this function
}


char *build_get_query(char *host, char *page)
{
char *query;
char *getpage = page;
char *tpl = "GET /%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";
if(getpage[0] == '/'){
getpage = getpage + 1;
fprintf(stderr,"Removing leading \"/\", converting %s to %s\n", page, getpage);
}
// -5 is to consider the %s %s %s in tpl and the ending \0
query = (char *)malloc(strlen(host)+strlen(getpage)+strlen("distributor")+strlen(tpl)-5+1024);
sprintf(query, tpl, getpage, host, "distributor");
return query;
}

void concatenate_string(char *original, char *add)
{
   while(*original)
      original++;

   while(*add)
   {
      *original = *add;
      add++;
      original++;
   }
   *original = '\0';
}

char *get_ip(char *host)
{
  struct hostent *hent;
  int iplen = 15; //XXX.XXX.XXX.XXX
  char *ip = (char *)malloc(iplen+1);
  memset(ip, 0, iplen+1);
  if((hent = gethostbyname(host)) == NULL)
  {
    herror("Can't get IP");
    exit(1);
  }
  if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL)
  {
    perror("Can't resolve host");
    exit(1);
  }
  return ip;
}

int main(int argc, char **argv) {
  pthread_t threads[4];

   char module_name[50];
   strcpy(module_name,"./libjob.so");
   char func_name[50];
   strcpy(func_name,"hello");
   char iargs[2000];
   strcpy(iargs,"hi hello\rhjkkjkj\r\0");
   char *master_host;
   master_host=malloc(20);
   int optval=1;
   socklen_t optlen = sizeof(optval);
   int master_port=5000;
   int sock_id;
   strcpy(master_host,"localhost");
   int functype=CHARARRAY_FUNC_CHARARRAY;
  // execute_function(functype, &module_name[0], &func_name[0], &iargs[0]);

   struct sockaddr_in remote; //remote address structure
    memset(&remote, 0, sizeof(remote));
   //remote = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in)); //allocating remote address
   remote.sin_family = AF_INET;
   remote.sin_addr.s_addr = inet_addr(get_ip(master_host));
   remote.sin_port=htons(master_port);



    if((sock_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){ //creating tcp socket
      perror("Can't create TCP socket");
      exit(1);
    }


    if(setsockopt(sock_id, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &optval, optlen) < 0) {
       perror("setsockopt()");
       exit(EXIT_FAILURE);
    }
    if(setsockopt(sock_id, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
        perror("setsockopt()");
        exit(EXIT_FAILURE);
    }

    if(connect(sock_id,(struct sockaddr *) &remote, sizeof(struct sockaddr)) < 0){ //connecting to remote address and ataching to socket
      perror("connect error");
    }
    //  flags = fcntl(sock[i], F_GETFL, 0);
//  fcntl(sock[i], F_SETFL, flags | O_NONBLOCK);
  char *get;

  get = build_get_query(master_host, "/");
  concatenate_string(get,"connect");
  char *tempget;int sent = 0; int ret=0;
  tempget=get;int len=strlen(get);
  sent = 0;ret=0;
  while(sent < len)
  {
    ret = send(sock_id, get+sent, len-sent, 0);
    if(ret == -1){
      perror("Can't send query");
      exit(1);
    }
    sent += ret;
  }
  get=tempget;
  // end of send block


  int epfd;
  epfd=epoll_create(10);
  struct epoll_event *events;
  events = malloc (sizeof (struct epoll_event)*10);
  events[0].data.fd = sock_id;
  events[0].events = EPOLLIN;
  ret = epoll_ctl (epfd, EPOLL_CTL_ADD, sock_id, &events[0]);
  printf("%d\n",ret );
  char read_buffer[512*512];
  //char body[512*1024];
  char header_key[100],header_value[100];
  int minor_version;
  size_t read_buffer_length = 0, method_length, path_length, num_headers;
  ssize_t received_bytes; char *method, *path;
  int body_index=0; int headerover=0;
  int header_end=0;
  int nr_events,i,j;char req_body_buffer[1024*1024];
  while (1) {
      nr_events = epoll_wait (epfd, events,1, -1);

      for(i=0;i<nr_events;i++){
        received_bytes=recv(events[i].data.fd, read_buffer, 1024*1024, 0);




        read_buffer[received_bytes]='\0';

        //splitting header and body;
        header_end=received_bytes-4;//header_end is an index to use in read_buffer. 4 indicates \r\n\r\n in http request to split body and header.
        body_index=0;headerover=0;//body array iterator and headerover is a flag to use inside below loop
        for(j=0;j<header_end;j++){
          printf("%c %d\n",read_buffer[j] ,headerover);
          if(read_buffer[j+1]=='\r')
            printf("%s\n","got 1" );
            if(headerover==0){
                if(read_buffer[j]=='\r' && read_buffer[j+1]=='\n' && read_buffer[j+2]=='\r' && read_buffer[j+3]=='\n'){
                    j=j+4;header_end=received_bytes; headerover=1;
                }
            }
            if (headerover==1) {
                req_body_buffer[body_index++]=read_buffer[j];

            }
        }

        //end of splitting header and body. now req_body_buffer holds full data payload in http request.


        //parsing headers
        //num_headers = sizeof(req->headers) / sizeof(req->headers[0]);
      //  phr_parse_request(read_buffer, received_bytes, &method, &method_length, &path, &path_length,&req->minor_version, req->headers, &num_headers, 0);
        //end of parsing headers


        // getting keepalive or not

        // //printf("%s\n",read_buffer );
        // for (j = 0; j != num_headers; j++) {
        //         //printf("%.*s: %.*s\n", (int)headers[j].name_len, headers[j].name,(int)headers[j].value_len, headers[j].value);
        //     sprintf(header_key,"%.*s", (int)req->headers[j].name_len, req->headers[j].name);
        //     sprintf(header_value,"%.*s", (int)req->headers[j].value_len, req->headers[j].value);
        //     if (strcmp(header_key,"Connection")==0) {
        //         if (header_value[0]=='K'||header_value[1]=='K'||header_value[0]=='k'||header_value[1]=='k') {
        //             printf("%s\n","keepalive connection");
        //         }
        //     }
        // }





        printf("%s\n",read_buffer );
        printf("%s\n",&req_body_buffer[0] );
        if (strncmp(req_body_buffer,"YOU",3)==0) {
          printf("%s\n","connected to master" );
        }else if (strcmp(&read_buffer[0], "job\n")==0) {
          struct job_req *job;job= malloc(sizeof(struct job_req));
          char** job_inputs;
          split(&req_body_buffer[0], '\n', &job_inputs);
          if (strcmp(&job_inputs[1][0], "module")==0) {
            job->module_name=&job_inputs[2][0];
            if (strcmp(&job_inputs[3][0], "function")==0) {
              job->func_name=&job_inputs[4][0];
              if (strcmp(&job_inputs[7][0],"type")==0) {
                job->func_type=int_from_string(&job_inputs[6][0]);
                if (strcmp(&job_inputs[7][0], "args")==0) {
                  job->iargs=&job_inputs[8][0];
                  pthread_create( &threads[0], NULL, &execute_function, job);
                }else{
                  free(job);
                  send(sock_id,"failed",6, MSG_NOSIGNAL|MSG_DONTWAIT);
                }
              }else{
                free(job);
                send(sock_id,"failed",6, MSG_NOSIGNAL|MSG_DONTWAIT);
              }
            }else{
              free(job);
              send(sock_id,"failed",6, MSG_NOSIGNAL|MSG_DONTWAIT);
            }
          }else{
            free(job);
            send(sock_id,"failed",6, MSG_NOSIGNAL|MSG_DONTWAIT);
          }
        }
      }

  }


}
