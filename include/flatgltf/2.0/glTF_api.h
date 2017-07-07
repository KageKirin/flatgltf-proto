#ifndef FLATGLTF_2_0_API_H_INC
#define FLATGLTF_2_0_API_H_INC

#include "glTF_generated.h"
#include "glb.h"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

namespace glTF_2_0
{
	// TODO: doc
	struct glTFDataT
	{
		glTFT				 object;
		std::vector<uint8_t> bindata;
	};


	// TODO: doc
	// TODO: API EXPORT
	bool load_glTFData(glTFDataT*, const char* filename);
	bool save_glTFData(const glTFDataT*, const char* filename);

	bool load_glTFData(glTFDataT*, FILE* file);
	bool save_glTFData(const glTFDataT*, FILE* file);

	bool load_glTFData(glTFDataT*, std::istream&);
	bool save_glTFData(const glTFDataT*, std::ostream&);

	bool load_glTFData(glTFDataT*, const std::vector<uint8_t>& buffer);
	bool save_glTFData(const glTFDataT*, std::vector<uint8_t>& buffer);

	// TODO: doc
	// TODO: API EXPORT
	bool load_glTFData_binary(glTFDataT*, const char* filename);
	bool save_glTFData_binary(const glTFDataT*, const char* filename);

	bool load_glTFData_binary(glTFDataT*, FILE* file);
	bool save_glTFData_binary(const glTFDataT*, FILE* file);

	bool load_glTFData_binary(glTFDataT*, std::istream&);
	bool save_glTFData_binary(const glTFDataT*, std::ostream&);

	bool load_glTFData_binary(glTFDataT*, const std::vector<uint8_t>& buffer);
	bool save_glTFData_binary(const glTFDataT*, std::vector<uint8_t>& buffer);

	// TODO: doc
	// TODO: API EXPORT
	bool load_glTFData_flat(glTFDataT*, const char* filename);
	bool save_glTFData_flat(const glTFDataT*, const char* filename);

	bool load_glTFData_flat(glTFDataT*, FILE* file);
	bool save_glTFData_flat(const glTFDataT*, FILE* file);

	bool load_glTFData_flat(glTFDataT*, std::istream&);
	bool save_glTFData_flat(const glTFDataT*, std::ostream&);

	bool load_glTFData_flat(glTFDataT*, const std::vector<uint8_t>& buffer);
	bool save_glTFData_flat(const glTFDataT*, std::vector<uint8_t>& buffer);

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_API_H_INC
