set(generic_src
	generic/message_buffer.cpp
	generic/pipe.cpp
	generic/savefile.cpp
	generic/utils/ayelog.cpp
	generic/utils/ayestring.cpp
	generic/utils/exception.cpp)

set(client_src
	${generic_src}
	client/data.cpp
	client/main.cpp
	client/network.cpp
	client/gui/button.cpp
	client/gui/gui_component.cpp
	client/gui/gui.cpp
	client/gui/gui_utils.cpp
	client/gui/login.cpp
	client/gui/textbox_character.cpp
	client/gui/textbox.cpp
	client/gui/textlabel.cpp)

set(server_src
	${generic_src}
	server/game.cpp
	server/main.cpp
	server/network.cpp
	server/session.cpp
	server/user.cpp)
	
# Alternative with wildcards (not recommended)
# generic
#AUX_SOURCE_DIRECTORY(generic generic_base_src)
#AUX_SOURCE_DIRECTORY(generic/utils generic_utils_src)
#set(generic_src ${generic_base_src} ${generic_utils_src})
# client
#AUX_SOURCE_DIRECTORY(client client_base_src)
#AUX_SOURCE_DIRECTORY(client/gui client_gui_src)
#set(client_src ${client_base_src} ${client_gui_src} ${generic_src})
# server
#AUX_SOURCE_DIRECTORY(server server_base_src)
#set(server_src ${server_base_src} ${generic_src})

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(eclient ${client_src})
target_link_libraries(eclient SDL SDL_ttf)

add_executable(eserver ${server_src})
