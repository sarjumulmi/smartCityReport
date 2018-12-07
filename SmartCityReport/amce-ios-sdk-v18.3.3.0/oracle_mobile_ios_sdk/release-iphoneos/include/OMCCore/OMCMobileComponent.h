//
//  OMCMobileComponent.h
//  OMCCore
//
//  Copyright © 2017 Oracle. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OMCCore.h"
@class OMCServiceProxy;
@class OMCMobileManager;

NS_ASSUME_NONNULL_BEGIN

/**
 A mobile component holds the settings that allow a service proxy
 to communicate with a mobile suite server.
 */
@interface OMCMobileComponent : NSObject

/**
 The mobile component's manager.
 */
@property (readonly) OMCMobileManager* manager;

/**
 The mobile component's name, as specified by the OMC property list file
 (`OMC.plist`). The default name is determined by the implementation class.
 */
@property (readonly) NSString* name;

/**
 The mobile component's properties, as specified by the OMC property list file
 (`OMC.plist`).
 */
@property (readonly) NSDictionary<NSString*, id>* properties;


#pragma mark - base URL

/**
 The mobile component's base URL, upon which requests such as HTTP URLs are
 built. Typically, this URL is set via the OMC property list file (`OMC.plist`)
 and is in the form `http://<host>:<port>`.
 */
@property (readonly) NSURL* baseURL;

/**
 The mobile component's path, which is appended to the `baseURL` to
 form the `url`. The mobile component path is determined by
 the subclass.
 */
@property (readonly) NSString* path;

/**
 The mobile component's URL, upon which requests such as HTTP URLs are
 built. This URL is built by appending the current `path`
 to the current `baseURL`.
 */
@property (readonly) NSURL* url;

/**
 The mobile component's OAuth scope.
 */
@property (readonly) NSString* oAuthScope;

/**
 Completion handler used when building a URL request that may require a network
 call (e.g. to retrieve an authorization token).
 */
typedef void (^OMCURLRequestCompletionBlock)(NSMutableURLRequest* _Nullable urlRequest, NSError* _Nullable error);


#pragma mark - OAuth token endpoint URL

/**
 The mobile component's OAuth token end point URL, which is used
 to acquire OAuth tokens, if necessary.
 */
@property (readonly, nullable) NSURL* oAuthTokenEndPointURL;


#pragma mark - service proxies

/**
 Returns the receiver's instance of the specified service proxy, if present.
 If the specified service proxy is not present, creates it via reflection and
 returns the new instance.
 @param serviceProxyClass The type of service proxy.
 @warning Raises an `NSInvalidArgumentException` if `serviceProxyClass` is `nil`.
 */
- (nullable OMCServiceProxy*)serviceProxyForClass:(Class)serviceProxyClass;

/**
 Removes the specified service proxy from the receiver.
 
 Does nothing if the receiver does not contain `serviceProxy`.
 @param serviceProxy The service proxy.
 @warning Raises an `NSInvalidArgumentException` if `serviceProxy` is `nil`.
 */
- (void)removeServiceProxy:(OMCServiceProxy*)serviceProxy;

/**
 Removes the receiver's instance of the specified service proxy.
 
 Does nothing if the receiver does not contain the specified service proxy.
 @param serviceProxyClass The type of service proxy.
 @warning Raises an `NSInvalidArgumentException` if `serviceProxyClass` is `nil`.
 */
- (void)removeServiceProxyForClass:(Class)serviceProxyClass;

@end


#pragma mark - constants

/**
 The mobile component `name` property name.
 */
extern NSString* const OMCMobileComponentNamePropertyName;

/**
 The mobile component `baseURL` property name.
 */
extern NSString* const OMCMobileComponentBaseURLPropertyName;

/**
 The mobile component `allowsCellularAccess` property name.
 */
extern NSString* const OMCMobileComponentAllowsCellularAccessPropertyName;

/**
 The mobile component `allowsCellularAccess` default value (`YES`).
 */
extern BOOL const OMCMobileComponentAllowsCellularAccessDefault;

/**
 The mobile component `networkConnectionTimeout` property name.
 */
extern NSString* const OMCMobileComponentNetworkConnectionTimeoutPropertyName;

/**
 The mobile component `networkConnectionTimeout` default value (`60`).
 */
extern NSTimeInterval const OMCMobileComponentNetworkConnectionTimeoutDefault;

NS_ASSUME_NONNULL_END
