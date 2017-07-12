#include "flatgltf/2.0/glTF_internal_types.h"
#include "flatgltf/2.0/glTF_generated.h"

#include <algorithm>
#include <cassert>	//TODO: improve using catch later
#include <memory>
#include <string>
#include <vector>

extern const std::string flatgltf_2_0_schema;	// for linker happiness

namespace glTF_2_0
{
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	std::string to_json(const Root_t& instance)
	{
		flatbuffers::Parser parser;
		bool				parseOk = parser.Parse(flatgltf_2_0_schema.c_str(), nullptr, "glTF_2.0.fbs");
		assert_msg(parseOk, parser.error_.c_str());
		if (!parseOk)
		{
			return parser.error_;
		}

		std::string jsongen;
		auto		root = CreateglTF(instance.get(), parser.builder_);
		GenerateText(parser, parser.builder_.GetBufferPointer(), &jsongen);
		return jsongen;
	}

	//-------------------------------------------------------------------------

	Root_t from_json(const std::string& json)
	{
		flatbuffers::Parser parser;
		bool				parseOk = parser.Parse(flatgltf_2_0_schema.c_str(), nullptr, "glTF_2.0.fbs");
		assert_msg(parseOk, parser.error_.c_str());
		if (!parseOk)
		{
			return Root_t();
		}

		parseOk = parseOk && parser.Parse(json);
		assert_msg(parseOk, parser.error_.c_str());
		if (!parseOk)
		{
			return Root_t();
		}

		auto root = flatbuffers::GetRoot<glTF>(parser.builder_.GetBufferPointer());
		return Root_t{root.UnPack()};
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	std::vector<uint8_t> to_flatbuffer(const Root_t& instance)
	{
		flatbuffers::FlatBufferBuilder builder_;
		auto						   root = CreateglTF(instance.get(), builder_);

		return std::vector<uint8_t>{builder_.GetBufferPointer(), builder_.GetBufferPointer() + builder_.GetrSize()};
	}

	//-------------------------------------------------------------------------

	Root_t from_flatbuffer(const std::vector<uint8_t>& buffer)
	{
		auto root = flatbuffers::GetRoot<glTF>(buffer.data());
		return Root_t{root.UnPack()};
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
