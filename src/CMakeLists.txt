add_subdirectory(common)
add_subdirectory(event)
add_subdirectory(resources)
add_subdirectory(scene)
add_subdirectory(render)
add_subdirectory(renderer)
add_subdirectory(tests)

include_directories(
${CMAKE_SOURCE_DIR}/include/renderer
${CMAKE_SOURCE_DIR}/include/event
${CMAKE_SOURCE_DIR}/include/resources
${CMAKE_SOURCE_DIR}/include/scene
${CMAKE_SOURCE_DIR}/include/common
${CMAKE_SOURCE_DIR}/include/render
${CMAKE_SOURCE_DIR}/include/terrain
${CMAKE_SOURCE_DIR}/include/gui
${OCEANSURFACE_INCLUDE}
${MESHLIB_INCLUDE_DIR}
${GLM_INCLUDE_DIRS}
${IMGUI_INCLUDE_DIR})


add_executable(main
  ${CMAKE_SOURCE_DIR}/src/main.cxx)
target_link_libraries(main
${GLFW_LIBRARY}
${Glad_LIBRARIES}
${CMAKE_DL_LIBS}
${MESHLIB_LIBRARY}
${CImg_LIBRARIES}
Common
Resource
Scene
Event
Render
Renderer)
