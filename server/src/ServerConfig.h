#pragma once
#include <QString>
#include <cstdint>

struct ServerConfig {
    int port = 5555;
    QString redisHost = "127.0.0.1";
    uint16_t redisPort = 6379;
    int redisDb = 0;
    QString redisPassword;
    int redisPoolSize = 4;
};
