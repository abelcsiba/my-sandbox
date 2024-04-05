
#ifndef __CertEnv_HH__
#define __CertEnv_HH__

#include <string>

class CertEnv {
public:
    static const std::string CERT_PATH;
    static const std::string KEY_PATH;
    static const std::string CA_PATH;
};

const std::string CertEnv::CERT_PATH = "NGBE_CERT";
const std::string CertEnv::KEY_PATH = "NGBE_KEY";
const std::string CertEnv::CA_PATH = "NGBE_CA";

#endif