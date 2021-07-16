#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <dlfcn.h>

//! test module to dynamically load openssl
//! and use the sha256 function
//! barrystyle 16072021

int main()
{
	//! load the lib
	void *sha_fnptr;
	sha_fnptr = dlopen("/usr/lib/x86_64-linux-gnu/libssl.so", RTLD_LAZY);
	if (!sha_fnptr) {
		printf("could not load library.\n");
		exit(1);
	}

	//! pass the args
        typedef void (*shaparams)(char *in, int len, char* out);
	shaparams sha_func = (shaparams) dlsym(sha_fnptr, "SHA256");

	//! create dummy buffers
	char fakeheader[80], fakehash[32];
	memset(fakeheader, 0, sizeof(fakeheader));
	memset(fakehash, 0, sizeof(fakehash));

	sha_func(fakeheader, 80, fakehash);

	for (int i=0; i<32; i++) {
		printf("%02hhx", fakehash[i]);
	}
	printf("\n");

	return 0;
}

