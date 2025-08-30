#ifndef DATATYPE_H
#define DATATYPE_H

#include "circularbuf.h"
#include <QString>

typedef struct Client{
    int ecgI;
    int ecgII;
    int ecgIII;
    int ecgAVL;
    int ecgAVR;
    int ecgAVF;
    int ecgV1;
    int ecgV2;
    int ecgV3;
    int ecgV4;
    int ecgV5;
    int ecgV6;

}client;

typedef struct Service{
    CircularBuf *ecg_data_I;
    CircularBuf *ecg_data_II;
    CircularBuf *ecg_data_III;
    CircularBuf *ecg_data_AVL;
    CircularBuf *ecg_data_AVR;
    CircularBuf *ecg_data_AVF;
    CircularBuf *ecg_data_V1;
    CircularBuf *ecg_data_V2;
    CircularBuf *ecg_data_V3;
    CircularBuf *ecg_data_V4;
    CircularBuf *ecg_data_V5;
    CircularBuf *ecg_data_V6;
}service;

typedef struct User{
    QString id;
    QString name;
    QString age;
    QString sex;
    QString career;
    QString history;
}user;
#endif // DATATYPE_H
