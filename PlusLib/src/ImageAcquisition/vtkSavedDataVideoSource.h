/*=Plus=header=begin======================================================
  Program: Plus
  Copyright (c) Laboratory for Percutaneous Surgery. All rights reserved.
  See License.txt for details.
=========================================================Plus=header=end*/

#ifndef __vtkSavedDataVideoSource_h
#define __vtkSavedDataVideoSource_h

#include "vtkPlusVideoSource.h"

class vtkVideoBuffer; 

class VTK_EXPORT vtkSavedDataVideoSource;

/*!
  \class vtkSavedDataVideoSource 
  \brief Class for providing VTK video input interface from sequence metafile
  \ingroup PlusLibImageAcquisition
*/
class VTK_EXPORT vtkSavedDataVideoSource : public vtkPlusVideoSource
{
public:
	vtkTypeRevisionMacro(vtkSavedDataVideoSource,vtkPlusVideoSource);
	void PrintSelf(ostream& os, vtkIndent indent);   
	static vtkSavedDataVideoSource* New();

  /*! Read configuration from xml data */
	virtual PlusStatus ReadConfiguration(vtkXMLDataElement* config); 
  /*! Write configuration to xml data */
	virtual PlusStatus WriteConfiguration(vtkXMLDataElement* config);

  /*! Set SequenceMetafile name with path with tracking buffer data  */
	vtkSetStringMacro(SequenceMetafile);
  /*! Get SequenceMetafile name with path with tracking buffer data  */
	vtkGetStringMacro(SequenceMetafile);

  /*! Set loop start time /sa LoopStartTime */
	vtkSetMacro(LoopStartTime, double); 
  /*! Get loop start time /sa LoopStartTime */
	vtkGetMacro(LoopStartTime, double); 

  /*! Set loop time /sa LoopTime */
	vtkSetMacro(LoopTime, double); 
  /*! Get loop time /sa LoopTime */
	vtkGetMacro(LoopTime, double); 

	/*! Set flag to to enable saved dataset reply /sa RepeatEnabled */
	vtkGetMacro(RepeatEnabled, bool);
	/*! Get flag to to enable saved dataset reply /sa RepeatEnabled */
	vtkSetMacro(RepeatEnabled, bool);
	vtkBooleanMacro(RepeatEnabled, bool);

  /*! Get local video buffer */
  vtkGetObjectMacro(LocalVideoBuffer, vtkVideoBuffer); 
	
protected:
	/*! Constructor */
	vtkSavedDataVideoSource();
	/*! Destructor */
	virtual ~vtkSavedDataVideoSource();

  /*! Connect to device */
	virtual PlusStatus InternalConnect();

  /*! Disconnect from device */
	virtual PlusStatus InternalDisconnect();

  /*! The internal function which actually does the grab.  */
	PlusStatus InternalGrab();

protected:
	/*! Byte alignment of each row in the framebuffer */
	int FrameBufferRowAlignment;

  /*! Name of input sequence metafile */
	char* SequenceMetafile;

	/*! Flag to to enable saved dataset looping. If it's enabled, the video source will continuously play saved data (starts playing from the beginning when the end is reached). */
	bool RepeatEnabled; 

  /*! Loop start time
      ItemTimestamp = loopStartTime + (actualTimestamp - startTimestamp) % loopTime 
  */
  double LoopStartTime; 

  /*! Loop time
      ItemTimestamp = loopStartTime + (actualTimestamp - startTimestamp) % loopTime 
  */
  double LoopTime; 

  /*! Local video buffer */
	vtkVideoBuffer* LocalVideoBuffer; 

  /*! Read all the frame fields from the file and provide them in the output */
  bool UseAllFrameFields;
  
  /*! Read the timestamps from the file and use provide them in the output (instead of the current time) */
  bool UseOriginalTimestamps;

  /*! Time of the last added frame (in the local buffer time coordinate frame) */
  double LastAddedFrameTimestamp;

  /*! Index of the loop when the last frame was added. Used for making sure we add each frame only once in one loop period. */
  int LastAddedFrameLoopIndex;

private:
	static vtkSavedDataVideoSource* Instance;
	vtkSavedDataVideoSource(const vtkSavedDataVideoSource&);  // Not implemented.
	void operator=(const vtkSavedDataVideoSource&);  // Not implemented.
};

#endif

