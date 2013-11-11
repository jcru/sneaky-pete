#ifndef __NOVA_VOLUME_MANAGER_H
#define __NOVA_VOLUME_MANAGER_H

#include <string>
#include <boost/utility.hpp>


namespace nova {


class VolumeDevice {
public:
    VolumeDevice(const std::string device_path);

    ~VolumeDevice();

    void format();

    void mount(const std::string mount_point);


private:

    const std::string device_path;
    const std::string mount_point;

    /** Check that the device path exists.
     * Verify that the device path has actually been created and can report
     * it's size, only then can it be available for formatting, retry
     * num_tries to account for the time lag.  **/
    void check_device_exists();
};

class VolumeManager : boost::noncopyable  {
public:
    VolumeManager(const int num_tries,
                  const std::string volume_fstype,
                  const std::string format_options,
                  const int volume_format_timeout);

    ~VolumeManager();

    VolumeDevice create_volume_device(const std::string device_path);


private:

    const int num_tries;
    const std::string volume_fstype;
    const std::string format_options;
    const int volume_format_timeout;
};

typedef boost::shared_ptr<VolumeManager> VolumeManagerPtr;

} // end namespace nova

#endif // __NOVA_VOLUME_MANAGER_H
