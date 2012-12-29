mu
==

Small utility for fixing FF5 SRAM checksums.
#Usage:
$: ./mu.bin <ff5.srm>

This modified save-ram will work on all emulators and on real hardware. 
----------------------------------------------------------------------------------------------------------------------+
---->BE CAREFUL<----
There are no safeguards about which file you supply. If you have write permissions, the program WILL overwrite whatever
is contained at offset 0x1FF0. To avoid errors, dont use any wildcards (*) when specifiying the file you want modified.
----------------------------------------------------------------------------------------------------------------------+
