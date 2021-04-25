cmake_minimum_required(VERSION 3.17)
project(itp298_capstone)
enable_testing()
set(CMAKE_CXX_STANDARD 14)
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

add_library(includes_lib OBJECT
		includes.hxx)

add_library(items_lib OBJECT
		classes/items/itembase.hxx
		classes/items/itembase.cpp
		classes/items/weapon.hxx
		classes/items/weapon.cpp
		classes/items/armor.hxx
		classes/items/armor.cpp)

add_library(inventory_lib OBJECT
		classes/containers/inventory.hxx
		classes/containers/loot_table.hxx)

add_library(actors_lib OBJECT
		classes/fighters/actor.hxx
		classes/fighters/mob.hxx
		classes/fighters/player.hxx
		)

#find_package(Threads REQUIRED)
add_executable(test_fighters
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		tests/actor_test.cpp
		)
##target_link_libraries( test_fighters Threads::Threads)

add_executable(battle_demo
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/battle/battle_system.hxx
		menus/battle.hxx
		tests/battle_demo.cpp)

#target_link_libraries( battle_demo Threads::Threads)
add_executable(test_battle
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/battle/battle_system.hxx
		menus/battle.hxx
		tests/battle_test.cpp)

#target_link_libraries( test_battle Threads::Threads)
add_executable(map_test
		includes.hxx
		classes/maps/room.hxx
		classes/maps/room.cpp
		classes/maps/map.hxx
		classes/maps/map.cpp
		tests/map_test.cpp
		)

#target_link_libraries( map_test Threads::Threads)
add_executable(test_items
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		tests/item_test.cpp
		)

add_executable(test_inventory
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		classes/containers/shop_inventory.hxx
		tests/inventory_test.cpp
		)

add_executable(test_shop
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/containers/shop_inventory.hxx
		classes/shopkeeper.hxx
		tests/shop_test.cpp
		)

add_executable(shop_demo
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/containers/shop_inventory.hxx
		classes/shopkeeper.hxx
		menus/shop.hxx
		tests/shop_demo.cpp
		tests/shop_demo.cpp)
#target_link_libraries( test_items Threads::Threads)
add_executable(itp298_capstone
		$<TARGET_OBJECTS:includes_lib>
		$<TARGET_OBJECTS:items_lib>
		$<TARGET_OBJECTS:inventory_lib>
		$<TARGET_OBJECTS:actors_lib>
		classes/shopkeeper.hxx
		menus/battle.hxx
		menus/map_movement.hxx
		menus/shop.hxx
		main.cpp
		menus/inputs.hxx)

#target_link_libraries(itp298_capstone Threads::Threads)
#have to make sure this works on windows first.
#if(MSVC)
#	#may not actually work but who knows.
#	add_test( NAME "Battle Test"
#			COMMAND test_battle.exe)
#else()
	#Test the battle system
	add_test(NAME "Battle_Module"
			COMMAND ./test_battle)
	#Test the Actor class and children classes.
	add_test(NAME "Actor_Module"
			COMMAND ./test_fighters)
	add_test(NAME "Inventory_Module"
			COMMAND ./test_inventory)
#endif()