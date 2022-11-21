#include "OAS/Attribute.hpp"
#include "OAS/SysBase.hpp"
#include "event/ObjectEvent.hpp"
#include "pch.hpp"
#include "SysGUI.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    SysGUI::SysGUI(): SysBase(SystemType(System::GUI))
    {
        m_req.set(AttributeType(Attribute::MouseRegion));
        m_req.set(AttributeType(Attribute::MouseRegion));
    }

    SysGUI::~SysGUI() {}

    void SysGUI::update(const float &l_dt) {}

    void SysGUI::notify(const ObjectEventContext &l_e)
    {
        auto &ctx = ATMAContext::getContext();
        for(auto &objID: m_objects)
        {
            auto mouse = l_e.m_properties.getAs<sf::Vector2i>("mousepos");
            ATMA_ENGINE_INFO("Mouse current location is {0:d} , {1:d}", mouse.x, mouse.y);
            auto attrRegion =
                ctx.getAttribute<AttrMouseRegion>(objID, AttributeType(Attribute::MouseRegion));
            ATMA_ENGINE_INFO(
                "Trigger Region is x:{0:d} y:{1:d} w:{2:d} h:{3:d}",
                attrRegion->m_region.left,
                attrRegion->m_region.top,
                attrRegion->m_region.width,
                attrRegion->m_region.height
            );
            if(attrRegion->m_region.contains(mouse))
            {
                if(l_e.m_objectEventType == ObjectEventType(ObjectEvent::MousePressed))
                {
                    ctx.getAttribute<AttrMouseTrigger>(
                           objID, AttributeType(Attribute::MouseTrigger)
                    )
                        ->m_mousePressFunc(l_e);
                }
                else if(l_e.m_objectEventType == ObjectEventType(ObjectEvent::MouseReleased))
                {
                    ctx.getAttribute<AttrMouseTrigger>(
                           objID, AttributeType(Attribute::MouseTrigger)
                    )
                        ->m_mouseReleaseFunc(l_e);
                }
                else if(l_e.m_objectEventType == ObjectEventType(ObjectEvent::MouseOver))
                {
                    ctx.getAttribute<AttrMouseTrigger>(
                           objID, AttributeType(Attribute::MouseTrigger)
                    )
                        ->m_mouseOverFunc(l_e);
                }
            }
        }
    }

}