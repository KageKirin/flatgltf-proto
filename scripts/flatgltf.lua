-- premake for flatgltf

flatgltf_root = path.join(SCAFFOLDING_THIRDPARTY_DIR, "flatgltf")

flatgltf_includedirs = {
	flatgltf_root,
    path.join(flatgltf_root, "include"),
}

flatgltf_libdirs = {}
flatgltf_links = {}
flatgltf_defines = {}

---

if generate_thirdparty_projects and generate_thirdparty_projects == true then

project "flatgltf_1_0"
	kind "StaticLib"
	language "C++"
	flags {}

	includedirs {
		flatgltf_includedirs,
		flatbuffers_includedirs,
	}

	defines {
	}

	files {
		path.join(flatgltf_root, "include", "flatgltf/1.0", "**.h"),
		path.join(flatgltf_root, "include", "flatgltf/1.0", "**.hpp"),
		path.join(flatgltf_root, "include", "flatgltf/1.0", "**.hxx"),
		path.join(flatgltf_root, "schemas/1.0", "**.fbs"),
		path.join(flatgltf_root, "src/1.0", "**.cpp"),
		path.join(flatgltf_root, "src/1.0", "**.cxx"),
	}

	links {
		"flatbuffers",
	}

build_cppfwd("flatgltf_1_0")

---

project "flatgltf_2_0"
	kind "StaticLib"
	language "C++"
	flags {}

	includedirs {
		flatgltf_includedirs,
		flatbuffers_includedirs,
	}

	defines {
	}

	files {
		path.join(flatgltf_root, "include", "flatgltf/2.0", "**.h"),
		path.join(flatgltf_root, "include", "flatgltf/2.0", "**.hpp"),
		path.join(flatgltf_root, "include", "flatgltf/2.0", "**.hxx"),
		path.join(flatgltf_root, "schemas/2.0", "**.fbs"),
		path.join(flatgltf_root, "src/2.0", "**.cpp"),
		path.join(flatgltf_root, "src/2.0", "**.cxx"),
	}

	links {
		"flatbuffers",
	}

build_cppfwd("flatgltf_2_0")


dofile("flatgltf_unittests.lua")

end -- _OPTIONS["with-thirdparty"] ~= nil

---

