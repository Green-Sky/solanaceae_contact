#pragma once

#include <entt/entity/fwd.hpp>

// strong typing for contacts
enum class Contact4 : uint32_t {};
using ContactRegistry4 = entt::basic_registry<Contact4>;
using ContactHandle4 = entt::basic_handle<ContactRegistry4>;

struct ContactStore4I;
struct ContactModel4I;
namespace ContactStore::Events {
	struct Contact4Construct;
	struct Contact4Update;
	struct Contact4Destory;
} // ContactStore::Events

