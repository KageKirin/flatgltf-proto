#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"

#include <algorithm>
#include <cassert>	//TODO: improve using catch later
#include <memory>
#include <string>
#include <vector>

// flatbuffer schema string for parser
extern const std::string flatgltf_2_0_schema;

namespace glTF_2_0
{
	using namespace detail;

	///------------------------------------------------------------------------
	/// types for GLB files
	///------------------------------------------------------------------------

	MANUALLY_ALIGNED_STRUCT(4) GLBHeader
	{
		/// magic equals 0x46546C67. It is ASCII string 'glTF', and can be used to identify data as Binary glTF.
		uint32_t magic = GLBConstant::magic;

		/// version indicates the version of the Binary glTF container format. This specification defines version 2.
		uint32_t version = GLBConstant::version;

		/// length is the total length of the Binary glTF, including Header and all Chunks, in bytes.
		uint32_t length;
	};
	static_assert(sizeof(GLBHeader) == 12, "GLBHeader is not 12 bytes");

	MANUALLY_ALIGNED_STRUCT(4) GLBChunkHeader
	{
		/// chunkLength is the length of chunkData, in bytes.
		/// NOTE: must be modulo 4
		uint32_t chunkLength;

		/// chunkType indicates the type of chunk. See Table 1 for details.
		/// chunkType equals 0x4E4F534A, ASCII string 'JSON' -> GLBConstant::json
		/// chunkType equals 0x004E4942	, ASCII string 'BIN' -> GLBConstant::binary
		uint32_t chunkType;
	};
	static_assert(sizeof(GLBChunkHeader) == 8, "GLBChunkHeader is not 8 bytes");


	///------------------------------------------------------------------------
	/// JSON serialization/deserialization
	///------------------------------------------------------------------------

	static std::string to_json(const Root_t& instance)
	{
		flatbuffers::Parser parser;
		bool				parseOk = parser.Parse(flatgltf_2_0_schema.c_str(), nullptr, "glTF_2.0.fbs");
		assert_msg(parseOk, parser.error_.c_str());
		if (!parseOk)
		{
			return parser.error_;
		}

		std::string jsongen;
		auto		root = CreateRoot(instance.get(), parser.builder_);
		GenerateText(parser, parser.builder_.GetBufferPointer(), &jsongen);
		return jsongen;
	}

	//---

	static Root_t from_json(const std::string& json)
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

		auto root = flatbuffers::GetRoot<Root>(parser.builder_.GetBufferPointer());
		return Root_t{root.UnPack()};
	}

	///------------------------------------------------------------------------
	/// flatbuffer marshalling/unmarshalling
	///------------------------------------------------------------------------

	static std::vector<uint8_t> to_flatbuffer(const Root_t& instance)
	{
		flatbuffers::FlatBufferBuilder builder_;
		auto						   root = CreateRoot(instance.get(), builder_);

		return std::vector<uint8_t>{builder_.GetBufferPointer(), builder_.GetBufferPointer() + builder_.GetrSize()};
	}

	//---

	static Root_t from_flatbuffer(const std::vector<uint8_t>& buffer)
	{
		auto root = flatbuffers::GetRoot<Root>(buffer.data());
		return Root_t{root.UnPack()};
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool load_glTFData_buffer(glTF_Object* cntr, const std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		std::string json(reinterpret_cast<const char*>(buffer.data()), buffer.size());
		cntr->root = from_json(json);
		return true;
	}

	//---

	std::vector<uint8_t> save_glTFData_buffer(const glTF_Object* cntr)
	{
		assert(cntr);
		auto json = to_json(cntr->root);
		return std::vector<uint8_t>{reinterpret_cast<const uint8_t*>(&*json.begin()),
									reinterpret_cast<const uint8_t*>(&*json.end())};
	}

	//-------------------------------------------------------------------------

	bool load_glTFData_binary_buffer(glTF_Object* cntr, const std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		assert(!buffer.empty());
		if (buffer.empty())
		{
			return false;
		}

		const GLBHeader& header = *reinterpret_cast<const GLBHeader*>(&*buffer.begin());
		assert(header.magic == GLBConstant::magic);
		assert(header.version == GLBConstant::version);
		assert(header.length == buffer.size());

		const GLBChunkHeader& jsChunk = *reinterpret_cast<const GLBChunkHeader*>(&*(buffer.begin() + sizeof(GLBHeader)));
		assert(jsChunk.chunkType == GLBConstant::json);
		assert(jsChunk.chunkLength >= 4);
		assert((jsChunk.chunkLength % 4) == 0);

		std::string jsonString(reinterpret_cast<const char*>(&*(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader))));
		assert(!jsonString.empty());

		cntr->root = from_json(jsonString);

		// check if there's more data, i.e. binary chunk
		if (header.length > sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength)
		{
			const GLBChunkHeader& binChunk = *reinterpret_cast<const GLBChunkHeader*>(
			  &*(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength));
			assert(binChunk.chunkType == GLBConstant::binary);
			assert(binChunk.chunkLength >= 4);
			assert((binChunk.chunkLength % 4) == 0);

			cntr->bindata["binary"].reserve(binChunk.chunkLength);
			std::copy(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength + sizeof(GLBChunkHeader),
					  buffer.end(),
					  std::back_inserter(cntr->bindata["binary"]));
		}

		return true;
	}

	//---

	std::vector<uint8_t> save_glTFData_binary_buffer(const glTF_Object* cntr)
	{
		assert(cntr);
		auto jsonString = to_json(cntr->root);
		jsonString.resize(jsonString.size() + jsonString.size() % 4, 0x20);	// pad to alignment with spaces

		size_t bindataSize = std::accumulate(cntr->bindata.begin(), cntr->bindata.end(), size_t(0), [](size_t sum, auto& kvp) {
			return sum + kvp.second.size() + kvp.second.size() % 4;	// pad to alignment with 0
		});

		std::vector<uint8_t> buffer;
		buffer.reserve(sizeof(GLBHeader) + 2 * sizeof(GLBChunkHeader) + jsonString.size() + bindataSize);

		GLBHeader header;
		assert(header.magic == GLBConstant::magic);
		assert(header.version == GLBConstant::version);
		header.length = buffer.size();

		GLBChunkHeader jsChunk{jsonString.size(), GLBConstant::json};
		GLBChunkHeader binChunk{bindataSize, GLBConstant::binary};

		auto bi = std::back_inserter(buffer);
		std::copy_n(reinterpret_cast<const uint8_t*>(&header), sizeof(GLBHeader), bi);
		std::copy_n(reinterpret_cast<const uint8_t*>(&jsChunk), sizeof(GLBChunkHeader), bi);
		std::transform(jsonString.begin(), jsonString.end(), bi, [](auto& c) { return static_cast<uint8_t>(c); });
		std::copy_n(reinterpret_cast<const uint8_t*>(&binChunk), sizeof(GLBChunkHeader), bi);
		std::for_each(cntr->bindata.begin(), cntr->bindata.end(), [&bi](auto& kvp) {
			std::copy(kvp.second.begin(), kvp.second.end(), bi);
			std::fill_n(bi, kvp.second.size() % 4, 0x0);	// pad to alignment with 0
		});

		assert(!buffer.empty());
		return buffer;
	}

	//-------------------------------------------------------------------------

	bool load_glTFData_flat_buffer(glTF_Object* cntr, const std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		cntr->root = from_flatbuffer(buffer);
		return true;
	}

	//---

	std::vector<uint8_t> save_glTFData_flat_buffer(const glTF_Object* cntr)
	{
		assert(cntr);
		return to_flatbuffer(cntr->root);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------


	typedef bool (*_glTFData_load_buffer_t)(glTF_Object&, cntr std::vector<uint8_t>&);

	static bool _load_file(glTF_Object* cntr, FILE* file, _glTFData_load_buffer_t loader)
	{
		assert(cntr);
		std::vector<uint8_t> buffer;
		auto				 bi = std::back_inserter(buffer);
		while (file && !feof(file))
		{
			*bi++ = fgetc(file);
		}
		return loader(cntr, buffer);
	}

	//---

	static bool _load_uri(glTF_Object* cntr, const char* uri, _glTFData_load_buffer_t loader)
	{
		assert(cntr);
		auto file = std::unique_ptr<FILE, decltype(&fclose)>(fopen(uri, "rb"), fclose);
		return _load_file(cntr, file.get(), loader);
	}

	//---

	static bool _load_stream(glTF_Object* cntr, std::istream& ins, _glTFData_load_buffer_t loader)
	{
		assert(cntr);
		std::vector<uint8_t> buffer;
		auto				 bi = std::back_inserter(buffer);
		while (ins)
		{
			char c;
			ins.read(&c, 1);
			*bi++ = c;
		}
		return loader(cntr, buffer);
	}

	//---
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool load_glTFData(glTF_Object* cntr, const char* uri)
	{
		assert(cntr);
		return _load_uri(cntr, uri, load_glTFData_buffer);
	}

	//---

	bool load_glTFData(glTF_Object* cntr, FILE* file)
	{
		assert(cntr);
		return _load_file(cntr, file, load_glTFData_buffer);
	}

	//---

	bool load_glTFData(glTF_Object* cntr, std::istream& ins)
	{
		assert(cntr);
		return _load_stream(cntr, ins, load_glTFData_buffer);
	}

	//---

	bool load_glTFData(glTF_Object* cntr, const std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		return load_glTFData_buffer(cntr, buffer);
	}

	//---
	//---

	bool load_glTFData_binary(glTF_Object* cntr, const char* uri)
	{
		assert(cntr);
		return _load_uri(cntr, uri, load_glTFData_binary_buffer);
	}

	//---

	bool load_glTFData_binary(glTF_Object* cntr, FILE* file)
	{
		assert(cntr);
		return _load_file(cntr, file, load_glTFData_binary_buffer);
	}

	//---

	bool load_glTFData_binary(glTF_Object* cntr, std::istream& ins)
	{
		assert(cntr);
		return _load_stream(cntr, ins, load_glTFData_binary_buffer);
	}

	//---

	bool load_glTFData_binary(glTF_Object* cntr, const std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		return load_glTFData_binary_buffer(cntr, buffer);
	}

	//---
	//---

	bool load_glTFData_flat(glTF_Object* cntr, const char* uri)
	{
		assert(cntr);
		return _load_uri(cntr, uri, load_glTFData_flat_buffer);
	}

	//---

	bool load_glTFData_flat(glTF_Object* cntr, FILE* file)
	{
		assert(cntr);
		return _load_file(cntr, file, load_glTFData_flat_buffer);
	}

	//---

	bool load_glTFData_flat(glTF_Object* cntr, std::istream& ins)
	{
		assert(cntr);
		return _load_stream(cntr, ins, load_glTFData_flat_buffer);
	}

	//---

	bool load_glTFData_flat(glTF_Object* cntr, const std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		return load_glTFData_flat_buffer(cntr, buffer);
	}

	//---
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	static bool _save_file(FILE* file, const std::vector<uint8_t>& buffer)
	{
		if (file)
		{
			auto written = fwrite(buffer.data(), buffer.size(), 1, file);
			return written == buffer.size();
		}
		return false;
	}

	//---

	static bool _save_uri(const char* uri, const std::vector<uint8_t>& buffer)
	{
		auto file = std::unique_ptr<FILE, decltype(&fclose)>(fopen(uri, "wb"), fclose);
		return _save_file(file.get(), buffer);
	}

	//---

	static bool _save_stream(std::ostream& outs, const std::vector<uint8_t>& buffer)
	{
		if (outs)
		{
			outs.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
			auto written = outs.tellp();
			return written == buffer.size();
		}
		return false;
	}

	//---
	//---

	bool save_glTFData(const glTF_Object* cntr, const char* uri)
	{
		assert(cntr);
		return _save_uri(uri, save_glTFData_buffer(cntr));
	}

	//---

	bool save_glTFData(const glTF_Object* cntr, FILE* file)
	{
		assert(cntr);
		return _save_file(file, save_glTFData_buffer(cntr));
	}

	//---

	bool save_glTFData(const glTF_Object* cntr, std::ostream& outs)
	{
		assert(cntr);
		return _save_stream(outs, save_glTFData_buffer(cntr));
	}

	//---

	bool save_glTFData(const glTF_Object* cntr, std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		buffer = save_glTFData_buffer(cntr);
		return true;
	}

	//---
	//---

	bool save_glTFData_binary(const glTF_Object* cntr, const char* uri)
	{
		assert(cntr);
		return _save_uri(uri, save_glTFData_binary_buffer(cntr));
	}

	//---

	bool save_glTFData_binary(const glTF_Object* cntr, FILE* file)
	{
		assert(cntr);
		return _save_file(file, save_glTFData_binary_buffer(cntr));
	}

	//---

	bool save_glTFData_binary(const glTF_Object* cntr, std::ostream& outs)
	{
		assert(cntr);
		return _save_stream(outs, save_glTFData_binary_buffer(cntr));
	}

	//---

	bool save_glTFData_binary(const glTF_Object* cntr, std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		buffer = save_glTFData_binary_buffer(cntr);
		return true;
	}

	//---
	//---

	bool save_glTFData_flat(const glTF_Object* cntr, const char* uri)
	{
		assert(cntr);
		return _save_uri(uri, save_glTFData_flat_buffer(cntr));
	}

	//---

	bool save_glTFData_flat(const glTF_Object* cntr, FILE* file)
	{
		assert(cntr);
		return _save_file(file, save_glTFData_flat_buffer(cntr));
	}

	//---

	bool save_glTFData_flat(const glTF_Object* cntr, std::ostream& outs)
	{
		assert(cntr);
		return _save_stream(outs, save_glTFData_flat_buffer(cntr));
	}

	//---

	bool save_glTFData_flat(const glTF_Object* cntr, std::vector<uint8_t>& buffer)
	{
		assert(cntr);
		buffer = save_glTFData_flat_buffer(cntr);
		return true;
	}

	//---
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool load_glTFData_bindata(glTF_Object* cntr)
	{
		assert(cntr);
		// TODO: implementation
		return false;
	}

	//---

	bool save_glTFData_bindata(const glTF_Object* cntr)
	{
		assert(cntr);
		// TODO: implementation
		return false;
	}

	//---

	bool load_glTFData_bindata(std::vector<uint8_t>& bindata, const char* uri)
	{
		// TODO: implementation
		return false;
	}

	//---

	bool load_glTFData_bindata(std::vector<uint8_t>& bindata, FILE* file)
	{
		// TODO: implementation
		return false;
	}

	//---

	bool load_glTFData_bindata(std::vector<uint8_t>& buffer, std::istream&)
	{
		// TODO: implementation
		return false;
	}

	//---

	bool save_glTFData_bindata(const std::vector<uint8_t>& bindata, const char* uri)
	{
		// TODO: implementation
		return false;
	}

	//---

	bool save_glTFData_bindata(const std::vector<uint8_t>& bindata, FILE* file)
	{
		// TODO: implementation
		return false;
	}

	//---

	bool save_glTFData_bindata(const std::vector<uint8_t>& buffer, std::ostream&)
	{
		// TODO: implementation
		return false;
	}

	//---
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
