//
// VMime library (http://vmime.sourceforge.net)
// Copyright (C) 2002-2005 Vincent Richard <vincent@vincent-richard.net>
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

#include "vmime/stringContentHandler.hpp"


namespace vmime
{


stringContentHandler::stringContentHandler(const string& buffer, const vmime::encoding& enc)
	: m_encoding(enc), m_string(buffer)
{
}


stringContentHandler::stringContentHandler(const stringContentHandler& cts)
	: contentHandler(), m_encoding(cts.m_encoding), m_string(cts.m_string)
{
}


stringContentHandler::stringContentHandler(const utility::stringProxy& str, const vmime::encoding& enc)
	: m_encoding(enc), m_string(str)
{
}


stringContentHandler::stringContentHandler(const string& buffer, const string::size_type start,
	const string::size_type end, const vmime::encoding& enc)
	: m_encoding(enc), m_string(buffer, start, end)
{
}


stringContentHandler::~stringContentHandler()
{
}


contentHandler* stringContentHandler::clone() const
{
	return new stringContentHandler(*this);
}


stringContentHandler& stringContentHandler::operator=(const stringContentHandler& cts)
{
	m_encoding = cts.m_encoding;
	m_string = cts.m_string;

	return (*this);
}


void stringContentHandler::setData(const utility::stringProxy& str, const vmime::encoding& enc)
{
	m_encoding = enc;
	m_string = str;
}


void stringContentHandler::setData(const string& buffer, const vmime::encoding& enc)
{
	m_encoding = enc;
	m_string.set(buffer);
}


void stringContentHandler::setData(const string& buffer, const string::size_type start,
	const string::size_type end, const vmime::encoding& enc)
{
	m_encoding = enc;
	m_string.set(buffer, start, end);
}


stringContentHandler& stringContentHandler::operator=(const string& buffer)
{
	setData(buffer, NO_ENCODING);
	return (*this);
}


void stringContentHandler::generate(utility::outputStream& os,
	const vmime::encoding& enc, const string::size_type maxLineLength) const
{
	// Managed data is already encoded
	if (isEncoded())
	{
		// The data is already encoded but the encoding specified for
		// the generation is different from the current one. We need
		// to re-encode data: decode from input buffer to temporary
		// buffer, and then re-encode to output stream...
		if (m_encoding != enc)
		{
			utility::auto_ptr <encoder> theDecoder(m_encoding.getEncoder());
			utility::auto_ptr <encoder> theEncoder(enc.getEncoder());

			theEncoder->getProperties()["maxlinelength"] = maxLineLength;

			utility::inputStreamStringProxyAdapter in(m_string);

			std::ostringstream oss;
			utility::outputStreamAdapter tempOut(oss);

			theDecoder->decode(in, tempOut);

			string str = oss.str();
			utility::inputStreamStringAdapter tempIn(str);

			theEncoder->encode(tempIn, os);
		}
		// No encoding to perform
		else
		{
			m_string.extract(os);
		}
	}
	// Need to encode data before
	else
	{
		utility::auto_ptr <encoder> theEncoder(enc.getEncoder());
		theEncoder->getProperties()["maxlinelength"] = maxLineLength;

		utility::inputStreamStringProxyAdapter in(m_string);

		theEncoder->encode(in, os);
	}
}


void stringContentHandler::extract(utility::outputStream& os) const
{
	// No decoding to perform
	if (!isEncoded())
	{
		m_string.extract(os);
	}
	// Need to decode data
	else
	{
		utility::auto_ptr <encoder> theDecoder(m_encoding.getEncoder());

		utility::inputStreamStringProxyAdapter in(m_string);

		theDecoder->decode(in, os);
	}
}


const string::size_type stringContentHandler::getLength() const
{
	return (m_string.length());
}


const bool stringContentHandler::isEmpty() const
{
	return (m_string.length() == 0);
}


const bool stringContentHandler::isEncoded() const
{
	return (m_encoding != NO_ENCODING);
}


const vmime::encoding& stringContentHandler::getEncoding() const
{
	return (m_encoding);
}


} // vmime