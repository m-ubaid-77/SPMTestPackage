//
//  Runner.h
//  AIFramework
//
//  Created by Muhammad Ubaid on 20/10/2020.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CoherentiOSSDKDelegate <NSObject>

@optional
-(void) coherentSDKProgress:(NSString*)processProgress;
-(void) coherentSDKWebviewResult:(NSDictionary*)result;
-(void) coherentSDKButtonAction:(NSString*)actionName ActionResult:(id)result;

@end

@interface CoherentiOSSDK : NSObject

@property (nonatomic, assign) id<CoherentiOSSDKDelegate> delegate;
/*!
    @brief This method provides a shared instance of SDK
 
    @return instance of SDK
 */
+ (instancetype)shared;

/*!
    @brief It initialises the SDK and confirms either initalsation completed or failed
 
    @discussion This method  reads the  manifest.json file  and intialise the SDK according to the configuration inside manifest file. Resturns the result either  <i>success</i>  or   <i>error</i>  in callback either initialsation is successfull or not.
 
    @code

     [[CoherentiOSSDK shared] initialiseSDKWithCompletion:^(NSString * _Nullable result) {
         NSLog(@"Initilisation result : %@",result);
     }];
    @endcode
 
    @param completionHandler called when initalisation is completed or failed with error.
 */

-(void) initialiseSDKWithCompletion:(void(^)(NSString* _Nullable result))completionHandler __deprecated_msg("Use initialiseSDKWithOfflineRunner:(BOOL)isOfflineRunner OfflineModel:(BOOL)isOfflineModel Update:(BOOL)updateable Completion:(void (^)(BOOL, NSString * _Nullable))completionHandler instead.");

/*!
    @brief This method process the user input and return the result in a callback.
 
    @discussion This method accepts a NSDictionary as inputs and process it and returns the result in <i> completionHandler </i> callback.
 
    @code

     NSDictionary* parameters = [[NSDictionary alloc] initWithObjects:@[@11,@15,@2000] forKeys:@[@"inputA",@"inputB",@"time"]];

     [[CoherentiOSSDK shared] executeEngine:parameters onComplete:^(NSDictionary * _Nullable result, NSError * _Nullable error) {
         if (error) {
             NSLog(@"Error : %@",error);
         }
         else{
             NSLog(@"Result : %@",result);
         }
     }];

    @endcode
 
    @param  modelId NSString value representing the model on which calculation will be performed.
    @param  inputArg NSDictionary value representing the user inputs.
    @param  completionHandler it is a callback parameter, called when execution completed. <b> completionHandler </b> contains two parameters, in case of successful execution error will be nil and result will be the output.
 */

- (void) executeEngine:(NSString*)modelId inputArg:(NSDictionary*)inputs onComplete:(void(^)(NSDictionary* _Nullable result,  NSError* _Nullable  error))completionHandler;


/*!
    @brief This method returns a webview to get user input and show results.
 
    @discussion This method do not take any input , call it when need a User Interface to get user input and show results.
 
    @code

    [[CoherentiOSSDK shared] getWebView:^(WKWebView * _Nullable webview) {
        if (webview) {
            NSLog(@"Webview instance received");
        }else{
            NSLog(@"Failed to get webview");
        }
    }];

    @endcode
 
    @param completionHandler callback parameters contains webview in case of successful UI loading, in case of errror webview will be nil.
 */

- (void) getWebView:(void(^)(WKWebView* _Nullable webview))completionHandler;


/*!
    @brief This method set user language
 
    @discussion This method take a NSString as language and sets the language in the WebView , to update language this method must be called before calling  <i> getWebView </i>.
 
    @code

    [[CoherentiOSSDK shared] setLanguage:@"en"];

    @endcode
 
    @param language must be short code for language, currently supports only "en" for english and "ch" for chinese. By default language is English("en" ).
 */

- (void) setLanguage:(NSString*)language;


/*!
    @brief This method set user information
 
    @discussion This method take a NSDictionary as input parameter and sets the user information in the WebView , to update user information this method must be called before calling  <i> getWebView </i>.
 
    @code

    NSDictionary* parameters = [[NSDictionary alloc] initWithObjects:@[@"200"] forKeys:@[@"id"]];
    [[CoherentiOSSDK shared] setUserProfile:parameters];

    @endcode
 
    @param userInfo contains all necessary user information to use in App .
*/

- (void) setUserProfile:(NSDictionary*)userInfo;

/*!
    @brief This method enables to display process logs happening inside SDK
 
    @code

    [[CoherentiOSSDK shared] enableDebugLogs:TRUE];
 
    @endcode
 
    @param enable pass a boolean value to enable or disable logs.
 */

- (void) enableDebugLogs:(BOOL)enable;

/*!
    @brief It initialises the SDK and confirms either initalsation completed or failed
 
    @discussion This method  reads the  manifest.json file  and intialise the SDK according to the configuration inside manifest file. Resturns the result either  <i>success</i>  or   <i>error</i>  in callback either initialsation is successfull or not. It also includes to support offline Runner and offline model.
        In case of Offline Runner , runner file must be included inside project bundle.
        In case of offline model , model file must be there inside project with the same name as its id in manifest.json file.
 
    @code

    [[CoherentiOSSDK shared] initialiseSDKWithOfflineRunner:TRUE OfflineModel:FALSE Update:FALSE Completion:^(BOOL status, NSString * _Nullable result) {

        if (status) {
            NSLog(@"Initialised SDK successfully");
        } else {
            NSLog(@"Initialisation failed, reason : %@",result);
        }
    }];
 
    @endcode
 
    @param isOfflineRunner A boolean value indicating either offline Runner will be used or online.
    @param isOfflineModel A boolean value indicating either offline Model will be used or online.
    @param updateable If TRUE then SDK will check for updates no matter either offline or online Runner/Model. In case of FALSE it will never check for updates and used the one which is being loaded firest time.
    @param completionHandler called when initalisation is completed or failed with error.
 */


- (void) initialiseSDKWithOfflineRunner:(BOOL)isOfflineRunner OfflineModel:(BOOL)isOfflineModel Update:(BOOL)updateable Completion:(void (^)(BOOL, NSString * _Nullable))completionHandler;


- (void) enableSandboxMode:(BOOL)enabled RunnerURL:(NSString*)sandboxUrl;

/*!
    @brief It initialises the SDK and confirms either initalsation completed or failed
 
    @discussion This method  reads the  manifest.json file  and intialise the SDK according to the configuration inside manifest file. Resturns the result either  <i>success</i>  or   <i>error</i>  in callback either initialsation is successfull or not. It also includes to support offline Runner and offline model.
        In case of Offline Runner , runner file must be included inside project bundle.
        In case of offline model , model file must be there inside project with the same name as its id in manifest.json file.
 
    @code

    [[CoherentiOSSDK shared] initialiseSDKWithOfflineRunner:TRUE OfflineModel:FALSE RunnerUpdates:(BOOL)isRunnerUpdatesOn  ModelUpdates:(BOOL)isModelUpdatesOn Completion:^(BOOL status, NSString * _Nullable result) {

        if (status) {
            NSLog(@"Initialised SDK successfully");
        } else {
            NSLog(@"Initialisation failed, reason : %@",result);
        }
    }];
 
    @endcode
 
    @param isOfflineRunner A boolean value indicating either offline Runner will be used or online.
    @param isOfflineModel A boolean value indicating either offline Model will be used or online.
    @param isRunnerUpdatesOn If TRUE then SDK will check for updates no matter either offline or online Runner. In case of FALSE it will never check for updates and used the one which is being loaded first time.
    @param isModelUpdatesOn If TRUE then SDK will check for updates no matter either offline or online Model. In case of FALSE it will never check for updates and used the one which is being loaded first time.
    @param completionHandler called when initalisation is completed or failed with error.
 */

- (void) initialiseSDKWithOfflineRunner:(BOOL)isOfflineRunner OfflineModel:(BOOL)isOfflineModel RunnerUpdates:(BOOL)isRunnerUpdatesOn  ModelUpdates:(BOOL)isModelUpdatesOn Completion:(void (^)(BOOL, NSString * _Nullable))completionHandler;

@end

NS_ASSUME_NONNULL_END
