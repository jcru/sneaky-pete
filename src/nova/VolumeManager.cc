#include "nova/Log.h"
#include "nova/process.h"
#include "nova/VolumeManager.h"
#include <boost/assign/list_of.hpp>
#include <string>

using std::string;
using namespace boost::assign;
namespace process = nova::process;

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
    check_device_exists();
}

void VolumeDevice::mount(const std::string mount_point) {

}

void VolumeDevice::check_device_exists() {
    // TODO (joe.cruz) add retries
    NOVA_LOG_INFO("Checking if device exists...");
    try{
        process::execute(list_of("/usr/bin/sudo")
                                ("blockdev")
                                (device_path.c_str()));
    }
    catch (process::ProcessException &e) {
        NOVA_LOG_ERROR("Checking if device exists FAILED!!!");
        // TODO (joe.cruz) create/add exception
        // throw VolumeDeviceException(VolumeDeviceException::VOLUME_DEVICE_DOES_NOT_EXIST)
    }
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
