//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <math/Vec.h>
#include <gfx/Forward.h>

namespace mud
{
	export_ MUD_GFX_EXPORT mat4 bxidentity();
	export_ MUD_GFX_EXPORT mat4 bxinverse(const mat4& mat);
	export_ MUD_GFX_EXPORT mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans);
	export_ MUD_GFX_EXPORT mat4 bxscale(const vec3& scale);
	// transpose because we are right-handed but bgfx assumes left-handed
	export_ MUD_GFX_EXPORT mat4 bxrotation(const quat& rot);
	//export_ MUD_GFX_EXPORT mat4 bxquat(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), &rot[0]); return result; }
	export_ MUD_GFX_EXPORT mat4 bxtranslation(const vec3& vec);
	export_ MUD_GFX_EXPORT mat4 bxmul(const mat4& lhs, const mat4& rhs);
	export_ MUD_GFX_EXPORT vec3 bxmul(const mat4& mat, const vec3& vec);
	export_ MUD_GFX_EXPORT vec3 bxmulh(const mat4& mat, const vec3& vec);
	export_ MUD_GFX_EXPORT mat4 bxlookat(const vec3& eye, const vec3& at);
	export_ MUD_GFX_EXPORT void bxlookat(mat4& result, const vec3& eye, const vec3& at, const vec3& up);
	export_ MUD_GFX_EXPORT mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up);
	export_ MUD_GFX_EXPORT mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc);
	export_ MUD_GFX_EXPORT mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc);
	export_ MUD_GFX_EXPORT mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc);
	export_ MUD_GFX_EXPORT mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans);
	export_ MUD_GFX_EXPORT mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans);
	 
	void debug_print_mat(const mat4& mat);

	export_ class refl_ MUD_GFX_EXPORT Node3
	{
	public:
		// @todo factor out scene management stuff from items, nodes, lights and add it to the graph / scene
		Node3(Scene* scene = nullptr, Ref object = {});

		attr_ Scene* m_scene = nullptr;
		attr_ uint16_t m_index = 0;

		attr_ vec3 m_position = Zero3;
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = Unit3;
		attr_ bool m_visible = true;

		Ref m_object;
		size_t m_last_updated = 0;

		mat4 transformTRS() const { return bxTRS(m_scale, m_rotation, m_position); }
		mat4 transformSRT() const { return bxSRT(m_scale, m_rotation, m_position); }
		mat4 transform() const { return transformTRS(); }

		vec3 axis(const vec3& dir) const { return normalize(rotate(m_rotation, dir)); }
		vec3 direction() const { return normalize(rotate(m_rotation, -Z3)); }

		//std::vector<Item*> m_items;
	};
}
