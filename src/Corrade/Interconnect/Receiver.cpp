/*
    This file is part of Corrade.

    Copyright © 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include "Receiver.h"

#include "Corrade/Interconnect/Emitter.h"
#include "Corrade/Utility/Assert.h"

namespace Corrade { namespace Interconnect {

Receiver::Receiver() = default;

Receiver::~Receiver() {
    for(auto end = connections.end(), it = connections.begin(); it != end; ++it) {
        /* Remove connection from emitter */
        for(auto end = (*it)->emitter->connections.end(), eit = (*it)->emitter->connections.begin(); eit != end; ++eit) {
            if(eit->second != *it) continue;

            (*it)->emitter->connections.erase(eit);
            (*it)->emitter->connectionsChanged = true;
            break;
        }

        /* If there is connection object, remove reference to connection data
           from it and mark it as disconnected */
        if((*it)->connection) {
            CORRADE_INTERNAL_ASSERT(*it == (*it)->connection->data);
            (*it)->connection->data = nullptr;
            (*it)->connection->connected = false;
        }

        /* Delete connection data (as they make no sense without receiver) */
        delete *it;
    }
}

void Receiver::disconnectAllSlots() {
    for(auto it = connections.begin(); it != connections.end(); ++it) {
        /* Remove connection from emitter */
        for(auto end = (*it)->emitter->connections.end(), eit = (*it)->emitter->connections.begin(); eit != end; ++eit) {
            if(eit->second != *it) continue;

            (*it)->emitter->connections.erase(eit);
            (*it)->emitter->connectionsChanged = true;
            break;
        }

        /* If there is no connection object, destroy also connection data (as we
           are the last remaining owner) */
        if(!(*it)->connection) delete *it;

        /* Else mark the connection as disconnected */
        else (*it)->connection->connected = false;
    }

    connections.clear();
}

}}
