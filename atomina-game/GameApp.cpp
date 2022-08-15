
#include "GameApp.hpp"

GameApp::GameApp() {

}

GameApp::~GameApp() {

}

void GameApp::run()
{
	// ATMA_ENGINE_INFO("Game is now running");
	// active = true;
	// ATMA::Window win{};
	// ATMA::ATMAContext ctx{};
	// ctx.m_event_manager = std::shared_ptr<ATMA::EventManager>{new ATMA::EventManager{}};
	// ctx.m_system_manager = std::shared_ptr<ATMA::SystemManager>{new ATMA::SystemManager{}};

	// ctx.m_system_manager->addSystem<ATMA::SysTranslator>(ATMA::System::Translator);
	// ctx.m_system_manager->addSystem<ATMA::SysController>(ATMA::System::Controller);
	// ctx.m_system_manager->addSystem<ATMA::SysRenderer>(ATMA::System::Renderer);
	// auto objMan = ctx.m_system_manager->getObjectManager();
	// auto objId = objMan->createObject();
	// objMan->addAttributeType<ATMA::AttrTranslatable>(ATMA::Attribute::Translatable);
	// objMan->addAttributeType<ATMA::AttrControllable>(ATMA::Attribute::Controllable);
	// objMan->addAttributeType<ATMA::AttrDrawable>(ATMA::Attribute::Drawable);
	// objMan->addAttribute(objId, ATMA::Attribute::Translatable);
	// objMan->addAttribute(objId, ATMA::Attribute::Controllable);
	// objMan->addAttribute(objId, ATMA::Attribute::Drawable);

	// std::bitset<ATConst::OBJECT_BIT_SIZE> bits = std::bitset<ATConst::OBJECT_BIT_SIZE>();
	// bits.set((int)ATMA::Attribute::Translatable);
	// bits.set((int)ATMA::Attribute::Controllable);
	// bits.set((int)ATMA::Attribute::Drawable);
	// ctx.m_system_manager->objectModified(objId, bits);


	// ATMA::StateManager stateMan{ctx};
	// GameState gameState{stateMan};

	// stateMan.registerState<GameState>(ATMA::State::COUNT);
	// ctx.m_event_manager->onStateChange(static_cast<ATMA::StateType>(ATMA::State::COUNT));

	// for(;;)
	// {
	// 	sf::Event sfE{};
	// 	ATMA::Event e{0, sfE};
	// 	win.popEvent(e);
	// 	auto &inner = std::get<sf::Event>(e.m_context);

	// 	if(e.m_type == sf::Event::EventType::KeyPressed || e.m_type == sf::Event::EventType::KeyReleased)
	// 	{
	// 		if(inner.key.code == sf::Keyboard::Escape)
	// 		{
	// 			ATMA_ENGINE_INFO("Escape key pressed");
	// 			break;
	// 		}
	// 		ctx.m_event_manager->handleEvent(e);
	// 		ctx.m_system_manager->handleEvents();
	// 	}
			
	// 	ctx.m_system_manager->update(1.0f);
	// 	std::shared_ptr<ATMA::SysRenderer> sys = ctx.m_system_manager->getSystem<ATMA::SysRenderer>(ATMA::System::Renderer);
	// 	win.clear();
	// 	win.draw(*sys);
	// 	win.display();
	// }
	// win.close();

}

void GameApp::shutdown()
{
	ATMA_ENGINE_INFO("Shutting down game");
	active = false;
}

std::unique_ptr<ATMA::Game> ATMA::CreateGame() {
	return std::unique_ptr<ATMA::Game>{new GameApp()};
}
