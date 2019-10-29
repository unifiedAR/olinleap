//
// Created by duncan on 10/29/19.
//

#ifndef SERVER_POINTCLOUDPACK_H
#define SERVER_POINTCLOUDPACK_H
#include <iostream>

class pointCloudPack {
    public:
        std::string pointString;

        void addXYZPoint(float xyz[3]);
        void clearPointString();
        char *returnMessageStr();
        long returnMessageLen();
};


#endif //SERVER_POINTCLOUDPACK_H
