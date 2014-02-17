#include "PushComponentVisitor.h"
#include "LuaT\stack_ops.h"
#include <exception>
#include "LuaComponent.h"
#include "..\LuaT\lua_ref.h"

using namespace xihad;
using namespace render3d;
using namespace luaT;
namespace xihad { namespace script
{
	void PushComponentVisitor::visit( render3d::AnimatedMeshComponent& c )
	{
		genericVisit(c);
	}

	void PushComponentVisitor::visit( script::LuaComponent& c )
	{
		LuaRef ref = c.getTable();
		ref.pushOnto(L);
	}

	void PushComponentVisitor::visit( render3d::MeshComponent& c )
	{
		genericVisit(c);
	}

	void PushComponentVisitor::visit( render3d::LightComponent& c )
	{
		genericVisit(c);
	}

	void PushComponentVisitor::visit( render3d::CameraComponent& c )
	{
		genericVisit(c);
	}

	void PushComponentVisitor::visit( render3d::BillboardComponent& c )
	{
		genericVisit(c);
	}

	bool PushComponentVisitor::handleUnkownVisitable( ngn::BaseVisitable& c )
	{
		// throw std::exception("unkown object");
		return false;
	}


}}