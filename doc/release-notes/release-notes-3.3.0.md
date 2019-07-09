# Summary

This is a mandatory update which will hard fork the chain.

## How to Upgrade

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/Galilel-Qt (on Mac) or
galileld/galilel-qt (on Linux).

## Compatibility

Galilel Core is extensively tested on multiple operating systems using the
Linux kernel, macOS 10.10+, and Windows 7 and later.

Microsoft ended support for Windows XP on April 8th, 2014, No attempt is made
to prevent installing or running the software on Windows XP, you can still do
so at your own risk but be aware that there are known instabilities and issues.
Please do not report issues about Windows XP to the issue tracker.

Apple released it's last Mountain Lion update August 13, 2015, and officially
ended support on December 14, 2015. Galilel Core software starting with v3.3.0
will no longer run on macOS versions prior to Yosemite (10.10). Please do not
report issues about macOS versions prior to Yosemite to the issue tracker.

Galilel Core should also work on most other Unix-like systems and is frequently
tested on Arch Linux, Fedora and Ubuntu.

## Notable Changes

### Minimum Supported macOS Version

The minimum supported version of macOS (OSX) has been moved from 10.8 Mountain
Lion to 10.10 Yosemite. Users still running a macOS version prior to Yosemite
will need to upgrade their OS if they wish to continue using the latest
version(s) of the Galilel Core wallet.

### Wrapped Serials

The vulnerability allows an attacker to fake serials accepted by the network
and thus to spend zerocoins that have never been minted. As severe as it is, it
does not harm users' privacy and does not affect their holdings directly.

### Automint Addresses

A new "Automint Addresses" feature has been added to the wallet that allows for
the creation of new addresses who's purpose is to automatically convert any
GALI funds received by such addresses to zGALI. The feature as a whole can be
enabled/disabled either at runtime using the `-enableautoconvertaddress`
option, via RPC/Console with the `enableautomintaddress` command, or via the
GUI's options dialog, with the default being enabled.

Creation of these automint addresses is currently only available via the
RPC/Console `createautomintaddress` command, which takes no additional
arguments. The command returns a new GALI address each time, but addresses
created by this command can be re-used if desired.

### In-wallet Proposal Voting

A new UI wallet tab has been introduced that allows users to view the current
budget proposals, their vote counts, and vote on proposals if the wallet is
acting as a masternode controller. The visual design is to be considered
temporary, and will be undergoing further design and display improvements in
the future.

### Zerocoin Lite Node Protocol

Support for the ZLN Protocol has been added, which allows for a node to opt-in
to providing extended network services for the protocol. By default, this
functionality is disabled, but can be enabled by using the
`-peerbloomfilterszc` runtime option.

A full technical writeup of the protocol can be found [here](https://pivx.org/wp-content/uploads/2018/11/Zerocoin_Light_Node_Protocol.pdf).

### Precomputed Zerocoin Proofs

This introduces the ability to do most of the heavy computation required for
zGALI spends **before** actually initiating the spend. A new thread,
`ThreadPrecomputeSpends`, is added which constantly runs in the background.

`ThreadPrecomputeSpends`' purpose is to monitor the wallet's zGALI mints and
perform partial witness accumulations up to `nHeight - 20` blocks from the
chain's tip (to ensure that it only ever computes data that is at least 2
accumulator checkpoints deep), retaining the results in memory.

Additionally, a file based cache is introduced, `precomputes.dat`, which serves
as a place to store any precomputed data between sessions, or when the
in-memory cache size is exhausted. Swapping data between memory and disk file
is done as needed, and periodic cache flushes to the disk are routine.

This also introduces 2 new runtime configuration options:

* `-precompute` is a binary boolean option (`1` or `0`) that determines whether
  or not pre-computation should be activated at runtime (default value is to
  activate, `1`).
* `-precomputecachelength` is a numeric value between `500` and `2000` that
  tells the precompute thread how many blocks to include during each pass
  (default is `1000`).

A new RPC command, `clearspendcache`, has been added that allows for the
clearing/resetting of the precompute cache (both memory and disk). This command
takes no additional arguments.

Finally, the "security level" option for spending zGALI has been completely
removed, and all zGALI spends now spend at what was formerly "security level"
`100`. This change has been reflected in any RPC command that previously took
a security level argument, as well as in the GUI's Privacy section for spending
zGALI.

### Unit Test Suite

The unit test suite has been completely ported to work with Galilel blockchain
to enable Travis CI integration for build pass validation and continuous
integration testing.

### Regression Test Suite

The RegTest network mode has been re-worked to once again allow for the
generation of on-demand PoW and PoS blocks. Additionally, many of the existing
functional test scripts have been adapted for use with Galilel, and we now have
a solid testing base for highly customizable tests to be written.

With this, the old `setgenerate` RPC command no longer functions in regtest
mode, instead a new `generate` command has been introduced that is more suited
for use in regtest mode.

## Update Type

Optional | Soft fork | Hard fork
---------|-----------|----------
No       | No        | Yes

## Changelog v3.3.0

* Fixed "Wrapped Serials" attack for zPoS, protocol change at
  Tue Apr 23 14:00:00 UTC 2019
* Minimum Supported macOS Version is 10.10 Yosemite
* Automint Addresses for automatic GALI to zGALI conversion
* In-wallet Proposal Voting
* Zerocoin Lite Node Protocol (ZLN)
* Precomputed Zerocoin Proofs
* Working Unit Test Suite
* Working Regression Test Suite

## Credits

* mbroemme
* ChristianGrieger
* presstab
* Fuzzbawls
* Mrs-X
* Warrows
* cevap
* furszy
