#include "driver.h"

extern "C" NTSTATUS NTAPI IoCreateDriver(PUNICODE_STRING DriverName, PDRIVER_INITIALIZE InitializationFunction);

extern "C" NTSTATUS DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	LOG_INFO("VermilionDriver DriverEntry called");

	WCHAR driverNameBuf[64];
	ULONG64 count = __rdtsc();
	swprintf(driverNameBuf, L"\\Driver\\VermilionDriver_%llu", count);
	UNICODE_STRING driverName = RTL_CONSTANT_STRING(driverNameBuf);

	UNICODE_STRING keyPath;
	RtlInitUnicodeString(&keyPath, L"\\Registry\\Machine\\Software\\Vermilion");

	OBJECT_ATTRIBUTES oa{};
	InitializeObjectAttributes(
		&oa,
		&keyPath,
		OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
		nullptr,
		nullptr
	);

	HANDLE hKey;
	NTSTATUS status = ZwCreateKey(
		&hKey,
		KEY_ALL_ACCESS,
		&oa,
		0,
		nullptr,
		REG_OPTION_NON_VOLATILE,
		nullptr
		);

	if (!NT_SUCCESS(status)) {
		LOG_ERROR("ZwCreateKey failed: 0x%X", status);
		return status;
	}

	UNICODE_STRING valueName;
	RtlInitUnicodeString(&valueName, L"DriverInstanceName");

	SIZE_T byteSize = (driverName.Length + sizeof(WCHAR));

	status = ZwSetValueKey(
		hKey,
		&valueName,
		0,
		REG_SZ,
		driverName.Buffer,
		static_cast<ULONG>(byteSize)
	);

	if (!NT_SUCCESS(status)) {
		LOG_ERROR("ZwSetValueKey failed: 0x%X", status);
		ZwClose(hKey);
		return status;
	}

	ZwClose(hKey);

	NTSTATUS createRes = IoCreateDriver(
		&driverName,
		VermilionDriver::MainEntryPoint
	);

	if (!NT_SUCCESS(createRes)) {
		LOG_ERROR("IoCreateDriver failed: 0x%X", createRes);
		return createRes;
	}

	LOG_INFO("VermilionDriver loaded successfully");
	return STATUS_SUCCESS;
}