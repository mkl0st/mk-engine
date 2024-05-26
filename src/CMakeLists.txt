# Library
add_library(
  MK
  SHARED
  Core.cpp
  Graphics.cpp
)

# Linking Dependencies
target_link_libraries(MK PUBLIC ${GLEW_LIB} ${GLFW_LIB} ${PNG_LIB})
if(BUILD_FOR_WINDOWS)
  target_link_libraries(MK PUBLIC gdi32 user32 kernel32 opengl32)
  target_link_options(MK -static -static-libgcc -static-libstdc++ -mwindows)
else()
  target_link_libraries(MK PUBLIC GL)
endif()
