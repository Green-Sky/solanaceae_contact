#pragma once

#include "./contact_model3.hpp"

#include <string>

// fwd
struct ContactModel3I;

namespace Contact::Components {

	struct TagSelfWeak {};
	struct TagSelfStrong {};
	struct TagBig {};

	// self counterpart
	struct Self {
		Contact3 self;
	};

	// tier 1
	struct Parent {
		Contact3 parent;
	};

	// TODO: maybe rename to children
	struct ParentOf {
		std::vector<Contact3> subs;
	};

	// TODO: this is very hacky
	// maybe refwrapper?
	using ContactModel = ContactModel3I*;

	struct Name {
		std::string name;
	};

	// (display)alias

	// avatar
	// status

	struct ConnectionState {
		enum State {
			disconnected,
			direct, // tox udp-direct?
			cloud, // tox tcp-relayed / most messengers ?
		} state = disconnected;
	};

	// status message
	struct StatusMessage {
		std::string msg;
	};

	// last seen (not disconnected?)

} // Contact::Components

#include "./components_id.inl"

