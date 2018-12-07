//
//  OMCMobileBackend.h
//  OMCCore
//
//  Copyright (c) 2015-2017, Oracle Corp. All rights reserved. 
//

#import <Foundation/Foundation.h>
#import "OMCMobileComponent.h"
@class OMCDiagnostics;
@class OMCAuthorization;
@class OMCCustomCodeClient;
@class OMCAppConfig;

NS_ASSUME_NONNULL_BEGIN

/**
 A mobile backend holds the settings that allow a mobile backend service proxy
 to communicate with an OMCe mobile backend server.
 */
@interface OMCMobileBackend : OMCMobileComponent

/**
 The mobile backend's diagnostics.
 */
@property (readonly) OMCDiagnostics* diagnostics;

/**
 The mobile backend's authorization.
 */
@property (readonly) OMCAuthorization* authorization;


#pragma mark - base URL requests

/**
 Builds a URL request configured with a URL with the specified path,
 relative to the mobile backend's base URL and path.
 
 The request will be configured with the appropriate OMCe HTTP headers:
 
 - authorization
 - diagnostics device ID
 - diagnostics session ID
 - diagnostics timestamp
 
 @param relativePath The request's URL path, relative to the mobile backend's URL.
 @param completionHandler The completion block invoked when the URL request
 is built or an error occurs.
 @see -[OMCMobileComponent baseURL]
 @see -[OMCMobileComponent path]
 @see -[OMCMobileComponent url]
 */
- (void)buildURLRequestWithPath:(nullable NSString*)relativePath
              completionHandler:(OMCURLRequestCompletionBlock)completionHandler;

/**
 Sets the receiver's HTTP headers on the specified URL request.
 The headers will include:
 
 - authorization
 - diagnostics device ID
 - diagnostics session ID
 - diagnostics timestamp

 Call this method to ensure that all the required OMCe headers are set
 appropriately.
 
 @param request A URL request.
 @param completionHandler The completion block invoked once the mobile
 backend's HTTP headers have been added to the URL request
 or an error occurs.
 @warning Raises an `NSInvalidArgumentException` if `request` is `nil`.
 */
- (void)setHTTPHeadersOnURLRequest:(NSMutableURLRequest*)request
                 completionHandler:(OMCErrorCompletionBlock)completionHandler;

/**
 Builds an anonymous authorization URL request configured with a URL with the specified path,
 relative to the mobile backend's base URL and path.
 
 The request will be configured with the appropriate OMCe HTTP headers:
 
 - authorization (anonymous)
 - diagnostics device ID
 - diagnostics session ID
 - diagnostics timestamp
 
 @param relativePath The request's URL path, relative to the mobile backend's URL.
 @param completionHandler The completion block invoked when the URL request
 is built or an error occurs.
 @see -[OMCMobileComponent baseURL]
 @see -[OMCMobileComponent path]
 @see -[OMCMobileComponent url]
 */
- (void)buildAnonymousAuthorizationURLRequestWithPath:(nullable NSString*)relativePath
                                    completionHandler:(OMCURLRequestCompletionBlock)completionHandler;

/**
 Sets the receiver's anonymous authorization HTTP headers on the specified URL request.
 The headers will include:
 
 - authorization (anonymous)
 - diagnostics device ID
 - diagnostics session ID
 - diagnostics timestamp
 
 Call this method to ensure that all the required OMCe headers are set
 appropriately.
 
 @param request A URL request.
 @param completionHandler The completion block invoked once the mobile
 backend's HTTP headers have been added to the URL request
 or an error occurs.
 @warning Raises an `NSInvalidArgumentException` if `request` is `nil`.
 */
- (void)setAnonymousAuthorizationHTTPHeadersOnURLRequest:(NSMutableURLRequest*)request
                                       completionHandler:(OMCErrorCompletionBlock)completionHandler;


#pragma mark - platform

/**
 The mobile backend's platform path, which is appended to the `url` to
 form the `platformURL`.
 The platform path is held by `OMCMobileBackendPlatformPath`.
 */
@property (readonly) NSString* platformPath;

/**
 The mobile backend's platform URL, upon which requests such as HTTP URLs are
 built. This URL is built by appending the `platformPath` to the `url`.
 */
@property (readonly) NSURL* platformURL;

/**
 Builds a URL request configured with a URL with the specified path,
 relative to the mobile backend's platform URL.
 
 The request will be configured with the appropriate OMCe HTTP headers:
 
 - authorization
 - diagnostics device ID
 - diagnostics session ID
 - diagnostics timestamp
 
 @param relativePath The request's URL path, relative to the mobile backend's platform URL.
 @param completionHandler The completion block invoked when the URL request
 is built or an error occurs.
 @see platformPath
 @see platformURL
 */
- (void)buildPlatformURLRequestWithPath:(nullable NSString*)relativePath
                      completionHandler:(OMCURLRequestCompletionBlock)completionHandler;

/**
 Builds an anonymous authorization URL request configured with a URL with the specified path,
 relative to the mobile backend's platform URL.
 
 The request will be configured with the appropriate OMCe HTTP headers:
 
 - authorization (anonymous)
 - diagnostics device ID
 - diagnostics session ID
 - diagnostics timestamp
 
 @param relativePath The request's URL path, relative to the mobile backend's platform URL.
 @param completionHandler The completion block invoked when the URL request
 is built or an error occurs.
 @see platformPath
 @see platformURL
 */
- (void)buildAnonymousAuthorizationPlatformURLRequestWithPath:(nullable NSString*)relativePath
                                            completionHandler:(OMCURLRequestCompletionBlock)completionHandler;


#pragma mark - app config

/**
 Completion handler used when loading a mobile backend's application configuration.
 @see -[OMCMobileBackend appConfigWithCompletionHandler:]
 */
typedef void (^OMCAppConfigCompletionBlock)(OMCAppConfig* _Nullable appConfig, NSError* _Nullable error);

/**
 The mobile backend's application configuration path, which is appended to the `platformURL` to
 form the `appConfigURL`.
 The application configuration path is held by `OMCMobileBackendAppConfigPath`.
 */
@property (readonly) NSString* appConfigPath;

/**
 The mobile backend's application configuration URL, upon which requests such as HTTP URLs are
 built. This URL is built by appending the current `appConfigPath`
 to the current `platformURL`.
 */
@property (readonly) NSURL* appConfigURL;

/**
 The mobile backend's application configuration.
 The application configuration will be empty until it is loaded.
 @see appConfigWithCompletionHandler:
 */
@property (readonly) OMCAppConfig* appConfig;

/**
 Loads the receiver's application configuration asynchronously.
 @param completionHandler The completion block invoked when the application configuration
 is loaded or an error occurs.
 */
- (void)appConfigWithCompletionHandler:(OMCAppConfigCompletionBlock)completionHandler;

/**
 Builds an HTTP URL `GET` request configured with a URL with the specified path,
 relative to the mobile backend's application configuration URL.
 
 The request will be configured with the appropriate OMCe HTTP headers:
 
 - diagnostics device ID
 - diagnostics session ID
 - diagnostics timestamp
 - anonymous authorization
 - gzip JSON accept encoding
 
 @param relativePath The request's URL path, relative to the mobile backend's application configuration URL.
 @param completionHandler The completion block invoked when the URL request
 is built or an error occurs.
 @see appConfigURL
 */
- (void)buildAppConfigURLRequestWithPath:(nullable NSString*)relativePath
                       completionHandler:(OMCURLRequestCompletionBlock)completionHandler;


#pragma mark - custom code

/**
 The mobile backend's custom API path, which is appended to the `url` to
 form the `customCodeURL`.
 The custom API path is held by `OMCMobileBackendCustomCodePath`.
 */
@property (readonly) NSString* customCodePath;

/**
 The mobile backend's custom API URL, upon which requests such as HTTP URLs are
 built. This URL is built by appending the current `customCodePath`
 to the current `url`.
 */
@property (readonly) NSURL* customCodeURL;

/**
 The mobile backend's custom code client.
 */
@property (readonly) OMCCustomCodeClient* customCodeClient;

/**
 Builds a URL request configured with a URL with the specified path,
 relative to the mobile backend's custom code URL.
 
 @param relativePath The return request's URL path, relative to the mobile backend's custom code URL.
 @param completionHandler The completion block invoked when the URL request
 is built or an error occurs.
 @see customCodePath
 @see customCodeURL
 */
- (void)buildCustomCodeURLRequestWithPath:(nullable NSString*)relativePath
                        completionHandler:(OMCURLRequestCompletionBlock)completionHandler;

/**
 Builds an anonymous authorization URL request configured with a URL with the specified path,
 relative to the mobile backend's custom code URL.
 
 @param relativePath The return request's URL path, relative to the mobile backend's custom code URL.
 @param completionHandler The completion block invoked when the URL request
 is built or an error occurs.
 @see customCodePath
 @see customCodeURL
 */
- (void)buildAnonymousAuthorizationCustomCodeURLRequestWithPath:(nullable NSString*)relativePath
                                              completionHandler:(OMCURLRequestCompletionBlock)completionHandler;

@end


#pragma mark - constants

/**
 The mobile backend base path (`mobile`).
 */
extern NSString* const OMCMobileBackendPath;

/**
 The mobile backend `authentication` property name.
 */
extern NSString* const OMCMobileBackendAuthenticationPropertyName;

/**
 The mobile backend platform path (`platform`).
 */
extern NSString* const OMCMobileBackendPlatformPath;

/**
 The mobile backend application configuration path (`appconfig`).
 */
extern NSString* const OMCMobileBackendAppConfigPath;

/**
 The mobile backend client application configuration path (`client`),
 appended to the mobile backend application configuration URL.
 */
extern NSString* const OMCMobileBackendClientAppConfigPath;

/**
 The value of the `code` of the `NSError` generated when
 an issue occurs requesting the app config.
 See the values in the `userInfo` dictionary.
 */
extern NSInteger const OMCMobileBackendGetAppConfigError;

/**
 The mobile backend custom code path (`custom`).
 */
extern NSString* const OMCMobileBackendCustomCodePath;

NS_ASSUME_NONNULL_END
