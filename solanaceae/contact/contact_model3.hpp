#pragma once

#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>

// strong typing for contacts
enum class Contact3 : uint32_t {};

using Contact3Registry = entt::basic_registry<Contact3>;
using Contact3Handle = entt::basic_handle<Contact3Registry>;

struct ContactModel3I {
	virtual ~ContactModel3I(void) {}

	// eg friends, confs, groups
	//virtual std::vector<Contact3> getBigContacts(void) = 0;
	// eg, all clients in a group
	//virtual std::vector<Contact3> getSubContacts(const Contact3& c) = 0;

	//virtual Contact3Handle toSelfStrong(void) = 0;

	//virtual Contact3Handle toBig(void) = 0;

	//virtual Contact3Handle toPersistent(void) = 0;
	//virtual Contact3Handle toEphemeral(void) = 0;
};

