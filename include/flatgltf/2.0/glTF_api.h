#ifndef FLATGLTF_2_0_API_H_INC
#define FLATGLTF_2_0_API_H_INC

#include "glTF_generated.h"
#include "glTF_types.h"
#include "glb.h"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

namespace glTF_2_0
{


	// TODO: doc
	// TODO: API EXPORT
	bool load_glTFData(glTFDataT*, const char* uri);
	bool save_glTFData(const glTFDataT*, const char* uri);

	bool load_glTFData(glTFDataT*, FILE* file);
	bool save_glTFData(const glTFDataT*, FILE* file);

	bool load_glTFData(glTFDataT*, std::istream&);
	bool save_glTFData(const glTFDataT*, std::ostream&);

	bool load_glTFData(glTFDataT*, const std::vector<uint8_t>& buffer);
	bool save_glTFData(const glTFDataT*, std::vector<uint8_t>& buffer);

	// API to fill/dump bindata from glTF
	// TODO: doc
	// TODO: API EXPORT
	bool load_glTFData_bindata(glTFDataT*);
	bool save_glTFData_bindata(const glTFDataT*);

	bool load_glTFData_bindata(std::vector<uint8_t>& bindata, const char* uri);
	bool save_glTFData_bindata(const std::vector<uint8_t>& bindata, const char* uri);

	bool load_glTFData_bindata(std::vector<uint8_t>& bindata, FILE* file);
	bool save_glTFData_bindata(const std::vector<uint8_t>& bindata, FILE* file);

	bool load_glTFData_bindata(std::vector<uint8_t>& buffer, std::istream&);
	bool save_glTFData_bindata(const std::vector<uint8_t>& buffer, std::ostream&);

	// TODO: doc
	// TODO: API EXPORT
	bool load_glTFData_binary(glTFDataT*, const char* uri);
	bool save_glTFData_binary(const glTFDataT*, const char* uri);

	bool load_glTFData_binary(glTFDataT*, FILE* file);
	bool save_glTFData_binary(const glTFDataT*, FILE* file);

	bool load_glTFData_binary(glTFDataT*, std::istream&);
	bool save_glTFData_binary(const glTFDataT*, std::ostream&);

	bool load_glTFData_binary(glTFDataT*, const std::vector<uint8_t>& buffer);
	bool save_glTFData_binary(const glTFDataT*, std::vector<uint8_t>& buffer);

	// TODO: doc
	// TODO: API EXPORT
	bool load_glTFData_flat(glTFDataT*, const char* uri);
	bool save_glTFData_flat(const glTFDataT*, const char* uri);

	bool load_glTFData_flat(glTFDataT*, FILE* file);
	bool save_glTFData_flat(const glTFDataT*, FILE* file);

	bool load_glTFData_flat(glTFDataT*, std::istream&);
	bool save_glTFData_flat(const glTFDataT*, std::ostream&);

	bool load_glTFData_flat(glTFDataT*, const std::vector<uint8_t>& buffer);
	bool save_glTFData_flat(const glTFDataT*, std::vector<uint8_t>& buffer);

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_API_H_INC
