add_library("Ash" STATIC
  "src/Ash.h"
    "src/Components/BasicMovementComponent.cpp"
    "src/Components/BasicMovementComponent.h"
    "src/Components/CameraComponent.cpp"
    "src/Components/CameraComponent.h"
    "src/Components/Component.cpp"
    "src/Components/Component.h"
    "src/Components/ComponentInterface.h"
    "src/Components/LightComponent.cpp"
    "src/Components/LightComponent.h"
    "src/Components/ModelComponent.cpp"
    "src/Components/ModelComponent.h"
    "src/Components/TagComponent.cpp"
    "src/Components/TagComponent.h"
    "src/Components/TransformComponent.cpp"
    "src/Components/TransformComponent.h"
    "src/Config/Config.cpp"
    "src/Config/Config.h"
    "src/Core/Assert.h"
    "src/Core/ErrorCallbacks.cpp"
    "src/Core/ErrorCallbacks.h"
    "src/Core/Log.cpp"
    "src/Core/Log.h"
    "src/Core/Log.inl"
    "src/Entity/Entity.cpp"
    "src/Entity/Entity.h"
    "src/Entity/Entity.inl"
    "src/Events/Event.cpp"
    "src/Events/Event.h"
    "src/Events/Event.inl"
    "src/Events/EventDispatcher.cpp"
    "src/Events/EventDispatcher.h"
    "src/Events/EventType.h"
    "src/Events/KeyEvents.h"
    "src/Events/WindowEvents.h"
    "src/Input/Input.cpp"
    "src/Input/Input.h"
    "src/Input/Keys.h"
    "src/Model/Model.cpp"
    "src/Model/Model.h"
    "src/Model/Model.inl"
    "src/Scene/Scene.cpp"
    "src/Scene/Scene.h"
    "src/Scene/Scene.inl"
    "src/Utility/File.cpp"
    "src/Utility/File.h"
      "src/Vulkan/Buffer/Buffer.cpp"
      "src/Vulkan/Buffer/Buffer.h"
      "src/Vulkan/Context/Context.cpp"
      "src/Vulkan/Context/Context.h"
      "src/Vulkan/Context/Context.inl"
      "src/Vulkan/Defaults/Defaults.cpp"
      "src/Vulkan/Defaults/Defaults.h"
      "src/Vulkan/Descriptor/Descriptor.cpp"
      "src/Vulkan/Descriptor/Descriptor.h"
      "src/Vulkan/Device/Device.cpp"
      "src/Vulkan/Device/Device.h"
      "src/Vulkan/Device/Queue.h"
      "src/Vulkan/Device/SwapChainSupportDetails.h"
      "src/Vulkan/Instance/Instance.cpp"
      "src/Vulkan/Instance/Instance.h"
      "src/Vulkan/RenderSystem/Pipeline.cpp"
      "src/Vulkan/RenderSystem/Pipeline.h"
      "src/Vulkan/RenderSystem/PipelineConfig.cpp"
      "src/Vulkan/RenderSystem/PipelineConfig.h"
      "src/Vulkan/RenderSystem/RenderSystem.cpp"
      "src/Vulkan/RenderSystem/RenderSystem.h"
      "src/Vulkan/SwapChain/SwapChain.cpp"
      "src/Vulkan/SwapChain/SwapChain.h"
      "src/Vulkan/SwapChain/SwapChainSpecification.h"
      "src/Vulkan/Texture/SwapChainTextures.cpp"
      "src/Vulkan/Texture/SwapChainTextures.h"
      "src/Vulkan/Texture/Texture.cpp"
      "src/Vulkan/Texture/Texture.h"
        "src/Vulkan/Utility/Commands/SingleTimeCommands.cpp"
        "src/Vulkan/Utility/Commands/SingleTimeCommands.h"
        "src/Vulkan/Utility/Shapes/Cube.cpp"
        "src/Vulkan/Utility/Shapes/Cube.h"
        "src/Vulkan/Utility/Shapes/Quad.cpp"
        "src/Vulkan/Utility/Shapes/Quad.h"
      "src/Vulkan/Window/Window.cpp"
      "src/Vulkan/Window/Window.h"
  "src/pch.cpp"
  "src/pch.h"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_dependencies("Ash"
    "GLFW"
    "ImGui"
  )
  set_target_properties("Ash" PROPERTIES
    OUTPUT_NAME "Ash"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Debug-linux-x86_64/Ash"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Debug-linux-x86_64/Ash"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Debug-linux-x86_64/Ash"
  )
endif()
target_include_directories("Ash" PRIVATE
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash/src>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash//Include>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash/vendor/entt/entt/src/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash/vendor/glfw/glfw/include/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash/vendor/glm/glm/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash/vendor/imgui/imgui/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash/vendor/stb/stb/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash/vendor/tinygltf/tinygltf>
)
target_compile_definitions("Ash" PRIVATE
  $<$<CONFIG:Debug>:ASH_PLATFORM_LINUX>
  $<$<CONFIG:Debug>:ASH_DEBUG>
)
target_link_directories("Ash" PRIVATE
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Ash//Lib>
)
target_link_libraries("Ash"
  $<$<CONFIG:Debug>:GLFW>
  $<$<CONFIG:Debug>:ImGui>
  $<$<CONFIG:Debug>:vulkan-1>
)
target_compile_options("Ash" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("Ash" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Debug)
target_precompile_headers("Ash" PUBLIC src/pch.h)
endif()
if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_dependencies("Ash"
    "GLFW"
    "ImGui"
  )
  set_target_properties("Ash" PROPERTIES
    OUTPUT_NAME "Ash"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Release-linux-x86_64/Ash"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Release-linux-x86_64/Ash"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Release-linux-x86_64/Ash"
  )
endif()
target_include_directories("Ash" PRIVATE
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash/src>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash//Include>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash/vendor/entt/entt/src/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash/vendor/glfw/glfw/include/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash/vendor/glm/glm/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash/vendor/imgui/imgui/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash/vendor/stb/stb/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash/vendor/tinygltf/tinygltf>
)
target_compile_definitions("Ash" PRIVATE
  $<$<CONFIG:Release>:ASH_PLATFORM_LINUX>
  $<$<CONFIG:Release>:ASH_RELEASE>
)
target_link_directories("Ash" PRIVATE
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Ash//Lib>
)
target_link_libraries("Ash"
  $<$<CONFIG:Release>:GLFW>
  $<$<CONFIG:Release>:ImGui>
  $<$<CONFIG:Release>:vulkan-1>
)
target_compile_options("Ash" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("Ash" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Release)
target_precompile_headers("Ash" PUBLIC src/pch.h)
endif()
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  add_dependencies("Ash"
    "GLFW"
    "ImGui"
  )
  set_target_properties("Ash" PROPERTIES
    OUTPUT_NAME "Ash"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Dist-linux-x86_64/Ash"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Dist-linux-x86_64/Ash"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/bin/Dist-linux-x86_64/Ash"
  )
endif()
target_include_directories("Ash" PRIVATE
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash/src>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash//Include>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash/vendor/entt/entt/src/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash/vendor/glfw/glfw/include/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash/vendor/glm/glm/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash/vendor/imgui/imgui/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash/vendor/stb/stb/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash/vendor/tinygltf/tinygltf>
)
target_compile_definitions("Ash" PRIVATE
  $<$<CONFIG:Dist>:ASH_PLATFORM_LINUX>
  $<$<CONFIG:Dist>:ASH_DIST>
)
target_link_directories("Ash" PRIVATE
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Ash//Lib>
)
target_link_libraries("Ash"
  $<$<CONFIG:Dist>:GLFW>
  $<$<CONFIG:Dist>:ImGui>
  $<$<CONFIG:Dist>:vulkan-1>
)
target_compile_options("Ash" PRIVATE
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("Ash" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE False
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Dist)
target_precompile_headers("Ash" PUBLIC src/pch.h)
endif()