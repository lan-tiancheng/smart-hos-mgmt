# 智慧医疗管理系统（Qt + Redis 最小骨架）

本项目提供一个可编译运行的最小骨架：
- 服务端：Qt QTcpServer + redis-plus-plus/hiredis，提供注册/登录（auth.register/auth.login）
- 客户端：Qt Widgets（患者端），可连接服务端完成注册与登录

## 依赖
- Ubuntu 20.04/22.04
- Qt 5.12+（qtbase5-dev 等）
- CMake 3.16+
- g++ 9+
- Redis Server
- hiredis, redis-plus-plus

## 安装
```bash
sudo apt update
sudo apt install -y build-essential cmake git qtbase5-dev qtdeclarative5-dev libqt5sql5-sqlite
sudo apt install -y redis-server libhiredis-dev pkg-config
# 安装 redis-plus-plus（C++ Redis 客户端）
if ! pkg-config --exists redis++; then
  git clone https://github.com/sewenew/redis-plus-plus.git
  cd redis-plus-plus && mkdir -p build && cd build
  cmake .. -DREDIS_PLUS_PLUS_BUILD_TEST=OFF -DREDIS_PLUS_PLUS_BUILD_SHARED=ON
  make -j && sudo make install && sudo ldconfig
  cd ../..
fi
```

## 构建
```bash
mkdir -p build && cd build
cmake ..
cmake --build . -j
```

## 运行（终端1：服务端）
```bash
./server/med_server
# 默认读取 ./config/server_config.json 连接 Redis
```

## 运行（终端2：患者端）
```bash
./client-patient/patient_client
# 默认连接 127.0.0.1:5555
```

## 测试流程
- 在患者端界面输入邮箱与密码：
  - 点“注册”完成注册（默认 role=patient）
  - 再点“登录”，成功后进入占位主页

## 协议（行分隔 JSON）
- 请求：`{"action":"auth.register","data":{"email":"a@b.com","password":"123456","role":"patient","name":"张三"}}`
- 响应 OK：`{"ok":true,"action":"auth.register","data":{"user_id":1,"role":"patient"}}`
- 响应错误：`{"ok":false,"action":"auth.login","error_code":401,"error_message":"invalid credentials"}`

## Redis 逻辑设计（最小集）
- 生成用户ID：`INCR counters:user:id`
- 邮箱到 ID 索引（唯一）：`SETNX u:email:<email> <user_id>`
- 用户 Hash：`HSET user:<id> email role name pass_hash salt created_at`

## 路线图（后续）
- M2 数据模型（Redis）：appointments、medical_records、prescriptions、attendance、messages 等
- M3 患者端：医生列表、挂号与预约、处方/医嘱查看、个人信息修改
- M4 医生端：预约患者、诊断与医嘱、处方开具、考勤
- M5 聊天：Qt WebSockets + Redis Pub/Sub 或 Streams
- M6 图表：Qt Charts 展示数据
- M7 安全与部署：鉴权（JWT/Session）、AOF/RDB、systemd、反向代理与证书

---