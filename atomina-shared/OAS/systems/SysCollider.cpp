#include "core/api.hpp"
#include "SysCollider.hpp"

namespace ATMA
{

    SysCollider::SysCollider(): SysBase(SystemType(System::Collider), "Collider")
    {
        m_req.set(AttrType(Attribute::Collidable));
    }

    SysCollider::~SysCollider() {}

    void SysCollider::update(const long long &l_dt)
    {
        ATMAContext &ctx = ATMAContext::getContext();
        for(int i = 0; i < m_objects.size(); ++i)
        {
            std::shared_ptr<AttrCollidable> collideComp = ctx.getAttribute<AttrCollidable>(
                m_objects[i], AttributeType(Attribute::Collidable)
            );
            for(int j = i + 1; j < m_objects.size(); ++j)
            {
                std::shared_ptr<AttrCollidable> otherComp = ctx.getAttribute<AttrCollidable>(
                    m_objects[j], AttributeType(Attribute::Collidable)
                );
                Vec2<float> result{};
                if(getCollideVector(collideComp->m_collider, otherComp->m_collider, result))
                {
                    ATMA_ENGINE_TRACE(
                        "Object id {0} and object id {1} collided", m_objects[i], m_objects[j]
                    );
                    Props eventProps{};
                    eventProps["id1"] = std::make_any<unsigned int>(m_objects[i]);
                    eventProps["id2"] = std::make_any<unsigned int>(m_objects[j]);
                    eventProps["vec"] = std::make_any<Vec2<float>>(result);
                    ctx.dispatchObjectEvent(ObjectEventContext{
                        ObjectEventType(ObjectEvent::Collision), eventProps});
                }
            }
        }
    }

    void SysCollider::notify(const ObjectEventContext &l_e) {}

}