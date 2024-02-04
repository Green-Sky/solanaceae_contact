cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

include(FetchContent)

if (NOT TARGET EnTT::EnTT)
	FetchContent_Declare(EnTT
		GIT_REPOSITORY https://github.com/skypjack/entt.git
		GIT_TAG v3.12.2
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(EnTT)
endif()

