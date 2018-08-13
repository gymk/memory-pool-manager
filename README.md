# memory-pool-manager
A CPP based memory mamanger, which creates a pool of fixed size buffers, enabling get/release of those fixed buffers - avoiding frequent memory allocation.

Say for example, in DVB systems, we will be receiving multiple sections in parallel in Transport Stream, all having a maximum section size of 4 KiB (0x1000).
Instead of doing malloc()/ free() whenever we get new section, we can this kind of pool manager to get available buffer to process current section, release it after using it for buffer availability to next available section.

For an IPTV platform handling single-program-transport-stream, a maxium of 10 buffers of size 0x1000 is enough to handle almost all kind of cases (Zapper/ PVR/ PVOD/...)