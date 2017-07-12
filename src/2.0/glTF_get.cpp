#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"

#include "glTF_internal_types.h"

namespace glTF_2_0
{
	using namespace detail;

	///-----------------------------------------------------------------------
	/// simple get for unique elements
	///-----------------------------------------------------------------------

	AssetT const* get_Asset(glTF_Object* const obj)
	{
		return (obj && obj->root) ? obj->root->asset.get() : nullptr;
	}

	SceneT const* get_Scene(glTF_Object* const obj)
	{
		return (obj && obj->root) ? get_Scene(obj, obj->root->scene) : nullptr;
	}

	///-----------------------------------------------------------------------
	/// get-by-id
	///-----------------------------------------------------------------------

	AccessorT const* get_Accessor(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->accessors.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	AnimationT const* get_Animation(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->animations.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	BufferT const* get_Buffer(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->buffers.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	BufferViewT const* get_BufferView(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->bufferviews.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	CameraT const* get_Camera(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->cameras.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	ImageT const* get_Image(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->images.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	MaterialT const* get_Material(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->materials.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	MeshPrimitiveT const* get_MeshPrimitive(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->meshprimitives.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	MeshT const* get_Mesh(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->meshs.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	NodeT const* get_Node(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->nodes.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	SceneT const* get_Scene(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->scenes.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	SamplerT const* get_Sampler(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->samplers.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	TextureT const* get_Texture(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->textures.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---

	SkinT const* get_Skin(glTF_Object* const obj, glTFId_t id)
	{
		if (obj && obj->root)
		{
			try
			{
				return obj->root->skins.at(id).get();
			}
			catch (...)
			{
			}
		}
		return nullptr;
	}

	//---


	///-----------------------------------------------------------------------
	/// get-by-name
	/// note that names are optional and this might not work
	///-----------------------------------------------------------------------

	AccessorT const* get_Accessor(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->accessors.begin(), obj->root->accessors.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->accessors.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	AnimationT const* get_Animation(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->animations.begin(), obj->root->animations.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->animations.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	BufferT const* get_Buffer(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->buffers.begin(), obj->root->buffers.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->buffers.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	BufferViewT const* get_BufferView(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->bufferviews.begin(), obj->root->bufferviews.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->bufferviews.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	CameraT const* get_Camera(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->cameras.begin(), obj->root->cameras.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->cameras.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	ImageT const* get_Image(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->images.begin(), obj->root->images.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->images.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	MaterialT const* get_Material(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->materials.begin(), obj->root->materials.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->materials.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	MeshPrimitiveT const* get_MeshPrimitive(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->meshprimitives.begin(), obj->root->meshprimitives.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->meshprimitives.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	MeshT const* get_Mesh(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->meshs.begin(), obj->root->meshs.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->meshs.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	NodeT const* get_Node(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->nodes.begin(), obj->root->nodes.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->nodes.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	SceneT const* get_Scene(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->scenes.begin(), obj->root->scenes.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->scenes.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	SamplerT const* get_Sampler(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->samplers.begin(), obj->root->samplers.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->samplers.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	TextureT const* get_Texture(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->textures.begin(), obj->root->textures.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->textures.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---

	SkinT const* get_Skin(glTF_Object* const obj, const char* name)
	{
		if (obj && obj->root)
		{
			auto it = std::find_if(obj->root->skins.begin(), obj->root->skins.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != obj->root->skins.end())
			{
				return &*it;
			}
		}
		return nullptr;
	}

	//---


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
