#ifndef FLATGLTF_2_0_INTERNAL_TYPES_H_INC
#define FLATGLTF_2_0_INTERNAL_TYPES_H_INC

#include "glTF_generated.h"
#include "glTF_types.h"
#include "glb.h"
#include <glm/glm.hpp>
#include <glm/quaternion.hpp>

#include <cctype>
#include <memory>
#include <string>
#include <vector>

namespace glTF_2_0
{
	namespace detail
	{
		//---
		using AccessorSparseIndices_t		 = std::unique_ptr<AccessorSparseIndicesT>;
		using AccessorSparseValues_t		 = std::unique_ptr<AccessorSparseValuesT>;
		using AccessorSparse_t				 = std::unique_ptr<AccessorSparseT>;
		using Accessor_t					 = std::unique_ptr<AccessorT>;
		using Asset_t						 = std::unique_ptr<AssetT>;
		using AnimationChannelTarget_t		 = std::unique_ptr<AnimationChannelTargetT>;
		using AnimationChannel_t			 = std::unique_ptr<AnimationChannelT>;
		using AnimationSampler_t			 = std::unique_ptr<AnimationSamplerT>;
		using Animation_t					 = std::unique_ptr<AnimationT>;
		using Buffer_t						 = std::unique_ptr<BufferT>;
		using BufferView_t					 = std::unique_ptr<BufferViewT>;
		using CameraOrthographic_t			 = std::unique_ptr<CameraOrthographicT>;
		using CameraPerspective_t			 = std::unique_ptr<CameraPerspectiveT>;
		using Camera_t						 = std::unique_ptr<CameraT>;
		using Image_t						 = std::unique_ptr<ImageT>;
		using TextureInfo_t					 = std::unique_ptr<TextureInfoT>;
		using MaterialNormalTextureInfo_t	= std::unique_ptr<MaterialNormalTextureInfoT>;
		using MaterialOcclusionTextureInfo_t = std::unique_ptr<MaterialOcclusionTextureInfoT>;
		using MaterialPbrMetallicRoughness_t = std::unique_ptr<MaterialPbrMetallicRoughnessT>;
		using Material_t					 = std::unique_ptr<MaterialT>;
		using MeshPrimitive_t				 = std::unique_ptr<MeshPrimitiveT>;
		using Mesh_t						 = std::unique_ptr<MeshT>;
		using Node_t						 = std::unique_ptr<NodeT>;
		using Scene_t						 = std::unique_ptr<SceneT>;
		using Sampler_t						 = std::unique_ptr<SamplerT>;
		using Texture_t						 = std::unique_ptr<TextureT>;
		using Skin_t						 = std::unique_ptr<SkinT>;
		using Root_t						 = std::unique_ptr<RootT>;

		//! container structure to keep glTF data along with buffers
		struct glTF_Object
		{
			Root_t root;
			std::map<std::string, std::vector<uint8_t>> bindata;
		};

		//---
		// matrix types with fitting padding
		// maybe move to glTF_glm.h
		template <typename T, precision P = defaultp>
		using tmat2_t = glm::tmat2x4<T, P>;

		template <typename T, precision P = defaultp>
		using tmat3_t = glm::tmat3x4<T, P>;

		template <typename T, precision P = defaultp>
		using tmat4_t = glm::tmat4x4<T, P>;

		template <typename T, precision P = defaultp>
		using tvec2_t = glm::tvec2<T, P>;

		template <typename T, precision P = defaultp>
		using tvec3_t = glm::tvec3<T, P>;

		template <typename T, precision P = defaultp>
		using tvec4_t = glm::tvec4<T, P>;

		template <typename T, precision P = defaultp>
		using tquat_t = glm::tquat<T, P>;

		using mat2_t  = glm::mat2x4;
		using mat3_t  = glm::mat3x4;
		using mat4_t  = glm::mat4x4;
		using vec2_t  = glm::vec2;
		using vec3_t  = glm::vec3;
		using vec4_t  = glm::vec4;
		using quat_t  = glm::quat;
		using imat2_t = glm::imat2x4;
		using imat3_t = glm::imat3x4;
		using imat4_t = glm::imat4x4;
		using ivec2_t = glm::ivec2;
		using ivec3_t = glm::ivec3;
		using ivec4_t = glm::ivec4;


		//--
		template <typename T, precision P = defaultp>
		inline tmat2_t<T, P> glm_cast(const glm::tmat2x2<T, P>& m)
		{
			return tmat2_t<T, P>{
			  {m[0].x, m[0].y, 0, 0},	//
			  {m[1].x, m[1].y, 0, 0},
			};
		}

		template <typename T, precision P = defaultp>
		inline tmat3_t<T, P> glm_cast(const glm::tmat3x3<T, P>& m)
		{
			return tmat3_t<T, P>{
			  {m[0].x, m[0].y, m[0].z, 0},	//
			  {m[1].x, m[1].y, m[1].z, 0},
			  {m[2].x, m[2].y, m[2].z, 0},
			};
		}

		template <typename T, precision P = defaultp>
		inline tmat4_t<T, P> glm_cast(const glm::tmat4x4<T, P>& m)
		{
			return m;
		}

		template <typename T, precision P = defaultp>
		inline glm::tmat2x2<T, P> glm_cast(const tmat2_t<T, P>& m)
		{
			return glm::tmat2x2<T, P>{
			  {m[0].x, m[0].y},	//
			  {m[1].x, m[1].y},
			};
		}

		template <typename T, precision P = defaultp>
		inline glm::tmat3x3<T, P> glm_cast(const tmat3_t<T, P>& m)
		{
			return glm::tmat3x3<T, P>{
			  {m[0].x, m[0].y, m[0].z},	//
			  {m[1].x, m[1].y, m[1].z},
			  {m[2].x, m[2].y, m[2].z},
			};
		}

		template <typename T, precision P = defaultp>
		inline glm::tmat4x4<T, P> glm_cast(const tmat4_t<T, P>& m)
		{
			return m;
		}
	}	// namespace detail
}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_INTERNAL_TYPES_H_INC