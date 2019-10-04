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
owner(owner),
image(Image::RGB, 300, 400, true),
myGraphics(image)
{
    if (auto* peer = getPeer())
        peer->setCurrentRenderingEngine (0);
    
    openGLContext.attachTo (*this);
   
    widgetData.addListener (this);
    startTimer(10);
    this->setWantsKeyboardFocus (false);
    initialiseCommonAttributes (this, wData);
}

void CabbageGraphics::timerCallback()
{
    myGc.fillAll(Colours::red);
    myGc.setColour(Colours::green);
    myGc.fillEllipse(x+=10, 10, 10, 10);
    repaint();
}
//==============================================================================
void CabbageGraphics::paint (Graphics& g)
{
    g.drawImageAt(image, 0, 0);
}

Image* CabbageGraphics::getImage()
{
    if(CabbagePluginProcessor* proc = dynamic_cast<CabbagePluginProcessor*>(&owner->getProcessor()))
    {

        Image** gc = (Image**)proc->getCsound()->QueryGlobalVariable("graphics1");
        if(*gc)
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




