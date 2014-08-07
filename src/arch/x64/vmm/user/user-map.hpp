#ifndef __ANARCH_X64_USER_MAP_HPP__
#define __ANARCH_X64_USER_MAP_HPP__

#include "../page-table.hpp"
#include "free-list.hpp"
#include <anarch/api/user-map>
#include <anarch/lock>

namespace anarch {

namespace x64 {

class UserMap : public anarch::UserMap {
public:
  static const VirtAddr SpaceStart = 0x8000000000L;
  
  UserMap(); // @noncritical
  virtual ~UserMap(); // @noncritical
  
  PageTable & GetPageTable();
  
  // anarch::MemoryMap
  virtual void Set();
  virtual bool Read(PhysAddr *, Attributes *, PhysSize *, VirtAddr);
  virtual bool Map(VirtAddr &, PhysAddr, Size, const Attributes &);
  virtual void MapAt(VirtAddr, PhysAddr, Size, const Attributes &);
  virtual void Unmap(VirtAddr, Size);
  virtual bool Reserve(VirtAddr &, Size);
  virtual void ReserveAt(VirtAddr, Size);
  
  // anarch::UserMap
  virtual void Delete();
  virtual void CopyToKernel(void * dest, VirtAddr start, size_t size);
  virtual void CopyFromKernel(VirtAddr dest, void * start, size_t size);
  
protected:
  void DistInvlpg(VirtAddr start, PhysSize size);
  
  NoncriticalLock lock;
  
  PageTable table;
  FreeList freeList;
};

}

}

#endif