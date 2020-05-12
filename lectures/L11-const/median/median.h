#ifndef BOUNDED_VECTOR_H // include guard
#define BOUNDED_VECTOR_H

#include <cstddef>
#include <iostream>
#include <vector>

namespace mycollection {
    template <typename T, typename Compare = std::less<T>>
    class StreamingMedianTracker {
    public:
        using const_reference = const T&;

        StreamingMedianTracker(const Compare& comp = Compare());
        void insert(const_reference elem);
        const_reference getMedian() const;
        
        template <typename InputIt>
        void insert(InputIt first, InputIt last);

    private:
        /* TODO: add any private members (variables) here */
        std::vector<T> _elems;
        Compare _comp;
    };

    template <typename T, typename Compare>
    StreamingMedianTracker<T, Compare>::StreamingMedianTracker(const Compare& comp) : _elems(), _comp(comp) {}
    template <typename T, typename Compare>
    void StreamingMedianTracker<T, Compare>::insert(const_reference element) {
        auto pos = std::lower_bound(_elems.begin(), _elems.end(), element, _comp);
        _elems.insert(pos, element);
    }

    template <typename T, typename Compare>
    typename StreamingMedianTracker<T, Compare>::const_reference
    StreamingMedianTracker<T, Compare>::getMedian() const {
        return _elems[_elems.size()/2];
    }

    template <typename T, typename Compare>
    template <typename InputIt>
    void StreamingMedianTracker<T, Compare>::insert(InputIt first, InputIt last) {
        std::for_each(first, last, [this](const auto& elem) {return this->insert(elem); });
    }


}

#endif /* STREAMING_MEDIAN_TRACKER */