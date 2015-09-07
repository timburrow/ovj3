/*
 * @(#)disc_builtin.h    generated by: makeheader    Mon Dec  3 23:08:19 2007
 *
 *		built from:	builtin.ifc
 */

#ifndef disc_builtin_h
#define disc_builtin_h



#ifndef pres_participant_h
    #include "pres/pres_participant.h"
#endif

#ifndef cdr_encapsulation_h
    #include "cdr/cdr_encapsulation.h"
#endif

#ifndef cdr_stream_h
    #include "cdr/cdr_stream.h"
#endif

#ifndef rti_makeheader_h
    #include "log/log_makeheader.h"
#endif

#ifndef disc_dll_h
    #include "disc/disc_dll.h"
#endif

#ifndef osapi_heap_h
    #include "osapi/osapi_heap.h"
#endif

#ifndef reda_fastBuffer_h
    #include "reda/reda_fastBuffer.h"
#endif

#ifndef pres_typePlugin_h
    #include "pres/pres_typePlugin.h"
#endif

#ifndef pres_participant_h
    #include "pres/pres_common.h"
#endif

#ifndef pres_participant_h
    #include "pres/pres_participant.h"
#endif

#ifndef pres_psService_h
    #include "pres/pres_psService.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif



/* Protocol defined built-in endpoint bits */ 
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_ANNOUNCER                     0x00000001 << 0
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_DETECTOR                      0x00000001 << 1
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_ANNOUNCER                     0x00000001 << 2
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_DETECTOR                      0x00000001 << 3
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_ANNOUNCER                    0x00000001 << 4
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_DETECTOR                     0x00000001 << 5
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_ANNOUNCER               0x00000001 << 6
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_DETECTOR                0x00000001 << 7
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_ANNOUNCER               0x00000001 << 8
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_DETECTOR                0x00000001 << 9


/* Builtin topic names */
#define DISC_BUILTIN_TOPIC_PARTICIPANT_SELF             "DISCParticipant"
#define DISC_BUILTIN_TOPIC_PARTICIPANT_PROXY            "DISCParticipantProxy"
#define DISC_BUILTIN_TOPIC_PARTICIPANT_STATE            "DISCParticipantState"
#define DISC_BUILTIN_TOPIC_PUBLICATION                  "DISCPublication"
#define DISC_BUILTIN_TOPIC_SUBSCRIPTION                 "DISCSubscription"


struct DISCPluginInfo {
    /*e Identifies vendor/implementer of the plugin. Meaningful only if (classId&0x8000)==1.
    */
    long vendorId;
    /*e Identifies the plugin. (classId&0x8000)==0 is reserved for standardized (interoperable) discovery protocols.
    */
    long classId;
    /*e Version info of the plugin.
    */
    long version;
    /*e Additional config parameters of the plugin.
    */
    struct PRESSequenceOctet parameters;
};


/*e \ingroup DISCPluggableModule
  \brief Used to initialize DISCPluginInfo.
*/
#define DISC_PLUGIN_INFO_INITIALIZE {   \
0, /* vendorId */                       \
0, /* classId */                        \
0, /* version */                        \
{0, 0, NULL} /* parameters */           \
}

extern DISCDllExport RTIBool
DISCPluginInfo_isSamePlugin(const struct DISCPluginInfo *left,
                            const struct DISCPluginInfo *right);

extern DISCDllExport void
DISCPluginInfo_copyShallow(struct DISCPluginInfo *to,
                           const struct DISCPluginInfo *from);


/*e \ingroup DISCPluggableModule
  \brief Maximum number of installable participant discovery plugins.
*/
  #define DISC_MAX_PDP_PLUGINS 8
/*e \ingroup DISCPluggableModule
  \brief Maximum number of installable endpoint discovery plugins.
*/
  #define DISC_MAX_EDP_PLUGINS 8

typedef enum {
    /*e Participant builtin topic.
    */
    DISC_BUILTIN_TOPIC_KIND_PARTICIPANT = 0,
    /*e Publication builtin topic.
    */
    DISC_BUILTIN_TOPIC_KIND_PUBLICATION,
    /*e Subscription builtin topic.
    */
    DISC_BUILTIN_TOPIC_KIND_SUBSCRIPTION,
    /*e Topic builtin topic.
    */
    DISC_BUILTIN_TOPIC_KIND_TOPIC,
    /* do not remove this; used to size internal array */
    _DISC_BUILTIN_TOPIC_KIND
} DISCBuiltinTopicKind;

struct
DISCBuiltinTopicParticipantData {
    /*e Guid of the participant
    */
    struct MIGRtpsGuid guid;
    /*e Parameters of the participant.
    */
    struct PRESParticipantParameter *parameter;
};


/*e \ingroup DISCPluggableModule
  \brief Initialize participant builtin topic data.
*/
#define DISC_BUILTIN_TOPIC_PARTICIPANT_DATA_INITIALIZE {        \
    MIG_RTPS_GUID_UNKNOWN, /* guid */                           \
    NULL /* parameter */                                        \
}

struct
DISCBuiltinTopicPublicationData {
    /*e GUID of the participant of the data writer.
    */
    struct MIGRtpsGuid participantGuid;
    /*e GUID of the data writer itself.
    */
    struct MIGRtpsGuid guid;
    /*e Parameters of the data writer.
    */
    struct PRESPsPublicationParameter *parameter;
};


/*e \ingroup DISCPluggableModule
  \brief Initialize publication builtin topic data.
*/
#define DISC_BUILTIN_TOPIC_PUBLICATION_DATA_INITIALIZE { \
    MIG_RTPS_GUID_UNKNOWN, /* participantGuid */ \
    MIG_RTPS_GUID_UNKNOWN, /* guid */ \
    NULL /* parameter */ \
}

struct
DISCBuiltinTopicSubscriptionData {
    /*e GUID of the participant of the data reader.
    */
    struct MIGRtpsGuid participantGuid;
    /*e GUID of the data reader itself.
    */
    struct MIGRtpsGuid guid;
    /*e Parameters of the data reader.
    */
    struct PRESPsSubscriptionParameter *parameter;
};


/*e \ingroup DISCPluggableModule
  \brief Initialize subscription builtin topic data.
*/
#define DISC_BUILTIN_TOPIC_SUBSCRIPTION_DATA_INITIALIZE { \
    MIG_RTPS_GUID_UNKNOWN, /* participantGuid */ \
    MIG_RTPS_GUID_UNKNOWN, /* guid */ \
    NULL /* parameter */ \
}

struct
DISCBuiltinTopicTopicData {
    /*e GUID.
    */
    struct MIGRtpsGuid guid;
};


/*e \ingroup DISCPluggableModule
  \brief Initialize topic builtin topic data.
*/
#define DISC_BUILTIN_TOPIC_TOPIC_DATA_INITIALIZE { \
    MIG_RTPS_GUID_UNKNOWN /* guid */ \
}

extern DISCDllExport RTIBool
DISCBuiltin_isBuiltinTopicName(const char* topicName);

struct DISCBuiltinTopicParticipantDataPluginSerializeOption {
    /* Use for PropertyQosPolicy parameter serialization */
    int propertyMaximumSerializationLength;
};

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPluginSerializeOption_initialize(
    struct DISCBuiltinTopicParticipantDataPluginSerializeOption * self,
    int propertyListMaximumLength,
    int propertyStringMaximumLength);

struct DISCBuiltinTopicParticipantDataPool {
    struct PRESTypePluginDataPool _super;

    struct REDAFastBufferPool *_bufferPool;

    struct REDAFastBufferPool *_samplePool;
    struct REDAFastBufferPool *_participantParameterDataPool;

    struct REDAFastBufferPool *_userDataPool;

    struct REDAFastBufferPool *_propertyListPool;

    struct REDAFastBufferPool *_participantNamePool;
    /* The property list is made up of to parts;
     * the sequence elements and the strings. When we
     * de-serialize we need to know how many elements
     * it was created with
     */
    int _propertyListMaximumLength;
    int _propertyStringMaximumLength;
    int _propertyMaximumSerializationLength;

    int _maxSizeSerialized;
};

extern DISCDllExport RTIBool
DISCBuiltinTopicParticipantDataPool_initialize(
    struct DISCBuiltinTopicParticipantDataPool *self,
    int initialBuffers, int maxBuffers, /* for writer */
    int bufferMaxSizeSerialized,
    int initialSamples, int maxSamples, /* for reader */
    int userDataMaximumLength,
    int propertyListMaximumLength,
    int propertyStringMaximumLength);

extern DISCDllExport struct DISCBuiltinTopicParticipantDataPool*
DISCBuiltinTopicParticipantDataPool_new(
    int initialBuffers, int maxBuffers, /* for writer */
    int bufferMaxSizeSerialized,
    int initialSamples, int maxSamples, /* for reader */
    int userDataMaximumLength,
    int propertyListMaximumLength,
    int propertyStringMaximumLength);

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPool_finalize(
    struct DISCBuiltinTopicParticipantDataPool* self);

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPool_delete(
    struct DISCBuiltinTopicParticipantDataPool* self);

extern DISCDllExport int 
DISCBuiltinTopicParticipantDataPool_getMaxSizeSerialized(
    struct DISCBuiltinTopicParticipantDataPool *self);

extern DISCDllExport char * 
DISCBuiltinTopicParticipantDataPool_getBuffer(
    struct DISCBuiltinTopicParticipantDataPool *self,
    int *bufferLength /* out */);

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPool_returnBuffer(
    struct DISCBuiltinTopicParticipantDataPool *self,
    char* buffer);

extern DISCDllExport struct DISCBuiltinTopicParticipantData *
DISCBuiltinTopicParticipantDataPool_getSample(
    struct DISCBuiltinTopicParticipantDataPool *self,
    void** handle /* out */);

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPool_returnSample(
    struct DISCBuiltinTopicParticipantDataPool *self,
    struct DISCBuiltinTopicParticipantData *sample,
    void *handle /* in */);

extern DISCDllExport struct PRESTypePluginDataPool *
DISCBuiltinTopicParticipantDataPool_getBaseDataPool(
    struct DISCBuiltinTopicParticipantDataPool* self);

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPlugin_setDefaultParameterValues(
    struct DISCBuiltinTopicParticipantData *topic_data);

struct DISCBuiltinTopicSubscriptionDataPluginSerializeOption {
    /* Use for PropertyQosPolicy parameter serialization */
    int propertyMaximumSerializationLength;
    /* Use for type code parameter serialization */
    int typeCodeMaximumSerializedLength;
};

extern void DISCBuiltinTopicSubscriptionDataPluginSerializeOption_initialize(
    struct DISCBuiltinTopicSubscriptionDataPluginSerializeOption * self,
    int propertyListMaximumLength,
    int propertyStringMaximumLength,
    int typeCodeMaximumSerializedLength);

struct DISCBuiltinTopicSubscriptionDataPool {
    struct PRESTypePluginDataPool _super;

    struct REDAFastBufferPool *_bufferPool;

    struct REDAFastBufferPool *_samplePool;
    struct REDAFastBufferPool *_subscriptionParameterPool;

    struct REDAFastBufferPool *_topicNamePool;
    struct REDAFastBufferPool *_typeNamePool;

    struct REDAFastBufferPool *_userDataPool;
    struct REDAFastBufferPool *_groupDataPool;
    struct REDAFastBufferPool *_topicDataPool;

    struct REDAFastBufferPool *_partitionPool;

    struct REDAFastBufferPool *_filterPropertyPool;
    
    struct REDAFastBufferPool *_typeCodePool;        

    struct REDAFastBufferPool *_propertyPool;

    int _propertyListMaximumLength;
    int _propertyStringMaximumLength;
    int _propertyMaximumSerializationLength;

    int _maxSizeSerialized;
};

extern DISCDllExport int 
DISCBuiltinTopicSubscriptionDataPool_getMaxSizeSerialized(
    struct DISCBuiltinTopicSubscriptionDataPool *self);

extern DISCDllExport char * 
DISCBuiltinTopicSubscriptionDataPool_getBuffer(
    struct DISCBuiltinTopicSubscriptionDataPool *self,
    int *bufferLength /* out */);

extern DISCDllExport void 
DISCBuiltinTopicSubscriptionDataPool_returnBuffer(
    struct DISCBuiltinTopicSubscriptionDataPool *self,
    char* buffer);

extern DISCDllExport struct DISCBuiltinTopicSubscriptionData *
DISCBuiltinTopicSubscriptionDataPool_getSample(
    struct DISCBuiltinTopicSubscriptionDataPool *self,
    void** handle /* out */);

extern DISCDllExport void 
DISCBuiltinTopicSubscriptionDataPool_returnSample(
    struct DISCBuiltinTopicSubscriptionDataPool *self,
    struct DISCBuiltinTopicSubscriptionData *sample,
    void *handle /* in */);

extern DISCDllExport void 
DISCBuiltinTopicSubscriptionDataPool_delete(
    struct DISCBuiltinTopicSubscriptionDataPool* self);

extern DISCDllExport 
struct DISCBuiltinTopicSubscriptionDataPool *
DISCBuiltinTopicSubscriptionDataPool_new(
    int initialBuffers, int maxBuffers, /* for writer */
    int bufferMaxSizeSerialized,
    int initialSamples, int maxSamples, /* for reader */
    int userDataMaximumLength,
    int groupDataMaximumLength,
    int topicDataMaximumLength,
    int partitionMaximumCumulativeLength,
    int maxContentFilterPropertyLength,
    int typeCodeMaximumSerializedLength,
    int propertyListMaximumLength,
    int propertyStringMaximumLength);

extern DISCDllExport 
struct PRESTypePluginDataPool *
DISCBuiltinTopicSubscriptionDataPool_getBaseDataPool(
    struct DISCBuiltinTopicSubscriptionDataPool* self);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_serializeData(
    struct RTICdrStream *stream,
    const struct DISCBuiltinTopicSubscriptionData *topic_data,
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_serializeEncapsulation(
    struct RTICdrStream *stream, 
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_serialize(
    struct RTICdrStream *stream,
    const struct DISCBuiltinTopicSubscriptionData *topic_data,
    void *serializeOption);

extern DISCDllExport void 
DISCBuiltinTopicSubscriptionDataPlugin_setDefaultParameterValues(
    struct DISCBuiltinTopicSubscriptionData *topic_data);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_deserializeParameterValue(
    RTIBool *ok, struct DISCBuiltinTopicSubscriptionData *topic_data,
    struct RTICdrStream *stream,
    RTICdrUnsignedShort parameterId, RTICdrUnsignedShort parameterLength,
    struct DISCBuiltinTopicSubscriptionDataPool *dataPool);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_deserializeData(
    struct RTICdrStream *stream,
    struct DISCBuiltinTopicSubscriptionData *topic_data,
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_deserializeEncapsulation(
    struct RTICdrStream *stream, 
    void *deserializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_deserialize(
    struct RTICdrStream *stream,
    struct DISCBuiltinTopicSubscriptionData *topic_data,
    void *serializeOption);

extern DISCDllExport unsigned int 
DISCBuiltinTopicSubscriptionDataPlugin_getParametersMaxSizeSerialized(
    unsigned int size, int userDataMaximumLength, int groupDataMaximumLength,
    int topicDataMaximumLength,
    int partitionMaximumNameCount,
    int partitionMaximumCumulativeLength,
    int typeCodeMaximumSerializedLength,
    int contentFilterPropertyMaximumSerializedLength,
    int propertyListMaximumLength,int propertyStringMaximumLength);

extern DISCDllExport unsigned int
DISCBuiltinTopicSubscriptionDataPlugin_getMaxSizeSerializedWithData(
    unsigned int size, int userDataMaximumLength, int groupDataMaximumLength,
    int topicDataMaximumLength,
    int partitionMaximumNameCount,  
    int partitionMaximumCumulativeLength,
    int contentFilterPropertyMaxSerializedLength,
    int typeCodeMaximumSerializedLength,
    int propertyListMaximumLength,
    int propertyStringMaximumLength);

extern DISCDllExport void 
DISCBuiltinTopicSubscriptionDataPlugin_print(
    const struct DISCBuiltinTopicSubscriptionData *topic_data,
    const char *desc,
    unsigned int indent);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_copy(
    struct DISCBuiltinTopicSubscriptionData *out,
    const struct DISCBuiltinTopicSubscriptionData *in);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_initialize(
    struct DISCBuiltinTopicSubscriptionData *topic_data);

extern DISCDllExport RTIBool 
DISCBuiltinTopicSubscriptionDataPlugin_initialize_ex(
    struct DISCBuiltinTopicSubscriptionData *sample,
    RTIBool allocatePointers);

extern DISCDllExport void 
DISCBuiltinTopicSubscriptionDataPlugin_finalize(
    struct DISCBuiltinTopicSubscriptionData *topic_data);

extern DISCDllExport void
DISCBuiltinTopicSubscriptionDataPlugin_finalize_ex(
    struct DISCBuiltinTopicSubscriptionData *sample,
    RTIBool deletePointers);

extern DISCDllExport struct DISCBuiltinTopicSubscriptionData *
DISCBuiltinTopicSubscriptionDataPlugin_createSample();

extern DISCDllExport struct DISCBuiltinTopicSubscriptionData *
DISCBuiltinTopicSubscriptionDataPlugin_createSample_ex(
    RTIBool allocatePointers);

extern DISCDllExport void 
DISCBuiltinTopicSubscriptionDataPlugin_destroySample(
    struct DISCBuiltinTopicSubscriptionData *topic_data);

extern DISCDllExport struct PRESTypePlugin**
DISCBuiltinTopicSubscriptionDataPlugin_assert();

extern DISCDllExport void
DISCBuiltinTopicSubscriptionDataPlugin_delete(
    struct PRESTypePlugin *plugin);

extern DISCDllExport int
DISCBuiltinTopicSubscriptionDataPlugin_compare(
    const struct DISCBuiltinTopicSubscriptionData *left,
    const struct DISCBuiltinTopicSubscriptionData *right);

struct DISCBuiltinTopicPublicationDataPluginSerializeOption {
    /* Use for PropertyQosPolicy parameter serialization */
    int propertyMaximumSerializationLength;
    /* Use for TypeCode parameter serialization */
    int typeCodeMaximumSerializedLength;
};

extern DISCDllExport void 
DISCBuiltinTopicPublicationDataPluginSerializeOption_initialize(
    struct DISCBuiltinTopicPublicationDataPluginSerializeOption * self,
    int propertyListMaximumLength,
    int propertyStringMaximumLength,
    int typeCodeMaximumSerializedLength);

struct DISCBuiltinTopicPublicationDataPool {
    struct PRESTypePluginDataPool _super;

    struct REDAFastBufferPool *_bufferPool;

    struct REDAFastBufferPool *_samplePool;
    struct REDAFastBufferPool *_publicationParameterPool;

    struct REDAFastBufferPool *_topicNamePool;
    struct REDAFastBufferPool *_typeNamePool;

    struct REDAFastBufferPool *_userDataPool;
    struct REDAFastBufferPool *_groupDataPool;
    struct REDAFastBufferPool *_topicDataPool;
    struct REDAFastBufferPool *_partitionPool;
    
    struct REDAFastBufferPool *_typeCodePool;

    struct REDAFastBufferPool *_propertyPool;

    int _propertyListMaximumLength;
    int _propertyStringMaximumLength;
    int _propertyMaximumSerializationLength;

    int _maxSizeSerialized;
};

extern DISCDllExport char * 
DISCBuiltinTopicPublicationDataPool_getBuffer(
    struct DISCBuiltinTopicPublicationDataPool *self,
    int *bufferLength /* out */);

extern DISCDllExport void 
DISCBuiltinTopicPublicationDataPool_returnBuffer(
    struct DISCBuiltinTopicPublicationDataPool *self,
    char *buffer);

extern DISCDllExport 
struct DISCBuiltinTopicPublicationData *
DISCBuiltinTopicPublicationDataPool_getSample(
    struct DISCBuiltinTopicPublicationDataPool *self,
    void** handle /* out */);

extern DISCDllExport void 
DISCBuiltinTopicPublicationDataPool_returnSample(
    struct DISCBuiltinTopicPublicationDataPool *self,
    struct DISCBuiltinTopicPublicationData *sample,
    void *handle /* in */);

extern DISCDllExport void 
DISCBuiltinTopicPublicationDataPool_delete(
    struct DISCBuiltinTopicPublicationDataPool* self);

extern DISCDllExport 
struct DISCBuiltinTopicPublicationDataPool *
DISCBuiltinTopicPublicationDataPool_new(
    int initialBuffers, int maxBuffers, /* for writer */
    int bufferMaxSizeSerialized,
    int initialSamples, int maxSamples, /* for reader */
    int userDataMaximumLength,
    int groupDataMaximumLength,
    int topicDataMaximumLength,
    int partitionMaximumCumulativeLength,
    int typeCodeMaximumSerializedLength,
    int propertyListMaximumLength,
    int propertyStringMaximumLength);

extern DISCDllExport
struct PRESTypePluginDataPool *
DISCBuiltinTopicPublicationDataPool_getBaseDataPool(
    struct DISCBuiltinTopicPublicationDataPool* self);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_serializeData(
    struct RTICdrStream *stream,
    const struct DISCBuiltinTopicPublicationData *topic_data,
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_serializeEncapsulation(
    struct RTICdrStream *stream, 
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_serialize(
    struct RTICdrStream *stream,
    const struct DISCBuiltinTopicPublicationData *topic_data,
    void *serializeOption);

extern DISCDllExport void 
DISCBuiltinTopicPublicationDataPlugin_setDefaultParameterValues(
    struct DISCBuiltinTopicPublicationData *topic_data);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_deserializeParameterValue(
    RTIBool *ok, struct DISCBuiltinTopicPublicationData *topic_data,
    struct RTICdrStream *stream,
    RTICdrUnsignedShort parameterId, RTICdrUnsignedShort parameterLength,
    struct DISCBuiltinTopicPublicationDataPool *dataPool);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_deserializeData(
    struct RTICdrStream *stream,
    struct DISCBuiltinTopicPublicationData *topic_data,
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_deserializeEncapsulation(
    struct RTICdrStream *stream, 
    void *deserializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_deserialize(
    struct RTICdrStream *stream,
    struct DISCBuiltinTopicPublicationData *topic_data,
    void *serializeOption);

extern DISCDllExport unsigned int 
DISCBuiltinTopicPublicationDataPlugin_getParametersMaxSizeSerialized(
    unsigned int size, int userDataMaximumLength, int groupDataMaximumLength,
    int topicDataMaximumLength, int partitionMaximumNameCount,
    int partitionMaximumCumulativeLength, int typeCodeMaximumSerializedLength,
    int propertyListMaximumLength,int propertyStringMaximumLength);

extern DISCDllExport unsigned int
DISCBuiltinTopicPublicationDataPlugin_getMaxSizeSerializedWithData(
    unsigned int size, int userDataMaximumLength, int groupDataMaximumLength,
    int topicDataMaximumLength, int partitionMaximumNameCount,
    int partitionMaximumCumulativeLength,int typeCodeMaximumSerializedLength,
    int propertyListMaximumLength,int propertyStringMaximumLength);

extern DISCDllExport void 
DISCBuiltinTopicPublicationDataPlugin_print(
    const struct DISCBuiltinTopicPublicationData *topic_data,
    const char *desc,
    unsigned int indent);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_copy(
    struct DISCBuiltinTopicPublicationData *out,
    const struct DISCBuiltinTopicPublicationData *in);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_initialize(
    struct DISCBuiltinTopicPublicationData *topic_data);

extern DISCDllExport RTIBool 
DISCBuiltinTopicPublicationDataPlugin_initialize_ex(
    struct DISCBuiltinTopicPublicationData *sample,
    RTIBool allocatePointers);

extern DISCDllExport void 
DISCBuiltinTopicPublicationDataPlugin_finalize(
    struct DISCBuiltinTopicPublicationData *topic_data);

extern DISCDllExport void
DISCBuiltinTopicPublicationDataPlugin_finalize_ex(
    struct DISCBuiltinTopicPublicationData *sample,
    RTIBool deletePointers);

extern DISCDllExport struct DISCBuiltinTopicPublicationData*
DISCBuiltinTopicPublicationDataPlugin_createSample();

extern DISCDllExport struct DISCBuiltinTopicPublicationData *
DISCBuiltinTopicPublicationDataPlugin_createSample_ex(
    RTIBool allocatePointers);

extern DISCDllExport void 
DISCBuiltinTopicPublicationDataPlugin_destroySample(
    struct DISCBuiltinTopicPublicationData *topic_data);

extern DISCDllExport struct PRESTypePlugin**
DISCBuiltinTopicPublicationDataPlugin_assert();

extern DISCDllExport void
DISCBuiltinTopicPublicationDataPlugin_delete(
    struct PRESTypePlugin *plugin);

extern DISCDllExport int 
DISCBuiltinTopicPublicationDataPlugin_compare(
    const struct DISCBuiltinTopicPublicationData *left,
    const struct DISCBuiltinTopicPublicationData *right);

extern DISCDllExport RTIBool 
DISCBuiltinTopicParticipantDataPlugin_serializeData(
    struct RTICdrStream *stream,
    const struct DISCBuiltinTopicParticipantData *topic_data,
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicParticipantDataPlugin_serializeEncapsulation(
    struct RTICdrStream *stream,
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicParticipantDataPlugin_serialize(
    struct RTICdrStream *stream,
    const struct DISCBuiltinTopicParticipantData *topic_data,
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicParticipantDataPlugin_deserializeParameterValue(
    RTIBool *ok, struct DISCBuiltinTopicParticipantData *topic_data,
    struct RTICdrStream *stream,
    RTICdrUnsignedShort parameterId, RTICdrUnsignedShort parameterLength,
    struct DISCBuiltinTopicParticipantDataPool *dataPool);

extern DISCDllExport RTIBool
DISCBuiltinTopicParticipantDataPlugin_deserializeData(
    struct RTICdrStream *stream,
    struct DISCBuiltinTopicParticipantData *topic_data,
    void *serializeOption);

extern DISCDllExport RTIBool 
DISCBuiltinTopicParticipantDataPlugin_deserializeEncapsulation(
    struct RTICdrStream *stream, 
    void *deserializeOption);

extern DISCDllExport RTIBool
DISCBuiltinTopicParticipantDataPlugin_deserialize(
    struct RTICdrStream *stream,
    struct DISCBuiltinTopicParticipantData *topic_data,
    void *serializeOption);

extern DISCDllExport unsigned int
DISCBuiltinTopicParticipantDataPlugin_getMaxSizeSerializedWithData(
    unsigned int size,
    int userDataMaximumLength,
    int propertyListMaximumLength,
    int propertyStringMaximumLength);

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPlugin_print(
    const struct DISCBuiltinTopicParticipantData *topic_data,
    const char *desc,
    unsigned int indent);

extern DISCDllExport RTIBool 
DISCBuiltinTopicParticipantDataPlugin_copy(
    struct DISCBuiltinTopicParticipantData *out,
    const struct DISCBuiltinTopicParticipantData *in);

extern DISCDllExport RTIBool 
DISCBuiltinTopicParticipantDataPlugin_initialize(
    struct DISCBuiltinTopicParticipantData *topic_data);

extern DISCDllExport RTIBool 
DISCBuiltinTopicParticipantDataPlugin_initialize_ex(
    struct DISCBuiltinTopicParticipantData *sample,
    RTIBool allocatePointers);

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPlugin_finalize(
    struct DISCBuiltinTopicParticipantData *topic_data);

extern DISCDllExport void
DISCBuiltinTopicParticipantDataPlugin_finalize_ex(
    struct DISCBuiltinTopicParticipantData *sample,
    RTIBool deletePointers);

extern DISCDllExport struct DISCBuiltinTopicParticipantData *
DISCBuiltinTopicParticipantDataPlugin_createSample();

extern DISCDllExport struct DISCBuiltinTopicParticipantData *
DISCBuiltinTopicParticipantDataPlugin_createSample_ex(
    RTIBool allocatePointers);

extern DISCDllExport void 
DISCBuiltinTopicParticipantDataPlugin_destroySample(
    struct DISCBuiltinTopicParticipantData *topic_data);

extern DISCDllExport struct PRESTypePlugin **
DISCBuiltinTopicParticipantDataPlugin_assert();

extern DISCDllExport void
DISCBuiltinTopicParticipantDataPlugin_delete(
    struct PRESTypePlugin *plugin);

extern DISCDllExport int 
DISCBuiltinTopicParticipantDataPlugin_compare(
    const struct DISCBuiltinTopicParticipantData *left,
    const struct DISCBuiltinTopicParticipantData *right);

extern DISCDllExport void
DISCBuiltin_printDurabilityQosPolicy(const struct PRESDurabilityQosPolicy* p,
				     const char *desc, unsigned int indent);

extern DISCDllExport void
DISCBuiltin_printOwnershipQosPolicy(const struct PRESOwnershipQosPolicy *p,
				    const char *desc, unsigned int indent);

extern DISCDllExport void DISCBuiltin_printPresentationQosPolicy(
    const struct PRESPresentationQosPolicy *p,
    const char *desc, unsigned int indent);

extern DISCDllExport void DISCBuiltin_printDestinationOrderQosPolicy(
    const struct PRESDestinationOrderQosPolicy *p,
    const char *desc, unsigned int indent);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* disc_builtin_h */