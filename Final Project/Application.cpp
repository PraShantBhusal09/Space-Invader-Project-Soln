#include "Application.h"
#include "Display.h"
#include "Menu.h"
#include "Splash.h"

Application::Application()
{
	Display::init();
	this->pushState(std::make_unique<State::Splash>(*this));
}

Application::~Application()
{
}

void Application::runGameLoop()
{
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Time lastUpdate = sf::Time::Zero;
	sf::Clock frameClock;

	while (Display::isOpen())
	{
		Display::checkWindowEvents();

		Display::clear();

		this->m_states.top()->input();

		lastUpdate += frameClock.restart();
		while (lastUpdate > timePerFrame)
		{
			lastUpdate -= timePerFrame;
			this->m_states.top()->update(timePerFrame.asSeconds());
		}

		this->m_states.top()->draw();

		Display::display();
	}
}

void Application::pushState(std::unique_ptr<State::GameState> state)
{
	this->m_states.push(std::move(state));
}

void Application::popState()
{
	this->m_states.pop();
}

void Application::changeState(std::unique_ptr<State::GameState> state)
{
	this->popState();
	this->pushState(std::move(state));
}
