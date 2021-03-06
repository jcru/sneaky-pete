#ifndef __NOVA_GUEST_MONITORING_H
#define __NOVA_GUEST_MONITORING_H

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include "nova/guest/apt.h"
#include "nova/guest/guest.h"
#include <map>
#include <vector>
#include <string>


namespace nova { namespace guest { namespace monitoring {

    class Monitoring {
        public:

            Monitoring(const std::string & guest_id,
                       const std::string & agent_package_name,
                       const std::string & agent_config_file,
                       const double agent_install_timeout);

            /* Install the monitoring agent */
            void install_and_configure_monitoring_agent(
                nova::guest::apt::AptGuest & apt,
                std::string monitoring_token,
                std::string monitoring_endpoints) const;

            /* Removes the monitoring agent from the guest */
            void remove_monitoring_agent(
                nova::guest::apt::AptGuest & apt) const;

            void start_monitoring_agent() const;

            void stop_monitoring_agent() const;

            void restart_monitoring_agent() const;

        private:

            const std::string guest_id;
            const std::string agent_package_name;
            const std::string agent_config_file;
            const double agent_install_timeout;

    };

    class MonitoringException : public std::exception {

        public:
            enum Code {
                FILE_NOT_FOUND,
                PATTERN_DOES_NOT_MATCH,
                FILESYSTEM_NOT_FOUND,
                CANT_WRITE_CONFIG_FILE,
                ERROR_STOPPING_AGENT
            };

            MonitoringException(const Code code) throw();

            virtual ~MonitoringException() throw();

            virtual const char * what() const throw();

            const Code code;

    };


    class MonitoringMessageHandler : public MessageHandler {

        public:

            MonitoringMessageHandler(nova::guest::apt::AptGuestPtr apt,
                                     Monitoring & monitoring);

            virtual nova::JsonDataPtr handle_message(const GuestInput & input);

        private:
            nova::guest::apt::AptGuestPtr apt;
            const Monitoring & monitoring;
    };

} } }  // end namespace

#endif //__NOVA_GUEST_MONITORING_H
