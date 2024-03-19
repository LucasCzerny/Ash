#pragma once

#include "Layer.h"

#include "Config/Config.h"
#include "Scene/Scene.h"

#include "Events/Event.h"
#include "Events/WindowEvents.h"

#include "Vulkan/Context/Context.h"

namespace Ash
{
	class Application
	{
	public:
		void Run();

		static void DispatchEvent(Event& event);

		void AddLayer(std::unique_ptr<Layer> layer);
		void RemoveLayer(const Layer& layer);

		static Application& Get() { return s_Instance; }

	private:
		std::vector<std::unique_ptr<Layer>> m_Layers;

		static Application s_Instance;

	private:
		void Update(float deltaTime);
		void Draw();

		void OnEvent(Event& event);

		void ResizeWindow(WindowResizeEvent& event);
	};
}