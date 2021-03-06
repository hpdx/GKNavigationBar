//
//  GKNavigationBarDefine.h
//  GKNavigationBar
//
//  Created by QuintGao on 2019/10/27.
//  Copyright © 2019 QuintGao. All rights reserved.
//

#ifndef GKNavigationBarDefine_h
#define GKNavigationBarDefine_h

#import <objc/runtime.h>

// 屏幕相关
#define GK_SCREEN_WIDTH         [UIScreen mainScreen].bounds.size.width
#define GK_SCREEN_HEIGHT        [UIScreen mainScreen].bounds.size.height

// 判断是否是刘海屏
#define GK_NOTCHED_SCREEN      ([UIScreen instancesRespondToSelector:@selector(currentMode)] ?\
(\
CGSizeEqualToSize(CGSizeMake(375, 812),[UIScreen mainScreen].bounds.size)\
||\
CGSizeEqualToSize(CGSizeMake(812, 375),[UIScreen mainScreen].bounds.size)\
||\
CGSizeEqualToSize(CGSizeMake(414, 896),[UIScreen mainScreen].bounds.size)\
||\
CGSizeEqualToSize(CGSizeMake(896, 414),[UIScreen mainScreen].bounds.size))\
:\
NO)

// 顶部安全区域高度
#define GK_SAFEAREA_TOP             (GK_NOTCHED_SCREEN ? 24.0f : 0.0f)
// 底部安全区域高度
#define GK_SAFEAREA_BTM             (GK_NOTCHED_SCREEN ? 34.0f : 0.0f)
// 状态栏高度
#define GK_STATUSBAR_HEIGHT         (GK_NOTCHED_SCREEN ? 44.0f : 20.0f)
// 导航栏高度
#define GK_NAVBAR_HEIGHT            44.0f
// 状态栏+导航栏高度
#define GK_STATUSBAR_NAVBAR_HEIGHT  (GK_STATUSBAR_HEIGHT + GK_NAVBAR_HEIGHT)
// tabbar高度
#define GK_TABBAR_HEIGHT            (GK_NOTCHED_SCREEN ? 83.0f : 49.0f)

// 设备版本号，只获取到第二级的版本号，例如 10.3.1 只会获取到10.3
#define GKDeviceVersion             [UIDevice currentDevice].systemVersion.doubleValue

// 导航栏间距，用于不同控制器之间的间距
static const CGFloat GKNavigationBarItemSpace = -1;

// 返回按钮样式
typedef NS_ENUM(NSUInteger, GKNavigationBarBackStyle) {
    GKNavigationBarBackStyleNone,   // 无返回按钮
    GKNavigationBarBackStyleBlack,  // 黑色返回按钮
    GKNavigationBarBackStyleWhite   // 白色返回按钮
};

// 使用static inline创建静态内联函数，方便调用，新方法默认自带前缀gk_
static inline void gk_swizzled_instanceMethod(Class oldClass, NSString *oldSelector, Class newClass) {
    NSString *newSelector = [NSString stringWithFormat:@"gk_%@", oldSelector];
    
    SEL originalSelector = NSSelectorFromString(oldSelector);
    SEL swizzledSelector = NSSelectorFromString(newSelector);
    
    Method originalMethod = class_getInstanceMethod(oldClass, NSSelectorFromString(oldSelector));
    Method swizzledMethod = class_getInstanceMethod(newClass, NSSelectorFromString(newSelector));
    
    BOOL isAdd = class_addMethod(oldClass, originalSelector, method_getImplementation(swizzledMethod), method_getTypeEncoding(swizzledMethod));
    if (isAdd) {
        class_replaceMethod(newClass, swizzledSelector, method_getImplementation(originalMethod), method_getTypeEncoding(originalMethod));
    }else {
        method_exchangeImplementations(originalMethod, swizzledMethod);
    }
}

#endif /* GKNavigationBarDefine_h */
