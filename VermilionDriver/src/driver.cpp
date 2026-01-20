#include "driver.h"

NTSTATUS VermilionDriver::MainEntryPoint(PDRIVER_OBJECT pDriver, PUNICODE_STRING regPath) {
	UNREFERENCED_PARAMETER(pDriver);
	UNREFERENCED_PARAMETER(regPath);

	LOG_INFO("VermilionDriver loaded.");

	return STATUS_SUCCESS;
}