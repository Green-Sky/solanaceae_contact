project(solanaceae_contact C CXX)

add_library(solanaceae_contact INTERFACE
	./solanaceae/contact/fwd.hpp

	./solanaceae/contact/components.hpp
	./solanaceae/contact/components_id.inl
	./solanaceae/contact/contact_model4.hpp

	./solanaceae/contact/contact_store_events.hpp
	./solanaceae/contact/contact_store_i.hpp
)

target_include_directories(solanaceae_contact INTERFACE .)
target_compile_features(solanaceae_contact INTERFACE cxx_std_17)
target_link_libraries(solanaceae_contact INTERFACE
	EnTT::EnTT
	solanaceae_util
)

########################################

add_library(solanaceae_contact_impl
	./solanaceae/contact/contact_store_impl.hpp
	./solanaceae/contact/contact_store_impl.cpp
)

target_include_directories(solanaceae_contact_impl PUBLIC .)
target_compile_features(solanaceae_contact_impl PUBLIC cxx_std_17)
target_link_libraries(solanaceae_contact_impl PUBLIC
	solanaceae_contact
)

