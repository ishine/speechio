#ifndef SIO_BASE_MAP_H
#define SIO_BASE_MAP_H

#include <unordered_map>
#include "absl/container/flat_hash_map.h"

namespace sio {

template <
    class K,
    class V,
    class Hash = absl::container_internal::hash_default_hash<K>,
    class Eq = absl::container_internal::hash_default_eq<K>,
    class Allocator = std::allocator<std::pair<const K, V>>
>
using map = absl::flat_hash_map<K, V, Hash, Eq, Allocator>;


template <
    class K,
    class V,
    class Hash = std::hash<K>,
    class Eq = std::equal_to<K>,
    class Allocator = std::allocator<std::pair<const K, V>>
>
using gmap = std::unordered_map<K, V, Hash, Eq, Allocator>;

};

#endif
