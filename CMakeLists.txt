cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 20)
set(OpenGL_GL_PREFERENCE LEGACY)

project(willful_arcane)

find_package(OpenGL REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio network system REQUIRED)

set(SOURCES
    Application/alert_wks_state.cpp
    Application/alert_wks_state.hpp
    Application/animated_sprite.cpp
    Application/animated_sprite.hpp
    Application/animation.cpp
    Application/animation.hpp
    Application/application.cpp
    Application/application.hpp
    Application/bools.cpp
    Application/bools.hpp
    Application/button.cpp
    Application/button.hpp
    Application/category.hpp
    Application/color_identify.cpp
    Application/color_identify.hpp
    Application/command.cpp
    Application/command.hpp
    Application/command_queue.cpp
    Application/command_queue.hpp
    Application/component.cpp
    Application/component.hpp
    Application/container.cpp
    Application/container.hpp
    Application/controls_state.cpp
    Application/controls_state.hpp
    Application/credits_state.cpp
    Application/credits_state.hpp
    Application/data_storage.cpp
    Application/data_storage.hpp
    Application/dialogue_button.cpp
    Application/dialogue_button.hpp
    Application/dialogue.cpp
    Application/dialogue.hpp
    Application/dialogue_state.cpp
    Application/dialogue_state.hpp
    Application/enemy.cpp
    Application/enemy.hpp
    Application/entity.cpp
    Application/entity.hpp
    Application/final_state.cpp
    Application/final_state.hpp
    Application/forest.cpp
    Application/forest.hpp
    Application/forest_state.cpp
    Application/forest_state.hpp
    Application/hero.cpp
    Application/hero.hpp
    Application/image_state.cpp
    Application/image_state.hpp
    Application/key_bindings_state.cpp
    Application/key_bindings_state.hpp
    Application/label.cpp
    Application/label.hpp
    Application/long_button.cpp
    Application/long_button.hpp
    Application/mainMenu_state.cpp
    Application/mainMenu_state.hpp
    Application/npc.cpp
    Application/npc.hpp
    Application/pauseMenu_state.cpp
    Application/pauseMenu_state.hpp
    Application/placeholder.txt
    Application/player.cpp
    Application/player.hpp
    Application/quote_identify.hpp
    Application/quotes_identidy.cpp
    Application/quotes_storage.cpp
    Application/quotes_storage.hpp
    Application/resource_holder.hpp
    Application/resource_holder.inl
    Application/resource_identify.hpp
    Application/scene_node.cpp
    Application/scene_node.hpp
    Application/settings_state.cpp
    Application/settings_state.hpp
    Application/short_button.cpp
    Application/short_button.hpp
    Application/sprite_node.cpp
    Application/sprite_node.hpp
    Application/state.cpp
    Application/state.hpp
    Application/state_identify.hpp
    Application/state_stack.cpp
    Application/state_stack.hpp
    Application/text_node.cpp
    Application/text_node.hpp
    Application/title_state.cpp
    Application/title_state.hpp
    Application/tutorial_state.cpp
    Application/tutorial_state.hpp
    Application/UTF8_label.cpp
    Application/UTF8_label.hpp
    Application/utilities.cpp
    Application/utilities.hpp
    Application/warning_etd_state.cpp
    Application/warning_etd_state.hpp
    Application/weapon.cpp
    Application/weapon.hpp
    Application/white_state.cpp
    Application/white_state.hpp
    Application/world.cpp
    Application/world.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-network sfml-system)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})

