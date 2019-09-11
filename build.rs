use std::env;

fn main () {
    // println!("export MAGICLEAP_SDK=$MLSDK");
    env::set_var("MAGICLEAP_SDK", "$MLSDK");

}