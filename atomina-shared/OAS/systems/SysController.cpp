#include "OAS/attributes/AttrVelocity.hpp"
#include "pch.hpp"
#include "SysController.hpp"

namespace ATMA
{

    SysController::SysController(): SysBase(SystemType(System::Controller), "Controller")
    {
        m_req.set(AttrType(Attribute::Controllable));
        m_req.set(AttrType(Attribute::Velocity));
    }

    SysController::~SysController() {}

    void SysController::update(const long long &l_dt) 
    {

    }

    void SysController::notify(const ObjectEventContext &l_e) {}

}
