
#include "libipc/condition.h"

#include "libipc/utility/pimpl.h"
#include "libipc/memory/resource.h"
#include "libipc/platform/detail.h"
#if defined(IPC_OS_WINDOWS_)
#include "libipc/platform/condition_win.h"
#elif defined(IPC_OS_LINUX_)
#include "libipc/platform/condition_linux.h"
#else/*linux*/
#   error "Unsupported platform."
#endif

namespace ipc {
namespace sync {

class condition::condition_ : public ipc::pimpl<condition_> {
public:
    ipc::detail::sync::condition cond_;
};

condition::condition()
    : p_(p_->make()) {
}

condition::condition(char const * name)
    : condition() {
    open(name);
}

condition::~condition() {
    close();
    p_->clear();
}

void const *condition::native() const noexcept {
    return impl(p_)->cond_.native();
}

void *condition::native() noexcept {
    return impl(p_)->cond_.native();
}

bool condition::valid() const noexcept {
    return impl(p_)->cond_.valid();
}

bool condition::open(char const *name) noexcept {
    return impl(p_)->cond_.open(name);
}

void condition::close() noexcept {
    impl(p_)->cond_.close();
}

bool condition::wait(ipc::sync::mutex &mtx, std::uint64_t tm) noexcept {
    return impl(p_)->cond_.wait(mtx, tm);
}

bool condition::notify() noexcept {
    return impl(p_)->cond_.notify();
}

bool condition::broadcast() noexcept {
    return impl(p_)->cond_.broadcast();
}

} // namespace sync
} // namespace ipc
