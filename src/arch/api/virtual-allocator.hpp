#ifndef __ANARCH_API_VIRTUAL_ALLOCATOR_HPP__
#define __ANARCH_API_VIRTUAL_ALLOCATOR_HPP__

#include <anarch/stddef>
#include <anarch/types>
#include <anarch/new>
#include <ansa/nocopy>

namespace anarch {

class VirtualAllocator : public ansa::NoCopy {
public:
  virtual bool Alloc(void *& addr, size_t size) = 0; // @noncritical
  virtual void Free(void * addr) = 0; // @noncritical
  virtual bool Owns(void * ptr) = 0; // @noncritical
  
  template <typename T, typename... Args>
  T * New(Args... args) {
    void * buf;
    if (!Alloc(buf, sizeof(T))) return NULL;
    return new(buf) T(args...);
  }
  
  template <typename T>
  void Delete(T * ptr) {
    ptr->~T();
    Free((void *)ptr);
  }
};

}

#endif
