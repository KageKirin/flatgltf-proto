//! test fot flatgltf / glTF 1.0 loading

#include "flatgltf/1.0/glTF.hxx"
#include "flatgltf/1.0/glTF_generated.h"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#include "catch.hpp"

#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << argv[0] << " <file>.gltf" << std::endl;
		return -1;
	}

	std::string gltfFileContents;
	bool		gotFile = flatbuffers::LoadFile(argv[1], false, &gltfFileContents);

	if (!gotFile)
	{
		std::cerr << argv[1] << " does not seem to exist" << std::endl;
		return -1;
	}


	flatbuffers::Parser parser;
	bool				schemaOk = parser.Parse(flatgltf_1_0_schema.c_str(), nullptr, "glTF.fbs");
	if (!schemaOk)
	{
		std::cerr << "schema error: " << parser.error_ << std::endl;
		return 1;
	}

	bool gltfOk = parser.Parse(gltfFileContents.c_str(), nullptr, argv[1]);
	if (!gltfOk)
	{
		std::cerr << "json error: " << parser.error_ << std::endl;
		return 2;
	}

	std::cout << "gltf json file could be loaded" << std::endl;
	return 0;
}
