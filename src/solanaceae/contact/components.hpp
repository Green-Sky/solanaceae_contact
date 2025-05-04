#pragma once

#include "./fwd.hpp"

#include <entt/entity/entity.hpp>

#include <cstdint>
#include <string>
#include <vector>

// fwd
enum class Object : uint32_t;

namespace Contact::Components {

	struct TagSelfWeak {};
	struct TagSelfStrong {};

	// root node contact (like an account)
	struct TagRoot {};
	// hint to display this contact in the contact list
	struct TagBig {};

	// indicates to the UI, that this should be displayed like a 1to1 chat
	struct TagPrivate {};
	// indicates to the UI to show the subs list by default (overwritten by TagPrivate)
	struct TagGroup {};

	struct RequestIncoming {
		bool name = false;
		bool password = false;
	};
	struct TagRequestOutgoing {};

	// self counterpart
	struct Self {
		Contact4 self;
	};

	// tier 1 ?
	struct Parent {
		Contact4 parent;
	};

	// TODO: maybe rename to children
	// subs are not exclusive (only is some protocols)
	// this is not an indicator of a groupchat
	struct ParentOf {
		std::vector<Contact4> subs;
	};

	// TODO: this is very hacky
	// maybe refwrapper?
	using ContactModel = ContactModel4I*;

	struct Name {
		std::string name;
	};

	// stable, probably unique, ID
	// eg for tox this would be the public key of the contact
	// if the protocol does not have its own ids, you can use a hash or a random byte array
	// TODO: make more length specific variants?
	struct ID {
		std::vector<uint8_t> data;
	};

	// (display)alias

	// tag to signal an avatar change, and the texture needs to be reloaded
	struct TagAvatarInvalidate {};

	struct AvatarObj {
		//ObjectHandle obj;
		Object obj {entt::null};
	};

	struct AvatarMemory {
		// RGBA single-frame
		std::vector<uint8_t> data;
		uint64_t width;
		uint64_t height;
	};

	struct AvatarFile {
		std::string file_path;
	};

	// status

	struct ConnectionState {
		enum State {
			disconnected,
			direct, // tox udp-direct?
			cloud, // tox tcp-relayed / most messengers ?
		} state = disconnected;
	};

	struct StatusText {
		// aka status message
		std::string text;

		// how much of the beginning of the text is the first line
		size_t first_line_length {0u};

		void fillFirstLineLength(void) {
			first_line_length = 0u;
			// find end of line
			for (const auto c : text) {
				if (c == '\n' || c == '\0') {
					break;
				}

				first_line_length++;
			}
		}
	};

	// the first time *we* have seen the contact
	struct FirstSeen {
		uint64_t ts {0};
	};

	struct LastSeen {
		// update rate might vary, check connection state first
		uint64_t ts {0};
	};

	struct LastActivity {
		// message observed
		// maybe status set
		uint64_t ts {0};
	};

	// capabilities, supported by the protocol
	// usually not persistent
	namespace Caps {
		// usually supported, but can mean different things
		// eg tox ngc means destorying your group creds
		struct TagDeletable {};

		// can disconnect/reconnect without deleting
		struct TagConnectable {};

		// TODO: some acl thingy

		// message model?
		struct TagSendMessage {};
		struct SendMessageSize { uint64_t max {0}; };

		struct TagSetName {};

		struct TagSetStatus {}; // none(avail)/away/busy ??

		struct TagSetStatusText {};
		struct StatusTextSize { uint64_t max {0}; };

		struct TagSetStatusRich {}; // whatever that means; kvmap?
	} // Caps

} // Contact::Components

#include "./components_id.inl"

