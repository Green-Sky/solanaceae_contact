#include "./contact_store_impl.hpp"

#include "./components.hpp"
#include "./contact_store_events.hpp"

#include <entt/entity/handle.hpp>

#include <map>

#include <iostream>

ContactStore4Impl::~ContactStore4Impl(void) {
}

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

bool ContactStore4Impl::registerComponentToString(
	entt::id_type comp_type,
	comp_to_string_fn fn,
	std::string_view category,
	std::string_view name,
	std::string_view name_full,
	bool advanced
) {
	if (_comp2str.contains(comp_type)) {
		return false;
	}

	if (fn == nullptr) {
		return false;
	}

	_comp2str[comp_type] = Comp2StrEntry{
		fn,
		std::string{category},
		std::string{name},
		std::string{name_full},
		advanced,
	};

	return true;
}

bool ContactStore4Impl::unregisterComponentToString(entt::id_type comp_type) {
	if (!_comp2str.contains(comp_type)) {
		return false;
	}

	_comp2str.erase(comp_type);

	return true;
}


bool ContactStore4Impl::registerImGuiChatTab(
	entt::id_type comp_type,
	imgui_chat_tab_fn fn
) {
	if (_imgui_chat_tab.contains(comp_type)) {
		return false;
	}

	if (fn == nullptr) {
		return false;
	}

	_imgui_chat_tab[comp_type] = ImGuiChatTabEntry{
		fn,
	};

	return true;
}

bool ContactStore4Impl::unregisterImGuiChatTab(entt::id_type comp_type) {
	if (!_imgui_chat_tab.contains(comp_type)) {
		return false;
	}

	_imgui_chat_tab.erase(comp_type);

	return true;
}

#if 0
bool ContactStore4Impl::registerImGuiContext(
	entt::id_type comp_type,
	imgui_context_fn fn
) {
	if (_imgui_context.contains(comp_type)) {
		return false;
	}

	if (fn == nullptr) {
		return false;
	}

	_imgui_context[comp_type] = ImGuiContextEntry{
		fn,
	};

	return true;
}

bool ContactStore4Impl::unregisterImGuiContext(entt::id_type comp_type) {
	if (!_imgui_context.contains(comp_type)) {
		return false;
	}

	_imgui_context.erase(comp_type);

	return true;
}
#endif

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

std::vector<ContactStore4Impl::C2SEntry> ContactStore4Impl::compsToString(ContactHandle4 c) {
	if (!c) {
		return {};
	}

	std::map<std::string_view, std::map<std::string_view, decltype(_comp2str.cbegin())>> cat_map;

	// first iterate all comps the contact has
	// check if we have 2str
	for (const auto& si : c.storage()) {
		const auto c2se_it = _comp2str.find(si.first);
		if (c2se_it == _comp2str.cend()) {
			continue;
		}

		// store sorted by cat
		cat_map[c2se_it->second.category][c2se_it->second.name_full] = c2se_it;
	}

	// unfold into vec
	std::vector<ContactStore4Impl::C2SEntry> vec;
	for (const auto& [_, it] : cat_map) {
		for (const auto& a : it) {
			vec.push_back({
				a.second->first,
				a.second->second.fn,
				a.second->second.category,
				a.second->second.name,
				a.second->second.name_full,
				a.second->second.advanced
			});
		}
	}

	return vec;
}

std::vector<ContactStore4Impl::IGCTEntry> ContactStore4Impl::getImGuiChatTab(ContactHandle4 c) {
	if (!c) {
		return {};
	}

	std::vector<ContactStore4Impl::IGCTEntry> vec;
	for (const auto& si : c.storage()) {
		const auto igct_it = _imgui_chat_tab.find(si.first);
		if (igct_it == _imgui_chat_tab.cend()) {
			continue;
		}

		vec.push_back({
			igct_it->first,
			igct_it->second.fn,
		});
	}
	return vec;
}

#if 0
std::vector<ContactStore4Impl::IGCEntry> ContactStore4Impl::getImGuiContext(ContactHandle4 c) {
	if (!c) {
		return {};
	}

	std::vector<ContactStore4Impl::IGCEntry> vec;
	for (const auto& si : c.storage()) {
		const auto igc_it = _imgui_context.find(si.first);
		if (igc_it == _imgui_context.cend()) {
			continue;
		}

		vec.push_back({
			igc_it->first,
			igc_it->second.fn,
		});
	}
	return vec;
}
#endif
