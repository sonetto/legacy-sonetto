/*-----------------------------------------------------------------------------
This source file is part of Sonetto RPG Engine.

Copyright (C) 2007,2008 Arthur Carvalho de Souza Lima, Guilherme Pr� Vieira


Sonetto RPG Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Sonetto RPG Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA or go to
http://www.gnu.org/copyleft/lesser.txt
-----------------------------------------------------------------------------*/

#ifndef SONETTO_OPCODEHANDLER_H
#define SONETTO_OPCODEHANDLER_H

#include "SonettoPrerequisites.h"

namespace Sonetto
{
    class OpcodeHandler
    {
    public:
        OpcodeHandler() : mRegistered(false) {}
        virtual ~OpcodeHandler();

        virtual int handleOpcode(Script *script,
            size_t id,Opcode *opcode) = 0;

        virtual void registerOpcodes() { mRegistered = true; }
        virtual void unregisterOpcodes() { mRegistered = false; }

    protected:
        bool mRegistered;
    };
} // namespace Sonetto

#endif
