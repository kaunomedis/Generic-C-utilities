/* minimal "driver" for windows 64bit system. Visual Studio required. Just to test. */

#define _AMD64_
#include <wdm.h>

NSTATUS DriverEntry(void * a, void * b) {
	DbgPrint("Hello world");
	return STATUS_SUCCESS;
}
