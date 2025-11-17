#include "Account.h"
#include <ostream>

namespace MiniBank {

std::ostream& operator<<(std::ostream& os, const Account& a)
{
    // stream standard C++ types only
    os << "Account[" << a.accountNumber << "] owner=\"" << a.owner << "\" balance=" << a.balance;
    return os;
}

} // namespace MiniBank
