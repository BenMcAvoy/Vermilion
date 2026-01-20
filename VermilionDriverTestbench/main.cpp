#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <print>

int main() {
    wchar_t buffer[256];
    DWORD size = sizeof(buffer);

    LONG res = RegGetValueW(
        HKEY_LOCAL_MACHINE,
        L"Software\\Vermilion",
        L"DriverName",
        RRF_RT_REG_SZ,
        nullptr,
        buffer,
        &size
    );

    if (res != ERROR_SUCCESS) {
		std::println("RegGetValueW failed with error code: {}", res);
        return 1;
    }

    std::wstring driverName(buffer);
	std::string driverNameStr(driverName.begin(), driverName.end());

	std::println("Driver Name: {}", driverNameStr);

	return 0;
}