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

	bool registerImGuiChatTab(
		entt::id_type comp_type,
		imgui_chat_tab_fn fn
	) override;
	bool unregisterImGuiChatTab(entt::id_type comp_type) override;

#if 0
	bool registerImGuiContext(
		entt::id_type comp_type,
		imgui_context_fn fn
	) override;
	bool unregisterImGuiContext(entt::id_type comp_type) override;
#endif

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

		struct IGCTEntry {
			entt::id_type id;
			imgui_chat_tab_fn* fn;
		};
		std::vector<IGCTEntry> getImGuiChatTab(ContactHandle4 c);

#if 0
		struct IGCEntry {
			entt::id_type id;
			imgui_context_fn* fn;
		};
		std::vector<IGCEntry> getImGuiContext(ContactHandle4 c);
#endif

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

		struct ImGuiChatTabEntry {
			imgui_chat_tab_fn* fn;
		};
		entt::dense_map<entt::id_type, ImGuiChatTabEntry> _imgui_chat_tab;

#if 0
		struct ImGuiContextEntry {
			imgui_context_fn* fn;
		};
		entt::dense_map<entt::id_type, ImGuiContextEntry> _imgui_context;
#endif
};

