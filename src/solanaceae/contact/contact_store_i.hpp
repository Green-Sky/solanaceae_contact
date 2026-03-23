#pragma once

#include "./fwd.hpp"

#include <solanaceae/util/span.hpp>
#include <solanaceae/util/event_provider.hpp>

#include <string>

enum class ContactStore4_Event : uint16_t {
	contact_construct,
	contact_update,
	contact_destroy,

	MAX
};

struct ContactStore4EventI {
	using enumType = ContactStore4_Event;

	virtual ~ContactStore4EventI(void) {}

	virtual bool onEvent(const ContactStore::Events::Contact4Construct&) { return false; }
	virtual bool onEvent(const ContactStore::Events::Contact4Update&) { return false; }
	virtual bool onEvent(const ContactStore::Events::Contact4Destory&) { return false; }
};
using ContactStore4EventProviderI = EventProviderI<ContactStore4EventI>;

struct ContactStore4I : public ContactStore4EventProviderI{
	static constexpr const char* version {"4"};

	virtual ContactRegistry4& registry(void) = 0;
	virtual ContactHandle4 contactHandle(const Contact4 c) = 0;

	virtual ContactHandle4 getOneContactByID(const ByteSpan id) = 0;
	virtual ContactHandle4 getOneContactByID(const Contact4 hint, const ByteSpan id) = 0;

	// TODO: maybe not string? hmm
	using comp_to_string_fn = std::string(ContactHandle4 c, bool verbose);
	virtual bool registerComponentToString(
		entt::id_type comp_type,
		comp_to_string_fn fn,
		std::string_view category,
		std::string_view name, // user visible
		std::string_view name_full, // for the editor (derive cat from this?)
		bool advanced = true // not visible by default
	) = 0;
	virtual bool unregisterComponentToString(entt::id_type comp_type) = 0;

	// TODO: think about this more
	//using comp_to_imgui_fn = void(ContactHandle4 c, bool verbose);
	//virtual bool registerComponentToImGui(
	//    entt::id_type comp_type,
	//    std::string_view category,
	//    std::string_view name, // user visible
	//    std::string_view name_full, // for the editor (derive cat from this?)
	//    bool advanced = true // not visible by default
	//) = 0;
	//virtual bool unregisterComponentToImGui(entt::id_type comp_type) = 0;

	// comp_type gated, fn has to manage the tab item
	using imgui_chat_tab_fn = void(ContactHandle4 c);
	virtual bool registerImGuiChatTab(
		entt::id_type comp_type,
		imgui_chat_tab_fn fn
	) = 0;
	virtual bool unregisterImGuiChatTab(entt::id_type comp_type) = 0;

	// not used yet, not gonna push untested apis
#if 0
	// fn gets called in the context menu
	using imgui_context_fn = void(ContactHandle4 c);
	virtual bool registerImGuiContext(
		entt::id_type comp_type,
		imgui_context_fn fn
	) = 0;
	virtual bool unregisterImGuiContext(entt::id_type comp_type) = 0;
#endif

	virtual void throwEventConstruct(const Contact4 c) = 0;
	virtual void throwEventUpdate(const Contact4 c) = 0;
	//virtual void throwEventUpdate(const Contact4 c, std::vector<entt::id_type> comp_list) = 0;
	virtual void throwEventDestroy(const Contact4 c) = 0;
};

