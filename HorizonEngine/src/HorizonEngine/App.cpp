#include "pch.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "HorizonEngine/Camera.h"

#include "App.h"

namespace Hzn
{
	App* App::m_Instance = nullptr;
	//! App class constructor, initializes the application
	App::App() : m_Running(true)
	{
		registerComponents();
		/*HZN_CORE_ASSERT(false, "application already initialized");*/
		m_Instance = this;
		m_Input = std::unique_ptr<Input>(Input::create());
		m_Window = std::unique_ptr<Window>(Window::create(800, 600, "HorizonEngine"));
		m_Window->setEventCallback(std::bind(&App::onEvent, this, std::placeholders::_1));
		m_Window->setVsync(true);

		m_ImguiLayer = new ImguiLayer();
		addOverlay(m_ImguiLayer);
	}

	App::~App() {}

	//! the main App run loop. This loop keeps the application running and updates and renders
	//! different layers
	void App::run()
	{
		HZN_CORE_WARN("App started running...");

		while (m_Running)
		{
			float currentFrameTime = glfwGetTime();
			TimeStep deltaTime = currentFrameTime - lastFrameTime;
			lastFrameTime = currentFrameTime;
			//! general layer update
			for (auto& layer : m_Layers)
			{
				layer->onUpdate(deltaTime);
			}

			//! updates UI components on any layers
			m_ImguiLayer->imguiBegin();
			for (auto& layer : m_Layers)
			{
				layer->onRenderImgui();
			}
			m_ImguiLayer->imguiEnd();

			m_Window->onUpdate();
		}
	}

	//! terminates the App run loop
	//! always returns true
	bool App::onWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	//! the onEvent function of application class that handles any events coming to the application
	void App::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&App::onWindowClose, this, std::placeholders::_1));

		/*auto val = Input::getMousePos();*/
		/*HZN_CORE_TRACE("{0}, {0}", val.first, val.second);*/

		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
		{
			(*it)->onEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	void App::registerComponents() {
		REGISTER(Component, Transform);
		REGISTER(Component, BoxCollider2D);
		REGISTER(Component, Rigidbody2D);
	}
}