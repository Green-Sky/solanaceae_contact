#pragma once

#include "./fwd.hpp"

#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>

namespace ContactStore::Events {

	struct Contact4Construct {
		const ContactHandle4 e;
	};
	struct Contact4Update {
		const ContactHandle4 e;
	};
	struct Contact4Destory {
		const ContactHandle4 e;
	};

} // ContactStore::Events

