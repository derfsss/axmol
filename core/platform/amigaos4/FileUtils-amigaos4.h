#pragma once

#include "platform/FileUtils.h"
#include "platform/PlatformMacros.h"
#include "base/Types.h"
#include <string>
#include <vector>

namespace ax
{

class AX_DLL FileUtilsAmigaOS4 : public FileUtils
{
    friend class FileUtils;

protected:
    FileUtilsAmigaOS4();

private:
    std::string _writablePath;

public:
    bool init() override;
    virtual std::string getWritablePath() const override;
    std::string getNativeWritableAbsolutePath() const override;

private:
    virtual bool isFileExistInternal(std::string_view strFilePath) const override;

    static std::string s_exeName;
};

}
