/*
  Copyright (C) 2007 Rory Walsh

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
#ifndef CABBPARSE_H
#define CABBPARSE_H


#include "../Utilities/CabbageUtilities.h"
#include "../CabbageIds.h"

class CabbageWidgetData : public CabbageUtilities
{
//    Array<int> tableNumbers;
//    Array<float> tableChannelValues;
//    String warningMessages;
//    bool refreshFromDisk;

public:
    CabbageWidgetData(){};
    ~CabbageWidgetData(){};
	static void setWidgetState(ValueTree widgetData, String lineFromCsd, int ID);
	static void setCustomWidgetState(ValueTree widgetData, String lineFromCsd, String identifier=String::empty);
	//============================================================================
	static void setCheckBoxProperties(ValueTree widgetData, int ID);
	static void setComboBoxProperties(ValueTree widgetData, int ID);
	static void setImageProperties(ValueTree widgetData, int ID);
	static void setFormProperties(ValueTree widgetData, int ID);
	//============================================================================
    static float getNumProp(ValueTree widgetData, Identifier prop);
    static void setNumProp(ValueTree widgetData, Identifier prop, float val);
    static void setStringProp(ValueTree widgetData, Identifier prop, String val);
    static String getStringProp(ValueTree widgetData, Identifier prop, int index=0);
	static Rectangle<int> getBounds(ValueTree widgetData);
	static void setProperty(ValueTree widgetData, Identifier name, const var &value);
	static var getProperty(ValueTree widgetData, Identifier name);
	//============================================================================
	static Colour getColourFromText(String text);
	static String getCabbageCodeFromIdentifiers(ValueTree props);
	//============================================================================
	static String getBoundsTextAsCabbageCode(Rectangle<int> rect);
	static String getMultiItemTextAsCabbageCode(ValueTree widgetData, String identifier);
	static String getColoursTextAsCabbageCode(ValueTree widgetData);
	static String getNumericalValueTextAsCabbageCode(ValueTree widgetData, String identifier);
	static String getRotateTextAsCabbageCode(ValueTree widgetData);
	static String getSimpleTextAsCabbageCode(ValueTree widgetData, String identfier);
	static String getImagesTextAsCabbageCode(ValueTree widgetData);
	//============================================================================
	static ValueTree getValueTreeForComponent(ValueTree widgetData, String name);
    void setTableChannelValues(int index, float val);
    float getTableChannelValues(int index);
    void addTableChannelValues();
    void scaleWidget(Point<float> scale);
    static Rectangle<int> getBoundsFromText(String text);
    

};

#endif
