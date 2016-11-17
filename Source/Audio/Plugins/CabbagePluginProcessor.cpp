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

#include "CabbagePluginProcessor.h"
#include "CabbagePluginEditor.h"


char tmp_string[4096] = {0};
char channelMessage[4096] = {0};


CabbagePluginProcessor::CabbagePluginProcessor(File inputFile)
:CsoundPluginProcessor(inputFile), 
csdFile(inputFile),
cabbageWidgets("CabbageWidgetData")
{	
	
	//initAllCsoundChannels(cabbageWidgets);
	if(inputFile.existsAsFile())
	{
		parseCsdFile();
		createParameters();
	}
	
	initAllCsoundChannels(cabbageWidgets);

}

CabbagePluginProcessor::~CabbagePluginProcessor()
{

}

//==============================================================================
void CabbagePluginProcessor::parseCsdFile()
{
	StringArray linesFromCsd;
	linesFromCsd.addLines(csdFile.loadFileAsString());
	String parentComponent, previousComponent;
	bool withinPlantGroup = false;
	for( int lineNumber = 0; lineNumber < linesFromCsd.size() ; lineNumber++ )
	{
		if(linesFromCsd[lineNumber].equalsIgnoreCase("</Cabbage>"))
			return;
		
		const String widgetTreeIdentifier = "WidgetFromLine_"+String(lineNumber);
		ValueTree temp(widgetTreeIdentifier);
		CabbageWidgetData::setWidgetState(temp, linesFromCsd[lineNumber], lineNumber);
		CabbageWidgetData::setStringProp(temp, CabbageIdentifierIds::csdfile, csdFile.getFullPathName());
		
		if(linesFromCsd[lineNumber].contains("}"))
		{
			parentComponent = "";
		}	
		
		if(parentComponent.isNotEmpty())
			CabbageWidgetData::setStringProp(temp, CabbageIdentifierIds::parentcomponent, parentComponent);
			
		if(CabbageWidgetData::getProperty(temp, CabbageIdentifierIds::basetype).toString()=="interactive" ||
			CabbageWidgetData::getProperty(temp, CabbageIdentifierIds::basetype).toString()=="layout" )
		{
			CabbageUtilities::debug(CabbageWidgetData::getStringProp(temp, CabbageIdentifierIds::channel));
			cabbageWidgets.addChild(temp, -1, 0);
		}
		
		if(linesFromCsd[lineNumber].contains("{"))
		{
			if(linesFromCsd[lineNumber].removeCharacters(" ")=="{")
			{
				parentComponent = previousComponent;
			}
			else
			{ 
				parentComponent = CabbageWidgetData::getProperty(temp, CabbageIdentifierIds::name).toString();
				CabbageWidgetData::setProperty(temp, "containsOpeningCurlyBracket", 1);
			}
		}
		
		previousComponent = CabbageWidgetData::getProperty(temp, CabbageIdentifierIds::name).toString();	
	}
}

//==============================================================================
// create parameters for sliders, buttons, comboboxes, checkboxes, encoders and xypads. 
// Other widgets can communicate with Csound, but they cannot be automated

void CabbagePluginProcessor::createParameters()	
{
	for(int i = 0; i < cabbageWidgets.getNumChildren(); i++)
	{
		const String typeOfWidget = CabbageWidgetData::getStringProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::type);
		CabbageControlWidgetStrings controlWidgetTypes;
		if(controlWidgetTypes.contains(typeOfWidget))
		{
			const String name = CabbageWidgetData::getStringProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::name);
			const String channel = CabbageWidgetData::getStringProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::channel);
			const int value = CabbageWidgetData::getNumProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::value);
			
			if(typeOfWidget==CabbageIdentifierIds::checkbox)
				addParameter(new CabbageAudioParameter(*getCsound(), channel, name, 0, 1, value));	
			else if(typeOfWidget==CabbageIdentifierIds::combobox)
			{
				addParameter(new CabbageAudioParameter(*getCsound(), channel, name, 0, 1, value));
			}
		}
	}	
}

//==============================================================================
bool CabbagePluginProcessor::hasEditor() const	
{
    return true; 
}

AudioProcessorEditor* CabbagePluginProcessor::createEditor()
{
    return new CabbagePluginEditor(*this);
}

//==============================================================================
void CabbagePluginProcessor::receiveChannelDataFromCsound()
{
	for( int i = 0; i < cabbageWidgets.getNumChildren(); i++)
	{
		const String channel = CabbageWidgetData::getStringProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::channel);
		const float value = CabbageWidgetData::getNumProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::value);
		const String identChannel = CabbageWidgetData::getStringProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::identchannel);
		const String identChannelMessage = CabbageWidgetData::getStringProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::identchannelmessage);
		
		//infinite loop here with comboxes, NOT AGAIN!!! Bloody eck. Same shite as last time. 
		if(getCsound()->GetChannel(channel.toUTF8())!=value)
			CabbageWidgetData::setNumProp(cabbageWidgets.getChild(i), CabbageIdentifierIds::value, getCsound()->GetChannel(channel.toUTF8()));			
		
		if(identChannel.isNotEmpty())
		{	
			getCsound()->GetStringChannel(identChannel.toUTF8(), tmp_string);
			if(String(tmp_string)!=identChannelMessage)
			{
				CabbageWidgetData::setCustomWidgetState(cabbageWidgets.getChild(i), " "+String(tmp_string));
			}	
		}
				
	}
}

