#include "./components.hpp"

#include <entt/core/type_info.hpp>

// TODO: move more central
#define DEFINE_COMP_ID(x) \
template<> \
constexpr entt::id_type entt::type_hash<x>::value() noexcept { \
    using namespace entt::literals; \
    return #x##_hs; \
}

// cross compiler stable ids

DEFINE_COMP_ID(Contact::Components::TagSelfWeak)
DEFINE_COMP_ID(Contact::Components::TagSelfStrong)
DEFINE_COMP_ID(Contact::Components::TagBig)
DEFINE_COMP_ID(Contact::Components::Self)
DEFINE_COMP_ID(Contact::Components::BigParent)
DEFINE_COMP_ID(Contact::Components::ParentOf)
DEFINE_COMP_ID(Contact::Components::ContactModel)
DEFINE_COMP_ID(Contact::Components::Name)
DEFINE_COMP_ID(Contact::Components::ConnectionState)
DEFINE_COMP_ID(Contact::Components::StatusMessage)

#undef DEFINE_COMP_ID
