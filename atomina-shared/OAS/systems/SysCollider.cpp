#include "core/api.hpp"
#include "SysCollider.hpp"

namespace ATMA
{

    SysCollider::SysCollider(): SysBase(SystemType(System::Collider), "Collider")
    {
        m_req.push_back(std::bitset<ATConst::OBJECT_BIT_SIZE>{});
        m_req[0].set(AttrType(Attribute::Collidable));
    }

    SysCollider::~SysCollider() {}

    void SysCollider::update(const long long &l_dt)
    {
        m_stopwatch.start();
        ATMAContext &ctx = ATMAContext::getContext();
        for(int i = 0; i < m_objects.size(); ++i)
        {
            std::shared_ptr<AttrCollidable> collideComp = ctx.getAttribute<AttrCollidable>(
                m_objects[i].second, AttributeType(Attribute::Collidable)
            );
            for(int j = i + 1; j < m_objects.size(); ++j)
            {
                std::shared_ptr<AttrCollidable> otherComp = ctx.getAttribute<AttrCollidable>(
                    m_objects[j].second, AttributeType(Attribute::Collidable)
                );
                Vec2<float> result{};
                if(getCollideVector(collideComp->m_collider, otherComp->m_collider, result))
                {
                    ATMA_ENGINE_TRACE(
                        "Object id {0} and object id {1} collided", m_objects[i].second, m_objects[j].second
                    );
                    Props eventProps{};
                    eventProps["id1"] = std::make_any<unsigned int>(m_objects[i].second);
                    eventProps["id2"] = std::make_any<unsigned int>(m_objects[j].second);
                    eventProps["vec"] = std::make_any<Vec2<float>>(result);
                    ctx.dispatchObjectEvent(ObjectEventContext{
                        ObjectEventType(ObjectEvent::Collision), eventProps});
                }
            }
        }
        m_stopwatch.stop();
        // ATMA_ENGINE_TRACE("Collider update took {}ms", m_stopwatch.getElapsedDuration()/1000000.0);
        m_stopwatch.reset();
    }

    void SysCollider::notify(const ObjectEventContext &l_e) {}

}