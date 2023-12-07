set(RSL_SRC_FILES_CPLUSPLUS
        Internal.hpp
        portable/Headers.hpp
        portable/Portable.hpp
        log/Log.cpp
        log/Log.hpp
        memory/ByteAllocator.hpp
        memory/HeapAllocator.hpp
        container/base/StaticArray.hpp
        container/base/StaticList.hpp
        container/base/DynamicArray.hpp
        container/base/DynamicList.hpp
        container/Queue.hpp
        container/Deque.hpp
        container/Stack.hpp
        stream/Pipeline.hpp
        stream/Pipeline.hpp
        utils/Types.hpp
        utils/Utils.hpp
        stream/filter/ConstrainFilter.hpp stream/filter/MedianFilter.hpp stream/filter/AverageFilter.hpp stream/filter/MedianAverageFilter.hpp stream/filter/ConstrainedAverageFilter.hpp stream/filter/IIRFilter.hpp stream/filter/KalmanFilter.hpp stream/filter/WeightedAverageFilter.hpp stream/filter/JitterFilter.hpp stream/filter/ConstrainedJitterFilter.hpp)


add_library(RSL STATIC ${RSL_SRC_FILES_CPLUSPLUS})
set_target_properties(RSL PROPERTIES LINKER_LANGUAGE CXX)