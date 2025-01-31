#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

int vread(const char *buffer, char *fmt, ...)
{
   int rc;
   va_list arg_ptr;
   va_start(arg_ptr, fmt);
   rc = vsscanf(buffer, fmt, arg_ptr);
   va_end(arg_ptr);
   return(rc);
}
int main(void)
{
   char *tokenstring = "JP 12 14";
   char * idestring = "ABC Z";
   char ws[81];
   char wc;
   int i;
   float fp;
   char s[81];
   char c;
   /* Input various data */
   /* In the first invocation of vsscanf, the format string is */
   /* "%s %c%d%f". If there were no space between %s and %c, */
   /* vsscanf would read the first character following the */
   /* string, which is a blank space. */
   vread(tokenstring, "%s %c%d%f", s, &c, &i, &fp);
   vread(idestring, "%s %c", ws,&wc);
   /* Display the data */
   printf("\nstring = ");
   puts(s);
   printf("character = %c\n",c);
   printf("integer = %d\n",i);
   printf("floating-point number = %f\n",fp);
   printf("wide-character string = %s\n", ws);
   printf("wide-character = %c\n", wc);
}
/***************** Output should be similar to: *****************
string = 15
character = 1
integer = 2
floating-point number = 14.000000
wide-character string = ABC
wide-character = Z
*******************************************************************/