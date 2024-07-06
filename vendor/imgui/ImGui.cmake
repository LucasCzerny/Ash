add_library("ImGui" STATIC
    "vendor/Ash/Ash/vendor/imgui/imgui/backends/imgui_impl_glfw.cpp"
    "vendor/Ash/Ash/vendor/imgui/imgui/backends/imgui_impl_vulkan.cpp"
  "vendor/Ash/Ash/vendor/imgui/imgui/imgui.cpp"
  "vendor/Ash/Ash/vendor/imgui/imgui/imgui_demo.cpp"
  "vendor/Ash/Ash/vendor/imgui/imgui/imgui_draw.cpp"
  "vendor/Ash/Ash/vendor/imgui/imgui/imgui_tables.cpp"
  "vendor/Ash/Ash/vendor/imgui/imgui/imgui_widgets.cpp"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  add_dependencies("ImGui"
    "GLFW"
  )
  set_target_properties("ImGui" PROPERTIES
    OUTPUT_NAME "ImGui"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Debug-linux-x86_64/ImGui"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Debug-linux-x86_64/ImGui"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Debug-linux-x86_64/ImGui"
  )
endif()
target_include_directories("ImGui" PRIVATE
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui//Include>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/imgui>
  $<$<CONFIG:Debug>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/glfw/glfw/include>
)
target_compile_definitions("ImGui" PRIVATE
  $<$<CONFIG:Debug>:IMGUI_USE_WCHAR32>
)
target_link_directories("ImGui" PRIVATE
)
target_link_libraries("ImGui"
  $<$<CONFIG:Debug>:GLFW>
)
target_compile_options("ImGui" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-fPIC>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-fPIC>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("ImGui" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE True
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Release)
  add_dependencies("ImGui"
    "GLFW"
  )
  set_target_properties("ImGui" PROPERTIES
    OUTPUT_NAME "ImGui"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Release-linux-x86_64/ImGui"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Release-linux-x86_64/ImGui"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Release-linux-x86_64/ImGui"
  )
endif()
target_include_directories("ImGui" PRIVATE
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui//Include>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/imgui>
  $<$<CONFIG:Release>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/glfw/glfw/include>
)
target_compile_definitions("ImGui" PRIVATE
  $<$<CONFIG:Release>:IMGUI_USE_WCHAR32>
)
target_link_directories("ImGui" PRIVATE
)
target_link_libraries("ImGui"
  $<$<CONFIG:Release>:GLFW>
)
target_compile_options("ImGui" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-fPIC>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-fPIC>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("ImGui" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE True
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  add_dependencies("ImGui"
    "GLFW"
  )
  set_target_properties("ImGui" PROPERTIES
    OUTPUT_NAME "ImGui"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Dist-linux-x86_64/ImGui"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Dist-linux-x86_64/ImGui"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/bin/Dist-linux-x86_64/ImGui"
  )
endif()
target_include_directories("ImGui" PRIVATE
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui//Include>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/imgui/imgui>
  $<$<CONFIG:Dist>:/home/lucas/Documents/Code/Lava/vendor/Ash/Ash/vendor/glfw/glfw/include>
)
target_compile_definitions("ImGui" PRIVATE
  $<$<CONFIG:Dist>:IMGUI_USE_WCHAR32>
)
target_link_directories("ImGui" PRIVATE
)
target_link_libraries("ImGui"
  $<$<CONFIG:Dist>:GLFW>
)
target_compile_options("ImGui" PRIVATE
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-fPIC>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-fPIC>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-std=c++17>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("ImGui" PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE True
    INTERPROCEDURAL_OPTIMIZATION False
  )
endif()