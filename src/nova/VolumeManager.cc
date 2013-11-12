#include "nova/Log.h"
#include "nova/process.h"
#include "nova/VolumeManager.h"
#include <boost/assign/list_of.hpp>
#include <string>

using std::string;
using namespace boost::assign;
namespace proc = nova::process;

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

        void mount() {
            NOVA_LOG_INFO("Check mount point exists...")

            NOVA_LOG_INFO("Mounting Volume...")
            proc::CommandList cmds = list_of("/usr/bin/sudo")
                                            ("mount")
                                            ("-t")
                                            // (volume_fstype.c_str())
                                            ("-o")
                                            // (mount_options.c_str())
                                            (device_path.c_str())
                                            (mount_point.c_str());
            proc::Process<proc::StdErrAndStdOut> process(cmds);
            // TODO (joe.cruz) expect EOF
            // TODO (joe.cruz) create/add exception
        }

        void write_to_fstab() {
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
    format_device();
    check_format();
}

void VolumeDevice::mount(const std::string mount_point) {
    VolumeMountPoint volume_mount_point(device_path, mount_point);
    volume_mount_point.mount();
    volume_mount_point.write_to_fstab();
}

void VolumeDevice::check_device_exists() {
    // TODO (joe.cruz) add retries
    NOVA_LOG_INFO("Checking if device exists...");
    try{
        proc::execute(list_of("/usr/bin/sudo")
                             ("blockdev")
                             (device_path.c_str()));
    }
    catch (proc::ProcessException &e) {
        NOVA_LOG_ERROR("Checking if device exists FAILED!!!");
        // TODO (joe.cruz) create/add exception
        // throw VolumeDeviceException(VolumeDeviceException::VOLUME_DEVICE_DOES_NOT_EXIST)
    }
}

void VolumeDevice::format_device() {
    NOVA_LOG_INFO("Formatting device...");
    proc::CommandList cmds = list_of("/usr/bin/sudo")
                                    ("mkfs")("-t")
                                    // (volume_fstype.c_str())
                                    // (format_options.c_str())
                                    (device_path.c_str());
    proc::Process<proc::StdErrAndStdOut> process(cmds);
    // TODO (joe.cruz) expect EOF
    // TODO (joe.cruz) create/add exception
}

void VolumeDevice::check_format() {
   NOVA_LOG_INFO("Checking device format...");
    proc::CommandList cmds = list_of("/usr/bin/sudo")
                                    ("dumpe2fs")
                                    (device_path.c_str());
    proc::Process<proc::StdErrAndStdOut> process(cmds);
    // TODO (joe.cruz) expect patterns "has_journal", "Wrong magic number"
    // TODO (joe.cruz) create/add exception
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
