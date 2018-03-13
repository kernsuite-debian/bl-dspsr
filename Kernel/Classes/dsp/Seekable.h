//-*-C++-*-
/***************************************************************************
 *
 *   Copyright (C) 2002 by Willem van Straten
 *   Licensed under the Academic Free License version 2.1
 *
 ***************************************************************************/

/* $Source: /cvsroot/dspsr/dspsr/Kernel/Classes/dsp/Seekable.h,v $
   $Revision: 1.15 $
   $Date: 2010/06/04 03:36:31 $
   $Author: straten $ */


#ifndef __Seekable_h
#define __Seekable_h

#include "dsp/Input.h"

namespace dsp {

  //! Pure virtual base class of sources that can seek through data
  /*! 
    This class defines the common interface as well as some basic
    functionality relating to sources of TimeSeries data that can seek
  */
  class Seekable : public Input 
  {
    
  public:
    
    //! Constructor
    Seekable (const char* name);
    
    //! Destructor
    virtual ~Seekable ();
    
    //! End of data
    virtual bool eod();
    
    //! Rewind to the start of the data
    virtual void rewind ();

    //! Inquire current time sample
    virtual uint64_t get_current_sample() { return current_sample; }

    //! Buffer used to store overlap (useful in multi-threaded applications)
    void set_overlap_buffer (BitSeries*);

  protected:
    
    //! set end_of_data
    virtual void set_eod(bool _eod){ end_of_data = _eod; }

    //! Load next block of data into BitSeries
    virtual void load_data (BitSeries* data);
 
    //! Load data from device and return the number of bytes read.
    virtual int64_t load_bytes (unsigned char* buffer, uint64_t bytes) = 0;
    
    //! Seek to absolute position and return absolute position in bytes
    virtual int64_t seek_bytes (uint64_t bytes) = 0;
    
    //! Conserve access to resources by re-using data already in BitSeries
    virtual uint64_t recycle_data (BitSeries* data);

    //! end of data reached
    bool end_of_data;
    
    //! Current time sample
    uint64_t current_sample;

    //! Buffer used to store overlap
    Reference::To<BitSeries> overlap_buffer;

    //! initialize variables
    void init();
  };

}

#endif // !defined(__Seekable_h)
