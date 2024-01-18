#include "pch.h"
#include "Application.h"

namespace Ash
{
	Application* Application::s_ActiveApplication = nullptr;

	Application::Application(const Config& config)
		: m_Config(config), m_Context(m_Config)
	{
		if (s_ActiveApplication == nullptr)
		{
			SetActive();
		}
	}

	void Application::Run()
	{
		float lastTime = (float)glfwGetTime();

		while (!glfwWindowShouldClose(m_Context.Window))
		{
			float time = (float)glfwGetTime();
			float deltaTime = time - lastTime;
			lastTime = time;

			// m_Scene.OnUpdate(deltaTime);
			Update(deltaTime);
			Draw();

			// ImGui_ImplVulkan_NewFrame();
			// ImGui_ImplGlfw_NewFrame();
			// ImGui::NewFrame();

			DrawUi();

			// ImGui::Render();

			glfwPollEvents();
		}
	}

	void Application::DispatchEvent(Event& event)
	{
		GetActive().OnEvent(event);
	}

	void Application::SetActive()
	{
		s_ActiveApplication = this;
	}

	void Application::AddLayer(const Layer& layer)
	{
		m_Layers.push_back(layer);
	}

	void Application::RemoveLayer(const Layer& layer)
	{
		for (auto it = m_Layers.begin(); it != m_Layers.end(); it++)
		{
			if (layer == *it)
			{
				m_Layers.erase(it);
				break;
			}
		}
	}

	void Application::OnEvent(Event& event)
	{
		if (event.HasType(EventType::WindowResize))
		{
			ResizeWindow(event.Cast<WindowResizeEvent>());
		}

		for (Layer& layer : m_Layers)
		{
			bool handled = layer.OnEvent(event);

			if (handled)
			{
				break;
			}
		}

		Log::Info(event.GetName(), " was not handled.");
	}

	void Application::ResizeWindow(WindowResizeEvent& event)
	{
		Log::Info("Application::ResizeWindow: ", event.Width, ", ", event.Height);
		m_Context.Resize(event.Width, event.Height);
	}
}
