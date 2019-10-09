/*
 Copyright (C) 2016 Rory Walsh

 Cabbage is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 Cabbage is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU General Public
 License along with Csound; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 02111-1307 USA
*/


#include "CabbageGraphics.h"
#include "../Audio/Plugins/CabbagePluginProcessor.h"
#include "../Audio/Plugins/CabbagePluginEditor.h"

using GL = juce::OpenGLExtensionFunctions;

CabbageGraphics::CabbageGraphics (ValueTree wData, CabbagePluginEditor* owner) : CabbageWidgetBase(),
                                                                                 widgetData (wData),
                                                                                 owner(owner)
{

    if (auto* peer = getPeer())
        peer->setCurrentRenderingEngine (0);
    
    if(CabbagePluginProcessor* proc = dynamic_cast<CabbagePluginProcessor*>(&owner->getProcessor()))
    {
        gc = (Component **) proc->getCsound()->QueryGlobalVariable("component");

    }

    openGLContext.setRenderer(this);
    openGLContext.attachTo(*this);
    openGLContext.setContinuousRepainting (true);
    widgetData.addListener (this);
    initialiseCommonAttributes (this, wData);
}

void CabbageGraphics::createImage()
{

}

void CabbageGraphics::newOpenGLContextCreated()
{
    // This will identify our vertex buffer
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
};

void CabbageGraphics::openGLContextClosing()
{
}

void CabbageGraphics::renderOpenGL()
{
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    openGLContext.extensions.glActiveTexture (GL_TEXTURE0);
    glEnable (GL_TEXTURE_2D);
//     glBegin(GL_POLYGON);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

void CabbageGraphics::timerCallback()
{
    static_cast<Component*>(*gc)->repaint();
    repaint();
}

void CabbageGraphics::resized()
{
//    static_cast<Component*>(*gc)->setBounds(getLocalBounds());
}


//void CabbageGraphics::renderOpenGL()
//{
// glEnable (GL_DEPTH_TEST);
// glDepthFunc (GL_LESS);
// glEnable (GL_BLEND);
// glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
// openGLContext.extensions.glActiveTexture (GL_TEXTURE0);
// glEnable (GL_TEXTURE_2D);
//
// glViewport (0, 0, roundToInt (getWidth()), roundToInt (getHeight()));
//
//
// glBegin(GL_POLYGON);
// glColor3d(255,0,0);
// int x1 = 20;
// int y1 = 20;
// double halfside = 40 / 2;
// glVertex2d(x1 + halfside, y1 + halfside);
// glVertex2d(x1 + halfside, y1 - halfside);
// glVertex2d(x1 - halfside, y1 - halfside);
// glVertex2d(x1 - halfside, y1 + halfside);
// glEnd();
// drawToOpenGL();
//}
//==============================================================================
//void CabbageGraphics::drawToOpenGL(OpenGLContext openGL)
//{
//std::unique_ptr<LowLevelGraphicsContext> glRenderer (createOpenGLGraphicsContext (openGLContext,
// getWidth(),
// getHeight()));
// if (glRenderer.get() != nullptr)
// {
// Graphics g(*glRenderer);
// Random rand;
// g.fillAll(Colours::red);
// g.setColour(Colours::white);
// g.fillEllipse(rand.nextFloat()*100, 50, 10, 10);
// g.drawImageAt(*getImage(), 0, 0);
// }
//}
//==============================================================================
void CabbageGraphics::valueTreePropertyChanged (ValueTree& valueTree, const Identifier& prop)
{
    handleCommonUpdates (this, valueTree);
    repaint();
}
