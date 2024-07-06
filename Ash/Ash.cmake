add_library("Ash" STATIC
  "vendor/Ash/Ash/Ash/src/Ash.h"
    "vendor/Ash/Ash/Ash/src/Components/BasicMovementComponent.cpp"
    "vendor/Ash/Ash/Ash/src/Components/BasicMovementComponent.h"
    "vendor/Ash/Ash/Ash/src/Components/CameraComponent.cpp"
    "vendor/Ash/Ash/Ash/src/Components/CameraComponent.h"
    "vendor/Ash/Ash/Ash/src/Components/Component.cpp"
    "vendor/Ash/Ash/Ash/src/Components/Component.h"
    "vendor/Ash/Ash/Ash/src/Components/ComponentInterface.h"
    "vendor/Ash/Ash/Ash/src/Components/LightComponent.cpp"
    "vendor/Ash/Ash/Ash/src/Components/LightComponent.h"
    "vendor/Ash/Ash/Ash/src/Components/ModelComponent.cpp"
    "vendor/Ash/Ash/Ash/src/Components/ModelComponent.h"
    "vendor/Ash/Ash/Ash/src/Components/TagComponent.cpp"
    "vendor/Ash/Ash/Ash/src/Components/TagComponent.h"
    "vendor/Ash/Ash/Ash/src/Components/TransformComponent.cpp"
    "vendor/Ash/Ash/Ash/src/Components/TransformComponent.h"
    "vendor/Ash/Ash/Ash/src/Config/Config.cpp"
    "vendor/Ash/Ash/Ash/src/Config/Config.h"
    "vendor/Ash/Ash/Ash/src/Core/Assert.h"
    "vendor/Ash/Ash/Ash/src/Core/ErrorCallbacks.cpp"
    "vendor/Ash/Ash/Ash/src/Core/ErrorCallbacks.h"
    "vendor/Ash/Ash/Ash/src/Core/Log.cpp"
    "vendor/Ash/Ash/Ash/src/Core/Log.h"
    "vendor/Ash/Ash/Ash/src/Core/Log.inl"
    "vendor/Ash/Ash/Ash/src/Entity/Entity.cpp"
    "vendor/Ash/Ash/Ash/src/Entity/Entity.h"
    "vendor/Ash/Ash/Ash/src/Entity/Entity.inl"
    "vendor/Ash/Ash/Ash/src/Events/Event.cpp"
    "vendor/Ash/Ash/Ash/src/Events/Event.h"
    "vendor/Ash/Ash/Ash/src/Events/Event.inl"
    "vendor/Ash/Ash/Ash/src/Events/EventDispatcher.cpp"
    "vendor/Ash/Ash/Ash/src/Events/EventDispatcher.h"
    "vendor/Ash/Ash/Ash/src/Events/EventType.h"
    "vendor/Ash/Ash/Ash/src/Events/KeyEvents.h"
    "vendor/Ash/Ash/Ash/src/Events/WindowEvents.h"
    "vendor/Ash/Ash/Ash/src/Input/Input.cpp"
    "vendor/Ash/Ash/Ash/src/Input/Input.h"
    "vendor/Ash/Ash/Ash/src/Input/Keys.h"
    "vendor/Ash/Ash/Ash/src/Model/Model.cpp"
    "vendor/Ash/Ash/Ash/src/Model/Model.h"
    "vendor/Ash/Ash/Ash/src/Model/Model.inl"
    "vendor/Ash/Ash/Ash/src/Scene/Scene.cpp"
    "vendor/Ash/Ash/Ash/src/Scene/Scene.h"
    "vendor/Ash/Ash/Ash/src/Scene/Scene.inl"
    "vendor/Ash/Ash/Ash/src/Utility/File.cpp"
    "vendor/Ash/Ash/Ash/src/Utility/File.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Buffer/Buffer.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Buffer/Buffer.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Context/Context.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Context/Context.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Context/Context.inl"
      "vendor/Ash/Ash/Ash/src/Vulkan/Defaults/Defaults.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Defaults/Defaults.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Descriptor/Descriptor.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Descriptor/Descriptor.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Device/Device.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Device/Device.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Device/Queue.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Device/SwapChainSupportDetails.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Instance/Instance.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Instance/Instance.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/RenderSystem/Pipeline.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/RenderSystem/Pipeline.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/RenderSystem/PipelineConfig.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/RenderSystem/PipelineConfig.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/RenderSystem/RenderSystem.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/RenderSystem/RenderSystem.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/SwapChain/SwapChain.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/SwapChain/SwapChain.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/SwapChain/SwapChainSpecification.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Texture/SwapChainTextures.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Texture/SwapChainTextures.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Texture/Texture.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Texture/Texture.h"
        "vendor/Ash/Ash/Ash/src/Vulkan/Utility/Commands/SingleTimeCommands.cpp"
        "vendor/Ash/Ash/Ash/src/Vulkan/Utility/Commands/SingleTimeCommands.h"
        "vendor/Ash/Ash/Ash/src/Vulkan/Utility/Shapes/Cube.cpp"
        "vendor/Ash/Ash/Ash/src/Vulkan/Utility/Shapes/Cube.h"
        "vendor/Ash/Ash/Ash/src/Vulkan/Utility/Shapes/Quad.cpp"
        "vendor/Ash/Ash/Ash/src/Vulkan/Utility/Shapes/Quad.h"
      "vendor/Ash/Ash/Ash/src/Vulkan/Window/Window.cpp"
      "vendor/Ash/Ash/Ash/src/Vulkan/Window/Window.h"
  "vendor/Ash/Ash/Ash/src/pch.cpp"
  "vendor/Ash/Ash/Ash/src/pch.h"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_dependencies("Ash"
    "GLFW"
    "ImGui"
  )
  set_target_properties("Ash" PROPERTIES
    OUTPUT_NAME "Ash"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Debug-linux-x86_64/Ash"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Debug-linux-x86_64/Ash"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Debug-linux-x86_64/Ash"
  )
endif()
target_include_directories("Ash" PRIVATE
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/src>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash//Include>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/entt/entt/src/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/glfw/glfw/include/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/glm/glm/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/imgui/imgui/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/stb/stb/>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/tinygltf/tinygltf>
)
target_compile_definitions("Ash" PRIVATE
  $<$<CONFIG:Debug>:ASH_PLATFORM_LINUX>
  $<$<CONFIG:Debug>:ASH_DEBUG>
)
target_link_directories("Ash" PRIVATE
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash//Lib>
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
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Release-linux-x86_64/Ash"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Release-linux-x86_64/Ash"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Release-linux-x86_64/Ash"
  )
endif()
target_include_directories("Ash" PRIVATE
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/src>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash//Include>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/entt/entt/src/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/glfw/glfw/include/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/glm/glm/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/imgui/imgui/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/stb/stb/>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/tinygltf/tinygltf>
)
target_compile_definitions("Ash" PRIVATE
  $<$<CONFIG:Release>:ASH_PLATFORM_LINUX>
  $<$<CONFIG:Release>:ASH_RELEASE>
)
target_link_directories("Ash" PRIVATE
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash//Lib>
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
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Dist-linux-x86_64/Ash"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Dist-linux-x86_64/Ash"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/bin/Dist-linux-x86_64/Ash"
  )
endif()
target_include_directories("Ash" PRIVATE
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/src>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash//Include>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/entt/entt/src/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/glfw/glfw/include/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/glm/glm/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/imgui/imgui/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/stb/stb/>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash/../vendor/tinygltf/tinygltf>
)
target_compile_definitions("Ash" PRIVATE
  $<$<CONFIG:Dist>:ASH_PLATFORM_LINUX>
  $<$<CONFIG:Dist>:ASH_DIST>
)
target_link_directories("Ash" PRIVATE
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/Ash//Lib>
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