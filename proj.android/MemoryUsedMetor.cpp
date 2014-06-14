#include "MemoryUsedMetor.h" 
#include <sys/sysctl.h>
#import <mach/mach.h>
#import <mach/mach_host.h>

bool MemoryUsedMetor::init() {
if (!CCLabelTTF::initWithString("000.0", "Arial", 48)) {
return false;
}

scheduleUpdate();
return true;
}

MemoryUsedMetor::~MemoryUsedMetor() {
unscheduleUpdate();
}

void MemoryUsedMetor::update(float delta) {
char megaBytes[12];
sprintf(megaBytes, "%.1f MB", getAvailableMegaBytes());
setString(megaBytes);
}

double MemoryUsedMetor::getAvailableBytes() {
vm_statistics_data_t vmStats;
mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
kern_return_t kernReturn = host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmStats, &infoCount);
if (kernReturn != KERN_SUCCESS) {
return 0.0f;
}

return (vm_page_size * vmStats.free_count);
}

double MemoryUsedMetor::getAvailableKiloBytes() {
return getAvailableBytes() / 1024.0f;

}

double MemoryUsedMetor::getAvailableMegaBytes() {
return getAvailableKiloBytes() / 1024.0f;
}