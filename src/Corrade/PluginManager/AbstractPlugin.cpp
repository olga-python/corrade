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

#include "AbstractPlugin.h"

#include "Corrade/PluginManager/AbstractManager.h"
#include "Corrade/Utility/Assert.h"

namespace Corrade { namespace PluginManager {

void AbstractPlugin::initialize() {}

void AbstractPlugin::finalize() {}

AbstractPlugin::AbstractPlugin(): _manager(nullptr), _metadata(nullptr) {}

AbstractPlugin::AbstractPlugin(AbstractManager& manager, std::string plugin): _manager(&manager) {
    _manager->registerInstance(std::move(plugin), *this, _metadata);
}

AbstractPlugin::~AbstractPlugin() {
    /* Unregister the instance only if the plugin was instantiated through
       plugin manager */
    if(_manager && _metadata)
        _manager->unregisterInstance(_metadata->name(), *this);
}

bool AbstractPlugin::canBeDeleted() { return false; }

}}
