/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <activemq/connector/openwire/marshal/v2/MessageDispatchNotificationMarshaller.h>

#include <activemq/connector/openwire/commands/MessageDispatchNotification.h>

//
//     NOTE!: This file is autogenerated - do not modify!
//            if you need to make a change, please see the Java Classes in the
//            activemq-core module
//

using namespace std;
using namespace activemq;
using namespace activemq::io;
using namespace activemq::connector;
using namespace activemq::connector::openwire;
using namespace activemq::connector::openwire::commands;
using namespace activemq::connector::openwire::marshal;
using namespace activemq::connector::openwire::util;
using namespace activemq::connector::openwire::marshal::v2;

///////////////////////////////////////////////////////////////////////////////
DataStructure* MessageDispatchNotificationMarshaller::createObject() const {
    return new MessageDispatchNotification();
}

///////////////////////////////////////////////////////////////////////////////
unsigned char MessageDispatchNotificationMarshaller::getDataStructureType() const {
    return MessageDispatchNotification::ID_MESSAGEDISPATCHNOTIFICATION;
}

///////////////////////////////////////////////////////////////////////////////
void MessageDispatchNotificationMarshaller::tightUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn, BooleanStream* bs ) {
   BaseCommandMarshaller::tightUnmarshal( wireFormat, dataStructure, dataIn, bs );

    MessageDispatchNotification* info =
        dynamic_cast<MessageDispatchNotification*>( dataStructure );
    info->setConsumerId( dynamic_cast< ConsumerId* >(
        tightUnmarsalCachedObject( wireFormat, dataIn, bs ) );
    info->setDestination( dynamic_cast< ActiveMQDestination* >(
        tightUnmarsalCachedObject( wireFormat, dataIn, bs ) );
    info->setDeliverySequenceId( TightUnmarshalLong( wireFormat, dataIn, bs ) );
    info->setMessageId( dynamic_cast< MessageId* >(
        tightUnmarsalNestedObject( wireFormat, dataIn, bs ) );
}

///////////////////////////////////////////////////////////////////////////////
int MessageDispatchNotificationMarshaller::tightMarshal1( OpenWireFormat& wireFormat, DataStructure* dataStructure, BooleanStream& bs ) {

    MessageDispatchNotification* info =
        dynamic_cast<MessageDispatchNotification*>( dataStructure );

    int rc = BaseCommandMarshaller::tightMarshal1( wireFormat, dataStructure, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    rc += tightMarshalCachedObject1( wireFormat, data, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    rc += tightMarshalCachedObject1( wireFormat, data, bs );
    rc += tightMarshalLong1( wireFormat, info->getDeliverySequenceId(), bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getMessageId() );

    rc += tightMarshalNestedObject1( wireFormat, data, bs );

    return rc + 0;
}

///////////////////////////////////////////////////////////////////////////////
void MessageDispatchNotificationMarshaller::tightMarshal2( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataOutputStream& dataOut, BooleanStream& bs ) {

    BaseCommandMarshaller::tightMarshal2( wireFormat, dataStructure, dataOut, bs );

    MessageDispatchNotification* info =
        dynamic_cast<MessageDispatchNotification*>( dataStructure );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    tightMarshalCachedObject2( wireFormat, data, dataOut, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    tightMarshalCachedObject2( wireFormat, data, dataOut, bs );
    tightMarshalLong2( wireFormat, info->getDeliverySequenceId(), dataOut, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getMessageId() );

    tightMarshalNestedObject2( wireFormat, data, dataOut, bs );
}

///////////////////////////////////////////////////////////////////////////////
void MessageDispatchNotificationMarshaller::looseUnmarshal( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataInputStream& dataIn ) {
    BaseCommandMarshaller::looseUnmarshal( wireFormat, dataStructure, dataIn );
    MessageDispatchNotification* info = 
        dynamic_cast<MessageDispatchNotification*>( dataStructure );
   info->setConsumerId( dynamic_cast<ConsumerId* >( 
       looseUnmarshalCachedObject( wireFormat, dataIn ) ) );
   info->setDestination( dynamic_cast<ActiveMQDestination* >( 
       looseUnmarshalCachedObject( wireFormat, dataIn ) ) );
    info->setDeliverySequenceId( looseUnmarshalLong( wireFormat, dataIn ) );
   info->setMessageId( dynamic_cast<MessageId* >( 
       looseUnmarshalNestedObject( wireFormat, dataIn ) ) );
}

///////////////////////////////////////////////////////////////////////////////
void MessageDispatchNotificationMarshaller::looseMarshal( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataOutputStream& dataOut ) {
    MessageDispatchNotification* info =
        dynamic_cast<MessageDispatchNotification*>( dataStructure );
    BaseCommandMarshaller::looseMarshal( wireFormat, dataStructure, dataOut );

    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    looseMarshalCachedObject( wireFormat, data, dataOut );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    looseMarshalCachedObject( wireFormat, data, dataOut );
    looseMarshalLong( wireFormat, info->getDeliverySequenceId(), dataOut );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getMessageId() );

    looseMarshalNestedObject( wireFormat, data, dataOut );
}

