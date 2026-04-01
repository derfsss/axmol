#include "platform/amigaos4/FileUtils-amigaos4.h"
#include "platform/amigaos4/Application-amigaos4.h"
#include "platform/Common.h"
#include "base/Macros.h"
#include "base/UTF8.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

using namespace std;

namespace ax
{

std::string FileUtilsAmigaOS4::s_exeName;

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsAmigaOS4();
        if (!s_sharedFileUtils->init())
        {
            delete s_sharedFileUtils;
            s_sharedFileUtils = nullptr;
            AXLOGE("ERROR: Could not init FileUtilsAmigaOS4");
        }
    }
    return s_sharedFileUtils;
}

FileUtilsAmigaOS4::FileUtilsAmigaOS4() {}

bool FileUtilsAmigaOS4::init()
{
    // On AmigaOS4, PROGDIR: always refers to the application directory.
    // For cross-compiled testing, use the current working directory.
    if (s_exeDir.empty())
    {
        char cwd[4096];
        if (getcwd(cwd, sizeof(cwd)))
        {
            s_exeDir = cwd;
            if (!s_exeDir.empty() && s_exeDir.back() != '/')
                s_exeDir += '/';
        }
        else
        {
            s_exeDir = "./";
        }
        s_exeName = "LordsOfMidnight";
    }

    _defaultResRootPath = s_exeDir;

    // Writable path: use application directory for now
    _writablePath = s_exeDir;

    return FileUtils::init();
}

string FileUtilsAmigaOS4::getWritablePath() const
{
    return getNativeWritableAbsolutePath();
}

std::string FileUtilsAmigaOS4::getNativeWritableAbsolutePath() const
{
    struct stat st;
    if (stat(_writablePath.c_str(), &st) != 0 || !S_ISDIR(st.st_mode))
    {
        mkdir(_writablePath.c_str(), 0744);
    }
    return _writablePath;
}

bool FileUtilsAmigaOS4::isFileExistInternal(std::string_view path) const
{
    struct stat sts;
    return (stat(path.data(), &sts) == 0) && S_ISREG(sts.st_mode);
}

}
