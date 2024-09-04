Pod::Spec.new do |spec|
  spec.name         = "social-sdk"
  spec.version      = "0.0.1"
  spec.license      = { :type => "MIT", :file => "FILE_LICENSE" }
  spec.platform     = :ios
  spec.swift_version = '5.7'
  spec.ios.deployment_target = "12.0"
  spec.source       = { :git => "https://github.com/G-E-E-B-S/social-sdk-wrapper.git", :tag => "#{spec.version}" }
  spec.source_files  = ["ios/*", "ios/social-sdk/*.swift", "ios/social-sdk/social-sdk/*", "socialsdk/*.h"]
  spec.public_header_files = [
    "ios/social-sdk/social-sdk/social_sdk.h",
    "ios/TournamentBridge.hpp",
    "ios/FacebookGamingShareBridge.hpp"]
  spec.dependency 'FBSDKCoreKit'
  spec.dependency 'FBSDKShareKit'
  spec.dependency 'FBSDKGamingServicesKit'

  spec.pod_target_xcconfig = {
    "HEADER_SEARCH_PATHS" => '${inherited} '+
    '"${PODS_TARGET_SRCROOT}/external/includes" ',
    "USER_HEADER_SEARCH_PATHS" => '${inherited} '+
    '"${PODS_TARGET_SRCROOT}" ' +
    '"${PODS_TARGET_SRCROOT}/../jsb-helper" '
  }
end
