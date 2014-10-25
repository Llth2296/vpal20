    //------------------------------------------------------------------------------
/*
    Portions of this file are from Vpallab: https://github.com/vpallabs
    Copyright (c) 2013 - 2014 - Vpallab.com.
    Please visit http://www.vpallab.com/
    
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2012, 2013 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef RIPPLE_APP_RPCHTTPSERVER_H_INCLUDED
#define RIPPLE_APP_RPCHTTPSERVER_H_INCLUDED

#include <ripple/core/Config.h>
#include <beast/utility/Journal.h>
#include <beast/utility/PropertyStream.h>
#include <beast/cxx14/memory.h> // <memory>

namespace ripple {

class RPCHTTPServer
    : public beast::Stoppable
    , public beast::PropertyStream::Source
{
protected:
    RPCHTTPServer (Stoppable& parent);

public:
    virtual
    ~RPCHTTPServer() = default;

    /** Opens listening ports based on the Config settings
        This is implemented outside the constructor to support
        two-stage initialization in the Application object.
    */
    virtual
    void
    setup (beast::Journal journal) = 0;
};

std::unique_ptr <RPCHTTPServer>
make_RPCHTTPServer (beast::Stoppable& parent, JobQueue& jobQueue,
    NetworkOPs& networkOPs, Resource::Manager& resourceManager,
        RPC::Setup const& setup);

} // ripple

#endif