#pragma once

#include "./fwd.hpp"

#include <string_view>

struct ContactModel4I {
	virtual ~ContactModel4I(void) {}

	// DRAFT: good idea? make it like acceptRequest? change acceptRequest?
	// create and fill in the required info and then tell the CM about it
	// eg tox friend requests will use the tox friend id (with nospam+cs) to send a friend request
	// or ngc will use chatid to join group
	// triggers an construct event on c
	virtual bool addContact(Contact4 c) = 0;

	//// eg tox friend id is toxid (with nospam) and include the hello text in the request, but self_name and pw are ignored
	//// tox ngc id is chatid, self_name and pw are used, but hello_text is ignored
	//// TODO: how to diff???
	//// triggers an construct event on c
	//virtual bool addContact(std::string_view id, std::string_view hello_text, std::string_view self_name, std::string_view password);

	// accept incoming request
	// triggers an update event on c
	virtual bool acceptRequest(Contact4 c, std::string_view self_name, std::string_view password) = 0;

	// delete
	// triggers a destroy event on c
	virtual bool leave(Contact4 c, std::string_view reason) = 0;

	// invite c to to (as you speak it)
	// eg on tox, only firends can be invited
	virtual bool invite(Contact4 c, Contact4 to) = 0;
	// might be called rapidly from ui code
	virtual bool canInvite(Contact4 c, Contact4 to) = 0;
};

