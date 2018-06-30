//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#ifdef MUD_PROTO
#include <proto/Complex.h>
#endif
#include <refl/Class.h>
#include <refl/Convert.h>
#include <ui/Structs/Window.h>
#include <ui/Structs/Container.h>
#include <ui/Sequence.h>
#include <uio/Types.h>
#include <uio/Unode.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Method.h>
#endif

namespace mud
{
	string object_name(Ref object)
	{
		return object ? to_name(type(object), object) : "null";
	}

	string object_icon(Ref object)
	{
		return object ? "(" + string(meta(object).m_name) + ")" : "";
	}

	void object_context(Widget& parent, Ref object, uint32_t mode)
	{
		Widget& self = ui::popup(parent, ui::PopupFlags::Modal);
		if(!self.m_open)
			parent.m_switch &= ~mode;

#ifdef MUD_PROTO
		if(meta(object).m_type_class == TypeClass::Complex)
			object = val<Complex>(object).m_construct;
#endif

		for(Method* method : cls(object).m_deep_methods)
		{
#ifdef MUD_PROTO
			Ref component = cls(object).get_related(object, *method->m_object_type);
#else
			Ref component = object;
#endif
			method_hook(self, component, *method);
		}
	}

	enum HookState
	{
		HOOK_CONTEXT = (1 << 0)
	};

	Widget& generic_object_item(Widget& parent, Ref object)
	{
		Widget& self = ui::multi_button(parent, carray<cstring, 2>{ object_icon(object).c_str(), object_name(object).c_str() });
		if(MouseEvent event = self.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			self.m_switch |= HOOK_CONTEXT;
		if((self.m_switch & HOOK_CONTEXT) != 0)
			object_context(self, object, HOOK_CONTEXT);
		return self;
	}

	Widget& object_button(Widget& parent, Ref object)
	{
		return generic_object_item(parent, object);
	}

	Widget& object_item(Widget& parent, Ref object)
	{
		if(DispatchItem::me().check(object))
			return DispatchItem::me().dispatch(object, parent);
		else
			return generic_object_item(parent, object);
	}

	bool object_item(Widget& parent, Ref object, Ref& selection)
	{
		Widget& self = object_item(parent, object);
		return ui::select_logic(self, object, selection);
	}

	bool object_item(Widget& parent, Ref object, std::vector<Ref>& selection)
	{
		Widget& self = object_item(parent, object);
		return ui::select_logic(self, object, selection);
	}
}
