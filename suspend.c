#include <windows.h>
#include <powrprof.h>
#include <stdio.h>

int main() {
	BOOLEAN ret = SetSuspendState(0, 0, 0);
	printf("SetSuspendState ret: %d\n", ret);
}
