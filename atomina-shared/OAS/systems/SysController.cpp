#include "OAS/attributes/AttrVelocity.hpp"
#include "core/ATMAContext.hpp"
#include "pch.hpp"
#include "util/ATConst.hpp"
#include "SysController.hpp"

namespace ATMA
{

    SysController::SysController(): SysBase(SystemType(System::Controller), "Controller")
    {
        m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
        m_req[0].set(AttrType(Attribute::Controllable));
        m_req[0].set(AttrType(Attribute::Velocity));
    }

    SysController::~SysController() {}

    void SysController::update(ATMAContext *l_ctx, const double &l_dt) {}

    void SysController::notify(ATMAContext *l_ctx, const ObjectEventContext &l_e) {}

}
