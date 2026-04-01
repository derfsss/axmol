#include "platform/amigaos4/Application-amigaos4.h"
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include <thread>
#include "base/Director.h"
#include "base/Utils.h"
#include "platform/FileUtils.h"

namespace ax
{

Application* Application::sm_pSharedApplication = nullptr;

Application::Application() : _animationInterval(16666667)
{
    AX_ASSERT(!sm_pSharedApplication);
    sm_pSharedApplication = this;
}

Application::~Application()
{
    AX_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = nullptr;
}

int Application::run()
{
    initGLContextAttrs();
    if (!applicationDidFinishLaunching())
    {
        return 0;
    }

    std::chrono::steady_clock::time_point lastTime{};

    auto director = Director::getInstance();
    auto glView   = director->getGLView();

    glView->retain();

    while (!glView->windowShouldClose())
    {
        lastTime = std::chrono::steady_clock::now();

        director->mainLoop();
        glView->pollEvents();

        auto interval = std::chrono::steady_clock::now() - lastTime;
        if (interval < _animationInterval)
        {
            auto waitDuration = _animationInterval - interval;
            std::this_thread::sleep_for(waitDuration);
        }
        else
        {
            std::this_thread::yield();
        }
    }

    if (glView->isOpenGLReady())
    {
        director->end();
        director->mainLoop();
        director = nullptr;
    }
    glView->release();
    return EXIT_SUCCESS;
}

void Application::setAnimationInterval(float interval)
{
    _animationInterval =
        std::chrono::nanoseconds{static_cast<std::chrono::nanoseconds::rep>(std::nano::den * interval)};
}

Application::Platform Application::getTargetPlatform()
{
    return Platform::Linux;  // closest match; no Platform::AmigaOS4 enum value yet
}

std::string Application::getVersion()
{
    return "";
}

bool Application::openURL(std::string_view url)
{
    // AmigaOS4: could use IDOS->SystemTags("open URL ...") in the future
    return false;
}

Application* Application::getInstance()
{
    AX_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

Application* Application::sharedApplication()
{
    return Application::getInstance();
}

const char* Application::getCurrentLanguageCode()
{
    static char code[3] = {0};
    char* pLanguageName = getenv("LANG");
    if (!pLanguageName)
        return "en";
    strtok(pLanguageName, "_");
    if (!pLanguageName)
        return "en";
    strncpy(code, pLanguageName, 2);
    code[2] = '\0';
    return code;
}

LanguageType Application::getCurrentLanguage()
{
    char* pLanguageName = getenv("LANG");
    if (!pLanguageName)
    {
        return LanguageType::ENGLISH;
    }
    strtok(pLanguageName, "_");
    if (!pLanguageName)
    {
        return LanguageType::ENGLISH;
    }

    return utils::getLanguageTypeByISO2(pLanguageName);
}

}
