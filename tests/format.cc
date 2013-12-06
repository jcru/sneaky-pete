#include <stdio.h>
#include <iostream>
// #include "nova/flags.h"
#include "nova/Log.h"
#include "nova/VolumeManager.h"

using namespace std;
// using namespace nova::flags;
using nova::Log;
using nova::LogApiScope;
using nova::LogOptions;
using nova::VolumeManager;
using nova::VolumeDevice;

// FlagMapPtr get_flags() {
//     FlagMapPtr ptr(new FlagMap());
//     char * test_args = getenv("TEST_ARGS");
//     BOOST_REQUIRE_MESSAGE(test_args != 0,
//                           "TEST_ARGS environment var not defined.");
//     if (test_args != 0) {
//         ptr->add_from_arg(test_args);
//     }
//     return ptr;
// }


int main(int argc, char **argv)
{
    // FlagValues flags;
    LogApiScope log(LogOptions::simple());

    if (argc < 3) {
        cerr << "Usage: " << (argc > 0 ? argv[0] : "format_and_mount")
        << " device_path mount_point" << endl;
        return 1;
    }

    const unsigned int num_tries_device_exists = 3;
    const string volume_fstype = "ext3";
    const string format_options = "-m 5";
    const unsigned int volume_format_timeout = 120;
    const string mount_options = "defaults,noatime";

    const string device_path = argv[1];
    // const string mount_point = argv[2];

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

    vol_device.format();

    NOVA_LOG_INFO("Mounted the volume.");

    return 0;
}
