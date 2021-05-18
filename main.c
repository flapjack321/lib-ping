#include <stdio.h>
#include "ping.h"

int main(int argc, char *argv[])
{
	fprintf(stderr, "running ping on argv\n");
	return ping(argc, argv);
}
