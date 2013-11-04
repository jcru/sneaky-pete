#include "nova/Log.h"
#include "nova/VolumeManager.h"
#include <string>

using std::string;

namespace nova {

namespace {  // Begin anonymous namespace

/**---------------------------------------------------------------------------
 *- VolumeMountPoint
 *---------------------------------------------------------------------------*/

class VolumeMountPoint {
    public:
        VolumeMountPoint(
            const std::string device_path,
            const std::string mount_point)
        :   device_path(device_path),
            mount_point(mount_point)
        {
        }

        ~VolumeMountPoint() {
        }

    private:

        const std::string device_path;
        const std::string mount_point;
};

} // end anonymous namespace

/**---------------------------------------------------------------------------
 *- VolumeDevice
 *---------------------------------------------------------------------------*/


VolumeDevice::VolumeDevice(const string device_path)
:   device_path(device_path)
{
}

VolumeDevice::~VolumeDevice() {
}

void VolumeDevice::format() {

}

void VolumeDevice::mount(const std::string mount_point) {

}

/**---------------------------------------------------------------------------
 *- VolumeManager
 *---------------------------------------------------------------------------*/

VolumeManager::VolumeManager(
    const int num_tries,
    const std::string volume_fstype,
    const std::string format_options,
    const int volume_format_timeout)
:   num_tries(num_tries),
    volume_fstype(volume_fstype),
    format_options(format_options),
    volume_format_timeout(volume_format_timeout)
{
}

VolumeManager::~VolumeManager() {
}

VolumeDevice VolumeManager::create_volume_device(const string device_path) {
    return VolumeDevice(device_path);
}


} // end namespace nova
