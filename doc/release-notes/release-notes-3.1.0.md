# Summary

This is a mandatory update which will hard fork the chain. We have already
valid zGALIv1 mints in the chain at block 247,434 so we moved back the
activation block to make them spendable. Also during zGALIv1 activation we
forgot to store the accumulator checkpoints in the chain. We have added a
workaround to make these coins spendable and first good checkpoint will occur
at block 286,600. As Zerocoin activation were created with payload of zGALIv2
we aligned the activation block between v1 and v2. This will simplify code in
future a lot.

### Update Type

Optional | Soft fork | Hard fork
---------|-----------|----------
No       | No        | Yes

### Changelog v3.1.0

* Block 245,000: Zerocoin v1 activation
* Block 245,000: Zerocoin v2 activation
* Block 286,600: zPoS activation
* Modified reward structure to generate only integer numbers during PoS / zPoS
  as smallest Zerocoin denomination is 1
* zGALI Rewards (from block 245,001): 1 zGALI
* zGALI Rewards (from block 340,001): MN 40%, zPoS 60%
* zGALI Rewards (from block 430,001): MN 40%, zPoS 60%
