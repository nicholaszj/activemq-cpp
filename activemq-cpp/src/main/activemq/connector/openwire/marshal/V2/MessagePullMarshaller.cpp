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

#include <activemq/connector/openwire/marshal/v2/MessagePullMarshaller.h>

#include <activemq/connector/openwire/commands/MessagePull.h>

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
DataStructure* MessagePullMarshaller::createObject() const {
    return new MessagePull();
}

///////////////////////////////////////////////////////////////////////////////
unsigned char MessagePullMarshaller::getDataStructureType() const {
    return MessagePull::ID_MESSAGEPULL;
}

///////////////////////////////////////////////////////////////////////////////
void MessagePullMarshaller::tightUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn, BooleanStream* bs ) {
   BaseCommandMarshaller::tightUnmarshal( wireFormat, dataStructure, dataIn, bs );

    MessagePull* info =
        dynamic_cast<MessagePull*>( dataStructure );
    info->setConsumerId( dynamic_cast< ConsumerId* >(
        tightUnmarsalCachedObject( wireFormat, dataIn, bs ) );
    info->setDestination( dynamic_cast< ActiveMQDestination* >(
        tightUnmarsalCachedObject( wireFormat, dataIn, bs ) );
    info->setTimeout( TightUnmarshalLong( wireFormat, dataIn, bs ) );
}

///////////////////////////////////////////////////////////////////////////////
int MessagePullMarshaller::tightMarshal1( OpenWireFormat& wireFormat, DataStructure* dataStructure, BooleanStream& bs ) {

    MessagePull* info =
        dynamic_cast<MessagePull*>( dataStructure );

    int rc = BaseCommandMarshaller::tightMarshal1( wireFormat, dataStructure, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    rc += tightMarshalCachedObject1( wireFormat, data, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    rc += tightMarshalCachedObject1( wireFormat, data, bs );
    rc += tightMarshalLong1( wireFormat, info->getTimeout(), bs );

    return rc + 0;
}

///////////////////////////////////////////////////////////////////////////////
void MessagePullMarshaller::tightMarshal2( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataOutputStream& dataOut, BooleanStream& bs ) {

    BaseCommandMarshaller::tightMarshal2( wireFormat, dataStructure, dataOut, bs );

    MessagePull* info =
        dynamic_cast<MessagePull*>( dataStructure );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    tightMarshalCachedObject2( wireFormat, data, dataOut, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    tightMarshalCachedObject2( wireFormat, data, dataOut, bs );
    tightMarshalLong2( wireFormat, info->getTimeout(), dataOut, bs );
}

///////////////////////////////////////////////////////////////////////////////
void MessagePullMarshaller::looseUnmarshal( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataInputStream& dataIn ) {
    BaseCommandMarshaller::looseUnmarshal( wireFormat, dataStructure, dataIn );
    MessagePull* info = 
        dynamic_cast<MessagePull*>( dataStructure );
   info->setConsumerId( dynamic_cast<ConsumerId* >( 
       looseUnmarshalCachedObject( wireFormat, dataIn ) ) );
   info->setDestination( dynamic_cast<ActiveMQDestination* >( 
       looseUnmarshalCachedObject( wireFormat, dataIn ) ) );
    info->setTimeout( looseUnmarshalLong( wireFormat, dataIn ) );
}

///////////////////////////////////////////////////////////////////////////////
void MessagePullMarshaller::looseMarshal( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataOutputStream& dataOut ) {
    MessagePull* info =
        dynamic_cast<MessagePull*>( dataStructure );
    BaseCommandMarshaller::looseMarshal( wireFormat, dataStructure, dataOut );

    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    looseMarshalCachedObject( wireFormat, data, dataOut );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    looseMarshalCachedObject( wireFormat, data, dataOut );
    looseMarshalLong( wireFormat, info->getTimeout(), dataOut );
}

