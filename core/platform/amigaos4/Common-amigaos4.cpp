#include "platform/Common.h"
#include "platform/amigaos4/StdC-amigaos4.h"
#include "base/Logging.h"

namespace ax
{

AlertResult showAlert(std::string_view msg, std::string_view title, AlertStyle style)
{
    AXLOGE("{}: {}", title, msg);
    return AlertResult::Ok;
}

}
