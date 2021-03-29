cmake_minimum_required(VERSION 3.18)
project(itp298_capstone)

set(CMAKE_CXX_STANDARD 17)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14 /W4")
	set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g3 ")
	#since CLion decides that you debug from the damn release buildl always instead of from debug and won't let you change that.
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O1")

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()
endif()
add_executable(test_fighters
		main.cpp
		classes/fighters/actor.hxx
		classes/fighters/player.hxx
		classes/fighters/mob.hxx
		)

add_executable(test_battle
		main.cpp
		classes/battle/loottable.hxx
		)

add_executable(test_items
		main.cpp
		classes/items/itembase.hxx
		classes/items/weapon.cpp classes/items/weapon.hxx classes/items/armor.cpp classes/items/armor.hxx)

add_executable(itp298_capstone main.cpp
		classes/fighters/actor.cpp classes/fighters/actor.hxx
		classes/fighters/player.cpp classes/fighters/player.hxx
		classes/battle/loottable.cpp classes/battle/loottable.hxx
		classes/fighters/mob.cpp classes/fighters/mob.hxx
		classes/items/itembase.cpp classes/items/itembase.hxx classes/items/weapon.cpp classes/items/weapon.hxx classes/items/armor.cpp classes/items/armor.hxx)