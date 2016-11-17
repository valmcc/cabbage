/*
  ==============================================================================

    ComponentLayoutEditor.h
    Created: 26 Oct 2016 9:18:16pm
    Author:  rory

  ==============================================================================
*/

#ifndef COMPONENTLAYOUTEDITOR_H_INCLUDED
#define COMPONENTLAYOUTEDITOR_H_INCLUDED


/*
 *  ComponentLayoutEditor.h
 *  
 *  Original written by Haydxn
 *  Modified by Jordan Hochenbaum on 10/25/10.
 *  http://www.rawmaterialsoftware.com/viewtopic.php?f=6&t=2635
 *
 */

#include "../CabbageCommonHeaders.h"

class ChildAlias;
class CabbagePluginEditor;
class ComponentLayoutEditor;
//=============================================================================
class SelectedComponents   : public SelectedItemSet<ChildAlias*>
{
public:
    void itemSelected (ChildAlias* item);
    void itemDeselected (ChildAlias* item);
};

//=============================================================================
class ChildAlias   :   public Component
{
    public:
		ChildAlias (Component* targetChild, ComponentLayoutEditor* layoutEditor);
		~ChildAlias ();
		void resized ();
		void paint (Graphics& g);
		const Component* getTargetChild ();
		void updateFromTarget ();
		void applyToTarget ();
		virtual void userChangedBounds ();
		virtual void userStartedChangingBounds (){};
		virtual void userStoppedChangingBounds (){};
		bool boundsChangedSinceStart ();
		void mouseEnter (const MouseEvent& e);
		void mouseExit (const MouseEvent& e);
		void mouseDown (const MouseEvent& e);
		void mouseUp (const MouseEvent& e);
		void mouseDrag (const MouseEvent& e);
		
		void setInterest(String isInteresting)
		{
			interest = isInteresting;
		}
		
		CabbagePluginEditor* getPluginEditor();		
		void updateBoundsDataForTarget();
		void setBoundsForChildren();
		bool mouseDownSelectStatus = false;
		
		const Component* getTarget()
		{
			return target;
		}
		
    private:
		CriticalSection bounds;
		ScopedPointer<ComponentBoundsConstrainer>  constrainer;
    	ComponentDragger dragger;
		SafePointer<Component> target;
		Array<juce::Rectangle<int> > childBounds;
		String interest;
		bool userAdjusting;
		Rectangle<int> startBounds;
		ScopedPointer<ComponentBoundsConstrainer> resizeContainer; 
		ResizableBorderComponent* resizer;
		ComponentLayoutEditor* layoutEditor;

};
//=============================================================================
class ComponentLayoutEditor   :   public Component, public LassoSource <ChildAlias*>
{
    public:
		ComponentLayoutEditor (ValueTree valueTree);
		~ComponentLayoutEditor ();
		
		ValueTree widgetData;
		void resized ();
		void paint (Graphics& g);
		void setTargetComponent (Component* target);
		void bindWithTarget ();
		void updateFrames ();
    	void enablementChanged ();
		void mouseUp(const MouseEvent& e);
		void mouseDrag(const MouseEvent& e);
		void mouseDown(const MouseEvent& e);
		const Component* getTarget();
		void findLassoItemsInArea (Array <ChildAlias*>& results, const juce::Rectangle<int>& area);
		void updateCodeEditor();
		void updateSelectedComponentBounds();
		void setComponentBoundsProperties(Component* child, Rectangle<int> bounds);

		SelectedItemSet <ChildAlias*>& getLassoSelection();
	    LassoComponent <ChildAlias*> lassoComp;
		SelectedComponents selectedComponents;	
		Point<int> currentMouseCoors;
		void resetAllInterest();
		CabbagePluginEditor* getPluginEditor();
	
	private:	
		virtual ChildAlias* createAlias (Component* child);		
		SafePointer<Component> target;
		OwnedArray<ChildAlias> frames;

	
};


#endif  // COMPONENTLAYOUTEDITOR_H_INCLUDED
