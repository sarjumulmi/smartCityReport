//
//  OMCMobileBackendServiceProxy.h
//  OMCCore
//
//  Copyright © 2017 Oracle. All rights reserved.
//

#import "OMCServiceProxy.h"
@class OMCMobileBackend;

NS_ASSUME_NONNULL_BEGIN

/**
 Interface to an Oracle Mobile Backend service proxy.
 */
@interface OMCMobileBackendServiceProxy : OMCServiceProxy

/**
 The service proxy's mobile backend.
 */
@property (readonly) OMCMobileBackend* mobileBackend;

@end

NS_ASSUME_NONNULL_END
