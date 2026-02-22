#pragma once

#include "./contact_store_i.hpp"

#include <entt/entity/registry.hpp>
#include <entt/container/dense_map.hpp>

// default implementation
struct ContactStore4Impl : public ContactStore4I {
	~ContactStore4Impl(void);

	ContactRegistry4& registry(void) override;
	ContactHandle4 contactHandle(const Contact4 c) override;

	ContactHandle4 getOneContactByID(const ByteSpan id) override;
	ContactHandle4 getOneContactByID(const Contact4 hint, const ByteSpan id) override;

	bool registerComponentToString(
		entt::id_type comp_type,
		comp_to_string_fn fn,
		std::string_view category,
		std::string_view name, // user visible
		std::string_view name_full, // for the editor (derive cat from this?)
		bool advanced = true // not visible by default
	) override;
	bool unregisterComponentToString(entt::id_type comp_type) override;

	void throwEventConstruct(const Contact4 c) override;
	void throwEventUpdate(const Contact4 c) override;
	void throwEventDestroy(const Contact4 c) override;

	public:
		// TODO: think about promoting to interface
		struct C2SEntry {
			entt::id_type id;
			comp_to_string_fn* fn;
			std::string_view category;
			std::string_view name;
			std::string_view name_full;
			bool advanced;
		};
		std::vector<C2SEntry> compsToString(ContactHandle4 c);

	private:
		entt::basic_registry<Contact4> _reg;

		struct Comp2StrEntry {
			comp_to_string_fn* fn;
			std::string category;
			std::string name;
			std::string name_full;
			bool advanced;
		};
		entt::dense_map<entt::id_type, Comp2StrEntry> _comp2str;
};

