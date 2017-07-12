#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glb.h"

#include <algorithm>
#include <cassert>	//TODO: improve using catch later
#include <memory>
#include <string>
#include <vector>

namespace glTF_2_0
{
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	glTFid_t add_Accessor(glTF_Container& cntr, Accessor_t&& accessor)
	{
		cntr.root->accessors.push_back(std::move(accessor));
		return glTFid(cntr.root->accessors.size()) - 1;
	}

	glTFid_t add_Accessor(glTF_Container& cntr, AccessorT accessor)
	{
		return add_Accessor(cntr, Accessor_t{new AccessorT(std::move(accessor))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Animation(glTF_Container& cntr, Animation_t&& animation)
	{
		cntr.root->animations.push_back(std::move(animation));
		return glTFid(cntr.root->animations.size()) - 1;
	}

	glTFid_t add_Animation(glTF_Container& cntr, AnimationT animation)
	{
		return add_Animation(cntr, Animation_t{new AnimationT(std::move(animation))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Buffer(glTF_Container& cntr, Buffer_t&& buffer)
	{
		cntr.root->buffers.push_back(std::move(buffer));
		return glTFid(cntr.root->buffers.size()) - 1;
	}

	glTFid_t add_Buffer(glTF_Container& cntr, BufferT buffer)
	{
		return add_Buffer(cntr, Buffer_t{new BufferT(std::move(buffer))});
	}

	/// adds buffer as base64 string
	glTFid_t add_Buffer(glTF_Container& cntr, const std::vector<uint8_t>& bufferdata)
	{
		BufferT buffer;
		buffer.byteLength = bufferdata.size();
		buffer.uri		  = base64_encode(bufferdata.data(), bufferdata.size());
		return add_Buffer(cntr, std::move(buffer));
	}

	/// adds buffer as external bindata, given name
	/// returns -1 if bindata with same name already exists
	glTFid_t add_Buffer(glTF_Container& cntr, std::vector<uint8_t> bufferdata, const char* name)
	{
		assert(name);
		BufferT buffer;
		buffer.byteLength = bufferdata.size();
		buffer.uri		  = name;
		auto it			  = cntr.bindata.find(name);
		if (it != end())
			return -1;
		cntr.bindata[name].swap(bufferdata);
		return add_Buffer(cntr, std::move(buffer));
	}

	//-------------------------------------------------------------------------

	glTFid_t add_BufferView(glTF_Container& cntr, BufferView_t&& bufferview)
	{
		cntr.root->bufferviews.push_back(std::move(bufferview));
		return glTFid(cntr.root->bufferviews.size()) - 1;
	}

	glTFid_t add_BufferView(glTF_Container& cntr, BufferViewT bufferview)
	{
		return add_BufferView(cntr, BufferView_t{new BufferViewT(std::move(bufferview))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Camera(glTF_Container& cntr, Camera_t&& camera)
	{
		cntr.root->cameras.push_back(std::move(camera));
		return glTFid(cntr.root->cameras.size()) - 1;
	}

	glTFid_t add_Camera(glTF_Container& cntr, CameraT camera)
	{
		return add_Camera(cntr, Camera_t{new CameraT(std::move(camera))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Image(glTF_Container& cntr, Image_t&& image)
	{
		cntr.root->images.push_back(std::move(image));
		return glTFid(cntr.root->images.size()) - 1;
	}

	glTFid_t add_Image(glTF_Container& cntr, ImageT image)
	{
		return add_Image(cntr, Image_t{new ImageT(std::move(image))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Material(glTF_Container& cntr, Material_t&& material)
	{
		cntr.root->materials.push_back(std::move(material));
		return glTFid(cntr.root->materials.size()) - 1;
	}

	glTFid_t add_Material(glTF_Container& cntr, MaterialT material)
	{
		return add_Material(cntr, Material_t{new MaterialT(std::move(material))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Mesh(glTF_Container& cntr, Mesh_t&& mesh)
	{
		cntr.root->meshs.push_back(std::move(mesh));
		return glTFid(cntr.root->meshs.size()) - 1;
	}

	glTFid_t add_Mesh(glTF_Container& cntr, MeshT mesh)
	{
		return add_Mesh(cntr, Mesh_t{new MeshT(std::move(mesh))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Node(glTF_Container& cntr, Node_t&& node)
	{
		cntr.root->nodes.push_back(std::move(node));
		return glTFid(cntr.root->nodes.size()) - 1;
	}

	glTFid_t add_Node(glTF_Container& cntr, NodeT node)
	{
		return add_Node(cntr, Node_t{new NodeT(std::move(node))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Sampler(glTF_Container& cntr, Sampler_t&& sampler)
	{
		cntr.root->samplers.push_back(std::move(sampler));
		return glTFid(cntr.root->samplers.size()) - 1;
	}

	glTFid_t add_Sampler(glTF_Container& cntr, SamplerT sampler)
	{
		return add_Sampler(cntr, Sampler_t{new SamplerT(std::move(sampler))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Scene(glTF_Container& cntr, Scene_t&& scene)
	{
		cntr.root->scenes.push_back(std::move(scene));
		return glTFid(cntr.root->scenes.size()) - 1;
	}

	glTFid_t add_Scene(glTF_Container& cntr, SceneT scene)
	{
		return add_Scene(cntr, Scene_t{new SceneT(std::move(scene))});
	}


	glTFid_t add_Scene(glTF_Container& cntr, SceneT scene, bool display)
	{
		auto id = add_Scene(cntr, scene);
		assert(id >= 0);
		if (display && id >= 0)
		{
			cntr.root->scene = id;
		}
		return id;
	}

	glTFid_t add_Scene(glTF_Container& cntr, Scene_t&& scene, bool display)
	{
		auto id = add_Scene(cntr, scene);
		assert(id >= 0);
		if (display && id >= 0)
		{
			cntr.root->scene = id;
		}
		return id;
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Skin(glTF_Container& cntr, Skin_t&& skin)
	{
		cntr.root->skins.push_back(std::move(skin));
		return glTFid(cntr.root->skins.size()) - 1;
	}

	glTFid_t add_Skin(glTF_Container& cntr, SkinT skin)
	{
		return add_Skin(cntr, Skin_t{new SkinT(std::move(skin))});
	}

	//-------------------------------------------------------------------------

	glTFid_t add_Texture(glTF_Container& cntr, Texture_t&& texture)
	{
		cntr.root->textures.push_back(std::move(texture));
		return glTFid(cntr.root->textures.size()) - 1;
	}

	glTFid_t add_Texture(glTF_Container& cntr, TextureT texture)
	{
		return add_Texture(cntr, Texture_t{new TextureT(std::move(texture))});
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	/// getters

	AccessorT* const get_Accessor(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->accessors.size())
			return nullptr;
		if (id == cntr.root->accessors.size())
			return cntr.root->accessors.back().get();
		return cntr.root->accessors.at(id).get();
	}

	AnimationT* const get_Animation(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->animations.size())
			return nullptr;
		if (id == cntr.root->animations.size())
			return cntr.root->animations.back().get();
		return cntr.root->animations.at(id).get();
	}

	BufferT* const get_Buffer(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->buffers.size())
			return nullptr;
		if (id == cntr.root->buffers.size())
			return cntr.root->buffers.back().get();
		return cntr.root->buffers.at(id).get();
	}

	BufferViewT* const get_BufferView(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->bufferviews.size())
			return nullptr;
		if (id == cntr.root->bufferviews.size())
			return cntr.root->bufferviews.back().get();
		return cntr.root->bufferviews.at(id).get();
	}

	CameraT* const get_Camera(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->cameras.size())
			return nullptr;
		if (id == cntr.root->cameras.size())
			return cntr.root->cameras.back().get();
		return cntr.root->cameras.at(id).get();
	}

	ImageT* const get_Image(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->images.size())
			return nullptr;
		if (id == cntr.root->images.size())
			return cntr.root->images.back().get();
		return cntr.root->images.at(id).get();
	}

	MaterialT* const get_Material(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->materials.size())
			return nullptr;
		if (id == cntr.root->materials.size())
			return cntr.root->materials.back().get();
		return cntr.root->materials.at(id).get();
	}

	MeshT* const get_Mesh(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->meshs.size())
			return nullptr;
		if (id == cntr.root->meshs.size())
			return cntr.root->meshs.back().get();
		return cntr.root->meshs.at(id).get();
	}

	NodeT* const get_Node(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->nodes.size())
			return nullptr;
		if (id == cntr.root->nodes.size())
			return cntr.root->nodes.back().get();
		return cntr.root->nodes.at(id).get();
	}

	SamplerT* const get_Sampler(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->samplers.size())
			return nullptr;
		if (id == cntr.root->samplers.size())
			return cntr.root->samplers.back().get();
		return cntr.root->samplers.at(id).get();
	}

	SceneT* const get_Scene(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->scenes.size())
			return nullptr;
		if (id == cntr.root->scenes.size())
			return cntr.root->scenes.back().get();
		return cntr.root->scenes.at(id).get();
	}

	SkinT* const get_Skin(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->skins.size())
			return nullptr;
		if (id == cntr.root->skins.size())
			return cntr.root->skins.back().get();
		return cntr.root->skins.at(id).get();
	}

	TextureT* const get_Texture(glTF_Container& cntr, glTFid_t id)
	{
		assert(id >= 0);
		if (id < 0)
			return nullptr;
		if (id > cntr.root->textures.size())
			return nullptr;
		if (id == cntr.root->textures.size())
			return cntr.root->textures.back().get();
		return cntr.root->textures.at(id).get();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	glTFid_t add_Buffer(glTF_Container& cntr, const std::vector<uint8_t>& bufferdata)
	{
		BufferT buffer;
		buffer.byteLength = bufferdata.size();
		buffer.uri		  = base64_encode(bufferdata.data(), bufferdata.size());
		return add_Buffer(cntr, std::move(buffer));
	}

	/// adds buffer as external bindata, given name
	/// returns -1 if bindata with same name already exists
	glTFid_t add_Buffer(glTF_Container& cntr, std::vector<uint8_t> bufferdata, const char* name)
	{
		assert(name);
		BufferT buffer;
		buffer.byteLength = bufferdata.size();
		buffer.uri		  = name;
		auto it			  = cntr.bindata.find(name);
		if (it != end())
			return -1;
		cntr.bindata[name].swap(bufferdata);
		return add_Buffer(cntr, std::move(buffer));
	}

	//-------------------------------------------------------------------------

	add_TypedDataBuffer_ReturnT add_TypedDataBuffer(glTF_Container& cntr, add_TypedDataBuffer_ParamT param, const char* name = nullptr);
	{
		add_TypedDataBuffer_ReturnT ret;
		ret.bufferId = name ? add_Buffer(cntr, param.bufferdata) : add_Buffer(cntr, std::move(param.bufferdata), name);

		ret.bufferViewIdsAndAccessorIds.reserve(param.bufferViewsAndAccessors.size());
		std::transform(param.bufferviewsAndAccessors.begin(),
					   param.bufferviewsAndAccessors.end(),
					   std::back_inserter(ret.bufferViewIdsAndAccessorIds),
					   [& bufferId = ret.bufferId](auto& bv) {
						   bv.buffer = bufferId;
						   add_TypedDataBuffer_ReturnT::BufferViewIdAndAccessorIds rv;
						   rv.bufferViewId = add_BufferView(cntr, std::move(bv));
						   rv.accessorIds.reserve(bv.accessors.size());
						   std::transform(bv.accessors.begin(), bv.accessors.end(), std::back_inserter(rv.accessorIds), [& bvId = rv.bufferViewId](auto& ac) {
							   ac.bufferView = bvId;
							   return add_Accessor(cntr, std::move(ac));
						   });
						   return rv;
					   });
		return ret;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
