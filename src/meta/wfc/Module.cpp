#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/wfc/Module.h>
#include <meta/wfc/Convert.h>
#endif

#include <wfc/Api.h>
#define MUD_WFC_REFLECTION_IMPL
#include <meta/wfc/Meta.h>

namespace mud
{
	mud_wfc::mud_wfc()
		: Module("mud::wfc", { &mud_infra::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m() })
	{
		// setup reflection meta data
		mud_wfc_meta(*this);
	}
}

#ifdef MUD_WFC_MODULE
extern "C"
Module& getModule()
{
		return mud_wfc::m();
}
#endif
