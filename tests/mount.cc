#include <stdio.h>
#include <iostream>
#include "nova/Log.h"
#include "nova/VolumeManager.h"

using namespace std;
using nova::Log;
using nova::LogApiScope;
using nova::LogOptions;
using nova::VolumeManager;
using nova::VolumeDevice;


int main(int argc, char **argv)
{
    // FlagValues flags;
    LogApiScope log(LogOptions::simple());

    if (argc < 4) {
        cerr << "Usage: " << (argc > 0 ? argv[0] : "format_and_mount")
        << " device_path mount_point" << endl;
        return 1;
    }

    const string command = argv[1]
    const string device_path = argv[2];
    const string mount_point = argv[3];

    if (command == "mount") {

    } else if (command == "write_to_fstab") {

    } else {
        cerr << "Valid commands: mount, write_to_fstab" << endl;
        return 1;
    }

    const unsigned int num_tries_device_exists = 3;
    const string volume_fstype = "ext3";
    const string format_options = "-m 5";
    const unsigned int volume_format_timeout = 120;
    const string mount_options = "defaults,noatime";

    /* Create Volume Manager. */
    VolumeManager volumeManager(
        // flags.check_device_num_retries(),
        num_tries_device_exists,
        // flags.volume_file_system_type(),
        volume_fstype,
        // flags.format_options(),
        format_options,
        // flags.volume_format_timeout(),
        volume_format_timeout,
        // flags.mount_options()
        mount_options
    );

    VolumeDevice vol_device = volumeManager.create_volume_device(device_path);

    vol_device.mount(mount_point);

    NOVA_LOG_INFO("Mounted the volume.");

    return 0;
}
