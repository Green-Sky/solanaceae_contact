#pragma once

#include "./components.hpp"

#include <entt/core/type_info.hpp>

// TODO: move more central
#define DEFINE_COMP_ID(x) \
template<> \
constexpr entt::id_type entt::type_hash<x>::value() noexcept { \
	using namespace entt::literals; \
	return #x##_hs; \
} \
template<> \
constexpr std::string_view entt::type_name<x>::value() noexcept { \
	return #x; \
}

// cross compiler stable ids

DEFINE_COMP_ID(Contact::Components::TagSelfWeak)
DEFINE_COMP_ID(Contact::Components::TagSelfStrong)
DEFINE_COMP_ID(Contact::Components::TagRoot)
DEFINE_COMP_ID(Contact::Components::TagBig)
DEFINE_COMP_ID(Contact::Components::TagPrivate)
DEFINE_COMP_ID(Contact::Components::TagGroup)
DEFINE_COMP_ID(Contact::Components::RequestIncoming)
DEFINE_COMP_ID(Contact::Components::TagRequestOutgoing)
DEFINE_COMP_ID(Contact::Components::Self)
DEFINE_COMP_ID(Contact::Components::Parent)
DEFINE_COMP_ID(Contact::Components::ParentOf)
DEFINE_COMP_ID(Contact::Components::ContactModel)
DEFINE_COMP_ID(Contact::Components::Name)
DEFINE_COMP_ID(Contact::Components::ID)
DEFINE_COMP_ID(Contact::Components::TagAvatarInvalidate)
DEFINE_COMP_ID(Contact::Components::AvatarMemory)
DEFINE_COMP_ID(Contact::Components::AvatarFile)
DEFINE_COMP_ID(Contact::Components::ConnectionState)
DEFINE_COMP_ID(Contact::Components::StatusText)
DEFINE_COMP_ID(Contact::Components::FirstSeen)
DEFINE_COMP_ID(Contact::Components::LastSeen)
DEFINE_COMP_ID(Contact::Components::LastActivity)

#undef DEFINE_COMP_ID

