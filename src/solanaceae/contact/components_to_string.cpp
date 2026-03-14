#include "./components_to_string.hpp"

#include "./components.hpp"

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>
#include <entt/entity/handle.hpp>

#include <solanaceae/util/utils.hpp>

#include <string>

namespace Contact {

void registerComponents2Str(ContactStore4I& cs) {
#define regTag(X, Cat, Adv) \
	cs.registerComponentToString( \
		entt::type_id<Contact::Components::X>().hash(), \
		+[](ContactHandle4, bool) -> std::string { return ""; }, \
		Cat, \
		#X, \
		entt::type_id<Contact::Components::X>().name(), \
		Adv \
	)

	regTag(TagSelfWeak, "Self", true);
	regTag(TagSelfStrong, "Self", true);
	regTag(TagRoot, "Hierarchy", false);
	regTag(TagBig, "Hierarchy", false);
	regTag(TagPrivate, "Hierarchy", false);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::RequestIncoming>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			const auto& comp = c.get<Contact::Components::RequestIncoming>();
			return
				std::string{"name:"} + (comp.name ? "true" : "false") +
				std::string{" password:"} + (comp.password ? "true" : "false")
			;
		},
		"", // general
		"RequestIncoming",
		entt::type_id<Contact::Components::RequestIncoming>().name(),
		true
	);

	regTag(TagRequestOutgoing, "", true);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::Self>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			const auto& self_comp = c.get<Contact::Components::Self>();
			return std::to_string(entt::to_entity(self_comp.self));
		},
		"Self",
		"Self",
		entt::type_id<Contact::Components::Self>().name(),
		true
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::Parent>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			const auto& parent_comp = c.get<Contact::Components::Parent>();
			return std::to_string(entt::to_entity(parent_comp.parent));
		},
		"", // general
		"Parent",
		entt::type_id<Contact::Components::Parent>().name(),
		true
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::ParentOf>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			const auto& subs_comp = c.get<Contact::Components::ParentOf>();
			std::string str;
			for (const auto& sub : subs_comp.subs) {
				str += std::to_string(entt::to_entity(sub)) + ",";
			}
			return str;
		},
		"", // general
		"ParentOf",
		entt::type_id<Contact::Components::ParentOf>().name(),
		true
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::ContactModel>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			// TODO: hex?
			return std::to_string(reinterpret_cast<intptr_t>(c.get<Contact::Components::ContactModel>()));
		},
		"", // general
		"ContactModel",
		entt::type_id<Contact::Components::ContactModel>().name(),
		true
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::Name>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string { return c.get<Contact::Components::Name>().name; },
		"", // general
		"Name",
		entt::type_id<Contact::Components::Name>().name(),
		false
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::ID>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string { return bin2hex(c.get<Contact::Components::ID>().data); },
		"", // general
		"ID",
		entt::type_id<Contact::Components::ID>().name(),
		false // maybe
	);

	regTag(TagAvatarInvalidate, "Avatar", true);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::AvatarObj>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			return std::to_string(entt::to_entity(c.get<Contact::Components::AvatarObj>().obj));
		},
		"Avatar",
		"AvatarObj",
		entt::type_id<Contact::Components::AvatarObj>().name(),
		true
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::AvatarMemory>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			const auto& comp = c.get<Contact::Components::AvatarMemory>();
			return std::to_string(comp.width) + "x" + std::to_string(comp.height) + "," + std::to_string(comp.data.size()) + "bytes";
		},
		"Avatar",
		"AvatarMemory",
		entt::type_id<Contact::Components::AvatarMemory>().name(),
		true
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::AvatarFile>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			return c.get<Contact::Components::AvatarFile>().file_path;
		},
		"Avatar",
		"AvatarFile",
		entt::type_id<Contact::Components::AvatarFile>().name(),
		true
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::ConnectionState>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			switch (c.get<Contact::Components::ConnectionState>().state) {
				case Contact::Components::ConnectionState::State::disconnected: return "disconnected";
				case Contact::Components::ConnectionState::State::direct: return "direct";
				case Contact::Components::ConnectionState::State::cloud: return "cloud";
			}
			std::abort();
		},
		"Status",
		"ConnectionState",
		entt::type_id<Contact::Components::ConnectionState>().name(),
		false
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::StatusText>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			const auto& comp = c.get<Contact::Components::StatusText>();
			if (verbose) {
				return comp.text;
			} else {
				return comp.text.substr(0, comp.first_line_length);
			}
		},
		"Status",
		"StatusText",
		entt::type_id<Contact::Components::StatusText>().name(),
		false
	);

	// TODO: all the timestamps to human
	cs.registerComponentToString(
		entt::type_id<Contact::Components::FirstSeen>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			return std::to_string(c.get<Contact::Components::FirstSeen>().ts);
		},
		"Time",
		"FirstSeen",
		entt::type_id<Contact::Components::FirstSeen>().name(),
		false
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::LastSeen>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			return std::to_string(c.get<Contact::Components::LastSeen>().ts);
		},
		"Time",
		"LastSeen",
		entt::type_id<Contact::Components::LastSeen>().name(),
		false
	);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::LastActivity>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			return std::to_string(c.get<Contact::Components::LastActivity>().ts);
		},
		"Time",
		"LastActivity",
		entt::type_id<Contact::Components::LastActivity>().name(),
		false
	);

#undef regTag

#define regCapTag(X) \
	cs.registerComponentToString( \
		entt::type_id<Contact::Components::Caps::X>().hash(), \
		+[](ContactHandle4, bool) -> std::string { return ""; }, \
		"Caps", \
		#X, \
		entt::type_id<Contact::Components::Caps::X>().name(), \
		true \
	)

	regCapTag(TagDeletable);
	regCapTag(TagConnectable);
	regCapTag(TagSendMessage);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::Caps::SendMessageSize>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			return std::to_string(c.get<Contact::Components::Caps::SendMessageSize>().max);
		},
		"Caps",
		"SendMessageSize",
		entt::type_id<Contact::Components::Caps::SendMessageSize>().name(),
		true
	);

	regCapTag(TagSetName);
	regCapTag(TagSetStatus);
	regCapTag(TagSetStatusText);

	cs.registerComponentToString(
		entt::type_id<Contact::Components::Caps::StatusTextSize>().hash(),
		+[](ContactHandle4 c, bool verbose) -> std::string {
			return std::to_string(c.get<Contact::Components::Caps::StatusTextSize>().max);
		},
		"Caps",
		"StatusTextSize",
		entt::type_id<Contact::Components::Caps::StatusTextSize>().name(),
		true
	);

	regCapTag(TagSetStatusRich);

#undef regCapTag
}

} // Contact
