//  Copyright (c) 2007-2009 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_HPX_FWD_MAR_24_2008_1119AM)
#define HPX_HPX_FWD_MAR_24_2008_1119AM

#include <boost/config.hpp>
#if defined(BOOST_WINDOWS)
#include <winsock2.h>
#include <excpt.h>
#endif

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/cstdint.hpp>
#include <boost/coroutine/coroutine.hpp>
#include <hpx/config.hpp>
#include <hpx/util/unused.hpp>

/// \namespace hpx
///
/// The namespace \a hpx is the main namespace of the HPX library. All classes
/// functions and variables are defined inside this namespace.
namespace hpx
{
    /// \namespace applier
    ///
    /// The namespace \a applier contains all definitions needed for the
    /// class \a hpx#applier#applier and its related functionality. This 
    /// namespace is part of the HPX core module.
    namespace applier
    {
        class HPX_API_EXPORT applier;

        /// The function \a get_applier returns a reference to the (thread
        /// specific) applier instance.
        HPX_API_EXPORT applier& get_applier();
        HPX_API_EXPORT applier* get_applier_ptr();

        /// The function \a get_prefix_id returns the id of this locality
        HPX_API_EXPORT boost::uint32_t get_prefix_id();
    }

    /// \namespace actions
    ///
    /// The namespace \a actions contains all definitions needed for the
    /// class \a hpx#action_manager#action_manager and its related 
    /// functionality. This namespace is part of the HPX core module.
    namespace actions
    {
        struct HPX_API_EXPORT base_action;
        typedef boost::shared_ptr<base_action> action_type;

        class HPX_API_EXPORT continuation;
        typedef boost::shared_ptr<continuation> continuation_type;

        class HPX_API_EXPORT action_manager;
    }

    /// \namespace naming
    ///
    /// The namespace \a naming contains all definitions needed for the AGAS
    /// (Distributed Global Address Space) service.
    namespace naming
    {
        struct HPX_API_EXPORT id_type;
        struct HPX_API_EXPORT address;
        class HPX_API_EXPORT locality;
        class HPX_API_EXPORT resolver_client;
        class HPX_API_EXPORT resolver_server;

        namespace server
        {
            class reply;
            class request;
        }
    }

    /// \namespace parcelset
    namespace parcelset
    {
        class HPX_API_EXPORT parcel;
        class HPX_API_EXPORT parcelport;
        class parcelport_connection;
        class connection_cache;
        class HPX_API_EXPORT parcelhandler;
        
        namespace server
        {
            class parcelport_queue;
            class parcelport_server_connection;
            class parcelhandler_queue;
        }
    }

    /// \namespace threads
    ///
    /// The namespace \a threadmanager contains all the definitions required 
    /// for the scheduling, execution and general management of \a 
    /// hpx#threadmanager#thread's.
    namespace threads
    {
        namespace policies
        {
            class HPX_API_EXPORT global_queue_scheduler;
            class HPX_API_EXPORT local_queue_scheduler;
            class HPX_API_EXPORT callback_notifier;

            // define the default scheduler to use
            typedef local_queue_scheduler queue_scheduler;
        }

        struct HPX_API_EXPORT threadmanager_base;
        class HPX_API_EXPORT thread;

        template <
            typename SchedulingPolicy, 
            typename NotificationPolicy = threads::policies::callback_notifier> 
        class HPX_API_EXPORT threadmanager_impl;

        ///////////////////////////////////////////////////////////////////////
        /// \enum thread_state
        ///
        /// The thread_state enumerator encodes the current state of a \a 
        /// thread instance
        enum thread_state
        {
            unknown = -1,
            init = 0,       ///< thread is initializing
            active = 1,     ///< thread is currently active (running,
                            ///< has resources)
            pending = 2,    ///< thread is pending (ready to run, but 
                            ///< no hardware resource available)
            suspended = 3,  ///< thread has been suspended (waiting for 
                            ///< synchronization event, but still known 
                            ///< and under control of the threadmanager)
            marked_for_suspension = 4,  ///< synchronization support: allows
                            ///< to mark a thread as being suspended while it's
                            ///< still active
            depleted = 5,   ///< thread has been depleted (deeply 
                            ///< suspended, it is not known to the thread 
                            ///< manager)
            terminated = 6  ///< thread has been stopped an may be garbage 
                            ///< collected

        };
        HPX_API_EXPORT char const* const get_thread_state_name(thread_state state);

        ///////////////////////////////////////////////////////////////////////
        /// \enum thread_state_ex
        ///
        enum thread_state_ex
        {
            wait_unknown = -1,
            wait_signaled = 0,  ///< The thread has been signaled
            wait_timeout = 1,   ///< The thread has been reactivated after a timeout
        };

        typedef thread_state thread_function_type(thread_state_ex);

        ///////////////////////////////////////////////////////////////////////
        typedef boost::coroutines::static_coroutine<
                thread_function_type, boost::function<thread_function_type> 
        > coroutine_type;
        typedef coroutine_type::thread_id_type thread_id_type;
        typedef coroutine_type::self thread_self;

        /// The function \a get_self returns a reference to the (OS thread 
        /// specific) self reference to the current PX thread.
        HPX_API_EXPORT thread_self& get_self();

        /// The function \a get_self returns a pointer to the (OS thread 
        /// specific) self reference to the current PX thread.
        HPX_API_EXPORT thread_self* get_self_ptr();

        /// The function \a get_self_id returns the PX thread id of the current
        /// thread (or zero if the current thread is not a PX thread).
        HPX_API_EXPORT thread_id_type get_self_id();

        /// The function \a get_parent_id returns the PX thread id of the 
        /// currents thread parent (or zero if the current thread is not a 
        /// PX thread).
        HPX_API_EXPORT thread_id_type get_parent_id();

        /// The function \a get_parent_prefix returns the id of the locality of
        /// the currents thread parent (or zero if the current thread is not a 
        /// PX thread).
        HPX_API_EXPORT boost::uint32_t get_parent_prefix();

        /// The function \a get_self_component_id returns the lva of the 
        /// component the current thread is acting on
        HPX_API_EXPORT boost::uint64_t get_self_component_id();

    }

    class HPX_API_EXPORT runtime;

    template <
        typename SchedulingPolicy, 
        typename NotificationPolicy = threads::policies::callback_notifier> 
    class HPX_API_EXPORT runtime_impl;

    /// The function \a get_runtime returns a reference to the (thread
    /// specific) runtime instance.
    HPX_API_EXPORT runtime& get_runtime();
    HPX_API_EXPORT runtime* get_runtime_ptr();

    /// Register a function to be called during system shutdown
    HPX_API_EXPORT bool register_on_exit(boost::function<void()>);

    /// \namespace components
    namespace components
    {
        namespace detail 
        { 
            struct this_type {};
            struct simple_component_tag {};
            struct managed_component_tag {};
        }

        template <typename Component> 
        class simple_component_base;

        template <typename Component, typename Derived = detail::this_type>
        class managed_component;

        struct HPX_API_EXPORT component_factory_base;

        template <typename Component> 
        struct component_factory;

        class runtime_support;
        class memory;
        class memory_block;

        namespace stubs 
        {
            struct runtime_support;
            struct memory;
            struct memory_block;
        }

        namespace server
        {
            class HPX_API_EXPORT runtime_support;
            class HPX_API_EXPORT memory;
            class HPX_API_EXPORT memory_block;
        }
    }

    /// \namespace lcos
    namespace lcos
    {
        class base_lco;
        template <typename Result> 
        class base_lco_with_value;

        template <typename Result, int N = 1> 
        class future_value;

        template <typename Action, 
            typename Result = typename Action::result_type,
            typename DirectExecute = typename Action::direct_execution> 
        class eager_future;

        template <typename Action, 
            typename Result = typename Action::result_type,
            typename DirectExecute = typename Action::direct_execution> 
        class lazy_future;
    }

    /// \namespace util
    namespace util
    {
        class HPX_API_EXPORT section;
        class runtime_configuration;
    }
}

#endif

