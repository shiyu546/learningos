#kill process(QEMU) on gdb exits
define hook-quit
    kill
end

target remote localhost:1234
file a.out
break *0x7c00
layout src
continue
