#include <cstdlib>
#include <ctime>
#include <CCGLView.h>

#include "cocos2d.h"
#include "AppDelegate.h"
#include "HillClimbLayer.h"
#include "HillClimbUtility.h"

namespace hillclimb {

    void AppDelegate::initGLContextAttrs() {
        GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
        cocos2d::GLView::setGLContextAttrs(glContextAttrs);
    }

    static int register_all_packages() {
        return 0;
    }

    bool AppDelegate::applicationDidFinishLaunching() {
        auto director = cocos2d::Director::getInstance();
        auto glview = director->getOpenGLView();
        if(!glview) {
#if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
            glview = cocos2d::GLViewImpl::createWithRect("SampleGame", cocos2d::Rect(0, 0, DESIGN_RESOLUTION_SIZE.width, DESIGN_RESOLUTION_SIZE.height));
#else
            glview = cocos2d::GLViewImpl::create("SampleGame");
#endif
            director->setOpenGLView(glview);
        }
    
        director->setDisplayStats(true);
        director->setAnimationInterval(1.0f / 60);
        glview->setDesignResolutionSize(DESIGN_RESOLUTION_SIZE.width, DESIGN_RESOLUTION_SIZE.height, ResolutionPolicy::NO_BORDER);

        auto frameSize = glview->getFrameSize();
        if (frameSize.height > MEDIUM_RESOLUTION_SIZE.height) {        
            director->setContentScaleFactor(MIN(LARGE_RESOLUTION_SIZE.height / DESIGN_RESOLUTION_SIZE.height,
                                                LARGE_RESOLUTION_SIZE.width / DESIGN_RESOLUTION_SIZE.width));
        } else if (frameSize.height > SMALL_RESOLUTION_SIZE.height)  {        
            director->setContentScaleFactor(MIN(MEDIUM_RESOLUTION_SIZE.height / DESIGN_RESOLUTION_SIZE.height,
                                                MEDIUM_RESOLUTION_SIZE.width / DESIGN_RESOLUTION_SIZE.width));
        } else {        
            director->setContentScaleFactor(MIN(SMALL_RESOLUTION_SIZE.height / DESIGN_RESOLUTION_SIZE.height,
                                                SMALL_RESOLUTION_SIZE.width / DESIGN_RESOLUTION_SIZE.width));
        }
        register_all_packages();
        std::srand(std::time(NULL));

        auto scene = HillClimbLayer::createScene();
        director->runWithScene(scene);

        return true;
    }

    void AppDelegate::applicationDidEnterBackground() {
        cocos2d::Director::getInstance()->stopAnimation();
    }

    void AppDelegate::applicationWillEnterForeground() {
        cocos2d::Director::getInstance()->startAnimation();
    }
}
