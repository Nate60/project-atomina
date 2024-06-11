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
        m_stopwatch.start();
        m_stopwatch.stop();
        // ATMA_ENGINE_TRACE("Controller update took {}ms", m_stopwatch.getElapsedDuration()/1000000.0);
        m_stopwatch.reset();
    }

    void SysController::notify(const ObjectEventContext &l_e) {}

}
