# Summary

This is an optional update which will fix a Dynamic Zerocoin Proof-of-Stake
(zPoS) v2 bug. In previous version 3.1.1 you get only 5 zGALI rewards instead
of 6 between block 340,000 and 430,000, this has been corrected in 3.1.2.
Upstream fixes have been merged.

### Update Type

Optional | Soft fork | Hard fork
---------|-----------|----------
Yes      | No        | No

### Changelog v3.1.2

* Block 340,000 - 430,000: Dynamic zPoS v2 will generate correct 6 zGALI
* Improved performance when listing zGALI mints
* Fixed zGALI spend when too much mints are selected
* Fixed missing explorer icon
* Stability improvements
