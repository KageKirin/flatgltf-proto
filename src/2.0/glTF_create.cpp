#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"

#include "glTF_internal_types.h"

namespace glTF_2_0
{
	using namespace detail;

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	static AssetT* create_Asset_default(const char* name)
	{
		auto instance		 = Asset_t{new AssetT};
		instance->name		 = name;
		instance->version	= "2.0";
		instance->minVersion = "2.0";
		instance->copyright  = "NONE, unless specified otherwise";
		instance->generator  = "flatgltf, unless specified otherwise";
		return instance.release();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	glTF_Object* const create_RootObject(const char* name)
	{
		auto instance		  = glTF_Object_t{new glTF_Object};
		instance->root		  = Root_t{new RootT};
		instance->root->asset = create_Asset_default(name);

		return instance.release();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	AccessorT const* create_Accessor(glTF_Object* const obj, const char* name)
	{
		auto instance = Accessor_t{new AccessorT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->accessors.push_back(std::move(instance));
		return &obj->root->accessors.back();
	}

	//---

	AnimationT const* create_Animation(glTF_Object* const obj, const char* name)
	{
		auto instance = Animation_t{new AnimationT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->animations.push_back(std::move(instance));
		return &obj->root->animations.back();
	}

	//---

	BufferT const* create_Buffer(glTF_Object* const obj, const char* name)
	{
		auto instance = Buffer_t{new BufferT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->buffers.push_back(std::move(instance));
		return &obj->root->buffers.back();
	}

	//---

	BufferViewT const* create_BufferView(glTF_Object* const obj, const char* name)
	{
		auto instance = BufferView_t{new BufferViewT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->bufferviews.push_back(std::move(instance));
		return &obj->root->bufferviews.back();
	}

	//---

	CameraT const* create_Camera(glTF_Object* const obj, const char* name)
	{
		auto instance = Camera_t{new CameraT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->cameras.push_back(std::move(instance));
		return &obj->root->cameras.back();
	}

	//---

	ImageT const* create_Image(glTF_Object* const obj, const char* name)
	{
		auto instance = Image_t{new ImageT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->images.push_back(std::move(instance));
		return &obj->root->images.back();
	}

	//---

	MaterialT const* create_Material(glTF_Object* const obj, const char* name)
	{
		auto instance = Material_t{new MaterialT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->materials.push_back(std::move(instance));
		return &obj->root->materials.back();
	}

	//---

	MeshPrimitiveT const* create_MeshPrimitive(glTF_Object* const obj, const char* name)
	{
		auto instance = MeshPrimitive_t{new MeshPrimitiveT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->meshprimitives.push_back(std::move(instance));
		return &obj->root->meshprimitives.back();
	}

	//---

	MeshT const* create_Mesh(glTF_Object* const obj, const char* name)
	{
		auto instance = Mesh_t{new MeshT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->meshs.push_back(std::move(instance));
		return &obj->root->meshs.back();
	}

	//---

	NodeT const* create_Node(glTF_Object* const obj, const char* name)
	{
		auto instance = Node_t{new NodeT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->nodes.push_back(std::move(instance));
		return &obj->root->nodes.back();
	}

	//---

	SceneT const* create_Scene(glTF_Object* const obj, const char* name)
	{
		auto instance = Scene_t{new SceneT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->scenes.push_back(std::move(instance));
		return &obj->root->scenes.back();
	}

	//---

	SamplerT const* create_Sampler(glTF_Object* const obj, const char* name)
	{
		auto instance = Sampler_t{new SamplerT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->samplers.push_back(std::move(instance));
		return &obj->root->samplers.back();
	}

	//---

	TextureT const* create_Texture(glTF_Object* const obj, const char* name)
	{
		auto instance = Texture_t{new TextureT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->textures.push_back(std::move(instance));
		return &obj->root->textures.back();
	}

	//---

	SkinT const* create_Skin(glTF_Object* const obj, const char* name)
	{
		auto instance = Skin_t{new SkinT};
		if (name)
		{
			instance->name = name;
		}
		obj->root->skins.push_back(std::move(instance));
		return &obj->root->skins.back();
	}

	//---


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
