//
//  OMCServiceProxy.h
//  OMCCore
//
//  Copyright (c) 2015, Oracle Corp. All rights reserved. 
//

#import <Foundation/Foundation.h>
@class OMCMobileComponent;

NS_ASSUME_NONNULL_BEGIN

/**
 Interface to an OMCe service proxy.
 This is an abstract superclass of the various OMC service proxies.
 */
@interface OMCServiceProxy : NSObject

/**
 The service proxy's mobile component.
 */
@property (readonly) OMCMobileComponent* mobileComponent;

/**
 The service proxy's properties, as specified by the OMC property list file
 (`OMC.plist`).
 */
@property (readonly) NSDictionary<NSString*, id>* properties;

@end

NS_ASSUME_NONNULL_END
