#pragma once
#include <atomina.hpp>

class SysFly : public ATMA::SysBase
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
    /**
     * Default Constructor
     */
    SysFly(): SysBase(ATMA::SystemType(ATMA::System::COUNT), "Fly")
    {
        m_req.set(ATMA::AttrType(ATMA::Attribute::Shape));
        m_req.set(ATMA::AttrType(ATMA::Attribute::Velocity));
        m_req.set(ATMA::AttrType(ATMA::Attribute::Controllable));
        m_req.set(ATMA::AttrType(ATMA::Attribute::Render));
    }

    /**
     * Updates all attributes contained in the systems with respect to
     * how many ticks have passed
     * @param l_dt time since last update
     */
    virtual void update(const long long &l_dt) override
    {
        for(auto &id :m_objects)
        {
            auto vel = ctx.getAttribute<ATMA::AttrVelocity>(id,ATMA::AttributeType(ATMA::Attribute::Velocity));
            if (vel->m_dpos.y > -2)
            {
                vel->m_dpos.y -= (l_dt >> 23)/700.f;
            }
            else
            {
                vel->m_dpos.y = -2;
            }

            if (vel->m_drot > -2)
            {
                vel->m_drot -= (l_dt >> 23) / 40.f;
            }
            else
            {
                vel->m_drot = -2;
            }
            auto pos = ctx.getAttribute<ATMA::AttrShape>(
                id, ATMA::AttributeType(ATMA::Attribute::Shape)
            );
            auto renderPos =
                ctx.getAttribute<ATMA::AttrRenderable>(id, ATMA::AttributeType(ATMA::Attribute::Render));
            auto collider =
                ctx.getAttribute<ATMA::AttrCollidable>(id, ATMA::AttributeType(ATMA::Attribute::Collidable));
            if (pos->m_pos.y < -0.85f)
            {
                ctx.dispatchObjectEvent(ATMA::ObjectEventContext{GameEventType(GameEventEnum::GAMEOVER), ATMA::Props{}});
                vel->m_drot = 0;
                pos->m_pos.y = -0.85f;
            }
            else if( pos->m_pos.y > 0.85)
            {
                ctx.dispatchObjectEvent(ATMA::ObjectEventContext{GameEventType(GameEventEnum::GAMEOVER), ATMA::Props{}});
                vel->m_dpos.y = -0.02f;
                pos->m_pos.y = 0.85;
            }
            renderPos->m_screenPos.x = pos->m_pos.x;
            renderPos->m_screenPos.y = pos->m_pos.y;
            renderPos->m_rot = pos->m_rot;
            collider->m_collider.setBase(ATMA::Vec2<float>{pos->m_pos.x, pos->m_pos.y});
            collider->m_collider.setRotation(pos->m_rot);

        }
    }

    /**
     * Triggers any event specific functionality of the system
     * @param l_e event details of the passed event
     */
    virtual void notify(const ATMA::ObjectEventContext& l_e) override
    {
        for (auto& id : m_objects)
        {
            auto vel = ctx.getAttribute<ATMA::AttrVelocity>(
                id, ATMA::AttributeType(ATMA::Attribute::Velocity)
            );
            vel->m_dpos.y = 0.03f;
            vel->m_drot = 0;
            auto shape = ctx.getAttribute<ATMA::AttrShape>(id, ATMA::AttributeType(ATMA::Attribute::Shape));
            shape->m_rot = 15.f;

            
        }
    }

};