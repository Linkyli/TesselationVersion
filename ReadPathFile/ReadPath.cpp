#pragma once

#include"../ReadPathfile/ReadPath.h"

void ReadPath::ReadPathfile(const char* cfilename) {
    FILE* pFile;
    long lSize;
    char* buffer;
    size_t result;

    /* ��Ҫһ��byte��©�ض��������ļ���ֻ�ܲ��ö����Ʒ�ʽ�� */
    fopen_s(&pFile, cfilename, "rb");
    if (pFile == NULL)
    {
        fputs("File error", stderr);
        exit(1);
    }

    /* ��ȡ�ļ���С */
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    /* �����ڴ�洢�����ļ� */
    buffer = (char*)malloc(sizeof(char) * lSize);
    if (buffer == NULL)
    {
        fputs("Memory error", stderr);
        exit(2);
    }

    /* ���ļ�������buffer�� */
    result = fread(buffer, 1, lSize, pFile);
    if (result != lSize)
    {
        fputs("Reading error", stderr);
        exit(3);
    }


    /* ������ʾ���ر��ļ����ͷ��ڴ� */
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
