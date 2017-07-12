#ifndef FLATGLTF_2_0_INTERNAL_API_H_INC
#define FLATGLTF_2_0_INTERNAL_API_H_INC

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
	namespace detail
	{
		///-----------------------------------------------------------------------
		/// instantiation
		///-----------------------------------------------------------------------
		/// all functions return glTFid_t (aka int)
		/// negative values --> error
		/// TODO: define negative values as error return codes

		glTFid_t add_Accessor(glTF_Object&, AccessorT);
		glTFid_t add_Animation(glTF_Object&, AnimationT);
		glTFid_t add_Buffer(glTF_Object&, BufferT);
		glTFid_t add_BufferView(glTF_Object&, BufferViewT);
		glTFid_t add_Camera(glTF_Object&, CameraT);
		glTFid_t add_Image(glTF_Object&, ImageT);
		glTFid_t add_Material(glTF_Object&, MaterialT);
		glTFid_t add_Mesh(glTF_Object&, MeshT);
		glTFid_t add_Node(glTF_Object&, NodeT);
		glTFid_t add_Sampler(glTF_Object&, SamplerT);
		glTFid_t add_Scene(glTF_Object&, SceneT);
		glTFid_t add_Skin(glTF_Object&, SkinT);
		glTFid_t add_Texture(glTF_Object&, TextureT);

		glTFid_t add_Accessor(glTF_Object&, Accessor_t&&);
		glTFid_t add_Animation(glTF_Object&, Animation_t&&);
		glTFid_t add_Buffer(glTF_Object&, Buffer_t&&);
		glTFid_t add_BufferView(glTF_Object&, BufferView_t&&);
		glTFid_t add_Camera(glTF_Object&, Camera_t&&);
		glTFid_t add_Image(glTF_Object&, Image_t&&);
		glTFid_t add_Material(glTF_Object&, Material_t&&);
		glTFid_t add_Mesh(glTF_Object&, Mesh_t&&);
		glTFid_t add_Node(glTF_Object&, Node_t&&);
		glTFid_t add_Sampler(glTF_Object&, Sampler_t&&);
		glTFid_t add_Scene(glTF_Object&, Scene_t&&);
		glTFid_t add_Skin(glTF_Object&, Skin_t&&);
		glTFid_t add_Texture(glTF_Object&, Texture_t&&);


		AccessorT* const   get_Accessor(glTF_Object&, glTFid_t);
		AnimationT* const  get_Animation(glTF_Object&, glTFid_t);
		BufferT* const	 get_Buffer(glTF_Object&, glTFid_t);
		BufferViewT* const get_BufferView(glTF_Object&, glTFid_t);
		CameraT* const	 get_Camera(glTF_Object&, glTFid_t);
		ImageT* const	  get_Image(glTF_Object&, glTFid_t);
		MaterialT* const   get_Material(glTF_Object&, glTFid_t);
		MeshT* const	   get_Mesh(glTF_Object&, glTFid_t);
		NodeT* const	   get_Node(glTF_Object&, glTFid_t);
		SamplerT* const	get_Sampler(glTF_Object&, glTFid_t);
		SceneT* const	  get_Scene(glTF_Object&, glTFid_t);
		SkinT* const	   get_Skin(glTF_Object&, glTFid_t);
		TextureT* const	get_Texture(glTF_Object&, glTFid_t);


		/// adds buffer as base64 string
		glTFid_t add_Buffer(glTF_Object& cntr, const std::vector<uint8_t>& bufferdata);

		/// adds buffer as external bindata, given name
		/// returns -1 if bindata with same name already exists
		glTFid_t add_Buffer(glTF_Object& cntr, std::vector<uint8_t> bufferdata, const char* name);


		struct add_TypedDataBuffer_ReturnT
		{
			glTFid_t bufferId;

			struct BufferViewIdAndAccessorIds
			{
				glTFid_t			  bufferViewId;
				std::vector<glTFid_t> accessorIds;
			};
			std::vector<BufferViewIdAndAccessorIds> bufferViewIdsAndAccessorIds;
		};
		struct add_TypedDataBuffer_ParamT
		{
			std::vector<uint8_t> bufferdata;
			struct BufferViewAndAccessors
			{
				BufferViewT			   bufferView;
				std::vector<AccessorT> accessors;
			};
			std::vector<BufferViewAndAccessors> bufferviewsAndAccessors;
		};
		add_TypedDataBuffer_ReturnT add_TypedDataBuffer(glTF_Object& cntr, add_TypedDataBuffer_ParamT param, const char* name = nullptr);

		glTFid_t add_Scene(glTF_Object&, SceneT, bool display);
		glTFid_t add_Scene(glTF_Object&, Scene_t&&, bool display);
	}	// namespace detail

	///-----------------------------------------------------------------------
	/// utility
	///-----------------------------------------------------------------------

	/// prepares glTF data for GLB serialization
	//- changes URIs
	//- merges all mapped bindata into a single blob
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API binarize_glTFData(glTF_Object&);

	/// prepares glTF data for glTF-embedded format
	//- changes URIs to contain base64 encoded buffers
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API embed_glTFData(glTF_Object&);

	/// prepares glTF data for glTF-multi format
	//- changes URIs to reference external buffers
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API dislodge_glTFData(glTF_Object&);


	///-----------------------------------------------------------------------
	/// file I/O
	///-----------------------------------------------------------------------

	// JSON file interface
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData(glTF_Object&, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData(const glTF_Object&, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData(glTF_Object&, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData(const glTF_Object&, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData(glTF_Object&, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData(const glTF_Object&, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData(glTF_Object&, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData(const glTF_Object&, std::vector<uint8_t>& buffer);

	// API to fill/dump bindata from glTF
	// file interface for external bindata resources
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_bindata(glTF_Object&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_bindata(const glTF_Object&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_bindata(std::vector<uint8_t>& bindata, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_bindata(const std::vector<uint8_t>& bindata, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_bindata(std::vector<uint8_t>& bindata, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_bindata(const std::vector<uint8_t>& bindata, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_bindata(std::vector<uint8_t>& buffer, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_bindata(const std::vector<uint8_t>& buffer, std::ostream&);

	// GLB file interface
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_binary(glTF_Object&, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_binary(const glTF_Object&, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_binary(glTF_Object&, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_binary(const glTF_Object&, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_binary(glTF_Object&, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_binary(const glTF_Object&, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_binary(glTF_Object&, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_binary(const glTF_Object&, std::vector<uint8_t>& buffer);

	// GLF file interface
	// GLF is a FlatGLTF original format, basically JSON dumped as flatbuffer
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_flat(glTF_Object&, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_flat(const glTF_Object&, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_flat(glTF_Object&, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_flat(const glTF_Object&, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_flat(glTF_Object&, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_flat(const glTF_Object&, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_glTFData_flat(glTF_Object&, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_glTFData_flat(const glTF_Object&, std::vector<uint8_t>& buffer);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_INTERNAL_API_H_INC
