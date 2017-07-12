#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"

#include "glTF_internal_types.h"

namespace glTF_2_0
{
	using namespace detail;

	///-----------------------------------------------------------------------
	/// utility
	///-----------------------------------------------------------------------

	/// prepares glTF data for GLB serialization
	//- changes URIs
	//- merges all mapped bindata into a single blob
	//- changes bufferViews accordingly
	bool binarize_glTFData(glTF_Object* obj)
	{
	}

	//---

	/// prepares glTF data for glTF-embedded format
	//- changes URIs to contain base64 encoded buffers
	//- changes bufferViews accordingly
	bool embed_glTFData(glTF_Object* obj)
	{
	}

	//---

	/// prepares glTF data for glTF-multi format
	//- changes URIs to reference external buffers
	//- changes bufferViews accordingly
	bool dislodge_glTFData(glTF_Object* obj)
	{
	}

	//---

	/// prepares glTF data for glTF-multi format
	//- splits buffers into multiple buffers according to bufferViews
	//- changes bufferViews accordingly
	bool split_glTFData(glTF_Object* obj)
	{
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
