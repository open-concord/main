#include "crypto++/sha.h"

#include <string>
#include <iostream>
#include <fstream>

#include "../../inc/hash.h"
#include "../../inc/b64.h"

using namespace CryptoPP;
// read from file or raw      
std::string calc_hash (bool use_disk, std::string target) {
    // if use_disk is true, target is a file name
    // if use_disk isn't than it's raw text

    std::string outstr;

    if (use_disk) { // target is filename (disk)
        std::ifstream fl(target);
        fl.seekg(0, std::ios::end);
        size_t len = fl.tellg();
        char *ret = new char[len];
        fl.seekg(0, std::ios::beg);
        fl.read(ret, len);
        fl.close();
        outstr = ret;
    } else { // target is raw message (mem)
        outstr = target;
    }

    byte const* pbData = (byte*) outstr.data();
    unsigned int nDataLen = outstr.size();
    byte abDigest[SHA256::DIGESTSIZE];

    SHA256().CalculateDigest(abDigest, pbData, nDataLen);

    return b64_encode(std::string((char*)abDigest));
};

std::string gen_trip(size_t quad_chars) {
    return b64_encode(gen_string(quad_chars*3));
}