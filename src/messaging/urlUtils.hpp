//
// VMime library (http://vmime.sourceforge.net)
// Copyright (C) 2002-2004 Vincent Richard <vincent@vincent-richard.net>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef VMIME_MESSAGING_URLUTILS_HPP_INCLUDED
#define VMIME_MESSAGING_URLUTILS_HPP_INCLUDED


#include "../types.hpp"
#include "../base.hpp"


namespace vmime {
namespace messaging {


/** Miscellaneous functions related to URLs.
  */

class urlUtils
{
public:

	/** Encode extended characters in a URL string (ASCII characters
	  * are unmodified, other are encoded as '%' followed by hex code).
	  */
	static const string encode(const string& s);

	/** Decode an hex-encoded URL (see encode()).
	  */
	static const string decode(const string& s);
};


} // messaging
} // vmime


#endif // VMIME_MESSAGING_URLUTILS_HPP_INCLUDED