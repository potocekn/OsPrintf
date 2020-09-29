#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//#include "print.h"
void simple_printf(const char* format, ...);
char *convert(unsigned int num, int base);


int main()
{
    puts("[EXPECTED]: This is ONE string.");
    printf("_____________________________\n");
    simple_printf("[ ACTUAL ]: This is %s string.\n", "ONE");
    printf("_____________________________\n");

    puts("[EXPECTED]: This is FIRST and SECOND string.");
    printf("_____________________________\n");
    simple_printf("[ ACTUAL ]: This is %s and %s string.\n", "FIRST", "SECOND");
    printf("_____________________________\n");

    // For completeness, test also printing not "const char*" string
    char buffer[10];
    strncpy(buffer, "Hello", 10);
    puts("[EXPECTED]: Hello, World.");
    printf("_____________________________\n");
    simple_printf("[ ACTUAL ]: %s, World.\n", buffer);
    printf("_____________________________\n");

    // This is actually undefined behaviour but it is probably safer
    // to test for it explicitly...
    puts("[EXPECTED]: This is NULL string: (null).");
    printf("_____________________________\n");
    simple_printf("[ ACTUAL ]: This is NULL string: %s.\n", NULL);
    printf("_____________________________\n");

    printf("Tests for int\n\n");
    puts("[EXPECTED]: This is forty two: 42.");
       simple_printf("[ ACTUAL ]: This is forty two: %d.\n", 42);

       puts("[EXPECTED]: This is minus five: -5.");
       simple_printf("[ ACTUAL ]: This is minus five: %d.\n", -5);

       puts("[EXPECTED]: -2 -1 0 1 2.");
       simple_printf("[ ACTUAL ]: %d %d %d %d %d.\n", -2, -1, 0, 1, 2);

       puts("[EXPECTED]: INT_MIN = -2147483648 ; INT_MAX 2147483647.");
       simple_printf("[ ACTUAL ]: INT_MIN = %d ; INT_MAX %d.\n", INT_MIN, INT_MAX);


     printf("Tests for hex\n\n");
     puts("[EXPECTED]: This is forty two: 2a.");
         simple_printf("[ ACTUAL ]: This is forty two: %x.\n", 42);

         puts("[EXPECTED]: This is minus five: fffffffb.");
         simple_printf("[ ACTUAL ]: This is minus five: %x.\n", -5);

         puts("[EXPECTED]: -2 -1 0 1 2.");
         simple_printf("[ ACTUAL ]: %d %d %d %d %d.\n", -2, -1, 0, 1, 2);

         puts("[EXPECTED]: INT_MIN in hexa: 80000000 ; INT_MIN in hexa: 7fffffff.");
         simple_printf("[ ACTUAL ]: INT_MIN in hexa: %x ; INT_MIN in hexa: %x.\n", 0x80000000, 0x7fffffff);

         puts("[EXPECTED]: Capital letters: 0xABCD.");
         simple_printf("[ ACTUAL ]: Capital letters: 0x%X.\n", 0xabcd);

    return 0;
}


char *convertNumber(unsigned int num, int base, int low)
{
	static char RepresentationUpper[]= "0123456789ABCDEF";
	static char RepresentationLower[]= "0123456789abcdef";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		if (low == 1)
		{
			*--ptr = RepresentationLower[num%base];
		}
		else
		{
			*--ptr = RepresentationUpper[num%base];
		}

		num /= base;
	}while(num != 0);

	return(ptr);
}

void printString(char* s)
{
	if (s == NULL)
	{
		putchar('(');
		putchar('n');
		putchar('u');
		putchar('l');
		putchar('l');
		putchar(')');
	}
	else
	{
		while (*s != '\0')
		{
			putchar(*s);
			s++;
		}
	}
}

void simple_printf(const char* format, ...)
{
    va_list arguments;
    va_start(arguments, format);
    for (char* i = format; *i !='\0'; i++)
    {
        //while there is only ordinary char -> nothing to do -> just write the character and go to next
    	 if (*i != '%') { putchar(*i); continue; }
        //go to next because we are on % char now
        i++;

        //
        if (*i == 'c')
        {
            char c = (char)va_arg(arguments, int);
            putchar(c);
        }
        else if (*i == 'd')
        {
        	int d = va_arg(arguments, int);
        	if (d < 0)
        	{
        		putchar('-');
        		d = (-1)*d;
        	}

        	char * s = convertNumber(d,10,0);
        	printString(s);


        }
        else if (*i == 'x')
        {
        	unsigned int i = va_arg(arguments, unsigned int);
        	char * s = convertNumber(i,16,1);
        	printString(s);

        }
        else if (*i == 'X')
        {
        	unsigned int i = va_arg(arguments, unsigned int);
			char * s = convertNumber(i,16,0);
			printString(s);
        }
        else if (*i == 's')
        {
            char *s = va_arg(arguments, char *);
            printString(s);

        }
        else if (*i == 'p')
        {

        }

    }
    va_end(arguments);


    /*const char* it = format;
    while (*it != '\0') {
        char c = *it;
        putchar(c);
        putchar('\n');
        it++;
    }
    */

}
