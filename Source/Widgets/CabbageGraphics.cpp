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

    addAndMakeVisible(mainComp = new Component());
    startTimer(100);

//    openGLContext.setContinuousRepainting (true);

    if(CabbagePluginProcessor* proc = dynamic_cast<CabbagePluginProcessor*>(&owner->getProcessor()))
    {
        proc->getCsound()->CreateGlobalVariable("component", sizeof(Component*));
        Component** gc = (Component **) proc->getCsound()->QueryGlobalVariable("component");
        *gc = mainComp;


    }


    widgetData.addListener (this);
    initialiseCommonAttributes (this, wData);
}

void CabbageGraphics::createImage()
{

}
void CabbageGraphics::timerCallback()
{
    repaint();
}

void CabbageGraphics::resized()
{
    mainComp->setBounds(getLocalBounds());
}


//void CabbageGraphics::renderOpenGL()
//{
//    glEnable (GL_DEPTH_TEST);
//    glDepthFunc (GL_LESS);
//    glEnable (GL_BLEND);
//    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    openGLContext.extensions.glActiveTexture (GL_TEXTURE0);
//    glEnable (GL_TEXTURE_2D);
//
//    glViewport (0, 0, roundToInt (getWidth()), roundToInt (getHeight()));
//
//
//    glBegin(GL_POLYGON);
//    glColor3d(255,0,0);
//    int x1 = 20;
//    int y1 = 20;
//    double halfside = 40 / 2;
//    glVertex2d(x1 + halfside, y1 + halfside);
//    glVertex2d(x1 + halfside, y1 - halfside);
//    glVertex2d(x1 - halfside, y1 - halfside);
//    glVertex2d(x1 - halfside, y1 + halfside);
//    glEnd();
//    drawToOpenGL();
//}
//==============================================================================
void CabbageGraphics::drawToOpenGL()
{
    std::unique_ptr<LowLevelGraphicsContext> glRenderer (createOpenGLGraphicsContext (openGLContext,
                                                                                      getWidth(),
                                                                                      getHeight()));
        if (glRenderer.get() != nullptr)
        {
            Graphics g(*glRenderer);
//            Random rand;
//            g.fillAll(Colours::red);
//            g.setColour(Colours::white);
//            g.fillEllipse(rand.nextFloat()*100, 50, 10, 10);
//            g.drawImageAt(*getImage(), 0, 0);
        }
}


const Image* CabbageGraphics::getImage()
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




