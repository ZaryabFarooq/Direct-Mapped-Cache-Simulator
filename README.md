# Direct-Mapped-Cache-Simulator

Implemented a 256 byte Direct-mapped cache with a line size of 8 bytes. 
Cache supported read and write operatioms.

My cache also supported a write-back write policy which required me to use a dirty-bit. 
In addition, my cache supported a write-allocate write miss policy.

This caued the appropriate line to be brought into the cache from memory, and the write's value to update the correct part of the line in
the cache, which then became dirty.
