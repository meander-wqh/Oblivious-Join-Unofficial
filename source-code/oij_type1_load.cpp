#include <cmath>
#include <vector>
#include <chrono>
#include <time.h>
#include "ObliIndexJoin.h"
#include "PathORAM.h"

//bash scripts/run_oij_type1_load.sh 1 0.05x 1
int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: ./oij_type1_load <mode> <scale> <outsourced_height>\n");
        return -1;
    }
    
    const uint32_t mode = atoi(argv[1]);
    const std::string method = "obj";
    std::string scale = std::string(argv[2]);
    const uint32_t outsourced_height = atoi(argv[3]);
    std::string prefix = getCollectionPrefix(mode, method, scale, outsourced_height);
    std::string dst = "oram." + prefix;
    std::string meta_prefix = "metas/" + prefix;
    std::cout<<"prefix: "<<prefix<<std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    ObliIndexJoin <PathORAM>* oij = new ObliIndexJoin <PathORAM> (mode, scale, outsourced_height, dst, meta_prefix);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    auto time = diff.count();
    
    printf("\n----------------------------------------\n");
    printf("Loading Time: %.6lf\n", time);
    printf("Data Block Number: %u\n", oij->getDataBlockNum());
    size_t server_size = oij->getServerSize();
    printf("Server Size is %lf MB\n", (double)server_size / (1 << 20));
    size_t client_size = oij->getClientSize();
    printf("Client Size is %lf MB\n", (double)client_size / (1 << 20));
    printf("\n----------------------------------------\n");
    
    delete oij;
    return 0;
}
