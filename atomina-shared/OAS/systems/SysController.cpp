#include "OAS/attributes/AttrVelocity.hpp"
#include "pch.hpp"
#include "SysController.hpp"

namespace ATMA
{

    SysController::SysController(): SysBase(SystemType(System::Controller))
    {
        m_req.set(AttrType(Attribute::Controllable));
        m_req.set(AttrType(Attribute::Velocity));
    }

    void SysController::update(const float &l_dt) {}

    void SysController::notify(const ObjectEventContext &l_e)
    {

        // auto &sfEvent = l_e.m_sfEvent.value();
        // auto &context = ATMAContext::getContext();
        // for(auto &obj: m_objects)
        // {
        //     std::shared_ptr<AttrVelocity> obj_vel =
        //         context.getAttribute<AttrVelocity>(obj, AttrType(Attribute::Velocity));

        //     auto acceleration = 0.0f;

        //     if(sfEvent.type == sf::Event::EventType::KeyPressed)
        //     {
        //         acceleration = 1.0f;
        //     }
        //     else if(sfEvent.type == sf::Event::EventType::KeyReleased)
        //     {
        //         acceleration = 0;
        //     }

        //     switch(sfEvent.key.code)
        //     {
        //     case sf::Keyboard::W:
        //         obj_vel->m_dy = -acceleration;
        //         break;
        //     case sf::Keyboard::S:
        //         obj_vel->m_dy = acceleration;
        //         break;
        //     default:
        //         break;
        //     }
        // }
    }

}
