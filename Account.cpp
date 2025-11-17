#include "Account.h"
#include <ostream>

namespace MiniBank {

std::ostream& operator<<(std::ostream& os, const Account& a)
{
    os << "Account[" << a.getAccountNumber() << "] owner=\""
       << a.getOwner() << "\" balance=" << a.getBalance();
    return os;
}

} // namespace MiniBank
