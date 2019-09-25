extern crate neon_build;

fn main() {
    let path = "/Users/jonkelley/Development/Support/MagicLeap/mlsdk/v0.22.0/lumin/usr/lib/";

    println!("cargo:rustc-link-search=all={}", path);
    
    // println!("cargo:rustc-link-search=all={}", path);
    // println!("cargo:rustc-link-lib={}","/Users/jonkelley/Development/Support/MagicLeap/mlsdk/v0.22.0/lumin/usr/lib/");

    // println!("cargo:rustc-link-lib={}", path);
    println!("cargo:rustc-link-search=native={}", path);
    println!("cargo:libdir={}", path);

    neon_build::setup(); // must be called in build.rs

    // add project-specific build logic here...
}
