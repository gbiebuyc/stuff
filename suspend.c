//
// cc file.c -lpowrprof
//

#include <windows.h>
#include <powrprof.h>
#include <stdio.h>

int main() {
	OpenClipboard(NULL);
	EmptyClipboard();
	CloseClipboard();
	BOOLEAN ret = SetSuspendState(0, 0, 0);
	printf("SetSuspendState ret: %d\n", ret);
}
