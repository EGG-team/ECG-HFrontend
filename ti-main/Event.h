// Include application, user and local libraries
#include <Energia.h>
#include <xdc/runtime/Error.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/BIOS.h>

#ifndef Event_h
#define Event_h

class Event
{
private:
    Event_Handle EventHandle;
    static xdc_UInt EventId;
    
public:
    Event();
    
    void begin();
    
    void send(xdc_UInt eventId_number = Event_Id_00);
    
    uint32_t waitFor(xdc_UInt andMask = Event_Id_00, xdc_UInt orMask  = Event_Id_NONE);
};

#endif
