some patch file to compile AFL in qemu mode.
you can modify build_qemu_support.sh and add following lines to avoid compress error:
```
tar xf "$ARCHIVE" --exclude qemu-2.10.0/roms/u-boot/scripts/Kconfig || exit 1
```
