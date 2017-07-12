#ifndef FLATGLTF_2_0_GLB_H_INC
#define FLATGLTF_2_0_GLB_H_INC

#include "flatbuffers/flatbuffers.h"
#include <cctype>
#include <string>
#include <vector>

namespace glTF_2_0
{
	MANUALLY_ALIGNED_STRUCT(4) GLBHeader
	{
		/// magic equals 0x46546C67. It is ASCII string 'glTF', and can be used to identify data as Binary glTF.
		static constexpr uint32_t MAGIC = 0x46546C67;
		uint32_t				  magic = MAGIC;

		/// version indicates the version of the Binary glTF container format. This specification defines version 2.
		static constexpr uint32_t VERSION = 2;
		uint32_t				  version = VERSION;

		/// length is the total length of the Binary glTF, including Header and all Chunks, in bytes.
		uint32_t length;
	};
	static_assert(sizeof(GLBHeader) == 12, "glB header is not 12 bytes");

	MANUALLY_ALIGNED_STRUCT(4)
	GLBChunkHeader
	{
		static constexpr uint32_t JSON = 0x4E4F534A;
		static constexpr uint32_t BIN  = 0x004E4942;

		/// chunkLength is the length of chunkData, in bytes.
		/// NOTE: must be modulo 4
		uint32_t chunkLength;

		/// chunkType indicates the type of chunk. See Table 1 for details.
		/// chunkType equals 0x4E4F534A, ASCII string 'JSON'
		/// chunkType equals 0x004E4942	, ASCII string 'BIN'
		uint32_t chunkType;
	};

}	// namespace glTF_2_0
#endif	// !FLATGLTF_2_0_GLB_H_INC
