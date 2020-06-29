/*
 * VoodooTrackpointMessages.h
 * VoodooTrackpoint
 *
 * Copyright (c) 2020 Leonard Kleinhans <leo-labs>
 *
 */

#ifndef VoodooTrackpointMessages_h
#define VoodooTrackpointMessages_h

#define kIOMessageVoodooTrackpointRelativePointer iokit_vendor_specific_msg(430)
#define kIOMessageVoodooTrackpointScrollWheel iokit_vendor_specific_msg(431)

struct RelativePointerEvent {
    uint64_t timestamp;
    int dx;
    int dy;
    int buttons;
};

struct ScrollWheelEvent {
    uint64_t timestamp;
    short deltaAxis1;
    short deltaAxis2;
    short deltaAxis3;
};

#endif /* VoodooTrackpointMessages_h */
