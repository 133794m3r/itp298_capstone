cmake_minimum_required(VERSION 3.18)
project(itp298_capstone)

set(CMAKE_CXX_STANDARD 17)

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