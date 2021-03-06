/*
 * @(#)netio_configurator.h    generated by: makeheader    Mon Dec  3 23:08:05 2007
 *
 *		built from:	configurator.ifc
 */

#ifndef netio_configurator_h
#define netio_configurator_h


  #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
  #endif
  #ifndef reda_fastBuffer_h
    #include "reda/reda_fastBuffer.h"
  #endif
  #ifndef netio_dll_h
    #include "netio/netio_dll.h"
  #endif
  #ifndef transport_interface_h
    #include "transport/transport_interface.h"
  #endif
  #ifndef netio_common_h
    #include "netio/netio_common.h"
  #endif
  #ifndef transport_udpv4_h
    #include "transport/transport_udpv4.h"
  #endif
  #ifndef transport_shmem_h
    #include "transport/transport_shmem.h"
  #endif
  #ifndef transport_intra_h
    #include "transport/transport_intra.h"
  #endif
  #ifndef transport_udpv6_h
    #include "transport/transport_udpv6.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct REDAWorker;

struct REDAExclusiveArea;

struct REDAWeakReference;

struct REDADatabase;

struct RTIEventActiveObjectListener;

struct RTINetioConfiguratorListener;


struct RTINetioConfiguratorProperty {
    /*e @brief Control size of the transport plugin table. */
    struct REDAFastBufferPoolGrowthProperty pluginGrowth;

    /*e @brief Control size of the send route table. */
    struct REDAFastBufferPoolGrowthProperty sendRouteGrowth;

    /*e @brief Control size of the receive route table. */
    struct REDAFastBufferPoolGrowthProperty receiveRouteGrowth;

    /*e @brief Address separator

      This character is used to separate the network address portion from
      a transport specific address in an address string.

      @see RTINetioConfigurator_populateLocatorsFromAddressString()
     */
    char addressSeparator;

    /*e @brief Locator separator

      This character is used to separate the alias portion from
      the address portion in a locator string.

      @see RTINetioConfigurator_populateLocatorsFromLocatorString()
     */
    char locatorSeparator[4];
};


#define RTI_NETIO_CONFIGURATOR_PROPERTY_DEFAULT {     \
  REDA_FAST_BUFFER_POOL_GROWTH_PROPERTY_DEFAULT, /* pluginGrowth */ \
  {4, REDA_FAST_BUFFER_POOL_UNLIMITED, REDA_FAST_BUFFER_POOL_UNLIMITED},\
  {4, REDA_FAST_BUFFER_POOL_UNLIMITED, REDA_FAST_BUFFER_POOL_UNLIMITED},\
     '#' /* address separator */, \
     "://" /* locator separator */ \
}


struct RTINetioConfigurator;

extern RTINetioDllExport
struct RTINetioConfigurator* RTINetioConfigurator_new(
    const struct RTINetioConfiguratorProperty *propertyIn,
    struct REDADatabase *databaseIn,
    struct REDAExclusiveArea *tableEAIn,
    struct RTIEventActiveObjectListener *shutdownListenerIn,
    struct REDAWorker *worker);

extern RTINetioDllExport void
RTINetioConfigurator_delete(struct RTINetioConfigurator *me);

extern RTINetioDllExport void
RTINetioConfigurator_getProperty(
    struct RTINetioConfigurator *me,
    struct RTINetioConfiguratorProperty *propertyOut,
    struct REDAWorker *worker);

extern RTINetioDllExport
RTIBool RTINetioConfigurator_shutdown(
        struct RTINetioConfigurator* me,
        struct REDAWorker *worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_installTransportPlugin(
                struct RTINetioConfigurator* me,
                struct REDAWeakReference* pluginHandleOut,
                NDDS_Transport_Plugin* pluginInstanceIn,
                const struct RTINetioAliasList* aliasListIn,
                const NDDS_Transport_Address_t* networkAddressIn,
                struct REDAWorker* worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_queryTransportPlugin(
                struct RTINetioConfigurator* me,
		struct RTINetioAliasList* aliasListOut,
		NDDS_Transport_Address_t* networkAddressOut,
		struct REDAWeakReference* pluginHandleOut,
		const NDDS_Transport_Plugin* pluginInstanceIn,
		struct REDAWorker* worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_addDestinationRoute(
        struct RTINetioConfigurator *me,
        NDDS_Transport_ClassId_t serviceTransportClassIn,
        const struct RTINetioAddressFilter *serviceAddressRangeIn,
        const struct REDAWeakReference *pluginHandleIn,
        const struct RTINetioLocator* relayLocatorIn,
        struct REDAWorker *worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_addEntryportRoute(
        struct RTINetioConfigurator *me,
        const struct RTINetioAddressFilter *serviceAddressRangeIn,
        const struct REDAWeakReference *pluginHandleIn,
        struct REDAWorker *worker);

extern RTIBool RTINetioDllExport
RTINetioConfigurator_addDefaultRoutes(
        struct RTINetioConfigurator *me,
        struct REDAWorker *worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_queryInterfaces(
                struct RTINetioConfigurator *me,
		RTIBool* foundMoreInterfacesThanProvidedForOut,
                NDDS_Transport_Interface_t *interfaceArrayOut,
                int* interfaceCountOut,
                const struct RTINetioAliasList* aliasListIn,
                int interfaceArraySizeIn,
                struct REDAWorker* worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_getMinMaxMessageSize(
                struct RTINetioConfigurator *me,
                const struct RTINetioAliasList* aliasListIn,
                int* messageSizeOut,
                struct REDAWorker* worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_populateUnicastLocators(
                const struct RTINetioConfigurator *me,
                RTIBool* foundMoreThanProvidedForOut,
                int* locatorArrayLengthInOut,
                struct RTINetioLocator *locatorArrayInOut,
                int locatorArrayCapacityIn,
                const struct RTINetioAliasList* unicastPluginAliasesIn,
                RTI_INT32 portIn,
                const struct RTINetioAliasList* enabledPluginAliasesIn,
                struct REDAWorker* worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_populateLocators(
    const struct RTINetioConfigurator *me,
    RTIBool* foundMoreThanProvidedForOut,
    int* locatorArrayLengthInOut,
    struct RTINetioLocator *locatorArrayInOut,
    int locatorArrayCapacityIn,
    const NDDS_Transport_Address_t* networkAddressIn,
    const char* transportAddressStringIn,
    RTI_INT32 portIn,
    const struct RTINetioAliasList* pluginAliasesIn,
    const struct RTINetioAliasList* enabledPluginAliasesIn,
    RTIBool mustBeAllowedByEntryportRoutingtTableIn,
    RTIBool mustBeAllowedByDestinationRoutingtTableIn,
    RTIBool mustBeMulticastIn,
    struct REDAWorker* worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_populateLocatorsFromAddressString(
    const struct RTINetioConfigurator *me,
    RTIBool* foundMoreThanProvidedForOut,
    int* locatorArrayLengthInOut,
    struct RTINetioLocator *locatorArrayInOut,
    int locatorArrayCapacityIn,
    const char* addressStringIn,
    RTI_INT32 portIn,
    const struct RTINetioAliasList* pluginAliasesIn,
    const struct RTINetioAliasList* enabledPluginAliasesIn,
    RTIBool mustBeAllowedByEntryportRoutingtTableIn,
    RTIBool mustBeAllowedByDestinationRoutingtTableIn,
    RTIBool mustBeMulticastIn,
    struct REDAWorker* worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_populateLocatorsFromLocatorString(
    const struct RTINetioConfigurator *me,
    RTIBool* foundMoreThanProvidedForOut,
    int* locatorArrayLengthInOut,
    struct RTINetioLocator *locatorArrayInOut,
    int locatorArrayCapacityIn,
    const char* locatorStringIn,
    RTI_INT32 defaultPortIn,
    struct RTINetioAliasList* defaultAliasIn,
    const struct RTINetioAliasList* enabledPluginAliasesIn,
    RTIBool mustBeAllowedByEntryportRoutingtTableIn,
    RTIBool mustBeAllowedByDestinationRoutingtTableIn,
    RTIBool mustBeMulticastIn,
    struct REDAWorker* worker);

extern RTINetioDllExport RTIBool
RTINetioConfigurator_splitLocatorString(
    const char **aliasStrOut,
    const char **addressStrOut,
    char *aliasStrCopyInOut,
    const char *locatorStringIn,
    const char *locatorSeparator);

typedef void (*RTINetioConfiguratorListenerOnAfterInstall)(
    struct RTINetioConfiguratorListener *me,
    const struct REDAWeakReference *pluginHandleIn,
    NDDS_Transport_Plugin *transportIn,
    const struct RTINetioAliasList *aliasListIn,
    const struct RTINetioAddressFilter *serviceRangeIn,
    struct REDAWorker *worker);

typedef RTIBool (*RTINetioConfiguratorListenerOnBeforeUninstall)(
    struct RTINetioConfiguratorListener *me,
    const struct REDAWeakReference *pluginHandleIn,
    NDDS_Transport_Plugin *transportIn, struct REDAWorker *worker);

struct RTINetioConfiguratorListener {
    /*e Start using the new transport plugin in the configurator */
    RTINetioConfiguratorListenerOnAfterInstall      onAfterTransportPluginInstall;
    /*e Stop using the transport plugin about to be uninstalled
        from the configurator
    */
    RTINetioConfiguratorListenerOnBeforeUninstall onBeforeTransportPluginUninstall;
};

extern RTINetioDllExport RTIBool
RTINetioConfiguratorUtil_assembleFullyQualifiedAddress(
                NDDS_Transport_Address_t* fullyQualifiedAddressOut,
                const NDDS_Transport_Address_t* networkAddressIn,
                const NDDS_Transport_Address_t* transportAddressIn,
                int transportAddressBitCountIn);

extern RTINetioDllExport RTIBool
RTINetioConfiguratorUtil_disassembleFullyQualifiedAddress(
                NDDS_Transport_Address_t* networkAddressOut,
                NDDS_Transport_Address_t* transportAddressOut,
                const NDDS_Transport_Address_t* fullyQualifiedAddressIn,
                int transportAddressBitCountIn);

/*e @ingroup RTINetioConfiguratorUtilClass
  @brief Generate a default 96-bit network address based on the
         transport class id, rtps host id, and the rtps app id.

  This method is suitable for generating a default network address for the
  transport plugins that require <= 32-bits for addressing the transport
  network.

  Generates a 96-bit network address using the following heuristic:

     transportClassIdIn, rtpsHostIdIn, rtpsAppIdIn, rtpsInstanceIdIn, instanceId,  0
         2-bytes           4-bytes       3-bytes     1-byte            2-bytes     4-bytes

  This heuristic ensures that the given instance of a given transport class
  will have a unique 96-bit network address in the NDDS domain.

  Note that the parameters are in the host-byte order. This method takes of
  composing a network address in network-byte order.

  @pre Valid arguments

  @param networkAddressOut \st_out A non-NULL pointer for storing the output.
                        Only the least significant two bytes are used.

  @param transportClassIdIn \st_in The transport plugin class id.

  @param rtpsHostIdIn \st_in The RTPS protocol host Id

  @param rtpsHostIdIn \st_in The RTPS protocol app Id

  @param pluginInstanceIdIn \st_in The plugin instance number on this a
                                   application.  Only the least significant
                                   two bytes are used.

  @return RTI_TRUE on success, RTI_FALSE on failure (precondition not met).
*/
extern RTINetioDllExport RTIBool
RTINetioConfiguratorUtil_generateDefaultNetworkAddress96(
               NDDS_Transport_Address_t* networkAddressOut,
               NDDS_Transport_ClassId_t transportClassIdIn,
               RTI_UINT32 rtpsHostIdIn,
               RTI_UINT32 rtpsAppIdIn,
               RTI_UINT32 rtpsInstanceIdIn, /*RTPS.2.0*/
               RTI_UINT32 pluginInstanceIdIn);

extern RTINetioDllExport RTIBool
RTINetioConfiguratorUtil_populateEntryports(
                struct RTINetioConfigurator *configuratorIn,
                struct RTINetioLocatorInfo *entryportArrayOut,
                int* entryportCountOut,
                int entryportArraySizeIn,
                const struct RTINetioAliasList* aliasListIn,
                NDDS_Transport_Port_t portIn,
                int cosIn,
                struct REDAWorker* worker);

extern RTINetioDllExport NDDS_Transport_Plugin*
RTINetioConfiguratorUtil_setupIntraPlugin(
               struct REDAWeakReference* pluginHandleOut,
               NDDS_Transport_Address_t* networkAddressInOut,
               struct RTINetioConfigurator *configuratorIn,
               RTI_UINT32 rtpsHostIdIn,
               RTI_UINT32 rtpsAppIdIn,
               RTI_UINT32 rtpsInstanceIdIn, /*RTPS.2.0*/
               struct RTIClock *clockIn,
               struct RTINetioAliasList* aliasListIn,
               struct NDDS_Transport_Intra_Property_t* propertyIn,
               struct REDAWorker* worker);

extern RTINetioDllExport NDDS_Transport_Plugin*
RTINetioConfiguratorUtil_setupShmemPlugin(
               struct REDAWeakReference* pluginHandleOut,
               NDDS_Transport_Address_t* networkAddressInOut,
               struct RTINetioConfigurator *configuratorIn,
               RTI_UINT32 rtpsHostIdIn,
               struct RTIClock *clockIn,
               struct RTINetioAliasList* aliasListIn,
               struct NDDS_Transport_Shmem_Property_t* propertyIn,
               struct REDAWorker* worker);

extern RTINetioDllExport NDDS_Transport_Plugin*
RTINetioConfiguratorUtil_setupUDPv4Plugin(
               struct REDAWeakReference* pluginHandleOut,
               struct RTINetioConfigurator *configuratorIn,
               struct RTIClock *clockIn,
               struct NDDS_Transport_UDPv4_SocketFactory *socketFactoryIn,
               struct RTINetioAliasList* aliasListIn,
               struct NDDS_Transport_UDPv4_Property_t* propertyIn,
               struct REDAWorker* worker);

extern RTINetioDllExport NDDS_Transport_Plugin*
RTINetioConfiguratorUtil_setupUDPv6Plugin(
               struct REDAWeakReference* pluginHandleOut,
               struct RTINetioConfigurator *configuratorIn,
               struct RTIClock *clockIn,
               struct NDDS_Transport_UDPv6_SocketFactory *socketFactoryIn,
               struct RTINetioAliasList* aliasListIn,
               struct NDDS_Transport_UDPv6_Property_t* propertyIn,
               struct REDAWorker* worker);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* netio_configurator_h */
