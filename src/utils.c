#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
int int_from_string(char *str){
  return atoi(str);
}
char char_from_string(char *str){
  return str[0];
}
double double_from_string(char *str){
  double val;
  sscanf(str, "%lf", &val);
  return val;
}
long int long_from_string(char *str){
  long int val;
  sscanf(str, "%lu", &val);
  return val;
}


char* string_from_int(int val){
  char *str=malloc(15);
  sprintf(str, "%d", val);
  return &str[0];
}
char* string_from_long(long val){
  char *str=malloc(15);
  sprintf(str, "%lu", val);
  return &str[0];
}
char* string_from_double(double val){
  char *str=malloc(15);
  sprintf(str, "%lf", val);
  return &str[0];
}
char* string_from_char(char val){
  char *str=malloc(2);
  sprintf(str, "%c", val);
  return &str[0];
}
