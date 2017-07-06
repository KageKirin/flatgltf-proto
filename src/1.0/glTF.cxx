#include <string>

extern const std::string flatgltf_1_0_schema; // for linker happiness
const std::string flatgltf_1_0_schema =
std::string(R"(
table glTF {
	foobar: int;
})") +
"";
