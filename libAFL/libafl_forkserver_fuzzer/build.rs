use std::env;
use std::process::Command;

fn main() {
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=src/main.rs");

    let cwd = env::current_dir().unwrap().to_string_lossy().to_string();
    let xpdf_dir = format!("{}", cwd);

    // make clean; remove any leftover gunk from prior builds
    Command::new("afl-gcc")
        .arg("-fsanitize=address,undefined")
	.arg("imgRead.c")
	.arg("-o")
	.arg("./target/release/imgRead")
        .current_dir(xpdf_dir.clone())
        .status()
        .expect("Couldn't clean program directory");
/*
    // clean doesn't know about the install directory we use to build, remove it as well
    Command::new("rm")
        .arg("-r")
        .arg("-v")
        .arg("-f")
        .arg(&format!("{}/install", xpdf_dir))
        .current_dir(xpdf_dir.clone())
        .status()
        .expect("Couldn't clean xpdf's install directory");

    // export LLVM_CONFIG=llvm-config-11
    env::set_var("LLVM_CONFIG", "llvm-config-11");

    // configure with afl-clang-fast and set install directory to ./xpdf/install
    Command::new("./configure")
        .arg(&format!("--prefix={}/install", xpdf_dir))
        .env("CC", "/usr/local/bin/afl-clang-fast")
        .current_dir(xpdf_dir.clone())
        .status()
        .expect("Couldn't configure xpdf to build using afl-clang-fast");

    // make && make install
    Command::new("make")
        .current_dir(xpdf_dir.clone())
        .status()
        .expect("Couldn't make xpdf");

    Command::new("make")
        .arg("install")
        .current_dir(xpdf_dir)
        .status()
        .expect("Couldn't install xpdf");
*/
}
