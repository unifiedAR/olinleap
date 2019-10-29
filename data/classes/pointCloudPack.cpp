//
// Created by duncan on 10/29/19.
//

#include "pointCloudPack.h"
#include <iostream>

void pointCloudPack::addXYZPoint(float xyz[3]) {
    for (int i=0; i < 3; i++) {
        pointCloudPack::pointString.append(std::to_string(xyz[i]));
        i < 3 ? pointCloudPack::pointString.append(",") :  pointCloudPack::pointString.append(";");
    }
}

void pointCloudPack::clearPointString() {
    pointCloudPack::pointString.clear();
}

char *pointCloudPack::returnMessageStr() {
    return const_cast<char *>(pointCloudPack::pointString.c_str());
}

long pointCloudPack::returnMessageLen() {
    return pointCloudPack::pointString.length();
}
