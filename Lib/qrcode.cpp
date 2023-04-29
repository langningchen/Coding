#include "qrcode.h"
QRCode::QRCode(const std::string &_str, uint8_t _ver, COR_LEV _ecl, uint8_t _mask, DataCodeT _type)
    : ver_(_ver), len_(4 * (this->ver_ - 1) + 21), mask_(_mask), ecl_(_ecl), bitmap_(nullptr), type_(_type)
{
    // step1:size
    this->bitmap_ = new bool[len_ * len_];
    this->alCenterxys_ = this->getAliData();
    // 一定要设置，因为有空白区域（画不到）的存在
    for (uint16_t i = 0; i < len_ * len_; i++)
        this->bitmap_[i] = false;
    // step4:string encode
    const std::vector<uint8_t> &data = this->getDataCode(_str);
    const std::vector<uint8_t> &errdata = this->getErrDataCode(data);
    // step5:string pattern
    this->drawStrPatt(data, errdata);
    this->drawMask();
    // step2:fixed pattern
    this->drawPosDectPatt(0, 0);
    this->drawPosDectPatt(0, this->len_ - 7);
    this->drawPosDectPatt(this->len_ - 7, 0);

    this->drawFixPatt();

    for (QRC_XY &xy : this->alCenterxys_)
        this->drawAlignPatt(xy.x, xy.y);
    // step3:version and format pattern
    this->drawFormPatt();
    if (this->ver_ >= 7)
        this->drawVerPatt();
}

bool QRCode::get(uint8_t _x, uint8_t _y)
{
    return this->bitmap_[_x + _y * this->len_];
}
bool QRCode::get(QRC_XY _xy)
{
    return this->get(_xy.x, _xy.y);
}
void QRCode::set(uint8_t _x, uint8_t _y, bool _flag)
{
    this->bitmap_[_x + _y * this->len_] = _flag;
}
void QRCode::set(QRC_XY _xy, bool _flag)
{
    this->set(_xy.x, _xy.y, _flag);
}

void QRCode::drawPosDectPatt(uint8_t _startX, uint8_t _startY)
{
    uint8_t i /*delta_y*/, j /*delta_x | y*/;

    // 图案
    // 1、2、6、7行
    for (i = 0; i < 2; i++)
    {
        // 2、6行 i*4+1 in [1,5]
        j = _startY + i * 4 + 1;
        this->set(_startX, j, true);
        this->set(_startX + 1, j, false);
        this->set(_startX + 2, j, false);
        this->set(_startX + 3, j, false);
        this->set(_startX + 4, j, false);
        this->set(_startX + 5, j, false);
        this->set(_startX + 6, j, true);
        // 1、7行 i*6 in [0,6]
        for (j = 0; j < 7; j++)
            this->set(_startX + j, _startY + i * 6, true);
    }
    // 3、4、5行
    for (i = 0; i < 3; i++)
    {
        this->set(_startX + 0, _startY + i + 2, true);
        this->set(_startX + 1, _startY + i + 2, false);
        this->set(_startX + 2, _startY + i + 2, true);
        this->set(_startX + 3, _startY + i + 2, true);
        this->set(_startX + 4, _startY + i + 2, true);
        this->set(_startX + 5, _startY + i + 2, false);
        this->set(_startX + 6, _startY + i + 2, true);
    }

    // 分隔符
    if (_startX == 0)
    {
        if (_startY == 0) // 左上
        {
            for (i = 0; i < 8; i++)
                this->set(7, i, false);
            for (j = 0; j < 7; j++)
                this->set(j, 7, false);
        }
        else // 左下
        {
            for (i = 0; i < 8; i++)
                this->set(7, _startY + i - 1, false);
            for (j = 0; j < 7; j++)
                this->set(j, _startY - 1, false);
        }
    }
    else // 右上
    {
        for (i = 0; i < 8; i++)
            this->set(_startX - 1, i, false);
        for (j = 0; j < 7; j++)
            this->set(_startX + j, 7, false);
    }
}

void QRCode::drawFixPatt(void)
{
    uint8_t printLen = (this->len_ - 17) / 2, i, j;
    // 行
    for (i = 0; i < printLen; i++)
    {
        this->set(9 + 2 * i, 6, false);
        this->set(10 + 2 * i, 6, true);
    }

    // 列
    for (i = 0; i < printLen; i++)
    {
        this->set(6, 9 + 2 * i, false);
        this->set(6, 10 + 2 * i, true);
    }
    // 不能忘记这一点
    this->set(8, this->len_ - 8, true);
}

void QRCode::drawAlignPatt(uint8_t _centerX, uint8_t _centerY)
{
    uint8_t i, j;
    // 1、2、4、5行
    for (i = 0; i < 2; i++)
    {
        // 1、5行
        for (j = 0; j < 5; j++)
            this->set(_centerX - 2 + j, _centerY - 2 + 4 * i, true);
        // 2、4行
        this->set(_centerX - 2, _centerY - 1 + 2 * i, true);
        this->set(_centerX - 1, _centerY - 1 + 2 * i, false);
        this->set(_centerX, _centerY - 1 + 2 * i, false);
        this->set(_centerX + 1, _centerY - 1 + 2 * i, false);
        this->set(_centerX + 2, _centerY - 1 + 2 * i, true);
    }
    // 3行
    this->set(_centerX - 2, _centerY, true);
    this->set(_centerX - 1, _centerY, false);
    this->set(_centerX, _centerY, true);
    this->set(_centerX + 1, _centerY, false);
    this->set(_centerX + 2, _centerY, true);
}

std::list<QRC_XY> QRCode::getAliData(void)
{
    std::list<QRC_XY> xy;
    if (this->ver_ == 1)
        return xy;

    uint8_t
        multy = (this->ver_ / 7 + 2),
        mulmin = (multy - 1),
        distance = (this->len_ - 13) / mulmin,
        delta = (this->len_ - 13) % mulmin,
        x, y;

    // 当进入循环时，mulmin > 1，因为mulmin=0，1时，distance一定为偶数
    if (distance & 0x1)
        while (--distance)
        {
            delta += mulmin;
            if (delta % (mulmin - 1) == 0)
            {
                delta = delta / (mulmin - 1);
                break;
            }
        }
    for (uint8_t i = 0; i < multy; i++)
        for (uint8_t j = 0; j < multy; j++)
        {
            if ((i == 0 && j == 0) ||
                (i == 0 && j == mulmin) ||
                (i == mulmin && j == 0))
                continue;
            x = 6 + j * distance;
            y = 6 + i * distance;
            if (i > 1)
                y += (i - 1) * delta;
            if (j > 1)
                x += (j - 1) * delta;
            xy.push_back(QRC_XY(x, y));
        }

    return xy;
}

uint16_t QRCode::get15Bit(void)
{
    return g_15Bit[this->ecl_ << 3 | this->mask_];
}

void QRCode::drawFormPatt(void)
{
    uint16_t bch15_5 = this->get15Bit();
    bool tof;
    // 0-5、9-14位
    for (uint8_t i = 0; i < 6; i++)
    {
        tof = (0x1 << i) & bch15_5;
        this->set(this->len_ - i - 1, 8, tof);
        this->set(8, i, tof);
        tof = (0x1 << (14 - i)) & bch15_5;
        this->set(i, 8, tof);
        this->set(8, this->len_ - i - 1, tof);
    }
    // 6、7、8位
    tof = (0x1 << 6) & bch15_5;
    this->set(8, 7, tof);
    this->set(this->len_ - 7, 8, tof);
    tof = (0x1 << 7) & bch15_5;
    this->set(8, 8, tof);
    this->set(this->len_ - 8, 8, tof);
    tof = (0x1 << 8) & bch15_5;
    this->set(7, 8, tof);
    this->set(8, this->len_ - 7, tof);
}

uint32_t QRCode::getVerBit(void)
{
    return g_verBit[this->ver_ - 7];
}

void QRCode::drawVerPatt(void)
{
    uint32_t verBit = this->getVerBit();
    for (uint8_t i = 0; i < 6; i++)
        for (uint8_t j = 0; j < 3; j++)
        {
            bool tof = verBit & (0x1 << (i * 3 + j));
            this->set(this->len_ - 11 + j, i, tof);
            this->set(i, this->len_ - 11 + j, tof);
        }
}

uint16_t QRCode::getCapBit(void)
{
    return g_capBit[this->ver_ - 1][this->ecl_];
}

uint8_t QRCode::getStuff(uint16_t _index)
{
    return g_stuffing[_index & 1];
}

std::vector<uint8_t> QRCode::getDataCode(const std::string &_str)
{
    std::vector<uint8_t> data;
    uint16_t len_ = _str.length(), index = 0, i;
    data.push_back(this->type_ << 4);
    switch (this->type_)
    {
    case bit8:
    {
        if (this->ver_ <= 9) // 8
        {
            // 前4位
            data[0] |= len_ >> 4;
            // 后4位
            data.push_back((0xf & len_) << 4);
            index = 1;
        }
        else // 16
        {
            // 前4位
            data[0] |= len_ >> 12;
            // 中8位
            data.push_back(0xff & (len_ >> 4));
            // 后4位
            data.push_back((0xf & len_) << 4);
            index = 2;
        }

        for (i = 0; i < len_; i++)
        {
            // 前4位
            data[index + i] |= _str[i] >> 4;
            // 后4位
            data.push_back((0xf & _str[i]) << 4);
        }
    }
    break;
        // case ...
    }

    // 填充
    len_ = data.size();
    // 一定要确保大小小于标准长度（查看表7），不然会减出一个非常大的值，后果很严重
    index = this->getCapBit() - len_;
    if (index != 0)
        for (i = 0; i < index; i++)
            data.push_back(this->getStuff(i));

    return data;
}

uint16_t QRCode::getAllBit(void)
{
    return g_allBit[this->ver_ - 1];
}

uint16_t QRCode::getCorCap(void)
{
    return static_cast<uint16_t>((this->ver_ < 27) ? g_corCap[this->ver_ - 1][this->ecl_] : g_corCap[26][this->ecl_]);
}

std::vector<uint8_t> QRCode::getErrDataCode(const std::vector<uint8_t> &_data)
{
    uint16_t
        allBit = getAllBit(),
        corCap = getCorCap(),
        capBit = getCapBit(),
        errLen = allBit - capBit,
        blockErrSize = 2 * corCap,
        blockNum = errLen / blockErrSize,
        blockDataSize = capBit / blockNum,
        blockNum_big = capBit % blockNum,
        blockNum_small = blockNum - blockNum_big;

    const std::vector<uint8_t> &errdata = QRC_Reed_Solomon(_data, blockNum_big, blockNum_small, blockErrSize, blockDataSize);

    return errdata;
}

InPositionPat QRCode::inPositionPattern(QRC_XY _xy)
{
    for (auto cxy : this->alCenterxys_)
        if (cxy.y - 3 < _xy.y && _xy.y < cxy.y + 3)
        {
            if (cxy.x - 2 < _xy.x && _xy.x < cxy.x + 3)
                return (cxy.x == 6) ? left : normal;
            if (_xy.x == cxy.x - 2)
                return normal_left;
        }

    return not_in;
}

QRC_XY QRCode::getDeltaByXY(QRC_XY _xy)
{
    const bool inRight = (_xy.x <= 6) ? (_xy.x % 2) : ((_xy.x - 1) % 2), blockUp = (_xy.x <= 6) ? (_xy.x / 2) % 2 : !(((_xy.x - 7) / 2) % 2);
    QRC_XY delta = {inRight ? -1 : 1, blockUp ? (inRight ? 0 : -1) : (inRight ? 0 : 1)};
    InPositionPat position = this->inPositionPattern(QRC_XY(_xy.x + delta.x, _xy.y + delta.y));

    switch (position)
    {
    case left:
    case normal:
        delta.y += (blockUp) ? -5 : 5;
        break;
    case normal_left:
        delta.x = 0;
        break;
    case not_in:
        break;
    }

    // 上面一条杠
    if (_xy.y + delta.y == 6)
        delta.y += (blockUp) ? -1 : 1;

    // 格式消息下方
    if (_xy.y + delta.y == 8 && (_xy.x + delta.x <= 8 || _xy.x + delta.x >= this->len_ - 8))
    {
        delta = {(_xy.x + delta.x == 8) ? -2 : -1, 0};
        goto RETURN;
    }

    // 向下上没位子
    if (_xy.y + delta.y == this->len_ || _xy.y + delta.y == -1)
    {
        delta = {-1, (_xy.x + delta.x == 10) ? -8 : 0};
        goto RETURN;
    }

    // 版本块 >=7
    if (this->ver_ >= 7)
    {
        // -7-4 // 左下版本消息
        if (_xy.y + delta.y == this->len_ - 11 && _xy.x + delta.x == 5)
        {
            delta = {-1, 0};
        }
        // 右上
        else if (_xy.x + delta.x == this->len_ - 9 && _xy.y + delta.y == 5)
        {
            delta = {-2, -7};
        }
        // 右边是右上的版本信息块
        else if (_xy.x + delta.x == this->len_ - 11)
        {
            if (_xy.y + delta.x < 6)
            {
                delta = {0, 1};
            }
            else if (_xy.y + delta.x == 6)
            {
                delta = {1, 2};
            }
        }

        goto RETURN;
    }
    // 左下
    // 右上和平时无差别
    else
    {
        if ((_xy.y + delta.y) == this->len_ - 8 && _xy.x + delta.x <= 6)
        {
            delta = {-1, 0};
            goto RETURN;
        }
    }
    // 无特殊情况
RETURN:
    return delta;
}

void QRCode::drawStrPatt(const std::vector<uint8_t> _data, const std::vector<uint8_t> _errdata)
{
    uint16_t
        allBit = getAllBit(),
        corCap = getCorCap(),
        capBit = getCapBit(),
        errLen = allBit - capBit,
        blockErrSize = 2 * corCap,
        blockNum = errLen / blockErrSize,
        blockDataSize = capBit / blockNum,
        blockNum_big = capBit % blockNum,
        blockNum_small = blockNum - blockNum_big;
    uint8_t i, j, k, block;
    QRC_XY delta = {0, 0}, xy = {this->len_ - 1, this->len_ - 1};
    uint8_t blcokDelta = 0;

    // 数据块绘图
    // Data 1
    for (i = 0; i < blockDataSize; i++)
        for (j = 0; j < blockNum; j++)
        {
            if (j > blockNum_small)
                blcokDelta = j - blockNum_small;
            else
                blcokDelta = 0;

            block = _data[i + j * blockDataSize + blcokDelta];
            for (k = 0; k < 8; k++)
            {
                this->set(xy, block & (0x1 << (7 - k)));
                delta = getDeltaByXY(xy);
                xy += delta;
            }
        }

    // Data 2 (if existed)
    for (i = 0; i < blockNum_big; i++)
    {
        block = _data[i * (blockDataSize + 1) + (blockNum_small + 1) * blockDataSize];
        for (k = 0; k < 8; k++)
        {
            this->set(xy, block & (0x1 << (7 - k)));
            delta = getDeltaByXY(xy);
            xy += delta;
        }
    }
    // 纠错块绘图
    for (i = 0; i < blockErrSize; i++)
        for (j = 0; j < blockNum; j++)
        {
            block = _errdata[i + j * blockErrSize];
            for (k = 0; k < 8; k++)
            {
                this->set(xy, block & (0x1 << (7 - k)));
                delta = getDeltaByXY(xy);
                xy += delta;
            }
        }
    return;
}

bool QRCode::maskFunc0(QRC_XY _xy) { return (_xy.x + _xy.y) % 2 == 0; }
bool QRCode::maskFunc1(QRC_XY _xy) { return _xy.x % 2 == 0; }
bool QRCode::maskFunc2(QRC_XY _xy) { return _xy.y % 3 == 0; }
bool QRCode::maskFunc3(QRC_XY _xy) { return (_xy.x + _xy.y) % 3 == 0; }
bool QRCode::maskFunc4(QRC_XY _xy) { return ((_xy.x / 2) + (_xy.y / 3)) % 2 == 0; }
bool QRCode::maskFunc5(QRC_XY _xy) { return (_xy.x * _xy.y) % 2 + (_xy.x * _xy.y) % 3 == 0; }
bool QRCode::maskFunc6(QRC_XY _xy) { return ((_xy.x * _xy.y) % 2 + (_xy.x * _xy.y) % 3) % 2 == 0; }
bool QRCode::maskFunc7(QRC_XY _xy) { return ((_xy.x + _xy.y) % 2 + (_xy.x * _xy.y) % 3) % 2 == 0; }
// 获得函数指针
bool (*QRCode::getMaskFunc(void))(QRC_XY _xy)
{
    bool (*func)(QRC_XY _xy) = maskFunc0;
    switch (this->mask_)
    {
    case 0:
        func = maskFunc0;
        break;
    case 1:
        func = maskFunc2;
        break;
    case 2:
        func = maskFunc2;
        break;
    case 3:
        func = maskFunc3;
        break;
    case 4:
        func = maskFunc4;
        break;
    case 5:
        func = maskFunc5;
        break;
    case 6:
        func = maskFunc6;
        break;
    case 7:
        func = maskFunc7;
        break;
    }
    return func;
}

bool QRCode::getMask(QRC_XY _xy)
{
    return this->getMaskFunc();
}

bool QRCode::getMask(uint8_t _x, uint8_t _y)
{
    return this->getMask(QRC_XY(_x, _y));
}

void QRCode::drawMask(void)
{
    bool (*maskFunc)(QRC_XY xy) = getMaskFunc();
    for (uint8_t i = 0; i < len_; i++)
        for (uint8_t j = 0; j < len_; j++)
            this->set(i, j, this->get(i, j) != maskFunc(QRC_XY(i, j)));
}

const uint8_t *QRCode::getGenPolyExpByBlockErrSize(uint16_t _blockErrSize)
{
    // 为了获得多项式在全局变量的位置，多项式长度就是blockSize
    uint8_t index = 0;
    switch (_blockErrSize)
    {
    case 30:
        index += 29;
    case 28:
        index += 27;
    case 26:
        index += 25;
    case 24:
        index += 23;
    case 22:
        index += 21;
    case 20:
        index += 19;
    case 18:
        index += 18;
    case 17:
        index += 17;
    case 16:
        index += 16;
    case 15:
        index += 14;
    case 13:
        index += 11;
    case 10:
        index += 8;
    case 7:
        break;
    default:
        break;
    }
    return &g_generator_polynomial_exp[index];
}

uint8_t QRCode::getAlphaByExp(size_t _exp)
{
    uint16_t result = 1, i;
    _exp %= 255;
    for (i = 0; i < _exp; i++)
    {
        result *= 2;
        if (result > 255)
            result ^= 285;
    }
    return (uint8_t)result;
}

uint8_t QRCode::getAlphaByInt(uint8_t _int)
{
    return g_alpha_int_is_index[_int - 1];
}

std::vector<uint8_t> QRCode::QRC_Reed_Solomon(const std::vector<uint8_t> &_data, uint16_t _blockNum_big, uint16_t _blockNum_small, uint16_t _blockErrSize, uint16_t _blockDataSize)
{
    std::vector<uint8_t> errdata;
    // 生成多项式
    const uint8_t *poly = getGenPolyExpByBlockErrSize(_blockErrSize);
    // 一个大小为大块大小的块
    uint8_t *blockData = new uint8_t[_blockErrSize + _blockDataSize + 1];
    uint16_t i, j, k;

    // 小块
    for (i = 0; i < _blockNum_small; i++)
    {
        // 进位,补零
        for (j = 0; j < _blockDataSize; j++)
            blockData[j] = _data[j + i * _blockDataSize];
        for (j = 0; j < _blockErrSize; j++)
            blockData[j + _blockDataSize] = 0;

        // 除法
        for (j = 0; j < _blockDataSize; j++)
            if (blockData[j] != 0)
            {
                uint8_t deltaAlpha = this->getAlphaByInt(blockData[j]);
                for (k = 0; k < _blockErrSize + 1; k++)
                    blockData[j + k] ^= this->getAlphaByExp(static_cast<size_t>(poly[k] + deltaAlpha));
            }

        for (j = 0; j < _blockErrSize; j++)
            errdata.push_back(blockData[_blockDataSize + j]);
    }
    // 大块
    for (i = 0; i < _blockNum_big; i++)
    {
        for (j = 0; j < _blockDataSize + 1; j++)
            blockData[j] = _data[j + i * (_blockDataSize + 1) + _blockNum_small * _blockDataSize];
        for (j = 0; j < _blockErrSize; j++)
            blockData[j + _blockDataSize + 1] = 0;

        // 除法
        for (j = 0; j < _blockDataSize + 1; j++)
            if (blockData[j] != 0)
            {
                uint8_t deltaAlpha = this->getAlphaByInt(blockData[j]);
                for (k = 0; k < _blockErrSize + 1; k++)
                    blockData[k + j] ^= this->getAlphaByExp(static_cast<size_t>(poly[k] + deltaAlpha));
            }
        for (j = 0; j < _blockErrSize; j++)
            errdata.push_back(blockData[_blockDataSize + j + 1]);
    }
    delete[] blockData;

    return errdata;
}

uint8_t QRCode::getLen(void)
{
    return this->len_;
}
