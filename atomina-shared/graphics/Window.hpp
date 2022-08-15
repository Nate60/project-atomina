#include "../pch.hpp"
#include "../core/api.hpp"
#include "../event/EventContext.hpp"

namespace ATMA
{

	using ViewId = unsigned int;

	class ATMA_API Window
	{
	public:
		Window(const std::string &l_name = "Project Atomina", const sf::Vector2u &l_dimensions = {640,480});
		~Window();

		void beginDraw();
		void endDraw();

		void update();

		bool isDone() const;
		bool isFullscreen() const;
		bool isFocused() const;

		void toggleFullscreen();
		void close();

		sf::Vector2u getWindowSize();
		sf::Rect<float> getViewSpace();

		EventContext popEvent();

		void clear();
		void display();
		void draw(const sf::Drawable &l_drawable, const sf::RenderStates &l_states = sf::RenderStates::Default);
	
	private:
		std::unordered_map<ViewId, sf::View> m_layers;
		bool m_done{false};
		bool m_fullscreen{false};
		bool m_focused{false};
		sf::RenderWindow m_window;

	};

}