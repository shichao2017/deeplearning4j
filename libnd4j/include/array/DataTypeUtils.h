/*******************************************************************************
 * Copyright (c) 2015-2018 Skymind, Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

//
// @author raver119@gmail.com
//

#ifndef DATATYPEUTILS_H
#define DATATYPEUTILS_H

#include <types/float16.h>
#include <array/DataType.h>
#include <graph/generated/array_generated.h>
#include <op_boilerplate.h>

namespace nd4j {
    class DataTypeUtils {
    public:
        static int asInt(DataType type);
        static DataType fromInt(int dtype);
        static DataType fromFlatDataType(nd4j::graph::DataType dtype);

        template <typename T>
        static DataType fromT();
        static size_t sizeOfElement(DataType type);

        // returns the smallest finite value of the given type
        template <typename T>
        FORCEINLINE static _CUDA_HD T min();

        // returns the largest finite value of the given type
        template <typename T>
        FORCEINLINE static _CUDA_HD T max();

        // returns the difference between 1.0 and the next representable value of the given floating-point type 
        template <typename T>
        FORCEINLINE static T eps();

        FORCEINLINE static size_t sizeOf(DataType type);
    };


//////////////////////////////////////////////////////////////////////////
///// IMLEMENTATION OF INLINE METHODS ///// 
//////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
FORCEINLINE size_t DataTypeUtils::sizeOf(DataType type) {
    return sizeOfElement(type);
}

// returns the smallest finite value of the given type
template<>
FORCEINLINE _CUDA_HD int DataTypeUtils::min<int>() {
    return 1;
}

template<>
FORCEINLINE _CUDA_HD char DataTypeUtils::min<char>() {
    return 1;
}

template <>
FORCEINLINE _CUDA_HD bool DataTypeUtils::min<bool>() {
    return false;
}

template<>
FORCEINLINE _CUDA_HD Nd4jLong DataTypeUtils::min<Nd4jLong>() {
    return 1L;
}

template<>
FORCEINLINE _CUDA_HD uint64_t DataTypeUtils::min<uint64_t>() {
    return 1L;
}

template<>
FORCEINLINE _CUDA_HD uint32_t DataTypeUtils::min<uint32_t>() {
    return 1;
}

template<>
FORCEINLINE _CUDA_HD float DataTypeUtils::min<float>() {         
    return 1.175494e-38;    
}

template<>
FORCEINLINE _CUDA_HD float16 DataTypeUtils::min<float16>() {
    return (float16) 6.1035e-05;    
}

template<>
FORCEINLINE _CUDA_HD double DataTypeUtils::min<double>() {       
    return 2.2250738585072014e-308;    
}

///////////////////////////////////////////////////////////////////
// returns the largest finite value of the given type
template <>
FORCEINLINE _CUDA_HD int DataTypeUtils::max<int>() {
    return 2147483647;
}

template <>
FORCEINLINE _CUDA_HD bool DataTypeUtils::max<bool>() {
    return true;
}

template <>
FORCEINLINE _CUDA_HD int8_t DataTypeUtils::max<int8_t>() {
    return 127;
}

template <>
FORCEINLINE _CUDA_HD uint8_t DataTypeUtils::max<uint8_t>() {
    return 255;
}

template <>
FORCEINLINE _CUDA_HD int16_t DataTypeUtils::max<int16_t>() {
    return 32767;
}

template <>
FORCEINLINE _CUDA_HD uint16_t DataTypeUtils::max<uint16_t>() {
    return 65535;
}

template <>
FORCEINLINE _CUDA_HD Nd4jLong DataTypeUtils::max<Nd4jLong>() {
    return 9223372036854775807LL;
}

template <>
FORCEINLINE _CUDA_HD uint32_t DataTypeUtils::max<uint32_t>() {
    return 4294967295;
}

template <>
FORCEINLINE _CUDA_HD Nd4jULong DataTypeUtils::max<Nd4jULong>() {
    return 18446744073709551615LLU;
}

template <>
FORCEINLINE _CUDA_HD float DataTypeUtils::max<float>() {    
    return 3.402823e+38;
}

template <>
FORCEINLINE _CUDA_HD double DataTypeUtils::max<double>() {       
    return 1.7976931348623157E308;   
}

template <>
FORCEINLINE _CUDA_HD float16 DataTypeUtils::max<float16>() {       
    return static_cast<float16>(65504.f);
}

///////////////////////////////////////////////////////////////////
// returns the difference between 1.0 and the next representable value of the given floating-point type 
template <typename T>
FORCEINLINE T DataTypeUtils::eps() {
        if (std::is_same<T, double>::value)
            return std::numeric_limits<double>::epsilon();
        else if (std::is_same<T, float>::value)
            return std::numeric_limits<float>::epsilon();
        else if (std::is_same<T, float16>::value)
            return 0.00097656;    
        else
            return 0;
}


}

#endif //DATATYPEUTILS_H