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


#include "../CabbageCommonHeaders.h"
#include "CabbageWidgetBase.h"

#pragma once

class CabbagePluginEditor;

class CabbageGraphics : public Component, public Timer, public ValueTree::Listener, public CabbageWidgetBase
{
    
    String name, tooltipText, shape;
    ValueTree widgetData;
    Colour outlineColour, mainColour;
    Image img;
    String svgText;
    Image emptyImage;
    void timerCallback() override;
    Component** gc;
public:
//    Component* mainComp;
//    LowLevelGraphicsContext* glRenderer;
    void createImage();
    CabbagePluginEditor* owner;
    const Image* getImage();
    CabbageGraphics (ValueTree cAttr, CabbagePluginEditor* owner);
    ~CabbageGraphics()
    {
        *gc = nullptr;
    };
    void resized() override;



    void valueTreePropertyChanged (ValueTree& valueTree, const Identifier&)  override;
    void drawToOpenGL();

    void valueTreeChildAdded (ValueTree&, ValueTree&) override {}
    void valueTreeChildRemoved (ValueTree&, ValueTree&, int) override {}
    void valueTreeChildOrderChanged (ValueTree&, int, int) override {}
    void valueTreeParentChanged (ValueTree&) override {}

    String getTooltip()
    {
        return tooltipText;
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CabbageGraphics);
};


