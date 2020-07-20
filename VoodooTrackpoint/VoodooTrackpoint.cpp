/*
 * VoodooTrackpoint.cpp
 * VoodooTrackpoint
 *
 * Copyright (c) 2020 Leonard Kleinhans <leo-labs>
 *
 */

#include "VoodooTrackpoint.hpp"

OSDefineMetaClassAndStructors(VoodooTrackpoint, IOService)

#define super IOService


bool VoodooTrackpoint::start(IOService *provider) {
    if (!super::start(provider)) {
        return false;
    }
    
    setProperty(VOODOO_TRACKPOINT_IDENTIFIER, kOSBooleanTrue);
    
    if (!provider->open(this)) {
        return false;
    }
    
    return publishTrackpoint();
}

bool VoodooTrackpoint::willTerminate(IOService *provider, IOOptionBits options) {
    if (provider->isOpen(this)) {
        provider->close(this);
    }
    
    return super::willTerminate(provider, options);
}

void VoodooTrackpoint::stop(IOService *provider) {
    unpublishTrackpoint();
    OSSafeReleaseNULL(trackpoint);
    super::stop(provider);
}

bool VoodooTrackpoint::publishTrackpoint() {
    trackpoint = OSTypeAlloc(TrackpointDevice);
    if (!trackpoint) {
        IOLogError("No memory to allocate TrackpointDevice instance\n");
        goto trackpoint_exit;
    }
    if (!trackpoint->init(NULL)) {
        IOLogError("Failed to init TrackpointDevice\n");
        goto trackpoint_exit;
    }
    if (!trackpoint->attach(this)) {
        IOLogError("Failed to attach TrackpointDevice\n");
        goto trackpoint_exit;
    }
    if (!trackpoint->start(this)) {
        IOLogError("Failed to start TrackpointDevice \n");
        goto trackpoint_exit;
    }
    
    trackpoint->registerService();
    return true;
trackpoint_exit:
    unpublishTrackpoint();
    return false;
}

void VoodooTrackpoint::unpublishTrackpoint() {
    if (trackpoint) {
        trackpoint->stop(this);
    }
}

IOReturn VoodooTrackpoint::message(UInt32 type, IOService* provider, void* argument) {
    switch (type) {
        case kIOMessageVoodooTrackpointRelativePointer: {
            if(trackpoint) {
                const RelativePointerEvent& event = *(RelativePointerEvent*)argument;
                trackpoint->updateRelativePointer(event.dx, event.dy, event.buttons, event.timestamp);
            }
            break;
        }
        case kIOMessageVoodooTrackpointScrollWheel: {
            if(trackpoint) {
                const ScrollWheelEvent& event = *(ScrollWheelEvent*)argument;
                trackpoint->updateScrollwheel(event.deltaAxis1, event.deltaAxis2, event.deltaAxis3, event.timestamp);
            }
            break;
        }
    }
    
    return kIOReturnSuccess;
}
