// Copyright (c) 2009-2009 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018-2018 The Galilel developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0xcb478f2a2e8f911c09dbd5c088e92ccfff918c9eab5632433b5388012fff611d")); //!< Network split here
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1562155200, // * UNIX timestamp of last checkpoint block
    400,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    200        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of
    (0, uint256("0xcb478f2a2e8f911c09dbd5c088e92ccfff918c9eab5632433b5388012fff611d"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1562155201,
    100,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0xcb478f2a2e8f911c09dbd5c088e92ccfff918c9eab5632433b5388012fff611d"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1562155202,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xe9;
        pchMessageStart[1] = 0xc4;
        pchMessageStart[2] = 0xc4;
        pchMessageStart[3] = 0xfd;
        vAlertPubKey = ParseHex("046f9377ce4a132dc5ed4b1f75d0a414309e12301a9e09945ccab045bf0b355c128e89c5b64d84177cdfac3793a0bb700ca035e236b1867dd76ddfb89bae94e2b8");
        nDefaultPort = 36001;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // GALI starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // GALI: 1 day
        nTargetSpacing = 1 * 60;  // GALI: 1 minute
        nMaturity = 19;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 25000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 150;
        nModifierUpdateBlock = 1;
        nZerocoinStartTime = 1582155200;		/* Fri Dec  7 21:00:00 UTC 2018 */
        nBlockFirstGoodChecksum = 285471;		/* First block with valid Zerocoin checksums */
        nBlockFirstMint = 247432;
        nBlockEnforceSerialRange = 281451;		/* Enforce serial range starting this block */
        nBlockZerocoinV2 = 281451;			/* First mint at block 247432 */
        nEnforceNewSporkKey = 1553907600;		/* Sat Mar 30 01:00:00 UTC 2019: sporks signed after must use the new spork key */
        nRejectOldSporkKey = 1554080400;		/* Mon Apr  1 01:00:00 UTC 2019: after that reject old spork key */

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01043747616c696c656c20436f696e2053746172742040204672696461792c2032352e204d617920323031382030343a30303a303020474d542e)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "RedSpace Coin and Games 3.07.2019";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0428df210a2159ca5b86889ad4d2043c029b7e61deca3628382e1eae46efdda6b604b9f0690038d35b16d98ab75e29bf2ac765d3272df9216df660ad8aba9ac21a") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1562155200;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 290678;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xcb478f2a2e8f911c09dbd5c088e92ccfff918c9eab5632433b5388012fff611d"));
        assert(genesis.hashMerkleRoot == uint256("0xce52f8fab4d04679297def98bb0b845ba79818be2c0ecfe271ca0ddb10e18cf2"));;

        vSeeds.push_back(CDNSSeedData("80.240.17.77", "80.240.17.77")); // 1st DNS Seeder from mbroemme
        vSeeds.push_back(CDNSSeedData("45.76.151.173", "45.76.151.173")); // 2nd DNS Seeder from mbroemme
        //vSeeds.push_back(CDNSSeedData("seed3.galilel.org", "seed3.galilel.org")); // 3rd DNS Seeder from mbroemme
        //vSeeds.push_back(CDNSSeedData("seed4.galilel.org", "seed4.galilel.org")); // 4th DNS Seeder from mbroemme
        //vSeeds.push_back(CDNSSeedData("seed5.galilel.org", "seed5.galilel.org")); // 5th DNS Seeder from gridscale.io
        //vSeeds.push_back(CDNSSeedData("seed6.galilel.org", "seed6.galilel.org")); // 6th DNS Seeder from gridscale.io
        //vSeeds.push_back(CDNSSeedData("seed7.galilel.org", "seed7.galilel.org")); // 7th DNS Seeder from gridscale.io
        //vSeeds.push_back(CDNSSeedData("seed8.galilel.org", "seed8.galilel.org")); // 8th DNS Seeder from gridscale.io

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 68);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 16);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x6d).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0422f1a9df4dafeb4142eb5a2ea3aa6d7928f91d943beb383762c3183fd3822d8fc09915a36b289816ee2695ca2dfccd10adbb1132aef53b98730c2a54ff307352";
        strSporkKeyOld = "0422f1a9df4dafeb4142eb5a2ea3aa6d7928f91d943beb383762c3183fd3822d8fc09915a36b289816ee2695ca2dfccd10adbb1132aef53b98730c2a54ff307352";
        strObfuscationPoolDummyAddress = "UZtNU63X1ct8bJULwCPZrh4oF8AE62CVJ1";
        nStartMasternodePayments = 1525192183; // Tue May  1 18:29:43 CEST 2018
        nRequiredMasternodeCollateral = 15000 * COIN; // Masternode collateral amount

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; // high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; // the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; // full security level for accumulators
        nZerocoinHeaderVersion = 4; // block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 240; //The required confirmations for a zgali to be stakable

        nBudgetFeeConfirmations = 6; // number of confirmations for the finalization fee

        nBudgetSuperBlocks = 43200; // amount of blocks in a months period of time using 1 minutes per block
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x14;
        pchMessageStart[1] = 0x64;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x65;
        vAlertPubKey = ParseHex("046f9377ce4a132dc5ed4b1f75d0a414309e12301a9e09945ccab045bf0b355c128e89c5b64d84177cdfac3793a0bb700ca035e236b1867dd76ddfb89bae94e2b8");
        nDefaultPort = 56123;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // GALI: 1 day
        nTargetSpacing = 1 * 60;  // GALI: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197;
        nMaxMoneyOut = 25000000 * COIN;
        nZerocoinStartTime = 1582155200;		/* Fri Nov  9 21:00:00 UTC 2018 */
        nBlockFirstGoodChecksum = 26751;		/* First block with valid Zerocoin checksums */
        nBlockFirstMint = 312;
        nBlockEnforceSerialRange = 2181;		/* Enforce serial range starting this block */
        nBlockZerocoinV2 = 2181;			/* First mint at block 312 */
        nEnforceNewSporkKey = 1553907600;		/* Sat Mar 30 01:00:00 UTC 2019: sporks signed after must use the new spork key */
        nRejectOldSporkKey = 1554080400;		/* Mon Apr  1 01:00:00 UTC 2019: after that reject old spork key */

        /* Testnet genesis block. */
        genesis.nTime = 1562155201;
        genesis.nNonce = 509176;

        //hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("0xcb478f2a2e8f911c09dbd5c088e92ccfff918c9eab5632433b5388012fff611d"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.push_back(CDNSSeedData("seed1.testnet.galilel.org", "seed1.testnet.galilel.org"));
        vSeeds.push_back(CDNSSeedData("seed2.testnet.galilel.org", "seed2.testnet.galilel.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 83);  // Testnet galilel addresses start with 'a'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // Testnet galilel script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 193);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet Galilel BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Galilel BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Galilel BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "042d29f026121ae1d1c14a7005b55196c9a5e388c8895ba2373c049cefb65c333f4626b19bcb4af9e10b82e47e9e6cea4847d410a2599f6271813c263d430a2d9d";
        strSporkKeyOld = "04363509d5c65f5a9ca7ceedad4887007ae85469d249a6f566b788504ee5e105bcf1bbc515f49a7aac3bceb8864bb2ba84bebd92c66ff9022309e2bfbd5f70d11f";
        strObfuscationPoolDummyAddress = "acW3shX2oxMLykakdi9zvjvaX6NBCyVLTw";
        nStartMasternodePayments = 1540587600; // Fri Oct 26 21:00:00 UTC 2018
        nRequiredMasternodeCollateral = 15000 * COIN; // Masternode collateral amount
        nBudgetFeeConfirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet

        nBudgetSuperBlocks = 120; // amount of blocks in a 2 hours period of time using 1 minutes per block
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x65;
        pchMessageStart[1] = 0x14;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x65;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // GALI: 1 day
        nTargetSpacing = 1 * 60;        // GALI: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nLastPOWBlock = 200;
        nMaturity = 99;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 0;
        nMaxMoneyOut = 25000000 * COIN;
        nBlockZerocoinV2 = 300;
        nZerocoinStartTime = 1582155200;
        nBlockEnforceSerialRange = 300; //Enforce serial range starting this block

        // Modify the regtest genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1540587600;
        genesis.nNonce = 1745260;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 57123;
        //assert(hashGenesisBlock == uint256("0xcb478f2a2e8f911c09dbd5c088e92ccfff918c9eab5632433b5388012fff611d"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 58123;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
