//
//  OMCUser.h
//  OMCCore
//
//  Copyright (c) 2015, Oracle Corp. All rights reserved. 
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 An OMCe user has a name and various other properties. A user is retrieved
 from the OMCe server and is not stored locally. Note a user cannot be
 constructed directly. It is retrieved via the method
 `-[OMCAuthorization getCurrentUser:]`.
*/
@interface OMCUser : NSObject

/**
 The user's user name.
 */
@property (readonly) NSString* username;

/**
 The user's first name.
 */
@property (readonly, nullable) NSString* firstName;

/**
 The user's last name.
 */
@property (readonly, nullable) NSString* lastName;

/**
 The user's email.
 */
@property (readonly, nullable) NSString* email;

@end

/**
 The user username property name (`username`).
 */
extern NSString* const OMCUserUsernamePropertyName;

/**
 The user first name property name (`firstName`).
 */
extern NSString* const OMCUserFirstNamePropertyName;

/**
 The user last name property name (`lastName`).
 */
extern NSString* const OMCUserLastNamePropertyName;

/**
 The user email property name (`email`).
 */
extern NSString* const OMCUserEmailPropertyName;

NS_ASSUME_NONNULL_END
