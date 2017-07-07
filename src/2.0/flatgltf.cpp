#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glb.h"

#include <memory>
#include <vector>
#include <string>
#include <algorithm>

namespace glTF_2_0
{
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool load_glTFData_buffer(glTFDataT* object, const std::vector<uint8_t>& buffer)
	{
	}

	std::vector<uint8_t> save_glTFData_buffer(const glTFDataT* object)
	{
	}

	//-------------------------------------------------------------------------

	bool load_glTFData_binary_buffer(glTFDataT* object, const std::vector<uint8_t>& buffer)
	{
	}

	std::vector<uint8_t> save_glTFData_binary_buffer(const glTFDataT* object)
	{
	}

	//-------------------------------------------------------------------------

	bool load_glTFData_flat_buffer(glTFDataT* object, const std::vector<uint8_t>& buffer)
	{
	}

	std::vector<uint8_t> save_glTFData_flat_buffer(const glTFDataT* object)
	{
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------


	typedef bool (*_glTFData_load_buffer_t)(glTFDataT*, const std::vector<uint8_t>&);

	static bool _load_file(glTFDataT* object, FILE* file, _glTFData_load_buffer_t loader)
	{
		std::vector<uint8_t> buffer;
		auto bi = std::back_inserter(buffer);
		while (file && !feof(file))
		{
			*bi++ = fgetc(file);
		}
		return loader(object, buffer);
	}
	
	static bool _load_filename(glTFDataT* object, const char* filename, _glTFData_load_buffer_t loader)
	{
		auto file = std::unique_ptr<FILE, decltype(&fclose)>(fopen(filename, "rb"), fclose);
		return _load_file(object, file.get(), loader);
	}

	static bool _load_stream(glTFDataT* object, std::istream& ins, _glTFData_load_buffer_t loader)
	{
		std::vector<uint8_t> buffer;
		auto bi = std::back_inserter(buffer);
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

	bool load_glTFData(glTFDataT* object, const char* filename)
	{
		return _load_filename(object, filename, load_glTFData_buffer);
	}

	bool load_glTFData(glTFDataT* object, FILE* file)
	{
		return _load_file(object, file, load_glTFData_buffer);
	}

	bool load_glTFData(glTFDataT* object, std::istream& ins)
	{
		return _load_stream(object, ins, load_glTFData_buffer);
	}

	bool load_glTFData(glTFDataT* object, const std::vector<uint8_t>& buffer)
	{
		return load_glTFData_buffer(object, buffer);
	}

	//---

	bool load_glTFData_binary(glTFDataT* object, const char* filename)
	{
		return _load_filename(object, filename, load_glTFData_binary_buffer);
	}

	bool load_glTFData_binary(glTFDataT* object, FILE* file)
	{
		return _load_file(object, file, load_glTFData_binary_buffer);
	}

	bool load_glTFData_binary(glTFDataT* object, std::istream& ins)
	{
		return _load_stream(object, ins, load_glTFData_binary_buffer);
	}

	bool load_glTFData_binary(glTFDataT* object, const std::vector<uint8_t>& buffer)
	{
		return load_glTFData_binary_buffer(object, buffer);
	}

	//---

	bool load_glTFData_flat(glTFDataT* object, const char* filename)
	{
		return _load_filename(object, filename, load_glTFData_flat_buffer);
	}

	bool load_glTFData_flat(glTFDataT* object, FILE* file)
	{
		return _load_file(object, file, load_glTFData_flat_buffer);
	}

	bool load_glTFData_flat(glTFDataT* object, std::istream& ins)
	{
		return _load_stream(object, ins, load_glTFData_flat_buffer);
	}

	bool load_glTFData_flat(glTFDataT* object, const std::vector<uint8_t>& buffer)
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
	
	static bool _save_filename(const char* filename, const std::vector<uint8_t>& buffer)
	{
		auto file = std::unique_ptr<FILE, decltype(&fclose)>(fopen(filename, "wb"), fclose);
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

	bool save_glTFData(const glTFDataT* object, const char* filename)
	{
		return _save_filename(filename, save_glTFData_buffer(object));
	}
	
	bool save_glTFData(const glTFDataT* object, FILE* file)
	{
		return _save_file(file, save_glTFData_buffer(object));
	}

	bool save_glTFData(const glTFDataT* object, std::ostream& outs)
	{
		return _save_stream(outs, save_glTFData_buffer(object));
	}

	bool save_glTFData(const glTFDataT* object, std::vector<uint8_t>& buffer)
	{
		buffer = save_glTFData_buffer(object);
		return true;
	}

	//---

	bool save_glTFData_binary(const glTFDataT* object, const char* filename)
	{
		return _save_filename(filename, save_glTFData_binary_buffer(object));
	}

	bool save_glTFData_binary(const glTFDataT* object, FILE* file)
	{
		return _save_file(file, save_glTFData_binary_buffer(object));
	}

	bool save_glTFData_binary(const glTFDataT* object, std::ostream& outs)
	{
		return _save_stream(outs, save_glTFData_binary_buffer(object));
	}

	bool save_glTFData_binary(const glTFDataT* object, std::vector<uint8_t>& buffer)
	{
		buffer = save_glTFData_binary_buffer(object);
		return true;
	}

	//---

	bool save_glTFData_flat(const glTFDataT* object, const char* filename)
	{
		return _save_filename(filename, save_glTFData_flat_buffer(object));
	}

	bool save_glTFData_flat(const glTFDataT* object, FILE* file)
	{
		return _save_file(file, save_glTFData_flat_buffer(object));
	}

	bool save_glTFData_flat(const glTFDataT* object, std::ostream& outs)
	{
		return _save_stream(outs, save_glTFData_flat_buffer(object));
	}

	bool save_glTFData_flat(const glTFDataT* object, std::vector<uint8_t>& buffer)
	{
		buffer = save_glTFData_flat_buffer(object);
		return true;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
