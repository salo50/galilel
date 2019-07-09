# Summary

This is a mandatory update which will hard fork the chain. Recently several
resource exhaustion attacks on PoS has been discovered.

- Vulnerability 1:

It is called "I Can't Believe it's not Stake" attack. It was introduced while
merging upstream headers first feature into PoS forks. It fills a victims node
memory until resources are exhausted and node may crash due to out of memory
condition. Codebase is not affected by it.

- Vulnerability 2:

It is called "Spent Stake" attack. It was discoverd while investigating
vulnerability 1 above. It works because block verification ensures that the
coin exists, but not that it is unspent. After forking of the main chain the
coinstake transaction is still validated against the main chain TxDB. It allows
to generate arbitrary amount of apparent stake and inject it into victims node.
Codebase is fixed with this update.

### Update Type

Optional | Soft fork | Hard fork
---------|-----------|----------
No       | No        | Yes

### Changelog v3.2.0

* Fixed "Stake Spent" attack for PoS and zPoS, protocol change at
  Mon Feb 18 10:00:00 UTC 2019
* Stability improvements for Win32/Win64, switching build environment to
  POSIX MinGW
* Added RISC-V architecture to default builds
