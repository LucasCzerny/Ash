add_library("GLFW" STATIC
  "vendor/glfw/glfw/src/context.c"
  "vendor/glfw/glfw/src/egl_context.c"
  "vendor/glfw/glfw/src/glx_context.c"
  "vendor/glfw/glfw/src/init.c"
  "vendor/glfw/glfw/src/input.c"
  "vendor/glfw/glfw/src/linux_joystick.c"
  "vendor/glfw/glfw/src/monitor.c"
  "vendor/glfw/glfw/src/null_init.c"
  "vendor/glfw/glfw/src/null_joystick.c"
  "vendor/glfw/glfw/src/null_monitor.c"
  "vendor/glfw/glfw/src/null_window.c"
  "vendor/glfw/glfw/src/osmesa_context.c"
  "vendor/glfw/glfw/src/platform.c"
  "vendor/glfw/glfw/src/posix_module.c"
  "vendor/glfw/glfw/src/posix_poll.c"
  "vendor/glfw/glfw/src/posix_thread.c"
  "vendor/glfw/glfw/src/posix_time.c"
  "vendor/glfw/glfw/src/vulkan.c"
  "vendor/glfw/glfw/src/window.c"
  "vendor/glfw/glfw/src/x11_init.c"
  "vendor/glfw/glfw/src/x11_monitor.c"
  "vendor/glfw/glfw/src/x11_window.c"
  "vendor/glfw/glfw/src/xkb_unicode.c"
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set_target_properties("GLFW" PROPERTIES
    OUTPUT_NAME "GLFW"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Debug-linux-x86_64/GLFW"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Debug-linux-x86_64/GLFW"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Debug-linux-x86_64/GLFW"
  )
endif()
target_include_directories("GLFW" PRIVATE
)
target_compile_definitions("GLFW" PRIVATE
  $<$<CONFIG:Debug>:_GLFW_X11>
)
target_link_directories("GLFW" PRIVATE
)
target_link_libraries("GLFW"
)
target_compile_options("GLFW" PRIVATE
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-fPIC>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:C>>:-g>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-fPIC>
  $<$<AND:$<CONFIG:Debug>,$<COMPILE_LANGUAGE:CXX>>:-g>
)
if(CMAKE_BUILD_TYPE STREQUAL Release)
  set_target_properties("GLFW" PROPERTIES
    OUTPUT_NAME "GLFW"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Release-linux-x86_64/GLFW"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Release-linux-x86_64/GLFW"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Release-linux-x86_64/GLFW"
  )
endif()
target_include_directories("GLFW" PRIVATE
)
target_compile_definitions("GLFW" PRIVATE
  $<$<CONFIG:Release>:_GLFW_X11>
)
target_link_directories("GLFW" PRIVATE
)
target_link_libraries("GLFW"
)
target_compile_options("GLFW" PRIVATE
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:C>>:-fPIC>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Release>,$<COMPILE_LANGUAGE:CXX>>:-fPIC>
)
if(CMAKE_BUILD_TYPE STREQUAL Dist)
  set_target_properties("GLFW" PROPERTIES
    OUTPUT_NAME "GLFW"
    ARCHIVE_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Dist-linux-x86_64/GLFW"
    LIBRARY_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Dist-linux-x86_64/GLFW"
    RUNTIME_OUTPUT_DIRECTORY "/home/lucas/Documents/Code/Ash/vendor/glfw/bin/Dist-linux-x86_64/GLFW"
  )
endif()
target_include_directories("GLFW" PRIVATE
)
target_compile_definitions("GLFW" PRIVATE
  $<$<CONFIG:Dist>:_GLFW_X11>
)
target_link_directories("GLFW" PRIVATE
)
target_link_libraries("GLFW"
)
target_compile_options("GLFW" PRIVATE
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-O2>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:C>>:-fPIC>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-m64>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-O2>
  $<$<AND:$<CONFIG:Dist>,$<COMPILE_LANGUAGE:CXX>>:-fPIC>
)