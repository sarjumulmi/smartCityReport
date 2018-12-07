//
//  OMCMobileManager.h
//  OMCCore
//
//  Copyright (c) 2015, Oracle Corp. All rights reserved. 
//

#import <Foundation/Foundation.h>

@class OMCMobileBackend;
@class OMCServiceProxy;
@class OMCAuthorization;

NS_ASSUME_NONNULL_BEGIN

/**
 The mobile manager is the entry point to the
 Oracle Mobile Cloud, Enterprise (OMCe) Service SDK.
 It is responsible for building and holding the mobile backend and analytics app.
 */
@interface OMCMobileManager : NSObject

/**
 Returns the singleton mobile manager.
 */
+ (OMCMobileManager*)sharedManager;


#pragma mark - Mobile Backend

/**
 The mobile manager's mobile backend. This is the mobile backend
 configured in the OMC property list file (`OMC.plist`).
 */
@property (readonly, nullable) OMCMobileBackend* mobileBackend;

/**
 Sets and returns the receiver's mobile backend,
 initializing it with the specified properties.
 The properties must be in the same form as the `backend`
 properties in the OMC property list file (`OMC.plist`).
 
 Clears the receiver's mobile backend if the specified properties is `nil`.
 
 If the receiver already contains a mobile backend, replaces
 it with the newly created mobile backend.
 
 @param properties The new mobile backend's initial properties.
 */
- (OMCMobileBackend*)setMobileBackendWithProperties:(nullable NSDictionary<NSString*, id>*)properties;

/**
 Builds and returns a new mobile backend,
 initializing it with the specified properties.
 The properties must be in the same form as the `backend`
 properties in the OMC property list file (`OMC.plist`).
 Returns `nil` if the specified properties is `nil`.
 
 NB: The new mobile backend does not replace the mobile manager's
 mobile backend; it is simply returned.
 
 @param properties The new mobile backend's initial properties.
 */
- (OMCMobileBackend*)buildMobileBackendWithProperties:(nullable NSDictionary<NSString*, id>*)properties;

#pragma mark - Authorization

/**
 The mobile manager's OAuth token end point URL, which is used by the
 `mobileBackend` and `analyticsApp` to acquire OAuth tokens, if necessary.
 This URL is built by appending the pre-defined OAuth token path
 to the Identity Service base URL.
 
 @see -[OMCMobileManager identityServiceBaseURL]
 */
@property (readonly, nullable) NSURL* oAuthTokenEndPointURL;

/**
 The mobile manager's Identity Service base URL, which is used to build
 the manager's OAuth token end point URL.
 Typically, this URL is set via the OMC property list file (`OMC.plist`)
 and is in the form `https://<host>:<port>`.

 @see -[OMCMobileManager oAuthTokenEndPointURL]
 */
@property (nullable) NSURL* identityServiceBaseURL;


#pragma mark - Logging

/**
 The mobile manager's log level. This log level controls the volume of log entries
 produced by the OMCe SDK. The log level can be set to one of the following
 levels: `"none"`, `"error"`, `"warning"`, `"info"`, `"debug"`.
 This log level can be either initialized
 from the default property list file (`OMC.plist`) or set directly at
 runtime via this property. If it is not set explicitly, the log level is `error`.
 */
@property (nonatomic) NSString* logLevel;

/**
 The mobile manager's log HTTP flag. This flag controls whether,
 when logging HTTP requests and responses,
 the OMCe SDK also logs the headers and bodies of the requests and responses.
 This flag can be either initialized
 from the default property list file (`OMC.plist`) or set directly at
 runtime via this property. If it is not set explicitly,
 the flag's value is `NO`.

 @see -[OMCMobileManager logHTTPMaxHeaderSize]
 @see -[OMCMobileManager logHTTPMaxBodySize]
 */
@property BOOL logHTTP;

/**
 The mobile manager's log HTTP max header size. This value determines the
 maximum number of characters to be logged when logging an HTTP header value.
 If an HTTP header value is longer than the specified maximum, a truncated version
 of the value will be logged with a trailing ellipsis (`...`).
 This value can be either initialized
 from the default property list file (`OMC.plist`) or set directly at
 runtime via this property. If it is not set explicitly, the value is `100`.
 If this value is set to `0`, all HTTP header values will be printed in entirety.
 
 @see -[OMCMobileManager logHTTP]
 @see -[OMCMobileManager logHTTPMaxBodySize]
 */
@property NSUInteger logHTTPMaxHeaderSize;

/**
 The mobile manager's log HTTP max body size. This value determines the
 maximum number of bytes to be logged when logging an HTTP body.
 If an HTTP body is longer than the specified maximum, a truncated version
 of the value will be logged with a trailing ellipsis (`...`).
 This value can be either initialized
 from the default property list file (`OMC.plist`) or set directly at
 runtime via this property. If it is not set explicitly, the value is `10000`.
 If this value is set to `0`, all HTTP bodies will be printed in entirety.
 
 @see -[OMCMobileManager logHTTP]
 @see -[OMCMobileManager logHTTPMaxHeaderSize]
 */
@property NSUInteger logHTTPMaxBodySize;


#pragma mark - OMC.plist properties

/**
 The mobile manager's properties, as specified by the OMC property list file
 (`OMC.plist`).
 */
@property (readonly, nonatomic) NSDictionary<NSString*, id>* properties;

@end


#pragma mark - constants

/**
 The mobile manager's `mobileBackend` property name.
 */
extern NSString* const OMCMobileManagerMobileBackendPropertyName;

/**
 The mobile manager's `analyticsApp` property name.
 */
extern NSString* const OMCMobileManagerAnalyticsAppPropertyName;

/**
 The mobile manager's `identityServiceBaseURL` property name.
 */
extern NSString* const OMCMobileManagerIdentityServiceBaseURLPropertyName;

/**
 The mobile manager's OAuth token path,
 appended to the Identity Service base URL.
 (i.e. `"/oauth2/v1/token"`).
 */
extern NSString* const OMCMobileManagerOAuthTokenPath;

/**
 The mobile manager's `logLevel` property name.
 */
extern NSString* const OMCMobileManagerLogLevelPropertyName;

/**
 Use this constant to set the mobile manager's log level to `"none"`.
 */
extern NSString* const OMCMobileManagerLogLevelNone;

/**
 Use this constant to set the mobile manager's log level to `"error"`.
 */
extern NSString* const OMCMobileManagerLogLevelError;

/**
 Use this constant to set the mobile manager's log level to `"warning"`.
 */
extern NSString* const OMCMobileManagerLogLevelWarning;

/**
 Use this constant to set the mobile manager's log level to `"info"`.
 */
extern NSString* const OMCMobileManagerLogLevelInfo;

/**
 Use this constant to set the mobile manager's log level to `"debug"`.
 */
extern NSString* const OMCMobileManagerLogLevelDebug;

/**
 This constant specifies the mobile manager's default log level
 (i.e. `"error"`).
 */
extern NSString* const OMCMobileManagerLogLevelDefault;

/**
 The mobile manager's `logHTTP` property name.
 */
extern NSString* const OMCMobileManagerLogHTTPPropertyName;

/**
 This constant specifies the mobile manager's default log HTTP value (i.e. `NO`).
 */
extern BOOL const OMCMobileManagerLogHTTPDefault;

/**
 The mobile manager's `logHTTPMaxHeaderSize` property name.
 */
extern NSString* const OMCMobileManagerLogHTTPMaxHeaderSizePropertyName;

/**
 This constant specifies the mobile manager's default
 log HTTP max header size value (i.e. `100`).
 */
extern NSUInteger const OMCMobileManagerLogHTTPMaxHeaderSizeDefault;

/**
 The mobile manager's `logHTTPMaxBodySize` property name.
 */
extern NSString* const OMCMobileManagerLogHTTPMaxBodySizePropertyName;

/**
 This constant specifies the mobile manager's default
 log HTTP max body size value (i.e. `10000`).
 */
extern NSUInteger const OMCMobileManagerLogHTTPMaxBodySizeDefault;

/**
 A key to the `userInfo` dictionary in
 the `NSError` generated when an HTTP call generates an unexpected response.
 The corresponding value is the `NSURLRequest` that generated the error.
 */
extern NSString* const OMCMobileErrorRequest;

/**
 A key to the `userInfo` dictionary in
 the `NSError` generated when an HTTP call generates an unexpected response.
 The corresponding value is the `NSHTTPURLResponse` returned by the HTTP call.
 */
extern NSString* const OMCMobileErrorResponse;

/**
 A key to the `userInfo` dictionary in
 the `NSError` generated when an HTTP call generates an unexpected response.
 The corresponding value is the `NSData` returned by the HTTP call.
 */
extern NSString* const OMCMobileErrorResponseData;

/**
 A key to the `userInfo` dictionary in
 the `NSError` generated when an unexpected error is encountered.
 The corresponding value is the `NSError` encountered.
 */
extern NSString* const OMCMobileErrorCause;

/**
 The Mobile Client SDK Info header field name (`"Oracle-Mobile-Client-SDK-Info"`).
 */
extern NSString* const OMCMobileClientSDKInfoHTTPHeaderFieldName;

NS_ASSUME_NONNULL_END
