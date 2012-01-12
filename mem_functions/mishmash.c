/* DO use memmove() instead of memcpy() in case you're dealing with overlapping memory regions.
DON'T try to use memset() to initialize type int, float, or double arrays to any value other than 0. 
DO use memset to initalize a char array to any 0-255 character. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	char message1[] = "0123456789";
	char message2[] = "abcdefghij";
	char temp[10];
	char *p_c;
	
	printf("temp (local variable) before memset: %s\n", temp);
	memset(temp, '\0', sizeof(temp));
	printf("temp (local variable) after memset: %s\n", temp);
	
	/* p_c points at char '3' in message 1 */
	p_c = message1 + 3;
	
#ifdef MEMCPY
	/* copy "01234" from message1 onto p_c which starts at '3' in message1 */
	/* "34" overlap */
	memcpy(p_c, message1, 5);
	
	printf("printout after mempcpy with overlap: %s\n", p_c);
#else
	/* guarantees copy even if overlap */
	memmove(p_c, message1, 5);
	
	printf("printout after memmove with overlap: %s\n", p_c);
#endif
	exit(0);	
}