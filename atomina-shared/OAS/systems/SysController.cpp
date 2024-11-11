#include "OAS/attributes/AttrVelocity.hpp"
#include "pch.hpp"
#include "SysController.hpp"

namespace ATMA
{

    SysController::SysController(): SysBase(SystemType(System::Controller), "Controller")
    {
        m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
        m_req[0].set(AttrType(Attribute::Controllable));
        m_req[0].set(AttrType(Attribute::Velocity));
    }

    SysController::~SysController() {}

    void SysController::update(const long long &l_dt) 
    {
        m_stopwatch.start();
        m_stopwatch.stop();
        m_stopwatch.reset();
    }

    void SysController::notify(const ObjectEventContext &l_e) {}

}
