#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glb.h"

#include <algorithm>
#include <cassert>	//TODO: improve using catch later
#include <memory>
#include <string>
#include <vector>

namespace glTF_2_0
{
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool load_glTFData_buffer(glTF_DataContainer* object, const std::vector<uint8_t>& buffer)
	{
		std::string json(reinterpret_cast<const char*>(buffer.data()), buffer.size());
		object->object = from_json(json);
		return true;
	}

	std::vector<uint8_t> save_glTFData_buffer(const glTF_DataContainer* object)
	{
		auto json = to_json(object->object);
		return std::vector<uint8_t>{reinterpret_cast<const uint8_t*>(&*json.begin()),
									reinterpret_cast<const uint8_t*>(&*json.end())};
	}

	//-------------------------------------------------------------------------

	bool load_glTFData_binary_buffer(glTF_DataContainer* object, const std::vector<uint8_t>& buffer)
	{
		assert(object);
		assert(!buffer.empty());
		if (!object || buffer.empty())
		{
			return false;
		}

		const GLBHeader& header = *reinterpret_cast<const GLBHeader*>(&*buffer.begin());
		assert(header.magic == GLBHeader::MAGIC);
		assert(header.version == GLBHeader::VERSION);
		assert(header.length == buffer.size());

		const GLBChunkHeader& jsChunk = *reinterpret_cast<const GLBChunkHeader*>(&*(buffer.begin() + sizeof(GLBHeader)));
		assert(jsChunk.chunkType == GLBChunkHeader::JSON);
		assert(jsChunk.chunkLength >= 4);
		assert((jsChunk.chunkLength % 4) == 0);

		std::string jsonString(reinterpret_cast<const char*>(&*(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader))));
		assert(!jsonString.empty());

		object->object = from_json(jsonString);

		// check if there's more data, i.e. binary chunk
		if (header.length > sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength)
		{
			const GLBChunkHeader& binChunk = *reinterpret_cast<const GLBChunkHeader*>(
			  &*(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength));
			assert(binChunk.chunkType == GLBChunkHeader::BIN);
			assert(binChunk.chunkLength >= 4);
			assert((binChunk.chunkLength % 4) == 0);

			object->bindata["binary"].reserve(binChunk.chunkLength);
			std::copy(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength + sizeof(GLBChunkHeader),
					  buffer.end(),
					  std::back_inserter(object->bindata["binary"]));
		}

		return true;
	}

	std::vector<uint8_t> save_glTFData_binary_buffer(const glTF_DataContainer* object)
	{
		assert(object);
		if (!object)
		{
			return std::vector<uint8_t>();
		}

		auto jsonString = to_json(object->object);
		jsonString.resize(jsonString.size() + jsonString.size() % 4, 0x20);	// pad to alignment with spaces

		size_t bindataSize = std::accumulate(object->bindata.begin(), object->bindata.end(), size_t(0), [](size_t sum, auto& kvp) {
			return sum + kvp.second.size() + kvp.second.size() % 4;	// pad to alignment with 0
		});

		std::vector<uint8_t> buffer;
		buffer.reserve(sizeof(GLBHeader) + 2 * sizeof(GLBChunkHeader) + jsonString.size() + bindataSize);

		GLBHeader header;
		assert(header.magic == GLBHeader::MAGIC);
		assert(header.version == GLBHeader::VERSION);
		header.length = buffer.size();

		GLBChunkHeader jsChunk{jsonString.size(), GLBChunkHeader::JSON};
		GLBChunkHeader binChunk{bindataSize, GLBChunkHeader::BIN};

		auto bi = std::back_inserter(buffer);
		std::copy_n(reinterpret_cast<const uint8_t*>(&header), sizeof(GLBHeader), bi);
		std::copy_n(reinterpret_cast<const uint8_t*>(&jsChunk), sizeof(GLBChunkHeader), bi);
		std::transform(jsonString.begin(), jsonString.end(), bi, [](auto& c) { return static_cast<uint8_t>(c); });
		std::copy_n(reinterpret_cast<const uint8_t*>(&binChunk), sizeof(GLBChunkHeader), bi);
		std::for_each(object->bindata.begin(), object->bindata.end(), [&bi](auto& kvp) {
			std::copy(kvp.second.begin(), kvp.second.end(), bi);
			std::fill_n(bi, kvp.second.size() % 4, 0x0);	// pad to alignment with 0
		});

		assert(!buffer.empty());
		return buffer;
	}

	//-------------------------------------------------------------------------

	bool load_glTFData_flat_buffer(glTF_DataContainer* object, const std::vector<uint8_t>& buffer)
	{
		object->object = from_flatbuffer(buffer);
		return true;
	}

	std::vector<uint8_t> save_glTFData_flat_buffer(const glTF_DataContainer* object)
	{
		return to_flatbuffer(object->object);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------


	typedef bool (*_glTFData_load_buffer_t)(glTF_DataContainer*, const std::vector<uint8_t>&);

	static bool _load_file(glTF_DataContainer* object, FILE* file, _glTFData_load_buffer_t loader)
	{
		std::vector<uint8_t> buffer;
		auto				 bi = std::back_inserter(buffer);
		while (file && !feof(file))
		{
			*bi++ = fgetc(file);
		}
		return loader(object, buffer);
	}

	static bool _load_uri(glTF_DataContainer* object, const char* uri, _glTFData_load_buffer_t loader)
	{
		auto file = std::unique_ptr<FILE, decltype(&fclose)>(fopen(uri, "rb"), fclose);
		return _load_file(object, file.get(), loader);
	}

	static bool _load_stream(glTF_DataContainer* object, std::istream& ins, _glTFData_load_buffer_t loader)
	{
		std::vector<uint8_t> buffer;
		auto				 bi = std::back_inserter(buffer);
		while (ins)
		{
			char c;
			ins.read(&c, 1);
			*bi++ = c;
		}
		return loader(object, buffer);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool load_glTFData(glTF_DataContainer* object, const char* uri)
	{
		return _load_uri(object, uri, load_glTFData_buffer);
	}

	bool load_glTFData(glTF_DataContainer* object, FILE* file)
	{
		return _load_file(object, file, load_glTFData_buffer);
	}

	bool load_glTFData(glTF_DataContainer* object, std::istream& ins)
	{
		return _load_stream(object, ins, load_glTFData_buffer);
	}

	bool load_glTFData(glTF_DataContainer* object, const std::vector<uint8_t>& buffer)
	{
		return load_glTFData_buffer(object, buffer);
	}

	//---

	bool load_glTFData_binary(glTF_DataContainer* object, const char* uri)
	{
		return _load_uri(object, uri, load_glTFData_binary_buffer);
	}

	bool load_glTFData_binary(glTF_DataContainer* object, FILE* file)
	{
		return _load_file(object, file, load_glTFData_binary_buffer);
	}

	bool load_glTFData_binary(glTF_DataContainer* object, std::istream& ins)
	{
		return _load_stream(object, ins, load_glTFData_binary_buffer);
	}

	bool load_glTFData_binary(glTF_DataContainer* object, const std::vector<uint8_t>& buffer)
	{
		return load_glTFData_binary_buffer(object, buffer);
	}

	//---

	bool load_glTFData_flat(glTF_DataContainer* object, const char* uri)
	{
		return _load_uri(object, uri, load_glTFData_flat_buffer);
	}

	bool load_glTFData_flat(glTF_DataContainer* object, FILE* file)
	{
		return _load_file(object, file, load_glTFData_flat_buffer);
	}

	bool load_glTFData_flat(glTF_DataContainer* object, std::istream& ins)
	{
		return _load_stream(object, ins, load_glTFData_flat_buffer);
	}

	bool load_glTFData_flat(glTF_DataContainer* object, const std::vector<uint8_t>& buffer)
	{
		return load_glTFData_flat_buffer(object, buffer);
	}

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

	static bool _save_uri(const char* uri, const std::vector<uint8_t>& buffer)
	{
		auto file = std::unique_ptr<FILE, decltype(&fclose)>(fopen(uri, "wb"), fclose);
		return _save_file(file.get(), buffer);
	}

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

	bool save_glTFData(const glTF_DataContainer* object, const char* uri)
	{
		return _save_uri(uri, save_glTFData_buffer(object));
	}

	bool save_glTFData(const glTF_DataContainer* object, FILE* file)
	{
		return _save_file(file, save_glTFData_buffer(object));
	}

	bool save_glTFData(const glTF_DataContainer* object, std::ostream& outs)
	{
		return _save_stream(outs, save_glTFData_buffer(object));
	}

	bool save_glTFData(const glTF_DataContainer* object, std::vector<uint8_t>& buffer)
	{
		buffer = save_glTFData_buffer(object);
		return true;
	}

	//---

	bool save_glTFData_binary(const glTF_DataContainer* object, const char* uri)
	{
		return _save_uri(uri, save_glTFData_binary_buffer(object));
	}

	bool save_glTFData_binary(const glTF_DataContainer* object, FILE* file)
	{
		return _save_file(file, save_glTFData_binary_buffer(object));
	}

	bool save_glTFData_binary(const glTF_DataContainer* object, std::ostream& outs)
	{
		return _save_stream(outs, save_glTFData_binary_buffer(object));
	}

	bool save_glTFData_binary(const glTF_DataContainer* object, std::vector<uint8_t>& buffer)
	{
		buffer = save_glTFData_binary_buffer(object);
		return true;
	}

	//---

	bool save_glTFData_flat(const glTF_DataContainer* object, const char* uri)
	{
		return _save_uri(uri, save_glTFData_flat_buffer(object));
	}

	bool save_glTFData_flat(const glTF_DataContainer* object, FILE* file)
	{
		return _save_file(file, save_glTFData_flat_buffer(object));
	}

	bool save_glTFData_flat(const glTF_DataContainer* object, std::ostream& outs)
	{
		return _save_stream(outs, save_glTFData_flat_buffer(object));
	}

	bool save_glTFData_flat(const glTF_DataContainer* object, std::vector<uint8_t>& buffer)
	{
		buffer = save_glTFData_flat_buffer(object);
		return true;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool load_glTFData_bindata(glTF_DataContainer*)
	{
		// TODO: implementation
		return false;
	}
	bool save_glTFData_bindata(const glTF_DataContainer*)
	{
		// TODO: implementation
		return false;
	}


	bool load_glTFData_bindata(std::vector<uint8_t>& bindata, const char* uri)
	{
		// TODO: implementation
		return false;
	}
	bool load_glTFData_bindata(std::vector<uint8_t>& bindata, FILE* file)
	{
		// TODO: implementation
		return false;
	}
	bool load_glTFData_bindata(std::vector<uint8_t>& buffer, std::istream&)
	{
		// TODO: implementation
		return false;
	}


	bool save_glTFData_bindata(const std::vector<uint8_t>& bindata, const char* uri)
	{
		// TODO: implementation
		return false;
	}
	bool save_glTFData_bindata(const std::vector<uint8_t>& bindata, FILE* file)
	{
		// TODO: implementation
		return false;
	}
	bool save_glTFData_bindata(const std::vector<uint8_t>& buffer, std::ostream&)
	{
		// TODO: implementation
		return false;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
