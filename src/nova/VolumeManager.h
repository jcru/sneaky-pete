#ifndef __NOVA_VOLUME_MANAGER_H
#define __NOVA_VOLUME_MANAGER_H

#include <string>
#include <boost/utility.hpp>


namespace nova {

// struct FormatInfo {
//     FormatInfo();
//     int num_tries_device_exists;
//     std::string volume_fstype;
//     std::string format_options;
//     int volume_format_timeout;
// };

// typedef boost::shared_ptr<FormatInfo> FormatInfoPtr;

// struct MountInfo {
//     MountInfo();
//     std::string device_path;
//     std::string mount_point;
//     std::string volume_fstype;
//     std::string mount_options;
// };

// typedef boost::shared_ptr<MountInfo> MountInfoPtr;

class VolumeDevice {
public:
    VolumeDevice(const std::string device_path,
                 const unsigned int num_tries_device_exists,
                 const std::string volume_fstype,
                 const std::string format_options,
                 const unsigned int volume_format_timeout,
                 const std::string mount_options);

    ~VolumeDevice();

    void format();

    void mount(const std::string mount_point);


private:

    const std::string device_path;
    // The rest of these are exactly the same from VolumeManager
    // Should be better (pattern) way of doing this
    const unsigned int num_tries_device_exists;
    const std::string volume_fstype;
    const std::string format_options;
    const unsigned int volume_format_timeout;
    const std::string mount_options;

    /** Check that the device path exists.
     * Verify that the device path has actually been created and can report
     * it's size, only then can it be available for formatting, retry
     * num_tries_device_exists to account for the time lag.  **/
    void check_device_exists();

    /** Calls mkfs to format the device at device_path.  **/
    void format_device();

    /** Checks that an unmounted volume is formatted.  **/
    void check_format();

};

class VolumeManager : boost::noncopyable  {
public:
    VolumeManager(const unsigned int num_tries_device_exists,
                  const std::string & volume_fstype,
                  const std::string & format_options,
                  const unsigned int volume_format_timeout,
                  const std::string & mount_options);

    ~VolumeManager();

    VolumeDevice create_volume_device(const std::string device_path);


private:

    const unsigned int num_tries_device_exists;
    const std::string volume_fstype;
    const std::string format_options;
    const unsigned int volume_format_timeout;
    const std::string mount_options;
};

typedef boost::shared_ptr<VolumeManager> VolumeManagerPtr;

class VolumeException : public std::exception {

    public:
        enum Code {
            DEVICE_DOES_NOT_EXIST,
            FORMAT_DEVICE_FAILURE,
            CHECK_FORMAT_FAILURE,
            MOUNT_FAILURE,
            WRITE_TO_FSTAB_FAILURE
        };

        VolumeException(Code code) throw();

        virtual ~VolumeException() throw();

        const Code code;

        virtual const char * what() const throw();
};

} // end namespace nova

#endif // __NOVA_VOLUME_MANAGER_H
