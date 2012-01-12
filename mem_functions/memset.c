/* memset example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] = "almost every programmer should know memset!";
  /* second argument is an int, but the function uses converts it to unsigned char */
  /* thus it takes values from 0-255 (eg. if you put 257, you'll get the effect of 2) */
  memset (str, '-', 6);
  puts (str);
  return 0;
}