#pragma once

#include "platform/Common.h"
#include "platform/ApplicationBase.h"
#include <string>
#include <chrono>

namespace ax
{
class Rect;

class Application : public ApplicationBase
{
public:
    Application();
    virtual ~Application();

    virtual void setAnimationInterval(float interval) override;

    int run();

    static Application* getInstance();
#ifndef AX_CORE_PROFILE
    AX_DEPRECATED(2.1) static Application* sharedApplication();
#endif

    virtual LanguageType getCurrentLanguage() override;
    virtual const char* getCurrentLanguageCode() override;
    virtual std::string getVersion() override;
    virtual bool openURL(std::string_view url) override;
    virtual Platform getTargetPlatform() override;

protected:
    std::chrono::nanoseconds _animationInterval;
    std::string _resourceRootPath;

    static Application* sm_pSharedApplication;
};

}
