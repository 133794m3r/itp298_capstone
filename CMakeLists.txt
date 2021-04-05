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
		includes.hxx
		classes/fighters/actor.hxx
		classes/fighters/player.hxx
		classes/fighters/mob.hxx
		tests/actor_test.cpp
		)

add_executable(test_battle
		includes.hxx
		classes/battle/loottable.hxx
		classes/battle/battle_system.hxx
		menus/battle.hxx
		tests/battle_test.cpp
		)

add_executable(map_test
		includes.hxx
		classes/maps/room.hxx
		classes/maps/room.cpp
		classes/maps/map.hxx
		classes/maps/map.cpp
		tests/map_test.cpp
		)

add_executable(test_items
		includes.hxx
		classes/items/itembase.hxx
		classes/items/weapon.cpp
		classes/items/weapon.hxx
		classes/items/armor.cpp
		classes/items/armor.hxx
		tests/item_test.cpp
		)

add_executable(itp298_capstone
		includes.hxx
		classes/fighters/actor.hxx
		classes/fighters/player.hxx
		classes/battle/loottable.hxx
		classes/fighters/mob.hxx
		classes/items/itembase.cpp
		classes/items/itembase.hxx
		classes/items/weapon.cpp
		classes/items/weapon.hxx
		classes/items/armor.cpp
		classes/items/armor.hxx
		classes/shopkeeper.hxx
		menus/battle.hxx
		menus/map_movement.hxx
		menus/shop.hxx
		main.cpp
		menus/inputs.hxx)