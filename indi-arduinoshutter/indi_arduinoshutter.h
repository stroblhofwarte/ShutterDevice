/*******************************************************************************
  Copyright(c) 2010 Gerry Rozema. All rights reserved.
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License version 2 as published by the Free Software Foundation.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.
 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
*******************************************************************************/

/******************************************************************************

  Adapted to the ArduinoFW project by Othmar Ehrhardt, 
  https://astro.stroblhof-oberrohrbach.de

******************************************************************************/

#pragma once

#include "indifilterwheel.h"

/**
 * @brief The ArduinoFw class provides a simple arduino based shutter as filter wheel. The filter names are saved to a config file when updated.
 */
namespace Connection
{
  class Serial;
}

class ArduinoFw :  public INDI::FilterWheel
{
  public:
    ArduinoFw() = default;
    virtual ~ArduinoFw() = default;

    bool initProperties() override;
    bool updateProperties() override;
    const char *getDefaultName() override;
    
    virtual int QueryFilter() override;
    virtual bool SelectFilter(int) override;
    virtual void TimerHit() override;

  protected:
    virtual bool Disconnect() override;
    virtual bool Handshake() override;

  private:
    int PortFD = -1;
    Connection::Serial *serialConnection { nullptr };
};