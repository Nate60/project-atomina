#include "OAS/attributes/AttrVelocity.hpp"
#include "pch.hpp"
#include "SysController.hpp"

namespace ATMA
{

    SysController::SysController(): SysBase(SystemType(System::Controller), "Controller")
    {
        std::bitset<ATConst::OBJECT_BIT_SIZE> first{};

        first.set(AttrType(Attribute::Controllable));
        first.set(AttrType(Attribute::Velocity));

        m_req.push_back(first);
    }

    SysController::~SysController() {}

    void SysController::update(const float &l_dt) {}

    void SysController::notify(const ObjectEventContext &l_e) {}

}
