#ifndef FLATGLTF_2_0_TYPES_H_INC
#define FLATGLTF_2_0_TYPES_H_INC

#include "glTF_generated.h"
#include "glb.h"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

namespace glTF_2_0
{
	typedef std::unique_ptr<AccessorSparseIndicesT>		   AccessorSparseIndices_t;
	typedef std::unique_ptr<AccessorSparseValuesT>		   AccessorSparseValues_t;
	typedef std::unique_ptr<AccessorSparseT>			   AccessorSparse_t;
	typedef std::unique_ptr<AccessorT>					   Accessor_t;
	typedef std::unique_ptr<AssetT>						   Asset_t;
	typedef std::unique_ptr<AnimationChannelTargetT>	   AnimationChannelTarget_t;
	typedef std::unique_ptr<AnimationChannelT>			   AnimationChannel_t;
	typedef std::unique_ptr<AnimationSamplerT>			   AnimationSampler_t;
	typedef std::unique_ptr<AnimationT>					   Animation_t;
	typedef std::unique_ptr<BufferT>					   Buffer_t;
	typedef std::unique_ptr<BufferViewT>				   BufferView_t;
	typedef std::unique_ptr<CameraOrthographicT>		   CameraOrthographic_t;
	typedef std::unique_ptr<CameraPerspectiveT>			   CameraPerspective_t;
	typedef std::unique_ptr<CameraT>					   Camera_t;
	typedef std::unique_ptr<ImageT>						   Image_t;
	typedef std::unique_ptr<TextureInfoT>				   TextureInfo_t;
	typedef std::unique_ptr<MaterialNormalTextureInfoT>	MaterialNormalTextureInfo_t;
	typedef std::unique_ptr<MaterialOcclusionTextureInfoT> MaterialOcclusionTextureInfo_t;
	typedef std::unique_ptr<MaterialPbrMetallicRoughnessT> MaterialPbrMetallicRoughness_t;
	typedef std::unique_ptr<MaterialT>					   Material_t;
	typedef std::unique_ptr<MeshPrimitiveT>				   MeshPrimitive_t;
	typedef std::unique_ptr<MeshT>						   Mesh_t;
	typedef std::unique_ptr<NodeT>						   Node_t;
	typedef std::unique_ptr<SceneT>						   Scene_t;
	typedef std::unique_ptr<SamplerT>					   Sampler_t;
	typedef std::unique_ptr<TextureT>					   Texture_t;
	typedef std::unique_ptr<SkinT>						   Skin_t;
	typedef std::unique_ptr<glTFT>						   glTF_t;

	std::string to_json(const glTF_t&);
	glTF_t		from_json(const std::string&);

	std::vector<uint8_t> to_flatbuffer(const glTF_t&);
	glTF_t				 from_flatbuffer(const std::vector<uint8_t>&);

	struct glTF_DataContainer
	{
		glTF_t object;
		std::map<std::string, std::vector<uint8_t>> bindata;
	};
}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_TYPES_H_INC