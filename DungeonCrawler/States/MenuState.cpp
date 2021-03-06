#include "MenuState.h"
#include "StateManager.h"
#include "System/Log.h"
#include "System/Input.h"
#include "Vendor/ImGui/imgui.h"
#include "../Audio/AudioEngine.h"

#include <Graphics/ShaderMap.h>
#include <Globals/Settings.h>

#include <thread>
#include "PlayState.h"

using namespace std::chrono_literals;

void loadScreen(const bool& completed) {
	while (!completed) {
		//LOG_INFO("LOADING");
		std::this_thread::sleep_for(10ms);
	}
}

MenuState::MenuState() {
	m_camera = new UICamera();
	m_uiManager = new UIManager(m_camera);
	m_glInit = new GLinit();
	createUIElements();
	AudioEngine::loadSSO("Menu.sso");
	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(glfwGetCurrentContext(), cursor);
}

MenuState::~MenuState()
{
	delete m_camera;
	delete m_glInit;
	delete m_uiManager;
}

void MenuState::createUIElements()
{
	m_logo = new Image(
		glm::vec2((float)Settings::getScreenWidth() * 0.5f, (float)Settings::getScreenHeight() * 0.8f),
		glm::vec2(300.f, 150.f),
		m_glInit,
		"logo.png");

	m_playButton = new Button(
		glm::vec2((float)Settings::getScreenWidth() * 0.5f, (float)Settings::getScreenHeight() * 0.5),
		glm::vec2(150.f, 100.f),
		m_glInit,
		"Play-Sel.png",
		"Play-UnSel.png");

	m_exitButton = new Button(
		glm::vec2((float)Settings::getScreenWidth() * 0.5f, (float)Settings::getScreenHeight() * 0.30),
		glm::vec2(150.f, 100.f),
		m_glInit,
		"Exit-Sel.png",
		"Exit-UnSel.png");

	m_uiManager->registerUIElement(m_logo);
	m_uiManager->registerUIElement(m_playButton);
	m_uiManager->registerUIElement(m_exitButton);
}

void MenuState::update(float dt) {
	m_camera->update(dt);
	m_uiManager->update(dt);

	if (Input::isMousePressed(GLFW_MOUSE_BUTTON_1)) {
		AudioEngine::play("LMouseClick", 1.0f);
	}


	if (m_playButton->isPressed()) {
		bool completed = false;

		//Have a side thread output text while it's loading
		std::thread b(loadScreen, std::ref(completed));
		//The main thread will then create the playstate
		PlayState* state = new PlayState();
		completed = true;
		b.join();

		AudioEngine::unloadSSO("Menu.sso");
		m_stateManager->pushTemporaryState(state); // this is where the loading happens

	}

	if (m_exitButton->isPressed()) {
		glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
	}

	AudioEngine::update();
}

void MenuState::renderImGUI()
{
	ImGui::Begin("MenuState");

	ImGui::Text("Press right mouse to switch to the play state");

	ImGui::End();
}


void MenuState::render() 
{
	m_uiManager->render();
}

