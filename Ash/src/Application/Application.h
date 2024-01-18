#pragma once

#include "Layer.h"

#include "Config/Config.h"

#include "Events/Event.h"
#include "Events/WindowEvents.h"

#include "Vulkan/Context/Context.h"

namespace Ash
{
	class Application
	{
	public:
		Application(const Config& config);

		void Run();

		static void DispatchEvent(Event& event);

		void SetActive();
		static Application& GetActive() { return *s_ActiveApplication; }

		Config& GetConfig() { return m_Config; }
		Vulkan::Context& GetContext() { return m_Context; }

	protected:
		void AddLayer(const Layer& layer);
		void RemoveLayer(const Layer& layer);

		virtual void Update(float deltaTime) {}
		virtual void Draw() {}
		virtual void DrawUi() {}

		void OnEvent(Event& event);

	private:
		static Application* s_ActiveApplication;

		Config m_Config;
		Vulkan::Context m_Context;

		std::vector<Layer> m_Layers;

	private:
		void ResizeWindow(WindowResizeEvent& event);
	};
}