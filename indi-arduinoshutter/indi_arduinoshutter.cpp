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

#include "indicom.h"
#include "connectionplugins/connectionserial.h"
#include "indi_arduinofw.h"

#include <memory>

#define COM_TIMEOUT  1000
#define POLL_TIMER 100
// We declare an auto pointer to ArduinoFw.
std::unique_ptr<ArduinoFw> arduinofw(new ArduinoFw());

void ISPoll(void *p);

void ISGetProperties(const char *dev)
{
    arduinofw->ISGetProperties(dev);
}

void ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
    arduinofw->ISNewSwitch(dev, name, states, names, n);
}

void ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n)
{
    arduinofw->ISNewText(dev, name, texts, names, n);
}

void ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n)
{
    arduinofw->ISNewNumber(dev, name, values, names, n);
}

void ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[], char *formats[],
               char *names[], int n)
{
    INDI_UNUSED(dev);
    INDI_UNUSED(name);
    INDI_UNUSED(sizes);
    INDI_UNUSED(blobsizes);
    INDI_UNUSED(blobs);
    INDI_UNUSED(formats);
    INDI_UNUSED(names);
    INDI_UNUSED(n);
}
void ISSnoopDevice(XMLEle *root)
{
    arduinofw->ISSnoopDevice(root);
}

const char *ArduinoFw::getDefaultName()
{
    return "Arduino Shutter";
}

bool ArduinoFw::initProperties()
{
    INDI::FilterWheel::initProperties();

    serialConnection = new Connection::Serial(this);
    serialConnection->registerHandshake([&]()
    {
        return Handshake();
    });
    registerConnection(serialConnection);

    serialConnection->setDefaultPort("/dev/ttyUSB0");
    serialConnection->setDefaultBaudRate(serialConnection->B_115200);

    return true;
}

bool ArduinoFw::updateProperties()
{
    INDI::FilterWheel::updateProperties();

    if (isConnected())
    {
        CurrentFilter = 1;
    }
    else
    {
        
    }

    return true;
}

bool ArduinoFw::Disconnect() 
{

    return true;
}

bool ArduinoFw::Handshake()
{
    char greeting_cmd[32] = "G";
    char cmd_res[16] = {0};
    int nbytes_written = 0;
    int nbytes_read = 0;

    LOG_DEBUG("Handshake");

    tty_write_string(PortFD, greeting_cmd, &nbytes_written);
    if (tty_read_section(PortFD, cmd_res, '#', COM_TIMEOUT, &nbytes_read) == TTY_OK) {
        LOGF_DEBUG("RES (%s)", cmd_res);
        return true;
    } else {
        LOG_ERROR("ERROR HANDSHAKE");
    }

    return false;
}

bool ArduinoFw::SelectFilter(int f)
{
    CurrentFilter = f;
    SetTimer(POLLMS);
    return true;
}

int ArduinoFw::QueryFilter()
{
    return CurrentFilter;
}

void ArduinoFw::TimerHit()
{
    QueryFilter();

    if (CurrentFilter != TargetFilter)
    {
        SetTimer(POLL_TIMER);
    }
    else
    {
        SelectFilterDone(CurrentFilter);
    }
}