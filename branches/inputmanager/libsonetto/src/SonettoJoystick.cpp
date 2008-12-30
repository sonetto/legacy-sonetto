/*-----------------------------------------------------------------------------
Copyright (c) 2009, Sonetto Project Developers
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1.  Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
2.  Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
3.  Neither the name of the Sonetto Project nor the names of its contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------*/

#include <iostream>
#include "SonettoJoystick.h"

namespace Sonetto
{
    // ----------------------------------------------------------------------
    // Sonetto::Joystick implementation
    // ----------------------------------------------------------------------
    Joystick::~Joystick()
    {
        if (mJoy != NULL)
        {
            SDL_JoystickClose(mJoy);
        }
    }
    // ----------------------------------------------------------------------
    bool Joystick::isPlugged()
    {
        if (!mJoy)
        {
            return false;
        }

        #ifdef WINDOWS
        SONETTO_THROW("Implement Joystick::isPlugged() winmm hack");
        /*{
            JOYINFOEX joyinfo;

            if (joyGetPosEx(hwData->id,&joyinfo) == JOYERR_UNPLUGGED)
            {
                return false;
            }
        }*/
        #endif

        return true;
    }
    // ----------------------------------------------------------------------
    void Joystick::setEnabled(bool enable)
    {
        if (enable) {
            if (!mJoy)
            {
                mJoy = SDL_JoystickOpen(mID - 1);
            }
        } else {
            if (mJoy)
            {
                SDL_JoystickClose(mJoy);
                mJoy = NULL;
            }
        }
    }
    // ----------------------------------------------------------------------
    bool Joystick::getRawButtonState(RawButton button)
    {
        if (!mJoy)
        {
            return false;
        }

        if (button < RWB_FIRST_HAT) {
            return SDL_JoystickGetButton(mJoy,button - 1);
        } else {
            if (SDL_JoystickNumHats(mJoy) < 1)
            {
                return false;
            }

            uint8 hatone = SDL_JoystickGetHat(mJoy,0);
            switch (button - RWB_FIRST_HAT)
            {
                case 0:
                    return (hatone & SDL_HAT_UP);
                break;

                case 1:
                    return (hatone & SDL_HAT_RIGHT);
                break;

                case 2:
                    return (hatone & SDL_HAT_DOWN);
                break;

                case 3:
                    return (hatone & SDL_HAT_LEFT);
                break;

                default:
                    return false;
                break;
            }
        }
    }
    // ----------------------------------------------------------------------
    Ogre::Vector2 Joystick::getRawAnalogState(RawAnalog analog,
            InputSource::InvertInput invertions)
    {
        if (!mJoy)
        {
            return Ogre::Vector2(0.0f,0.0f);
        }

        Ogre::Vector2 state;
        uint8 baseid = (analog - 1) * 2,xid = 0,yid = 1;

        if (invertions & InputSource::INV_ORDER)
        {
            xid = 1;
            yid = 0;
        }

        state.x = SDL_JoystickGetAxis(mJoy,baseid + xid);
        state.y = SDL_JoystickGetAxis(mJoy,baseid + yid);

        state.x /= ((state.x > 0) ? 32767.0f : 32768.0f);
        state.y /= ((state.y > 0) ? 32767.0f : 32768.0f);

        if (invertions & InputSource::INV_X_POLARITY)
        {
            state.x = -state.x;
        }

        if (invertions & InputSource::INV_Y_POLARITY)
        {
            state.y = -state.y;
        }

        return state;
    }
} // namespace

