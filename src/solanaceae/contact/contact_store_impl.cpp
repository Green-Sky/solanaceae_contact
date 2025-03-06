#include "./contact_store_impl.hpp"

#include "./components.hpp"
#include "./contact_store_events.hpp"

#include <entt/entity/handle.hpp>

#include <iostream>

ContactRegistry4& ContactStore4Impl::registry(void) {
	return _reg;
}

ContactHandle4 ContactStore4Impl::contactHandle(const Contact4 c) {
	return {_reg, c};
}

ContactHandle4 ContactStore4Impl::getOneContactByID(const ByteSpan id) {
	// TODO: accelerate
	// maybe keep it sorted and binary search? hash table lookup?
	for (const auto& [contact, id_comp] : _reg.view<Contact::Components::ID>().each()) {
		if (id == ByteSpan{id_comp.data}) {
			return {_reg, contact};
		}
	}

	return {_reg, entt::null};
}

ContactHandle4 ContactStore4Impl::getOneContactByID(const Contact4 hint, const ByteSpan id) {
	// TODO: implement me
	return getOneContactByID(id);
}

void ContactStore4Impl::throwEventConstruct(const Contact4 c) {
	std::cout << "CS debug: event construct " << entt::to_integral(c) << "\n";
	dispatch(
		ContactStore4_Event::contact_construct,
		ContactStore::Events::Contact4Construct{
			ContactHandle4{_reg, c}
		}
	);
}

void ContactStore4Impl::throwEventUpdate(const Contact4 c) {
	std::cout << "CS debug: event update " << entt::to_integral(c) << "\n";
	dispatch(
		ContactStore4_Event::contact_update,
		ContactStore::Events::Contact4Update{
			ContactHandle4{_reg, c}
		}
	);
}

void ContactStore4Impl::throwEventDestroy(const Contact4 c) {
	std::cout << "CS debug: event destroy " << entt::to_integral(c) << "\n";
	dispatch(
		ContactStore4_Event::contact_destroy,
		ContactStore::Events::Contact4Destory{
			ContactHandle4{_reg, c}
		}
	);
}

