#ifndef __EASTL_ALLOCATOR_COMM
#define __EASTL_ALLOCATOR_COMM

#include <comm/alloc/commalloc.h>
#include <comm/alloc/memtrack.h>

namespace eastl {

    class allocator_comm {
    public:
        allocator_comm(const char* = NULL)
        { }

        allocator_comm(const allocator_comm&)
        { }

        allocator_comm(const allocator_comm&, const char*)
        { }

        allocator_comm& operator=(const allocator_comm&)
        {
            return *this;
        }

        bool operator==(const allocator_comm&)
        {
            return true;
        }

        bool operator!=(const allocator_comm&)
        {
            return false;
        }

        void* allocate(size_t n, int /*flags*/ = 0, const char *trackname = "eastl_comm_alocator.untyped")
        {
            void *p = dlmalloc(n);
            MEMTRACK_ALLOC(trackname, dlmalloc_usable_size(p));
            return p;
        }

        void* allocate(size_t n, size_t alignment, size_t alignmentOffset, int /*flags*/ = 0, const char *trackname = "eastl_comm_alocator.untyped")
        {
            void *p = dlmemalign(alignment, n);
            MEMTRACK_ALLOC(trackname, dlmalloc_usable_size(p));
            return p;
        }

        void deallocate(void* p, size_t /*n*/, const char *trackname = "eastl_comm_alocator.untyped")
        {
            if (!p) {
                return;
            }

            MEMTRACK_FREE(trackname, dlmalloc_usable_size(p));
            dlfree(p);
        }

        const char* get_name() const
        {
            return "allocator_comm";
        }

        void set_name(const char*)
        { }
    };
} // namespace eastl

#endif // __EASTL_ALLOCATOR_COMM