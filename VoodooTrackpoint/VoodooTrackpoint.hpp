/*
 * VoodooTrackpoint.hpp
 * VoodooTrackpoint
 *
 * Copyright (c) 2020 Leonard Kleinhans <leo-labs>
 *
 */

#ifndef VoodooTrackpoint_hpp
#define VoodooTrackpoint_hpp

#include <IOKit/IOService.h>
#include "helpers.hpp"
#include "TrackpointDevice.hpp"
#include "VoodooTrackpointMessages.h"

class VoodooTrackpoint : public IOService {
    OSDeclareDefaultStructors(VoodooTrackpoint)
public:
    virtual bool start(IOService *provider) override;
    virtual void stop(IOService *provider) override;
    bool willTerminate(IOService *provider, IOOptionBits options) override;
    
    
private:
    TrackpointDevice *trackpoint;
    
    void unpublishTrackpoint();
    bool publishTrackpoint();
    
    virtual IOReturn message(UInt32 type, IOService* provider, void* argument) override;
};

#endif /* VoodooTrackpoint_hpp */
