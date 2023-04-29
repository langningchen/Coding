#include <vector>
#include <list>
#include <string>

const uint8_t g_stuffing[2] = {0xec, 0x11};
// g_15Bit[cel << 3 | mask]
const uint16_t g_15Bit[32] = {
    21522,
    20773,
    24188,
    23371,
    17913,
    16590,
    20375,
    19104,
    30660,
    29427,
    32170,
    30877,
    26159,
    25368,
    27713,
    26998,
    5769,
    5054,
    7399,
    6608,
    1890,
    597,
    3340,
    2107,
    13663,
    12392,
    16177,
    14854,
    9396,
    8579,
    11994,
    11245,
};
// g_verBit[ver-7]
const uint32_t g_verBit[34] = {
    0x7c94, 0x85bc, 0x9a99, 0xa4d3, 0xbbf6, 0xc762, 0xd847, 0xe60d, 0xf928,
    0x10b78, 0x1145d, 0x12a17, 0x13532, 0x149a6, 0x15683, 0x168c9, 0x177ec,
    0x18ec4, 0x191e1, 0x1afab, 0x1b08e, 0x1cc1a, 0x1d33f, 0x1ed75, 0x1f250,
    0x209d5, 0x216f0, 0x228ba, 0x2379f, 0x24b0b, 0x2542e, 0x26a64, 0x27541, 0x28c69};
// g_capBit[ver - 1][mask]
const uint16_t g_capBit[40][4] = {
    {16, 19, 9, 13}, {28, 34, 16, 22}, {44, 55, 26, 34}, {64, 80, 36, 48}, {86, 108, 46, 62}, {108, 136, 60, 76}, {124, 156, 66, 88}, {154, 194, 86, 110}, {182, 232, 100, 132}, {216, 274, 122, 154}, {254, 324, 140, 180}, {290, 370, 158, 206}, {334, 428, 180, 244}, {365, 461, 197, 261}, {415, 523, 223, 295}, {453, 589, 253, 325}, {507, 647, 283, 367}, {563, 721, 313, 397}, {627, 795, 341, 445}, {669, 861, 385, 485}, {714, 932, 406, 512}, {782, 1006, 442, 568}, {860, 1094, 464, 614}, {914, 1174, 514, 664}, {1000, 1276, 538, 718}, {1062, 1370, 596, 754}, {1128, 1468, 628, 808}, {1193, 1531, 661, 871}, {1267, 1631, 701, 911}, {1373, 1735, 745, 985}, {1455, 1843, 793, 1033}, {1541, 1955, 845, 1115}, {1631, 2071, 901, 1171}, {1725, 2191, 961, 1231}, {1812, 2306, 986, 1286}, {1914, 2434, 1054, 1354}, {1992, 2566, 1096, 1426}, {2102, 2702, 1142, 1502}, {2216, 2812, 1222, 1582}, {2334, 2956, 1276, 1666}};
// (ver < 27)? g_corCap[ver-1][ecl]:g_corCap[26][ecl]
const uint8_t g_corCap[27][4] = {
    {4, 2, 8, 6}, {8, 4, 14, 11}, {13, 7, 11, 9}, {9, 10, 8, 13}, {12, 13, 11, 9}, {8, 9, 14, 12}, {9, 10, 13, 9}, {11, 12, 13, 11}, {11, 15, 12, 10}, {13, 9, 14, 12}, {15, 10, 12, 14}, {11, 12, 14, 13}, {11, 13, 11, 12}, {12, 15, 12, 10}, {12, 11, 12, 15}, {14, 12, 15, 12}, {14, 14, 14, 14}, {13, 15, 14, 14}, {13, 14, 13, 13}, {13, 14, 14, 15}, {13, 14, 15, 14}, {14, 14, 12, 15}, {14, 15, 15, 15}, {14, 15, 15, 15}, {14, 13, 15, 15}, {14, 14, 15, 14}, {14, 15, 15, 15}};
// g_allBit[ver - 1]
const uint16_t g_allBit[40] = {
    26, 44, 70, 100, 134, 172, 196, 242, 292, 346,
    404, 466, 532, 581, 655, 733, 815, 901, 991, 1085,
    1156, 1258, 1364, 1474, 1588, 1706, 1828, 1921, 2051, 2185,
    2323, 2465, 2611, 2761, 2876, 3034, 3196, 3362, 3532, 3706};
// &g_generator_polynomial_exp[index]
const uint8_t g_generator_polynomial_exp[259] = {
    /*纠错字数 在此数组上的索引*/
    0, 87, 229, 146, 149, 238, 102, 21,                                                                                                             /*7 0*/
    0, 251, 67, 46, 61, 118, 70, 64, 94, 32, 45,                                                                                                    /*10 8*/
    0, 74, 152, 176, 100, 86, 100, 106, 104, 130, 218, 206, 140, 78,                                                                                /*13 19*/
    0, 8, 183, 61, 91, 202, 37, 51, 58, 58, 237, 140, 124, 5, 99, 105,                                                                              /*15 33*/
    0, 120, 104, 107, 109, 102, 161, 76, 3, 91, 191, 147, 169, 182, 194, 225, 120,                                                                  /*16 49*/
    0, 43, 139, 206, 78, 43, 239, 123, 206, 214, 147, 24, 99, 150, 39, 243, 163, 136,                                                               /*17 66*/
    0, 215, 234, 158, 94, 184, 97, 118, 170, 79, 187, 152, 148, 252, 179, 5, 98, 96, 153,                                                           /*18 84*/
    0, 17, 60, 79, 50, 61, 163, 26, 187, 202, 180, 221, 225, 83, 239, 156, 164, 212, 212, 188, 190,                                                 /*20 103*/
    0, 210, 171, 247, 242, 93, 230, 14, 109, 221, 53, 200, 74, 8, 172, 98, 80, 219, 134, 160, 105, 165, 231,                                        /*22 124*/
    0, 229, 121, 135, 48, 211, 117, 251, 126, 159, 180, 169, 152, 192, 226, 228, 218, 111, 0, 117, 232, 87, 96, 227, 21,                            /*24 147*/
    0, 173, 125, 158, 2, 103, 182, 118, 17, 145, 201, 111, 28, 165, 53, 161, 21, 245, 142, 13, 102, 48, 227, 153, 145, 218, 70,                     /*26 172*/
    0, 168, 223, 200, 104, 224, 234, 108, 180, 110, 190, 195, 147, 205, 27, 232, 201, 21, 43, 245, 87, 42, 195, 212, 119, 242, 37, 9, 123,          /*28*/
    0, 41, 173, 145, 152, 216, 31, 179, 182, 50, 48, 110, 86, 239, 96, 222, 125, 42, 173, 226, 193, 224, 130, 156, 37, 251, 216, 238, 40, 192, 180, /*30*/
};
// <https://www.thonky.com/qr-code-tutorial/log-antilog-table> 预先算出来的
// g_alpha_int_is_index[inte - 1]
const uint8_t g_alpha_int_is_index[255] = {0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75,
                                           4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113, 5, 138, 101, 47,
                                           225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69, 29, 181, 194, 125, 106, 39, 249, 185,
                                           201, 154, 9, 120, 77, 228, 114, 166, 6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37,
                                           179, 16, 145, 34, 136, 54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131,
                                           56, 70, 64, 30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61, 202, 94,
                                           155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87, 7, 112, 192, 247, 140, 128,
                                           99, 13, 103, 74, 222, 237, 49, 197, 254, 24, 227, 165, 153, 119, 38, 184, 180, 124, 17, 68,
                                           146, 217, 35, 32, 137, 46, 55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220,
                                           252, 190, 97, 242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162, 31, 45, 67,
                                           216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246, 108, 161, 59, 82, 41, 157, 85,
                                           170, 251, 96, 134, 177, 187, 204, 62, 90, 203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235,
                                           122, 117, 44, 215, 79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175};

// 障碍
typedef enum _InPositionPat
{
    not_in,
    left,
    normal,
    normal_left,
} InPositionPat;

typedef enum _COR_LEV
{
    M = 0,
    L = 1,
    Q = 2,
    H = 3
} COR_LEV;

typedef enum _DataCodeT
{
    // ...
    bit8 = 4 // 8位字节指示符，占4位
             // ...
} DataCodeT;

struct QRC_XY
{
    int16_t x;
    int16_t y;
    QRC_XY(int16_t x, int16_t y) : x(x), y(y){};
    QRC_XY operator+=(const QRC_XY _other)
    {
        this->x += _other.x;
        this->y += _other.y;
        return *this;
    }
};

class QRCode
{
public:
private:
    std::list<QRC_XY> alCenterxys_;
    bool *bitmap_;
    uint8_t ver_;
    uint8_t len_;
    uint8_t mask_;
    COR_LEV ecl_;
    DataCodeT type_;

public:
    QRCode(const std::string &_str, uint8_t _ver = 7, COR_LEV _ecl = M, uint8_t _mask = 5, DataCodeT type_ = bit8);
    bool get(uint8_t _x, uint8_t _y);
    bool get(QRC_XY _xy);
    void set(uint8_t _x, uint8_t _y, bool _flag);
    void set(QRC_XY _xy, bool _flag);
    uint8_t getLen(void);

private:
    void drawPosDectPatt(uint8_t _startX, uint8_t startY);
    void drawFixPatt(void);
    void drawAlignPatt(uint8_t centerX, uint8_t centerY);
    std::list<QRC_XY> getAliData(void);
    uint16_t get15Bit(void);
    void drawFormPatt(void);
    uint32_t getVerBit(void);
    void drawVerPatt(void);
    uint16_t getCapBit(void);
    uint8_t getStuff(uint16_t _index);
    std::vector<uint8_t> getDataCode(const std::string &_str);
    uint16_t getAllBit(void);
    uint16_t getCorCap(void);
    std::vector<uint8_t> getErrDataCode(const std::vector<uint8_t> &_data);
    InPositionPat inPositionPattern(QRC_XY _xy);
    QRC_XY getDeltaByXY(QRC_XY _xy);
    void drawStrPatt(const std::vector<uint8_t> _data, const std::vector<uint8_t> _errdata);
    static bool maskFunc0(QRC_XY _xy);
    static bool maskFunc1(QRC_XY _xy);
    static bool maskFunc2(QRC_XY _xy);
    static bool maskFunc3(QRC_XY _xy);
    static bool maskFunc4(QRC_XY _xy);
    static bool maskFunc5(QRC_XY _xy);
    static bool maskFunc6(QRC_XY _xy);
    static bool maskFunc7(QRC_XY _xy);
    bool (*getMaskFunc(void))(QRC_XY _xy);
    bool getMask(uint8_t _x, uint8_t _y);
    bool getMask(QRC_XY _xy);
    void drawMask(void);
    const uint8_t *getGenPolyExpByBlockErrSize(uint16_t _blockErrSize);
    uint8_t getAlphaByExp(size_t _exp);
    uint8_t getAlphaByInt(uint8_t _int);
    std::vector<uint8_t> QRC_Reed_Solomon(const std::vector<uint8_t> &_data, uint16_t _blockNum_big, uint16_t _blockNum_small, uint16_t _blockErrSize, uint16_t _blockDataSize);
};
