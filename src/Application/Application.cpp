#include "pch.h"
#include "Application.h"

namespace Ash
{
	Application Application::s_Instance;

	static Vulkan::Context& context = Vulkan::Context::Get();

	void Application::Run()
	{
		float lastTime = (float)glfwGetTime();

		while (!glfwWindowShouldClose(context.Window))
		{
			float time = (float)glfwGetTime();
			float deltaTime = time - lastTime;
			lastTime = time;

			Update(deltaTime);
			Draw();

			// ImGui_ImplVulkan_NewFrame();
			// ImGui_ImplGlfw_NewFrame();
			// ImGui::NewFrame();

			// ImGui::Render();

			glfwPollEvents();
		}
	}

	void Application::DispatchEvent(Event& event)
	{
		Get().OnEvent(event);
	}

	void Application::AddLayer(std::unique_ptr<Layer> layer)
	{
		m_Layers.push_back(std::move(layer));
	}

	void Application::RemoveLayer(const Layer& layer)
	{
		for (auto it = m_Layers.begin(); it != m_Layers.end(); it++)
		{
			if (layer == *(*it).get())
			{
				m_Layers.erase(it);
				break;
			}
		}
	}
	
	void Application::Update(float deltaTime)
	{
		for (std::unique_ptr<Layer>& layer : m_Layers)
		{
			layer->Update(deltaTime);
		}
	}

	void Application::Draw()
	{
		for (std::unique_ptr<Layer>& layer : m_Layers)
		{
			layer->Draw();
		}
	}
	
	void Application::OnEvent(Event& event)
	{
		if (event.HasType(EventType::WindowResize))
		{
			ResizeWindow(event.Cast<WindowResizeEvent>());
		}

		for (std::unique_ptr<Layer>& layer : m_Layers)
		{
			bool handled = layer->OnEvent(event);

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
		context.Resize(event.Width, event.Height);
	}
}
