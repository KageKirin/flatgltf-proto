#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"

#include "glTF_internal_types.h"

namespace glTF_2_0
{
	using namespace detail;

	///-----------------------------------------------------------------------
	/// get-id
	///-----------------------------------------------------------------------
	// all functions return a glTFid_t >= 0 if found, < 0 if not

	glTFid_t id_of(glTF_Object* const obj, AccessorT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->accessors.begin(), obj->root->accessors.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->accessors.end())
			{
				return glTFid_t(std::distance(obj->root->accessors.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, AnimationT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->animations.begin(), obj->root->animations.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->animations.end())
			{
				return glTFid_t(std::distance(obj->root->animations.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, BufferT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->buffers.begin(), obj->root->buffers.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->buffers.end())
			{
				return glTFid_t(std::distance(obj->root->buffers.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, BufferViewT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->bufferviews.begin(), obj->root->bufferviews.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->bufferviews.end())
			{
				return glTFid_t(std::distance(obj->root->bufferviews.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, CameraT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->cameras.begin(), obj->root->cameras.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->cameras.end())
			{
				return glTFid_t(std::distance(obj->root->cameras.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, ImageT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->images.begin(), obj->root->images.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->images.end())
			{
				return glTFid_t(std::distance(obj->root->images.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, MaterialT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->materials.begin(), obj->root->materials.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->materials.end())
			{
				return glTFid_t(std::distance(obj->root->materials.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, MeshPrimitiveT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->meshprimitives.begin(), obj->root->meshprimitives.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->meshprimitives.end())
			{
				return glTFid_t(std::distance(obj->root->meshprimitives.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, MeshT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->meshs.begin(), obj->root->meshs.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->meshs.end())
			{
				return glTFid_t(std::distance(obj->root->meshs.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, NodeT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->nodes.begin(), obj->root->nodes.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->nodes.end())
			{
				return glTFid_t(std::distance(obj->root->nodes.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, SceneT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->scenes.begin(), obj->root->scenes.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->scenes.end())
			{
				return glTFid_t(std::distance(obj->root->scenes.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, SamplerT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->samplers.begin(), obj->root->samplers.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->samplers.end())
			{
				return glTFid_t(std::distance(obj->root->samplers.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, TextureT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->textures.begin(), obj->root->textures.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->textures.end())
			{
				return glTFid_t(std::distance(obj->root->textures.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t id_of(glTF_Object* const obj, SkinT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->skins.begin(), obj->root->skins.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != obj->root->skins.end())
			{
				return glTFid_t(std::distance(obj->root->skins.begin(), it));
			}
		}
		return -1;
	}

	//---


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
