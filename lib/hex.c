/* Convert hex values to string.
* I refered the code in https://codereview.stackexchange.com/questions/30579/integer-to-hex-string-generator
*/

#include <misc.h>

size_t num_hex_digits(size_t n)
{
	int ret=0;
	if(n==0)return 1;
	while(n!=0){
		n >>= 4;
		ret++;
	}
	return ret;
}

void itoh(size_t n,char* s)
{
	int len=num_hex_digits(n);
	const char hex_lookup[]="0123456789ABCDEF";

	if(len & 1){
		*s++ = '0';
	}
	s[len]='\0';
	for(--len; len>=0; n>>= 4, --len){
		s[len]=hex_lookup[n & 0xF];
	}
}

