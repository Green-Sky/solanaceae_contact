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
DEFINE_COMP_ID(Contact::Components::AvatarObj)
DEFINE_COMP_ID(Contact::Components::AvatarMemory)
DEFINE_COMP_ID(Contact::Components::AvatarFile)
DEFINE_COMP_ID(Contact::Components::ConnectionState)
DEFINE_COMP_ID(Contact::Components::StatusText)
DEFINE_COMP_ID(Contact::Components::FirstSeen)
DEFINE_COMP_ID(Contact::Components::LastSeen)
DEFINE_COMP_ID(Contact::Components::LastActivity)

DEFINE_COMP_ID(Contact::Components::Caps::TagDeletable)
DEFINE_COMP_ID(Contact::Components::Caps::TagConnectable)
DEFINE_COMP_ID(Contact::Components::Caps::TagSendMessage)
DEFINE_COMP_ID(Contact::Components::Caps::SendMessageSize)
DEFINE_COMP_ID(Contact::Components::Caps::TagSetName)
DEFINE_COMP_ID(Contact::Components::Caps::TagSetStatus)
DEFINE_COMP_ID(Contact::Components::Caps::TagSetStatusText)
DEFINE_COMP_ID(Contact::Components::Caps::StatusTextSize)
DEFINE_COMP_ID(Contact::Components::Caps::TagSetStatusRich)

#undef DEFINE_COMP_ID

