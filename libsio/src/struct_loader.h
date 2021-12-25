#ifndef SIO_STRUCT_LOADER
#define SIO_STRUCT_LOADER

#include <map>

#include "sio/log.h"
#include "sio/check.h"
#include "sio/ptr.h"
#include "sio/str.h"
#include "sio/vec.h"
#include "sio/json.h"

namespace sio {
class StructLoader {
 public:
  void Load(const Json& j) {
    for (const auto& kv : bool_map_) {
      auto& k = kv.first;
      auto& v = kv.second;
      const Json *node = FindEntry(j, k);
      if (node) {
        *v = node->get<bool>();
      }
    }

    for (const auto& kv : int_map_) {
      auto& k = kv.first;
      auto& v = kv.second;
      const Json *node = FindEntry(j, k);
      if (node) {
        *v = node->get<int>();
      }
    }

    for (const auto& kv : float_map_) {
      auto& k = kv.first;
      auto& v = kv.second;
      const Json *node = FindEntry(j, k);
      if (node) {
        *v = node->get<float>();
      }
    }

    for (const auto& kv : string_map_) {
      auto& k = kv.first;
      auto& v = kv.second;
      const Json *node = FindEntry(j, k);
      if (node) {
        *v = node->get<Str>();
      }
    }
  }


  void AddEntry(const StrView prefix, const StrView field, bool* p) {
    bool_map_[absl::StrCat(prefix, field)] = p;
  }

  void AddEntry(const StrView prefix, const StrView field, int* p) {
    int_map_[absl::StrCat(prefix, field)] = p;
  }

  void AddEntry(const StrView prefix, const StrView field, float* p) {
    float_map_[absl::StrCat(prefix, field)] = p;
  }

  void AddEntry(const StrView prefix, const StrView field, Str* p) {
    string_map_[absl::StrCat(prefix, field)] = p;
  }


  void Print() {
    SIO_INFO << "--------------------";
    for (const auto& kv : bool_map_) {
      SIO_INFO << kv.first << " : " << *kv.second;
    }
    for (const auto& kv : int_map_) {
      SIO_INFO << kv.first << " : " << *kv.second;
    }
    for (const auto& kv : float_map_) {
      SIO_INFO << kv.first << " : " << *kv.second;
    }
    for (const auto& kv : string_map_) {
      SIO_INFO << kv.first << " : " << *kv.second;
    }
    SIO_INFO << "====================";
  }


 private:
  static Optional<const Json*> FindEntry(const Json& json, const StrView entry) {
    // longest path match
    Vec<Str> fields = absl::StrSplit(entry, ".", absl::SkipWhitespace());
    const Json *node = &json;
    int k = 0;
    SIO_CHECK("Loop invariant: the path from root to node matches fields[0,k)");
    while(k != fields.size()) {
      Str& field = fields[k];
      if (node->contains(field)) {
        node = &((*node)[field]);
        ++k;
      } else {
        break;
      }
    }

    if (k == fields.size()) { // successful full match
      return node;
    } else { // non-terminal partial match
      return nullptr;
    }
  }

 private:
  std::map<Str, bool*> bool_map_;
  std::map<Str, int*> int_map_;
  std::map<Str, float*> float_map_;
  std::map<Str, Str*> string_map_;

}; // End of class StructLoader
}  // End of namespace sio

#endif
