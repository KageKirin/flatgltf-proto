#ifndef FLATGLTF_2_0_API_H_INC
#define FLATGLTF_2_0_API_H_INC

#include "../common/glTF_api_exports.h"
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
	///-----------------------------------------------------------------------
	/// instantiation
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if error

	glTF_Object* const create_RootObject(const char* name);

	AccessorT const* create_Accessor(glTF_Object* const, const char* name = nullptr);
	AnimationT const* create_Animation(glTF_Object* const, const char* name = nullptr);
	BufferT const* create_Buffer(glTF_Object* const, const char* name = nullptr);
	BufferViewT const* create_BufferView(glTF_Object* const, const char* name = nullptr);
	CameraT const* create_Camera(glTF_Object* const, const char* name = nullptr);
	ImageT const* create_Image(glTF_Object* const, const char* name = nullptr);
	MaterialT const* create_Material(glTF_Object* const, const char* name = nullptr);
	MeshPrimitiveT const* create_MeshPrimitive(glTF_Object* const, const char* name = nullptr);
	MeshT const* create_Mesh(glTF_Object* const, const char* name = nullptr);
	NodeT const* create_Node(glTF_Object* const, const char* name = nullptr);
	SceneT const* create_Scene(glTF_Object* const, const char* name = nullptr);
	SamplerT const* create_Sampler(glTF_Object* const, const char* name = nullptr);
	TextureT const* create_Texture(glTF_Object* const, const char* name = nullptr);
	SkinT const* create_Skin(glTF_Object* const, const char* name = nullptr);

	///-----------------------------------------------------------------------
	/// simple get for unique elements
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found

	AssetT const* get_Asset(glTF_Object* const);	// has no name
	SceneT const* get_Scene(glTF_Object* const);	// return scene if set, nullptr else

	///-----------------------------------------------------------------------
	/// get-by-id
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found


	AccessorT const*	  get_Accessor(glTF_Object* const, glTFId_t);
	AnimationT const*	 get_Animation(glTF_Object* const, glTFId_t);
	BufferT const*		  get_Buffer(glTF_Object* const, glTFId_t);
	BufferViewT const*	get_BufferView(glTF_Object* const, glTFId_t);
	CameraT const*		  get_Camera(glTF_Object* const, glTFId_t);
	ImageT const*		  get_Image(glTF_Object* const, glTFId_t);
	MaterialT const*	  get_Material(glTF_Object* const, glTFId_t);
	MeshPrimitiveT const* get_MeshPrimitive(glTF_Object* const, glTFId_t);
	MeshT const*		  get_Mesh(glTF_Object* const, glTFId_t);
	NodeT const*		  get_Node(glTF_Object* const, glTFId_t);
	SceneT const*		  get_Scene(glTF_Object* const, glTFId_t);
	SamplerT const*		  get_Sampler(glTF_Object* const, glTFId_t);
	TextureT const*		  get_Texture(glTF_Object* const, glTFId_t);
	SkinT const*		  get_Skin(glTF_Object* const, glTFId_t);

	///-----------------------------------------------------------------------
	/// get-by-name
	/// note that names are optional and this might not work
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found

	AccessorT const* get_Accessor(glTF_Object* const, const char* name);
	AnimationT const* get_Animation(glTF_Object* const, const char* name);
	BufferT const* get_Buffer(glTF_Object* const, const char* name);
	BufferViewT const* get_BufferView(glTF_Object* const, const char* name);
	CameraT const* get_Camera(glTF_Object* const, const char* name);
	ImageT const* get_Image(glTF_Object* const, const char* name);
	MaterialT const* get_Material(glTF_Object* const, const char* name);
	MeshPrimitiveT const* get_MeshPrimitive(glTF_Object* const, const char* name);
	MeshT const* get_Mesh(glTF_Object* const, const char* name);
	NodeT const* get_Node(glTF_Object* const, const char* name);
	SceneT const* get_Scene(glTF_Object* const, const char* name);
	SamplerT const* get_Sampler(glTF_Object* const, const char* name);
	TextureT const* get_Texture(glTF_Object* const, const char* name);
	SkinT const* get_Skin(glTF_Object* const, const char* name);

	///-----------------------------------------------------------------------
	/// get-id
	///-----------------------------------------------------------------------
	// all functions return a glTFid_t >= 0 if found, < 0 if not

	glTFid_t id_of(glTF_Object* const, AccessorT* const);
	glTFid_t id_of(glTF_Object* const, AnimationT* const);
	glTFid_t id_of(glTF_Object* const, BufferT* const);
	glTFid_t id_of(glTF_Object* const, BufferViewT* const);
	glTFid_t id_of(glTF_Object* const, CameraT* const);
	glTFid_t id_of(glTF_Object* const, ImageT* const);
	glTFid_t id_of(glTF_Object* const, MaterialT* const);
	glTFid_t id_of(glTF_Object* const, MeshPrimitiveT* const);
	glTFid_t id_of(glTF_Object* const, MeshT* const);
	glTFid_t id_of(glTF_Object* const, NodeT* const);
	glTFid_t id_of(glTF_Object* const, SceneT* const);
	glTFid_t id_of(glTF_Object* const, SamplerT* const);
	glTFid_t id_of(glTF_Object* const, TextureT* const);
	glTFid_t id_of(glTF_Object* const, SkinT* const);


	///-----------------------------------------------------------------------
	/// utility
	///-----------------------------------------------------------------------

	/// prepares glTF data for GLB serialization
	//- changes URIs
	//- merges all mapped bindata into a single blob
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API binarize_glTFData(glTF_Object*);

	/// prepares glTF data for glTF-embedded format
	//- changes URIs to contain base64 encoded buffers
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API embed_glTFData(glTF_Object*);

	/// prepares glTF data for glTF-multi format
	//- changes URIs to reference external buffers
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API dislodge_glTFData(glTF_Object*);

	/// prepares glTF data for glTF-multi format
	//- splits buffers into multiple buffers according to bufferViews
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API split_glTFData(glTF_Object*);

	///-----------------------------------------------------------------------
	/// file I/O
	///-----------------------------------------------------------------------

	// JSON file interface
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData(glTF_Object* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData(const glTF_Object* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData(glTF_Object* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData(const glTF_Object* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData(glTF_Object* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData(const glTF_Object* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData(glTF_Object* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData(const glTF_Object* const, std::vector<uint8_t>& buffer);

	// API to fill/dump bindata from glTF
	// file interface for external bindata resources
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_bindata(glTF_Object*);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_bindata(const glTF_Object*);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_bindata(std::vector<uint8_t>& bindata, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_bindata(const std::vector<uint8_t>& bindata, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_bindata(std::vector<uint8_t>& bindata, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_bindata(const std::vector<uint8_t>& bindata, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_bindata(std::vector<uint8_t>& buffer, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_bindata(const std::vector<uint8_t>& buffer, std::ostream&);

	// GLB file interface
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_binary(glTF_Object* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_binary(const glTF_Object* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_binary(glTF_Object* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_binary(const glTF_Object* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_binary(glTF_Object* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_binary(const glTF_Object* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_binary(glTF_Object* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_binary(const glTF_Object* const, std::vector<uint8_t>& buffer);

	// GLF file interface
	// GLF is a FlatGLTF original format, basically JSON dumped as flatbuffer
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_flat(glTF_Object* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_flat(const glTF_Object* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_flat(glTF_Object* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_flat(const glTF_Object* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_flat(glTF_Object* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_flat(const glTF_Object* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_flat(glTF_Object* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_flat(const glTF_Object* const, std::vector<uint8_t>& buffer);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_API_H_INC
