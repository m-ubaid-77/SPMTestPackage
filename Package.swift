// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "SPMTestPackage",
    platforms: [
        .iOS(.v11)
    ],
    products: [
        .library(
            name: "CoherentSDK",
            targets: ["CoherentSDK"]),
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.3"),
    ],
    targets: [
        .binaryTarget(
            name: "CoherentSDK",
            path: "./Sources/CoherentSDK.xcframework"),
    ]
)
