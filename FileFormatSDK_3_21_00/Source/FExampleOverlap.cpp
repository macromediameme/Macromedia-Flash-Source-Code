// Copyright � 1999 Middlesoft, Inc. All rights reserved.
// First Created By Bate Yu
// First Created On 10/13/1999.
// Last Modified On 11/09/1999.

/****************************************************************************************

				File Summary: FExampleOverlap.cpp

   Creates a one frame movie with containing a single defineShape data tag block, which 
   has two squares:
   
	1) blue one over red one, both have a standard 1 pixel wide, black edge.
	2) but the display is always red over blue, independent of drawing order.

****************************************************************************************/

#include "F3SDK.h"
#include "FExample.h"

void CreateOverlapMovie(){

	//Create a collection of FObj's, allTags, to contain the FObjs that make the movie
	//Each SWF tag in the movie will be represented by an FObj
	FObjCollection allTags;


// Construct first flash tag object (set background color):

	//define a color for the background
	const FColor white(0xff, 0xff, 0xff);

	//construct the SetBackgroundColor object which takes a color as an argument
	//All routines beginning with FCT create Flash Control Tags
	FCTSetBackgroundColor* background = new FCTSetBackgroundColor( new FColor( white ) );

	//add the SetBackgroundColor tag to allTags
	allTags.AddFObj(background);


	
	//construct a rect that defines the shape's bounds 
	FRect* rectBounds = new FRect(2000, 2000, 5000, 5000);  //coordinate values are in TWIPS

	//construct the FDTDefineShape which will be the rectangle image
	FDTDefineShape* rectangle = new FDTDefineShape(rectBounds);

	//record its ID so that we can later refer to it
	U16 rectangleID = rectangle->ID();

	//construct a red and a blue FColor
	FColor red = FColor(0xff, 0, 0);
	FColor blue = FColor(0, 0, 0xff);
	
	//construct a solid fill style of the given color
	//add the fill style to the rectangle
	//you must record the position of the fill style in the fill style array 
	//so that you can later refer to it.  The AddFillStyle function of fillStyle 
	//array returns the position so record that in a field called fillID
	U32 bluefillID = rectangle->AddSolidFillStyle(new FColor( blue));
    U32 redfillID = rectangle->AddSolidFillStyle(new FColor( red));

	//construct a black color
	FColor black = FColor(0, 0, 0);

	//add a black, 1 pixel (20 TWIPS) wide line style to rectangle, remembering to store the
	// position of the line style just as in the fill style.
	U32 blackLineStyleID = rectangle->AddLineStyle(20, new FColor( black ) );

	//Since you are done creating fill and line styles, indicate so
	rectangle->FinishStyleArrays();

	//construct the shape records which will describe the rectangle
	//there are FShapeRecChange, FShapeRecEdge, and FShapeRecEnd shapes
	FShapeRec* rectangleShapeRecords[11];
	rectangleShapeRecords[0] = new FShapeRecChange(false, true, true, false, true, 4000, 2000,
													0, redfillID, blackLineStyleID, 0, 0);
	//Create straight edge object (just a stuct of info), store it in EdgeRecord
	rectangleShapeRecords[1] = new FShapeRecEdgeStraight( 0, 2000);
	rectangleShapeRecords[2] = new FShapeRecEdgeStraight( -2000, 0);
	rectangleShapeRecords[3] = new FShapeRecEdgeStraight( 0, -2000);
	rectangleShapeRecords[4] = new FShapeRecEdgeStraight( 2000, 0);

	// Now change the fill color to blue.
	rectangleShapeRecords[5] = new FShapeRecChange(false, false, true, false, true, 5000, 3000, 
												   0, bluefillID, 0, 0, 0);
	rectangleShapeRecords[6] = new FShapeRecEdgeStraight( 0, 2000);
	rectangleShapeRecords[7] = new FShapeRecEdgeStraight( -2000, 0);
	rectangleShapeRecords[8] = new FShapeRecEdgeStraight( 0, -2000);
	rectangleShapeRecords[9] = new FShapeRecEdgeStraight( 2000, 0);

	rectangleShapeRecords[10] = new FShapeRecEnd();

	
	//Add the shape records to the rectangle shape object
	for (int i = 0;  i < 11 ;  i++)
		rectangle->AddShapeRec(rectangleShapeRecords[i]);

	//Add the rectangle to the given object collection
	allTags.AddFObj(rectangle);

	//create a place object tag which puts the rectangle on the display list
	FCTPlaceObject2 *placeRectangle = new FCTPlaceObject2(false, // ~ _hasClipDepth
														  false, true, false, 
														  1, rectangleID, 0, 0, 0, 0, 0/**/);

	//add the place object tag to the FObjCollection
	allTags.AddFObj(placeRectangle);

	//construct a show frame object
	FCTShowFrame *showFrame = new FCTShowFrame();

	//add the show frame object to the FObj collection;
	allTags.AddFObj(showFrame);

	//now create the movie
	allTags.CreateMovie("FExampleOverlap.swf", 11000, 8000, 12);

}