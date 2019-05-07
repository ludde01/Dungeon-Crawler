#include "GameOverState.h"
#include <System/Application.h>
#include "MenuState.h"
#include "Vendor/ImGui/imgui.h"


GameOverState::GameOverState()
{
	m_camera = new UICamera();
	m_manager = new UIManager(m_camera);
	m_glInit = new GLinit();

	m_logo = new Image(
		glm::vec2((float)Application::windowWidth * 0.5f, (float)Application::windowHeight *0.8f),
		glm::vec2(300.f, 200.f),
		m_glInit,
		"logo.png");

	m_dead = new Image(
		glm::vec2((float)Application::windowWidth * 0.5f, (float)Application::windowHeight * 0.5f),
		glm::vec2(300.f, 100.f),
		m_glInit,
		"Dead-New.png");

	m_playAgain = new Button(glm::vec2(Application::windowWidth * 0.7, Application::windowHeight * 0.2f),
		glm::vec2(400.f, 150.f), m_glInit,
		"PlayAgain-Sel.png",
		"PlayAgain-Unsel.png");

	m_menu = new Button(glm::vec2(Application::windowWidth * 0.3, Application::windowHeight * 0.2f),
		glm::vec2(400.f, 150.f), m_glInit,
		"MainMenu-Sel.png",
		"MainMenu-UnSel.png");

	m_manager->registerUIElement(m_playAgain);
	m_manager->registerUIElement(m_menu);
	m_manager->registerUIElement(m_logo);
	m_manager->registerUIElement(m_dead);

}

GameOverState::~GameOverState()
{
	delete m_camera;
	delete m_glInit;
	delete m_manager;
}

void GameOverState::update(float dt)
{
	m_camera->update(dt);
	m_manager->update(dt);

	if (m_playAgain->isPressed())
	{
		m_stateManager->popState();
		return;
	}

	if (m_menu->isPressed())
	{
		MenuState* menu = new MenuState();
		m_stateManager->setState(menu);
		return;
	}
}

void GameOverState::renderImGUI()
{
	ImGui::Begin("GameOverState");

	ImGui::Text("Press right mouse to switch to the play state");

	ImGui::End();
}

void GameOverState::render()
{
	m_manager->render();
}
