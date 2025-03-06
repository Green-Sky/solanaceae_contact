#pragma once

#include "./contact_store_i.hpp"
#include "solanaceae/contact/fwd.hpp"

#include <entt/entity/registry.hpp>

// default implementation
struct ContactStore4Impl : public ContactStore4I {
	ContactRegistry4& registry(void) override;
	ContactHandle4 contactHandle(const Contact4 c) override;

	ContactHandle4 getOneContactByID(const ByteSpan id) override;
	ContactHandle4 getOneContactByID(const Contact4 hint, const ByteSpan id) override;

	void throwEventConstruct(const Contact4 c) override;
	void throwEventUpdate(const Contact4 c) override;
	void throwEventDestroy(const Contact4 c) override;

	private:
		entt::basic_registry<Contact4> _reg;
};

