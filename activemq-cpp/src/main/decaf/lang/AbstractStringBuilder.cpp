/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <decaf/lang/AbstractStringBuilder.h>

#include <decaf/lang/System.h>
#include <decaf/lang/Math.h>
#include <decaf/lang/ArrayPointer.h>
#include <decaf/util/Arrays.h>

#include <decaf/lang/exceptions/NegativeArraySizeException.h>
#include <decaf/lang/exceptions/NullPointerException.h>
#include <decaf/lang/exceptions/ArrayIndexOutOfBoundsException.h>
#include <decaf/lang/exceptions/StringIndexOutOfBoundsException.h>

#include <decaf/internal/util/StringUtils.h>

using namespace decaf;
using namespace decaf::lang;
using namespace decaf::lang::exceptions;
using namespace decaf::util;
using namespace decaf::internal::util;

////////////////////////////////////////////////////////////////////////////////
const int AbstractStringBuilder::INITIAL_CAPACITY = 16;

////////////////////////////////////////////////////////////////////////////////
namespace decaf {
namespace lang {

    class AbstractStringBuilderImpl {
    public:

        ArrayPointer<char> value;
        int length;
        bool shared;
        int hashCode;

    public:

        /**
         * Contents created with the given length, the array is length + 1 to add the
         * null terminating character.
         */
        AbstractStringBuilderImpl(int capacity) :
            value(capacity + 1), length(0), shared(false), hashCode(0) {}

        /**
         * Contents is a view of some other String which can either be all or a
         * window allowing for substring methods to not need to copy the contents.
         */
        AbstractStringBuilderImpl(int length, ArrayPointer<char> value) :
            value(value), length(length), shared(false), hashCode(0) {}

        void enlargeBuffer(int min) {
            // API calls for length() * 2 + 2 but we need to add one for Null termination.
            int newCount = ((value.length() >> 1) + value.length()) + 3;
            int newCapacity = (min > newCount ? min : newCount) + 1;
            ArrayPointer<char> newData(newCapacity);
            System::arraycopy(value.get(), 0, newData.get(), 0, length);
            value = newData;
            shared = false;
        }

        int capacity() const {
            return this->value.length() - 1;
        }

        // ensure enough room for current length + additional
        void ensureCapacity(int newLength) {
            if (newLength > (value.length() - 1)) {
                enlargeBuffer(newLength);
            }
        }
    };

}}

////////////////////////////////////////////////////////////////////////////////
AbstractStringBuilder::AbstractStringBuilder() :
    impl(new AbstractStringBuilderImpl(INITIAL_CAPACITY)) {
}

////////////////////////////////////////////////////////////////////////////////
AbstractStringBuilder::AbstractStringBuilder(int capacity) : impl() {

    if (capacity < 0) {
        throw NegativeArraySizeException(__FILE__, __LINE__, "Capacity cannot be negative");
    }

    impl = new AbstractStringBuilderImpl(capacity);
}

////////////////////////////////////////////////////////////////////////////////
AbstractStringBuilder::AbstractStringBuilder(const String& source) :
    impl(new AbstractStringBuilderImpl(source.length() + INITIAL_CAPACITY)) {

    for (int i = 0; i < source.length(); ++i) {
        impl->value[i] = source.charAt(i);
    }

    impl->length = source.length();
}

////////////////////////////////////////////////////////////////////////////////
AbstractStringBuilder::AbstractStringBuilder(const std::string& source) :
    impl(new AbstractStringBuilderImpl((int)source.length() + INITIAL_CAPACITY)) {

    for (int i = 0; i < (int) source.length(); ++i) {
        impl->value[i] = source.at(i);
    }

    impl->length = (int) source.length();
}

////////////////////////////////////////////////////////////////////////////////
AbstractStringBuilder::AbstractStringBuilder(const CharSequence* source) : impl() {

    if (source == NULL) {
        throw NullPointerException(__FILE__, __LINE__, "CharSequence was NULL");
    }

    std::string src = source->toString();
    int capacity = (int) src.length();

    impl = new AbstractStringBuilderImpl(capacity + INITIAL_CAPACITY);

    for (int i = 0; i < (int) src.length(); ++i) {
        impl->value[i] = src.at(i);
    }

    impl->length = (int) src.length();
}

////////////////////////////////////////////////////////////////////////////////
AbstractStringBuilder::~AbstractStringBuilder() {
    try {
        delete this->impl;
    }
    DECAF_CATCHALL_NOTHROW()
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppendNull() {
    int newCount = impl->length + 4;
    if (newCount > impl->capacity()) {
        impl->enlargeBuffer(newCount);
    }

    impl->value[impl->length++] = 'n';
    impl->value[impl->length++] = 'u';
    impl->value[impl->length++] = 'l';
    impl->value[impl->length++] = 'l';
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppend(const char value) {
    int newCount = impl->length + 1;
    if (newCount > impl->capacity()) {
        impl->enlargeBuffer(newCount);
    }

    impl->value[impl->length++] = value;
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppend(const char* value) {

    if (value == NULL) {
        throw NullPointerException(__FILE__, __LINE__, "C String cannot be null, call 'doAppendNull' instead");
    }

    int length = StringUtils::stringLength(value);

    if (length <= 0) {
        return;
    }

    int newLength = impl->length + length;
    impl->ensureCapacity(newLength);
    System::arraycopy(value, 0, impl->value.get(), impl->length, length);
    impl->length = newLength;
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppend(const char* value, int offset, int length) {

    if (value == NULL) {
        throw NullPointerException(__FILE__, __LINE__, "C String cannot be null, call 'doAppendNull' instead");
    }

    int arrayLength = StringUtils::stringLength(value);

    if ((offset | length) < 0 || offset > arrayLength || arrayLength - offset < length) {
        throw ArrayIndexOutOfBoundsException(__FILE__, __LINE__, "Invalid offset or length value given.");
    }

    if (length <= 0) {
        return;
    }

    int newLength = impl->length + length;
    impl->ensureCapacity(newLength);
    System::arraycopy(value, offset, impl->value.get(), impl->length, length);
    impl->length = newLength;
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppend(const CharSequence* value) {

    if (value == NULL) {
        throw NullPointerException(__FILE__, __LINE__, "C String cannot be null, call 'doAppendNull' instead");
    }

    int length = value->length();

    if (length <= 0) {
        return;
    }

    int newLength = impl->length + length;
    impl->ensureCapacity(newLength);
    for (int i = 0; i < length; ++i) {
        impl->value[impl->length++] = value->charAt(i);
    }
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppend(const CharSequence* value, int start, int end) {

    if (value == NULL) {
        const char* nullString = "null";
        doAppend(nullString, start, end - start);
        return;
    }

    int arrayLength = value->length();

    if ((start | end) < 0 || start > end || end > arrayLength) {
        throw ArrayIndexOutOfBoundsException(__FILE__, __LINE__, "Invalid offset or length value given.");
    }

    int length = end - start;

    if (length == 0) {
        return;
    }

    int newLength = impl->length + length;
    impl->ensureCapacity(newLength);

    for (int i = start; i < end; ++i) {
        impl->value[impl->length++] = value->charAt(i);
    }
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppend(const std::string& value) {

    int length = (int) value.length();
    int newLength = impl->length + length;
    impl->ensureCapacity(newLength);

    for (int i = 0; i < length; ++i) {
        impl->value[impl->length++] = value.at(i);
    }
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppend(const String& value) {

    int length = value.length();
    int newLength = impl->length + length;
    impl->ensureCapacity(newLength);

    for (int i = 0; i < length; ++i) {
        impl->value[impl->length++] = value.charAt(i);
    }

    // TODO direct access: string._getChars(0, length, value, count);
    // impl->length = newLength;
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doAppend(const AbstractStringBuilder& value) {

}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doDeleteRange(int start, int end) {

    // This method is specified not to throw if the end index is >= length(), as
    // long as it's >= start. This means we have to clamp it to count here.
    if (end > impl->length) {
        end = impl->length;
    }

    if (start < 0 || start > impl->length || start > end) {
        throw StringIndexOutOfBoundsException(__FILE__, __LINE__, "Invalid start index: %d", start);
    }

    // This method is defined to throw only if start > count and start == count is a NO-OP
    // Since 'end' is already a clamped value, that case is handled here.
    if (end == start) {
        return;
    }

    // At this point we know for sure that end > start.
    int length = impl->length - end;
    if (length >= 0) {
        if (!impl->shared) {
            System::arraycopy(impl->value.get(), end, impl->value.get(), start, length);
        } else {
            ArrayPointer<char> newValue(impl->value.length());
            System::arraycopy(impl->value.get(), 0, newValue.get(), 0, start);
            System::arraycopy(impl->value.get(), end, newValue.get(), start, length);
            impl->value = newValue;
            impl->shared = false;
        }
    }
    impl->length -= end - start;
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::doDeleteCharAt(int index) {
    if (index < 0 || index >= impl->length) {
        throw StringIndexOutOfBoundsException(__FILE__, __LINE__, "Invalid index: %d", index);
    }

    doDeleteRange(index, index + 1);
}

////////////////////////////////////////////////////////////////////////////////
int AbstractStringBuilder::capacity() const {
    return impl->capacity();
}

////////////////////////////////////////////////////////////////////////////////
char AbstractStringBuilder::charAt(int index) const {
    if (index < 0 || index >= impl->length) {
        throw StringIndexOutOfBoundsException(__FILE__, __LINE__, index);
    }

    return impl->value[index];
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::ensureCapacity(int minCapacity) {
    if (minCapacity > impl->value.length() - 1) {
        impl->enlargeBuffer(minCapacity);
    }
}

////////////////////////////////////////////////////////////////////////////////
int AbstractStringBuilder::length() const {
    return impl->length;
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::setCharAt(int index, char value) {

    if (index < 0) {
        throw ArrayIndexOutOfBoundsException(__FILE__, __LINE__, "Index < 0: %d", index);
    }

    if (index > impl->length) {
        throw ArrayIndexOutOfBoundsException(__FILE__, __LINE__, "Index > length(): %d", index);
    }

    if (impl->shared) {
        ArrayPointer<char> newValue(impl->value.length());
        System::arraycopy(impl->value.get(), 0, newValue.get(), 0, impl->length);
        impl->value = newValue;
        impl->shared = false;
    }

    impl->value[index] = value;
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::setLength(int length) {

    if (length < 0) {
        throw StringIndexOutOfBoundsException(__FILE__, __LINE__, "length < 0: %d", length);
    }

    if (length > impl->value.length() - 1) {
        impl->enlargeBuffer(length);
    } else {
        if (impl->shared) {
            ArrayPointer<char> newValue(impl->value.length());
            System::arraycopy(impl->value.get(), 0, newValue.get(), 0, impl->length);
            impl->value = newValue;
            impl->shared = false;
        } else {
            if (impl->length < length) {
                Arrays::fill(impl->value.get(), impl->value.length(), impl->length, length, (char) 0);
            }
        }
    }
    impl->length = length;
}

////////////////////////////////////////////////////////////////////////////////
String AbstractStringBuilder::toString() const {

    // TODO optimize so that internal data can be shared with the returned String
    //      and discarded only after a new mutating method call is made.
    //      ensure the shared flag is set once we do this.

    return String(impl->value.get(), 0, impl->length);
}

////////////////////////////////////////////////////////////////////////////////
void AbstractStringBuilder::trimToSize() {
    if (impl->length < (impl->value.length() - 1)) {
        ArrayPointer<char> newValue(impl->length + 1);
        System::arraycopy(impl->value.get(), 0, newValue.get(), 0, impl->length);
        impl->value = newValue;
        impl->shared = false;
    }
}
