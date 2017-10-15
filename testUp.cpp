#include <memory>

int main()
{
	const char* data = "sadasd";
	auto upBuf = std::unique_ptr(data, &std::free);

	return 0;
}
