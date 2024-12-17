/*
* ImagiNet Compiler 1.0.0+0ab2c4ad366da00c2c3aea0976e0fea212163bf4
* Copyright © 2023- Imagimob AB, All Rights Reserved.
*
* Generated at 12/11/2024 21:27:46 UTC. Any changes will be lost.
*
* Model ID  617d4ffc-751b-46dd-ac09-7091641a26f7
*
* Memory    Size                      Efficiency
* Buffers   10256 bytes (RAM)         90 %
* State     11592 bytes (RAM)         100 %
* Readonly  40432 bytes (Flash)       100 %
*
* Backend              tensorflow
* Keras Version        2.15.0
* Backend Model Type   Sequential
* Backend Model Name   conv1d-medium-balanced-0
*
* Class Index | Symbol Label
* 0           | unlabelled
* 1           | down
* 2           | up
*
* Exported functions:
*
*  @description: Try read data from model.
*  @param dataout Output Features. Output float[3].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_dequeue(float *dataout);
*
*  @description: Try write data to model.
*  @param datain Input features. Input float[1].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_enqueue(const float *datain);
*
*  @description: Closes and flushes streams, free any heap allocated memory.
*  void IMAI_finalize(void);
*
*  @description: Initializes buffers to initial state.
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*  int IMAI_init(void);
*
*
* Disclaimer:
*   The generated code relies on the optimizations done by the C compiler.
*   For example many for-loops of length 1 must be removed by the optimizer.
*   This can only be done if the functions are inlined and simplified.
*   Check disassembly if unsure.
*   tl;dr Compile using gcc with -O3 or -Ofast
*/

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

#include "keyword_spotter.h"

#ifdef __GNUC__
#define ALIGNED(x) __attribute__((aligned(x)))
#else
#define ALIGNED(x) __declspec(align(x))
#endif
// Working memory
static ALIGNED(16) int8_t _buffer[10256];
static ALIGNED(16) int8_t _state[11592];

// Parameters
static const uint32_t _K6[] = {
    0x3da3d70a, 0x3da3e945, 0x3da41ff6, 0x3da47b1a, 0x3da4faae, 0x3da59ead, 0x3da66711, 0x3da753d1,
    0x3da864e6, 0x3da99a43, 0x3daaf3de, 0x3dac71a8, 0x3dae1393, 0x3dafd990, 0x3db1c38b, 0x3db3d173,
    0x3db60333, 0x3db858b5, 0x3dbad1e2, 0x3dbd6ea1, 0x3dc02eda, 0x3dc3126f, 0x3dc61946, 0x3dc9433f,
    0x3dcc903c, 0x3dd0001c, 0x3dd392bc, 0x3dd747fa, 0x3ddb1fb0, 0x3ddf19b9, 0x3de335ed, 0x3de77423,
    0x3debd432, 0x3df055ed, 0x3df4f929, 0x3df9bdb7, 0x3dfea369, 0x3e01d506, 0x3e0468b9, 0x3e070cb2,
    0x3e09c0d8, 0x3e0c8510, 0x3e0f593f, 0x3e123d48, 0x3e15310f, 0x3e183476, 0x3e1b4760, 0x3e1e69af,
    0x3e219b42, 0x3e24dbfc, 0x3e282bba, 0x3e2b8a5d, 0x3e2ef7c4, 0x3e3273cb, 0x3e35fe51, 0x3e399733,
    0x3e3d3e4d, 0x3e40f37b, 0x3e44b697, 0x3e48877d, 0x3e4c6608, 0x3e50520f, 0x3e544b6e, 0x3e5851fc,
    0x3e5c6591, 0x3e608606, 0x3e64b330, 0x3e68ece8, 0x3e6d3302, 0x3e718555, 0x3e75e3b6, 0x3e7a4df9,
    0x3e7ec3f3, 0x3e81a2bc, 0x3e83e92d, 0x3e863537, 0x3e8886c2, 0x3e8addb8, 0x3e8d3a02, 0x3e8f9b87,
    0x3e920232, 0x3e946de9, 0x3e96de94, 0x3e99541c, 0x3e9bce69, 0x3e9e4d61, 0x3ea0d0ec, 0x3ea358f1,
    0x3ea5e557, 0x3ea87604, 0x3eab0ae0, 0x3eada3d1, 0x3eb040bc, 0x3eb2e189, 0x3eb5861c, 0x3eb82e5d,
    0x3ebada30, 0x3ebd897b, 0x3ec03c23, 0x3ec2f20e, 0x3ec5ab21, 0x3ec86741, 0x3ecb2653, 0x3ecde83b,
    0x3ed0acdf, 0x3ed37422, 0x3ed63de9, 0x3ed90a1a, 0x3edbd897, 0x3edea945, 0x3ee17c09, 0x3ee450c6,
    0x3ee72760, 0x3ee9ffbb, 0x3eecd9bb, 0x3eefb544, 0x3ef29239, 0x3ef5707e, 0x3ef84ff6, 0x3efb3086,
    0x3efe1210, 0x3f007a3c, 0x3f01ebd1, 0x3f035db8, 0x3f04cfe4, 0x3f064245, 0x3f07b4ce, 0x3f09276f,
    0x3f0a9a1c, 0x3f0c0cc5, 0x3f0d7f5c, 0x3f0ef1d3, 0x3f10641b, 0x3f11d626, 0x3f1347e6, 0x3f14b94c,
    0x3f162a4a, 0x3f179ad3, 0x3f190ad7, 0x3f1a7a48, 0x3f1be918, 0x3f1d5739, 0x3f1ec49d, 0x3f203136,
    0x3f219cf5, 0x3f2307cc, 0x3f2471ae, 0x3f25da8c, 0x3f274259, 0x3f28a906, 0x3f2a0e86, 0x3f2b72ca,
    0x3f2cd5c6, 0x3f2e376a, 0x3f2f97ab, 0x3f30f679, 0x3f3253c7, 0x3f33af88, 0x3f3509af, 0x3f36622d,
    0x3f37b8f7, 0x3f390dfd, 0x3f3a6134, 0x3f3bb28d, 0x3f3d01fd, 0x3f3e4f76, 0x3f3f9aea, 0x3f40e44e,
    0x3f422b95, 0x3f4370b1, 0x3f44b397, 0x3f45f439, 0x3f47328c, 0x3f486e82, 0x3f49a811, 0x3f4adf2b,
    0x3f4c13c5, 0x3f4d45d2, 0x3f4e7547, 0x3f4fa219, 0x3f50cc3a, 0x3f51f3a1, 0x3f531841, 0x3f543a0f,
    0x3f555901, 0x3f56750a, 0x3f578e20, 0x3f58a437, 0x3f59b746, 0x3f5ac742, 0x3f5bd420, 0x3f5cddd5,
    0x3f5de457, 0x3f5ee79d, 0x3f5fe79c, 0x3f60e44a, 0x3f61dd9d, 0x3f62d38c, 0x3f63c60e, 0x3f64b518,
    0x3f65a0a2, 0x3f6688a3, 0x3f676d11, 0x3f684de4, 0x3f692b13, 0x3f6a0495, 0x3f6ada62, 0x3f6bac72,
    0x3f6c7abd, 0x3f6d453a, 0x3f6e0be2, 0x3f6ecead, 0x3f6f8d94, 0x3f70488f, 0x3f70ff97, 0x3f71b2a4,
    0x3f7261b1, 0x3f730cb6, 0x3f73b3ac, 0x3f74568d, 0x3f74f553, 0x3f758ff8, 0x3f762676, 0x3f76b8c6,
    0x3f7746e3, 0x3f77d0c8, 0x3f78566f, 0x3f78d7d4, 0x3f7954f0, 0x3f79cdc0, 0x3f7a423f, 0x3f7ab267,
    0x3f7b1e35, 0x3f7b85a5, 0x3f7be8b3, 0x3f7c475a, 0x3f7ca197, 0x3f7cf767, 0x3f7d48c6, 0x3f7d95b2,
    0x3f7dde26, 0x3f7e2221, 0x3f7e619f, 0x3f7e9c9f, 0x3f7ed31e, 0x3f7f051a, 0x3f7f3290, 0x3f7f5b80,
    0x3f7f7fe7, 0x3f7f9fc5, 0x3f7fbb17, 0x3f7fd1dd, 0x3f7fe416, 0x3f7ff1c2, 0x3f7ffadf, 0x3f7fff6e,
    0x3f7fff6e, 0x3f7ffadf, 0x3f7ff1c2, 0x3f7fe416, 0x3f7fd1dd, 0x3f7fbb17, 0x3f7f9fc5, 0x3f7f7fe7,
    0x3f7f5b80, 0x3f7f3290, 0x3f7f051a, 0x3f7ed31e, 0x3f7e9c9f, 0x3f7e619f, 0x3f7e2221, 0x3f7dde26,
    0x3f7d95b2, 0x3f7d48c6, 0x3f7cf767, 0x3f7ca197, 0x3f7c475a, 0x3f7be8b3, 0x3f7b85a5, 0x3f7b1e35,
    0x3f7ab267, 0x3f7a423f, 0x3f79cdc0, 0x3f7954f0, 0x3f78d7d4, 0x3f78566f, 0x3f77d0c8, 0x3f7746e3,
    0x3f76b8c6, 0x3f762676, 0x3f758ff8, 0x3f74f553, 0x3f74568d, 0x3f73b3ac, 0x3f730cb6, 0x3f7261b1,
    0x3f71b2a4, 0x3f70ff97, 0x3f70488f, 0x3f6f8d94, 0x3f6ecead, 0x3f6e0be2, 0x3f6d453a, 0x3f6c7abd,
    0x3f6bac72, 0x3f6ada62, 0x3f6a0495, 0x3f692b13, 0x3f684de4, 0x3f676d11, 0x3f6688a3, 0x3f65a0a2,
    0x3f64b518, 0x3f63c60e, 0x3f62d38c, 0x3f61dd9d, 0x3f60e44a, 0x3f5fe79c, 0x3f5ee79d, 0x3f5de457,
    0x3f5cddd5, 0x3f5bd420, 0x3f5ac742, 0x3f59b746, 0x3f58a437, 0x3f578e20, 0x3f56750a, 0x3f555901,
    0x3f543a0f, 0x3f531841, 0x3f51f3a1, 0x3f50cc3a, 0x3f4fa219, 0x3f4e7547, 0x3f4d45d2, 0x3f4c13c5,
    0x3f4adf2b, 0x3f49a811, 0x3f486e82, 0x3f47328c, 0x3f45f439, 0x3f44b397, 0x3f4370b1, 0x3f422b95,
    0x3f40e44e, 0x3f3f9aea, 0x3f3e4f76, 0x3f3d01fd, 0x3f3bb28d, 0x3f3a6134, 0x3f390dfd, 0x3f37b8f7,
    0x3f36622d, 0x3f3509af, 0x3f33af88, 0x3f3253c7, 0x3f30f679, 0x3f2f97ab, 0x3f2e376a, 0x3f2cd5c6,
    0x3f2b72ca, 0x3f2a0e86, 0x3f28a906, 0x3f274259, 0x3f25da8c, 0x3f2471ae, 0x3f2307cc, 0x3f219cf5,
    0x3f203136, 0x3f1ec49d, 0x3f1d5739, 0x3f1be918, 0x3f1a7a48, 0x3f190ad7, 0x3f179ad3, 0x3f162a4a,
    0x3f14b94c, 0x3f1347e6, 0x3f11d626, 0x3f10641b, 0x3f0ef1d3, 0x3f0d7f5c, 0x3f0c0cc5, 0x3f0a9a1c,
    0x3f09276f, 0x3f07b4ce, 0x3f064245, 0x3f04cfe4, 0x3f035db8, 0x3f01ebd1, 0x3f007a3c, 0x3efe1210,
    0x3efb3086, 0x3ef84ff6, 0x3ef5707e, 0x3ef29239, 0x3eefb544, 0x3eecd9bb, 0x3ee9ffbb, 0x3ee72760,
    0x3ee450c6, 0x3ee17c09, 0x3edea945, 0x3edbd897, 0x3ed90a1a, 0x3ed63de9, 0x3ed37422, 0x3ed0acdf,
    0x3ecde83b, 0x3ecb2653, 0x3ec86741, 0x3ec5ab21, 0x3ec2f20e, 0x3ec03c23, 0x3ebd897b, 0x3ebada30,
    0x3eb82e5d, 0x3eb5861c, 0x3eb2e189, 0x3eb040bc, 0x3eada3d1, 0x3eab0ae0, 0x3ea87604, 0x3ea5e557,
    0x3ea358f1, 0x3ea0d0ec, 0x3e9e4d61, 0x3e9bce69, 0x3e99541c, 0x3e96de94, 0x3e946de9, 0x3e920232,
    0x3e8f9b87, 0x3e8d3a02, 0x3e8addb8, 0x3e8886c2, 0x3e863537, 0x3e83e92d, 0x3e81a2bc, 0x3e7ec3f3,
    0x3e7a4df9, 0x3e75e3b6, 0x3e718555, 0x3e6d3302, 0x3e68ece8, 0x3e64b330, 0x3e608606, 0x3e5c6591,
    0x3e5851fc, 0x3e544b6e, 0x3e50520f, 0x3e4c6608, 0x3e48877d, 0x3e44b697, 0x3e40f37b, 0x3e3d3e4d,
    0x3e399733, 0x3e35fe51, 0x3e3273cb, 0x3e2ef7c4, 0x3e2b8a5d, 0x3e282bba, 0x3e24dbfc, 0x3e219b42,
    0x3e1e69af, 0x3e1b4760, 0x3e183476, 0x3e15310f, 0x3e123d48, 0x3e0f593f, 0x3e0c8510, 0x3e09c0d8,
    0x3e070cb2, 0x3e0468b9, 0x3e01d506, 0x3dfea369, 0x3df9bdb7, 0x3df4f929, 0x3df055ed, 0x3debd432,
    0x3de77423, 0x3de335ed, 0x3ddf19b9, 0x3ddb1fb0, 0x3dd747fa, 0x3dd392bc, 0x3dd0001c, 0x3dcc903c,
    0x3dc9433f, 0x3dc61946, 0x3dc3126f, 0x3dc02eda, 0x3dbd6ea1, 0x3dbad1e2, 0x3db858b5, 0x3db60333,
    0x3db3d173, 0x3db1c38b, 0x3dafd990, 0x3dae1393, 0x3dac71a8, 0x3daaf3de, 0x3da99a43, 0x3da864e6,
    0x3da753d1, 0x3da66711, 0x3da59ead, 0x3da4faae, 0x3da47b1a, 0x3da41ff6, 0x3da3e945, 0x3da3d70a
};

static const uint32_t _K18[] = {
    0x000b0009, 0x000f000d, 0x00130011, 0x00170015, 0x001d001a, 0x0022001f, 0x00290025, 0x0030002c,
    0x00380034, 0x0040003c, 0x004a0045, 0x0055004f, 0x0061005b, 0x006e0067, 0x007d0076, 0x008e0085,
    0x00a00097, 0x00b400aa, 0x00cb00bf, 0x00e400d7, 0x010000f2
};

static const uint32_t _K25[] = {
    0xbc078db1, 0x3d0cd176, 0x3dcbcf7e, 0x3ea41859, 0x3e86636c, 0x3ceda3a6, 0x3da2f228, 0x3d6ccb44,
    0xbe4ce7ad, 0xbda14a68, 0xbe2e6286, 0x3e6f435c, 0x3e9eb91e, 0x3ec2cb57, 0x3db8790c, 0xbd0db42a,
    0xbeca3df3, 0xbdb5b6ef, 0x3e220871, 0x3dddf17f, 0x3dfe7428, 0x3eb69e7e, 0x3e03849b, 0x3de0a25c,
    0x3e3f8dfa, 0xbe5a6619, 0xbe40b487, 0xbcab8d5a, 0x3de16acd, 0x3e3002b0, 0x3d3c2792, 0x3e2bf75b,
    0x3dfd6094, 0x3e94199a, 0xbe0dcada, 0xbc0cb2c0, 0x3e191dce, 0x3e889688, 0x3eae8704, 0x3e0394bd,
    0x3e598732, 0x3e7c6f26, 0x3e3c94ce, 0x3e666641, 0x3eb5a442, 0x3e2dd906, 0xbdd5b011, 0x3e7c0f92,
    0xbeb3cbbc, 0xbe36e01a, 0xbde8baf9, 0x3e821392, 0x3e26395c, 0x3e7abbe4, 0x3ce76601, 0xbe835943,
    0xbe8b9d17, 0xbe97660f, 0xbe081c1f, 0xbc32250c, 0xbe61a9f1, 0x3ea40ee3, 0x3df73999, 0xbca257e5,
    0xbdfc9329, 0xbe4892d9, 0xbe9db62a, 0xbdb80256, 0x3d94fe4e, 0x3e1b1f1e, 0x3b9c5d39, 0xbe495c52,
    0xbd4d202a, 0xbd8bff0b, 0x3d744df0, 0xbe14f4a7, 0xbcf3c1b0, 0x3e872d54, 0x3e61942d, 0x3d30f832,
    0xbe9248a0, 0xbd8bdb77, 0xbe9cf969, 0xbdaa1691, 0x3db5d4a4, 0x3c8b0344, 0xbd2c1ba4, 0xbe18ce45,
    0xbe9434ef, 0xbe4dbcc0, 0xbd7d9005, 0xbc787a55, 0xbe136947, 0x3dc125ea, 0xbdc95f6f, 0xbe4ae3b7,
    0xbf019e4d, 0xbe84bdc4, 0xbe14bdba, 0xbe7cfdbd, 0x3d542121, 0x3df5f3da, 0xbca95463, 0x3e29ada9,
    0xbda2e66e, 0xbe2c5600, 0xbeb904c1, 0xbde11081, 0x3c8f06e1, 0xbe30fd98, 0x3bccba9d, 0xbdb579e1,
    0x3c89c8fa, 0xbe09836a, 0xbe15986e, 0xbe26aa7b, 0xbd422852, 0xbd37724f, 0xbc7741da, 0xbe811425,
    0x3ba5c785, 0x3d8efc3e, 0x3d9d9ae2, 0xbd8bec2f, 0x3e3c7bbe, 0xbcfb675b, 0xbdf25a19, 0x3d476f81,
    0x3d016e3f, 0x3d21f448, 0x3dd6d0bd, 0xbc8d94a2, 0x3d9807e5, 0x3ddeefe0, 0x3e02169c, 0x3cf0ad50,
    0x3e03640e, 0x3c9fcb01, 0x3aad06c1, 0x3dd3c556, 0x3de75a1c, 0x3c785be3, 0xba835cb0, 0x3d41ee74,
    0x3c1e727e, 0x3d27c9c3, 0x3d336776, 0x3d6dc533, 0x3e1502d0, 0x3cc275db, 0xbddd2e55, 0xbe13bce4,
    0xbd933c17, 0xbc633443, 0xbda5dcc7, 0xbdae451d, 0xbe29e124, 0xbdaa0b25, 0xbdce161c, 0x3b8f6c11,
    0xbd0d148a, 0x3dc64faa, 0x3ca98634, 0x3ba87528, 0x3d4e9a37, 0xbd9f1129, 0x3c68f24f, 0xbcacdfba,
    0x3dad41e8, 0x3debebcd, 0x3d3f3afc, 0xbc87500d, 0xbcf8bfc5, 0xbd0cbfed, 0x3d9333a8, 0x3ccd61e3,
    0x3e27dd36, 0x3de19b27, 0x3d2fcb09, 0x3c09c243, 0xbcb10f58, 0xbd1f4c49, 0x38288185, 0x3dc9834f,
    0x3d627f3c, 0x3da29124, 0x3c91f3ef, 0x3d801ecf, 0x3db4bf95, 0x3d425dcb, 0xbd7b5566, 0xbdde3c26,
    0xbcd50850, 0xbce11318, 0xbe087238, 0xbdb3ed83, 0x3c11f189, 0xbdcc4eb2, 0xbdd873be, 0x3ccbd337,
    0x3c60763e, 0x3e504152, 0x3d53cbc4, 0x3e16f84f, 0xbd91e309, 0xbd14db66, 0x3db70f65, 0xbe30d05f,
    0x3dca7e93, 0x3c9bdbc4, 0x3dd30926, 0x3d2b2f83, 0xbd1ed5d1, 0x3bae626b, 0x3dee04db, 0x3cad5165,
    0x3dd80f2c, 0x3d6864ef, 0xbd7b2ecd, 0x3d0aa20a, 0x3d06ba11, 0xbe0bda9f, 0xbdd54306, 0xbcabc10c,
    0xbbea8d71, 0x3d60e376, 0x3dc377ed, 0x3d680fc5, 0x3e287d1e, 0x3cc7f971, 0xbde07f96, 0xbd8d12e0,
    0xbda14085, 0xbdf67c44, 0xbe138fe8, 0xbb2ceb80, 0xbcc2f460, 0xbde57692, 0xbd7f0db0, 0xbd334592,
    0x3e3ece7b, 0x3defda53, 0x3cc83245, 0x3ceaacf0, 0xbb7c5218, 0xbe19e278, 0xbccdacf7, 0xbd493c17,
    0xbd193270, 0x3e26c677, 0xbc6ddca4, 0x3dc50abb, 0xbcf71e93, 0x3de61b19, 0xbe8a2df0, 0xbd8268e2,
    0xbd44e33d, 0xbe09f8fa, 0xbd4ae82e, 0x3e46e922, 0x3c9f93ed, 0xbdc91c0b, 0x3daff602, 0x3e15062c,
    0x3cd66d44, 0xbe9ee4c8, 0xbea9d6f1, 0xbe38d0f7, 0xbe7d8a22, 0xbe18a552, 0x3e50db95, 0x3d5391d8,
    0x3c660fea, 0xbcd75ee3, 0x3bc3a8ab, 0x3e177a79, 0xbe03b175, 0xbd4e33df, 0xbe3a6a4c, 0xbcad1ad2,
    0x3ed834ef, 0x3e0da8fa, 0x3e1ba75a, 0xbba88c20, 0xbc3159ff, 0x3c8b0672, 0xbde752ac, 0xbd20eee9,
    0x3d45b43d, 0xbc94d664, 0x3d518ca5, 0xbd92ec99, 0xbd324214, 0xbd048a60, 0xbe5ac69e, 0xbc814cb2,
    0xbd6b49e9, 0x3cfe0976, 0x3da4d066, 0x3da72cd6, 0x3e1626f4, 0xbe319283, 0xbdc2e5a9, 0x3dc2f5bd,
    0xbb923fb3, 0xbe7847f3, 0xbe3a6784, 0xbe910d73, 0xbe2f2e1e, 0xbc3993fb, 0x3d81bafc, 0x3df174fa,
    0xbdab8b8d, 0x3dbc1030, 0x3d02ff36, 0x3d8b033a, 0xbd8107b9, 0xbd408e8a, 0x3c939876, 0xbbc48fc4,
    0x3eb8b14e, 0x3e651e93, 0xbd31c8b9, 0xbd5701f4, 0x3c1641c3, 0xbdc4c023, 0xbe92c821, 0xbc89beab,
    0xbdeb4bf9, 0x3be85484, 0xbda77a3b, 0xbd9c55f3, 0xbd4bd018, 0xbd8d7ef3, 0xbd65209d, 0xbe0f359f,
    0xbcc87b99, 0xbda73607, 0x3e4e54ae, 0x3e9f4825, 0x3dce61dd, 0x3d85f304, 0x3da0e1d2, 0x3d9a6a7b,
    0x3dee9fa7, 0xbe36d53e, 0xbe6befbb, 0xbe3e2580, 0xbe385818, 0xbd014adb, 0x3e6599df, 0x3e125f17,
    0xbcc7fe69, 0xbc6247fa, 0x3d25315f, 0xbd57ddd1, 0xbe3959b9, 0xbe370299, 0xbc2296bb, 0x3cdfe67b,
    0xbee4bf9d, 0xbecb382c, 0xbe2c2e2b, 0xbf12c2ba, 0xbe9714a8, 0xbe855cfc, 0xbe8c11db, 0xbee3088f,
    0xbe419f22, 0xbe9c848d, 0x3e4c7b09, 0x3e8fef6b, 0x3ebcf6e4, 0x3e561a7f, 0xbb87c18b, 0x3dddc5a5,
    0xbe91e4ba, 0xbe8bbd88, 0x3de08ec9, 0x3d47cdf4, 0xbdda9aba, 0x3d7d3a5d, 0xbe380be7, 0xbe5a96a4,
    0x3d782ec3, 0x3da92912, 0xbe052973, 0x3e0da7c3, 0xbccba9a4, 0xbda29eca, 0xbeb66c03, 0xbe887245,
    0xbd7d7bdd, 0x3e23ff34, 0xbe200b2f, 0xbdc4100b, 0x3d963343, 0x3d9a30dc, 0x3da501c9, 0xbdaa6534,
    0x3dd1a7d4, 0xbd040866, 0xbb9ce093, 0xbe67dbda, 0x3e027c9c, 0x3e4e1550, 0x3db791e5, 0x3dfe4791,
    0x3df7ec8d, 0xbd8639ee, 0x3ee62f74, 0x3eb28d43, 0x3ef2857b, 0x3e1da47b, 0xbdba0c77, 0x3e248eb4,
    0xbd89c202, 0xbe643bea, 0x3e744d5d, 0x3e84ebab, 0x3e4b4ac9, 0x3dc4511d, 0x3bd54769, 0xbdb1c193,
    0xbcf9bd83, 0x3d797e75, 0x3e747f66, 0x3dab9ebe, 0xbd220a27, 0xbe304286, 0xbe36f943, 0xbda726fa,
    0xbdaa9a3e, 0xbdbc146d, 0x3ce98df9, 0xbdcae322, 0x3d96c5f2, 0xbdbfe247, 0xbc196dcb, 0xbef03c9b,
    0x3cfc2bb0, 0x3dc8c254, 0x3d277162, 0x3e1a9580, 0x3dcbb349, 0x3e909819, 0x3eb3a673, 0x3c918cfe,
    0xbd440248, 0xbd97be6e, 0x3e356198, 0x3df399ae, 0x3e1ee48b, 0x3e135432, 0xbe65b9d8, 0xbd9d05ab,
    0xbe81d85c, 0xbe218710, 0xbcb5d7a7, 0xbc6259e3, 0xbce6fd79, 0x3e22355b, 0x3d8838c8, 0xbe95bb7b,
    0xbe517689, 0x3cf42e10, 0x3e0831ff, 0xbc753a9e, 0xbccaf4dd, 0xbd8756bd, 0x3e2ddc06, 0x3e455186,
    0x3e842cf1, 0x3e858599, 0x3d4694fd, 0xbcdf1d0f, 0x3e0f57d6, 0x3d39edbb, 0xbdf5cd8d, 0xbe7504ec,
    0x3cbdd7de, 0x3d598486, 0x3d0abba7, 0x3db458bd, 0x3d876abd, 0xbd2cd328, 0x3cadaa6b, 0xbbdfa2fd,
    0x3d9f3534, 0x3d011f40, 0x3cb15eb3, 0x3d6a94d1, 0x3dd381cc, 0x3d834c90, 0x3d62a519, 0x3ce03fc3,
    0xbc9241ce, 0xbbf787f6, 0x3b3964b4, 0xbce8ce40, 0x3c77c3da, 0x3c84fa4c, 0x3c9a8b71, 0x3d850535,
    0x3cd61e36, 0xbc84cbbd, 0xbb2aa75f, 0xbcfdd6a0, 0xbd559434, 0x3bef2360, 0xbddbb3ed, 0xbd899537,
    0xbd7b60df, 0xbcf3dbef, 0xbd9e6a9c, 0xbdb2bc67, 0xbd977dba, 0xbd9c9968, 0xbd9358fc, 0xbcb8ef1c,
    0x3b8ddc0d, 0x3d0efb4c, 0x3cd87f85, 0xb9782f89, 0x3d746667, 0xbd8d4811, 0x3d4c3485, 0xbcf7d928,
    0x3db7f19f, 0x3d2ae0f2, 0xbc2f03ea, 0x3d4f6e28, 0x3dc1794f, 0x3db736f4, 0xbd07daa3, 0xbcc436e1,
    0xbd3dfe08, 0xbbac93e0, 0x3d2327e5, 0xbd29fa98, 0xbd2302ca, 0x3baf4741, 0x3d3ee960, 0x3c3f20e1,
    0x3d8c9535, 0x3c7518d5, 0xbde8b0d3, 0xbda87bdb, 0xbd4ba495, 0xbd117387, 0xbd118228, 0xbda4b298,
    0xbc9d9745, 0xbcb88a34, 0xbc8e664b, 0xbdc26802, 0xbe17fac1, 0xbe03fed0, 0xbda4d820, 0xbda0bb7d,
    0xbd156083, 0x3c936fbb, 0xbd8db396, 0xbd1b5e8b, 0xbd02236c, 0xbda0f150, 0x3cb3bb04, 0xbd1b9e83,
    0xbb62aadb, 0xbd86d9af, 0xbd001107, 0x3d366267, 0xbc413961, 0x3daddb44, 0xbd834ce0, 0xbc49be60,
    0x3ae62138, 0xbb3d5fcb, 0xbd9389b8, 0x3ca2e293, 0xbda1b5b9, 0xbdc404f1, 0xbd4f4f09, 0x3ada9ecd,
    0x3c1b9cf7, 0xbd8824f0, 0xbdbca8aa, 0xbda82f16, 0xbdb1e0d8, 0xbc87fea0, 0xbdc04e5c, 0xbd8b4565,
    0xbb579ab0, 0x3d38122d, 0xbd0f8d90, 0xbd10b852, 0xbde519a1, 0xbde8d96e, 0xbd1889d1, 0xbdff1f79,
    0xbccc4d74, 0x3b254b38, 0xbdaeb7ec, 0x3daee9b1, 0x3dbd92a0, 0x3b7709bb, 0xbd0ab8af, 0xbdf75014,
    0x3e426d08, 0x3da3456a, 0x3e35ef2d, 0x3e6e8eaa, 0x3d5f32c0, 0xbd0a7aa0, 0xbe5abf11, 0xbc9fd27f,
    0xbda41b55, 0xbd8300a2, 0x3e0bdf55, 0x3e609af1, 0x3df17b26, 0xbd79a3d5, 0xbd5a3bcf, 0xbd1c95cf,
    0xbd8ae1bc, 0xbd1479f7, 0x3e424a23, 0x3d2bbef5, 0xbe80e1ae, 0xbd640207, 0xbdf35da2, 0xbdc6c5b9,
    0x3d46c540, 0x3cf5029d, 0x3cb05fe5, 0x3e022ed8, 0xbdb0044d, 0x3d9190a6, 0xbdf4a42b, 0xbe0f159f,
    0xbdc99f32, 0xbdac0fff, 0xbdb562ba, 0x3d05e0f2, 0xbd127c2f, 0xbd7859a2, 0xbdc24b9e, 0xbe17e674,
    0x3dabf9b5, 0xbd716f91, 0x3c7da457, 0x3dcbcd34, 0xbe69b6a5, 0xbe1b28f6, 0xbeaf1d07, 0xbd8e1130,
    0xbdde9cd9, 0xbd9b857c, 0xbc986fee, 0x3e5cf11e, 0x3ddc7730, 0xbcbdbb49, 0xbd957203, 0xbd0dd60f,
    0xbd9f0824, 0x3c915116, 0x3e44cd96, 0xbcc5e1b9, 0xbe1dbf61, 0xbe548cd7, 0xbd3590ce, 0x3d4cbcad,
    0xbcd02bcc, 0x3e5cd77f, 0xbc4b67b3, 0x3cce3f75, 0x3e1577d7, 0x3d5ef1f8, 0xbd692b1d, 0x3ce16869,
    0x3d27ca6a, 0xbe40b525, 0xbd52e9c6, 0x3e5ac4e7, 0xbd0c3f06, 0xbd37333b, 0x3c335b8b, 0xbddbd33f,
    0x3db99d0c, 0xbd098ee8, 0x3c1b20e8, 0x3dd77a1a, 0xbe681739, 0xbeb847b3, 0xbeb8422a, 0xbdf7ac2e,
    0x3d561715, 0x3db55090, 0x3a6c8343, 0x3da726f9, 0xbd767a85, 0xba6ad66a, 0x3c8d9487, 0x3d9a3973,
    0x3da515e2, 0x3adb8d9d, 0x3e71b123, 0x3dc4e867, 0xbdfbff46, 0xbe640e35, 0x3cfed31b, 0xbd1d3a07,
    0xbcfdfd41, 0x3dd41aac, 0x3d468550, 0x3dd73aa2, 0x3dfc8590, 0xbc9c6e12, 0xbcdc9ab4, 0xbd03db37,
    0xbe0cadca, 0x3d8c6c94, 0x3dbee2ef, 0x3d4709f7, 0xbe372737, 0xbe660e55, 0xbe35cdc9, 0xbe807e06,
    0xbe15786f, 0xbde9c6e3, 0xbe6bfd05, 0xbd2f31c7, 0x3dba688b, 0x3e2365ad, 0xbd2ecbed, 0xbe25d48f,
    0x3d16a5b1, 0xbe15f14c, 0xbe905213, 0xbe12c3cc, 0xbe46f26c, 0xbdb42053, 0xbd9236c8, 0xbe050542,
    0x3ccab58f, 0xbc78a613, 0xbdecb79d, 0xbd90c518, 0xbcfe1036, 0xbd51806e, 0x3dfc9fa2, 0x3e06630a,
    0x3c5dd63c, 0xbe2ce9ff, 0xbe2e8b88, 0xbe1797d1, 0xbcb1edc1, 0xbda81587, 0xbe0310fb, 0xbb0562c8,
    0xbe83b284, 0x3d753403, 0x3e84a5d1, 0x3df2b530, 0xbba7354c, 0xbe3fa847, 0xbdc80434, 0xbdd77176,
    0xbe10feff, 0xbd92c6ae, 0xbe5ab73b, 0xbe3a548f, 0x3dd2a123, 0xbd4ef996, 0x3e66b66f, 0xbd8773d8,
    0x3c9a20a8, 0x3da348d0, 0xbd67fa46, 0x3c39adcd, 0xbe0d1566, 0xbd8ca5de, 0x3d9a98c3, 0x3dfb627e,
    0x3e5b4dbc, 0x3e2e47c9, 0xbd9d2b59, 0xbe047908, 0xbd8d1b62, 0x3de4d416, 0x3c87a092, 0x3dc30045,
    0x3d269b54, 0x3e0a1d48, 0x3dfc08f8, 0xbd927abd, 0xbd35b255, 0x3dcccf75, 0x3e1951e9, 0x3ddaeae7,
    0x3def41f8, 0x3e29b004, 0x3ed2fb3a, 0x3e9c750d, 0xbd5ed213, 0x3d8982a9, 0xbe650f6f, 0x3e47dc98,
    0xbdad0968, 0x3b8fcbd9, 0xbe8b627f, 0x3ce57e18, 0x3e0fe702, 0x3e5ffdfc, 0x3e5fd582, 0x3b9c9476,
    0xbd27e2d3, 0x3e3a666c, 0xbd7ca6b4, 0xbda5f0e2, 0xbe009f29, 0x3cb8a521, 0x3bd2a4dd, 0x3dcde8ab,
    0x3d2a4e9c, 0x3bc537d5, 0xbba04d39, 0x3d2ff357, 0x3df9c905, 0x3dd372e7, 0x3e37dc62, 0x3dcf9e01,
    0xbca7d67f, 0xbcb25d02, 0x3d915573, 0xbbe0975e, 0x3c017feb, 0x3d2a93de, 0x3e8a9f43, 0x3df82863,
    0x3d86c620, 0x3b915f41, 0x3c683ece, 0x3d8a0403, 0x3d17d5c1, 0xbdd37af0, 0x3c35b4e1, 0x3d868845,
    0x3e001b47, 0x3dc6dc43, 0x3dfe42ee, 0x3c8ba8ed, 0xbddc9884, 0xbd0e2376, 0x3cb6ed05, 0x3d63e7ef,
    0x3d0c168f, 0xbcf05cb6, 0xbe40eb99, 0xbe09f979, 0x3d8d2ef8, 0xbc41e0d4, 0xbe1cd8c4, 0x3b057bfa,
    0x3dd698ab, 0xbd84d83d, 0xbda25623, 0xbc2f7afa, 0x3df6c86f, 0x3d85ba00, 0x3e1344a4, 0x3e0558b9,
    0x3dba0a8d, 0xbd49ae14, 0x3d71e72c, 0x3db25a56, 0x3e21f119, 0x3d9a746b, 0xbc9b8245, 0x3dfd9c25,
    0x3d0eb0e8, 0xbde9350b, 0xbd7077c6, 0x3e2d1578, 0x3d28eb6c, 0x3d0b3ae0, 0xbc04e458, 0x3dcf718f,
    0x3de15f1d, 0x3df13a5e, 0x3dca982f, 0x3dba98c6, 0xbd936cfd, 0xbdb09333, 0xbd1019eb, 0x3d31a3b5,
    0xbca4c5a7, 0xbd24e847, 0xbd82ad3a, 0xbccdd46a, 0x3c7c0d74, 0xbd9624b3, 0xbd18bee9, 0x3bcb27d6,
    0xbc68786c, 0x3d5bb733, 0x3c52aa7a, 0xbd5dbc87, 0x3b7395ec, 0xbd79c37e, 0x3e23d8f1, 0x3c7501c5,
    0x3d915081, 0x3c8daf44, 0xbcc01214, 0x3cfecf3f, 0xbc5c88b2, 0xbd59e1ab, 0xbe42acda, 0x3d7c780a,
    0xbd97c0aa, 0x3e04b0bd, 0x3ddcc01a, 0x3e1060d7, 0x3b8955f5, 0xbdd209c0, 0xbccdc62d, 0xbc422be5,
    0x3da6ee55, 0x3e306b97, 0x3d9d8540, 0x3acb69ec, 0xbdd52409, 0x3b61f2b6, 0x3d929ef3, 0x3ccd2aa3,
    0xbde5f2e2, 0x3d294dad, 0x3be70058, 0xbdf9125c, 0x3db687c0, 0x3d9cab81, 0xbd84d77b, 0x3ca375bb,
    0xbd76527c, 0xbddaac16, 0xbdb9b818, 0xbd57f216, 0x3d270605, 0x3dbb2356, 0x3e2c0cf0, 0x3e1b8c2a,
    0x3e2086c2, 0x3dc639b4, 0x3df6e029, 0x3d5a59f1, 0x3ce69c95, 0xbe06e9de, 0xbdb738d8, 0x3e4a8ea4,
    0x3ccb8be4, 0xbd53b837, 0x3d840170, 0x3d3f2c32, 0xbbbd100c, 0xbdb43ba5, 0x3d734e9f, 0xbdeb175f,
    0xbd4a51b7, 0xbe246c9f, 0xbd6a336b, 0xbd519478, 0xbdf83d5b, 0xbdc50cd3, 0xbd52b2ee, 0x3dad4dcc,
    0x3be9dd7e, 0x3dce189a, 0xbdc4ac41, 0xbc889e35, 0x3d2c0d08, 0xbdedf4f2, 0x3dce4f18, 0x3e055dde,
    0xbdf99c48, 0xbe2753b6, 0xbc20cb15, 0xbda75986, 0xbd1a2171, 0x3cd73dac, 0xbbc7204a, 0x3d2485ab,
    0x3caa1128, 0x3da51e80, 0x3d4337aa, 0x3d21454c, 0x3c0001db, 0xbdb8f22a, 0xbd5cd564, 0xbda2343b,
    0xbd97d876, 0xbd6a3377, 0x3d83d3e9, 0xbd8a22c2, 0x3d63e742, 0x3a2eeee2, 0xbca4f41d, 0xbdeb36c2,
    0x3c8477e6, 0xbe4a3d5e, 0xbda32972, 0xbe4ca83e, 0xbdced579, 0xbe11ef94, 0xbd93f73c, 0x3dfa8091,
    0x3d86f7bf, 0x3e883853, 0x3de61813, 0x3e16f268, 0x3cf77fae, 0x3c71fce1, 0x3e262e3d, 0x3d9d45ef,
    0x3cdf7e4f, 0xbd9ab064, 0x3cd571cd, 0x3cdbbe5a, 0xbd7c9282, 0x3ca07356, 0x3de617fe, 0x3e14d530,
    0x3d3ffba7, 0x3e8b1695, 0x3e40f84a, 0x3e5e986a, 0x3db6d365, 0xbd4cbfdd, 0x3dabc0b7, 0xbe069436,
    0x3d05a68e, 0xbbba93b4, 0x3e3d11d3, 0x3dfb8f45, 0xbd8779a7, 0x3d07849a, 0x3da30663, 0xbcdcad63,
    0x3e1fd181, 0x3d889e3d, 0x3df92fd3, 0xbc8727f9, 0x3d061dd4, 0xbd5df9db, 0x3e33014a, 0x3e9dfa8a,
    0x3e56b972, 0x3ea6a77f, 0x3cf903bc, 0x3e8514a6, 0x3e0f570f, 0x3d864eb0, 0xbd179eb1, 0x3d81ddf0,
    0xbdf0a5ee, 0xbccea8cd, 0x3e05e310, 0x3d85783a, 0x3c2d5b41, 0xbd479e7a, 0xbcd16cc8, 0xbd828d37,
    0xbc979321, 0x3d0ff99e, 0x3d6aa20c, 0x3d9a521a, 0x3de7981a, 0xbd960247, 0xbe2073df, 0xbe1a7448,
    0x3dcdd3b8, 0xbce474f8, 0xbe1a1a61, 0x3e360d25, 0xbca99722, 0x3d8a1b7c, 0x3d9e12cf, 0x3db3b5f2,
    0x3e2aa913, 0x3cf90daa, 0x3e4d5a39, 0xbd7c1960, 0xbd3e3809, 0xbddd057f, 0xbe398ba3, 0x3e25312b,
    0x3c7abf13, 0xbdc4bc50, 0xbe29972c, 0x3dc87351, 0x3d898abf, 0x3e275cd3, 0x3daf11dd, 0x3e21a1fa,
    0x3e502319, 0x3db449c4, 0xbd2a222a, 0xbe01e970, 0xbd54b1e5, 0x3e0be21e, 0x3c69ddc1, 0x3db354e5,
    0xbdbb1461, 0xbc072239, 0xbca76086, 0xbc4dfb58, 0xbd800fd4, 0x3c536ec1, 0xbe07fda1, 0xbd3a4685,
    0x3e1f11b1, 0xbd7f99d2, 0xbd07c8d4, 0x3cd66cbb, 0x3c546cf0, 0x3d3e5334, 0x3eb7c9e6, 0x3e88c80f,
    0x3e05d08c, 0xbe06b83b, 0x3e6c2fe1, 0x3db7b9f7, 0xbe5d39fd, 0xbe8c3da0, 0xbe443840, 0x3d1f6468,
    0xbe15610f, 0xbda8cd59, 0xbe03f4b8, 0xb727662d, 0xbd0b7418, 0xbdade6a9, 0x3c78498f, 0x3db167f5,
    0x3d5231a5, 0xbd964045, 0xbcf96fbd, 0xbccf0190, 0x3c2dffc3, 0xbd518404, 0xbd5f4d0e, 0x3dc3041f,
    0xbd846327, 0xbd82bd79, 0xbc09f74e, 0xbdda9d3f, 0xbc8cb365, 0xbdcdaee2, 0xbe50652a, 0xbe6b3288,
    0xbd315bcb, 0x3dd23bbd, 0xbcdd3906, 0x3daae000, 0xbd7679da, 0x3d070da3, 0x3e7379d0, 0xbcbd2297,
    0x3df3798b, 0x3b95c555, 0x3d93e927, 0x3dba6912, 0xbe0251fb, 0xbe4f7cfb, 0xbdd3d537, 0xbd34ebd1,
    0xbe96ab26, 0xbe672490, 0xbe090891, 0xbe556d40, 0xbc1cca73, 0xbddcbe98, 0x3e1c206b, 0x3e0cac52,
    0x3da366ca, 0xbd5d77a0, 0x3d78f297, 0xbd303715, 0xbd065ded, 0x3d9a201a, 0x3cbec104, 0x3e19e912,
    0x3d4bf12b, 0x3d265b98, 0x3d0455a8, 0xbddd89e2, 0x3d334881, 0x3b460bf8, 0xbe0c07ac, 0xbd9ddedf,
    0xbd6fb5a4, 0x3ce69e60, 0xbd985707, 0xbdf60315, 0xbd386c26, 0xbd54fb09, 0xbda0b0b3, 0x3cf2781e,
    0x3e0734c4, 0xbdd5db36, 0xbe1675cb, 0x3c948aa9, 0x3dd77696, 0x3c61a0cb, 0xbce7bc67, 0xbd183e70,
    0x3d2b01f5, 0xbcb1019e, 0xbe55578c, 0xbe16d3b3, 0x3cb73217, 0x3e1dba3f, 0x3d38dea2, 0xbdcd5aea,
    0xbe16e389, 0xbd5eec67, 0xbd1862fd, 0xbbe0ab07, 0x3d8c6723, 0x3c8fc5f5, 0xbd208cb9, 0x3cd0e164,
    0x3c4d9d42, 0xbd6b5482, 0xbdc8534a, 0xbd39c3db, 0x3d53149d, 0xbb31f76a, 0x3dc7595d, 0xbcca6fec,
    0xbe7e786a, 0xbe41fa86, 0xbe13ea81, 0xbe0f0f83, 0x3c8d762a, 0xbd8dc9f1, 0xbc335f8e, 0x3ddbce99,
    0x3c55d4e0, 0x3ce873fd, 0xbdafc419, 0xbab69b5a, 0x3d223ffc, 0xbd3c4b3b, 0x3d8c7fda, 0x3cfd38ed,
    0x3d81a180, 0x3b0a1f4d, 0xbde4724d, 0xbe143d5e, 0xbcbaa909, 0x3cdce58e, 0x3d5cff33, 0x3c84d63b,
    0xbccbd9ca, 0xb9e9ba1a, 0xbde224e3, 0xbdb29248, 0x3db660c1, 0x3bc95949, 0xbc750bca, 0xbcee444f,
    0x399a1141, 0xbd73f317, 0xbc008052, 0xbb8964e8, 0x3dbe3d37, 0x3d86df15, 0x3d8b9cab, 0x3d8b5db5,
    0xbea18a43, 0xbe2ee35b, 0xbcf7ca41, 0xbd12b154, 0xbcca96c7, 0x3cd8eafb, 0x3d343004, 0x3db579b9,
    0x3e2c69c7, 0x3d9d6fb0, 0xbe07c9cf, 0xbcafa664, 0x3dfc5d3e, 0x3b0391ed, 0x3c830afa, 0x3c351981,
    0x3bd9ddcc, 0x3d74b88d, 0xbda3ef6e, 0xbe2b56c8, 0x3d1867fa, 0x3d81540d, 0x3dd743f2, 0xbd9215ce,
    0x3cb95ef0, 0xbd2b3bc9, 0xbd9fee08, 0xbd8debf7, 0x3de48997, 0xbb103460, 0xbd062824, 0xbcb66c02,
    0xbc48baac, 0xbdb04857, 0x3b831c5e, 0x3d4e3771, 0x3cf83b23, 0xbc1ef935, 0x3de92019, 0xbbcf5b52,
    0x3e80539b, 0x3cb0a65e, 0xbd4983cf, 0xbe2777ae, 0xbe837555, 0x3e51af7e, 0x3c6eb6b4, 0xbdd90385,
    0x3a41ad47, 0xbdc5b99b, 0x3d22992c, 0xbcc2eb51, 0xbcd7b241, 0x3e1ce54f, 0x3c012e2b, 0x3ec28fce,
    0x3e84355e, 0x3e426d5b, 0x3ce9be3e, 0xbcb4d5d7, 0x3e03348a, 0x3da1c4cb, 0x3b869af0, 0x3d1f3078,
    0x3d27186c, 0xbc949d0e, 0xbd8ded9b, 0x3cf2af83, 0x3cd15edf, 0x3df59a9b, 0x3d9ecf85, 0xbd37f39f,
    0xbda445af, 0xbd39b4d4, 0xbda96921, 0x3e31f77b, 0x3e4c604e, 0x3da4e904, 0xbc0ed894, 0xbe8f17fc,
    0x3e68a849, 0xbd9afdfe, 0xbd894ea0, 0xbe405f16, 0x3dc015f2, 0x3e91e578, 0x3d6aa3db, 0x3e4a1f5e,
    0xbdee6571, 0xbb52600d, 0x3de1f18c, 0xbe007496, 0x3dab9ea8, 0x3e0ac33e, 0x3d98cbda, 0x3ddd253c,
    0x3e5aff2e, 0x3d179803, 0xbd6d2c13, 0x3cba249c, 0x3dbd6535, 0x3d3dbf7b, 0xbd3d0886, 0x3e116d02,
    0x3c8c1d8e, 0xbcdaf4a8, 0xbe2e4a65, 0xbd916b36, 0xbc97e103, 0x3ce1d3a5, 0x3e090afd, 0x3dd15388,
    0x3d8be9a8, 0x3d43f71b, 0xbd54dbd5, 0x3b29dce6, 0x3d88c555, 0xbd154cc7, 0xbe092b61, 0xbe85df29,
    0xbcc5845e, 0x3e9aec7f, 0xbdc6a2ee, 0x3cc1f5c8, 0xbc76a0a9, 0x3e268456, 0x3dfe9ef3, 0x3e206fc0,
    0xbd26c535, 0xbdf542ce, 0x3d37c58d, 0xbd07945d, 0x3e55a314, 0x3e537f18, 0xbd50fda8, 0x3d0b235c,
    0xbce3e5dc, 0xbda73f56, 0xbc5f7a9c, 0xbe322f9f, 0xbe702fd6, 0xbde1062d, 0xbd802e8d, 0x3d8e3026,
    0xbce954af, 0xbd576574, 0xbd63256b, 0x3dfd5428, 0x3ddacb17, 0xbaf097eb, 0xbd7be1cf, 0xbc2adb71,
    0x3c839f83, 0x3c65e1fc, 0xbdb9d36a, 0xbdda7ac2, 0x3ccf92d6, 0xbe55e4ff, 0xbe913001, 0xbec81032
};

static const uint32_t _K27[] = {
    0xbec4b3cf, 0xbf3b99a3, 0x3f18b4e3, 0x3de9787a, 0x3bbed9a0, 0x3f867038, 0x3ef9b69a, 0xbe8d29b6,
    0xbf18fd98, 0xbec9ebcc, 0x3f7afa3a, 0xbf4df352
};

static const uint32_t _K30[] = {
    0xbdd1dfcd, 0x3cc24ba1, 0x3e93571c, 0x3efe0117, 0x3e10efe7, 0x3d82aa7a, 0x3d898a35, 0x3d02f10f,
    0xbe79578a, 0xbc84abef, 0xbdd59c79, 0x3e0c210c, 0x3de03b9a, 0x3e5cf18a, 0x3dd56ccb, 0x3e89b9ae,
    0x3e819780, 0x3e8cee8f, 0x3cad1b86, 0xbdc9590e, 0xbe97d91c, 0x3d6317b0, 0xbe7167f6, 0xbe9fcd86,
    0xbe27cebd, 0x3e49f280, 0x3e0830f1, 0xbe54b61b, 0xbe8e9861, 0x3d362f48, 0x3d80075c, 0x3e6e837d,
    0x3e83e4bc, 0x3e833359, 0xbdf2f08b, 0xbce53430, 0x3eaee662, 0x3f0ac880, 0x3e711ab8, 0x3cfc3eb8,
    0x3dcde98c, 0x3ec5b859, 0x3dcefe35, 0x3d9877ff, 0x3dd5527d, 0x3dfc5304, 0x3e4222b2, 0x3f035516,
    0x3ddf8004, 0x3e491ea7, 0xbe826613, 0x3d35a8fe, 0x3ed3b4e7, 0xbe46ca6e, 0x3eb5d187, 0xbe09dafb,
    0x3dd2135c, 0xbde98bd8, 0x3d393b96, 0xbe32f263, 0x3ebfa8b8, 0xbea6f964, 0x3c803da4, 0xbe57777e,
    0x3f20251e, 0x3ec7bb74, 0x3e598409, 0xbe68acfa, 0x3d9c9f94, 0xbe86236c, 0x3e2ac890, 0xbee33f31,
    0x3c70d3eb, 0xbce7e12f, 0xbccd7a44, 0xbed06329, 0xbeb70df4, 0x3e6b75eb, 0xbe0b9fae, 0x3d007dc4,
    0xbd18092c, 0xbdd95ac8, 0x3e95fedc, 0xbe057d64, 0x3dcb1db9, 0xbe1dac73, 0x3f2f8df1, 0x3d859de1,
    0xbd1afab0, 0xbebcce5f, 0xbeeecb9e, 0x3e970989, 0x3e5fee57, 0x3e18b4b1, 0xbc100516, 0x3f012b28,
    0xbe44bcfa, 0x3e646ebe, 0xbdad84ae, 0xbe2d31d2, 0x3e29b874, 0xbe967994, 0x3d25b633, 0x3dd9b372,
    0x3d4b1d0d, 0xbe940cfa, 0x3e18f6e7, 0xbd5a7c08, 0xbe09fc37, 0xbe205b60, 0x3e704922, 0x3c22e08b,
    0xbea03e81, 0xbb7ef6bc, 0xbdd1c02f, 0xbed91191, 0xbe7b4e1e, 0xbe550826, 0x3ea57d69, 0xbd5b57e3,
    0xbe724073, 0x3d7d7bec, 0x3e21bec5, 0x3e95a523, 0xbea56403, 0xbc789298, 0x3eb8e495, 0x3e6d43b7,
    0xbec61677, 0x3da01904, 0xbddd1747, 0xbda48eb8, 0x3f08e5dd, 0xbd52ab12, 0x3ee0a668, 0xbd9d48b2,
    0xbdb04c6c, 0xbe7809d3, 0x3e331084, 0x3dbeba3c, 0xbe900dc2, 0x3e88641e, 0xbec068fc, 0x3d6a892e,
    0xbda5ee10, 0x3da99dc7, 0x3ed8dd44, 0x3d911b5e, 0x3e0a8642, 0x3c9dddce, 0xbd931063, 0xbe97ec59,
    0xbe4a9060, 0xbe245c5b, 0x3e77fb07, 0x3d35ac47, 0xbe66f942, 0x3e33b9ca, 0x3ed252fa, 0xbe05faff,
    0xbe50ead6, 0xbe16a4ea, 0xbd438e2c, 0x3e8ed8b1, 0xbeaaaa00, 0x3e3e86ef, 0x3e85e996, 0xbd5e3166,
    0xbdfb606e, 0x3e8180ac, 0xbe1a6b62, 0x3d804ef4, 0xbb9a219c, 0xbbb42cd9, 0xbe832700, 0x3eb301e9,
    0x3e0f6c82, 0x3ebaf4b8, 0x3e169e67, 0x3ed9a0a4, 0x3ef22125, 0x3e162e2a, 0x3df02730, 0xbf0bb0b6,
    0xbd448e3f, 0x3e8b4c16, 0xbec91711, 0xbd892a1c, 0xbdd554fe, 0x3e0aa1a5, 0xbef088d2, 0x3de6e9b6,
    0xbed5df11, 0x3dd31914, 0xbe2d6f7e, 0x3db95aa4, 0xbd8965c3, 0xbbfbfaf3, 0x3edf89e5, 0xbd258ddc,
    0x3e2fec54, 0x3db117eb, 0x3dcfe83c, 0x3e37a06e, 0x3cf225d1, 0x3e4af157, 0xbe491cc2, 0x3d004680,
    0x3d1177ee, 0x3e9037b0, 0xbe9e8cdf, 0xbe0f6861, 0x3e5ebb8c, 0x3d1c0bd4, 0x3e8cd2a6, 0x3e9e164b,
    0xbd950859, 0xbe45859d, 0x3e871dff, 0xbeacaa8e, 0xbdeff656, 0xbec9077c, 0x3df7759a, 0x3d76de8c,
    0xbddb35a5, 0xbe8acc63, 0xbe8eb958, 0x3e746081, 0xbdc75fd2, 0x3e5bf322, 0x3f0db434, 0xbe84ffa3,
    0x3d4a191e, 0xbe515561, 0xbd974289, 0x3e0d5db8, 0x3e009fc8, 0xbe504975, 0xbe8dd6dd, 0x3e708271,
    0xbddcfa35, 0x3edf273f, 0x3e7707ad, 0xbe5a9f4f, 0xbe4a266a, 0xbe9f036c, 0x3e89a8d6, 0x3dcca923,
    0x3b94fc96, 0xbe196a13, 0xbe84fa41, 0xbe138ff6, 0xbe8a7d6a, 0xbe22a3dc, 0x3e9816b5, 0x3dabd407,
    0x3e9358a6, 0x3f105a94, 0x3dc725ab, 0xbd206982, 0xbdc7e7ed, 0x3e214270, 0x3e967d1d, 0xbd1c1cea,
    0xbe5d1fb3, 0x3de943ea, 0x3d942815, 0xbddb9839, 0x3de0ce52, 0x3e5eed46, 0x3e392471, 0x3e975842,
    0x3e48287d, 0x3da0cd05, 0xbdfff4f5, 0x3e9854c5, 0x3df63f12, 0x3ea6a07b, 0x3e12c8ca, 0xbe5d97c9,
    0xbd16d436, 0x3e469b9a, 0x3d5f298b, 0x3db169e9, 0x3ec95b4c, 0x3ea08824, 0x3cd1acf1, 0x3de4c5df,
    0x3ecc5c50, 0x3e95074d, 0x3f0c1e6c, 0x3dc76c73, 0xbe815aee, 0x3e0c26e3, 0xbdbcb01d, 0x3ef360a8,
    0x3e41ac0a, 0x3ec125ec, 0xbe1747c7, 0x3e87d001, 0x3e0d54e5, 0x3db4f695, 0x3e81921a, 0x3dfd9ac1,
    0x3e4aa06c, 0xbe22f3e8, 0x3d92dfd1, 0x3c66a212, 0xbe440bce, 0xbc4d9d45, 0xbbbcc2b1, 0xbd9da916,
    0xbeca9076, 0xbea118f7, 0xbec4d94a, 0x3d88f662, 0xbe962ca7, 0x3f0af7fa, 0xbe9619db, 0xbe02527b,
    0x3e5c94f9, 0xbe9d11a1, 0x3e091907, 0xbe33277a, 0x3e5aab8a, 0xbd8a30dc, 0x3b10a9ca, 0xbefb2321,
    0x3e03ed0f, 0xbc8d8e2c, 0x3d4691fb, 0xbd0519e9, 0x3e5a3e0f, 0x3eab5532, 0x3da45bf8, 0x3d901524,
    0xbd9d63d1, 0xbe0d1498, 0xbcc45d72, 0x3c7c03cb, 0x3dc9444b, 0xbdd3dab8, 0xbdc0de95, 0xbeb322bb,
    0xbe4babdc, 0xbe0d1850, 0xbe924863, 0xbdbe4e86, 0xbe747754, 0xbe95c446, 0xbcf02e34, 0xbdc87303,
    0xbe544352, 0xbe160c26, 0xbf29e16f, 0xbef0f7c9, 0xbebfa61b, 0xbd5bb415, 0xbe2d5598, 0xbdc11bb1,
    0xbd0b53a4, 0xbd7aea0c, 0xbe1ce45b, 0xbc20e5d9, 0xbe7015cc, 0xbe8295d3, 0xbeba6317, 0x3df6a974,
    0xbdcf5401, 0x3c1d3ae7, 0xbed2e04b, 0x3ebb45fb, 0x3da63302, 0x3e32e07d, 0x3e6fb2d2, 0x3ed13b2b,
    0x3e2197a6, 0x3d1c0f04, 0xbe497157, 0x3e3a634c, 0xbe2f7b35, 0xbe84014a, 0xbe875c2d, 0xbe25d0ed,
    0x3d9432fb, 0xbcb34336, 0x3eb2b0de, 0xbdcfbc68, 0xbcf69b18, 0x3c13faa1, 0x3e8363f8, 0xbd811981,
    0x3e9635f3, 0x3d992cad, 0xbeaf3dd9, 0xbebdc6a0, 0x3e2bd9ae, 0xbdaa1fa1, 0x3c9ba292, 0xbe12aa60,
    0xbcfc6cf4, 0x3dc53bbb, 0x3c225a1e, 0x3e0367a0, 0x3c4d4049, 0xba0353ca, 0xbeccf58b, 0x3cb92b63,
    0xbe0ce380, 0xbe3d9c46, 0x3da21ea4, 0x3e900cef, 0x3d8a1ab2, 0x3ec72341, 0x3eb1b87e, 0x3e9524d5,
    0x3ed67d8b, 0x3e052f2e, 0xbe9b8960, 0x3e54611a, 0x3e88d307, 0xbef942da, 0x3e2a9320, 0xbe974ca6,
    0xbc946e89, 0x3c400107, 0xbe969b2a, 0xbeeb036d, 0xbdd9e0be, 0xbed56439, 0xbd628e51, 0xbe1e85af,
    0xbe071707, 0xbe528661, 0xbe9b05e2, 0x3cb39f88, 0xbde0e1ab, 0xbe858302, 0x3e4ef031, 0xbe768edb,
    0x3ea229e7, 0xbdc8d306, 0xbe4520f4, 0x3e0e698a, 0x3e09aff2, 0x3e779cce, 0xbe5df0be, 0x3e959f84,
    0x3dcaf9dc, 0x3cab2f6b, 0x3ded61ed, 0xbece4109, 0x3d83bd08, 0xbe139b54, 0x3eaf0b0b, 0x3e3c0ebd,
    0xbd6816fd, 0x3edb4773, 0x3ea95cee, 0x3f0044ba, 0xbde6e4fb, 0xbecac612, 0x3eb8626b, 0x3eb0553c,
    0x3e5949be, 0x3ec8d565, 0xbd18d89e, 0xbc8374c4, 0x3de91dce, 0xbeb8ade0, 0xbeb73ce0, 0xbc4b0119,
    0x3ae7e911, 0x3e2f6e26, 0xbe72faa6, 0x3d7078e5, 0xbe4d3ae6, 0x3e722049, 0x3ed1f3eb, 0xbe8751c6,
    0xbe90c2f4, 0x3d458bcf, 0xbe046d5e, 0x3edd500a, 0xbef7ca5a, 0x3e26ff4b, 0x3de25037, 0x3ec052b6,
    0xbb5b0408, 0x3e708e0d, 0x3debf89c, 0xbe3239a8, 0x3f078f93, 0xbe1133f8, 0x3eb865ca, 0xb9c43a88,
    0x3c4f63ba, 0xbe7b0d46, 0x3e2ae285, 0x3e865727, 0xbcd3b2bb, 0x3e8f2f61, 0xbed30d70, 0xbe117006,
    0x3d0431b6, 0xbea4713e, 0xbf0306e4, 0xbea9615e, 0x3e6f76a4, 0xbed3050e, 0xbd9fadac, 0xbf12fa6d,
    0xbe45ec4e, 0xbf0ddc54, 0xbe5b4467, 0xbed0fc12, 0xbe7f9826, 0x3e5e2aaf, 0xbebd7c8d, 0x3dfe3dce,
    0xbd99de17, 0xbe06c281, 0x3c5677f9, 0xbc79dbf5, 0xbecf3a8a, 0x3d7ce9b8, 0x3e5d857b, 0xbe30adf2,
    0xbe969eef, 0xbd2485f1, 0x3e991c04, 0x3ea34793, 0x3e657cb1, 0xbe85ca20, 0xbead2d3a, 0x3e0dde5d,
    0xbf230c07, 0x3ec7f0bd, 0x3bcc87ce, 0x3dba59ec, 0x3d1292cb, 0x3ed1c411, 0x3d8ad525, 0x3d0440b5,
    0x3e38de51, 0xbda2a563, 0x3e528cf6, 0x3ee6955c, 0xbdc36b72, 0x3df1cbf2, 0xbe850cbb, 0x3ee5a411,
    0xbe14ea8b, 0x3e753277, 0x3ea3bed4, 0xbe1fff3b, 0xbe1784b3, 0xbc58f690, 0xbe4a7472, 0x3e4dfaaa,
    0xbe83797e, 0xbdc02e4f, 0xbea01f6f, 0xbd25eff0, 0xbeca3729, 0xbdd4afac, 0xbe7f1196, 0xbe6c0e84,
    0x3e6ee477, 0x3f2af1e0, 0xbe6552a8, 0xbe9fc8a5, 0xbe92c4c9, 0xbe5b1afa, 0xbd816be9, 0xbf0d57e7,
    0xbd84569b, 0x3e3b6709, 0x3de350b1, 0xbe110ff7, 0xbe9c20ea, 0x3f15ce3c, 0x3de0dd7c, 0xbe4505ff,
    0xbe282633, 0x3dcddbe7, 0x3eb3fd39, 0x3e4cd55c, 0x3ed25a0c, 0xbe457054, 0x3e3ea857, 0x3c6dcf87,
    0x3d5bf38d, 0xbe011044, 0xbb6f140e, 0x3d8bd4a2, 0xbdee57ed, 0x3d649717, 0xbeb30f11, 0x3e658c36,
    0xbdc200dd, 0xbde0c83a, 0xbe8d47e6, 0x3ddbe111, 0xbec7ef81, 0xbe6d75c0, 0x3ebbb0d2, 0xbe6c9e46,
    0xbea19f9c, 0xbdba0fd1, 0xbe951bed, 0x3e672575, 0x3e9e8f01, 0x3e77f5fb, 0x3e6917c1, 0x3d3f0f99,
    0x3e561226, 0x3e8ca1df, 0xbebaa98c, 0x3d5b21ae, 0x3df2888d, 0x3ea89272, 0xbe4ef60c, 0x3ed48b48,
    0xbd44117b, 0xbd7c99d1, 0xbd048441, 0x3f05a0ca, 0x3f307697, 0xbe3ee56b, 0xbea912d2, 0xbe8bae95,
    0x3a1197f2, 0x3e4984a8, 0xbe9a0bac, 0x3e937e74, 0x3c0d20cd, 0xbddd6d5f, 0xbe582278, 0x3df0ca9a,
    0x3e4f9ed0, 0xbda44dd1, 0xbe0350e5, 0x3d47fa38, 0x3cb14ced, 0x3e0cfaf7, 0xbd9a3e77, 0x3e2dfbde,
    0x3e77e429, 0x3d30a87e, 0xbdeeaf8b, 0x3cfe0df0, 0xbdc7f1e8, 0x3eaa1010, 0x3dd444e0, 0xbe91203d,
    0x3d1aa0d5, 0x3dba032b, 0x3e89ffc2, 0xbdd0d68e, 0x3ec1cab2, 0xbe17d0b4, 0xbe96736e, 0xbe8d8ba0,
    0xbe79feaf, 0xbe9a4892, 0x3e69f3b7, 0xbe13e742, 0x3d9f8098, 0xbcfbfb2b, 0x3e8490dd, 0x3cd94fbe,
    0x3d76a4e6, 0x3d4df8c6, 0xbd14c5ea, 0x3e2cba12, 0x3cef4ba2, 0xbee77ce7, 0x3ec2b0f4, 0x3e280277,
    0xbcad17d4, 0x3e67206d, 0x3c03e929, 0x3ed7c36e, 0x3ec680c5, 0x3ed86b4e, 0x3e128b42, 0x3e66e47b,
    0xbd54764c, 0xbcebfcca, 0x3bff267e, 0x3dde3281, 0xbc5262c1, 0x3e576068, 0x3e621454, 0x3e91aaf1,
    0x3d43b380, 0x3de4359a, 0xbe359342, 0xbe52a113, 0x3cf64dc7, 0xbda53553, 0x3d491ab8, 0x3e08ad03,
    0xbe3cf101, 0x3e8f04ab, 0x3e652569, 0xbec8d487, 0xbf154ec0, 0xbdb1a2b2, 0xbe9bd96d, 0x3db02ac8,
    0x3da3b2f6, 0xbe298893, 0xbe318891, 0xbc069d3c, 0xbe6b4702, 0xbdc73dfa, 0x3e91a339, 0xbdcd15df,
    0x3e050699, 0x3e0ac6dc, 0x3e0e416b, 0x3dac0b04, 0x3d12f5cd, 0xbf03953a, 0xbe194fd2, 0x3ecf6bdc,
    0x3c45eb73, 0x3dd676f2, 0xbe73ca24, 0x3f05ba10, 0x3ebe3003, 0x3e5c7017, 0x3e2a523f, 0xbdabddec,
    0xbe913971, 0xbe6c969b, 0xbc443b17, 0xbe7dcf8e, 0xbc66f3d8, 0x3d3f4b4c, 0x3e9fc3f1, 0xbe84a727,
    0xbea4e85e, 0xbca55803, 0xbe9d39a3, 0xbe9c78e8, 0xbe99686b, 0x3ed14498, 0x3ec6dd96, 0xbc2d2d7d,
    0xbd6d1ab8, 0xbeccb39b, 0x3f14eafd, 0xbe0b3850, 0x3e0713ec, 0x3e987a94, 0x3e9b63cc, 0xbe1ef0bb,
    0x3d67038c, 0xbc1cf21b, 0x3d9dc092, 0x3c203538, 0x3e9db6ad, 0xbe528376, 0x3e3c95f5, 0x3e99da01,
    0x3ecab631, 0x3e44b806, 0xbd12a7d4, 0x3d91e237, 0x3ef6223c, 0xbd35e634, 0x3d874520, 0xbe98dd78,
    0x3e0537fb, 0x3e9f1bc1, 0x3eab3242, 0x3daa0a82, 0xbd398f35, 0x3e9bf949, 0xbef960d4, 0x3c315a12,
    0xbdf5b1a2, 0xbe9fe88b, 0x3df28824, 0x3dbd38af, 0xbdc9ca91, 0x3e4b5bff, 0x3e66f723, 0xbe0dbb58,
    0x3e2a8595, 0x3e55223b, 0x3dc5677d, 0x3e9ed163, 0x3e8be2e5, 0x3df06ac4, 0x3d82df3e, 0x3b30c8ac,
    0x3e11d542, 0x3e1b4919, 0x3d91b1dc, 0xbe3797b5, 0x3e3ae5fa, 0xbe297180, 0xbceddba9, 0xbe57d256,
    0xbe90f594, 0x3d78e332, 0x3ee31b8c, 0x3eb47434, 0x3e0b6eca, 0xbd6be978, 0xbd9fa798, 0x3ed1d457,
    0xbd800437, 0x3db391e2, 0x3e19e5b3, 0xbeefe445, 0x3e0365a6, 0x3d4ce813, 0x3da3cd39, 0xbeb4f7ab,
    0x3e15d8ca, 0xbed438b3, 0x3effe6e7, 0xbdf7edad, 0x3e2d5771, 0xbe08e437, 0xbe48915b, 0x3cb3ce75,
    0xbe983f5e, 0xbe936c9a, 0x3ca0707e, 0x3e47f099, 0xbe3c9669, 0xbcf8d549, 0x3e255ce9, 0xbdff382e,
    0x3e808e58, 0x3e42fbd1, 0x3d618035, 0xbd99294f, 0xbd5499fe, 0xbe3db1c0, 0x3cfc552e, 0x3e2c25cf,
    0xbe47907f, 0x3e96fb2b, 0x3ea4a1ae, 0xbe16b1e8, 0xbea6a1dd, 0xbe0f7eea, 0xbe8a59fc, 0x3b420360,
    0xbe9b1f64, 0x3d019772, 0x3ec60c3e, 0x3e9ed5e2, 0xbe627faa, 0x3e3590dc, 0x3ebed2ce, 0x3cc997ba
};

static const uint32_t _K32[] = {
    0x3d424d39, 0xbd3641e1, 0xbc79db9d, 0xbb6600d0, 0xbd96fd49, 0xbd3b04cd, 0xbcf96e77, 0xbcfb3e21,
    0x3c312344, 0x3d711314, 0x3d03ba45, 0x3c930134, 0xbdbe4683, 0x3d38b5b7, 0xbd00867a, 0x3da8e743,
    0x3bbb496c, 0xbb3ab015, 0xbd9d20cb, 0x3d25bc5d, 0x3ca64d0b, 0xbca2f39c, 0xbcc70428, 0x3ccdb5d5,
    0xbc80fcd8, 0xbcdd811c, 0x3bc376e7, 0xbd1b82f7, 0x3c4f493b, 0xbc1de43c, 0xbc22f6a0, 0x3d5712dc,
    0x3d93b2d9, 0x3d3402b4, 0x3baddd75, 0x3d92d5ff, 0xbdff0126, 0xbb1e5c31, 0x3c42f0e2, 0x3d4ec2a2,
    0xbd9d3d94, 0xbc251937, 0xbdc69cb1, 0x3bb63ab8, 0x3a040fb5, 0xbdb9c9ad, 0x3d65aeea, 0x3cc75c28,
    0x3c062d50, 0xbc97af05, 0x3d77fa24, 0xbc81f214, 0xbc59380e, 0x3a259b5a, 0x3c638dba, 0x3d7aa4af,
    0x3cbd09c1, 0x3da7d37c, 0xbcfdf0fc, 0x3cdb0989, 0xbdfc039f, 0xbd853699, 0xbd771cbe, 0x3d8a8091,
    0xbd04dda6, 0xbd80a3a0, 0xbd255164, 0xbbbe9be2, 0xbae886c4, 0xbd90c6de, 0x3d5323db, 0xbd5c0eef,
    0xbe0e2915, 0x3da22e3d, 0x3d8308d6, 0xbcda99b3, 0xbd58bccb, 0x3d93636d, 0x3d02b3be, 0xbc8727ed,
    0xbcbe6906, 0x3d47b43d, 0xbd88d025, 0x3d912fca, 0x3d1577c9, 0xbe128bb0, 0xbbe96afc, 0xbc4c413e,
    0xbd5a084c, 0x3c3c848f, 0xba2ea894, 0xbdcfdeb2, 0x3dc6daa5, 0x3d84a435, 0x3dc59a7f, 0xbe0b8f05,
    0xbd3c87d3, 0x3dfcfa16, 0xba2c4533, 0x3d4280c9, 0xbcc157a9, 0xbc2db6c7, 0x3c6bc1cc, 0xbdd627da,
    0xbd23f186, 0x3cbcf0ec, 0x3d1fcc93, 0x3c8c0480, 0x3cb8f859, 0xbd47ea55, 0x3d6b36cc, 0x3b7e2145,
    0x3da3c5c2, 0x3c8a001d, 0xbc99b0a5, 0x3c5624c2, 0x3c58cf98, 0x3beac097, 0xbd44d0a1, 0xbc84a076,
    0x3d87ca53, 0xbd5b07ab, 0x3c5ba215, 0x3c4e495b, 0x3ddf892e, 0xbc449361, 0xbd35979b, 0xbc927605,
    0xbcde12a5, 0xbd11bc90, 0x3c9d021b, 0xbe3dad3f, 0x3df5190d, 0x3be9c26a, 0x3d6267b9, 0xbe043298,
    0x3c8a05e6, 0x3df3f10e, 0x3df2f733, 0x3bbdf15a, 0xbe4b9d87, 0x3d97d501, 0xbe028a30, 0x3c47b471,
    0xbd7b770d, 0x3d0fb133, 0x3ca0b99a, 0x3d789240, 0x3d8765c8, 0xbd2f4e3e, 0xbe1b9070, 0x3db93ffa,
    0xbde8e613, 0x3c60efd8, 0xbd867fc5, 0xbd4bfefc, 0xbd20c64d, 0x3d8f03b4, 0x3c44c665, 0xbe14ec0f,
    0xbd12ceda, 0xbd01c400, 0xbcfa1f46, 0xbd7cc930, 0xbc7ec4d5, 0xbdab27ce, 0x3d2ceeb3, 0x3c272126,
    0x3c8fabf0, 0xbd1fad65, 0xbd54c747, 0x3d3c61dc, 0xbd2eb17c, 0xbd2ede65, 0xbc9243c7, 0x3d80a282,
    0xbdfd2c78, 0xbc663deb, 0xbddae9b5, 0xbd4ba41a, 0x3c1de53d, 0xbb83266c, 0xbd0e9c9f, 0xbe1a0798,
    0x3d70d52f, 0xbc83503d, 0x3d40a825, 0xbca9af82, 0xbd1a2763, 0x3ba67808, 0x3cf6ec7a, 0xbcca1435,
    0xbd2b07d5, 0xbc475649, 0x3d610070, 0x3db77768, 0x3d16fbc9, 0x3d68a9b5, 0x3d24c61b, 0x3d300002,
    0xbdec0047, 0x3cc93b57, 0xbcb0eb74, 0xbcc41c7c, 0xbc2b6a4e, 0x3d94f22a, 0x3d550e98, 0xbe1094b0,
    0x3db29af7, 0xbd3159dc, 0x3de97bf3, 0xbdbc79f6, 0xbdafbe76, 0x3d681c1e, 0xbd3dbd00, 0xbd55bce6,
    0x3d29a8c9, 0x3bc46411, 0x3c2858da, 0x3dfb6e54, 0xbd24017e, 0xbe1d52c3, 0x3d9c4dfc, 0x3d324d91,
    0x3b5c93b0, 0x3c1b0fc8, 0x3b0756e0, 0x3d06a768, 0x3c998965, 0xbe12512b, 0xbd5b7343, 0x3bcddd47,
    0x3c931039, 0xbe0ba93f, 0xbceddff3, 0xbdfe1d7e, 0xbc07a842, 0xbd734365, 0x3ddddefc, 0xbbf890cd,
    0xbcd75c57, 0xbd0d9a52, 0xbd79438d, 0xbd1410e2, 0x3d437029, 0x3cdfaa1e, 0x3bd82821, 0xbd15d5f6,
    0x3bcca318, 0x3def7a2b, 0xbda6e7c4, 0xbd880bba, 0xbd1fb082, 0xbe1d433d, 0x3d8e4961, 0x3d1f9001,
    0x3ba138a2, 0xbdda4bcc, 0xbba9c88f, 0x3d8b09c7, 0x3df2a62f, 0xbc7c0658, 0xbc56b79b, 0xbcbca886,
    0x3b372809, 0xbd62fd7d, 0xbc2cfd33, 0x3e206f47, 0xbc19659b, 0x3d20921b, 0x3d1d405b, 0xbd99e972,
    0xbdf5e542, 0x3d13a90d, 0x3d577322, 0x3d875e42, 0xbc2ab63b, 0x3dddd6c3, 0x3e2f1cb7, 0xbd292498,
    0x3d8401d1, 0xbd7c88f5, 0xbcd2e292, 0x3c94ee73, 0xbe080c96, 0xbbd4b80a, 0xbd3385f9, 0xbd0fd4b7,
    0xbcc2f53b, 0xbdd51fd2, 0x3d3642b0, 0xb9d49627, 0x3c478f8b, 0x3d10e9ff, 0x3d55ab1f, 0x3db13b9c,
    0xbd9175d7, 0xbcfb1b91, 0xbc2a318e, 0x3d5490d4, 0xbc5a3a28, 0xbd2dcdf9, 0x3c4fac8d, 0x3cc71345,
    0xbd2b6f4b, 0xbd82dc4f, 0x3b05187f, 0xbd85014e, 0xbd809268, 0xbd7374b9, 0x3dca0cc3, 0xbd8f7efb,
    0xbce51923, 0xbc832575, 0x3d6db5fd, 0xbd98bca8, 0xbb722ba6, 0xbd3b2481, 0x3e078687, 0x3d463b1c,
    0x3dc9f3b9, 0x3dd72925, 0xbc9822ed, 0x3d12e9a8, 0xbc87e884, 0xbe00a801, 0xbd9ad509, 0x3dac8f81,
    0x3d63be40, 0x3d3dc5a1, 0xbde4d397, 0xbd67e174, 0x3cdba85f, 0x3cc41b03, 0xbd6421b8, 0xbd8cc20c,
    0x3dd70e80, 0xbd29eec6, 0xbd0cfe53, 0xbc87b37b, 0x3d91dad2, 0x3d10419b, 0x3d04130e, 0x3d4b55f7,
    0xbb83bc9d, 0xbceb3c50, 0xbc9be159, 0xbd1513ef, 0x3ce4744d, 0xbd67ae14, 0x3d7134d0, 0x3db5f317,
    0xbd48756c, 0xbbbf9f03, 0xbd93c688, 0x3db5dc04, 0x3d82b14e, 0xbd356dba, 0xbd267bbf, 0xbcc416fe,
    0xbb294c38, 0xba6ab065, 0x3d7c28f0, 0x3cb3b7ec, 0x3d89c8f7, 0x3cddf3dd, 0x3cea6515, 0x3cf3d041,
    0x3d407697, 0xbd2f7d74, 0x3d574a54, 0xbd09bfbd, 0xbc9357d7, 0x3d2fcf1b, 0xbc10e150, 0x3b98ace6,
    0x3d900465, 0x3d5ad28a, 0x3c8c91fb, 0x3d0832a8, 0x3cd3d2d3, 0x3d052610, 0xbba86ad2, 0x3d0ac5aa,
    0x3a36cf12, 0x3cb9a198, 0x3c3f5418, 0xbc5c3133, 0x3caac5a5, 0x3d8aeef2, 0xbcdf433f, 0x3c116b8c,
    0x3d77db62, 0xbd28f98e, 0x3d250ba2, 0xbcf0c3aa, 0x3d1c6a1f, 0x3c81bfdc, 0xbc93b6fd, 0xbd1d5ad6,
    0xbc8678d6, 0x3bc6d4e7, 0x3d1a9e95, 0x3cbfce53, 0x3cf68967, 0x3c6a9bf1, 0xbce2ec0a, 0x3ce6b325,
    0x3cb87b99, 0xbbfe54c2, 0x3c475ac3, 0xbd27616f, 0x3cde4875, 0x3b6343db, 0xbcbdd51b, 0x3c9456a6,
    0xbc39888e, 0xbd5ba352, 0x3c87dd1c, 0xbc8d03db, 0x3beb2cdd, 0x3c960bbf, 0x3bd2de35, 0xbcffee53,
    0xbcf263a5, 0x3d1f9583, 0xbc7c2482, 0x3bbcdf92, 0xbcd8cd2c, 0x3c9b24e2, 0xbc61e498, 0x3aa411e6,
    0x3d373a19, 0x3e04c4f2, 0x3e05be53, 0xbc2f2460, 0x3ddc6833, 0x3d879349, 0xbbf23e4b, 0x3db5004e,
    0x3e32fa34, 0xbd782a47, 0x3cd9cb78, 0x3daad4d0, 0xbde8e55e, 0xbc983501, 0xbe166d35, 0x3e1277c4,
    0x3cb766f6, 0x3cd90aa7, 0xbd3a46c7, 0x3d2802b8, 0x3cb17ed0, 0x3ded2863, 0xbbde3fae, 0x3b899001,
    0xbb2a75bc, 0x3db4aa7a, 0xbdb8501d, 0xbda92f14, 0xbde32888, 0xbd2caf46, 0xbd22157e, 0xbd14c83b,
    0x3d7b5855, 0x3d8e14cf, 0xbd31d7d7, 0x3c9401d5, 0xbd226ea1, 0x3cad8140, 0xbd924e17, 0x3d55efe5,
    0x3cc1ad31, 0xbd9e7988, 0xbc9cf9d7, 0x3da51b5b, 0x3d90724a, 0xbccdec1a, 0x3cc36a49, 0xbb5dd0d7,
    0xbdb33691, 0x3bdc8dee, 0xbd874a9b, 0xbc6e4bfe, 0xbe1ad4b1, 0x3cb3121c, 0xbe281ba5, 0xbe078fb9,
    0xbd6f64dd, 0x3db9f6f4, 0xbd2da18a, 0xbb808745, 0x3ab49e46, 0xbd1345da, 0x3e17c927, 0xbdc1431f,
    0xbd058519, 0x3cbe1b5a, 0x3db8d767, 0x3b0deff4, 0x3d6da063, 0xbd951c3a, 0x3c203376, 0x3de3e104,
    0x3d8bd5ce, 0xbd39c1db, 0xbd900fed, 0x3d8d6f9b, 0x3df7fc5a, 0xbdab9299, 0xbd4f3f38, 0xbd3e07ab,
    0xbcbdcd3e, 0xbd8c9e4e, 0x3cc6bf7b, 0xbdd95d2f, 0xbc460856, 0x3d9521af, 0x3da0f7af, 0xbb56129f,
    0xbce9b1d5, 0x3cd55768, 0xbcff28ca, 0x3db1fdfa, 0x3cadfb50, 0x3b4fe695, 0xbb94688a, 0x3d8432e6,
    0x3db78e56, 0xbd275b59, 0xbcddf1c5, 0x3e04bd9d, 0x3e22d3e6, 0x3d0d1e21, 0x3c03939b, 0x3c842bf8,
    0x3cb315ba, 0xbd18d27a, 0xbc7abe9a, 0xbcd67071, 0x3cf366d0, 0x3d0d263d, 0x3d6dc512, 0xbd724073,
    0x3d25851d, 0x3d148206, 0xbc500490, 0x3d8b322a, 0xbc5ca15d, 0xbcd3f4fe, 0xbc5b9822, 0x3d8b74d1,
    0x3c515299, 0xbdb90104, 0x3dbc7872, 0x3c7ba7f5, 0x3cee1ced, 0xbd84bb7e, 0x3d83b5fd, 0x3c948f18,
    0x3d427ebf, 0x3ca189af, 0x3d45df63, 0x3a53e242, 0x3cdf8f76, 0x3d08abef, 0xbdac3596, 0xbc8e3bd0,
    0x3d0354ae, 0x3cf9af0c, 0xbd2b96f3, 0x3d41c302, 0x3d2b74a6, 0x3cfd5d95, 0x3d0562ff, 0x3c6092a7,
    0xbe132655, 0xbdb46676, 0x3d6ed620, 0xbd441f65, 0xbd2f2384, 0xbd19a60f, 0x3c2de8db, 0xbdf18e5b,
    0xbe0cd990, 0x3cc7f030, 0xbcfebfed, 0xbad16002, 0xbc29e85c, 0x3cfc3521, 0x3dc41ca0, 0xbd110fe8,
    0xbe2eded7, 0xbded44ab, 0xbc7b4d49, 0xbcc6f8a6, 0xbdbe3c9e, 0xbcd3b266, 0xbd68fc6e, 0x3d355f6b,
    0xbe1db1d2, 0xbd0dcfed, 0x3d732448, 0xbd792e25, 0xbda8f405, 0xbd17e465, 0x3d51aeae, 0xbcfdff88,
    0x3cb8f2e3, 0x3b88f0c6, 0xbc8789da, 0x3cd26723, 0xbc92b463, 0x3d057d4f, 0xbd928ab4, 0x3d12544e,
    0x3d638e62, 0xbd652950, 0x3ce2ccbe, 0x3cd61a08, 0x3bb8cec3, 0xbe084226, 0x3d6cc421, 0x3cd94a4f,
    0x3c01fe33, 0xbd61423c, 0xbbc8b725, 0x3a74cff4, 0xbe061da7, 0xbc818698, 0x3d4e9d0f, 0xbde3d872,
    0x3d1af10a, 0xbd1356e2, 0x3d73a0d9, 0x3dbe0b23, 0xbccf3524, 0xbd87e482, 0x3ba92819, 0x3c21caf3,
    0xbcefc179, 0xbdd0a089, 0xbd7a829b, 0xbda8acb0, 0x3e271813, 0xbd6593a1, 0x3cfd5453, 0x3d3eccd6,
    0xbc52efaf, 0x3db24e56, 0xbd15f40c, 0x3e00363e, 0xbd97f6f2, 0xbe028a5e, 0xbd173444, 0x3bfca96a,
    0xbcb1c6a4, 0x3d8584f3, 0xbc8f8d2d, 0x3d80510a, 0xbddb755b, 0xbaf626ef, 0x3be2aa77, 0x3b7fd79c,
    0xbb46e716, 0xbdb39b9d, 0xbd907c13, 0x3b476c61, 0xbd776d64, 0xbdd324b1, 0x3da26fd3, 0x3b67c811,
    0xbb8a36c6, 0xbce49933, 0x3d7a2604, 0x3d4bd11e, 0x3cfb8dc0, 0xbc28b389, 0x3db54fb4, 0x3d801da9,
    0x3d2058b7, 0x3c9122a4, 0xbd2768a5, 0x3de71779, 0xbd1307c0, 0x39e9578b, 0xbb147102, 0xbd12c127,
    0x3dacab70, 0xbda0e276, 0x3cf9b9cc, 0xbdbc94b1, 0xbde730f3, 0xbbca4569, 0x3d760f8f, 0xbd42680d,
    0x3cff230f, 0xbdabf18c, 0xbc9d4acc, 0x3c22699b, 0x3adc2b98, 0xbc6916c9, 0x3d82c5fe, 0xbc1c404a,
    0x3cadf282, 0x3d87b5da, 0xbc69d602, 0x3d4efcee, 0xbc24083a, 0x3c510798, 0xbd4d2c02, 0x3d2107d9,
    0xbb32b12c, 0xbca127b1, 0xbbfdf5ad, 0xbc51d346, 0x3af7be71, 0xbd5777cf, 0xbd5def47, 0xbd173475,
    0xbdbd9637, 0x3dab05de, 0x3c758cfe, 0xbd9e3bc3, 0xbb1a1cc7, 0xbe0e01d8, 0xbdccc0fd, 0xbc14265e,
    0x3c207fe2, 0x3d8c9a94, 0xbd9a762d, 0x3c216546, 0xbe1c868d, 0x3c427ba6, 0x3d07dd4f, 0x3d1d3f21,
    0xbd3193bf, 0xbe096663, 0xbdfa0a2f, 0x3d0f1179, 0x3c882d39, 0xbe01f5b3, 0xbc898da6, 0x3d226a90,
    0xbd9b1b0d, 0xbdf61b23, 0x3ce37aa2, 0x3c5edf89, 0x3d6bdec4, 0x3d978198, 0xbdead985, 0x3d37049e,
    0x3b0e18dd, 0x3d0287a6, 0xbdc3c89a, 0x3d71d4f9, 0xbdc08a1a, 0x3d7360be, 0x3e082411, 0xbd2a234a,
    0xbdab5ac5, 0xbb2148b9, 0x3b5b7583, 0x3cbacc3f, 0xbd8593cb, 0xbda74e47, 0xbd2bad1e, 0xbc6f8626,
    0xbc44ce18, 0xbe4d5adf, 0xbd6d06cc, 0xbcfc8ccc, 0x3de6c8f6, 0x3bbc0957, 0xbe067928, 0x3cfc5c81,
    0xbc336e7e, 0x3d3a2273, 0xbdd8d63a, 0xbe3ecfcc, 0x3dd9c38a, 0xbd004137, 0x3e1b0a81, 0x3bc2c559,
    0x3dacef9b, 0x3ce0535b, 0x3bdcbd67, 0x3d1a2fbf, 0xbe004d92, 0x3d81f337, 0xbd470aaf, 0x3d46c475,
    0x3cf6a938, 0x3d4b57d4, 0xbc201955, 0x3cefc02f, 0x3c4b7b95, 0x3b83d8bb, 0x3bec6bc0, 0xbb95bb47,
    0x3dec4887, 0x3b881e24, 0x3cd7b0a4, 0x3d0c6e8a, 0xbcfae598, 0x3d285b86, 0xbda00c60, 0x3df17983,
    0x3d0ce01d, 0x3dcf7c3a, 0x3d4d181a, 0x3d9b9869, 0xbce798e1, 0xbbb98a30, 0xbc050cb4, 0xbd3cb85e,
    0xbcb37633, 0xbbc15c0b, 0x3c340178, 0xbd7f9716, 0xbdf62365, 0xbc0f3b79, 0xbbd9b1a1, 0xbd1e210a,
    0x3dbb726c, 0x3da5cf66, 0x3d1a660e, 0x3d9fa723, 0xbc0fab27, 0xbd0b336f, 0x3cde6a91, 0x3dbfaf9e,
    0x3d127a77, 0x3d21d905, 0xbd8287de, 0xbd387af5, 0x3d74ad45, 0x3b7b3a19, 0xbcae1847, 0xbcf62888,
    0xbd8d278b, 0x3cba38dd, 0xbda5d639, 0xbda46840, 0xbd03b0ef, 0x3cf10fbc, 0xbd3db36d, 0xbdd7462f,
    0x3ce91984, 0x3de3b1fc, 0xbd077c79, 0x3cc41906, 0xbdd9e4d7, 0xbdbd8c6e, 0x3c267a52, 0x3d39f017,
    0xbd86a247, 0xbd7935c6, 0xbda2e26e, 0x3d321d2a, 0x3d94451b, 0xbd9a1e7e, 0x3d8b4f0b, 0xbcc84ded,
    0x3e1ab9ea, 0xbd725de1, 0xbd923822, 0x3e0ccd16, 0xbce5d129, 0xbcadf4c0, 0xbcbb58ae, 0xbc7710e3,
    0x3c126157, 0xbce979f2, 0x3e294120, 0xbdb5080b, 0x3d855049, 0x3ded6df4, 0x3ccb07d9, 0x3cdf9c54,
    0xbc411c06, 0x3d5d95a5, 0xbc81d580, 0xbcb65e97, 0xbdf8bd0e, 0xbafa3ea9, 0xbe4aa28b, 0xbd0fc2c9,
    0x3daa9392, 0xbda7cd8e, 0xbdb1d969, 0x3da83992, 0xbd2409fb, 0x3d45ab4e, 0xbdf4685e, 0x3bc03097,
    0x3c11555b, 0x3d286ed1, 0x3bdf08c7, 0x3e2794ce, 0xbc095ae4, 0x3e1c2ebd, 0x3d6af86e, 0xbd7f6c1a,
    0x3d2265d9, 0xbab0f453, 0xbd84075f, 0xbcabaf2a, 0xbdd3abab, 0xbda8a31e, 0xbd8578b8, 0xbca1cc79,
    0xbc9e2e8e, 0x3d48a8d9, 0x3d1da232, 0x3da8f96c, 0xbcc901d3, 0xbdc88b83, 0xbd62a729, 0xbd8b002d,
    0xbcb90d51, 0x3d87d998, 0x3d8de3a1, 0x3e0e8001, 0xbca4c34a, 0x3dff7141, 0xbd3cb9f7, 0xbd163998,
    0xba7d8251, 0x3c3e40f2, 0x3d32f590, 0xbdee7d11, 0xbd81b832, 0xbd5942e0, 0x3ca74a83, 0xbd5731e6,
    0x3d040fd2, 0x3de3817d, 0xbcd9b375, 0x3d84a675, 0x3d422834, 0x3d4734b7, 0x3cd467a3, 0x3c1f1500,
    0x3d8d135c, 0x3d568dc9, 0x3c82af42, 0xbbaa7bce, 0x3cf2a402, 0x3d35cebb, 0x3be14a69, 0x3e2e8ffa,
    0x3d8bbd40, 0x3dc3e82f, 0x3c3acb88, 0x3d5938e8, 0x3dff3620, 0x3d471d77, 0xbd14edc7, 0xbd536657,
    0x3dc5c538, 0x3c8f6660, 0xbccedd19, 0x3d764189, 0x3da6ce16, 0xbd14d399, 0xbcda7be6, 0xbd82db86,
    0x3d8ae0dc, 0x3ca80d46, 0x3d9cf001, 0xbcda853c, 0xbd8cfb9b, 0xbc861216, 0x3d920ee4, 0x3dcd1c96,
    0xbd93337d, 0xbd8ffa53, 0xbda66b97, 0x3d056072, 0x3c5a453e, 0xbd91cb4f, 0xbcd6fbd1, 0x3d50263a,
    0x3d6856ee, 0xbdda8f39, 0x3dbe2347, 0x3ba178e7, 0x3e07aa5e, 0xbcab1865, 0x3ca5020e, 0x3df7aae5,
    0x3dad0ee0, 0xbcb4a47f, 0x3ca999bb, 0x3bfdf6af, 0xbe0ac7e3, 0x3cb71e28, 0x3bad9134, 0x3e2dd1ca,
    0xbd2ed8ab, 0x3cc53317, 0xbe19da1b, 0x3d7eaf0e, 0xbc007eca, 0xbda7e569, 0xbc42800a, 0x3db41c84,
    0x3cb5ae34, 0x3cd8a8d9, 0xbdcdb1e8, 0xbdac008b, 0xbe119894, 0xbce0d4f9, 0xbdda6fb6, 0xbd6fc2ca,
    0x3d157add, 0xbc0a4eaa, 0xbdacf49b, 0x3d947403, 0x3ca64527, 0xbdf8cbdf, 0x3d8e88fe, 0x3d8d7cc9,
    0x3cf3f6ff, 0x3d0e795b, 0xbd812646, 0xbc3400cb, 0x3c112aa3, 0xbbc6c780, 0x3d11b230, 0xbca6774a,
    0xbd411b4f, 0x3da9826e, 0xbdf90a81, 0xbd6261dc, 0xbdd62721, 0x3d47b31c, 0xbe11e38e, 0xbd4c1849,
    0x3d207b5f, 0x3d54b7b2, 0xbc4fa68d, 0x3e1949e1, 0xbcd14430, 0xb847fa07, 0x3cb86670, 0xbb3b8fa4,
    0xbd132b46, 0xbd6d9bf8, 0xbd9417b6, 0xbd50e8e1, 0xbda80260, 0xbd6177ee, 0x3d68fc51, 0xbdf7e294,
    0xbbc9a79c, 0xbcaf1536, 0xbd8c4177, 0xbda94417, 0xbdfd834e, 0xbde65997, 0xbde713c8, 0xbd9fb9e4,
    0xbde284c3, 0xbd93e03f, 0x3c9d2296, 0xbdde278d, 0x3dc6f10c, 0xbba9a8a1, 0x3cee73d8, 0xbdbf7e5b,
    0xbbb4e4dc, 0x3c73860c, 0x3d8bdb01, 0xbc8829f5, 0xbddba881, 0xbb1dcb48, 0xbda3c224, 0xbd8e2965,
    0x3d260a50, 0x3ddca067, 0xbd2dc42d, 0x3dd474ff, 0x3da5eb3e, 0x3d5037ab, 0x3bd31ee0, 0x3b8f7d34,
    0x3e05584d, 0xbcd56a2c, 0x3bcaece2, 0x3a5ccd0f, 0xbdd755cc, 0xbd55d9a1, 0xbd021faa, 0x3dabbc37,
    0x3d9a1847, 0x3d18af79, 0xbd50b98b, 0x3c1c6ebf, 0x3cadad21, 0xbd61124b, 0xbb132ae8, 0xbcf0a825,
    0x3b9b50dd, 0xbc50b1cc, 0xbdef097a, 0x3da7c22e, 0xbd7ffde9, 0xbc887375, 0xbc9b1071, 0xbc859071,
    0xbd89d8f0, 0x3cabed94, 0xbce67597, 0x3b9998b9, 0xbd3c732b, 0x3aa92036, 0x3d3df48c, 0x3d5002d3,
    0x3bf0b99b, 0xbd543805, 0xbdbcd9d1, 0xbd85fed1, 0x3ca80320, 0x3bdfffa7, 0xbd3f41d8, 0x3cfd175b,
    0xbb246c19, 0xbcd1343b, 0xbd19169a, 0x3cc118bd, 0xbd96af29, 0xbdece107, 0x3c51defa, 0xbdda6e6b,
    0xbdf741ce, 0x3d0090cf, 0x3b961725, 0x3ae0ecb6, 0xbc974d47, 0x3d834522, 0x3e07e94a, 0xbc58ee13,
    0x3d37d8c7, 0xbdb4fc34, 0x3d8b1d19, 0x3daa87b1, 0xbd11c8a8, 0xbcdc3dd6, 0x3d1fd7cb, 0xba5a8fe2,
    0x3ba9706a, 0xbe1013dc, 0xbcba71bc, 0x3c3b28ad, 0xbd54e09e, 0xbe073da5, 0xbd14bdc1, 0xbde6868c,
    0xbd851fb2, 0x3d6b5738, 0xbdae9edb, 0xbd2da21c, 0x3ce53ca0, 0xbdbfdfd9, 0x3e1ec67d, 0xbce223fb,
    0xbd2f85eb, 0xbdd04fe0, 0x3c9d6306, 0xba3de7a9, 0xbd7afd62, 0xbbca1931, 0xbdac577b, 0x3d17b695,
    0xbca78edc, 0xbd4b334a, 0x3dc13b5a, 0x3db99ec8, 0xbcfdd466, 0x3d7506bd, 0x3d0ae97b, 0xbc48477c,
    0xbddde43b, 0xbcbd8c8f, 0x3d962190, 0x3d61708e, 0xbd18afc6, 0x3e1596d1, 0xbb288df7, 0xbd2e98a2,
    0x3cb0829f, 0xbd6bf8dc, 0xbd082505, 0xbe0d91a4, 0xbda259c0, 0xbe0474ca, 0x3cd0ae15, 0xbb65eabf,
    0x3d1b4293, 0xbb9f08af, 0xbcd31099, 0x3ddef46d, 0x3c68eeb0, 0xbdea4481, 0x3dbe7592, 0x3d81fc7a,
    0x3cf4f58d, 0xbde71f6c, 0x3dfb4db2, 0x3c6e1945, 0x3dc5270d, 0x3e0c8bc6, 0xbe12043e, 0xbd9f3d5c,
    0xbcbd0eeb, 0x3d21a260, 0x3c3e5f51, 0xbdc5fa41, 0x3cd194dd, 0x3b851305, 0xbd1e0d32, 0xbd48fead,
    0xbd1ca94b, 0xbe7b98f3, 0x3da55f02, 0x3c71c6c7, 0xbdbcf63d, 0x3df5dc54, 0x3e68f910, 0xbe6fc2ae,
    0xbdaffcd8, 0x3ea5fde7, 0x3e79f1a2, 0x3d0e83cc, 0xbcf8625c, 0xbdd7e4ab, 0x3df37b3b, 0xbd0db563,
    0xbe00eab5, 0x3e78bea9, 0xbe4b58ce, 0xbe30c321, 0xbe57cf61, 0xbe077481, 0xbe846702, 0xbe985f64,
    0x3d853e75, 0x3cc6b951, 0xbd4d4706, 0x3893ff1e, 0x3d2856cf, 0xbde6e89a, 0x3bd6e118, 0xbd9adfff,
    0x3d140c1e, 0xbdc6260d, 0x3dac7663, 0x3ded423f, 0x3cba73a7, 0xbdb7c169, 0x3e14ae22, 0x3d8f9a7a,
    0xbe2c0e3b, 0xbe109b36, 0xbe0bb047, 0xbd9d41db, 0x3e108baa, 0xbd7fe150, 0x3d1b2151, 0xbc103c3b,
    0xbda7436b, 0x3e6b5dd6, 0xbd5611a5, 0xbc3e0ea6, 0xbd8db917, 0xbde477d0, 0xbe812ef1, 0x3d1201ad,
    0x3d823973, 0xbce85c76, 0xbe629a4a, 0x3cd4c830, 0xbe268539, 0x3d14096b, 0xbacb2121, 0xbce433be,
    0x3d98e244, 0xbd43fa4d, 0xb981d589, 0x3e015b43, 0x3de60846, 0x3c2626d8, 0x3e5c60de, 0x3da21380,
    0xbcdbbfde, 0x3da12811, 0xbce8fccd, 0x3da27549, 0x3d0b5dcb, 0xbc8edcdf, 0xbd17e377, 0xbc642860,
    0x3d06f408, 0x3d8c4161, 0xbda014de, 0x3c8dcce3, 0xbca15904, 0x3d0bfb52, 0x3b945ef7, 0x3c7810b7,
    0x3cd5b71e, 0xbd3731b0, 0xbd1ddc62, 0x3d4cf8bf, 0x3c4348d0, 0x3d0fbb59, 0xba942974, 0x3d07447b,
    0x3b6c1d0c, 0x3d746055, 0x3cd02c1a, 0x3d901606, 0x3cc6497e, 0xbdc61848, 0xbb80eb7b, 0xbc1d69d1,
    0x3b94e566, 0x3dd8acd9, 0x3cbf037b, 0x3d075284, 0xbdb71420, 0xbd22698e, 0x3d5ae4e5, 0x3dba4341,
    0x3b7997cd, 0xbd8b82f6, 0xbd30096d, 0xbd220a0d, 0x3954f429, 0xbdca30fa, 0xbb856478, 0xbdc639c5,
    0xbb398ac4, 0x3c9b8dd2, 0x3d8548b8, 0x3d844755, 0x3c539fc3, 0xbc9acedb, 0x3d8e2221, 0xbd100e22,
    0xbd0e4967, 0x3d556f39, 0x3bed1c8e, 0xbca4164b, 0xbd12ad03, 0xbdd651a0, 0x3cf9bcf1, 0x3d8a7bde,
    0x3c55f1df, 0xbc948acd, 0xbd9f19bf, 0xbd806006, 0x3cf2cc53, 0xbd9811f6, 0xbd2f9af5, 0xbdad7e35,
    0xbcdc668d, 0x3e0a1d7d, 0xbc625c3d, 0xbcd84251, 0x3c34f056, 0xbd0e23eb, 0xbd90dc7c, 0x3c3b060c,
    0x3dee8824, 0x3b04f712, 0xbdcb22fd, 0xbd4342e1, 0x3caf52df, 0x3d353511, 0xbdb6c6cc, 0xbd27cdad,
    0xbd5d82a0, 0xbd654735, 0x3d046f1e, 0x3dc6a6d2, 0x3ddb290d, 0x3d850521, 0x3db02c87, 0xbd38416d,
    0xbcfb8b2f, 0x3b978153, 0xbd1e2468, 0x3c3af803, 0xbc1d6382, 0xbd266065, 0x39e06782, 0x3beeb383,
    0x3d002fd3, 0x3cf53a1d, 0xbda2dae7, 0x3c72eb44, 0xbca395dd, 0x3b6b1fb8, 0xbd0500bf, 0xbd3a88b5,
    0xbc0a62f7, 0xbd0c5b93, 0x3c968314, 0xbd36f614, 0x3c91cc0a, 0xbd11ff49, 0x3de0c566, 0x3cec9524,
    0xbcd022f8, 0x3d51475d, 0x3d3a4273, 0xbca1bb94, 0x3da8f654, 0xbdce9a2d, 0xbda60cb3, 0x3b88b87a,
    0x3d8654d9, 0x3d769a05, 0xbe1c3ea0, 0xbd0d3fd7, 0xbca696a2, 0xbdb9078d, 0x3d9e7ee7, 0xbc2730e9,
    0xbe022895, 0xbe052ba5, 0xbd9b01ed, 0x3de9cf9c, 0x3e35eabe, 0x3cc5dd8d, 0x3dc56b2d, 0x3de9d2fb,
    0xbd4601b8, 0x3d7f1ef0, 0x3c853701, 0xbd74a174, 0x3c96b703, 0x3d0b58a3, 0x3d1f1076, 0xbd0aba0a,
    0x3d725f27, 0x3d601bb8, 0x3ce886ab, 0x3d2b846a, 0x3c0eb29b, 0xbd29d043, 0xbc1db727, 0x3ccfae91,
    0x3ce6ad1e, 0x3e1492f3, 0x3d56af8f, 0x3dbdbf9e, 0x3d88c3b0, 0x3d8c2ad0, 0x3c22904d, 0xbc87efe6,
    0x3d35aa72, 0xbc7425fd, 0xbc339a1b, 0x3c39b5d5, 0xbcaeb635, 0xbd23298f, 0xbca705a5, 0xbd135186,
    0x3b3cf6dc, 0x3d34c17a, 0x3cc3f86e, 0xbb5a1042, 0xbca826fc, 0x3d7137ac, 0x3cb847e5, 0x3b27419d,
    0xbc82fcc3, 0x3db2d55a, 0x3b34cc22, 0x3d48ad7d, 0x3d064384, 0x3ce66412, 0xbcdb8903, 0x3c9dafa4,
    0x3da4e471, 0x3b5f75b9, 0xbd4843cf, 0x3d9e2d23, 0x3a469c21, 0xbd4c3329, 0x3c87c61f, 0xbc980a2f,
    0xbc29ca15, 0xbbcf1c00, 0x3c99e5f0, 0xbb52b1a8, 0xbcd3ec97, 0x3d19360a, 0x3b0e0dba, 0x3daa84af,
    0xbc78e3e0, 0x3c002f2c, 0xbd994584, 0xbc88a1eb, 0x3bead1de, 0xbd0258e4, 0xbd28f1c5, 0x3d4aad16,
    0x3d6a6aa4, 0xbc804ee9, 0xbd16c92b, 0xbd12edc7, 0xbcbe097b, 0x3d04adf6, 0x3d9df13c, 0xb9968553,
    0x3dfa6781, 0x3d5e01c0, 0x3df612b7, 0xbe381b8b, 0x3d285244, 0x3ba30905, 0xbdc61f13, 0x3e08ab84,
    0x3d96878c, 0x3d1ad628, 0x3d75cdd6, 0x3d006ef5, 0x3e656eb9, 0x3d90c425, 0xbbb12db2, 0x3dec115d,
    0xbde33846, 0x3e07a433, 0xbcba96eb, 0x3e39d9a7, 0x3c941771, 0x3d239d4d, 0xbd9a42f8, 0xbd8e6917,
    0xbda39403, 0x3ba5a811, 0xbd9c98c1, 0x3e510d85, 0xbd36b937, 0x3e236ecf, 0x3e0c3559, 0xbda93845,
    0xbe1b3112, 0xbd9f01c7, 0xbd0ee430, 0xbcaacf39, 0xbe3e2295, 0xbdc276ac, 0x3db1ec86, 0xbdcbdd2b,
    0x3d3ec585, 0xbd2d8453, 0x3e313c23, 0xbddb5f33, 0x3cb50060, 0xbe44c4e9, 0x3d7984d3, 0xbe5b1dec,
    0x3deb98e0, 0x3dacafac, 0xbd13b344, 0xbddd5254, 0xbe0ec4bc, 0xbe7deb39, 0x3b4079ac, 0x3db9c288,
    0x3e34c10d, 0x3d8f8ba7, 0xbab9c54b, 0x3e026d1e, 0x3e3e5c0f, 0x3da0a134, 0xbd838157, 0x3de277c9,
    0xbd31bd1f, 0x3d535ad7, 0xbd975d04, 0x3d4364c1, 0xbcea7bab, 0xbcbffe07, 0xbd5478ee, 0xbcd7a25c,
    0xbd1f221d, 0x3d6c06a7, 0xbc872e42, 0xbc843255, 0xbd749021, 0x3dad1dd9, 0x3e0a2f88, 0x3c860c97,
    0xbd0cff69, 0xbd593abd, 0x3c093959, 0x3d077827, 0xbb7b026a, 0x3ba07ad8, 0xbcc98c3d, 0x3ddb11e0,
    0x3d0bf212, 0x3bd7d54b, 0xbb02132f, 0x3d25d717, 0xbd755de0, 0xbdbf192b, 0xbc239968, 0x3b4f0d0e,
    0x3c1586a5, 0x3d957eed, 0xbcc430ec, 0x3d1367cf, 0xbd9f96b8, 0x3ddec916, 0x3d110b32, 0x3cd5c5c0,
    0xbb13169b, 0xbd32bb96, 0xbcaafbf6, 0xbd447639, 0xbd2481af, 0xbdbdafaa, 0x3c80e013, 0xbcbc400b,
    0xbb82f2df, 0x3ce7c8f5, 0x3c517585, 0x3d22131f, 0x3a7fb7f0, 0xbd97388c, 0x3c9115b0, 0xbd1423f7,
    0xbd0c6534, 0x3d2fcb35, 0xbc813a8a, 0x3d086e62, 0xbd91a83c, 0xbd299aba, 0x3e025622, 0x3d5bb3fa,
    0x3ccf48a4, 0xbd30f7d2, 0xbd71fc58, 0xbc82330a, 0xbd0bf4cc, 0xbd607f5d, 0x3d162a6c, 0x3b21eeb9,
    0x3d3e2aac, 0xbb933cd3, 0x3e349bca, 0x3e453205, 0x3dc7299d, 0xbc2414db, 0x3e005369, 0x3e000a07,
    0x3cebd432, 0x3ca6bd4b, 0x3db81570, 0x3db33b83, 0xbce056f8, 0x3cdd15d8, 0xbc56b784, 0xbd9a48f1,
    0x3d601170, 0x3ca521ec, 0xbc02eb85, 0xbd93ac29, 0xbcfda8ca, 0x3d09695c, 0x3cf785a3, 0x3d6fc319,
    0x3c500016, 0x3d8b8c0e, 0xbd0aa200, 0x3d38dd02, 0x3d56dd8e, 0x3d34d47e, 0x3c5de7bb, 0xbcb819f3,
    0x3deb8eb0, 0xbbff6f65, 0xbc2f17ee, 0x3d917b83, 0xbd29677a, 0x3cb3fdbb, 0xbdf8ace4, 0xbc0a7717,
    0xbc728f18, 0xbd891dd1, 0x3cd61b31, 0x3b954d0e, 0x3cdd4524, 0xbcfe248e, 0x3d6c8408, 0xbd47650e,
    0x3c97430f, 0xbe9b4aeb, 0xbcc8e453, 0xbd9aa62b, 0x3e35c88d, 0x3d9318ba, 0xbc3601bc, 0x3cdf0d35,
    0xbc91ac86, 0xbdcb0afa, 0xbe0ceee2, 0xbe0780ee, 0x3d87d0bb, 0xbd156145, 0x3d060dce, 0xbe4b2238,
    0x3d14ca97, 0xbca35962, 0x3df66fc1, 0x3c03de89, 0xbd820196, 0x3d765928, 0xbda4eae8, 0x3debe69a
};

static const uint32_t _K34[] = {
    0x3e7b9328, 0x3e5fd9aa, 0xbf2c0b1c, 0x3fa40e72, 0x3de8b073, 0xbf9ad0cf, 0xbed01f0b, 0xbf621fa8,
    0x3fe2972a, 0x3ee37d78, 0x3f0cbdf2, 0x3e1852b0, 0x3e62a384, 0xbe85c38a, 0x3bb7e580, 0x3f59c9b6,
    0x3f388141, 0x3f89c2c5, 0x3f0a6df8, 0xbf841ee2, 0xbe1f29f5, 0xbc98fc00, 0x3f70c96c, 0xbf935362
};

static const uint32_t _K39[] = {
    0xbe1a1c9f, 0x3dd79510, 0xbddd6ddb, 0xbdeaaa83, 0xbe8ad67f, 0xbd1d3a58, 0xbdcf4cb6, 0x3e62b274,
    0x3ee67e3e, 0xbe93e2e6, 0x3d86461e, 0xbe3a94b7, 0x3dedcd03, 0xbe79a6aa, 0x3e81138e, 0xbece7693,
    0xbeac31df, 0xbda52b14, 0xbea936ce, 0xbe81c867, 0xbdd52495, 0xbe445dad, 0x3e31138a, 0xbee91191,
    0x3e7dad29, 0x3e1657cf, 0x3da176c5, 0x3e5d24e4, 0x3d8636fe, 0x3cc0e36b, 0xbe0d1ed2, 0x3e68967b,
    0x3e88b481, 0xbdca791f, 0xbc527075, 0x3da9aa8f, 0x3c3d8488, 0x3de958fb, 0xbef7028b, 0xbd6c1db1,
    0xbdc4488c, 0xbee4912d, 0x3d5c931e, 0xbe84a866, 0x3d9d9998, 0xbdfdf436, 0xbc44f323, 0x3e9b314b,
    0x3ea7fbac, 0x3e81c9f2, 0xbd65bd09, 0x3e4b7e8b, 0x3dff6399, 0x3d88f2db, 0x3e85462b, 0x3da65601,
    0xbe858080, 0x3e145113, 0x3e77b07c, 0x3e5e5edc, 0x3df7b7e0, 0x3e6d831c, 0xbed41a7f, 0xbdb3c22f,
    0xbe245127, 0xbd047fc3, 0x3ec1f027, 0x3c1e1703, 0xbdca7e9b, 0x3eae4209, 0x3e91560b, 0x3dc66a86,
    0x3e67050f, 0xbe5889f0, 0x3d52ea66, 0x3e5c9125, 0x3e99275e, 0x3de6e932, 0xbdf60dee, 0xbde67386,
    0x3e876b89, 0x3da0a236, 0xbe0ddc6e, 0xbd1fa297, 0x397b0797, 0x3d7ad8cb, 0xbda19572, 0xbe98d639,
    0x3ea08e7a, 0xbdb78bb3, 0x3e1aee4a, 0xbe13f588, 0x3d3d553e, 0x3e533127, 0xbd64e6a9, 0x3de185db,
    0x3d24235d, 0x3c133e5a, 0xbe9ad08a, 0xbba4720e, 0xbe0fd241, 0x3e2083eb, 0x3d90010d, 0xbe89990c,
    0xbbb3812e, 0xbe7a75c7, 0x3d0df86f, 0x3d59ba9e, 0xbe500360, 0xbb8e43c1, 0x3e181da3, 0xbe47f28e,
    0x3baaa2df, 0x3e53658c, 0xbd239957, 0xbe0f7785, 0xbd8d90e6, 0x3dc4a10d, 0xbcf18884, 0x3ca4cc70,
    0xbcfd74e1, 0xbc0b25d0, 0xbee164b9, 0xbcb0f54d, 0xbe57e23f, 0x3d9b065b, 0xbe8db629, 0x3eb2ced3,
    0xbd0a7434, 0xbe7d236e, 0x3ec0fd20, 0xbe34ed69, 0x3d95ad47, 0x3e2e50f4, 0xbe62bfe7, 0x3deceec1,
    0xbf238b97, 0x3d66f84e, 0x3d816de9, 0x3e9ff4fb, 0xbcc50a24, 0x3bd5e8ac, 0x3e6cf33d, 0xbcb922f2,
    0xbe334142, 0xbd5721c7, 0xbe4e68e7, 0xbd32e02a, 0x3e45f3b9, 0xbd8d1581, 0x3cae78a9, 0xbd56baf6,
    0xbe23cf67, 0xbde372ea, 0x3e14f34f, 0xbe0a839a, 0xbe17d615, 0xbe67ac61, 0xbdedea3b, 0x3d847ab2,
    0xbd8d3344, 0x3eccb690, 0x3bd175f6, 0x3e31a2ca, 0xbc87e62d, 0xbded07eb, 0x3e322390, 0xbceda540,
    0x3daea5d5, 0x3da3ebc2, 0xbdd505d1, 0xbeae7ab6, 0xbe9a4aa6, 0x3d9ca3bb, 0xbd7d3497, 0x3daaf9aa,
    0xbdf30944, 0x3e173e72, 0xbbe321ec, 0x3bb23d97, 0x3e67daf8, 0x3dcd0a3c, 0x3d98bc28, 0xbdc9cb94,
    0x3e1c63f0, 0xbe6d83b3, 0xbd9dc410, 0x3e289458, 0x3db9977b, 0xbed417af, 0x3e64968b, 0xbd8c94f0,
    0x3e6d96df, 0x3e13657d, 0x3d1a059d, 0xbdd4d932, 0x3da2d39d, 0x3d85af5f, 0x3ddfb6b0, 0xbec93a10,
    0xbd7b3d6c, 0x3ee679eb, 0x3e524339, 0x3e9f3d90, 0x3e9eb15a, 0x3e33bd06, 0x3e42b3e0, 0xbe57ad78,
    0x3eb06504, 0x3e45de0c, 0x3e102351, 0x3e7e0e2d, 0xbd47f6e4, 0x3e375c90, 0x3edba9f8, 0xbdbba196,
    0xbc9fd235, 0x3ecb0649, 0xbe40520f, 0xbe83d90b, 0xbd9cb763, 0x3e98845b, 0x3e0aa9bc, 0x3eb19fea,
    0xbec8a253, 0x3d34b378, 0x3df1d15c, 0xbdb2433d, 0x3e156fbb, 0xbde3917b, 0x3ef5ef3f, 0x3e6a2f11,
    0xbe8a3af9, 0x3d121d96, 0xbe6d6f1b, 0x3ec6f08f, 0x3eb3a0a9, 0x3dbeb685, 0xbca2116a, 0xbdb4bf42,
    0x3dd22155, 0xbc30e534, 0xbc8e13e6, 0x3ef26f51, 0x3e31a82d, 0x3eaf37d3, 0x3ca9dbd6, 0x3e19f816,
    0x3f37694b, 0xbda31471, 0x3d7c7eba, 0xbdc43c36, 0x3d4a6660, 0x3e9944ff, 0xbe082e44, 0x3eb15829,
    0x3d917495, 0xbd554aa6, 0x3e75047d, 0x3da12de4, 0x3db61841, 0xbe6aec4c, 0x3eedaf7c, 0xbeb01f39,
    0x3f0faa66, 0x3d06baa8, 0x3d40f82f, 0x3e79ac90, 0x3c9b214c, 0xbdb80f42, 0xbc33e8ab, 0xbc97f282,
    0x3e258040, 0x3ec5e3b4, 0xbe9685bc, 0x3ec23cb1, 0x3ee9c190, 0x3d285ea1, 0x3e64e89b, 0x3d084203,
    0x3efeb6dc, 0xbf395de6, 0x3ee8e9ff, 0xbeb4f0a4, 0xbe11b92d, 0x3c83229e, 0xbd052842, 0xbdc330b6,
    0x3c57f33c, 0xbe9371e6, 0xbd4ec2d6, 0x3d8fac99, 0x3e69a3f0, 0x3ea3292d, 0x3e032b72, 0xbe02970e,
    0xbd357501, 0x3ea6bad6, 0x3e515e6a, 0xbde8d56d, 0xbf02cf91, 0xbe4c3b5d, 0xbf0c9bf1, 0xbe56f83b,
    0x3d38c488, 0xbcfe1d98, 0x3e8baf03, 0x3ddd9d0e, 0xbe82c5cf, 0xbe08416e, 0x3dcc70c0, 0x3e829360,
    0xbda55797, 0x3e5188c6, 0x3e30d754, 0xbeb06922, 0xbec45c24, 0x3d69c483, 0x3ed2f949, 0xbdcea4a8,
    0xbeb87f7c, 0xbc90694d, 0xbd7b7f2e, 0x3e27ecea, 0x3e1e2911, 0xbd7f6e1f, 0x3f087231, 0x3cfe8974,
    0x3ebf2a5e, 0x3ec88dca, 0x3d0e1de7, 0x3dc8dd17, 0x3e480764, 0xbb8456b2, 0x3d70ecc1, 0xbe1e3d3c,
    0xbe3bb892, 0xbebfc361, 0x3e19f55a, 0x3c4f88e2, 0x3e37115b, 0xbda4b14a, 0x3a12e614, 0xbe05cf06,
    0x3eb09524, 0x3dbf091b, 0xbe6bf601, 0x3e52c0cc, 0xbc99f353, 0xbd527f18, 0x3dc70313, 0x3e940368,
    0x3e2ce250, 0x3e217077, 0xbd12a010, 0x3dd567d2, 0x3c950395, 0x3f1dcfab, 0x3daee743, 0xbee29c0b,
    0x3eecc5f9, 0xbd529d82, 0xbe37fc31, 0x3df7b7f4, 0xbbeee3b5, 0x3e04ee5b, 0x3e59ff46, 0x3e20ca53,
    0x3e326957, 0xbd7460b9, 0xbb9f7bc1, 0x3e21ad8b, 0xbe306ae1, 0x3d91dded, 0x3dc59874, 0x3e5dfb27,
    0x3d4a5eb5, 0x3f30bb13, 0x3c21b2f8, 0x3dde2f09, 0xbe0ed2b0, 0xbe43212d, 0xbc9dfb26, 0xbe1f3bad,
    0xbea22428, 0x3e2ede2a, 0xbd49ef6f, 0x3e1fec44, 0xbd40c8b3, 0x3e911ea0, 0xbd30fc5e, 0xbe49284d,
    0x3ec299a8, 0xbe3ebfc5, 0x3c6e21ed, 0xbd985046, 0x3d202ad4, 0x3cb8bb09, 0xbd85d916, 0xbda2621e,
    0x3df91a3b, 0x3da9d036, 0x3d5b6592, 0x3e28c6fe, 0x3ef485ef, 0x3ded045f, 0x3cf0c055, 0x3e6b8f5a,
    0xbecf021a, 0xbeecd1b2, 0xbc47e565, 0xbe8cecb2, 0x3dbbc5aa, 0x3db6be3b, 0xbe12b9ce, 0xbe3caff4,
    0xbe6a291e, 0x3d97cc4a, 0xbeb59414, 0xbea25c4a, 0xbe31fae4, 0x3c626fd0, 0xbd32b255, 0xbe468bff,
    0x3e54dde8, 0xbf03d4cd, 0xbe840d85, 0x3dc2ad93, 0x3e6a500c, 0xbe86f369, 0xbf0b9059, 0xbe8e0f3a,
    0xbe0a5da2, 0xbd8972b9, 0xbe4b2bcf, 0x3e6efc8c, 0x3dbb24fb, 0xbdacb042, 0x3c3d4149, 0x3e93b2ad,
    0x3e593910, 0xbe7ff5a1, 0x3e3c0b96, 0x3d853b2c, 0x3bfc2504, 0xbe3567ee, 0xbe87f600, 0xbe12ddca,
    0x3e3d58c1, 0xbd4b18fd, 0xbddf4cb2, 0x3b874fbb, 0xbdbbee93, 0x3e08b50a, 0x3e42b390, 0xbc699633,
    0xbdc4e123, 0x3e0b3320, 0xbe03bc6d, 0xbdaa8489, 0xbd82b192, 0x3e5389e2, 0x3ed06d5b, 0x3d2a9a3a,
    0x3e4d06d9, 0xbe8ff559, 0x3e44555c, 0x3d4bb935, 0xbcddadf2, 0xbda0de81, 0xbdf95aa8, 0x3e8ae1cb,
    0x3e1066d8, 0x3eb2b756, 0xbe5ee0c0, 0x3cad320d, 0xbdb7fe9f, 0x3dd44b05, 0x3e138080, 0xbd8e49d0,
    0xbde8cde3, 0xbe888a5a, 0x3e3045f8, 0xbe1c164e, 0x3cca39a9, 0x3e419e0e, 0x3ea8a938, 0xbe027c32,
    0x3e9ecefa, 0xbd95265a, 0x3c2b377c, 0x3d35fcb8, 0xbe4dbbfa, 0xbde1c251, 0xbde616b3, 0xbc915018,
    0xbd50765d, 0xbde887b6, 0xbcf0d726, 0x3ebec33e, 0xbd5464d0, 0x3e87726f, 0xbe83b720, 0xbb2234d5,
    0xbead5480, 0x3ea94473, 0xbec28c21, 0x3ed32b48, 0x3dbab11b, 0x3e5bacbc, 0x3eb3fb3a, 0x3ccc46f1,
    0xbe58aafa, 0x3c66bb97, 0x3d46e591, 0x3d4cbab1, 0x3dbcff37, 0x3e7aeb7f, 0x3e230385, 0x3e972237,
    0xbeab1009, 0xbf2e13bc, 0xbc0bebd5, 0x3eafcf6c, 0x3d2848c4, 0xbe519039, 0x3e2167f7, 0xbc803710,
    0xbd1057a5, 0x3e9c57b1, 0xbd3bbeaa, 0xbe982fd9, 0xbea8ab9b, 0xbcc54a72, 0xbe4eb1f3, 0x3e4e812d,
    0xbed532ff, 0x3d2f0666, 0xbb91359a, 0xbe915c79, 0x3e82578e, 0xbc7a18cd, 0xbd0a8a85, 0xbe916650,
    0xbe041297, 0xbefce6cd, 0x3d4a51c2, 0xbd81af18, 0x3da3e45a, 0x3ea05707, 0xbdd11871, 0xbe2187ae,
    0xbe64d6ca, 0xbd88398b, 0xbda02232, 0x3f5f6019, 0x3e7075f0, 0xbdcd5ea4, 0x3e09169f, 0xbda1cd76,
    0x3e926f75, 0x3eb9c3a7, 0x3e72d3e1, 0xbe5c85fc, 0x3e35a329, 0xbe2e963a, 0x3e1991c8, 0x3e2b8113,
    0x3eeba71c, 0xbc5f5029, 0x3e3b91bc, 0xbebe1667, 0xbd7a9b28, 0x3dd200c2, 0xbe4c979b, 0xbe548466,
    0x3e9e0ea7, 0x3d9dbc88, 0x3e3f1efc, 0xbda55a32, 0x3ec1fe40, 0x3ecd91bb, 0xbe2ec948, 0xbe0f5909,
    0x3e077675, 0x3eafe4d8, 0xbecf897c, 0x3e936ab1, 0x3e2d975c, 0x3e851469, 0xbe13ec56, 0x3ebda45e,
    0xbd641c60, 0xbd28eaec, 0x3f08e958, 0x3d24c9e9, 0x3e831abe, 0xbdb5f1b5, 0x3e2b99ef, 0x3e94cb40,
    0x3c943509, 0xbd5a435f, 0xbd504a66, 0xbea13bc6, 0xbec7e930, 0xbe17afc8, 0xbe78618f, 0x3dc56aed,
    0xbeb74550, 0xbe257263, 0xbddc26f4, 0x3d2708e3, 0x3b32a376, 0xbd44b449, 0x3dc5aa3a, 0xbe9ff0e3,
    0xbe117fdd, 0x3eb3b460, 0xbebc9a0d, 0x3ce5db77, 0xbd83a245, 0xbdf484b2, 0xbe44aa59, 0x3cbdc3d7,
    0xbe4b7219, 0xbd48ab58, 0xbd1f7432, 0x3e63c2a5, 0x3bc43333, 0xbde37f29, 0x3dc1108f, 0x3a9fba75,
    0x3e4e43da, 0xbd186846, 0x3ed05824, 0xbe1c1b55, 0x3ddc7a04, 0xbea70737, 0x3d3f19d6, 0x3ece73ba,
    0x3db6bed2, 0xbe9076c2, 0xbe2f0f15, 0x3ea37335, 0x3d573643, 0xbebec506, 0x3e4a07cf, 0xbe702420,
    0x3e26872b, 0x3e4cd443, 0xbe0d61ac, 0xbe95607b, 0x3ddf1804, 0x3e6fc8b3, 0xbe8b67f0, 0xbd2a1721,
    0x3e2de87e, 0x3e9a9eea, 0xbe8c8e05, 0xbe58e576, 0xbeb182cc, 0xbdb66be4, 0x3c15377d, 0xbdeade27,
    0xbeb59b70, 0x3e0611fd, 0x3e476ca5, 0xbdd71283, 0x3e16fc87, 0x3cf6fa63, 0x3e76551c, 0xbda0828c,
    0xbc7105a4, 0x3deb5a69, 0x3e34c94a, 0xbe9eae86, 0xbe1d5b97, 0x3e716544, 0xbeaa6583, 0xbe183db8,
    0x3e6ab1a0, 0xbce73afa, 0xbe4136f9, 0x3d9ea10d, 0xbdf73f76, 0x3e27a567, 0x3df69a5b, 0xbd47b68c,
    0xbd3c3be9, 0x3dc0ceb9, 0x3e9949ef, 0xbd8478ef, 0x3e4e6263, 0x3e21d82d, 0x3e85f13d, 0xbde28a95,
    0x3c41a1f9, 0x3dfa87ce, 0xbb4ff6c0, 0xbe646076, 0x3af86c82, 0x3e055fd3, 0xbd2f863e, 0x3e75f0d9,
    0x3ea2d598, 0x3c5184ff, 0x3e714be1, 0xbdb631a1, 0xbd6534b3, 0x3e48a288, 0xbd5a419c, 0x3e427ad9,
    0xbed3148f, 0xbd31c634, 0x3e2d7cd6, 0x3d5a1a67, 0x3d0708ee, 0xbcbc6a7b, 0x3ea1ac03, 0x3c194965,
    0x3c15f626, 0xbe928507, 0x3ed346e0, 0x3d8249c1, 0xbd952236, 0xbe9dda0f, 0xbe45edf4, 0x3e4c052b,
    0xbe9ba1d5, 0xbe0be19e, 0x3e44b3fa, 0x3dfaaa51, 0x3e09d3e8, 0xbdde8b2b, 0x3e4689fd, 0xbc85c1e9,
    0xbe629045, 0x3e120dda, 0xbe1421b9, 0x3bbdab6b, 0xbe540a2c, 0x3da4c90b, 0xbe499b2c, 0xbdd18e20,
    0x3d916042, 0xbcb3ce43, 0x3e519e3c, 0x3e39e05b, 0x3ad91ef5, 0x3dca9e67, 0x3e974310, 0x3d2bd155,
    0x3eae01b5, 0x3d9fb274, 0x3e014b49, 0x3d3800f4, 0xbe1c73aa, 0xbdc9a6e0, 0x3e0a9ccc, 0x3de49f57,
    0xbd6d45a1, 0x3e81b93a, 0xbc780133, 0xbe383d59, 0x3d6e9e7a, 0xbdcd1b88, 0x3da090de, 0x3e455eb3,
    0x3e8f4242, 0x3f093543, 0x3ecc4ebc, 0xbdc48d60, 0x3e3add77, 0x3e9b8510, 0x3e083b67, 0x3e2db637,
    0xbecce7d8, 0x3e02a7d9, 0x3ef2389f, 0x3ef15574, 0x3e84de44, 0xbbde2fe8, 0x3dd3e788, 0xbe29dfaa,
    0xbdf50ac5, 0x3e818d13, 0x3dd28746, 0xbe26178c, 0x3d288a86, 0x3d8db1de, 0x3d53762b, 0x3eea6243,
    0xbcea7736, 0xbe1dca42, 0x3c52f90f, 0x3e434559, 0x3efe3320, 0xbd84ab24, 0x3dbdf154, 0xbd041356,
    0x3e2f1292, 0x3eb7c692, 0xbcc20c22, 0xbe20580c, 0xbeaae309, 0xbda68706, 0xbe98689b, 0x3e589e29,
    0x3e756212, 0xbd865e3f, 0x3e1e3a8b, 0xbcfcb6a1, 0xbdb3532a, 0xbe9d1429, 0x3e6e18e4, 0x3ef5a8f4,
    0x3da81bc7, 0x3e880370, 0xbe8c57a3, 0x3d537d58, 0xbe482d82, 0xbe6cb9cd, 0x3bdedc9f, 0xbe0868ee,
    0xbf0b5102, 0xbebb1590, 0xbcffb740, 0x3e134b9f, 0x3eb12a14, 0x3e89fa1a, 0x3ebeeae7, 0xbe3d7a9d,
    0xbea2f6c3, 0x3e4f5e82, 0xbe84333e, 0xbd33a25c, 0xbea04c45, 0x3ef12169, 0xbe5582ef, 0xbe44e42d,
    0x3df32d8c, 0xbe128fa7, 0x3d006ab0, 0x3d59a012, 0xbeb31256, 0xbf1eb929, 0xbd35b166, 0xbd2095a1,
    0xbd79cdfa, 0xbeab55c2, 0x3e6c1578, 0xbe0a2d37, 0x3e538820, 0xbc1c6b3b, 0x3e0426ab, 0x3d2a2950,
    0x3de18387, 0x3d486bfb, 0xbe1feb9e, 0xbe14bd4f, 0xbe7f8f11, 0xbec347f5, 0x3ded1b7b, 0xbe860a8c,
    0x3eeadc93, 0xbd26b48f, 0x3d9906e3, 0xbe4792d0, 0xbdf7da42, 0x3eb2e550, 0xbf1df272, 0xbd1b57f3,
    0x3e5a5f99, 0xbcf4caa1, 0xbe469d16, 0x3d4428c9, 0x3e9bf6ee, 0x3e880af0, 0xbe667785, 0xbec3cf1c,
    0x3eb0673a, 0x3ede0e82, 0x3f14542f, 0xbd78138e, 0x3ddbdca4, 0x3e5657b2, 0x3efd4572, 0x3d7fec74,
    0xbca5f56b, 0x3ea22f35, 0x3ef1d13b, 0xbee80602, 0xbe15bcbb, 0xbd3907a4, 0xbe8fabc9, 0xbdccd386,
    0xbec653e6, 0x3d6356d9, 0xbdad4aa8, 0x3e080214, 0xbdac93c5, 0xbcc0765a, 0x3dee803e, 0xbe63dd35,
    0xbe10c7ca, 0x3d0505a4, 0x3cbe90b0, 0x3d54a959, 0xbdc1bc48, 0x3dea0512, 0xbe26585c, 0x3eabe797,
    0x3efd8b2d, 0xbe935b1d, 0x3e057f61, 0xbeb0f0c8, 0x3dc4536b, 0x3d9c8d4e, 0x3d4b1390, 0x3dd72296,
    0x3ed521e7, 0x3c9b3221, 0x3e32f777, 0x3e8d4b3b, 0xbd481f8f, 0xbeb84091, 0xbe374b34, 0x3f26334f,
    0xbf035286, 0x3e4ca21d, 0x3c92b558, 0x3f01041e, 0xbe889e29, 0xbee86184, 0x3f0771ad, 0xbe85cd07,
    0x3edf0d1d, 0xbd8233aa, 0xbdb4964e, 0x3d8e9334, 0x3d36e649, 0x3ce0a86f, 0x3e3d57ec, 0x3d08b9ed,
    0xbddb0691, 0xbd6c4532, 0x3c89593d, 0xbe2b7c55, 0x3ca378cd, 0xbc65fe5f, 0xbcf46ac4, 0xbe934ae1,
    0xbe0a90cd, 0x3d430441, 0xbdc33809, 0x3d81528a, 0x3ca993f8, 0xbdf82afc, 0x3e78f887, 0xbdf84cea,
    0xbd763930, 0xbca85dd8, 0x3ddb83f5, 0x3e459b76, 0x3d10aa58, 0x3e322af9, 0x3da076b6, 0xbe7ac618,
    0x3e922d4b, 0x3e23d0a3, 0x3e7f2e2a, 0x3d45e073, 0xbd8194b6, 0xbe28cf91, 0x3d276a30, 0x3d6b3962,
    0x3e45103e, 0x3eaa92a0, 0xbdb5049a, 0xbea0d724, 0x3e5009da, 0x3d425e92, 0x3d8487a2, 0x3c1d3253,
    0x3dccc375, 0xbd6f1a43, 0x3e84130a, 0xbd9daf09, 0xbd4b5b0c, 0xbcf275cf, 0xbd29437a, 0x3ddc060b,
    0xbe8f9c2d, 0xbe61425c, 0xbe135f35, 0x3c1e1e03, 0xbdc04018, 0x3f01b255, 0xbe362981, 0xbed9139b,
    0xbe3b94d4, 0xbd35f973, 0x3df3b22a, 0x3e2b1a5c, 0xbe0302e0, 0x3dd7eac9, 0x3da17d43, 0x3e04bcd5,
    0xbeb59857, 0x3e7faf9d, 0xbde54a75, 0x3f38077b, 0xbe1acfd3, 0xbe81ca67, 0xbda4b544, 0x3ec20743,
    0x3d1d7874, 0x3e53923d, 0x3e053ea1, 0x3e3a7845, 0x3edbf340, 0x3da8ff19, 0xbec3bc9d, 0x3ec03374,
    0x3dd7cb4c, 0xbed0fee5, 0x3e4b970e, 0xbd9c7d91, 0x3c6cf168, 0x3e97a506, 0xbd21ed3b, 0x3e1efe25,
    0x3d739048, 0x3c911dcb, 0xbe19fd5a, 0x3e79a221, 0xbe17d567, 0xbe04bded, 0xbe100bd5, 0x3d8bb893,
    0xbeb75b1f, 0xbe7b7676, 0x3e1fdd6c, 0xbe0ab4b0, 0x3e24a62f, 0x3e0fa1d3, 0x3dcbb25b, 0xbedb8d16,
    0xbe392ea6, 0xbe9048b5, 0xbeb6f9ed, 0xbe78a41a, 0xbebd3df4, 0x3d9c760b, 0xbf23e6a5, 0xbe192e67,
    0xbd9c14b2, 0xbe782475, 0x3e3fc4d7, 0xbd1c1fdf, 0x3ea59820, 0xbe9117cd, 0xbe20bf27, 0x3e30f91c,
    0xbe0c3206, 0xbe650f59, 0x3c6f9a8c, 0xbea3cfe3, 0xbda010dc, 0xbdba30a1, 0x3e1f03c4, 0x3dcb8fd2,
    0x3e41d452, 0x3dae569a, 0xbd5c1bea, 0xbeb7ba34, 0xbe264fdb, 0xbd84ca42, 0xbed2fca2, 0xbda931c5,
    0x3dd3a86b, 0x3e0a5ae9, 0xbd081ec5, 0x3e04f015, 0xbe22d7c3, 0x3cdb5a1a, 0x3d511841, 0xbe97bf28,
    0xbce94898, 0x3dcb645e, 0xbeb90ba4, 0x3e792407, 0xbd040e5c, 0xbd0dc9f3, 0xbd9865fb, 0xbdd5958d,
    0x3d78e034, 0x3f30ac08, 0xbe144792, 0xbe9c5dc9, 0xbe47f2f7, 0xbe211733, 0x3da3f91d, 0x3dc92890,
    0xbeb4df13, 0x3d25884e, 0xbd6c7c20, 0xbee92329, 0x3e179ae1, 0xbddcd65c, 0x3e0a5eb7, 0xbe5b95cb,
    0xbedcbaf6, 0xbe28b2de, 0xbe23e267, 0xbe4bd360, 0x3e2d090a, 0xbea5578c, 0xbe7a1d6e, 0x3eab6882,
    0x3e0c8aa4, 0x3de76733, 0xbeeaad12, 0xbe95b289, 0x3bf4d140, 0xbe8bda2c, 0xbe9afd5d, 0x3d195ffb,
    0x3c3a3f04, 0xbe5aaf7a, 0xbcd24a5e, 0xbe606dfb, 0x3e0609ca, 0x3d808aeb, 0xbe2176b2, 0xbe7dc292,
    0x3e4dcc5a, 0xbd87db03, 0xbe9efced, 0xbde84a0f, 0xbeb7e280, 0xbe24a082, 0x3e6e96a0, 0x3ec4ec60,
    0x3d8d8328, 0xbe410318, 0xbd38edc1, 0x3eb6beb0, 0x3dac5a5e, 0xbd71ca54, 0xbe059e9b, 0x3cf966b0,
    0xbe59ceff, 0xbe6f89be, 0x3ec1a64a, 0x3e4ec5fb, 0xbd038186, 0xbe51a45a, 0xbe48882b, 0xbd4ce171,
    0x3e137564, 0x3ec5fa75, 0xbc7e0398, 0x3dbbb4ac, 0xbef60d33, 0xbe9f59cf, 0xbe7badd5, 0x3ded3a34,
    0x3bb77b5e, 0xbec4a510, 0x3e7a4210, 0x3d4be2b2, 0xbdb584b0, 0x3e96c63b, 0xbe02e047, 0x3eebd8b7,
    0xbd336f09, 0x3e66b92a, 0xbe6a40de, 0x3da0c212, 0xbe906cf0, 0xbdb33ae5, 0x3eb2aa8a, 0xbec33edb,
    0xbe7153ba, 0xbc0b85a6, 0x3dc68420, 0xbdb60a16, 0xbdd30259, 0xbe538925, 0x3f1fc2d5, 0x3d9cd856,
    0x3d8c250e, 0x3e095f83, 0xbe4e1d75, 0xbe2e6a41, 0x3dec9d03, 0xbeb4b631, 0xbdb4fef2, 0xbd799152,
    0x3dfe8c68, 0xbe862361, 0xbb76b85f, 0xbeb29669, 0x3ad38fa6, 0xbddd44be, 0xbdc5bbd5, 0x3d8cd16c,
    0x3e229489, 0xbd093353, 0xbf4390f4, 0xbe36c190, 0x3ecc9dec, 0x3e90f114, 0x3e8c843d, 0x3df91ec0,
    0xbcfac044, 0x3e2422d7, 0x3e3ce2d7, 0x3da242c1, 0x3e40450d, 0x3d54dc9e, 0x3cbac45d, 0xbe74caff,
    0xbd82569a, 0xbe5673a9, 0xbef49cd9, 0x3e8f03f9, 0x3d932653, 0x3dc5b957, 0xbe97c1c1, 0x3ead0807,
    0x3f0fed7f, 0xbe06ee79, 0x3e36dab0, 0xbe5e35f4, 0x3de45ec5, 0xbe607050, 0xbdd0159f, 0xbdb6e85f,
    0x3eb280d4, 0xbd8d7a99, 0xbc9a3cf3, 0xbda62e11, 0xbe306db0, 0xbe1bd449, 0xbdde719e, 0xbebbfd54,
    0xbc9d3280, 0xbd358a1f, 0xbe6551ed, 0x3e14794d, 0x3e534286, 0x3e762c47, 0x3ecd48c5, 0x3e31f267,
    0x3e0dffff, 0x3debd091, 0xbd2f717b, 0x3eb02dae, 0xbdd64398, 0xbdfe057d, 0xbec0394e, 0xbe2316ab,
    0x3e58af70, 0xbc0dbd54, 0xbd9c4d46, 0xbe65abc4, 0x3d4d14a1, 0xbd7805cf, 0x3d4dcfed, 0x3e7ca64d,
    0xbeb526fd, 0x3af5bdee, 0xbc0286e8, 0x3e9c88c4, 0xbe243914, 0x3d97bd66, 0x3d227096, 0xbdae1ba4,
    0xbe5757bd, 0xbe483d54, 0x3e1e4648, 0xbe3017f4, 0xbde7cbe6, 0x3e6fbe9f, 0xbe9b15de, 0xbe9bfcf5,
    0xbe22a9b1, 0x3e41b750, 0xbd3e634d, 0xbdbf8b6e, 0xbd95ef8f, 0x3ef93de1, 0xbdc9e87c, 0x3e3dbf9f,
    0xbd8404fd, 0xbe141211, 0xbe071322, 0xbe23ce7e, 0xbe8a3f8e, 0xbe11c556, 0xbe6cd86f, 0x3df8a6b0,
    0x3e951cae, 0xbed1d6b8, 0x3eb2bad4, 0xbe22a8ed, 0xbe690fbf, 0xbe0014b8, 0xbe027878, 0xbeaf9b7a,
    0xbe71784f, 0xbe19980b, 0xbecbe09e, 0x3d9c7e7b, 0xbeeca791, 0xbc11aea2, 0x3d28a80e, 0xbe9cf2c0,
    0xbd059547, 0x3e09a3b3, 0x3c4ef285, 0x3e6409d1, 0xbdaee7fc, 0x3ea75d3c, 0xbdc8fb66, 0x3eddb028,
    0xbbf1c681, 0x3d16f491, 0x3d865a76, 0xbe35f6b4, 0xbe661be3, 0xbdf5257c, 0xbeb61977, 0x3d918df1,
    0x3e06cc4d, 0xbe4454c3, 0xbe5f8e2e, 0xbd60dfee, 0xbe0a1629, 0xbeffe68e, 0x3e00724a, 0x3e28f82e,
    0xbde033ee, 0xbebaf67a, 0xbe10bf22, 0xbdbe064b, 0x3d52af5c, 0x3e66c215, 0xbca4c964, 0x3e85e2ab,
    0xbe8405f3, 0xbd81d23d, 0xbea71df7, 0x3e1f1c96, 0xbd037ec8, 0x3ebef53e, 0xbedd1e6e, 0xbea645ac,
    0x3dcc42a6, 0x3e73facd, 0x3dd74637, 0x3b5a7a42, 0xbd42d4cd, 0x3eb2a9bb, 0x3debbc83, 0xbd38b778,
    0x3d5c77a7, 0xbd8ecaf4, 0x3ed2e685, 0xbec9594d, 0x3da1e7fe, 0x3cd6c5bc, 0x3e505807, 0x3d3469c6,
    0xbf06feb0, 0xbe82d768, 0xbdd38cd7, 0x3e83ebd2, 0x3e2cd7b2, 0xbcffde0a, 0x3dec0114, 0xbec0ec28,
    0xbd63c9bb, 0xbe230ebe, 0xbe581e14, 0xbe8e10c4, 0x3ea551f3, 0x3ea08749, 0xbe05e26d, 0x3df09833,
    0x3eabb695, 0xbe7cdc90, 0x3d990243, 0x3ea9fdf1, 0xbd3b08cd, 0xbdfb1f23, 0xbdc4b8d4, 0x3d395d84,
    0x3eb5ee61, 0xbd7ef3c1, 0xbe0957e8, 0x3d47b675, 0xbe2c7bc0, 0x3d8ed0fe, 0x3e2f842f, 0xbc137091,
    0x3dad5a51, 0x3ee75e88, 0x3e46a985, 0x3dc1c7b6, 0x3d7cc6a1, 0x3e0f57fd, 0xbd2a99bc, 0xbde28268,
    0x3e9195f1, 0x3de4e36a, 0x3d1bbc59, 0x3c691d21, 0x3e4acd96, 0xbd41000b, 0xbdf84ab5, 0xbd7bbd5e,
    0xbe499ea9, 0x3e2cf693, 0x3e931801, 0x3e73f9f9, 0x3dc9e860, 0x3c84e95d, 0xbe242899, 0x3cc50efa,
    0xbd356011, 0xbdbe1d56, 0x3d0c2f8f, 0x3bc80a33, 0xbd332c3e, 0xbb402303, 0x3da5e4a5, 0x3e4f49c8,
    0x3ebf2f80, 0xbb302d64, 0xbe80fb9e, 0x3ecd8cd0, 0x3da945b7, 0x3cdb2926, 0x3ce0191d, 0xbe5c6c74,
    0x3ee7f0cc, 0x3f27f8e6, 0xbf0ab5dc, 0x3e8b39fd, 0xbe18122c, 0x3d98266a, 0xbdb304c7, 0x3efb077d,
    0x3d857c45, 0x3e353fcd, 0x3ecc1863, 0x3e425400, 0xbc4e587d, 0xbed3d125, 0x3ef040d7, 0xbe67615a,
    0xbea44c35, 0x3dbbdb3e, 0x3e2cfa4a, 0x3dfc2178, 0xbe2d6131, 0xbd12a7d8, 0x3d9fbc1d, 0x3e3c9747,
    0xbe800cc3, 0xbdbd83e2, 0xbe521fb3, 0xbe73b003, 0xbdb56d25, 0x3e13a501, 0xbbd44a8c, 0xbe0e3473,
    0xbe7c28f7, 0xbed2c112, 0xbe97d63c, 0xbd334584, 0x3e28096a, 0xbe156c46, 0xbeb8e8b4, 0x3ddaba85,
    0xbd9d542c, 0x3e241741, 0xbe491777, 0x3d060e9c, 0x3e2c71e9, 0x3dd01972, 0x3e8ede54, 0x3e8f5fec,
    0x3e2f3e60, 0x3e398130, 0x3e5ac331, 0x3cea2ec5, 0x3da2bb37, 0xbca7ca98, 0x3e8979ec, 0xbeb2b14d,
    0x3e851dca, 0x3d2d53d5, 0x3be65b52, 0x3d3ced44, 0x3e9c219d, 0x3d8a5f9f, 0xbd179ecb, 0xbbfdecb6,
    0x3c3e316a, 0xbdfe25db, 0x3e59737f, 0xbd99a581, 0xbe2fbab3, 0xbe98de50, 0x3df6ef26, 0xbd985ea3,
    0xbe3e8f30, 0xbde8c904, 0x3e94207f, 0x3c2c0250, 0x3d23b471, 0xbea8ca3f, 0x3e4b4392, 0xbe4fabe9,
    0xbeadc236, 0xbcf4d7b6, 0xbea6df03, 0xbe6a10f6, 0xbe8cd746, 0x3ea696be, 0xbe88f7da, 0xbd9df861,
    0xbcbb8951, 0xbe0e1723, 0x3e2bf2a1, 0x3e89c049, 0x3e9ab1f9, 0x3e36ebdb, 0x3eec181e, 0x3e105c18,
    0x3ecce843, 0x3ea92933, 0xbda81fe7, 0x3d7f31e8, 0xbe2d4380, 0xbe936008, 0xbe270073, 0x3e0cf5a0,
    0x3ed86867, 0x3ec532af, 0x3e505b1d, 0xbe1a5329, 0x3e70ef07, 0x3cbb45e8, 0x3b39daf7, 0xbc57d7da,
    0xbda18315, 0xbd227bce, 0x3d4f2308, 0x3e4d9999, 0xbe174b19, 0x3eb4c6a8, 0xbe395d9b, 0xbd207053,
    0xbe2eb223, 0x3e1ecce9, 0xbdcec52c, 0xbecbb45d, 0xbc24a4b1, 0x3eade926, 0x3edfdc9b, 0xbebb3966,
    0x3db21a03, 0xbda54a3f, 0x3e5f8b13, 0xbe6f688b, 0x3e78d4e5, 0x3e34d4c7, 0xbe0675af, 0x3d42583d,
    0xbb5fffed, 0x3e2c542c, 0x3f1482ef, 0xbd8c3054, 0x3d7ca975, 0xbd113579, 0xbdf21ab0, 0x3e06587b,
    0xbe7be4f6, 0x3ea48176, 0xbdb87f28, 0x3e8a6bcd, 0x3e121795, 0x3ec59e77, 0x3e945fb4, 0xbe1e6a8d,
    0xbdbab054, 0x3e0ee529, 0x3cedb97a, 0xbee60278, 0x3e5517dd, 0x3eeaee5a, 0xbe9c998c, 0x3e3a52e5,
    0xbc864534, 0x3d98d66d, 0x3ee5ce3a, 0xbe2209e9, 0xbd223a7e, 0x3d54fa98, 0xbe9e6d84, 0x3c530ab7,
    0xbdee5552, 0xbdc5de94, 0xbe9278bf, 0x3e00da70, 0x3e9dc5de, 0xbd78db5f, 0x3e03b22e, 0x3e44f559,
    0x3d76fe74, 0x3efd583c, 0xbde98759, 0xbeb63957, 0x3e956a67, 0x3dd38f43, 0xbe986bcf, 0x3e5b6646,
    0xbcd1f43e, 0x3edf4c5b, 0x3e5acef3, 0xbe57735e, 0x3e6507e0, 0x3cacbd48, 0xbe25f493, 0xbd5ec014,
    0xbea235fe, 0x3e1c9266, 0x3d8abfee, 0x3ea1f898, 0x3e342da0, 0xbd8266a0, 0x3ee368f3, 0xbe44d6e7,
    0x3dc9f347, 0x3d3c367f, 0xbe77857b, 0xbe88764d, 0xbc3d5c24, 0xbe5e4e2a, 0x3977935e, 0x3e29ad77,
    0x3ea43c07, 0xbcb39c4c, 0x3e6bd1d2, 0x3e9194cd, 0x3e9edd57, 0x3b18ac18, 0xbebed4e0, 0xbe0e826e,
    0x3e898a6c, 0x3ebfc429, 0xbec243ba, 0xbd0b7190, 0xbe6e8446, 0x3db3276b, 0xbe140b06, 0x3e549faa,
    0xbe8b7e38, 0xbeaca96e, 0x3e849cbd, 0x3e57d12d, 0x3decacbf, 0xbe6c0702, 0x3d79fcfc, 0x3e09152e,
    0x3e054162, 0xbd11ccad, 0xbe4854ca, 0x3e509739, 0xbdb222b6, 0x3d3a4ab9, 0x3e0bb073, 0x3d93695a,
    0x3d649437, 0x3cbe8f67, 0xbebbee02, 0xbccb4068, 0xbe8678a1, 0x3e871c11, 0x3e43238b, 0x3e571f78,
    0xbeed208a, 0xbcd1436c, 0xbd7d56ee, 0xbcd0ed36, 0x3e34898a, 0xbe7be78a, 0x3dfdf196, 0x3e0c2815,
    0xbe6b8fce, 0x3e2ce23c, 0xbdfb4601, 0xbe8a44a2, 0xbd30e377, 0xbd20ed6c, 0xbf243ad0, 0x3e0f7521,
    0xbdde46c9, 0x3de84361, 0xbe1d46a1, 0xbed2daa0, 0xbe01feb7, 0x3eb5d003, 0xbe6667a7, 0xbe9df6f9,
    0xbe53f63c, 0x3e426191, 0xbdfd6d44, 0x3d841c8f, 0x3df98126, 0xbe7c30d4, 0xbcc86958, 0xbcb8c458,
    0xbd2548ec, 0x3d61d044, 0x3ec62b67, 0xbe52a73d, 0xbe4aff7d, 0x3cf4cdab, 0x3ef37d87, 0x3d34db7e,
    0xbe9d064c, 0xbe37b80a, 0xba29e42b, 0x3e7375f6, 0x3e922204, 0x3ecb8129, 0x3e8598a9, 0x3d31c230,
    0xbdf10367, 0x3e4a74a3, 0xbe6e62fc, 0xbe36ebb4, 0x3e18a4f3, 0x3e84ba1d, 0xbf035014, 0x3debb997,
    0xbde2c11a, 0xbdcbeb7e, 0x3e525eb4, 0x3e2de293, 0xbcaf6865, 0xbd27c1f3, 0x3e5722a0, 0x3db1951a,
    0x3e2a9b85, 0xbb389f28, 0xbb4da922, 0x3db4316e, 0x3bd8446a, 0xbe221e42, 0xbe027171, 0x3d798292,
    0x3d819748, 0x3e3f7651, 0xbd736de4, 0xbda7ddd2, 0x3c6bf3de, 0x3e973f84, 0xbe24cd4f, 0x3db1e09a,
    0xbebe1066, 0x3dd21813, 0x3e62b79e, 0xbe032324, 0x3e02f467, 0xbda9eeac, 0x3ed616c8, 0x3d638c81,
    0xbd8def53, 0xbdf57ea4, 0x3f1f0cde, 0x3c68df66, 0xbdf7d736, 0xbebf0cde, 0x3ec186c0, 0xbe234eb0,
    0x3e811871, 0xbc23a49d, 0xbee11e32, 0xbd113dd7, 0x3d2b6f78, 0xbe29a8ae, 0xbc67a131, 0x3dd73bbd,
    0xbe4bbacf, 0x3ecb7d85, 0xbeb2c437, 0x3dae5fec, 0xbdcbc855, 0xbe3afb89, 0xbe4984dd, 0xbe6c4dba,
    0xbc4d6abd, 0xbe706f3a, 0x3e978994, 0xbeedb66e, 0xbdd81948, 0xbe44b521, 0x3e16febe, 0x3dfa3075,
    0xbddded8a, 0x3e0cd18a, 0xbf030774, 0x3ddd7310, 0xbe2b1674, 0xbf0019c9, 0x3e5635eb, 0x3c693b70,
    0x3e69a948, 0x3e24e7ee, 0x3d02444d, 0xbdda56ac, 0x3d657b5a, 0xbe3649af, 0x3cd3998f, 0xbdf1742c,
    0xbe688a0e, 0xbcf34761, 0x3d54031c, 0x3d1aedc1, 0x3e8e706b, 0xbd2957dc, 0x3dafa514, 0x3e2f13b4,
    0xbd9ac507, 0xbdc59022, 0x3db8b2ed, 0x3d7b1c9e, 0xbe9f4ab2, 0xbd0d9d15, 0x3e372385, 0x3be0fba9,
    0x3eee1586, 0xbdd0e766, 0x3e7610ff, 0x3d53f13c, 0x3db4600f, 0xbe9d64fc, 0x3e5f384f, 0xbf0bca23,
    0xbeb7136f, 0x3e41edd9, 0xbf2875b9, 0x3e49e2ae, 0x3e42b306, 0x3e7333c4, 0xbdd9d55a, 0x3e0800d5,
    0x3f19a2a5, 0xbe306350, 0x3e177e86, 0xbd870a4e, 0x3de4b98b, 0x3e8c1399, 0xbd941051, 0xbe1c1db1,
    0xbd8f2e7f, 0xbcb7248d, 0x3bffa052, 0xbdea349b, 0xbc76532d, 0xbebfaa31, 0xbeac00f4, 0xbe134f57,
    0xbe06b195, 0xbe0e554b, 0xbea119a6, 0xbda22229, 0x3e45b407, 0xbd0fb8f3, 0x3e08fd15, 0x3a553fb6,
    0xbe87ef35, 0xbe009c9f, 0xbb55887f, 0xbd4aef77, 0xbe1ebe52, 0x3d24f918, 0xbe51c1ab, 0xbc801e69,
    0x3d23ea5c, 0x3c3e58b4, 0xbd8e4b07, 0x3eed4705, 0x3e663281, 0xbe188fb9, 0x3d4b6ebf, 0xbdbbde29,
    0x3e960e93, 0x3d69db4e, 0x3e867937, 0x3e161de2, 0xbe206d7e, 0xbda567a3, 0xbd566b8a, 0x3ce683e3,
    0x3dc680f0, 0xbe89410b, 0xbdca8a6d, 0xbdde8781, 0xbbf3cd60, 0xbeb7ea7f, 0xbe5b76d5, 0x3d420ec8,
    0x3e0ba8dc, 0x3eb90de7, 0x3eae8ace, 0x3cf61ade, 0x3caa78f8, 0x3df48693, 0xbce2dd56, 0x3e32b762,
    0xbf09199b, 0x3dc0400c, 0x3f00f543, 0x3def353a, 0x3cd358aa, 0x3ebd6086, 0x3def3d63, 0xbea1aa01,
    0x3e47e812, 0x3eeec56b, 0xbd146a3a, 0xbe005f4a, 0xbe0b4cb2, 0x3de40354, 0xbdf6fc4a, 0x3f1eaa1b,
    0x3e8b4698, 0xbe390aee, 0x3e513180, 0x3f3f6c73, 0x3eafb24d, 0x3ec3ca3c, 0x3d91c96c, 0x3f0fc5ef,
    0x3f0a70ee, 0x3ea8dff7, 0x3ea57406, 0x3e6506c5, 0x3e13a6e1, 0x3e8010ae, 0xbeb78855, 0x3e8be643,
    0x3deb7cb1, 0xbf189147, 0x3f23ac21, 0xbb0cadf3, 0xbd9f504a, 0xbdee6b82, 0x3e1fa2ae, 0x3e86cfbb,
    0x3e0a2f9b, 0x3e412981, 0x3db533ca, 0x3f16eba5, 0x3dec9edc, 0xbdffd8d8, 0x3f03656d, 0x3d4d5a66,
    0x3eb784d9, 0x3ddf53cf, 0xbe4365a7, 0x3e4663d8, 0x3d43c9de, 0x3d9d56b7, 0x3db760da, 0xbd85c5a6,
    0x3d0dad28, 0x3e79cede, 0x3e0b84f7, 0xbc809bd3, 0xbe1478e1, 0x3e60ac27, 0xbec4df4e, 0xbd6b15cb,
    0xbf394cc4, 0x3cb4a340, 0x3eaf7f0c, 0x3e412d2a, 0xbdcd351a, 0xbdb1631f, 0x3db8c3ee, 0xbded142d,
    0x3dd40cfb, 0xbd502b92, 0xbe3c24fe, 0x3e2d19b2, 0xbe7c13fe, 0xbe7f6ffc, 0x3e3201d2, 0xbe49f697,
    0xbdcaefa2, 0x3ea129e2, 0xbeb02c43, 0xbe46e776, 0x3e166ada, 0x3e873e55, 0xbf349072, 0xbe99c1e3,
    0x3e760b12, 0xbda18c98, 0xbed18f70, 0x3ecf19d2, 0x3e096af5, 0xbe37a47e, 0x3ed99fa1, 0x3c24393b,
    0x3ea49ffe, 0x3db8e3ff, 0x3edf96b5, 0x3d6a21d7, 0x3e34dfb8, 0x3e1ab3c2, 0x3d20ca57, 0x3eaa3a7e,
    0x3ed28d8c, 0x3ea0d49a, 0x3dfd1033, 0x3edb47ad, 0xbda5ce47, 0x3e0ec04a, 0x3d9ff315, 0x3de464ae,
    0xbeaec9d8, 0xbe1f33f1, 0xbec268dc, 0x3e1d288d, 0x3e1f35d3, 0x3d05e496, 0x3e4d7c09, 0x3e69a3e5,
    0x3de47bbe, 0xbcf29e19, 0x3efbd930, 0xbea23342, 0x3e51ceb3, 0xbe8c2120, 0xbd165527, 0x3e2c485c,
    0xbca3ac20, 0xbe535a6e, 0xbe27ef7d, 0xbbcb155e, 0xbe87af45, 0xbea81679, 0xbd263cb1, 0xbdb9687a,
    0xbead0cb9, 0xbcb9143d, 0xbe473acb, 0x3e9483b5, 0xbaae0968, 0x3c503569, 0x3ed25682, 0xbe15dd28,
    0xbe6e82ce, 0xbd761f29, 0x3ec94d87, 0xbe409ffe, 0x3e82d1ac, 0xbdbd3fd1, 0x3de05bcc, 0x3ddfe776,
    0x3de04bd5, 0xbaccde82, 0x3dbb221a, 0x3e4e5e81, 0x3d33da03, 0x3e3f2411, 0xbe21bb49, 0xbea19a88,
    0xbdfcfb8a, 0x3e7e41ab, 0xbe019f4c, 0x3dacaf97, 0x3dbafb8e, 0xbd8dcdd7, 0xbf0faa29, 0xbe9127e0,
    0x3e525dd2, 0x3d9c4124, 0xbe0b1f27, 0xbeca3200, 0xbd8965de, 0x3d160f59, 0xbd8ef836, 0xbd840729,
    0xbea1d108, 0xbf03deb6, 0x3d7f1dd3, 0xbe0db144, 0xbd6f104f, 0xbe8efecf, 0x3e48c6d1, 0xbe8c6207,
    0xbd8128c2, 0x3dca2ec5, 0x3e05934e, 0xbecbe839, 0x3d76921a, 0xba749ea2, 0xbed22336, 0xbdb52e6c,
    0xbe4fc5b7, 0xbd791b29, 0xbe07ab55, 0x3c9452bd, 0xbd0324ea, 0x3defb646, 0x3d8d0101, 0xbe93de94,
    0xbe983fd1, 0xbe96e6d7, 0xbe11f26c, 0xbc29fb8f, 0x3cf35800, 0xbdcb2b8b, 0x3dd8697e, 0x3ddee654,
    0x3efedd1c, 0x3da48c8b, 0xbe1b8991, 0xbe5de899, 0x3e64d480, 0x3ca22211, 0xbef81b82, 0x3e8b1122,
    0xbdaa1bf9, 0x3ea1f513, 0xbeb1bd56, 0xbdfa921b, 0xbd6f882d, 0x3e4e912e, 0xbea7ab0f, 0x3bbd4f57,
    0xbee30d87, 0xbdc3a280, 0x3ed4f630, 0x3d1d4175, 0x3e5a860f, 0xbe203e41, 0x3e7d2d09, 0x3e3e834e,
    0xbcf1fa8b, 0xbd1af9bf, 0xbd3954bc, 0x3e1a316b, 0x3ebd4ea3, 0xbe1dbf90, 0xbe954519, 0xbe3b9708,
    0x3e1a2cf8, 0x3e1322f7, 0x3e2efa97, 0xbea10cbf, 0xbdfa60cf, 0xbdf2a8a2, 0xbd6b3e8d, 0x3dff5ede,
    0x3eac03f3, 0xbe2a5876, 0xbe05513b, 0x3d3c2e66, 0xbea93934, 0xbdad9580, 0x3e50e689, 0xbd332d6a,
    0x3e6fff0c, 0x3e716db6, 0xbded02ff, 0xbeb2f503, 0x3e70ef74, 0xbd1d24fb, 0x3d49bb3f, 0x3dce1e4e,
    0xbe8107c0, 0x3d165490, 0xbd8af485, 0x3ea3d43c, 0x3d622326, 0xbdb647ce, 0x3d964bc8, 0x3cb0b741,
    0xbe0deea5, 0xbe7776f5, 0x3e029397, 0x3e134455, 0xbe05091e, 0xbdd42baa, 0x3e68f0c0, 0x3ce78fc8,
    0x3bedf5fa, 0xbe72d15d, 0xbe15d208, 0x3e1a6353, 0xbe20ff3c, 0x3e3cb7ea, 0x3cfcb766, 0x3de8596a,
    0xbd81a65d, 0xbdedb39d, 0xbc104c9f, 0x3b9e4b09, 0x3cc53095, 0xbe2028a9, 0xbe2e93c7, 0x3e40285d,
    0xbd7e549d, 0x3e5345e5, 0xbc9a5dd5, 0x3df8e497, 0xbe80ea24, 0x3e8071d5, 0x3e6114cd, 0x3e0a84df,
    0x3e8729d0, 0xbe7ec999, 0xbe1cd218, 0x3eae5eff, 0x3e6ffdf5, 0xbe61989c, 0xbd896e13, 0xbdf7f33b,
    0x3f26f4b0, 0x3e272eff, 0xbe28ed97, 0x3e23735c, 0x3cdc0842, 0xbc943694, 0x3d9981d9, 0x3d336285,
    0x3e9862ed, 0x3decb193, 0xbc8782c5, 0x3e49dc69, 0xbe673a16, 0xbea1deed, 0x3d2ea7d7, 0xbe6709ba,
    0xbdd1d2ca, 0xbe78144b, 0x3d8b42e1, 0x3e6e00f1, 0x3ebffd0b, 0x3e20cc54, 0x3eb3e668, 0x3ea33445,
    0x3e8b0bb6, 0xbb844a50, 0x3eb86ac0, 0x3e5884ee, 0xbe827433, 0xbf10a63c, 0xbe645b28, 0x3ec035cf,
    0x3cc30a3c, 0x3e25dd42, 0xbd4c6473, 0xbe72851e, 0xbe3cc846, 0xbe978321, 0x3d884914, 0xbc968d1b,
    0xbe8b5c17, 0x3ef9990e, 0xbd91e40e, 0xb9d388f6, 0xbea67b3b, 0x3eaec4b2, 0x3ea96bd8, 0xbbfa5489,
    0xbeec548f, 0xbe28b5e1, 0x3e01e857, 0x3e9459e4, 0x3d71f44d, 0x3ed58539, 0x3e7bd324, 0xbf07bdd4,
    0xbd211c05, 0x3e925cb4, 0xbe8a485d, 0xbec84412, 0x3eec7124, 0x3e80d447, 0xbdc08fa7, 0xbde4c0b4
};

static const uint32_t _K41[] = {
    0x3d832822, 0x3dd04a4d, 0x3da35837, 0x3d65adbb, 0x3bfb110d, 0x3d95972b, 0x3d6c68d8, 0xbdd0e6fd,
    0xbd20fe0b, 0x3b353ffa, 0xbc8583a9, 0xbd8b950f, 0xbc387d25, 0x3deb29ba, 0xbd4d9b24, 0xbdd10c2a,
    0xbcf159fa, 0x3da0c401, 0x3dd16ad0, 0xbc471e1e, 0x3d670ed1, 0x3c07e797, 0xbddc111e, 0xbb303dd1,
    0xbdbbd872, 0x3d7b25d5, 0xbd3a4299, 0x3b98fa36, 0x3dafcbb9, 0x3d088733, 0xbbfc02c3, 0x3d916995,
    0x3d71f0e3, 0x3ced82a1, 0x3c391e31, 0xbd72cadf, 0xbd3856be, 0x3da2d009, 0xbcd524c4, 0x3d9689d9,
    0x3d117838, 0x3c93115b, 0xbdf3732a, 0x3db7461c, 0x3d2b67e1, 0xbd3dce9e, 0x3d30f36b, 0x3cbb52b0,
    0xbe1c4200, 0x3d33c68d, 0xbccf520f, 0xbd1aefa3, 0xbabc4a4c, 0xbe24aefc, 0xbd8adf98, 0xbd272b4f,
    0x3d18cde9, 0xbd41d140, 0xbd07d0ed, 0xbd4149c0, 0xbd4cc479, 0x3ce08954, 0xbd7fe2a5, 0xbe2dba31,
    0xbcd6b5fc, 0xbd1c033f, 0xbd9f5cf8, 0xbdb54b3e, 0x3e069386, 0x3ba1d0b8, 0x3e0464ff, 0x3d54a30c,
    0xbdbcd445, 0xbd64b31b, 0xbe1e9188, 0x3cf21d02, 0xbdffcad9, 0x3c9cd347, 0x3d2ed0fc, 0x3d8ddeb4,
    0x3da28ad7, 0x3da4172a, 0x3d749aed, 0xbdeb212e, 0xbcd95061, 0xbb866a92, 0xbe005388, 0xbdb59548,
    0xbdb597e8, 0x3da1a06b, 0xbd989dc7, 0xbaa24bf3, 0x3d14b3c5, 0x3cecf7c9, 0x3e0b9b7f, 0x3d445c1d,
    0xbe5bfd1e, 0x3d9c63a5, 0xbd896a26, 0xbe7ccdb7, 0x3d5a37a9, 0x3bd39049, 0xbb83e6fc, 0xbe28e170,
    0x3e0ede5c, 0xbd79a985, 0xbce5f1f2, 0x3dcb1572, 0x3df8224a, 0x3c86a25c, 0x3bef42af, 0x3e65e1fc,
    0x3e0190e5, 0xbdc327c0, 0xbd7df732, 0xbde170bb, 0xbd1b5333, 0xbd462dd6, 0xbd21790f, 0xbd8fedfa,
    0x3dbee6c9, 0xbd3e2b31, 0xbd2b22c2, 0xbd819baa, 0x3e069691, 0xbe24d922, 0xbc845adf, 0x3e190d93,
    0x3e475611, 0xbd3b79ca, 0xbc1329e0, 0x3db4d986, 0xbe1cdcbb, 0xbd9c5869, 0xbcec240d, 0x3dc89d6b,
    0xbe770a15, 0xbd0667e0, 0x3e1017ad, 0xbda7662d, 0xbe5134cf, 0x3d499c11, 0xbda7c9fd, 0xbe07115e,
    0xbe36930b, 0x3e29f016, 0x3d649465, 0x3bc8bd4d, 0xbd0d847b, 0x3e1bbed2, 0xbddcf843, 0xbe1f1f94,
    0x3d2a80c7, 0x3b9a4709, 0x3e43fbdf, 0xbdfdd131, 0x3ce34c17, 0xbc178b03, 0x3d36e166, 0x3df0bca6,
    0xbd0f966b, 0x3d3ac91b, 0xbd3228b5, 0x3dc2c837, 0x3d9e3fc6, 0x3c989eea, 0x3db038da, 0x3d8e63a1,
    0x3da8cd9a, 0x3d12fe2c, 0xbde143b3, 0x3e01a992, 0x3c0809c5, 0xbc808d37, 0x3e1c32ee, 0xbda9f85a,
    0x3dfbe7c8, 0x3c86a855, 0xba96a69e, 0xbca46ff4, 0xbc486a76, 0xbc9bc198, 0xbdd5bbfa, 0x3d8b7f95,
    0xbd8469a8, 0xbd5b5d4b, 0xbdfdba02, 0x3e43f75f, 0x3d2f7ede, 0xbcf761c0, 0x3d9cf280, 0xbda08bd5,
    0x3e423763, 0x3c59dbac, 0x3c57f7bf, 0x3e0cfd93, 0x3d75d9c5, 0x3d448ba0, 0x3d46164d, 0xbdbe1425,
    0xbd6ea7c4, 0x3da0847b, 0x3d6cecf3, 0xbdd23d57, 0xbd9a3d29, 0x3d5de75d, 0xbe261472, 0xbdb1a319,
    0x3b58f68e, 0x3e075d39, 0x3e42c6d5, 0x3d9c25b1, 0xbdbc58db, 0x3c50e1d1, 0xbdef8554, 0xbd27beb8,
    0xbcf00c7d, 0x3c533756, 0x3cf4e25f, 0xbe1cddec, 0x3d13d7bd, 0x3a77a4d6, 0xbd829d2e, 0x3e0687af,
    0x3d0264d8, 0xbc880c58, 0x3d560570, 0xbdbb58d0, 0xbc66d612, 0xbda6031e, 0xbbf3c0dc, 0x3de20392,
    0x3d29d063, 0x3d57d2f0, 0xbdd4fd25, 0x3dd4be50, 0x3d4df531, 0xbd57b8ec, 0x3db534ba, 0xbd977401,
    0xbdff4500, 0xbd64ed7a, 0xbd5d0651, 0xbd9e2b7c, 0x3be1983a, 0xbd83fa46, 0xbdb90d6d, 0x3c70465a,
    0x3c0ef7e9, 0xbd4a3b34, 0xbdb8c4d9, 0x3d2d1da0, 0xbdc7063b, 0xbc84c8d1, 0x3c929efb, 0xbdefb737,
    0xbcf663e2, 0xbc4b69b2, 0xbc048442, 0xbe0eaedf, 0x3d5676fb, 0x3d005d0d, 0x3e192f49, 0x3d079ba3,
    0xbdbaad2f, 0xbdd320ca, 0xbe0739e6, 0x3ce9784b, 0xbde97963, 0xbb5344e4, 0x3bbd4134, 0x3dd0a711,
    0x3d53d3ee, 0x3dce4f91, 0x3deaa975, 0xbdae85ff, 0xbdc6cc7f, 0x3ca6bbb7, 0xbe453ff9, 0xbc959b1a,
    0xbe1fcf07, 0x3e518758, 0xbd3a1542, 0x3ccd2990, 0x3dd21c82, 0x3c97b630, 0x3db389a6, 0x3d042112,
    0xbd54cc09, 0x3cf1410d, 0xbd8fc111, 0x3d751557, 0xbcfbb85d, 0xbe25bc4c, 0x3d8a4c0e, 0x3d8adcef,
    0xbc9c1d41, 0xbd94b2ab, 0xbd174e5c, 0xbcc5260a, 0xbe4ffa67, 0xbd0df3e6, 0xbc1263b4, 0xbdb945b1,
    0x3b9ca145, 0x3ce44302, 0xbd9edede, 0x3daba689, 0xbe1fdbd3, 0x3d93a1bd, 0xbcbee18d, 0x3d6cbbe3,
    0xbc85dbde, 0xbd37e97c, 0x3cd9d57f, 0x3d1b2305, 0xbd92753d, 0xbd4c0414, 0xbd1b57f2, 0xbd32f478,
    0x3db16b8a, 0x3ca04596, 0xbd1e317b, 0xbd6935c7, 0xbe27c843, 0x3dbc294c, 0xbd91117a, 0xbd4d08a2,
    0x3c98f3b8, 0xbc6b24f8, 0xbbc33015, 0x3dff01f8, 0x3d1585b8, 0x3dad2d44, 0x3ba5c981, 0x3d85de10,
    0xbd7ab3de, 0x3de1f3b5, 0xbc5f0246, 0xbdae2f1a, 0x3e0a5a26, 0xbde8708e, 0xbd81aee1, 0xbb5cf98e,
    0xbd513daf, 0x3cac36e7, 0x3da877ce, 0xbdc90fcd, 0x3d5a315e, 0xbceab044, 0xbcdcd4f9, 0x3db04d10,
    0x3ba22929, 0xbe4cc653, 0x3dc77a23, 0xbd3144dc, 0x3e0ab243, 0x3ca4f22a, 0xbd1bc35f, 0x3ce0b88e,
    0xbdb0bc79, 0xbda45730, 0xbc828d5c, 0xbc405b33, 0xbe01c06a, 0x3b4ca484, 0x3e17002c, 0x3d9d636a,
    0x3de877f1, 0x3d5e531c, 0x3e2acae7, 0xbd51d15a, 0x3d4a3365, 0x3d8fc096, 0x3d413c6b, 0xbd148cdc,
    0x3d01c4a1, 0x3e1ced70, 0x3e2cb827, 0x3d079c8f, 0xbd2d94d1, 0x3a949147, 0x3d7bea19, 0x3cb47809,
    0xbdc964c5, 0x3db86a8a, 0xbda95d33, 0xbc6a403d, 0x3da1ab26, 0x3bd73c3f, 0x3ccf7374, 0xbe249764,
    0xbd6db868, 0x3d85deab, 0xbcc6565c, 0x3d20d9a3, 0x3d4a7060, 0x3da01325, 0xbe4364a5, 0x3d923d10,
    0xbd1eb91f, 0xbd28a485, 0xbd4e5b72, 0x3dc230b1, 0xbd5fcf6a, 0x3cfaeb1c, 0xbba47de4, 0xbcf28a9a,
    0x3d4576ca, 0xbd814c0c, 0xbd961f1d, 0x3cf919a7, 0xbdb92b8d, 0xbe0309db, 0xbd9b72b7, 0x3c5b7c6d,
    0xbdcd5127, 0x3de7e8e6, 0xbda3f19b, 0xbd36644b, 0xbd8bd75b, 0x3c049a0f, 0x3d4dccdc, 0x3c83abb5,
    0x3d6621ef, 0xbcdf6838, 0xbe1d1da1, 0x3d16d5a1, 0x3e10312d, 0xbdaa4aff, 0x3db8f003, 0x3da5c5c3,
    0x3db25e8e, 0xbd4c8455, 0xbd28e278, 0x3ba987f1, 0x3cd64abb, 0xbd6ff634, 0xbcd2bc40, 0xbcec39e9,
    0xbda7b42d, 0xbdaa1ac0, 0xbda78cc8, 0xbddf43fe, 0x3e3dd2d7, 0xbc959734, 0x3da5e722, 0xbd84e735,
    0xba843a6e, 0xbdf39200, 0x3dc8a5b0, 0x3deeda11, 0xbd2b0c81, 0x3caecfb7, 0x3cde23a5, 0x3e06c54f,
    0x3d800759, 0xbe16f8d2, 0x3ccfea4d, 0x3da2722e, 0xbe01dc32, 0xbd0d2fb8, 0x3d902a88, 0xbd060a36,
    0xbcb7d58b, 0xbd6af363, 0x3c559d20, 0xbddef3db, 0x3dbb28ed, 0xbc99021a, 0xbb82ab25, 0x3bff8ad7,
    0x3d3db6de, 0x3d04ac92, 0x3cca2797, 0xbbeae22b, 0x3e459ef5, 0xbe117a76, 0xbd07e20d, 0x3e0c29e3,
    0x3be640c0, 0x3d09c953, 0xbdbdf82d, 0x3c25826a, 0xbdf6e993, 0x3ce06a0b, 0x3da13ee1, 0x3db9952e,
    0x3d4eedfe, 0xbaa7dfee, 0xbdb5f550, 0x3c2c789f, 0x3df023df, 0xbca712c7, 0x3ddbb31b, 0xbdde75a6,
    0xbe26d9b2, 0x3dda3194, 0xbd222cf4, 0xbab142b6, 0xbc8f4b67, 0xbdb7cc42, 0xbc8f896c, 0xbba43561,
    0x3d12a2cb, 0xbdde2a06, 0xbbdce0fc, 0x3e027bdf, 0x3d0d26f7, 0xbd6988ab, 0x3bff35be, 0xbcd81a14,
    0xbcc52fa9, 0x3e06188e, 0xbdf0eca5, 0xbdc3a0fc, 0x3abd7fb1, 0x3d98e9ee, 0x3c8a2ea8, 0xbd3deee0,
    0x3c472d55, 0xbd936b55, 0xbd00df2e, 0x3da7d320, 0xbd2d912c, 0x3ccf4010, 0x3da2325a, 0xbcb9a4b8,
    0x3b939f0e, 0x3dabff50, 0x3d7b333c, 0xbb8316b4, 0xbcf4e0ba, 0x3d8d9fed, 0xbd2a1ec7, 0x3d8e848d,
    0xbd2fe69e, 0xbdcbabcc, 0xbd037f37, 0x3db18d80, 0x3d60ffe1, 0xbd5948cd, 0x3b60f385, 0x3d35b3ea,
    0x3e0653dc, 0x3d8d2777, 0xbd12a414, 0xbdf37064, 0x3c409895, 0xbdc05dd2, 0xbc2d236c, 0xbc876fba,
    0xbde56696, 0x3ca87c79, 0xbd44f8aa, 0xbc824b1d, 0xbd5a749d, 0xbd1bdebc, 0x3dc3974f, 0xbc15bce0,
    0x3e0e6ed2, 0x3d357142, 0x3e46cdab, 0x3bcc0cd2, 0x3ceeb4de, 0x3c456cd2, 0xbaf02e5b, 0x3d8a892e,
    0xbd998b84, 0x3bab0d05, 0x3c51dbe4, 0xbd2504c4, 0xbd6643e7, 0x3d385c14, 0x3d200a69, 0xbd2e498c,
    0xbd3f1bb0, 0xbda05b21, 0x3d20982b, 0xbb18fce8, 0x3e211284, 0x3d14cdd2, 0x3cdf496d, 0x3d9d9322,
    0x3cbe579d, 0x3bf0b56b, 0xbd0e0d13, 0x3cb4d8fa, 0x3dedad2b, 0x3d90aa17, 0xbc8e1431, 0x3ca2bc48,
    0xbd9dbffb, 0x3e047bd8, 0x3cfb4359, 0xbbc51a2f, 0x3e0237c3, 0x3daccd5d, 0xbd4dbc67, 0xbd88aa46,
    0x3bc0a586, 0x3d96fd37, 0xbd40bb97, 0x3e1c15d1, 0x3dae72e3, 0xbdb5c499, 0xbc8407d0, 0x3d579858,
    0xbd843b86, 0xbc8b0c52, 0xbd821933, 0x3d8b07e0, 0x3c8e42ab, 0x3e284e17, 0xbbbb4971, 0xbe46616e,
    0xbd13f6c6, 0xbda38c91, 0xbccf45c7, 0xbce23b42, 0xbdf3f37e, 0xbbdb041a, 0xbc653a38, 0x3dd7d9f6,
    0x3d44022b, 0x3def3170, 0x3d1756e3, 0xbd626089, 0xbca4048c, 0x3dd63946, 0xbc96e140, 0x3d328dcb,
    0x3d939eb5, 0xbda23f4a, 0xbc6a2ac7, 0x3dda6abe, 0x3d30dbf5, 0xbe193783, 0x3c928519, 0x3e13fc81,
    0xbca5d426, 0x3e069c61, 0x3cb36791, 0xbe6650d4, 0xbd0d687e, 0xbe150579, 0x3d1a94cc, 0xbdc4aabf,
    0xbcf3d27d, 0x3d74f8e2, 0x3cc37aa5, 0x3ddcb377, 0xbd88c3fd, 0x3d860bcf, 0x3cd6daf2, 0xbd761899,
    0x3c480e28, 0x3d6c507c, 0x3e07eb29, 0xbc0c942c, 0x3ce7b6c8, 0xbdb2d8ae, 0xbd994b13, 0x3d40852a,
    0xbd49da4c, 0xbd954e00, 0x3e036a50, 0xbd0b6d67, 0xbd65986b, 0x3d6174d7, 0x3d8ec5b8, 0xbd15dc02,
    0xbc12f817, 0x3c3b2bc4, 0xbcc11699, 0xbd86d32d, 0x3d8e1b81, 0x3dad1535, 0x3d46b7ed, 0xbdcc57b9,
    0xbce7a2de, 0xba81f673, 0xbc565328, 0x3d60d3d5, 0x3c0f9aea, 0xbcc41fbe, 0xbdf2412e, 0x3d482c9a,
    0x3d33ae5e, 0xbcbe032c, 0xbd924ca1, 0x3b6b2cfd, 0xbde00ffe, 0x3c4ace5d, 0x3ce17e74, 0xbcc10f4d,
    0x3d1ddafe, 0xbccb8f2f, 0xbd960188, 0xbd684149, 0xbd455276, 0xbd3bd525, 0xbc848a68, 0xbce297da,
    0xbcbbe9ca, 0x3dcb6c14, 0xbc9c9d9a, 0xbc843370, 0x3d53a3d6, 0x3c336465, 0x3c06c8f8, 0x3d03fd99,
    0x3d79d113, 0x3d4bdc7a, 0xbd919740, 0x3c7234aa, 0x3da9208d, 0x3ba9697b, 0xbd9f04af, 0xbc0efdd0,
    0x3d44ff18, 0x3d0c3619, 0xbd390aac, 0xbb3c28ca, 0xbcb33774, 0xbd9ce62b, 0xbc77d0f1, 0x3d08962c,
    0xbd3c54e3, 0xbddea29f, 0xbdeefa12, 0xbd2b113b, 0xbbced0ee, 0xbd246f89, 0x3ce89407, 0xbd8160f9,
    0xbc0af174, 0x3d0f1c8e, 0xbc5c879a, 0xbca16729, 0xbe534a58, 0x3d89a144, 0x3d1720d0, 0x3c65bf4b,
    0x3db33bbd, 0xbbec2720, 0xbcde9dc3, 0x3d4224ac, 0xbdfa47b6, 0xbd9ad754, 0xbcac1fa5, 0xbd40a3e2,
    0xbd4e2747, 0xbd9917e2, 0xbd8c9185, 0x3c1e13eb, 0x3dbf05de, 0xbd6bd7b1, 0xbcac8258, 0x3d469716,
    0x3d9c673f, 0xbd2ead17, 0x3d19a37f, 0xbc9bb030, 0x3dda5804, 0xbd5cf898, 0xbb0bf086, 0x3dc3b400,
    0xbd045ba4, 0x3d64507b, 0x3e032adf, 0xbdb91f81, 0x3dfef0c3, 0xbd276428, 0x3ccd2dc6, 0x3c7151e2,
    0xbdc86014, 0x3d1cd0fb, 0x3b8ead88, 0x3d397090, 0xbd5f6033, 0x3d8f69e1, 0xbda364df, 0xbb90ba88,
    0x3e09b2ea, 0xbc0d363d, 0x3caa8013, 0xbd807662, 0xbd54c108, 0x3dc1d345, 0x3c245cf5, 0xbd3999e5,
    0xbdf793b0, 0x3dfc93c2, 0x3b9505fd, 0xbe520aa3, 0x3b9b23b7, 0x3d8650d6, 0xbd025670, 0x3d1e05c8,
    0x3d9bde79, 0xbd0539be, 0x3d0e6775, 0x3d977772, 0x3d023243, 0x3d30954f, 0xbd286b23, 0xb9da0800,
    0xbd3b8b94, 0x3d9ef1e3, 0xbd577178, 0xbc052eb5, 0x3d0868d3, 0xbc9f7bb8, 0xbdac7b1a, 0xbd2157e0,
    0xbc1954d2, 0xbc7aac4a, 0x3d0ce514, 0xbbca54c6, 0x3d1d7ddf, 0xbcd55dc6, 0xbcb430cb, 0xbccdd77e,
    0xbb2ac46e, 0x3d1444af, 0xbde2cd69, 0xbe56d187, 0xbc113781, 0x3db88c7f, 0x3cf83598, 0xbc9eb90d,
    0x3c9aecc5, 0xbd6c8dc0, 0x3d13c22a, 0x3e36acda, 0x3d1df230, 0xbbb87f61, 0x3c8e1092, 0x3c288aa1,
    0x3daf2513, 0xbc8de781, 0x3cb86366, 0xbe023e07, 0x3dad9eae, 0xbd8e0202, 0xbe18737f, 0x3c89c1bc,
    0xbe00e169, 0xbd9cbb3a, 0xbda96959, 0x3cd27ca8, 0x3d4d8596, 0xbc928ac2, 0xbd7ae330, 0xbd215379,
    0x3ccca3af, 0x3d13f362, 0xbda75e05, 0xbcc0086d, 0xbd731b55, 0xbd3706ad, 0x3d4046cc, 0xbd3d7f6d,
    0x3c0c63b2, 0xbcae584e, 0x3d14e635, 0xbddced58, 0xbd074a1a, 0xbe0ffaa8, 0xbc919191, 0xbe1b4ef0,
    0xbceb8964, 0xbdc048bf, 0xbc2231bf, 0x3df96445, 0x3dd1a987, 0xbd871904, 0x3e1653d8, 0x3cb7108b,
    0x3d59b7c5, 0xbda1d312, 0xbcc7e52d, 0x3d1786cf, 0xbe3daae3, 0xbd72fc46, 0x3c99fb1c, 0xbe066ad1,
    0x3c4d5ba0, 0x3e2293f7, 0xbd8363fe, 0xbe32defb, 0xbd0d1d7e, 0x3d1837fa, 0x3d9a484f, 0xbda00a40,
    0xbdd9df66, 0x3d35b36d, 0x3cec5e18, 0x3c53a0b1, 0x3e4539fb, 0xbb915916, 0x3d70c647, 0xbc089969,
    0x3ddc56fa, 0xbd57d8fa, 0xbd539352, 0x3ddc6baf, 0xbce22b4f, 0x3cf0399f, 0xbd84df33, 0x3e0039c4,
    0x3dc70253, 0xbbf79c88, 0xbcd048ca, 0x3d0d60b3, 0xbe0633af, 0x3d38aa38, 0xbc1b9158, 0xbd95bd3b,
    0xbdc83e70, 0x3d663bbc, 0xbd47ba6b, 0x3d2efe87, 0xbca3ed25, 0xbd80b3fb, 0x3d789d29, 0xbc9e651b,
    0xbcdbcc6b, 0xbd3fcc75, 0xbb9621e2, 0x3dbbb102, 0xbdf38023, 0x3ddad542, 0xbd899954, 0xbdea6b92,
    0xbdd0bd39, 0xbceca323, 0xbe08d7e6, 0x3d66d80d, 0x3daf7d26, 0x3d5a4278, 0x3cd7b481, 0x3dbaa089,
    0xbca3c343, 0xbd2a8c3a, 0xbc63024e, 0xbcc8704e, 0x3d15a9d1, 0xbd0d3787, 0xbd782b2e, 0xbc3785a9,
    0xbe08bab0, 0x3e0c4fd2, 0x3c69804d, 0xbdb66072, 0xbcf48c5c, 0x3cc91d45, 0x3d14eb3a, 0x3c9cc7d7,
    0xbcbbe2e5, 0x3daf831b, 0xbd5d76ec, 0xbde72ce6, 0xbd7db36a, 0x3d7cca4f, 0x3da94be3, 0xbe0f14a5,
    0x3de821fa, 0xbd351038, 0xbdc7d3bf, 0x3e047d3e, 0x3d825884, 0xbc30f034, 0xbcff5804, 0x3d4c502f,
    0x3d3157fc, 0xbc73b226, 0xbdb54435, 0xbd4b0dfd, 0xbd15d26a, 0xbdcfe852, 0xbdbfeda3, 0x3b8a6a9b,
    0xbd92a66b, 0x3d93c61c, 0xbe10e774, 0x3bb3e590, 0x3d018734, 0x3cdfd039, 0xbc104fde, 0x3d9481ae,
    0x3dabfe6b, 0xbd4b6e29, 0x3daffcfd, 0x3d26b8e5, 0xbdbfa30c, 0xbd8f70c6, 0x3a902fbe, 0xbcf7eeea,
    0xbdaae08d, 0xbd2008cc, 0x3da1eea4, 0xbe3abe33, 0xbd5cfda6, 0x3d1b5c70, 0xbc9e0799, 0x3d16678e,
    0xbd4346ea, 0x3d7fde0e, 0x3e2740f1, 0xbd14095d, 0x3c5c1365, 0x3de5bcbd, 0xbdb69b03, 0xbdd69e5c,
    0xbccb9370, 0xbbca1889, 0x3dba9da9, 0xbdd64e08, 0x3c95b5bc, 0x3dc38940, 0x3c1400c8, 0x3dc69be7,
    0xbdcf0bd0, 0x3d5f7a9c, 0xbd6e7fef, 0xbd1101dc, 0x3e0a94bb, 0x3d1f7304, 0x3d0a455f, 0x3d3f905a,
    0x3cb3dbc8, 0xbb69a827, 0xbe010be2, 0x3dba5fcf, 0xbcb5404c, 0xbcbba71b, 0x3db4d1bc, 0xbd1aabe5,
    0x3d91a651, 0x3d0398cc, 0x3d0103c1, 0xbd5b9387, 0xb8548799, 0xbd42fb1e, 0xbdc456f8, 0x3d2ec0b8,
    0xbd3c0185, 0xbd9cc6f7, 0xbe30a254, 0x3e19c5d3, 0xbb847a21, 0xbd34c26f, 0x3dcdf778, 0xbdd1db08,
    0xbcecebfb, 0x3c480c91, 0x3db050f6, 0x3dc5d119, 0x3dcea1cd, 0x3da825e1, 0x3d3d610e, 0x3e066771,
    0x3cee908b, 0x3d16e1eb, 0xbddcb24e, 0xbc2b1364, 0xbda8cfdd, 0x3c5e7a8d, 0x3d4a092f, 0x3db65509,
    0xbdba5a72, 0x3ce2c52d, 0xbd8873fe, 0xbbf54fd4, 0x3df47f87, 0xbc7141a4, 0x3d1ec464, 0xbcec6d6b,
    0xbdaaf33f, 0x3e07d03e, 0xbd648974, 0xbcde78b7, 0xbd127fd4, 0x3cc4549c, 0x3d5d1486, 0x3bc6a896,
    0x3cbb6562, 0x3c3cdac9, 0x3c64be1a, 0xbd5795f5, 0xbca07327, 0xbdb3e4af, 0x3cfea176, 0x3d06280f,
    0x3d1db503, 0xbcbe6698, 0xbc87fcc0, 0xbd3c7f09, 0x3dc790e0, 0xbdd5fdc0, 0x3d8f661c, 0x3ca074f0,
    0xbd8cb05e, 0x3db8a6c3, 0xbb9f40da, 0xbdbd685f, 0x3bcb0c8b, 0xbc39b1a8, 0xbd955f46, 0xbd240fed,
    0xbd881a97, 0xbda1ae36, 0xbbced900, 0x3e10db00, 0x3d0c06fc, 0xbbea2a6a, 0x3d33cd49, 0x3e2afa11,
    0xbd50fefb, 0x3df3ed11, 0xbd9b0040, 0xbe24d311, 0xbd19f41a, 0x3e000539, 0x3d333836, 0xbe411d17,
    0x3d9d9590, 0x3d8154bd, 0x3c06f2b8, 0xbcc886c2, 0xbd390361, 0x3e0f4cb7, 0xbc29e7cc, 0xbd0f588d,
    0x3b1c6967, 0x3dcfdc6b, 0x3dbe30d8, 0xbd566079, 0x3d1ff754, 0x3d3d4096, 0xbd0c688b, 0x3de9f2ee,
    0x3cda03f3, 0xbe66e43a, 0x3d717d21, 0x3dc44395, 0x3a386eaa, 0xbd9f99f4, 0xbc2f847b, 0x3e4d6a8d,
    0xbd9df0f3, 0x3dadf5ac, 0xbb809f17, 0xbe1d7058, 0x3e3bf5cd, 0x3dc0bbcb, 0x3d553d20, 0xbe170048,
    0x3c2d6923, 0xbd4a9e28, 0x3c87dae3, 0x3d93a73a, 0x3e1d63fd, 0x3d4d46e6, 0xbdb1d0f1, 0xbb4d0cdd,
    0x3c2767d4, 0x3d879071, 0xbe10911f, 0xbacb1620, 0xbcd1d1ad, 0x39d0ab2d, 0xbd3740ef, 0x3dab105a,
    0xbc83acba, 0xbd49860b, 0xbcf90e3f, 0x3df6b2c1, 0xba12a6f6, 0xbdf8288c, 0x3d1761bb, 0xbd1362b0,
    0xbdcad44c, 0x3d27b205, 0x3b94f01f, 0xbcd3c9c0, 0xbcc856b1, 0xbd6148de, 0x3c418425, 0x3d3a0003,
    0x3e4b8a76, 0xbc0cc420, 0xbd48a90a, 0x3ccfef93, 0x3da8d661, 0xbd8baf21, 0xbc99c30d, 0xbb4b29cd,
    0xbcf50f26, 0xbdc7036e, 0x35bc76d2, 0x3ce2cf9e, 0x3d80b6d6, 0xbd30a191, 0xbd6c8b60, 0xbdc76e6a,
    0x3dc4472a, 0xbde45f1f, 0xbd96423a, 0xbd53df42, 0x3e3f47f5, 0xbd90dc6d, 0x3bf7e4ea, 0xbd3552ae,
    0xbdd648e7, 0xbdf6f785, 0x3e141e68, 0x3e21082c, 0xbcd77be1, 0x3d632f7a, 0xbc1da6d7, 0x3dd51128,
    0x3deaf8b8, 0xbdc45b88, 0x3dae50b5, 0x3d9548ed, 0xbd7855b8, 0xbcc59b93, 0x3b89517e, 0xbd89fee7,
    0xbbf3e067, 0xbe068f6d, 0xbd48779d, 0xbdaf82d0, 0x3db10c86, 0xbd99157d, 0xbda8c518, 0xbd3604a0,
    0x3d6ea8c9, 0x3d8f95eb, 0x3c954c4d, 0xbdb6df22, 0x3e32c147, 0xbe394d38, 0x3cafcba4, 0x3d2c686b,
    0x3d04aae8, 0xbcb2c3ac, 0xbd0b9bb5, 0xbb91cf09, 0xbd11d5b2, 0xbdcd436e, 0xbca4672b, 0x3ddc5c9a,
    0xbc78c354, 0xbbe1b1e8, 0xbe12851b, 0x3db23b37, 0xbd5728e7, 0xbc7fa5b3, 0xbd5d6662, 0xbdeb175c,
    0x3d3008c1, 0x3c28dda9, 0x3d12e34b, 0xbb6063e2, 0x3d25d161, 0xbdfde860, 0xbe1db04c, 0x3e39b67c,
    0xbddaf727, 0x3cd34fa3, 0x3df32d97, 0x3998917f, 0x3d8bc0e1, 0x3e2523c4, 0x3dde38b9, 0xbbce0c9f,
    0x3dc3fb7e, 0x3de63d74, 0x3c7d18b7, 0x3c532817, 0x3d420e2d, 0xbda3e94d, 0x3d03028a, 0x3d8e3d99,
    0x3e1b6447, 0xbc90d167, 0xbcd670b9, 0x3d6614e0, 0x3e1e90e4, 0x3d266149, 0xbd80aac7, 0x3cad37db,
    0x3c11e75e, 0xbde9dbe2, 0x3c9e4af4, 0x3bf37100, 0x3d269939, 0xbe0a026b, 0xbe085c06, 0x3d71dfc2,
    0xbde0ca28, 0xbd189fa5, 0xbd2e5004, 0xbd9d803b, 0xbd22cfc9, 0x3e60d1c3, 0x3d5a92d5, 0xbdd26afd,
    0xbddb55ea, 0xbe24217c, 0xbd2358c9, 0x3cb72524, 0xbd85a83c, 0x3d43186b, 0xbdcdc82d, 0x3c9b1ee0,
    0xbda07348, 0xbe00dc19, 0x3a1d0e7e, 0xbdaf229b, 0xbdd6f990, 0x3d11dddb, 0x3cdb4130, 0xbdb13861,
    0xbd8ea200, 0xbdc9ddcb, 0x3cff913f, 0x3dbc9896, 0xbe1fcfab, 0x3d72299f, 0x3c87be7a, 0x3e7d1bf8,
    0xbdd280c0, 0x3d182b79, 0xbbb358fa, 0x3c6fd40c, 0xbcc129c2, 0x3d5610eb, 0xbd139425, 0xbc060d14,
    0xbcc47af2, 0xbda4e152, 0x3c3bb332, 0xbe0b1380, 0x3deb34ba, 0xbbf7dc46, 0xbcebb9fa, 0xbe1ecdb3,
    0xbd333abe, 0x3b11afa9, 0x3d0ced69, 0xbd51d38b, 0xbd5acee4, 0x3d192e06, 0xbdd9bf6f, 0x3dc24a67,
    0x3e050ade, 0x3d213c9e, 0x3ca708ae, 0xbdb6c6d3, 0x3e866eb2, 0x3d3cb640, 0x3c6cc141, 0x3e1a7393,
    0xbe169c53, 0xbd195863, 0xbcd0a4d3, 0x3d8cf2b7, 0xbd6d6297, 0x3db184d9, 0x3ce22ad4, 0x3e4c6598,
    0xbd6cd332, 0x3c37127c, 0x3d7679f8, 0x3caa7e37, 0x3dadee56, 0x3a52002d, 0xbde6aab8, 0x3d6827b2,
    0x3d59d1a6, 0xbcd4a51d, 0xbd9083a6, 0x3d64ea2c, 0xbd508b68, 0xbdb4c253, 0xbc8f522c, 0xbd1cfc99,
    0x3d70777b, 0xbd06832a, 0xbdb28540, 0xbd09733a, 0x3e008cd0, 0xbd83dbdd, 0x3d509eab, 0x3d2d19cf,
    0x3cef0cde, 0xbdae5896, 0xbcd4873f, 0x3d04fd70, 0xbd6416f1, 0xbcc16fc6, 0x3c8c60b0, 0xbda06324,
    0xbcea7f2e, 0x3e18cea1, 0xbd985a75, 0x3d27fe41, 0xbd47fb03, 0x3d5832b6, 0x3cc0df7a, 0x3d418ac4,
    0x3d06849c, 0x3d9d305c, 0xbe2355bc, 0x3e5220f1, 0xbe383700, 0x3d8feeab, 0x3dfb44e2, 0x3d6a054b,
    0x3e08c421, 0x3bace086, 0x3ceb9461, 0xbdac8713, 0xbc92994a, 0x3db3170a, 0xbddfed80, 0x3e5a5947,
    0xbdd63252, 0x3d9fd315, 0xbbda6df7, 0xbde663b3, 0xbd4c30e3, 0x3e3d6568, 0x3b0929e2, 0xbccf0a91,
    0x3c15343a, 0xbdb6f077, 0x3e204c10, 0x3bbfa94a, 0x3da3f3bd, 0x3d843b94, 0xbd21da98, 0x3cda0546,
    0x3c9d0254, 0x3e0693e5, 0xbc9a85c5, 0x3c2af7aa, 0x3d4b6fa5, 0x3be63243, 0xbdd71748, 0x3e0ada48,
    0xbd9eed61, 0xbca2bc04, 0x3c099aa8, 0xbd8e19e4, 0xbcf8249b, 0xbd6ce14f, 0x3dd62c2a, 0xbdcf24c9,
    0x3cf6ff78, 0x3db12f9a, 0xbd6fe777, 0xbe27f1f0, 0xbdc1af74, 0x3d30a691, 0xbaff8fc5, 0xbdd09574,
    0x3d1e14bd, 0xbbc4c4a9, 0x3d6ea7c2, 0x3c0b5f18, 0xbd79ba6f, 0xbd897be5, 0xbd27fb74, 0xbd92b67c,
    0x3c4a0cd2, 0xbd85c3b2, 0x3c6076b4, 0xbd0db04e, 0x3d140285, 0xbb156ee6, 0xbcb386c4, 0x3d6dc96a,
    0xbd39eae2, 0xbd29a1dd, 0x399a8a64, 0x3cab796f, 0xbc6d15d4, 0xbc9d4339, 0x3db3e278, 0xbd2eaec7,
    0x3d7bf526, 0x3d9d184d, 0xbd4795c9, 0xbda15f74, 0x3c9dff22, 0xbd084db2, 0xbd792df0, 0xbc0f3539,
    0x3c143e5c, 0xbca14537, 0xbd6df5e5, 0x3d8b4d39, 0x3c03e7da, 0x3c33b562, 0xbc61d8a8, 0x3d2b0bf2,
    0xbc74be7f, 0xbd3b67e7, 0x3bba0ccc, 0xbcc39c96, 0xbd1e090c, 0x3c0ea62c, 0x3c7f1370, 0xbc7e8536,
    0x3db33ef3, 0xbd355299, 0xbd24caab, 0x3d85ed76, 0xbc8823f4, 0x3d113aae, 0xbc91a945, 0x3ce2ad5e,
    0x3c43e291, 0xbdae96e3, 0x3d44b0d0, 0xbd1e8f7f, 0xbd8faf1c, 0x3cc5503e, 0xbc78b7f4, 0xbda4d462,
    0xbd1f2565, 0x3d4833c2, 0x3d5244db, 0xbd1a61eb, 0x3dd6c105, 0xbdbdb2d0, 0xbd83e806, 0xbe8e14af,
    0xbd991f99, 0x3db27878, 0x3c879b24, 0xbcd5b535, 0x3e32471a, 0x3dd264f8, 0xbd7165d6, 0xbd0ffd41,
    0x3d6bb1fe, 0x3e0c9071, 0x3b27748b, 0x3d6a09c6, 0xbdc700eb, 0x3dbb01fb, 0xbda96ab3, 0x3c738f30,
    0xbe1e07be, 0x3cda3f70, 0x3de33f8e, 0xbc40361a, 0xbd304c40, 0x3d9bf00b, 0x3de0d7b2, 0xbc4c6c5a,
    0xbc137fb7, 0x3e2eff66, 0xbd876a70, 0xbda69d0b, 0xbc27d262, 0xbca9437b, 0x3b01d0c6, 0xbb06c2cd,
    0x3e05a5d8, 0x3dd76c42, 0xbd3c5f4a, 0x3e1d7060, 0x3de2ac4e, 0x3d974fe7, 0xbc0fea57, 0xbd11acd1,
    0xbd8204c8, 0xbd95d34f, 0xbe00b99d, 0xbc625b30, 0x3b0d8e8e, 0xbd33df06, 0xbce74507, 0x3db1a9a5,
    0x3cafe13a, 0xbe072f3b, 0xbd813ca2, 0x3cd1c934, 0x3df87021, 0xbd5f134b, 0x3db9fffc, 0x3dace33b,
    0xbdeb0955, 0xbe00a2c5, 0x3e0566d6, 0x3da3e714, 0x3d1a32fb, 0x3d952d0c, 0xbd87e4be, 0x3dd9f814,
    0xbceed534, 0xbe1e8bbf, 0xbc86e32c, 0x3e1670f6, 0xbe5f9c48, 0xbdfc9832, 0x3dc00641, 0x3ce393fe,
    0x3dc9c5c7, 0xbdae1a78, 0x3d1c1da4, 0xbdd1ed5f, 0x3e008c30, 0x3ca167f4, 0xbc64c2dc, 0xbde592ab,
    0x3cbd394f, 0x3db3127e, 0xbc597159, 0xbd85a605, 0x3e62b077, 0xbe53fa41, 0xbd36c0ed, 0x3d7a00e1,
    0xbc9a605d, 0xbd4ba2b5, 0xbb1016aa, 0x3d114abc, 0xbc831dc0, 0xbbb48fd9, 0x3dc9a314, 0xbe2019cb,
    0xbd86803b, 0x3d2ca41c, 0xbcd463d7, 0xbd383e33, 0xbd55745e, 0x3d0ff6b9, 0xbe27faa5, 0x3cc3ce35,
    0xbd51c565, 0x3dd7ec44, 0x3e1c3e08, 0xba8a470c, 0xbe0b9f08, 0x3d8f9cc8, 0xbe34c1c4, 0xbdc608f1,
    0x3c121450, 0x3be355a9, 0x3d3d73a6, 0xbdd5abd5, 0x3cf59821, 0xbd919ae5, 0x3d096d1f, 0x3c3aca4f,
    0x3d56b4a6, 0x3d5446c9, 0xbcaec2f4, 0xbdd25bc2, 0x3baef3cf, 0x3c7a44e6, 0x3d29ca4c, 0x3cc0481e,
    0x3d3f3241, 0xbd37ca2e, 0xbd024b4e, 0xbce07fb0, 0x3dbfad21, 0xbcf1b3a0, 0xba07d9f2, 0xbc4e4c86,
    0x3c64679d, 0x3d8262f4, 0x3d02a83f, 0xbd7e5a58, 0x3de7f781, 0xbd45c4da, 0xbe305a86, 0xbae66d5e,
    0xbdaa2c8c, 0xbd5480bd, 0x3d820b51, 0xbcea7faf, 0x3d7da820, 0x3d6fe402, 0x3cafd01e, 0xbbb23e29,
    0x3c22ec3e, 0xbccea690, 0xbcbda0ce, 0x3d3c650f, 0x3dbd961a, 0x3d668204, 0x3d2d42bb, 0x3da509d1,
    0xbcdf1d27, 0xbd0af27f, 0xbe5da19b, 0xbc1f4fc7, 0x3d923c37, 0x3d21fafb, 0x3d0aa823, 0x3c35256c,
    0x3d3eec81, 0xbc35db6a, 0x3d33d2b0, 0xbdee180a, 0x3baf0174, 0x3d855127, 0xbe283c05, 0x3b8bcf22,
    0xbd6759c2, 0x3d8abf5d, 0xbdce17a4, 0x3d8c4950, 0x3da54e28, 0xbc8ecfc7, 0x3d03d3c6, 0x3b927377,
    0x3c16ab89, 0x3caed6c9, 0xbe094ead, 0xbdeeb0c4, 0x3c5673e2, 0xbd29e641, 0x3c957e98, 0xbc0a0c81,
    0x3d154ab1, 0xbdbf6bda, 0x3c37dc10, 0x3d774418, 0x3cc352b0, 0xbdc4cb03, 0x3d9af98e, 0xba9bd4c1,
    0x3d9fc287, 0x3d9e2e49, 0x3c4cf0f0, 0xbd4da157, 0x3d272ed1, 0xbbe06236, 0xbba572f4, 0xbb7cfb3e,
    0x3d616758, 0xbe1c5608, 0xbaa4c26e, 0x3e3ecbbf, 0xbcb9289c, 0xbd772185, 0x3d2fa827, 0x3e017690,
    0xbd6e7f3a, 0x3da05c39, 0x3ca2e722, 0xbc3706e4, 0x3d458bea, 0x3d7837b0, 0x3d6d642a, 0xbd5f7c76,
    0xbcd52136, 0x3d4e86da, 0x3a1d783e, 0x3dae3e8b, 0xbe10b562, 0x3d636ff6, 0xbdc6ee2b, 0xba371269,
    0x3e4fa896, 0xbc7e5307, 0xbc573feb, 0x3c244d1f, 0xbd87a2f8, 0x3daf5787, 0xbc88e0e3, 0x3daa9f7f,
    0x3d142639, 0xbda6116c, 0xbd5232f1, 0x3d7b51b5, 0x3a83656a, 0xbd8c5fa6, 0xbbd0ba4f, 0x3daebb2b,
    0x3c4d9f3e, 0x3dcdb25d, 0xbcfda10e, 0xbcb42852, 0x3bae0af5, 0xbd8fb539, 0x3cb12ebb, 0x3ca79ec5,
    0xbb58b9d8, 0x3d2bf5fa, 0xbd4285de, 0x3d65ce12, 0xbdac03a6, 0xbc4aa6bb, 0xbbee4ff3, 0xbcc5389b,
    0xbcf1fc7c, 0x3d947c83, 0x3df32c6e, 0xbc9b9fed, 0xbdbbdaa9, 0xbd1ff5f3, 0xbd935317, 0x3d84445d,
    0xbdaa5533, 0x3a2dcca2, 0xbb073e73, 0xbe198cdc, 0xbd939c8e, 0x3dbede3d, 0x3d20eaed, 0xbd2ffe14,
    0xbd61848f, 0x3cc28609, 0xbd22b71b, 0xbdd42a89, 0x3ceb60ac, 0xbda7d5e5, 0xbd5220ab, 0xbd9a052a,
    0x3c504bea, 0x3df008b3, 0xbdcf4c54, 0x3e52f888, 0x3c8e3c1b, 0xbd1c98aa, 0xbd8c5ca8, 0x3d6f9fb8,
    0x3ddbd0d9, 0xbd18334a, 0xbe296a44, 0xbd95ed0a, 0x3dbefaeb, 0x3b60b8fb, 0xbddd82e5, 0x3e873ebf,
    0xbe74a9f5, 0x3d9115b7, 0x3d6cdde5, 0x3d833aa6, 0xbb990708, 0x3e15205c, 0x3e52c9ab, 0x3da6d579,
    0xbd3367af, 0xbb59411b, 0x3d17cd51, 0xbe211ae3, 0x3b4d124b, 0xbcc26ae5, 0xbd72af29, 0x3d009c8e,
    0x3cacd24f, 0x3d878d06, 0xbbb8eb94, 0xbd951323, 0x3d20956d, 0xbd266bcd, 0x3d9fb6a0, 0x3c98f9c3,
    0xbba677f5, 0xbdc349af, 0x3d27cb93, 0xbca26a4b, 0x3d763204, 0x3cc09646, 0xbca5b754, 0x3e0305fc,
    0xbcfc574b, 0xbd1f2b1a, 0x3d9a207b, 0xbdad35e7, 0xbd200c9c, 0x3e8c70f9, 0xbc37f52e, 0x3c9cfa73,
    0xbcad21b2, 0x3d9e102f, 0x3cf3010f, 0x3e0a7558, 0xbd4321cf, 0x3dbe8023, 0xbe57c7ba, 0x3c857066,
    0x3d72a525, 0x3d8bebe9, 0xbe0f5e1a, 0x3d51d341, 0xbd98619c, 0xbc94a623, 0x3d44dfc0, 0xbda3b496,
    0x3c8c2acc, 0xbd5d74d9, 0x3c660c5d, 0x3dddd188, 0xbd7c08f4, 0xbcb62334, 0xbc6186f9, 0x3e73f3e9,
    0xbdb4a417, 0x3c9a8ee2, 0xbdeb7a06, 0xbe038f78, 0xbd9c45c9, 0x3e419247, 0xbdbfa800, 0xbe462b9b,
    0xbceefdcc, 0xbbc81d14, 0xbc82efb2, 0xbc0e4781, 0xbcbeeaf7, 0x3dc8fe8b, 0xbd7b7d7b, 0xbd00f2bb,
    0x3d3a9da1, 0x3c8e64ab, 0x3bdf64ca, 0xbc196256, 0x3cc6a7a7, 0x3c378029, 0xbda5d846, 0x3dbadbbb,
    0x3bdef4b9, 0xbe13d2c1, 0xbd19af35, 0x3ddd8137, 0xbd14e0e3, 0x3db9c953, 0x3cf04db7, 0xbca2698e,
    0x3df08f16, 0xbdc34c62, 0xbdb8ea15, 0xbdb6c059, 0xbdd16007, 0xbd5a1bae, 0xbdb9e039, 0xbdd48fe4,
    0x3d0dec4e, 0x3d403c6d, 0x3d462703, 0xbcec3542, 0x3d48c9a8, 0x3c86b999, 0x3b73c656, 0xbd2f28cb,
    0xbd88065a, 0x3dc9b2a1, 0xbda44f59, 0xbe1a58d6, 0x3ddc9b52, 0xbda608eb, 0x3d24c08e, 0x3dac57a7,
    0x3df008ee, 0x3cd1e083, 0x3dfaf2f5, 0xbdcc80ff, 0x3d454b53, 0xbdee80e0, 0xbdadfe53, 0x3cccef6d,
    0xbd888a57, 0xbda555c3, 0xbdf5594c, 0xbd651748, 0x3d433910, 0x3d921b2f, 0x3d5edf5f, 0xbd79661e,
    0xbc952fde, 0x3c7aa24a, 0xbcf6c485, 0x3d7b6224, 0x3b1fd763, 0xbd81a7cf, 0xbb6656d2, 0x3dcdfef0,
    0x3bbe1213, 0x3c8312c6, 0xbdc2a9ea, 0xbc44e058, 0xbe4c37d5, 0xbcfec2ee, 0xbe0960bc, 0xbd515872,
    0xbd30a4bb, 0x3d18c8f1, 0xbd52c6fa, 0x3c3daf3b, 0xbccaa8c2, 0x3cb2d5ab, 0xbdaade92, 0x3d8a29ab,
    0x3ceafa43, 0x3db95280, 0xbc7fe4f5, 0x3d6340ff, 0x3db6218c, 0xbc81c2b6, 0x3cc2fff8, 0x3e10bf4f,
    0x3c60c812, 0x3d9cff2e, 0xbb5f3f74, 0xbe031f64, 0x3d0272ee, 0x3e15b335, 0x3dd69d89, 0xbe5e5c08,
    0xbdfcf2ce, 0xbdcc29b9, 0x3d2601b5, 0xbdbb7799, 0x3d62b7cc, 0xbc3b1f1d, 0xbb04062e, 0x3c831087,
    0x3d041695, 0x3e12fe9d, 0x3e15a157, 0xbd1bfbdd, 0xbdd4b09a, 0x3e069efa, 0xbccce197, 0xbd432bcc,
    0xbb8a2c8e, 0xbd421918, 0xbd802262, 0xbc389ac2, 0x3d9a2bf5, 0xbe039523, 0x3dade43b, 0x3d8011fb,
    0x3cf37a38, 0x3ca69540, 0x3d5cf31c, 0x3d4b7120, 0xbd5d7e7f, 0x3c0e1a02, 0x3ce682f4, 0xbccc3de4,
    0x3dbf5f0c, 0x3d13ebc2, 0xbcd9ed49, 0xbcbe63ae, 0x3b34c135, 0xbd5eb7d7, 0xbd2de120, 0x3d52d0fb,
    0xbd2fddae, 0x3d5c5adf, 0xbc472e61, 0x3ca9c1d3, 0x3d1b4dd5, 0xbd2a8f3d, 0xbcb34f50, 0xbd526450,
    0xbd50f9a6, 0xbd882113, 0xbd924f01, 0x3d23c417, 0x3df6d66d, 0xbe1ff924, 0xbda96f10, 0x3d021d62,
    0xbd4edf17, 0xbd13aeda, 0x3d19cfb8, 0x3e29bc5c, 0x3e4babc5, 0xbc04d5fe, 0x3d769429, 0x3db2f880,
    0xbd6bf5ae, 0xbc2f6101, 0xbdcfe59f, 0x3c863f63, 0xbd285ed8, 0x3c9ef984, 0xbd86270a, 0x3b353573,
    0x3dd5b0b2, 0xbd094db0, 0xbcbb6e66, 0x3d039d3d, 0x3ca87c69, 0xbd00682b, 0xbdbb064d, 0xbdd06e43,
    0xba3c55ce, 0x3e2278b8, 0xbdca01bc, 0x3e1ff785, 0x3d389700, 0xbe53834f, 0xbcee7c39, 0xbcb7d680,
    0xbd140c33, 0xbdce1307, 0x3c93f70c, 0x3bdeb0a1, 0x3dccd2a8, 0xbd807944, 0xbd74cf60, 0x3d88fdf3,
    0xbd17ca25, 0x3d76ad6c, 0x3d821b28, 0xbd75f3ea, 0xbdd098f4, 0x3d8ebd2d, 0xbdc3cf7b, 0xbd388c41,
    0x3d5792f3, 0xbdfd274a, 0x3cabfc6d, 0x3d8ef318, 0x3dbde5af, 0x3dc15a70, 0x3bbb7ce9, 0xbd61849a,
    0x3cbcb326, 0x3baa2186, 0x3d82b12e, 0xbd315782, 0xbc996a76, 0xbc9fed5f, 0xbba01406, 0x3e06b034,
    0xbcf9a8d8, 0xbd8ecf89, 0xbbdf8a9e, 0x3dde9938, 0x3cb1bac8, 0x3def8dae, 0x3d432568, 0xbd0b7349,
    0xbd77914f, 0x3d8e94a0, 0x3dd59cc6, 0x3b2a46dd, 0x3d3ad5c3, 0xbc88c103, 0xbe004e30, 0xbd8667a8,
    0x3d3c5aba, 0xbd513fdf, 0xbd87f315, 0x3d246619, 0x3c8da53b, 0x3de0dc5a, 0x3d49b613, 0xb993caf1,
    0x3d929d8e, 0xbd2ca1b4, 0xbcc7bfe9, 0x3d1ad03a, 0xbd0d0a12, 0xbd9a0ede, 0xbc83f424, 0x3a9ad5e3,
    0x3d873aac, 0x3b350c23, 0x3d590416, 0x3d24e9ae, 0xbcce6ecf, 0xbc845bcc, 0xbcea89bd, 0x3d9b58c5,
    0xbcbc906e, 0x3dc0ff60, 0xbd82c7f1, 0xbd5985fb, 0x3d87130a, 0xbd165e2b, 0xbdac2cde, 0xbd52c7b9,
    0xbd51d979, 0xbb5289b2, 0x3afe3c16, 0x3c298130, 0xbc478023, 0xbc3a733e, 0xbb6d160e, 0xbb42f89d,
    0xbd4ce4aa, 0xbd3cde04, 0xbdaae013, 0xbdca5a3f, 0x3cb17924, 0x3d549481, 0x3d90bfdd, 0xbd1ad31a,
    0x3ddbb940, 0xbe02acce, 0x3d98389b, 0x3dbb7730, 0x3d40d99d, 0x3e443e22, 0x3d81bf77, 0x3cda2aaa,
    0xbd8198ff, 0x3d8ce3ff, 0xbd0d2cb0, 0xbdc43e1c, 0x3d569845, 0x3d8d07d3, 0xbd2f6593, 0x3bd5af77,
    0xbe20a434, 0x3d747a5c, 0xbc06435b, 0xbd5e7e83, 0x3e0bb954, 0x3c4637cc, 0x3c955d32, 0xbe185a01,
    0x3dc904c0, 0x3e2334bf, 0xbd0d1af0, 0xbd51e0b2, 0x3cafdd7e, 0x3bd68bae, 0xbd82317c, 0x3d27353e,
    0xbc323b9a, 0xbcf1ffaf, 0x3c428caa, 0xbd0daa35, 0xbc97e66c, 0xbba1c38b, 0x3d7f7e5c, 0xbd5e441a,
    0x3ce713b5, 0xbdf5f6f0, 0x3d8b3a7b, 0xbda3f2c2, 0xbccdd315, 0xbdb2e7eb, 0xbd4e012e, 0x3e066dc3,
    0x39546cfa, 0x3bab10e5, 0xbd3a881e, 0x3d1931c3, 0x3dab7930, 0xbaab38d1, 0x3c8a80e9, 0x3c8e53f0,
    0x3d597f76, 0xbd827e80, 0x3d079af1, 0x3d021dbf, 0x3d8ca2fb, 0xbd70fb6a, 0x3af2759a, 0x3d3260c2,
    0xbdc2c740, 0x3dbd0a61, 0xbcf72c19, 0xbe1efa1d, 0x3b6d2a49, 0x3e0188ad, 0x3cdb098c, 0xbdc5207b,
    0xbe015142, 0xbcd09006, 0x3dab3770, 0xbd6b8978, 0xbdeafd77, 0x3d46efe9, 0x3ccc674e, 0xbd36e87c,
    0x3b7c9f7e, 0x3d9bb324, 0x3cf964fc, 0xbca3dab9, 0x3d1f3970, 0x3db2a6b3, 0x3d65eb65, 0x3d92fe54,
    0x3d011173, 0xbe0c1d29, 0x3dbe42d4, 0xbae9677c, 0x3c2dfec7, 0x3d50cf53, 0x3d95182c, 0x3da95c87,
    0xbdeb7db8, 0xbd5b19db, 0xbc5c8a0c, 0xbc9270a4, 0x3dba979c, 0x3e42b101, 0xbcae2927, 0xbcffdd1f,
    0x3d3e6bfd, 0x3d085e1e, 0xbd9ad1bd, 0xbdbf81b6, 0xbd3fa315, 0x3d405e02, 0xbde31d21, 0x3d4319d9,
    0xbc34be44, 0xbddc87e8, 0xbd15afba, 0x3d885533, 0xbd80b721, 0x3d772ee3, 0x3d417656, 0x3c7bbf91,
    0x3da9353e, 0xbddbc252, 0xbe0ab2e8, 0xbdedc8ea, 0xbd980c3d, 0xbd48633c, 0xbdf82086, 0xbe64e7b1,
    0x3d012ba7, 0x3ddc7965, 0xbd8c172d, 0xbd0d156c, 0xbcae6e0b, 0x3c2e3357, 0xbc661c14, 0x3bc3a2fa,
    0xbc946852, 0x3dc728ce, 0xbe1d3542, 0xbd82a1d3, 0x3dd4e8e4, 0xbb362cde, 0x3c9f80a8, 0x3dbd8704,
    0x3e0cadb0, 0x3cacf8b4, 0x3d616da1, 0xbd1abbb8, 0xbc6d55ed, 0xbb365bed, 0xbd420c0a, 0x3d30dd53,
    0xbe1cc66f, 0x3d760730, 0xbdfca4af, 0xbd2c04ed, 0x3c1f6bc9, 0x3da58562, 0x3d85ef8c, 0xbc866f60,
    0x3cb9725f, 0xbd033327, 0x3c198d52, 0xbd2d1fe1, 0x3b6651de, 0xbd37dcbf, 0xbca2ed0e, 0x3d316117,
    0x3c8e80da, 0xbcc2600b, 0xbca0633c, 0xbca32d7c, 0xbe8082ee, 0xbcf6eb0f, 0xbcff1d91, 0x3b1c3e6f,
    0xbd78974e, 0x3e5cc6d3, 0xbd7bcc07, 0x3b81971f, 0x3e0b1386, 0x3cc8f7fd, 0xbd810421, 0x3d118623,
    0x3cbda10b, 0xbc894641, 0x3ca14062, 0x3d22ae9b, 0x3d8e607d, 0xbd1ae01f, 0x3d968682, 0x3e0d0114,
    0xbdac82ff, 0x3d8e587b, 0xbca40f8b, 0xbca9d422, 0x3d4f24d6, 0x3ca2c0ae, 0xbdc0f8bc, 0xbdca88a9,
    0x3c2a0ec5, 0x3cef7b34, 0xbd040d0b, 0xbd148a2c, 0x3d3fa32f, 0xbcfe53aa, 0xbc87d13b, 0x3b89d18d,
    0xbd45fa08, 0x3d18f111, 0xbd853597, 0x3d3e169b, 0x3db38b4c, 0x3cbc5a3d, 0x3d546355, 0x3d38ce51,
    0x3cfc5381, 0xbe351426, 0xbdb426bb, 0x3dd51169, 0x3d49d828, 0xbd9633b2, 0x3b9d28e3, 0x3dbf1a85,
    0x3c184205, 0xbd1311ff, 0x3bbc5fe0, 0x3e094686, 0x3d6e5778, 0xbd03aff3, 0xbd873fd8, 0xbd98523f,
    0xbdbfe0c2, 0x3cd7e140, 0x3d021a85, 0xbd87adbe, 0xbc397e0e, 0x3dd1691a, 0xbc7ec445, 0xbdd96bc7,
    0xbd235e3d, 0x3d432ced, 0x3c8cb25e, 0x3e010098, 0xbb8b823c, 0x3d1e0b26, 0x3d32e70f, 0x3b8fc84a,
    0xbcf15e4f, 0xbd022f7e, 0x3b9eef3f, 0x3dd58e6f, 0xbce3ab56, 0xbd2ea6e8, 0xbd8ed752, 0x3d45d4ce,
    0x3de531b7, 0x3c8228e3, 0x3da5fc37, 0x3e3eaa96, 0x3e1b92b8, 0xbd4c6f76, 0xbd212a77, 0x3db0be75,
    0x3ceff381, 0x3cf8ba12, 0xbd87e66f, 0x3dbd41a5, 0x3dc0d83d, 0xbd09234e, 0xbcefefd3, 0xbdc477db,
    0x3d1840e2, 0xbb82cdb3, 0xbd5baff2, 0x3dac3565, 0x3d145bde, 0xbcaa44f4, 0x3d063212, 0xbcf0917f,
    0xbd85224b, 0x3c0e41fc, 0xbdb0986f, 0x3d3345f6, 0xbd57035c, 0xbd1841da, 0xbbdff1c4, 0xbd5b5b41,
    0xbd8c6ac5, 0x3c67e4d2, 0xbc5810ce, 0xbdd92652, 0x3cd08d24, 0xbd391540, 0xbcba30f6, 0xbc0a3210,
    0xbd18219f, 0xbd400a9a, 0xbd6aadba, 0x3d956d49, 0x3d8c9ae7, 0xbcd95cc4, 0xbca5266b, 0x3d4b4b0f,
    0x3df02f1b, 0xbd3ace03, 0xbd1bf04d, 0xbcd6722c, 0x3c86132f, 0xbabfb11e, 0x3c9f1070, 0xbc503ee8,
    0xbda6112c, 0x3ce0d477, 0x3c2bc344, 0x3cb5d66f, 0xbd1a4629, 0x3dd844c2, 0x3d6548c8, 0x3d6ab3a3,
    0xbcdaff62, 0x3dc720ec, 0x3bf68a88, 0x3c852ece, 0xbcf35055, 0xbc81ff51, 0xbd567bbe, 0x3cce6257,
    0x3cca0c8e, 0x3d180218, 0xbd693021, 0x3ceb03f9, 0x3d26f47c, 0xbd242d91, 0xbb979a5e, 0x3ce3d788,
    0x3d8a138c, 0xbd60b4cc, 0xbb90859b, 0xbcb2e410, 0xbbfc3b9a, 0xbd996357, 0x3b320a12, 0x3d322299,
    0xbd402ded, 0xbc244579, 0xbccaf9fe, 0xbdaec9c6, 0xbcbc028b, 0x3dfa5e18, 0x3cbabef3, 0xbd691b8b,
    0x3d6ee65d, 0x3ca7bddb, 0xbd51ee6f, 0x3d01dfc2, 0xbd380615, 0xbd878b45, 0xbd072698, 0x3da89ea4,
    0x3d83d8d4, 0x3df11351, 0xbccd4978, 0xbc1d0e20, 0x3d5a6a73, 0x3c03addf, 0xbd929cd3, 0xbcd0b600,
    0x3b666df7, 0xbc1ca31f, 0x3d592b82, 0xbd12fc97, 0xbd25b455, 0xbd68a868, 0xbb2bbf89, 0x3badd1b3,
    0xbd83fa51, 0xbc25cf66, 0xbd037401, 0xbdde90e5, 0xbd895e29, 0x3ddd1bc2, 0x3ca0ed7a, 0xbdfd76c6,
    0x3d699895, 0xbc6b7a46, 0xbd21f6e9, 0x3ab85b1f, 0x3ce6b6a5, 0xbd2a7093, 0xbd0d01dc, 0x3e00865f,
    0xbe2b1eb6, 0xbe3901b9, 0x3d83b154, 0x3c8b22ce, 0xbdb6b03c, 0xbd26dee7, 0x3e2ac852, 0xbdaf8633,
    0x3e0c90c8, 0xbc0346f5, 0x3e0d070d, 0xbdafe005, 0x3d580756, 0xbca4c4f3, 0xbdb16110, 0xbd7dc621,
    0xbd93d6fa, 0x3e2a010d, 0x3dbe978a, 0x3c874b51, 0x3de0baf2, 0x3d8d44e6, 0x3d20986b, 0x3d533a46,
    0x3d192dbe, 0x3d0cd99f, 0xbca02d52, 0x3c5c2838, 0xbe1c63d5, 0xbe17db39, 0xbd607535, 0x3e0df01d,
    0xbcf0db93, 0xbdb029e4, 0x3bd11226, 0xbd725e56, 0xbdb97f7a, 0x3b2a0423, 0x3e267b33, 0xbd140e3f,
    0xbd4695d5, 0x3d9beb2c, 0x3cc2a899, 0x3d0eded5, 0xbdcda8f2, 0x3d84f53c, 0x3cb07bb8, 0xbcb2cc32,
    0xbd1cbf58, 0xbc86142d, 0x3c93a2db, 0x3da294bc, 0x3da8715e, 0xbb00eda1, 0x3d327821, 0xbcb0d4af,
    0x3ddd81ce, 0xbcff84f3, 0x3d99f1c0, 0x3d14738d, 0x3d8cc4c8, 0x3a7a8333, 0xbd9b2d01, 0x3d2c6957,
    0x3d09d481, 0xbd6288ba, 0x3d899ad5, 0x3caf8cdb, 0x3dc895eb, 0xbc491797, 0xbd38b0f0, 0xbcf6d7b0,
    0x3db1713a, 0x3c07be1b, 0x3c3f0517, 0x3ccca777, 0x3db6705a, 0x3d723b32, 0xbd22da11, 0xbce07f16,
    0xbdbe1cae, 0x3dfc9d06, 0x3dc06a92, 0x3d51eb85, 0x3d1c57bf, 0x3cef621f, 0xbcee0475, 0x3d0ff0bb,
    0x3d1c00fb, 0x3b58ec2d, 0x3c2dfb0b, 0x3d114204, 0xbd7420ef, 0x3dc71af7, 0xbbd160d7, 0xbd70c21b,
    0xbd36da05, 0xbd7f5360, 0xbb980cb2, 0xbd29a357, 0xba01c0e1, 0xbd83c991, 0x3c671c7c, 0x3d821d6d,
    0xbd9ecbe8, 0x3d5041e7, 0x3de2f1fd, 0xbdb2e918, 0x3bc65c54, 0xbdae2af9, 0xbdcd28aa, 0x3ccce91c,
    0xbcd83137, 0x3d4aeeee, 0xbc7f8dd7, 0x3c3e2ce3, 0x3e0c37d0, 0x3d5e1495, 0x3de256e7, 0x3d3ed269,
    0x3d21acaf, 0xbbf2f50c, 0xbbf21c0d, 0xbdf7dc39, 0x3c83922f, 0xbdef8f36, 0x3d7c822e, 0x3dd0b1db,
    0x3dfce017, 0xbd81fe73, 0xbdb2220c, 0x3b57614a, 0x3d770a6c, 0xbbb76bd7, 0x3d7a66c0, 0xbcd71955,
    0xbc52df56, 0x3d5501ee, 0x3c7b26b4, 0xbda38503, 0x3da7bcb9, 0xbdc2ad43, 0xbe1450b9, 0x3d91b9a4,
    0xbd5ccea0, 0xbda3622f, 0xbcbec94a, 0xbd64b0bb, 0x3d0671e7, 0x3d73e06a, 0xbce25df0, 0xbddefe23,
    0xbddcaf4c, 0xbd368da7, 0xbe13b0ce, 0x3b8cb48c, 0xbd61d056, 0x3dc21b6f, 0x3da6808e, 0x3a19addd,
    0xbdaab30c, 0xbe004c0a, 0xbdd9a848, 0xbe1b9f2f, 0xbdc580c6, 0x3d03c2c8, 0x3d11ae73, 0x3d7100d7,
    0x3d87fa09, 0xbd54954f, 0x3d7a92f0, 0xbe02fc64, 0xbda33514, 0xbb87d3c6, 0xbe471383, 0xbbc823f7,
    0xbd2170f1, 0x3d414611, 0xbe148c7a, 0x3d6dcc43, 0x3d26b17b, 0xbafff6c3, 0x3d77e2ef, 0xbd4334f9,
    0xbd73250e, 0x3d84d0ec, 0x3c425464, 0xbdad2747, 0xbcc74e50, 0x3d81d982, 0x3da73880, 0xbdb088ad,
    0x3c403b28, 0xbd3a3b77, 0xbe0badba, 0x3e0f5fd0, 0x3cb7e5a9, 0x3a4803e0, 0x3dd8fc5a, 0x3db848dc,
    0x3b3ed87e, 0x3d6928fe, 0xbd63f50d, 0xbdf24a57, 0x3d9562f6, 0xbe2a56f6, 0xbdcdb1d7, 0x3d9cc07a,
    0xbdb38b33, 0x3da7e60c, 0xbdb5606b, 0x3d0e8df3, 0x3e179127, 0xbd20b51c, 0x3d8930e6, 0x3d844aba,
    0x3d5cd906, 0xbcd621f9, 0xbd96b25f, 0xbd4250b1, 0xbd846801, 0x3c18e40f, 0x3c1dcf1f, 0x3d2cdc99,
    0xbcb6e7ad, 0xbd055dde, 0xbcf8c03a, 0xbdd0d057, 0xbd0a1610, 0xbcd9e457, 0xbc8ad0c8, 0x3db3bb5b,
    0xbe29b422, 0x3d038274, 0x3de4eea0, 0xbda7ff3c, 0x3c31b32e, 0x3da13438, 0xbe04a7d1, 0xbd7c59ad,
    0x3c808e20, 0xbc53a4dc, 0xbcc77d83, 0xbdf6b80f, 0x3d79f0c0, 0x3d8155aa, 0x3c056046, 0x3caa05bc,
    0xbd94b79c, 0x3d602041, 0xbd8abc1c, 0x3c8646cc, 0x3e21836c, 0x3cd9f9fd, 0x3d91ca11, 0x3cf6a72b,
    0x3b88e79f, 0xbcf96bbd, 0xbdc111b1, 0x3d93afce, 0xbc894474, 0xbc9e5af1, 0x3d720f1e, 0xbcb0d7b2,
    0x3e231a14, 0x3d0e1699, 0x3d9188cb, 0x3d0c08fb, 0xbc6a48b2, 0xbd9c05bb, 0xbda80a46, 0x3d309e10,
    0xbdb37465, 0xbd6963ce, 0xbe1b93aa, 0x3ded97b7, 0x3d910e4f, 0xbc007007, 0xbca76264, 0xbd90ba76,
    0x3de45474, 0x3d9c6093, 0x3d6bdb1e, 0x3d4b0686, 0xbc99d382, 0x3d08567b, 0x3dc24a74, 0xbe2d9833,
    0xbda3be86, 0x3ad52812, 0x3d80eaa8, 0xbcc1afa7, 0xbcf2e084, 0x3d9bc5f3, 0xbd6b6a21, 0x3c8ee3ce,
    0xbc8cf091, 0x3da2b34d, 0x3e2b411b, 0x3cca8f20, 0xbc136236, 0x3d1a478d, 0xbda962c8, 0x3d833083,
    0xbdd40964, 0x3d80f3bd, 0x3dd3e84b, 0xbd914119, 0x3d117ccf, 0xbd11daab, 0x3cdb078a, 0x3cbafb49,
    0x3c64475e, 0xbc033da1, 0xbc8b52b7, 0xbdc5ee87, 0x3a265394, 0xbcb4d42d, 0xbd87c00e, 0x3dcca925,
    0x3cff3d15, 0x3d11e282, 0xbe1455e3, 0x3e0e2ed3, 0x3df547ae, 0xbcf5dcf1, 0x3b15124f, 0x3c0ba0da,
    0xbe19701b, 0x3d69e48c, 0xbb839761, 0xbd5bb90f, 0xbc78bb92, 0xbded51a2, 0xbdd456c1, 0xbd7d1178,
    0x3c4569c6, 0xbc84978c, 0xbe0b7611, 0x3c5a2477, 0x3cea8bda, 0x3db427c9, 0xbd409bb8, 0xbd3afd85,
    0xbdcc504f, 0xbdcff13f, 0x3c409694, 0xbda387a9, 0x3dcd9385, 0x3c697d48, 0x3dfe422a, 0x3d4469bd,
    0xbc6a6d0d, 0xbd793951, 0xbdba5133, 0xbbea7acb, 0xbe4c87e2, 0x3d0cd4ec, 0x3cfdce6f, 0x3de0e35b,
    0x3db24080, 0x3de1de32, 0x3d53a65d, 0xbe1a199d, 0xbd02adb0, 0x3dee0eee, 0xbe2a49df, 0xbd59c050,
    0xbdc43466, 0x3e0279bd, 0x3cf44ecb, 0x3d26bf57, 0x3cda4c89, 0xbdbf089e, 0x3dbb9b57, 0x3d2b7cc0,
    0xbddb0b10, 0x3e0a7575, 0xbc7caa84, 0xbcbed7ff, 0xbce0c1fd, 0x3ca7850e, 0xbd4cef8a, 0xbe0c0203,
    0x3e1d1526, 0x3dc27ec0, 0x3c1e440a, 0x3e43be2c, 0x3cea724c, 0xbbed61b3, 0xbd2da676, 0x3de690c0,
    0x3ad9a87a, 0x3d981235, 0xbd092af0, 0xbdcc0e03, 0x3d182e5c, 0xbc9a6001, 0x3d1f8d3d, 0x3dfb3f46,
    0xbd8f9a50, 0x3d9e212c, 0x3ca18bd9, 0x3d9e52f5, 0x3d4a397c, 0x3d205b08, 0x3e0e9cc4, 0x3e30da4f,
    0x3d109eb5, 0x3d217795, 0x3d26bc5b, 0xbddb85e1, 0x3c11494d, 0x3cb9aeb3, 0x3cad67e2, 0x3de47015,
    0x3d18d263, 0x3dbd25b1, 0xbd6a7e28, 0xbd2c6a67, 0x3d9cba60, 0x3c6f8ff6, 0x3cd3d1f8, 0x3e40b51c,
    0xbc35e095, 0x3d032514, 0x3d53464c, 0xbdfa013a, 0x3dc57141, 0xbc26c64d, 0xbcf13afd, 0x3d9f67a7,
    0xbde52e81, 0x3c573a16, 0x3d2db14c, 0xbe08b4c9, 0x3b62697c, 0x3d47b646, 0x3b637a8a, 0x394cabe9,
    0xbd7434dd, 0xb9f87e22, 0xbd99cc87, 0x3d85956b, 0xbd41bbcd, 0x3e6f300c, 0xbc998672, 0x3d24d53d,
    0xbcb95d43, 0xbcdadd16, 0xbe80e96d, 0xbd44b0c6, 0xbdad9721, 0x3d61ac51, 0x3d877248, 0xbceb14e4,
    0x3dfd5634, 0x3b03f7bf, 0xbd78d6ab, 0xbd847f29, 0xbd2eaa15, 0x3dc14431, 0xbdfd9d8d, 0x3d816db2,
    0xbe08865d, 0x3b796554, 0xbe049ff9, 0x3d51c7ed, 0x3ca6cf0f, 0x3dc1b494, 0xbe0c9ade, 0xbde68b22
};

static const uint32_t _K43[] = {
    0x3f881ae7, 0xbf0b7999, 0x3f5b18cd, 0x3f11fd17, 0xbf1efd38, 0x3f33a3a5, 0xbf33eab5, 0x3ccd6d2a,
    0x3e3981bf, 0x3fac50ad, 0x3efa3b00, 0xbf2fa0cb, 0xbfb27f71, 0x3fdfbb44, 0x3fa10826, 0x3f2c17a7,
    0xbef4cf6a, 0x3d42b798, 0x3edfe214, 0x402d4b0e, 0x3c93740c, 0xbfffa2ee, 0xbfbcdf22, 0xbf99f492,
    0x3e9ab3db, 0xc02d8ff9, 0x3fe84cc0, 0xbee7eb3b, 0x3f7de5ec, 0x3f289ec4, 0x3f6e5624, 0x3fabb9e0
};

static const uint32_t _K49[] = {
    0x3ea1a903, 0x3f254a06, 0x3f1869f5, 0xbe7a9565, 0x3dae1082, 0xbeaba66e, 0xbeb85a97, 0x3e4adf2f,
    0xbeadf149, 0xbf1e9343, 0x3ed12de0, 0xbf1f0bb3, 0x3eeb21f5, 0x3eaf36ec, 0x3eac50a1, 0xbe6bae8a,
    0x3d46a65b, 0x3f0e4aba, 0xbea2c357, 0x3e69219b, 0xbeb9c451, 0x3f3cfc0a, 0xbdc2a180, 0xbd7acbc8,
    0xbec47b14, 0x3d8001c0, 0xbd22489a, 0x3e4b5fba, 0x3edb152d, 0x3f478312, 0x3f39186e, 0x3f061e33,
    0xbea4dbc1, 0xbf70d9db, 0xbf12acfc, 0xbe518ef9, 0xbf514a54, 0x3f00eed6, 0x3f10c1fd, 0xbb120748,
    0x3ede9a0e, 0x3f172b24, 0xbf39f63b, 0x3e8499ec, 0xbf690d40, 0x3eae1f69, 0x3e450fa9, 0x3e6255c7,
    0xbf5a8878, 0xbf4cdf81, 0x3f0f34f1, 0x3e4b15d6, 0xbf170472, 0xbf005b14, 0xbdbe2519, 0x3f0b295f,
    0xbe95c709, 0xbed0baa1, 0x3eaec6b0, 0xbef416bb, 0x3dfca977, 0xbd4b3e40, 0xbee4d957, 0x3dc8b5cf,
    0xbed8ca19, 0x3d7e8068, 0xbf443cf9, 0x3f4aa9ee, 0x3f13a993, 0x3e661c87, 0xbe623609, 0x3f172190,
    0xbe9a36ad, 0x3f0a3bac, 0xbf27b606, 0xbe425aa8, 0x3f04430d, 0xbf89f412, 0xbf497cf2, 0xbe72ca0f,
    0x3ea1ac2d, 0xbf36e9e4, 0xbed9759b, 0xbf9ab00c, 0x3f34ecae, 0x3dee64f4, 0xbf0662ab, 0xbdf9e198,
    0x3ee43e3b, 0xbf19de2e, 0xbf084b97, 0x3f086744, 0xbf497556, 0xbefe8203, 0xbea27248, 0xbf8feb6e
};

static const uint32_t _K51[] = {
    0xbdfc136d, 0x3cd8422a, 0x3deedb5b
};

// Memory mapped buffers
#define _K18             ((int16_t *)_K18)                   // s16[42] (84 bytes)
#define _K25             ((float *)_K25)                     // f32[12,3,40] (5760 bytes)
#define _K27             ((float *)_K27)                     // f32[12] (48 bytes)
#define _K30             ((float *)_K30)                     // f32[24,3,12] (3456 bytes)
#define _K32             ((float *)_K32)                     // f32[24,3,24] (6912 bytes)
#define _K34             ((float *)_K34)                     // f32[24] (96 bytes)
#define _K39             ((float *)_K39)                     // f32[32,3,24] (9216 bytes)
#define _K41             ((float *)_K41)                     // f32[32,3,32] (12288 bytes)
#define _K43             ((float *)_K43)                     // f32[32] (128 bytes)
#define _K49             ((float *)_K49)                     // f32[3,32] (384 bytes)
#define _K51             ((float *)_K51)                     // f32[3] (12 bytes)
#define _K6              ((float *)_K6)                      // f32[512] (2048 bytes)
#define _K13             ((int32_t *)(_state + 0x000028e0))  // s32[24] (96 bytes)
#define _K14             ((float *)(_state + 0x00002940))    // f32[258] (1032 bytes)
#define _K2              ((int8_t *)(_state + 0x00000000))   // s8[2256] (2256 bytes)
#define _K5              ((int8_t *)(_state + 0x000008d0))   // s8[8208] (8208 bytes)
#define _K1              ((float *)(_buffer + 0x00000000))   // f32[512] (2048 bytes)
#define _K10             ((float *)(_buffer + 0x00000800))   // f32[512] (2048 bytes)
#define _K11             ((float *)(_buffer + 0x00001000))   // f32[257,2] (2056 bytes)
#define _K15             ((float *)(_buffer + 0x00001808))   // f32[1026] (4104 bytes)
#define _K17             ((float *)(_buffer + 0x00000000))   // f32[257] (1028 bytes)
#define _K22             ((float *)(_buffer + 0x00000404))   // f32[40] (160 bytes)
#define _K23             ((float *)(_buffer + 0x00000000))   // f32[40] (160 bytes)
#define _K24             ((float *)(_buffer + 0x000000a0))   // f32[40] (160 bytes)
#define _K26             ((float *)(_buffer + 0x00001f40))   // f32[25,12] (1200 bytes)
#define _K28             ((float *)(_buffer + 0x00000000))   // f32[25,12] (1200 bytes)
#define _K29             ((float *)(_buffer + 0x000004b0))   // f32[25,12] (1200 bytes)
#define _K3              ((float *)(_buffer + 0x00000000))   // f32[40] (160 bytes)
#define _K31             ((float *)(_buffer + 0x00000960))   // f32[25,24] (2400 bytes)
#define _K33             ((float *)(_buffer + 0x00000000))   // f32[25,24] (2400 bytes)
#define _K35             ((float *)(_buffer + 0x00000960))   // f32[25,24] (2400 bytes)
#define _K36             ((float *)(_buffer + 0x00000000))   // f32[25,24] (2400 bytes)
#define _K38             ((float *)(_buffer + 0x00000960))   // f32[12,24] (1152 bytes)
#define _K4              ((float *)(_buffer + 0x00000000))   // f32[50,40] (8000 bytes)
#define _K40             ((float *)(_buffer + 0x00000000))   // f32[12,32] (1536 bytes)
#define _K42             ((float *)(_buffer + 0x00000600))   // f32[12,32] (1536 bytes)
#define _K44             ((float *)(_buffer + 0x00000000))   // f32[12,32] (1536 bytes)
#define _K45             ((float *)(_buffer + 0x00000600))   // f32[12,32] (1536 bytes)
#define _K47             ((float *)(_buffer + 0x00000000))   // f32[6,32] (768 bytes)
#define _K48             ((float *)(_buffer + 0x00000300))   // f32[32] (128 bytes)
#define _K50             ((float *)(_buffer + 0x00000000))   // f32[3] (12 bytes)
#define _K52             ((float *)(_buffer + 0x0000000c))   // f32[3] (12 bytes)

#define IPWIN_RET_SUCCESS 0
#define IPWIN_RET_NODATA -1
#define IPWIN_RET_ERROR -2
#define IPWIN_RET_STREAMEND -3

// Represents a Circular Buffer
// https://en.wikipedia.org/wiki/Circular_buffer
typedef struct
{
    char* buf;
    int size;		// total bytes allocated in *buf
    int used;		// current bytes used in buffer.
    int read;
    int write;
} cbuffer_t;

#define CBUFFER_SUCCESS 0
#define CBUFFER_NOMEM -1

// Initializes a cbuffer handle with given memory and size.
static inline void cbuffer_init(cbuffer_t* dest, void* mem, int size) {
    dest->buf = mem;
    dest->size = size;
    dest->used = 0;
    dest->read = 0;
    dest->write = 0;
}

// Returns the number of free bytes in buffer.
static inline int cbuffer_get_free(cbuffer_t* buf) {
    return buf->size - buf->used;
}

// Returns the number of used bytes in buffer.
static inline int cbuffer_get_used(cbuffer_t* buf) {
    return buf->used;
}

// Writes given data to buffer.
// Returns CBUFFER_SUCCESS or CBUFFER_NOMEM if out of memory.
static inline int cbuffer_enqueue(cbuffer_t* buf, const void* data, int data_size) {
    int free = cbuffer_get_free(buf);

    // Out of memory?
    if (free < data_size)
        return CBUFFER_NOMEM;

    // Is the data split in the end?
    if (buf->write + data_size > buf->size) {
        int first_size = buf->size - buf->write;
        memcpy(buf->buf + buf->write, data, first_size);
        memcpy(buf->buf, ((char*)data) + first_size, data_size - first_size);
    }
    else {
        memcpy(buf->buf + buf->write, data, data_size);
    }
    buf->write += data_size;
    if (buf->write >= buf->size)
        buf->write -= buf->size;

    buf->used += data_size;
    return CBUFFER_SUCCESS;
}

// Advances the read pointer by given count.
// Returns CBUFFER_SUCCESS on success or CBUFFER_NOMEM if count is more than available data
static inline int cbuffer_advance(cbuffer_t* buf, int count) {
    int used = cbuffer_get_used(buf);

    if (count > used)
        return CBUFFER_NOMEM;

    buf->read += count;
    if (buf->read >= buf->size)
        buf->read -= buf->size;

    // Reset pointers to 0 if buffer is empty in order to avoid unwanted wrapps.
    if (buf->read == buf->write) {
        buf->read = 0;
        buf->write = 0;
    }

    buf->used -= count;
    return CBUFFER_SUCCESS;
}

// Reset instance (clear buffer)
static inline void cbuffer_reset(cbuffer_t* buf) {
    buf->read = 0;
    buf->write = 0;
    buf->used = 0;
}

// Copies given "count" bytes to the "dst" buffer without advancing the buffer read offset.
// Returns CBUFFER_SUCCESS on success or CBUFFER_NOMEM if count is more than available data.
static inline int cbuffer_copyto(cbuffer_t* buf, void* dst, int count, int offset) {

    if (count > cbuffer_get_used(buf))
        return CBUFFER_NOMEM;

    int a0 = buf->read + offset;
    if (a0 >= buf->size)
        a0 -= buf->size;

    int c0 = count;
    if (a0 + c0 > buf->size)
        c0 = buf->size - a0;

    memcpy(dst, buf->buf + a0, c0);

    int c1 = count - c0;

    if (c1 > 0)
        memcpy(((char*)dst) + c0, buf->buf, c1);

    return CBUFFER_SUCCESS;
}

// Returns a read pointer at given offset and  
// updates *can_read_bytes (if not NULL) with the number of bytes that can be read.
// 
// Note! Byte count written to can_read_bytes can be less than what cbuffer_get_used() returns.
// This happens when the read has to be split in two since it's a circular buffer.
static inline void* cbuffer_readptr(cbuffer_t* buf, int offset, int* can_read_bytes)
{
    int a0 = buf->read + offset;
    if (a0 >= buf->size)
        a0 -= buf->size;
    if (can_read_bytes != NULL)
    {
        int c0 = buf->used;
        if (a0 + c0 > buf->size)
            c0 = buf->size - a0;

        *can_read_bytes = c0;
    }
    return buf->buf + a0;
}

typedef struct {
    cbuffer_t data_buffer;			// Circular Buffer for features
    int input_size;					// Number of bytes in each input chunk
} fixwin_t;

#ifdef _MSC_VER
static_assert(sizeof(fixwin_t) <= 64, "Data structure 'fixwin_t' is too big");
#endif

/*
* Try to dequeue a window.
*
* @param handle Pointer to an initialized handle.
* @param dst Pointer where to write window.
* @param stride_count Number of items (of size handle->input_size) to stride window.
* @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1) is no data is available.
*/
static inline int fixwin_dequeue(void* restrict handle, void* restrict dst, int count, int stride_count)
{
    fixwin_t* fep = (fixwin_t*)handle;

    const int stride_bytes = stride_count * fep->input_size;
    const int size = count * fep->input_size;
    if (cbuffer_get_used(&fep->data_buffer) >= size) {
        if (cbuffer_copyto(&fep->data_buffer, dst, size, 0) != 0)
            return IPWIN_RET_ERROR;

        if (cbuffer_advance(&fep->data_buffer, stride_bytes) != 0)
            return IPWIN_RET_ERROR;

        return IPWIN_RET_SUCCESS;
    }
    return IPWIN_RET_NODATA;
}

// input array (any shape >= 1D)
// output array (same shape as input array)
// d0 = input.shape.step(axis)
// d1 = input.shape.size(axis)
// d2 = input.shape.slot(axis)
static inline void hammingmul_f32(const float* restrict input, const float* restrict w, int d0, int d1, int d2, float* restrict output)
{
    const int d3 = d0 * d1;

    const float* ip = input;
    float* op = output;

    for (int j = 0; j < d2; j++) {
        for (int i = 0; i < d0; i++) {
            for (int k = 0; k < d1; k++) {
                op[k * d0 + i] = ip[k * d0 + i] * w[k];
            }
        }

        ip += d3;
        op += d3;
    }
}

static void makeipt(int nw, int* ip)
{
    int j, l, m, m2, p, q;

    ip[2] = 0;
    ip[3] = 16;
    m = 2;
    for (l = nw; l > 32; l >>= 2) {
        m2 = m << 1;
        q = m2 << 3;
        for (j = m; j < m2; j++) {
            p = ip[j] << 2;
            ip[m + j] = p;
            ip[m2 + j] = p + q;
        }
        m = m2;
    }
}

static void makewt(int nw, int* ip, float* w)
{
    void makeipt(int nw, int* ip);
    int j, nwh, nw0, nw1;
    float delta, wn4r, wk1r, wk1i, wk3r, wk3i;

    ip[0] = nw;
    ip[1] = 1;
    if (nw > 2) {
        nwh = nw >> 1;
        delta = atan(1.0) / nwh;
        wn4r = cos(delta * nwh);
        w[0] = 1;
        w[1] = wn4r;
        if (nwh == 4) {
            w[2] = cos(delta * 2);
            w[3] = sin(delta * 2);
        }
        else if (nwh > 4) {
            makeipt(nw, ip);
            w[2] = 0.5 / cos(delta * 2);
            w[3] = 0.5 / cos(delta * 6);
            for (j = 4; j < nwh; j += 4) {
                w[j] = cos(delta * j);
                w[j + 1] = sin(delta * j);
                w[j + 2] = cos(3 * delta * j);
                w[j + 3] = -sin(3 * delta * j);
            }
        }
        nw0 = 0;
        while (nwh > 2) {
            nw1 = nw0 + nwh;
            nwh >>= 1;
            w[nw1] = 1;
            w[nw1 + 1] = wn4r;
            if (nwh == 4) {
                wk1r = w[nw0 + 4];
                wk1i = w[nw0 + 5];
                w[nw1 + 2] = wk1r;
                w[nw1 + 3] = wk1i;
            }
            else if (nwh > 4) {
                wk1r = w[nw0 + 4];
                wk3r = w[nw0 + 6];
                w[nw1 + 2] = 0.5 / wk1r;
                w[nw1 + 3] = 0.5 / wk3r;
                for (j = 4; j < nwh; j += 4) {
                    wk1r = w[nw0 + 2 * j];
                    wk1i = w[nw0 + 2 * j + 1];
                    wk3r = w[nw0 + 2 * j + 2];
                    wk3i = w[nw0 + 2 * j + 3];
                    w[nw1 + j] = wk1r;
                    w[nw1 + j + 1] = wk1i;
                    w[nw1 + j + 2] = wk3r;
                    w[nw1 + j + 3] = wk3i;
                }
            }
            nw0 = nw1;
        }
    }
}

static void makect(int nc, int* ip, float* c)
{
    int j, nch;
    float delta;

    ip[1] = nc;
    if (nc > 1) {
        nch = nc >> 1;
        delta = atan(1.0) / nch;
        c[0] = cos(delta * nch);
        c[nch] = 0.5 * c[0];
        for (j = 1; j < nch; j++) {
            c[j] = 0.5 * cos(delta * j);
            c[nc - j] = 0.5 * sin(delta * j);
        }
    }
}

static void bitrv2(int n, int* ip, float* a)
{
    int j, j1, k, k1, l, m, nh, nm;
    float xr, xi, yr, yi;

    m = 1;
    for (l = n >> 2; l > 8; l >>= 2) {
        m <<= 1;
    }
    nh = n >> 1;
    nm = 4 * m;
    if (l == 8) {
        for (k = 0; k < m; k++) {
            for (j = 0; j < k; j++) {
                j1 = 4 * j + 2 * ip[m + k];
                k1 = 4 * k + 2 * ip[m + j];
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += 2 * nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 -= nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += 2 * nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nh;
                k1 += 2;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= 2 * nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 += nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= 2 * nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += 2;
                k1 += nh;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += 2 * nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 -= nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += 2 * nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nh;
                k1 -= 2;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= 2 * nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 += nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= 2 * nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
            }
            k1 = 4 * k + 2 * ip[m + k];
            j1 = k1 + 2;
            k1 += nh;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += nm;
            k1 += 2 * nm;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += nm;
            k1 -= nm;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 -= 2;
            k1 -= nh;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += nh + 2;
            k1 += nh + 2;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 -= nh - nm;
            k1 += 2 * nm - 2;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
        }
    }
    else {
        for (k = 0; k < m; k++) {
            for (j = 0; j < k; j++) {
                j1 = 4 * j + ip[m + k];
                k1 = 4 * k + ip[m + j];
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nh;
                k1 += 2;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += 2;
                k1 += nh;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nh;
                k1 -= 2;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= nm;
                xr = a[j1];
                xi = a[j1 + 1];
                yr = a[k1];
                yi = a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
            }
            k1 = 4 * k + ip[m + k];
            j1 = k1 + 2;
            k1 += nh;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += nm;
            k1 += nm;
            xr = a[j1];
            xi = a[j1 + 1];
            yr = a[k1];
            yi = a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
        }
    }
}

static void bitrv216(float* a)
{
    float x1r, x1i, x2r, x2i, x3r, x3i, x4r, x4i,
        x5r, x5i, x7r, x7i, x8r, x8i, x10r, x10i,
        x11r, x11i, x12r, x12i, x13r, x13i, x14r, x14i;

    x1r = a[2];
    x1i = a[3];
    x2r = a[4];
    x2i = a[5];
    x3r = a[6];
    x3i = a[7];
    x4r = a[8];
    x4i = a[9];
    x5r = a[10];
    x5i = a[11];
    x7r = a[14];
    x7i = a[15];
    x8r = a[16];
    x8i = a[17];
    x10r = a[20];
    x10i = a[21];
    x11r = a[22];
    x11i = a[23];
    x12r = a[24];
    x12i = a[25];
    x13r = a[26];
    x13i = a[27];
    x14r = a[28];
    x14i = a[29];
    a[2] = x8r;
    a[3] = x8i;
    a[4] = x4r;
    a[5] = x4i;
    a[6] = x12r;
    a[7] = x12i;
    a[8] = x2r;
    a[9] = x2i;
    a[10] = x10r;
    a[11] = x10i;
    a[14] = x14r;
    a[15] = x14i;
    a[16] = x1r;
    a[17] = x1i;
    a[20] = x5r;
    a[21] = x5i;
    a[22] = x13r;
    a[23] = x13i;
    a[24] = x3r;
    a[25] = x3i;
    a[26] = x11r;
    a[27] = x11i;
    a[28] = x7r;
    a[29] = x7i;
}

static void bitrv208(float* a)
{
    float x1r, x1i, x3r, x3i, x4r, x4i, x6r, x6i;

    x1r = a[2];
    x1i = a[3];
    x3r = a[6];
    x3i = a[7];
    x4r = a[8];
    x4i = a[9];
    x6r = a[12];
    x6i = a[13];
    a[2] = x4r;
    a[3] = x4i;
    a[6] = x6r;
    a[7] = x6i;
    a[8] = x1r;
    a[9] = x1i;
    a[12] = x3r;
    a[13] = x3i;
}

static void cftf1st(int n, float* a, float* w)
{
    int j, j0, j1, j2, j3, k, m, mh;
    float wn4r, csc1, csc3, wk1r, wk1i, wk3r, wk3i,
        wd1r, wd1i, wd3r, wd3i;
    float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i,
        y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i;

    mh = n >> 3;
    m = 2 * mh;
    j1 = m;
    j2 = j1 + m;
    j3 = j2 + m;
    x0r = a[0] + a[j2];
    x0i = a[1] + a[j2 + 1];
    x1r = a[0] - a[j2];
    x1i = a[1] - a[j2 + 1];
    x2r = a[j1] + a[j3];
    x2i = a[j1 + 1] + a[j3 + 1];
    x3r = a[j1] - a[j3];
    x3i = a[j1 + 1] - a[j3 + 1];
    a[0] = x0r + x2r;
    a[1] = x0i + x2i;
    a[j1] = x0r - x2r;
    a[j1 + 1] = x0i - x2i;
    a[j2] = x1r - x3i;
    a[j2 + 1] = x1i + x3r;
    a[j3] = x1r + x3i;
    a[j3 + 1] = x1i - x3r;
    wn4r = w[1];
    csc1 = w[2];
    csc3 = w[3];
    wd1r = 1;
    wd1i = 0;
    wd3r = 1;
    wd3i = 0;
    k = 0;
    for (j = 2; j < mh - 2; j += 4) {
        k += 4;
        wk1r = csc1 * (wd1r + w[k]);
        wk1i = csc1 * (wd1i + w[k + 1]);
        wk3r = csc3 * (wd3r + w[k + 2]);
        wk3i = csc3 * (wd3i + w[k + 3]);
        wd1r = w[k];
        wd1i = w[k + 1];
        wd3r = w[k + 2];
        wd3i = w[k + 3];
        j1 = j + m;
        j2 = j1 + m;
        j3 = j2 + m;
        x0r = a[j] + a[j2];
        x0i = a[j + 1] + a[j2 + 1];
        x1r = a[j] - a[j2];
        x1i = a[j + 1] - a[j2 + 1];
        y0r = a[j + 2] + a[j2 + 2];
        y0i = a[j + 3] + a[j2 + 3];
        y1r = a[j + 2] - a[j2 + 2];
        y1i = a[j + 3] - a[j2 + 3];
        x2r = a[j1] + a[j3];
        x2i = a[j1 + 1] + a[j3 + 1];
        x3r = a[j1] - a[j3];
        x3i = a[j1 + 1] - a[j3 + 1];
        y2r = a[j1 + 2] + a[j3 + 2];
        y2i = a[j1 + 3] + a[j3 + 3];
        y3r = a[j1 + 2] - a[j3 + 2];
        y3i = a[j1 + 3] - a[j3 + 3];
        a[j] = x0r + x2r;
        a[j + 1] = x0i + x2i;
        a[j + 2] = y0r + y2r;
        a[j + 3] = y0i + y2i;
        a[j1] = x0r - x2r;
        a[j1 + 1] = x0i - x2i;
        a[j1 + 2] = y0r - y2r;
        a[j1 + 3] = y0i - y2i;
        x0r = x1r - x3i;
        x0i = x1i + x3r;
        a[j2] = wk1r * x0r - wk1i * x0i;
        a[j2 + 1] = wk1r * x0i + wk1i * x0r;
        x0r = y1r - y3i;
        x0i = y1i + y3r;
        a[j2 + 2] = wd1r * x0r - wd1i * x0i;
        a[j2 + 3] = wd1r * x0i + wd1i * x0r;
        x0r = x1r + x3i;
        x0i = x1i - x3r;
        a[j3] = wk3r * x0r + wk3i * x0i;
        a[j3 + 1] = wk3r * x0i - wk3i * x0r;
        x0r = y1r + y3i;
        x0i = y1i - y3r;
        a[j3 + 2] = wd3r * x0r + wd3i * x0i;
        a[j3 + 3] = wd3r * x0i - wd3i * x0r;
        j0 = m - j;
        j1 = j0 + m;
        j2 = j1 + m;
        j3 = j2 + m;
        x0r = a[j0] + a[j2];
        x0i = a[j0 + 1] + a[j2 + 1];
        x1r = a[j0] - a[j2];
        x1i = a[j0 + 1] - a[j2 + 1];
        y0r = a[j0 - 2] + a[j2 - 2];
        y0i = a[j0 - 1] + a[j2 - 1];
        y1r = a[j0 - 2] - a[j2 - 2];
        y1i = a[j0 - 1] - a[j2 - 1];
        x2r = a[j1] + a[j3];
        x2i = a[j1 + 1] + a[j3 + 1];
        x3r = a[j1] - a[j3];
        x3i = a[j1 + 1] - a[j3 + 1];
        y2r = a[j1 - 2] + a[j3 - 2];
        y2i = a[j1 - 1] + a[j3 - 1];
        y3r = a[j1 - 2] - a[j3 - 2];
        y3i = a[j1 - 1] - a[j3 - 1];
        a[j0] = x0r + x2r;
        a[j0 + 1] = x0i + x2i;
        a[j0 - 2] = y0r + y2r;
        a[j0 - 1] = y0i + y2i;
        a[j1] = x0r - x2r;
        a[j1 + 1] = x0i - x2i;
        a[j1 - 2] = y0r - y2r;
        a[j1 - 1] = y0i - y2i;
        x0r = x1r - x3i;
        x0i = x1i + x3r;
        a[j2] = wk1i * x0r - wk1r * x0i;
        a[j2 + 1] = wk1i * x0i + wk1r * x0r;
        x0r = y1r - y3i;
        x0i = y1i + y3r;
        a[j2 - 2] = wd1i * x0r - wd1r * x0i;
        a[j2 - 1] = wd1i * x0i + wd1r * x0r;
        x0r = x1r + x3i;
        x0i = x1i - x3r;
        a[j3] = wk3i * x0r + wk3r * x0i;
        a[j3 + 1] = wk3i * x0i - wk3r * x0r;
        x0r = y1r + y3i;
        x0i = y1i - y3r;
        a[j3 - 2] = wd3i * x0r + wd3r * x0i;
        a[j3 - 1] = wd3i * x0i - wd3r * x0r;
    }
    wk1r = csc1 * (wd1r + wn4r);
    wk1i = csc1 * (wd1i + wn4r);
    wk3r = csc3 * (wd3r - wn4r);
    wk3i = csc3 * (wd3i - wn4r);
    j0 = mh;
    j1 = j0 + m;
    j2 = j1 + m;
    j3 = j2 + m;
    x0r = a[j0 - 2] + a[j2 - 2];
    x0i = a[j0 - 1] + a[j2 - 1];
    x1r = a[j0 - 2] - a[j2 - 2];
    x1i = a[j0 - 1] - a[j2 - 1];
    x2r = a[j1 - 2] + a[j3 - 2];
    x2i = a[j1 - 1] + a[j3 - 1];
    x3r = a[j1 - 2] - a[j3 - 2];
    x3i = a[j1 - 1] - a[j3 - 1];
    a[j0 - 2] = x0r + x2r;
    a[j0 - 1] = x0i + x2i;
    a[j1 - 2] = x0r - x2r;
    a[j1 - 1] = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    a[j2 - 2] = wk1r * x0r - wk1i * x0i;
    a[j2 - 1] = wk1r * x0i + wk1i * x0r;
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    a[j3 - 2] = wk3r * x0r + wk3i * x0i;
    a[j3 - 1] = wk3r * x0i - wk3i * x0r;
    x0r = a[j0] + a[j2];
    x0i = a[j0 + 1] + a[j2 + 1];
    x1r = a[j0] - a[j2];
    x1i = a[j0 + 1] - a[j2 + 1];
    x2r = a[j1] + a[j3];
    x2i = a[j1 + 1] + a[j3 + 1];
    x3r = a[j1] - a[j3];
    x3i = a[j1 + 1] - a[j3 + 1];
    a[j0] = x0r + x2r;
    a[j0 + 1] = x0i + x2i;
    a[j1] = x0r - x2r;
    a[j1 + 1] = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    a[j2] = wn4r * (x0r - x0i);
    a[j2 + 1] = wn4r * (x0i + x0r);
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    a[j3] = -wn4r * (x0r + x0i);
    a[j3 + 1] = -wn4r * (x0i - x0r);
    x0r = a[j0 + 2] + a[j2 + 2];
    x0i = a[j0 + 3] + a[j2 + 3];
    x1r = a[j0 + 2] - a[j2 + 2];
    x1i = a[j0 + 3] - a[j2 + 3];
    x2r = a[j1 + 2] + a[j3 + 2];
    x2i = a[j1 + 3] + a[j3 + 3];
    x3r = a[j1 + 2] - a[j3 + 2];
    x3i = a[j1 + 3] - a[j3 + 3];
    a[j0 + 2] = x0r + x2r;
    a[j0 + 3] = x0i + x2i;
    a[j1 + 2] = x0r - x2r;
    a[j1 + 3] = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    a[j2 + 2] = wk1i * x0r - wk1r * x0i;
    a[j2 + 3] = wk1i * x0i + wk1r * x0r;
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    a[j3 + 2] = wk3i * x0r + wk3r * x0i;
    a[j3 + 3] = wk3i * x0i - wk3r * x0r;
}

static void cftmdl1(int n, float* a, float* w)
{
    int j, j0, j1, j2, j3, k, m, mh;
    float wn4r, wk1r, wk1i, wk3r, wk3i;
    float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;

    mh = n >> 3;
    m = 2 * mh;
    j1 = m;
    j2 = j1 + m;
    j3 = j2 + m;
    x0r = a[0] + a[j2];
    x0i = a[1] + a[j2 + 1];
    x1r = a[0] - a[j2];
    x1i = a[1] - a[j2 + 1];
    x2r = a[j1] + a[j3];
    x2i = a[j1 + 1] + a[j3 + 1];
    x3r = a[j1] - a[j3];
    x3i = a[j1 + 1] - a[j3 + 1];
    a[0] = x0r + x2r;
    a[1] = x0i + x2i;
    a[j1] = x0r - x2r;
    a[j1 + 1] = x0i - x2i;
    a[j2] = x1r - x3i;
    a[j2 + 1] = x1i + x3r;
    a[j3] = x1r + x3i;
    a[j3 + 1] = x1i - x3r;
    wn4r = w[1];
    k = 0;
    for (j = 2; j < mh; j += 2) {
        k += 4;
        wk1r = w[k];
        wk1i = w[k + 1];
        wk3r = w[k + 2];
        wk3i = w[k + 3];
        j1 = j + m;
        j2 = j1 + m;
        j3 = j2 + m;
        x0r = a[j] + a[j2];
        x0i = a[j + 1] + a[j2 + 1];
        x1r = a[j] - a[j2];
        x1i = a[j + 1] - a[j2 + 1];
        x2r = a[j1] + a[j3];
        x2i = a[j1 + 1] + a[j3 + 1];
        x3r = a[j1] - a[j3];
        x3i = a[j1 + 1] - a[j3 + 1];
        a[j] = x0r + x2r;
        a[j + 1] = x0i + x2i;
        a[j1] = x0r - x2r;
        a[j1 + 1] = x0i - x2i;
        x0r = x1r - x3i;
        x0i = x1i + x3r;
        a[j2] = wk1r * x0r - wk1i * x0i;
        a[j2 + 1] = wk1r * x0i + wk1i * x0r;
        x0r = x1r + x3i;
        x0i = x1i - x3r;
        a[j3] = wk3r * x0r + wk3i * x0i;
        a[j3 + 1] = wk3r * x0i - wk3i * x0r;
        j0 = m - j;
        j1 = j0 + m;
        j2 = j1 + m;
        j3 = j2 + m;
        x0r = a[j0] + a[j2];
        x0i = a[j0 + 1] + a[j2 + 1];
        x1r = a[j0] - a[j2];
        x1i = a[j0 + 1] - a[j2 + 1];
        x2r = a[j1] + a[j3];
        x2i = a[j1 + 1] + a[j3 + 1];
        x3r = a[j1] - a[j3];
        x3i = a[j1 + 1] - a[j3 + 1];
        a[j0] = x0r + x2r;
        a[j0 + 1] = x0i + x2i;
        a[j1] = x0r - x2r;
        a[j1 + 1] = x0i - x2i;
        x0r = x1r - x3i;
        x0i = x1i + x3r;
        a[j2] = wk1i * x0r - wk1r * x0i;
        a[j2 + 1] = wk1i * x0i + wk1r * x0r;
        x0r = x1r + x3i;
        x0i = x1i - x3r;
        a[j3] = wk3i * x0r + wk3r * x0i;
        a[j3 + 1] = wk3i * x0i - wk3r * x0r;
    }
    j0 = mh;
    j1 = j0 + m;
    j2 = j1 + m;
    j3 = j2 + m;
    x0r = a[j0] + a[j2];
    x0i = a[j0 + 1] + a[j2 + 1];
    x1r = a[j0] - a[j2];
    x1i = a[j0 + 1] - a[j2 + 1];
    x2r = a[j1] + a[j3];
    x2i = a[j1 + 1] + a[j3 + 1];
    x3r = a[j1] - a[j3];
    x3i = a[j1 + 1] - a[j3 + 1];
    a[j0] = x0r + x2r;
    a[j0 + 1] = x0i + x2i;
    a[j1] = x0r - x2r;
    a[j1 + 1] = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    a[j2] = wn4r * (x0r - x0i);
    a[j2 + 1] = wn4r * (x0i + x0r);
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    a[j3] = -wn4r * (x0r + x0i);
    a[j3 + 1] = -wn4r * (x0i - x0r);
}

static void cftmdl2(int n, float* a, float* w)
{
    int j, j0, j1, j2, j3, k, kr, m, mh;
    float wn4r, wk1r, wk1i, wk3r, wk3i, wd1r, wd1i, wd3r, wd3i;
    float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i, y0r, y0i, y2r, y2i;

    mh = n >> 3;
    m = 2 * mh;
    wn4r = w[1];
    j1 = m;
    j2 = j1 + m;
    j3 = j2 + m;
    x0r = a[0] - a[j2 + 1];
    x0i = a[1] + a[j2];
    x1r = a[0] + a[j2 + 1];
    x1i = a[1] - a[j2];
    x2r = a[j1] - a[j3 + 1];
    x2i = a[j1 + 1] + a[j3];
    x3r = a[j1] + a[j3 + 1];
    x3i = a[j1 + 1] - a[j3];
    y0r = wn4r * (x2r - x2i);
    y0i = wn4r * (x2i + x2r);
    a[0] = x0r + y0r;
    a[1] = x0i + y0i;
    a[j1] = x0r - y0r;
    a[j1 + 1] = x0i - y0i;
    y0r = wn4r * (x3r - x3i);
    y0i = wn4r * (x3i + x3r);
    a[j2] = x1r - y0i;
    a[j2 + 1] = x1i + y0r;
    a[j3] = x1r + y0i;
    a[j3 + 1] = x1i - y0r;
    k = 0;
    kr = 2 * m;
    for (j = 2; j < mh; j += 2) {
        k += 4;
        wk1r = w[k];
        wk1i = w[k + 1];
        wk3r = w[k + 2];
        wk3i = w[k + 3];
        kr -= 4;
        wd1i = w[kr];
        wd1r = w[kr + 1];
        wd3i = w[kr + 2];
        wd3r = w[kr + 3];
        j1 = j + m;
        j2 = j1 + m;
        j3 = j2 + m;
        x0r = a[j] - a[j2 + 1];
        x0i = a[j + 1] + a[j2];
        x1r = a[j] + a[j2 + 1];
        x1i = a[j + 1] - a[j2];
        x2r = a[j1] - a[j3 + 1];
        x2i = a[j1 + 1] + a[j3];
        x3r = a[j1] + a[j3 + 1];
        x3i = a[j1 + 1] - a[j3];
        y0r = wk1r * x0r - wk1i * x0i;
        y0i = wk1r * x0i + wk1i * x0r;
        y2r = wd1r * x2r - wd1i * x2i;
        y2i = wd1r * x2i + wd1i * x2r;
        a[j] = y0r + y2r;
        a[j + 1] = y0i + y2i;
        a[j1] = y0r - y2r;
        a[j1 + 1] = y0i - y2i;
        y0r = wk3r * x1r + wk3i * x1i;
        y0i = wk3r * x1i - wk3i * x1r;
        y2r = wd3r * x3r + wd3i * x3i;
        y2i = wd3r * x3i - wd3i * x3r;
        a[j2] = y0r + y2r;
        a[j2 + 1] = y0i + y2i;
        a[j3] = y0r - y2r;
        a[j3 + 1] = y0i - y2i;
        j0 = m - j;
        j1 = j0 + m;
        j2 = j1 + m;
        j3 = j2 + m;
        x0r = a[j0] - a[j2 + 1];
        x0i = a[j0 + 1] + a[j2];
        x1r = a[j0] + a[j2 + 1];
        x1i = a[j0 + 1] - a[j2];
        x2r = a[j1] - a[j3 + 1];
        x2i = a[j1 + 1] + a[j3];
        x3r = a[j1] + a[j3 + 1];
        x3i = a[j1 + 1] - a[j3];
        y0r = wd1i * x0r - wd1r * x0i;
        y0i = wd1i * x0i + wd1r * x0r;
        y2r = wk1i * x2r - wk1r * x2i;
        y2i = wk1i * x2i + wk1r * x2r;
        a[j0] = y0r + y2r;
        a[j0 + 1] = y0i + y2i;
        a[j1] = y0r - y2r;
        a[j1 + 1] = y0i - y2i;
        y0r = wd3i * x1r + wd3r * x1i;
        y0i = wd3i * x1i - wd3r * x1r;
        y2r = wk3i * x3r + wk3r * x3i;
        y2i = wk3i * x3i - wk3r * x3r;
        a[j2] = y0r + y2r;
        a[j2 + 1] = y0i + y2i;
        a[j3] = y0r - y2r;
        a[j3 + 1] = y0i - y2i;
    }
    wk1r = w[m];
    wk1i = w[m + 1];
    j0 = mh;
    j1 = j0 + m;
    j2 = j1 + m;
    j3 = j2 + m;
    x0r = a[j0] - a[j2 + 1];
    x0i = a[j0 + 1] + a[j2];
    x1r = a[j0] + a[j2 + 1];
    x1i = a[j0 + 1] - a[j2];
    x2r = a[j1] - a[j3 + 1];
    x2i = a[j1 + 1] + a[j3];
    x3r = a[j1] + a[j3 + 1];
    x3i = a[j1 + 1] - a[j3];
    y0r = wk1r * x0r - wk1i * x0i;
    y0i = wk1r * x0i + wk1i * x0r;
    y2r = wk1i * x2r - wk1r * x2i;
    y2i = wk1i * x2i + wk1r * x2r;
    a[j0] = y0r + y2r;
    a[j0 + 1] = y0i + y2i;
    a[j1] = y0r - y2r;
    a[j1 + 1] = y0i - y2i;
    y0r = wk1i * x1r - wk1r * x1i;
    y0i = wk1i * x1i + wk1r * x1r;
    y2r = wk1r * x3r - wk1i * x3i;
    y2i = wk1r * x3i + wk1i * x3r;
    a[j2] = y0r - y2r;
    a[j2 + 1] = y0i - y2i;
    a[j3] = y0r + y2r;
    a[j3 + 1] = y0i + y2i;
}

static int cfttree(int n, int j, int k, float* a, int nw, float* w)
{
    void cftmdl1(int n, float* a, float* w);
    void cftmdl2(int n, float* a, float* w);
    int i, isplt, m;

    if ((k & 3) != 0) {
        isplt = k & 1;
        if (isplt != 0) {
            cftmdl1(n, &a[j - n], &w[nw - (n >> 1)]);
        }
        else {
            cftmdl2(n, &a[j - n], &w[nw - n]);
        }
    }
    else {
        m = n;
        for (i = k; (i & 3) == 0; i >>= 2) {
            m <<= 2;
        }
        isplt = i & 1;
        if (isplt != 0) {
            while (m > 128) {
                cftmdl1(m, &a[j - m], &w[nw - (m >> 1)]);
                m >>= 2;
            }
        }
        else {
            while (m > 128) {
                cftmdl2(m, &a[j - m], &w[nw - m]);
                m >>= 2;
            }
        }
    }
    return isplt;
}

static void cftf161(float* a, float* w)
{
    float wn4r, wk1r, wk1i,
        x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i,
        y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i,
        y4r, y4i, y5r, y5i, y6r, y6i, y7r, y7i,
        y8r, y8i, y9r, y9i, y10r, y10i, y11r, y11i,
        y12r, y12i, y13r, y13i, y14r, y14i, y15r, y15i;

    wn4r = w[1];
    wk1r = w[2];
    wk1i = w[3];
    x0r = a[0] + a[16];
    x0i = a[1] + a[17];
    x1r = a[0] - a[16];
    x1i = a[1] - a[17];
    x2r = a[8] + a[24];
    x2i = a[9] + a[25];
    x3r = a[8] - a[24];
    x3i = a[9] - a[25];
    y0r = x0r + x2r;
    y0i = x0i + x2i;
    y4r = x0r - x2r;
    y4i = x0i - x2i;
    y8r = x1r - x3i;
    y8i = x1i + x3r;
    y12r = x1r + x3i;
    y12i = x1i - x3r;
    x0r = a[2] + a[18];
    x0i = a[3] + a[19];
    x1r = a[2] - a[18];
    x1i = a[3] - a[19];
    x2r = a[10] + a[26];
    x2i = a[11] + a[27];
    x3r = a[10] - a[26];
    x3i = a[11] - a[27];
    y1r = x0r + x2r;
    y1i = x0i + x2i;
    y5r = x0r - x2r;
    y5i = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    y9r = wk1r * x0r - wk1i * x0i;
    y9i = wk1r * x0i + wk1i * x0r;
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    y13r = wk1i * x0r - wk1r * x0i;
    y13i = wk1i * x0i + wk1r * x0r;
    x0r = a[4] + a[20];
    x0i = a[5] + a[21];
    x1r = a[4] - a[20];
    x1i = a[5] - a[21];
    x2r = a[12] + a[28];
    x2i = a[13] + a[29];
    x3r = a[12] - a[28];
    x3i = a[13] - a[29];
    y2r = x0r + x2r;
    y2i = x0i + x2i;
    y6r = x0r - x2r;
    y6i = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    y10r = wn4r * (x0r - x0i);
    y10i = wn4r * (x0i + x0r);
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    y14r = wn4r * (x0r + x0i);
    y14i = wn4r * (x0i - x0r);
    x0r = a[6] + a[22];
    x0i = a[7] + a[23];
    x1r = a[6] - a[22];
    x1i = a[7] - a[23];
    x2r = a[14] + a[30];
    x2i = a[15] + a[31];
    x3r = a[14] - a[30];
    x3i = a[15] - a[31];
    y3r = x0r + x2r;
    y3i = x0i + x2i;
    y7r = x0r - x2r;
    y7i = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    y11r = wk1i * x0r - wk1r * x0i;
    y11i = wk1i * x0i + wk1r * x0r;
    x0r = x1r + x3i;
    x0i = x1i - x3r;
    y15r = wk1r * x0r - wk1i * x0i;
    y15i = wk1r * x0i + wk1i * x0r;
    x0r = y12r - y14r;
    x0i = y12i - y14i;
    x1r = y12r + y14r;
    x1i = y12i + y14i;
    x2r = y13r - y15r;
    x2i = y13i - y15i;
    x3r = y13r + y15r;
    x3i = y13i + y15i;
    a[24] = x0r + x2r;
    a[25] = x0i + x2i;
    a[26] = x0r - x2r;
    a[27] = x0i - x2i;
    a[28] = x1r - x3i;
    a[29] = x1i + x3r;
    a[30] = x1r + x3i;
    a[31] = x1i - x3r;
    x0r = y8r + y10r;
    x0i = y8i + y10i;
    x1r = y8r - y10r;
    x1i = y8i - y10i;
    x2r = y9r + y11r;
    x2i = y9i + y11i;
    x3r = y9r - y11r;
    x3i = y9i - y11i;
    a[16] = x0r + x2r;
    a[17] = x0i + x2i;
    a[18] = x0r - x2r;
    a[19] = x0i - x2i;
    a[20] = x1r - x3i;
    a[21] = x1i + x3r;
    a[22] = x1r + x3i;
    a[23] = x1i - x3r;
    x0r = y5r - y7i;
    x0i = y5i + y7r;
    x2r = wn4r * (x0r - x0i);
    x2i = wn4r * (x0i + x0r);
    x0r = y5r + y7i;
    x0i = y5i - y7r;
    x3r = wn4r * (x0r - x0i);
    x3i = wn4r * (x0i + x0r);
    x0r = y4r - y6i;
    x0i = y4i + y6r;
    x1r = y4r + y6i;
    x1i = y4i - y6r;
    a[8] = x0r + x2r;
    a[9] = x0i + x2i;
    a[10] = x0r - x2r;
    a[11] = x0i - x2i;
    a[12] = x1r - x3i;
    a[13] = x1i + x3r;
    a[14] = x1r + x3i;
    a[15] = x1i - x3r;
    x0r = y0r + y2r;
    x0i = y0i + y2i;
    x1r = y0r - y2r;
    x1i = y0i - y2i;
    x2r = y1r + y3r;
    x2i = y1i + y3i;
    x3r = y1r - y3r;
    x3i = y1i - y3i;
    a[0] = x0r + x2r;
    a[1] = x0i + x2i;
    a[2] = x0r - x2r;
    a[3] = x0i - x2i;
    a[4] = x1r - x3i;
    a[5] = x1i + x3r;
    a[6] = x1r + x3i;
    a[7] = x1i - x3r;
}

static void cftf162(float* a, float* w)
{
    float wn4r, wk1r, wk1i, wk2r, wk2i, wk3r, wk3i,
        x0r, x0i, x1r, x1i, x2r, x2i,
        y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i,
        y4r, y4i, y5r, y5i, y6r, y6i, y7r, y7i,
        y8r, y8i, y9r, y9i, y10r, y10i, y11r, y11i,
        y12r, y12i, y13r, y13i, y14r, y14i, y15r, y15i;

    wn4r = w[1];
    wk1r = w[4];
    wk1i = w[5];
    wk3r = w[6];
    wk3i = -w[7];
    wk2r = w[8];
    wk2i = w[9];
    x1r = a[0] - a[17];
    x1i = a[1] + a[16];
    x0r = a[8] - a[25];
    x0i = a[9] + a[24];
    x2r = wn4r * (x0r - x0i);
    x2i = wn4r * (x0i + x0r);
    y0r = x1r + x2r;
    y0i = x1i + x2i;
    y4r = x1r - x2r;
    y4i = x1i - x2i;
    x1r = a[0] + a[17];
    x1i = a[1] - a[16];
    x0r = a[8] + a[25];
    x0i = a[9] - a[24];
    x2r = wn4r * (x0r - x0i);
    x2i = wn4r * (x0i + x0r);
    y8r = x1r - x2i;
    y8i = x1i + x2r;
    y12r = x1r + x2i;
    y12i = x1i - x2r;
    x0r = a[2] - a[19];
    x0i = a[3] + a[18];
    x1r = wk1r * x0r - wk1i * x0i;
    x1i = wk1r * x0i + wk1i * x0r;
    x0r = a[10] - a[27];
    x0i = a[11] + a[26];
    x2r = wk3i * x0r - wk3r * x0i;
    x2i = wk3i * x0i + wk3r * x0r;
    y1r = x1r + x2r;
    y1i = x1i + x2i;
    y5r = x1r - x2r;
    y5i = x1i - x2i;
    x0r = a[2] + a[19];
    x0i = a[3] - a[18];
    x1r = wk3r * x0r - wk3i * x0i;
    x1i = wk3r * x0i + wk3i * x0r;
    x0r = a[10] + a[27];
    x0i = a[11] - a[26];
    x2r = wk1r * x0r + wk1i * x0i;
    x2i = wk1r * x0i - wk1i * x0r;
    y9r = x1r - x2r;
    y9i = x1i - x2i;
    y13r = x1r + x2r;
    y13i = x1i + x2i;
    x0r = a[4] - a[21];
    x0i = a[5] + a[20];
    x1r = wk2r * x0r - wk2i * x0i;
    x1i = wk2r * x0i + wk2i * x0r;
    x0r = a[12] - a[29];
    x0i = a[13] + a[28];
    x2r = wk2i * x0r - wk2r * x0i;
    x2i = wk2i * x0i + wk2r * x0r;
    y2r = x1r + x2r;
    y2i = x1i + x2i;
    y6r = x1r - x2r;
    y6i = x1i - x2i;
    x0r = a[4] + a[21];
    x0i = a[5] - a[20];
    x1r = wk2i * x0r - wk2r * x0i;
    x1i = wk2i * x0i + wk2r * x0r;
    x0r = a[12] + a[29];
    x0i = a[13] - a[28];
    x2r = wk2r * x0r - wk2i * x0i;
    x2i = wk2r * x0i + wk2i * x0r;
    y10r = x1r - x2r;
    y10i = x1i - x2i;
    y14r = x1r + x2r;
    y14i = x1i + x2i;
    x0r = a[6] - a[23];
    x0i = a[7] + a[22];
    x1r = wk3r * x0r - wk3i * x0i;
    x1i = wk3r * x0i + wk3i * x0r;
    x0r = a[14] - a[31];
    x0i = a[15] + a[30];
    x2r = wk1i * x0r - wk1r * x0i;
    x2i = wk1i * x0i + wk1r * x0r;
    y3r = x1r + x2r;
    y3i = x1i + x2i;
    y7r = x1r - x2r;
    y7i = x1i - x2i;
    x0r = a[6] + a[23];
    x0i = a[7] - a[22];
    x1r = wk1i * x0r + wk1r * x0i;
    x1i = wk1i * x0i - wk1r * x0r;
    x0r = a[14] + a[31];
    x0i = a[15] - a[30];
    x2r = wk3i * x0r - wk3r * x0i;
    x2i = wk3i * x0i + wk3r * x0r;
    y11r = x1r + x2r;
    y11i = x1i + x2i;
    y15r = x1r - x2r;
    y15i = x1i - x2i;
    x1r = y0r + y2r;
    x1i = y0i + y2i;
    x2r = y1r + y3r;
    x2i = y1i + y3i;
    a[0] = x1r + x2r;
    a[1] = x1i + x2i;
    a[2] = x1r - x2r;
    a[3] = x1i - x2i;
    x1r = y0r - y2r;
    x1i = y0i - y2i;
    x2r = y1r - y3r;
    x2i = y1i - y3i;
    a[4] = x1r - x2i;
    a[5] = x1i + x2r;
    a[6] = x1r + x2i;
    a[7] = x1i - x2r;
    x1r = y4r - y6i;
    x1i = y4i + y6r;
    x0r = y5r - y7i;
    x0i = y5i + y7r;
    x2r = wn4r * (x0r - x0i);
    x2i = wn4r * (x0i + x0r);
    a[8] = x1r + x2r;
    a[9] = x1i + x2i;
    a[10] = x1r - x2r;
    a[11] = x1i - x2i;
    x1r = y4r + y6i;
    x1i = y4i - y6r;
    x0r = y5r + y7i;
    x0i = y5i - y7r;
    x2r = wn4r * (x0r - x0i);
    x2i = wn4r * (x0i + x0r);
    a[12] = x1r - x2i;
    a[13] = x1i + x2r;
    a[14] = x1r + x2i;
    a[15] = x1i - x2r;
    x1r = y8r + y10r;
    x1i = y8i + y10i;
    x2r = y9r - y11r;
    x2i = y9i - y11i;
    a[16] = x1r + x2r;
    a[17] = x1i + x2i;
    a[18] = x1r - x2r;
    a[19] = x1i - x2i;
    x1r = y8r - y10r;
    x1i = y8i - y10i;
    x2r = y9r + y11r;
    x2i = y9i + y11i;
    a[20] = x1r - x2i;
    a[21] = x1i + x2r;
    a[22] = x1r + x2i;
    a[23] = x1i - x2r;
    x1r = y12r - y14i;
    x1i = y12i + y14r;
    x0r = y13r + y15i;
    x0i = y13i - y15r;
    x2r = wn4r * (x0r - x0i);
    x2i = wn4r * (x0i + x0r);
    a[24] = x1r + x2r;
    a[25] = x1i + x2i;
    a[26] = x1r - x2r;
    a[27] = x1i - x2i;
    x1r = y12r + y14i;
    x1i = y12i - y14r;
    x0r = y13r - y15i;
    x0i = y13i + y15r;
    x2r = wn4r * (x0r - x0i);
    x2i = wn4r * (x0i + x0r);
    a[28] = x1r - x2i;
    a[29] = x1i + x2r;
    a[30] = x1r + x2i;
    a[31] = x1i - x2r;
}

static void cftf081(float* a, float* w)
{
    float wn4r, x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i,
        y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i,
        y4r, y4i, y5r, y5i, y6r, y6i, y7r, y7i;

    wn4r = w[1];
    x0r = a[0] + a[8];
    x0i = a[1] + a[9];
    x1r = a[0] - a[8];
    x1i = a[1] - a[9];
    x2r = a[4] + a[12];
    x2i = a[5] + a[13];
    x3r = a[4] - a[12];
    x3i = a[5] - a[13];
    y0r = x0r + x2r;
    y0i = x0i + x2i;
    y2r = x0r - x2r;
    y2i = x0i - x2i;
    y1r = x1r - x3i;
    y1i = x1i + x3r;
    y3r = x1r + x3i;
    y3i = x1i - x3r;
    x0r = a[2] + a[10];
    x0i = a[3] + a[11];
    x1r = a[2] - a[10];
    x1i = a[3] - a[11];
    x2r = a[6] + a[14];
    x2i = a[7] + a[15];
    x3r = a[6] - a[14];
    x3i = a[7] - a[15];
    y4r = x0r + x2r;
    y4i = x0i + x2i;
    y6r = x0r - x2r;
    y6i = x0i - x2i;
    x0r = x1r - x3i;
    x0i = x1i + x3r;
    x2r = x1r + x3i;
    x2i = x1i - x3r;
    y5r = wn4r * (x0r - x0i);
    y5i = wn4r * (x0r + x0i);
    y7r = wn4r * (x2r - x2i);
    y7i = wn4r * (x2r + x2i);
    a[8] = y1r + y5r;
    a[9] = y1i + y5i;
    a[10] = y1r - y5r;
    a[11] = y1i - y5i;
    a[12] = y3r - y7i;
    a[13] = y3i + y7r;
    a[14] = y3r + y7i;
    a[15] = y3i - y7r;
    a[0] = y0r + y4r;
    a[1] = y0i + y4i;
    a[2] = y0r - y4r;
    a[3] = y0i - y4i;
    a[4] = y2r - y6i;
    a[5] = y2i + y6r;
    a[6] = y2r + y6i;
    a[7] = y2i - y6r;
}

static void cftf082(float* a, float* w)
{
    float wn4r, wk1r, wk1i, x0r, x0i, x1r, x1i,
        y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i,
        y4r, y4i, y5r, y5i, y6r, y6i, y7r, y7i;

    wn4r = w[1];
    wk1r = w[2];
    wk1i = w[3];
    y0r = a[0] - a[9];
    y0i = a[1] + a[8];
    y1r = a[0] + a[9];
    y1i = a[1] - a[8];
    x0r = a[4] - a[13];
    x0i = a[5] + a[12];
    y2r = wn4r * (x0r - x0i);
    y2i = wn4r * (x0i + x0r);
    x0r = a[4] + a[13];
    x0i = a[5] - a[12];
    y3r = wn4r * (x0r - x0i);
    y3i = wn4r * (x0i + x0r);
    x0r = a[2] - a[11];
    x0i = a[3] + a[10];
    y4r = wk1r * x0r - wk1i * x0i;
    y4i = wk1r * x0i + wk1i * x0r;
    x0r = a[2] + a[11];
    x0i = a[3] - a[10];
    y5r = wk1i * x0r - wk1r * x0i;
    y5i = wk1i * x0i + wk1r * x0r;
    x0r = a[6] - a[15];
    x0i = a[7] + a[14];
    y6r = wk1i * x0r - wk1r * x0i;
    y6i = wk1i * x0i + wk1r * x0r;
    x0r = a[6] + a[15];
    x0i = a[7] - a[14];
    y7r = wk1r * x0r - wk1i * x0i;
    y7i = wk1r * x0i + wk1i * x0r;
    x0r = y0r + y2r;
    x0i = y0i + y2i;
    x1r = y4r + y6r;
    x1i = y4i + y6i;
    a[0] = x0r + x1r;
    a[1] = x0i + x1i;
    a[2] = x0r - x1r;
    a[3] = x0i - x1i;
    x0r = y0r - y2r;
    x0i = y0i - y2i;
    x1r = y4r - y6r;
    x1i = y4i - y6i;
    a[4] = x0r - x1i;
    a[5] = x0i + x1r;
    a[6] = x0r + x1i;
    a[7] = x0i - x1r;
    x0r = y1r - y3i;
    x0i = y1i + y3r;
    x1r = y5r - y7r;
    x1i = y5i - y7i;
    a[8] = x0r + x1r;
    a[9] = x0i + x1i;
    a[10] = x0r - x1r;
    a[11] = x0i - x1i;
    x0r = y1r + y3i;
    x0i = y1i - y3r;
    x1r = y5r + y7r;
    x1i = y5i + y7i;
    a[12] = x0r - x1i;
    a[13] = x0i + x1r;
    a[14] = x0r + x1i;
    a[15] = x0i - x1r;
}

static void cftleaf(int n, int isplt, float* a, int nw, float* w)
{
    void cftmdl1(int n, float* a, float* w);
    void cftmdl2(int n, float* a, float* w);
    void cftf161(float* a, float* w);
    void cftf162(float* a, float* w);
    void cftf081(float* a, float* w);
    void cftf082(float* a, float* w);

    if (n == 512) {
        cftmdl1(128, a, &w[nw - 64]);
        cftf161(a, &w[nw - 8]);
        cftf162(&a[32], &w[nw - 32]);
        cftf161(&a[64], &w[nw - 8]);
        cftf161(&a[96], &w[nw - 8]);
        cftmdl2(128, &a[128], &w[nw - 128]);
        cftf161(&a[128], &w[nw - 8]);
        cftf162(&a[160], &w[nw - 32]);
        cftf161(&a[192], &w[nw - 8]);
        cftf162(&a[224], &w[nw - 32]);
        cftmdl1(128, &a[256], &w[nw - 64]);
        cftf161(&a[256], &w[nw - 8]);
        cftf162(&a[288], &w[nw - 32]);
        cftf161(&a[320], &w[nw - 8]);
        cftf161(&a[352], &w[nw - 8]);
        if (isplt != 0) {
            cftmdl1(128, &a[384], &w[nw - 64]);
            cftf161(&a[480], &w[nw - 8]);
        }
        else {
            cftmdl2(128, &a[384], &w[nw - 128]);
            cftf162(&a[480], &w[nw - 32]);
        }
        cftf161(&a[384], &w[nw - 8]);
        cftf162(&a[416], &w[nw - 32]);
        cftf161(&a[448], &w[nw - 8]);
    }
    else {
        cftmdl1(64, a, &w[nw - 32]);
        cftf081(a, &w[nw - 8]);
        cftf082(&a[16], &w[nw - 8]);
        cftf081(&a[32], &w[nw - 8]);
        cftf081(&a[48], &w[nw - 8]);
        cftmdl2(64, &a[64], &w[nw - 64]);
        cftf081(&a[64], &w[nw - 8]);
        cftf082(&a[80], &w[nw - 8]);
        cftf081(&a[96], &w[nw - 8]);
        cftf082(&a[112], &w[nw - 8]);
        cftmdl1(64, &a[128], &w[nw - 32]);
        cftf081(&a[128], &w[nw - 8]);
        cftf082(&a[144], &w[nw - 8]);
        cftf081(&a[160], &w[nw - 8]);
        cftf081(&a[176], &w[nw - 8]);
        if (isplt != 0) {
            cftmdl1(64, &a[192], &w[nw - 32]);
            cftf081(&a[240], &w[nw - 8]);
        }
        else {
            cftmdl2(64, &a[192], &w[nw - 64]);
            cftf082(&a[240], &w[nw - 8]);
        }
        cftf081(&a[192], &w[nw - 8]);
        cftf082(&a[208], &w[nw - 8]);
        cftf081(&a[224], &w[nw - 8]);
    }
}

static void cftrec4(int n, float* a, int nw, float* w)
{
    int cfttree(int n, int j, int k, float* a, int nw, float* w);
    void cftleaf(int n, int isplt, float* a, int nw, float* w);
    void cftmdl1(int n, float* a, float* w);
    int isplt, j, k, m;

    m = n;
    while (m > 512) {
        m >>= 2;
        cftmdl1(m, &a[n - m], &w[nw - (m >> 1)]);
    }
    cftleaf(m, 1, &a[n - m], nw, w);
    k = 0;
    for (j = n - m; j > 0; j -= m) {
        k++;
        isplt = cfttree(m, j, k, a, nw, w);
        cftleaf(m, isplt, &a[j - m], nw, w);
    }
}

static void cftfx41(int n, float* a, int nw, float* w)
{
    void cftf161(float* a, float* w);
    void cftf162(float* a, float* w);
    void cftf081(float* a, float* w);
    void cftf082(float* a, float* w);

    if (n == 128) {
        cftf161(a, &w[nw - 8]);
        cftf162(&a[32], &w[nw - 32]);
        cftf161(&a[64], &w[nw - 8]);
        cftf161(&a[96], &w[nw - 8]);
    }
    else {
        cftf081(a, &w[nw - 8]);
        cftf082(&a[16], &w[nw - 8]);
        cftf081(&a[32], &w[nw - 8]);
        cftf081(&a[48], &w[nw - 8]);
    }
}

static void cftf040(float* a)
{
    float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;

    x0r = a[0] + a[4];
    x0i = a[1] + a[5];
    x1r = a[0] - a[4];
    x1i = a[1] - a[5];
    x2r = a[2] + a[6];
    x2i = a[3] + a[7];
    x3r = a[2] - a[6];
    x3i = a[3] - a[7];
    a[0] = x0r + x2r;
    a[1] = x0i + x2i;
    a[2] = x1r - x3i;
    a[3] = x1i + x3r;
    a[4] = x0r - x2r;
    a[5] = x0i - x2i;
    a[6] = x1r + x3i;
    a[7] = x1i - x3r;
}

static void cftx020(float* a)
{
    float x0r, x0i;

    x0r = a[0] - a[2];
    x0i = a[1] - a[3];
    a[0] += a[2];
    a[1] += a[3];
    a[2] = x0r;
    a[3] = x0i;
}

#ifdef USE_CDFT_THREADS
struct cdft_arg_st {
    int n0;
    int n;
    float* a;
    int nw;
    float* w;
};
typedef struct cdft_arg_st cdft_arg_t;


static void cftrec4_th(int n, float* a, int nw, float* w)
{
    void* cftrec1_th(void* p);
    void* cftrec2_th(void* p);
    int i, idiv4, m, nthread;
    cdft_thread_t th[4];
    cdft_arg_t ag[4];

    nthread = 2;
    idiv4 = 0;
    m = n >> 1;
    if (n > CDFT_4THREADS_BEGIN_N) {
        nthread = 4;
        idiv4 = 1;
        m >>= 1;
    }
    for (i = 0; i < nthread; i++) {
        ag[i].n0 = n;
        ag[i].n = m;
        ag[i].a = &a[i * m];
        ag[i].nw = nw;
        ag[i].w = w;
        if (i != idiv4) {
            cdft_thread_create(&th[i], cftrec1_th, &ag[i]);
        }
        else {
            cdft_thread_create(&th[i], cftrec2_th, &ag[i]);
        }
    }
    for (i = 0; i < nthread; i++) {
        cdft_thread_wait(th[i]);
    }
}


static void* cftrec1_th(void* p)
{
    int cfttree(int n, int j, int k, float* a, int nw, float* w);
    void cftleaf(int n, int isplt, float* a, int nw, float* w);
    void cftmdl1(int n, float* a, float* w);
    int isplt, j, k, m, n, n0, nw;
    float* a, * w;

    n0 = ((cdft_arg_t*)p)->n0;
    n = ((cdft_arg_t*)p)->n;
    a = ((cdft_arg_t*)p)->a;
    nw = ((cdft_arg_t*)p)->nw;
    w = ((cdft_arg_t*)p)->w;
    m = n0;
    while (m > 512) {
        m >>= 2;
        cftmdl1(m, &a[n - m], &w[nw - (m >> 1)]);
    }
    cftleaf(m, 1, &a[n - m], nw, w);
    k = 0;
    for (j = n - m; j > 0; j -= m) {
        k++;
        isplt = cfttree(m, j, k, a, nw, w);
        cftleaf(m, isplt, &a[j - m], nw, w);
    }
    return (void*)0;
}


static void* cftrec2_th(void* p)
{
    int cfttree(int n, int j, int k, float* a, int nw, float* w);
    void cftleaf(int n, int isplt, float* a, int nw, float* w);
    void cftmdl2(int n, float* a, float* w);
    int isplt, j, k, m, n, n0, nw;
    float* a, * w;

    n0 = ((cdft_arg_t*)p)->n0;
    n = ((cdft_arg_t*)p)->n;
    a = ((cdft_arg_t*)p)->a;
    nw = ((cdft_arg_t*)p)->nw;
    w = ((cdft_arg_t*)p)->w;
    k = 1;
    m = n0;
    while (m > 512) {
        m >>= 2;
        k <<= 2;
        cftmdl2(m, &a[n - m], &w[nw - m]);
    }
    cftleaf(m, 0, &a[n - m], nw, w);
    k >>= 1;
    for (j = n - m; j > 0; j -= m) {
        k++;
        isplt = cfttree(m, j, k, a, nw, w);
        cftleaf(m, isplt, &a[j - m], nw, w);
    }
    return (void*)0;
}
#endif /* USE_CDFT_THREADS */

static void cftfsub(int n, float* a, int* ip, int nw, float* w)
{
    void bitrv2(int n, int* ip, float* a);
    void bitrv216(float* a);
    void bitrv208(float* a);
    void cftf1st(int n, float* a, float* w);
    void cftrec4(int n, float* a, int nw, float* w);
    void cftleaf(int n, int isplt, float* a, int nw, float* w);
    void cftfx41(int n, float* a, int nw, float* w);
    void cftf161(float* a, float* w);
    void cftf081(float* a, float* w);
    void cftf040(float* a);
    void cftx020(float* a);
#ifdef USE_CDFT_THREADS
    void cftrec4_th(int n, float* a, int nw, float* w);
#endif /* USE_CDFT_THREADS */

    if (n > 8) {
        if (n > 32) {
            cftf1st(n, a, &w[nw - (n >> 2)]);
#ifdef USE_CDFT_THREADS
            if (n > CDFT_THREADS_BEGIN_N) {
                cftrec4_th(n, a, nw, w);
            }
            else
#endif /* USE_CDFT_THREADS */
                if (n > 512) {
                    cftrec4(n, a, nw, w);
                }
                else if (n > 128) {
                    cftleaf(n, 1, a, nw, w);
                }
                else {
                    cftfx41(n, a, nw, w);
                }
            bitrv2(n, ip, a);
        }
        else if (n == 32) {
            cftf161(a, &w[nw - 8]);
            bitrv216(a);
        }
        else {
            cftf081(a, w);
            bitrv208(a);
        }
    }
    else if (n == 8) {
        cftf040(a);
    }
    else if (n == 4) {
        cftx020(a);
    }
}

static void bitrv2conj(int n, int* ip, float* a)
{
    int j, j1, k, k1, l, m, nh, nm;
    float xr, xi, yr, yi;

    m = 1;
    for (l = n >> 2; l > 8; l >>= 2) {
        m <<= 1;
    }
    nh = n >> 1;
    nm = 4 * m;
    if (l == 8) {
        for (k = 0; k < m; k++) {
            for (j = 0; j < k; j++) {
                j1 = 4 * j + 2 * ip[m + k];
                k1 = 4 * k + 2 * ip[m + j];
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += 2 * nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 -= nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += 2 * nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nh;
                k1 += 2;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= 2 * nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 += nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= 2 * nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += 2;
                k1 += nh;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += 2 * nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 -= nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += 2 * nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nh;
                k1 -= 2;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= 2 * nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 += nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= 2 * nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
            }
            k1 = 4 * k + 2 * ip[m + k];
            j1 = k1 + 2;
            k1 += nh;
            a[j1 - 1] = -a[j1 - 1];
            xr = a[j1];
            xi = -a[j1 + 1];
            yr = a[k1];
            yi = -a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            a[k1 + 3] = -a[k1 + 3];
            j1 += nm;
            k1 += 2 * nm;
            xr = a[j1];
            xi = -a[j1 + 1];
            yr = a[k1];
            yi = -a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += nm;
            k1 -= nm;
            xr = a[j1];
            xi = -a[j1 + 1];
            yr = a[k1];
            yi = -a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 -= 2;
            k1 -= nh;
            xr = a[j1];
            xi = -a[j1 + 1];
            yr = a[k1];
            yi = -a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 += nh + 2;
            k1 += nh + 2;
            xr = a[j1];
            xi = -a[j1 + 1];
            yr = a[k1];
            yi = -a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            j1 -= nh - nm;
            k1 += 2 * nm - 2;
            a[j1 - 1] = -a[j1 - 1];
            xr = a[j1];
            xi = -a[j1 + 1];
            yr = a[k1];
            yi = -a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            a[k1 + 3] = -a[k1 + 3];
        }
    }
    else {
        for (k = 0; k < m; k++) {
            for (j = 0; j < k; j++) {
                j1 = 4 * j + ip[m + k];
                k1 = 4 * k + ip[m + j];
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nh;
                k1 += 2;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += 2;
                k1 += nh;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 += nm;
                k1 += nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nh;
                k1 -= 2;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
                j1 -= nm;
                k1 -= nm;
                xr = a[j1];
                xi = -a[j1 + 1];
                yr = a[k1];
                yi = -a[k1 + 1];
                a[j1] = yr;
                a[j1 + 1] = yi;
                a[k1] = xr;
                a[k1 + 1] = xi;
            }
            k1 = 4 * k + ip[m + k];
            j1 = k1 + 2;
            k1 += nh;
            a[j1 - 1] = -a[j1 - 1];
            xr = a[j1];
            xi = -a[j1 + 1];
            yr = a[k1];
            yi = -a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            a[k1 + 3] = -a[k1 + 3];
            j1 += nm;
            k1 += nm;
            a[j1 - 1] = -a[j1 - 1];
            xr = a[j1];
            xi = -a[j1 + 1];
            yr = a[k1];
            yi = -a[k1 + 1];
            a[j1] = yr;
            a[j1 + 1] = yi;
            a[k1] = xr;
            a[k1 + 1] = xi;
            a[k1 + 3] = -a[k1 + 3];
        }
    }
}

static void bitrv216neg(float* a)
{
    float x1r, x1i, x2r, x2i, x3r, x3i, x4r, x4i,
        x5r, x5i, x6r, x6i, x7r, x7i, x8r, x8i,
        x9r, x9i, x10r, x10i, x11r, x11i, x12r, x12i,
        x13r, x13i, x14r, x14i, x15r, x15i;

    x1r = a[2];
    x1i = a[3];
    x2r = a[4];
    x2i = a[5];
    x3r = a[6];
    x3i = a[7];
    x4r = a[8];
    x4i = a[9];
    x5r = a[10];
    x5i = a[11];
    x6r = a[12];
    x6i = a[13];
    x7r = a[14];
    x7i = a[15];
    x8r = a[16];
    x8i = a[17];
    x9r = a[18];
    x9i = a[19];
    x10r = a[20];
    x10i = a[21];
    x11r = a[22];
    x11i = a[23];
    x12r = a[24];
    x12i = a[25];
    x13r = a[26];
    x13i = a[27];
    x14r = a[28];
    x14i = a[29];
    x15r = a[30];
    x15i = a[31];
    a[2] = x15r;
    a[3] = x15i;
    a[4] = x7r;
    a[5] = x7i;
    a[6] = x11r;
    a[7] = x11i;
    a[8] = x3r;
    a[9] = x3i;
    a[10] = x13r;
    a[11] = x13i;
    a[12] = x5r;
    a[13] = x5i;
    a[14] = x9r;
    a[15] = x9i;
    a[16] = x1r;
    a[17] = x1i;
    a[18] = x14r;
    a[19] = x14i;
    a[20] = x6r;
    a[21] = x6i;
    a[22] = x10r;
    a[23] = x10i;
    a[24] = x2r;
    a[25] = x2i;
    a[26] = x12r;
    a[27] = x12i;
    a[28] = x4r;
    a[29] = x4i;
    a[30] = x8r;
    a[31] = x8i;
}

static void bitrv208neg(float* a)
{
    float x1r, x1i, x2r, x2i, x3r, x3i, x4r, x4i,
        x5r, x5i, x6r, x6i, x7r, x7i;

    x1r = a[2];
    x1i = a[3];
    x2r = a[4];
    x2i = a[5];
    x3r = a[6];
    x3i = a[7];
    x4r = a[8];
    x4i = a[9];
    x5r = a[10];
    x5i = a[11];
    x6r = a[12];
    x6i = a[13];
    x7r = a[14];
    x7i = a[15];
    a[2] = x7r;
    a[3] = x7i;
    a[4] = x3r;
    a[5] = x3i;
    a[6] = x5r;
    a[7] = x5i;
    a[8] = x1r;
    a[9] = x1i;
    a[10] = x6r;
    a[11] = x6i;
    a[12] = x2r;
    a[13] = x2i;
    a[14] = x4r;
    a[15] = x4i;
}

static void cftb1st(int n, float* a, float* w)
{
    int j, j0, j1, j2, j3, k, m, mh;
    float wn4r, csc1, csc3, wk1r, wk1i, wk3r, wk3i,
        wd1r, wd1i, wd3r, wd3i;
    float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i,
        y0r, y0i, y1r, y1i, y2r, y2i, y3r, y3i;

    mh = n >> 3;
    m = 2 * mh;
    j1 = m;
    j2 = j1 + m;
    j3 = j2 + m;
    x0r = a[0] + a[j2];
    x0i = -a[1] - a[j2 + 1];
    x1r = a[0] - a[j2];
    x1i = -a[1] + a[j2 + 1];
    x2r = a[j1] + a[j3];
    x2i = a[j1 + 1] + a[j3 + 1];
    x3r = a[j1] - a[j3];
    x3i = a[j1 + 1] - a[j3 + 1];
    a[0] = x0r + x2r;
    a[1] = x0i - x2i;
    a[j1] = x0r - x2r;
    a[j1 + 1] = x0i + x2i;
    a[j2] = x1r + x3i;
    a[j2 + 1] = x1i + x3r;
    a[j3] = x1r - x3i;
    a[j3 + 1] = x1i - x3r;
    wn4r = w[1];
    csc1 = w[2];
    csc3 = w[3];
    wd1r = 1;
    wd1i = 0;
    wd3r = 1;
    wd3i = 0;
    k = 0;
    for (j = 2; j < mh - 2; j += 4) {
        k += 4;
        wk1r = csc1 * (wd1r + w[k]);
        wk1i = csc1 * (wd1i + w[k + 1]);
        wk3r = csc3 * (wd3r + w[k + 2]);
        wk3i = csc3 * (wd3i + w[k + 3]);
        wd1r = w[k];
        wd1i = w[k + 1];
        wd3r = w[k + 2];
        wd3i = w[k + 3];
        j1 = j + m;
        j2 = j1 + m;
        j3 = j2 + m;
        x0r = a[j] + a[j2];
        x0i = -a[j + 1] - a[j2 + 1];
        x1r = a[j] - a[j2];
        x1i = -a[j + 1] + a[j2 + 1];
        y0r = a[j + 2] + a[j2 + 2];
        y0i = -a[j + 3] - a[j2 + 3];
        y1r = a[j + 2] - a[j2 + 2];
        y1i = -a[j + 3] + a[j2 + 3];
        x2r = a[j1] + a[j3];
        x2i = a[j1 + 1] + a[j3 + 1];
        x3r = a[j1] - a[j3];
        x3i = a[j1 + 1] - a[j3 + 1];
        y2r = a[j1 + 2] + a[j3 + 2];
        y2i = a[j1 + 3] + a[j3 + 3];
        y3r = a[j1 + 2] - a[j3 + 2];
        y3i = a[j1 + 3] - a[j3 + 3];
        a[j] = x0r + x2r;
        a[j + 1] = x0i - x2i;
        a[j + 2] = y0r + y2r;
        a[j + 3] = y0i - y2i;
        a[j1] = x0r - x2r;
        a[j1 + 1] = x0i + x2i;
        a[j1 + 2] = y0r - y2r;
        a[j1 + 3] = y0i + y2i;
        x0r = x1r + x3i;
        x0i = x1i + x3r;
        a[j2] = wk1r * x0r - wk1i * x0i;
        a[j2 + 1] = wk1r * x0i + wk1i * x0r;
        x0r = y1r + y3i;
        x0i = y1i + y3r;
        a[j2 + 2] = wd1r * x0r - wd1i * x0i;
        a[j2 + 3] = wd1r * x0i + wd1i * x0r;
        x0r = x1r - x3i;
        x0i = x1i - x3r;
        a[j3] = wk3r * x0r + wk3i * x0i;
        a[j3 + 1] = wk3r * x0i - wk3i * x0r;
        x0r = y1r - y3i;
        x0i = y1i - y3r;
        a[j3 + 2] = wd3r * x0r + wd3i * x0i;
        a[j3 + 3] = wd3r * x0i - wd3i * x0r;
        j0 = m - j;
        j1 = j0 + m;
        j2 = j1 + m;
        j3 = j2 + m;
        x0r = a[j0] + a[j2];
        x0i = -a[j0 + 1] - a[j2 + 1];
        x1r = a[j0] - a[j2];
        x1i = -a[j0 + 1] + a[j2 + 1];
        y0r = a[j0 - 2] + a[j2 - 2];
        y0i = -a[j0 - 1] - a[j2 - 1];
        y1r = a[j0 - 2] - a[j2 - 2];
        y1i = -a[j0 - 1] + a[j2 - 1];
        x2r = a[j1] + a[j3];
        x2i = a[j1 + 1] + a[j3 + 1];
        x3r = a[j1] - a[j3];
        x3i = a[j1 + 1] - a[j3 + 1];
        y2r = a[j1 - 2] + a[j3 - 2];
        y2i = a[j1 - 1] + a[j3 - 1];
        y3r = a[j1 - 2] - a[j3 - 2];
        y3i = a[j1 - 1] - a[j3 - 1];
        a[j0] = x0r + x2r;
        a[j0 + 1] = x0i - x2i;
        a[j0 - 2] = y0r + y2r;
        a[j0 - 1] = y0i - y2i;
        a[j1] = x0r - x2r;
        a[j1 + 1] = x0i + x2i;
        a[j1 - 2] = y0r - y2r;
        a[j1 - 1] = y0i + y2i;
        x0r = x1r + x3i;
        x0i = x1i + x3r;
        a[j2] = wk1i * x0r - wk1r * x0i;
        a[j2 + 1] = wk1i * x0i + wk1r * x0r;
        x0r = y1r + y3i;
        x0i = y1i + y3r;
        a[j2 - 2] = wd1i * x0r - wd1r * x0i;
        a[j2 - 1] = wd1i * x0i + wd1r * x0r;
        x0r = x1r - x3i;
        x0i = x1i - x3r;
        a[j3] = wk3i * x0r + wk3r * x0i;
        a[j3 + 1] = wk3i * x0i - wk3r * x0r;
        x0r = y1r - y3i;
        x0i = y1i - y3r;
        a[j3 - 2] = wd3i * x0r + wd3r * x0i;
        a[j3 - 1] = wd3i * x0i - wd3r * x0r;
    }
    wk1r = csc1 * (wd1r + wn4r);
    wk1i = csc1 * (wd1i + wn4r);
    wk3r = csc3 * (wd3r - wn4r);
    wk3i = csc3 * (wd3i - wn4r);
    j0 = mh;
    j1 = j0 + m;
    j2 = j1 + m;
    j3 = j2 + m;
    x0r = a[j0 - 2] + a[j2 - 2];
    x0i = -a[j0 - 1] - a[j2 - 1];
    x1r = a[j0 - 2] - a[j2 - 2];
    x1i = -a[j0 - 1] + a[j2 - 1];
    x2r = a[j1 - 2] + a[j3 - 2];
    x2i = a[j1 - 1] + a[j3 - 1];
    x3r = a[j1 - 2] - a[j3 - 2];
    x3i = a[j1 - 1] - a[j3 - 1];
    a[j0 - 2] = x0r + x2r;
    a[j0 - 1] = x0i - x2i;
    a[j1 - 2] = x0r - x2r;
    a[j1 - 1] = x0i + x2i;
    x0r = x1r + x3i;
    x0i = x1i + x3r;
    a[j2 - 2] = wk1r * x0r - wk1i * x0i;
    a[j2 - 1] = wk1r * x0i + wk1i * x0r;
    x0r = x1r - x3i;
    x0i = x1i - x3r;
    a[j3 - 2] = wk3r * x0r + wk3i * x0i;
    a[j3 - 1] = wk3r * x0i - wk3i * x0r;
    x0r = a[j0] + a[j2];
    x0i = -a[j0 + 1] - a[j2 + 1];
    x1r = a[j0] - a[j2];
    x1i = -a[j0 + 1] + a[j2 + 1];
    x2r = a[j1] + a[j3];
    x2i = a[j1 + 1] + a[j3 + 1];
    x3r = a[j1] - a[j3];
    x3i = a[j1 + 1] - a[j3 + 1];
    a[j0] = x0r + x2r;
    a[j0 + 1] = x0i - x2i;
    a[j1] = x0r - x2r;
    a[j1 + 1] = x0i + x2i;
    x0r = x1r + x3i;
    x0i = x1i + x3r;
    a[j2] = wn4r * (x0r - x0i);
    a[j2 + 1] = wn4r * (x0i + x0r);
    x0r = x1r - x3i;
    x0i = x1i - x3r;
    a[j3] = -wn4r * (x0r + x0i);
    a[j3 + 1] = -wn4r * (x0i - x0r);
    x0r = a[j0 + 2] + a[j2 + 2];
    x0i = -a[j0 + 3] - a[j2 + 3];
    x1r = a[j0 + 2] - a[j2 + 2];
    x1i = -a[j0 + 3] + a[j2 + 3];
    x2r = a[j1 + 2] + a[j3 + 2];
    x2i = a[j1 + 3] + a[j3 + 3];
    x3r = a[j1 + 2] - a[j3 + 2];
    x3i = a[j1 + 3] - a[j3 + 3];
    a[j0 + 2] = x0r + x2r;
    a[j0 + 3] = x0i - x2i;
    a[j1 + 2] = x0r - x2r;
    a[j1 + 3] = x0i + x2i;
    x0r = x1r + x3i;
    x0i = x1i + x3r;
    a[j2 + 2] = wk1i * x0r - wk1r * x0i;
    a[j2 + 3] = wk1i * x0i + wk1r * x0r;
    x0r = x1r - x3i;
    x0i = x1i - x3r;
    a[j3 + 2] = wk3i * x0r + wk3r * x0i;
    a[j3 + 3] = wk3i * x0i - wk3r * x0r;
}

static void cftb040(float* a)
{
    float x0r, x0i, x1r, x1i, x2r, x2i, x3r, x3i;

    x0r = a[0] + a[4];
    x0i = a[1] + a[5];
    x1r = a[0] - a[4];
    x1i = a[1] - a[5];
    x2r = a[2] + a[6];
    x2i = a[3] + a[7];
    x3r = a[2] - a[6];
    x3i = a[3] - a[7];
    a[0] = x0r + x2r;
    a[1] = x0i + x2i;
    a[2] = x1r + x3i;
    a[3] = x1i - x3r;
    a[4] = x0r - x2r;
    a[5] = x0i - x2i;
    a[6] = x1r - x3i;
    a[7] = x1i + x3r;
}

static void cftbsub(int n, float* a, int* ip, int nw, float* w)
{
    void bitrv2conj(int n, int* ip, float* a);
    void bitrv216neg(float* a);
    void bitrv208neg(float* a);
    void cftb1st(int n, float* a, float* w);
    void cftrec4(int n, float* a, int nw, float* w);
    void cftleaf(int n, int isplt, float* a, int nw, float* w);
    void cftfx41(int n, float* a, int nw, float* w);
    void cftf161(float* a, float* w);
    void cftf081(float* a, float* w);
    void cftb040(float* a);
    void cftx020(float* a);
#ifdef USE_CDFT_THREADS
    void cftrec4_th(int n, float* a, int nw, float* w);
#endif /* USE_CDFT_THREADS */

    if (n > 8) {
        if (n > 32) {
            cftb1st(n, a, &w[nw - (n >> 2)]);
#ifdef USE_CDFT_THREADS
            if (n > CDFT_THREADS_BEGIN_N) {
                cftrec4_th(n, a, nw, w);
            }
            else
#endif /* USE_CDFT_THREADS */
                if (n > 512) {
                    cftrec4(n, a, nw, w);
                }
                else if (n > 128) {
                    cftleaf(n, 1, a, nw, w);
                }
                else {
                    cftfx41(n, a, nw, w);
                }
            bitrv2conj(n, ip, a);
        }
        else if (n == 32) {
            cftf161(a, &w[nw - 8]);
            bitrv216neg(a);
        }
        else {
            cftf081(a, w);
            bitrv208neg(a);
        }
    }
    else if (n == 8) {
        cftb040(a);
    }
    else if (n == 4) {
        cftx020(a);
    }
}

static void rftfsub(int n, float* a, int nc, float* c)
{
    int j, k, kk, ks, m;
    float wkr, wki, xr, xi, yr, yi;

    m = n >> 1;
    ks = 2 * nc / m;
    kk = 0;
    for (j = 2; j < m; j += 2) {
        k = n - j;
        kk += ks;
        wkr = 0.5 - c[nc - kk];
        wki = c[kk];
        xr = a[j] - a[k];
        xi = a[j + 1] + a[k + 1];
        yr = wkr * xr - wki * xi;
        yi = wkr * xi + wki * xr;
        a[j] -= yr;
        a[j + 1] -= yi;
        a[k] += yr;
        a[k + 1] -= yi;
    }
}

static void rftbsub(int n, float* a, int nc, float* c)
{
    int j, k, kk, ks, m;
    float wkr, wki, xr, xi, yr, yi;

    m = n >> 1;
    ks = 2 * nc / m;
    kk = 0;
    for (j = 2; j < m; j += 2) {
        k = n - j;
        kk += ks;
        wkr = 0.5 - c[nc - kk];
        wki = c[kk];
        xr = a[j] - a[k];
        xi = a[j + 1] + a[k + 1];
        yr = wkr * xr + wki * xi;
        yi = wkr * xi - wki * xr;
        a[j] -= yr;
        a[j + 1] -= yi;
        a[k] += yr;
        a[k + 1] -= yi;
    }
}

static void rdft(int n, int isgn, float* a, int* ip, float* w)
{
    void makewt(int nw, int* ip, float* w);
    void makect(int nc, int* ip, float* c);
    void cftfsub(int n, float* a, int* ip, int nw, float* w);
    void cftbsub(int n, float* a, int* ip, int nw, float* w);
    void rftfsub(int n, float* a, int nc, float* c);
    void rftbsub(int n, float* a, int nc, float* c);
    int nw, nc;
    float xi;

    nw = ip[0];
    if (n > (nw << 2)) {
        nw = n >> 2;
        makewt(nw, ip, w);
    }
    nc = ip[1];
    if (n > (nc << 2)) {
        nc = n >> 2;
        makect(nc, ip, w + nw);
    }
    if (isgn >= 0) {
        if (n > 4) {
            cftfsub(n, a, ip, nw, w);
            rftfsub(n, a, nc, w + nw);
        }
        else if (n == 4) {
            cftfsub(n, a, ip, nw, w);
        }
        xi = a[0] - a[1];
        a[0] += a[1];
        a[1] = xi;
    }
    else {
        a[1] = 0.5 * (a[0] - a[1]);
        a[0] -= a[1];
        if (n > 4) {
            rftbsub(n, a, nc, w + nw);
            cftbsub(n, a, ip, nw, w);
        }
        else if (n == 4) {
            cftbsub(n, a, ip, nw, w);
        }
    }
}

// input array (any shape >= 1D)
// output array (shape = input.shape.replace(axis, n).insert(0,2))
// d0 = input.shape.step(axis)
// d1 = input.shape.size(axis)
// d2 = input.shape.slot(axis)
static inline void rfft_libfft_f32(
    const float* restrict input,
    float* restrict output,
    int d0, int d1, int d2,
    int32_t* restrict temp_ip, float* restrict temp_w, float* restrict temp_a)
{
    void rdft(int n, int isgn, float* a, int* ip, float* w);

    int d3 = d0 * d1;
    int d_out = (d1 >> 1) + 1;

    for (int k = 0; k < d2; k++)
    {
        int dk = k * d3;
        int dm = k * 2 * d_out * d0;
        for (int i = 0; i < d0; i++)
        {
            for (int j = 0; j < d1; j++)
            {
                temp_a[j] = input[dk + j * d0 + i];
            }
            rdft(d1, 1, temp_a, (int*)temp_ip, temp_w);

            for (int m = 2; m < d1; m += 2)
            {
                int index = (m * d0) + 2 * i + dm;
                output[index] = temp_a[m];
                output[index + 1] = -temp_a[m + 1];
            }
            int beta = dm + 2 * i;
            output[beta] = temp_a[0];
            output[beta + 1] = 0;
            output[beta + d3] = temp_a[1];
            output[beta + d3 + 1] = 0;
        }
    }
}

static inline float __norm_sqrt_sum_f32(const float* restrict input, int count)
{
    float sum = 0;
    for (int j = 0; j < count; j++) {
        float item = *input++;
        sum += item * item;
    }
    return sqrtf(sum);
}

static inline void norm_f32(const float* restrict input, int d1, int d2, float* restrict output)
{
    for (int k = 0; k < d2; k++) {
        *output++ = __norm_sqrt_sum_f32(input, d1);
        input += d1;
    }
}

static inline float __mel_f32(const float* restrict input, const short* restrict filter_points, int filter)
{
    short n0 = filter_points[filter];
    short n1 = filter_points[filter + 1];
    short n2 = filter_points[filter + 2];
    short c0 = n1 - n0;
    short c1 = n2 - n1;
    float sum = 0;

    for (int i = 0; i <= c0; i++) {
        float rate = i / (float)c0;
        float value = input[i + n0];
        sum += value * rate;
    }

    for (int i = 1; i <= c1; i++) {
        float rate = i / (float)c1;
        float value = input[i + n1];
        sum += value * (1.0 - rate);
    }

    return sum;
}

// input array (any shape >= 1D)
// output array (same shape as input array except with 0 replaced with num_filter)
// size = input.shape.size(0)
// slot = input.shape.slot(0)
static inline void mel_f32(const float* restrict input, const short* restrict filter_points, int size, int slot, int num_filter, float* restrict output)
{
    for (int k = 0; k < slot; k++) {
        const float* ip = input + k * size;
        for (int i = 0; i < num_filter; i++) {
            *output++ = __mel_f32(ip, filter_points, i);
        }
    }
}

static inline void addi_f32(
    const float* restrict x,
    int count,
    float immediate,
    float* restrict output)
{
    for (int i = 0; i < count; i++) {
        output[i] = x[i] + immediate;
    }
}

static inline void ln_f32(const float* restrict x, int count, float* restrict result)
{
    for (int i = 0; i < count; i++) {
        *result++ = logf(*x++);
    }
}

static inline void clip_f32(const float* restrict input, int count, float min, float max, float* restrict output)
{
    for (int i = 0; i < count; i++) {
        float value = input[i];
        if (value > max)
            value = max;
        if (value < min)
            value = min;

        output[i] = value;
    }
}

/**
 * Enqueue handle->input_size values from given *data pointer to internal window buffer.
 *
 * @param handle Pointer to an initialized handle.
 * @param data Data to enqueue.
 * @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_ERROR (-2) if internal buffer is out of memory.
 */
static inline int fixwin_enqueue(void* restrict handle, const void* restrict data)
{
    fixwin_t* fep = (fixwin_t*)handle;

    if (cbuffer_enqueue(&fep->data_buffer, data, fep->input_size) != 0)
        return IPWIN_RET_ERROR;

    return IPWIN_RET_SUCCESS;
}

static inline float conv_mac_f32(const float* restrict a, const float* restrict b, int count)
{
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += *a++ * *b++;
    }
    return sum;
}

static inline void conv1d_flat_f32(
    const float* restrict input,
    const float* restrict weight,
    float* restrict output,
    int top,
    int bottom,
    int n_output_rows,
    int filters,
    int strides,
    int kernel_size)
{
    for (int i = 0; i < n_output_rows; i++) {
        const float* wp = weight;		// Weight matrix
        const float* bp = input;		// Input matrix
        const int step = i * strides;	// Row size
        int len = kernel_size;			// Normally do one kernel

        int skip = top - step;			// Pad top?
        if (skip > 0) {
            len -= skip;				// Trim kernel length
            wp += skip;					// Advance kernel
        }
        else {						// No top padding,
            bp -= skip;					// Rollback input
        }

        skip = step + len - bottom;		// Pad bottom?
        if (skip > 0)
            len -= skip;				// Just cut the kernel at end

        float* op = output + i * filters;
        for (int j = 0; j < filters; j++) {
            *op++ = conv_mac_f32(wp + j * kernel_size, bp, len);
        }
    }
}

static inline void add_f32(
    const float* restrict a,
    const float* restrict b,
    int l, int g1, int m, int g2, int r,
    float* restrict output)
{
    int index = 0;
    for (int x = 0; x < l; x++) {
        for (int i = 0; i < g1; i++) {
            for (int y = 0; y < m; y++) {
                for (int j = 0; j < g2; j++) {
                    for (int z = 0; z < r; z++) {
                        output[index] = a[index] + b[x * m * r + y * r + z];
                        index++;
                    }
                }
            }
        }
    }
}

static inline void relu_f32(const float* restrict x, int count, float* restrict result)
{
    for (int i = 0; i < count; i++) {
        const float value = *x++;
        *result++ = value > 0 ? value : 0;
    }
}

static inline float maxpool1d_f32_max(const float* restrict x, int ncols, int pool_size)
{
    float max = -FLT_MAX;
    for (int i = 0; i < pool_size; i++) {
        const float value = *(x + i * ncols);
        if (value > max)
            max = value;
    }
    return max;
}

static inline void maxpool1d_f32_row(const float* restrict x, int pool_size, int ncols, float* restrict result)
{
    for (int i = 0; i < ncols; i++) {
        const float* xp = x + i;
        *result++ = maxpool1d_f32_max(xp, ncols, pool_size);
    }
}

static inline void maxpool1d_valid_f32(
    const float* restrict input,
    int pool_size,
    int strides,
    int ncols,
    int n_output_rows,
    float* restrict result)
{
    int input_pointer_step = ncols * strides;

    for (int i = 0; i < n_output_rows; i++) {
        const float* input_current = input + (i * input_pointer_step);
        float* rp = result + (i * ncols);
        maxpool1d_f32_row(input_current, pool_size, ncols, rp);
    }
}

static inline float _globav1d_f32_mean(const float* restrict x, int nchannel, int nsteps)
{
    float mean = 0.0;
    for (int i = 0; i < nsteps; i++) {
        const float value = *(x + i * nchannel);
        mean = mean + value;
    }
    mean = mean / (float)nsteps;
    return mean;
}

static inline void globav1d_f32(const float* restrict x, int nsteps, int nchannel, float* restrict result)
{
    // Loop over all channels
    for (int i = 0; i < nchannel; i++) {
        const float* xp = x + i;
        *result++ = _globav1d_f32_mean(xp, nchannel, nsteps);
    }
}

static inline float dot_mac_f32(const float* restrict a, const float* restrict b, int count)
{
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += *a++ * *b++;
    }
    return sum;
}

static inline void dott_f32(const float* restrict a, const float* restrict b, float* restrict out, int d0, int d1, int d2)
{
    for (int i = 0; i < d2; i++) {
        float* op = out;
        for (int j = 0; j < d1; j++) {
            *op++ = dot_mac_f32(a + j * d0, b, d0);
        }
        out += d1;
        b += d0;
    }
}

static inline void softmax_f32(const float* restrict x, int count, float* restrict result)
{
    float sum = 0;
    for (int i = 0; i < count; i++) {
        float value = expf(x[i]);
        sum += value;
        result[i] = value;
    }
    for (int i = 0; i < count; i++) {
        result[i] /= sum;
    }
}

/**
* Initializes a fixwin sampler handle.
*
* @param handle Pointer to a preallocated memory area of fixwin_handle_size() bytes to initialize.
*
* @param input_size Number of bytes to enqueue.
* @param count Number of items (of size input_size) in each window
*/
static inline void fixwin_init(void* restrict handle, int input_size, int count)
{
    fixwin_t* fep = (fixwin_t*)handle;
    fep->input_size = input_size;

    char* mem = ((char*)handle) + sizeof(fixwin_t);

    int data_buffer = input_size * count;

    cbuffer_init(&fep->data_buffer, mem, data_buffer);
}

#define __RETURN_ERROR(_exp) do { int __ret = (_exp); if(__ret < 0) return __ret; } while(0)
#define __RETURN_ALWAYS(_exp) return (_exp)
#define __RETURN_ERROR_BREAK_EMPTY(_exp) {  int __ret = (_exp); if(__ret == -1) break; if(__ret < 0) return __ret; }
#define __RETURN_ERROR_BREAK_EMPTY_END(_exp) {  int __ret = (_exp); if(__ret == -1 || __ret == -3) break; if(__ret < 0) return __ret; }
#define __RETURN_ERROR_CANCEL_EMPTY(_exp) {  int __ret = (_exp); if(__ret == -1) return 0; if(__ret < 0) return __ret; }
#define __BREAK_ERROR(_exp) {  int __ret = (_exp); if(__ret < 0) break; }

/*
* Try read data from model.
*
*  @param dataout Output Features. Output float[3].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/ 
int IMAI_dequeue(float* restrict dataout) {
    while (1) {
        __RETURN_ERROR_BREAK_EMPTY(fixwin_dequeue(_K2, _K1, 512, 160));
        hammingmul_f32(_K1, _K6, 1, 512, 1, _K10);
        rfft_libfft_f32(_K10, _K11, 1, 512, 1, _K13, _K14, _K15);
        norm_f32(_K11, 2, 257, _K17);
        mel_f32(_K17, _K18, 257, 1, 40, _K22);
        addi_f32(_K22, 40, 1, _K23);
        ln_f32(_K23, 40, _K24);
        clip_f32(_K24, 40, 0, 4, _K3);
        __RETURN_ERROR_BREAK_EMPTY(fixwin_enqueue(_K5, _K3));
    }
    __RETURN_ERROR(fixwin_dequeue(_K5, _K4, 50, 7));
    conv1d_flat_f32(_K4, _K25, _K26, 0, 2000, 25, 12, 80, 120);
    add_f32(_K26, _K27, 1, 1, 1, 25, 12, _K28);
    relu_f32(_K28, 300, _K29);
    conv1d_flat_f32(_K29, _K30, _K31, 12, 312, 25, 24, 12, 36);
    conv1d_flat_f32(_K31, _K32, _K33, 24, 624, 25, 24, 24, 72);
    add_f32(_K33, _K34, 1, 1, 1, 25, 24, _K35);
    relu_f32(_K35, 600, _K36);
    maxpool1d_valid_f32(_K36, 2, 2, 24, 12, _K38);
    conv1d_flat_f32(_K38, _K39, _K40, 24, 312, 12, 32, 24, 72);
    conv1d_flat_f32(_K40, _K41, _K42, 32, 416, 12, 32, 32, 96);
    add_f32(_K42, _K43, 1, 1, 1, 12, 32, _K44);
    relu_f32(_K44, 384, _K45);
    maxpool1d_valid_f32(_K45, 2, 2, 32, 6, _K47);
    globav1d_f32(_K47, 6, 32, _K48);
    dott_f32(_K49, _K48, _K50, 32, 3, 1);
    add_f32(_K50, _K51, 1, 1, 1, 1, 3, _K52);
    softmax_f32(_K52, 3, dataout);
    return 0;
}

/*
* Try write data to model.
*
*  @param datain Input features. Input float[1].
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/
int IMAI_enqueue(const float* restrict datain) {
    __RETURN_ERROR(fixwin_enqueue(_K2, datain));
    return 0;
}

/*
* Batch enqueue - slightly better performance than calling IMAI_enqueue repeatedly.
*/
/*
int IMAI_enqueue_batch(const float* restrict datain, int frame_count) {
    fixwin_t* fep = (fixwin_t*)_K2;

    if (cbuffer_enqueue(&fep->data_buffer, datain, fep->input_size * frame_count) != 0)
        return IPWIN_RET_ERROR;

    return IPWIN_RET_SUCCESS;
} 
*/

/*
* Get the number of times IMAI_enqueue may be called before IMAI_dequeue must be called.
*
*  @return Number of frames the model currently accepts.
*/
int IMAI_enqueue_batch_max_frames() {
    fixwin_t* fep = (fixwin_t*)_K2;

    int accepting_frames = cbuffer_get_free(&fep->data_buffer) / fep->input_size;

    return accepting_frames;
}


/*
* Closes and flushes streams, free any heap allocated memory.
*
*/
void IMAI_finalize(void) {
}

/*
* Initializes buffers to initial state.
*
*  @return IPWIN_RET_SUCCESS (0) or IPWIN_RET_NODATA (-1), IPWIN_RET_ERROR (-2), IPWIN_RET_STREAMEND (-3)
*/
int IMAI_init(void) {
    fixwin_init(_K2, 4, 512);
    fixwin_init(_K5, 160, 50);
    return 0;
}

#ifdef IMAI_REFLECTION

static IMAI_api_def _IMAI_api_def = {
    api_ver: 1,
    id : {0xfc, 0x4f, 0x7d, 0x61, 0x1b, 0x75, 0xdd, 0x46, 0xac, 0x09, 0x70, 0x91, 0x64, 0x1a, 0x26, 0xf7},
    api_type : IMAI_API_TYPE_QUEUE,
    prefix : "IMAI_",
    buffer_mem : {
        size: 10256,
        peak_usage : 9200,
    },
    static_mem : {
        size: 11592,
        peak_usage : 11592,
    },
    readonly_mem : {
        size: 40432,
        peak_usage : 40432,
    },
    func_count : 4,
    func_list : (IMAI_func_def[]) {
        {
            name: "IMAI_dequeue",
            description : "Try read data from model.",
            fn_ptr : IMAI_dequeue,
            attrib : 3,
            param_count : 1,
            param_list : (IMAI_param_def[]) {
                {
                    name: "dataout",
                    attrib : IMAI_PARAM_OUTPUT,
                    rank : 1,
                    shape : (IMAI_shape_dim[]) {
                        {
                            name: "Labels",
                            size : 3,
                            labels : (label_text_t[]) { "unlabelled","down","up" },
                        },
                    },
                    count: 3,
                    type_id : IMAGINET_TYPES_FLOAT32,
                    frequency : 14.285714285714286,
                    shift : 3,
                    scale : 1,
                    offset : 0,
                },
            },
        },
        {
            name: "IMAI_enqueue",
            description : "Try write data to model.",
            fn_ptr : IMAI_enqueue,
            attrib : 3,
            param_count : 1,
            param_list : (IMAI_param_def[]) {
                {
                    name: "datain",
                    attrib : IMAI_PARAM_INPUT,
                    rank : 1,
                    shape : (IMAI_shape_dim[]) {
                        {
                            name: "",
                            size : 1,
                        },
                    },
                    count : 1,
                    type_id : IMAGINET_TYPES_FLOAT32,
                    frequency : 16000,
                    shift : 0,
                    scale : 1,
                    offset : 0,
                },
            },
        },
        {
            name: "IMAI_finalize",
            description : "Closes and flushes streams, free any heap allocated memory.",
            fn_ptr : IMAI_finalize,
            attrib : 10,
            param_count : 0,
            param_list : (IMAI_param_def[]) {
            },
        },
        {
            name: "IMAI_init",
            description : "Initializes buffers to initial state.",
            fn_ptr : IMAI_init,
            attrib : 7,
            param_count : 0,
            param_list : (IMAI_param_def[]) {
            },
        },
    },
};

IMAI_api_def* IMAI_api(void) {
    return &_IMAI_api_def;
}

#endif /* IMAI_REFLECTION */

