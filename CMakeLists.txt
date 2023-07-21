cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(solanaceae)

add_library(solanaceae_contact INTERFACE
	#./solanaceae/contact/components.hpp
	#./solanaceae/contact/components_id.inl
	#./solanaceae/contact/contact_model3.hpp
)

target_include_directories(solanaceae_contact INTERFACE .)
target_compile_features(solanaceae_contact INTERFACE cxx_std_17)
target_link_libraries(solanaceae_contact INTERFACE
	EnTT::EnTT
)

