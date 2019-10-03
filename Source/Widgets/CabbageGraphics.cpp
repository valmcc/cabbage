/*
  Copyright (C) 2016 Rory Walsh

  Cabbage is free software; you can redistribute it
  and/or modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  Cabbage is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU General Public
  License along with Csound; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA
*/


#include "CabbageGraphics.h"
#include "../Audio/Plugins/CabbagePluginProcessor.h"
#include "../Audio/Plugins/CabbagePluginEditor.h"

CabbageGraphics::CabbageGraphics (ValueTree wData, CabbagePluginEditor* owner) : CabbageWidgetBase(),
widgetData (wData),
owner(owner)

{
    widgetData.addListener (this);
    startTimer(100);
    this->setWantsKeyboardFocus (false);
    initialiseCommonAttributes (this, wData);
}

void CabbageGraphics::timerCallback()
{
    repaint();
}
//==============================================================================
void CabbageGraphics::paint (Graphics& g)
{
    g.fillAll(Colours::black);
    g.drawImageAt(*getImage(), 0, 0);
}

const Image* CabbageGraphics::getImage()
{
    if(CabbagePluginProcessor* proc = dynamic_cast<CabbagePluginProcessor*>(&owner->getProcessor()))
    {

        Image** gc = (Image**)proc->getCsound()->QueryGlobalVariable("graphics1");
        if(*gc != NULL)
            return *gc;
    }

    return nullptr;
}
//==============================================================================
void CabbageGraphics::valueTreePropertyChanged (ValueTree& valueTree, const Identifier& prop)
{
    handleCommonUpdates (this, valueTree);
    repaint();
}




