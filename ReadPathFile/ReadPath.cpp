#pragma once

#include"../ReadPathfile/ReadPath.h"

void ReadPath::ReadPathfile(const char* cfilename) {
    FILE* pFile;
    long lSize;
    char* buffer;
    size_t result;

    /* 若要一个byte不漏地读入整个文件，只能采用二进制方式打开 */
    fopen_s(&pFile, cfilename, "rb");
    if (pFile == NULL)
    {
        fputs("File error", stderr);
        exit(1);
    }

    /* 获取文件大小 */
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    /* 分配内存存储整个文件 */
    buffer = (char*)malloc(sizeof(char) * lSize);
    if (buffer == NULL)
    {
        fputs("Memory error", stderr);
        exit(2);
    }

    /* 将文件拷贝到buffer中 */
    result = fread(buffer, 1, lSize, pFile);
    if (result != lSize)
    {
        fputs("Reading error", stderr);
        exit(3);
    }


    /* 结束演示，关闭文件并释放内存 */
    fclose(pFile);

    ios::sync_with_stdio(false);



    ReadASCII(buffer);

    free(buffer);
    return;
}

bool ReadPath::ReadASCII(const char* buffer) {
    //CricleNum;
    float x, y, z;
    string Position;
    stringstream ss(buffer);
    ss >> CricleNum >> PosNum;

    while (CricleNum) {
        while (PosNum) {
            ss >> x >> y >> z;
            CutterPath.push_back(glm::vec3(x, y, z));
            PosNum--;
        }
        ss >> PosNum;
       // cout << "PosNum: " << PosNum;
        CricleNum--;
    }
    

    return true;
}
