#include <qpdf/QPDFStreamFilter.hh>
#include <qpdf/Pl_AES_PDF.hh>
#include <memory>

#ifndef SF_JDDRMDECODE_HH
#define SF_JDDRMDECODE_HH

const size_t KEY_LEN = 32;
const uint8_t KEY[KEY_LEN] = {
  0xca, 0xc4, 0xb0, 0x80,
  0xec, 0xe8, 0x1f, 0x97,
  0x64, 0xb8, 0xdd, 0xae,
  0x8c, 0xa4, 0x4e, 0xe7,
  0x81, 0xd1, 0xb9, 0x45,
  0xb3, 0xa1, 0x18, 0x58,
  0xa7, 0xe9, 0xbe, 0x75,
  0xbf, 0xc5, 0x8a, 0x1b,
};

const size_t IV_LEN = 16;
const uint8_t IV[IV_LEN + 1] = "0000000000000000";

class SF_JDDRMDecode : public QPDFStreamFilter
{
  public:
    SF_JDDRMDecode() = default;
    virtual ~SF_JDDRMDecode() = default;

    virtual Pipeline* getDecodePipeline(Pipeline* next) override
    {
        this->pipeline = std::make_shared<Pl_AES_PDF>(
            "JDDRM decode", next, false, KEY, KEY_LEN);
        this->pipeline->setIV(IV, IV_LEN);
        return this->pipeline.get();
    }

    static std::shared_ptr<QPDFStreamFilter> factory()
    {
        return std::make_shared<SF_JDDRMDecode>();
    }

  private:
    std::shared_ptr<Pl_AES_PDF> pipeline;
};

#endif // SF_ASCIIHEXDECODE_HH
