/*
  Copyright (C) 2016 Rory Walsh

  Cabbage is free software; you can redistribute it
  and/or modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  Cabbage is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with Csound; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307 USA
*/

#ifndef CABBAGEPLUGINEDITOR_H_INCLUDED
#define CABBAGEPLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "CabbagePluginProcessor.h"
#include "CabbageAudioParameter.h"

#include "../../InterfaceEditor/ComponentLayoutEditor.h"

#include "../../Widgets/CabbageCheckbox.h"
#include "../../Widgets/CabbageComboBox.h"
#include "../../Widgets/CabbageImage.h"
#include "../../Widgets/CabbageCustomWidgets.h"

class CabbagePluginEditor;

//==============================================================================
static CabbagePluginEditor* getPluginEditor(Component* child)
{
	if(CabbagePluginEditor* c = child->findParentComponentOfClass<CabbagePluginEditor>())
		return c;
	else
		return nullptr;
}

//==============================================================================
class CabbagePluginEditor  : public AudioProcessorEditor, public Button::Listener,
							 public ChangeBroadcaster, public ComboBoxListener
{
public:
    CabbagePluginEditor (CabbagePluginProcessor&);
    ~CabbagePluginEditor();

	void createEditorInterface(ValueTree widgets);	
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	
	OwnedArray<Component> components;				
	Component mainComponent;						
	CabbageLookAndFeel2 lookAndFeel;					

	TooltipWindow tooltipWindow;
	//==============================================================================
	void SetupWindow(ValueTree cabbageWidgetData);
	// the following methods instantiate controls that CAN
	// be automated in a host...
	void InsertSlider(ValueTree cabbageWidgetData){};
    void InsertComboBox(ValueTree cabbageWidgetData);
    void InsertButton(ValueTree cabbageWidgetData){};
    void InsertCheckbox(ValueTree cabbageWidgetData);
    void InsertXYPad(ValueTree cabbageWidgetData){};
    void InsertRangeSlider(ValueTree cabbageWidgetData){};
	//the following methods instantiate controls that CANNOT 
	// be automated in a host...
    void InsertGroupBox(ValueTree cabbageWidgetData){};
    void InsertSoundfiler(ValueTree cabbageWidgetData){};
    void InsertSourceButton(ValueTree cabbageWidgetData){};
    void InsertDirectoryList(ValueTree cabbageWidgetData){};
    void InsertTextEditor(ValueTree cabbageWidgetData){};
    void InsertCsoundOutput(ValueTree cabbageWidgetData){};
    void InsertMIDIKeyboard(ValueTree cabbageWidgetData){};
    void InsertFileButton(ValueTree cabbageWidgetData){};
    void InsertRecordButton(ValueTree cabbageWidgetData){};
    void InsertImage(ValueTree cabbageWidgetData);
    void InsertLabel(ValueTree cabbageWidgetData){};
    void InsertTable(ValueTree cabbageWidgetData){};
    void InsertMultiTab(ValueTree cabbageWidgetData){};
    void InsertEncoder(ValueTree cabbageWidgetData){};
    void InsertInfoButton(ValueTree cabbageWidgetData){};
    void InsertLineSeparator(ValueTree cabbageWidgetData){};
    void InsertScope(ValueTree cabbageWidgetData){};
    void InsertPatternMatrix(ValueTree cabbageWidgetData){};
    void InsertSnapshot(ValueTree cabbageWidgetData){};
    void InsertTransport(ValueTree cabbageWidgetData){};
    void InsertListbox(ValueTree cabbageWidgetData){};
    void InsertPopupMenu(ValueTree cabbageWidgetData){};
    void InsertGenTable(ValueTree cabbageWidgetData){};
    void InsertTextbox(ValueTree cabbageWidgetData){};
    void InsertSignalDisplay(ValueTree cabbageWidgetData){};
    void InsertStepper(ValueTree cabbageWidgetData){};
    void InsertNumberBox(ValueTree cabbageWidgetData){};

	//=============================================================================
	void enableGUIEditor(bool enable);
	void setCurrentlySelectedComponents(StringArray componentNames);
	Array<ValueTree> getValueTreesForCurrentlySelectedComponents();
	ValueTree getValueTreeForComponent(String compName);
	Component* getComponentFromName(String name);
	void addToEditorAndMakeVisible(Component* comp, ValueTree widgetData);
	void updateLayoutEditorFrames();
	void componentMovedOrResized (Component &component, bool wasMoved, bool wasResized);
	//=============================================================================
	void buttonClicked(Button *button);
	void comboBoxChanged (ComboBox* combo);
	
    CabbageAudioParameter* getParameterForComponent (Component* button);	
	
	ComponentLayoutEditor& getLayoutEditor()
	{
		return layoutEditor;
	}
	
	bool inGUIEditMode()
	{
		return isGUIEnabled;
	}
	
	Colour backgroundColour;
private:
	bool isGUIEnabled=false;
    CabbagePluginProcessor& processor;
	ComponentLayoutEditor layoutEditor;			
	StringArray currentlySelectedComponentNames;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CabbagePluginEditor)
};


#endif  // CABBAGEPLUGINEDITOR_H_INCLUDED
