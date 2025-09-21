#include "core/api.hpp"
#include "SysCollider.hpp"
#include "../AttributeManager.hpp"
#include "event/ObjectEventManager.hpp"
#include "OAS/attributes/AttrCollidable.hpp"
#include "util/ATConst.hpp"

namespace ATMA
{

    SysCollider::SysCollider(): SysBase(SystemType(System::Collider), "Collider")
    {
        m_req.push_back(std::bitset<ATConst::BITSET_SIZE>{});
        m_req[0].set(AttrType(Attribute::Collidable));
    }

    SysCollider::~SysCollider() {}

    void SysCollider::update(ATMAContext *l_ctx, const double &l_dt)
    {
        m_stopwatch.start();
        for(int i = 0; i < m_objects.size(); ++i)
        {
            std::shared_ptr<AttrCollidable> collideComp = l_ctx->m_attrMan->getAttribute<AttrCollidable>(
                m_objects[i].second, AttributeType(Attribute::Collidable)
            );
            for(int j = i + 1; j < m_objects.size(); ++j)
            {
                std::shared_ptr<AttrCollidable> otherComp = l_ctx->m_attrMan->getAttribute<AttrCollidable>(
                    m_objects[j].second, AttributeType(Attribute::Collidable)
                );
                Vec2<float> result{};
                if(getCollideVector(collideComp->m_collider, otherComp->m_collider, result))
                {
                    Props eventProps{};
                    eventProps["id1"] = std::make_any<unsigned int>(m_objects[i].second);
                    eventProps["id2"] = std::make_any<unsigned int>(m_objects[j].second);
                    eventProps["vec"] = std::make_any<Vec2<float>>(result);
                    l_ctx->m_eventMan->dispatchObjectEvent(
                        l_ctx, ObjectEventContext{ObjectEventType(ObjectEvent::Collision), eventProps}
                    );
                }
            }
        }
        m_stopwatch.stop();
        m_stopwatch.reset();
    }

    void SysCollider::notify(ATMAContext *l_ctx, const ObjectEventContext &l_e) {}

}
