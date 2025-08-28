#!/usr/bin/env bash
set -euo pipefail
sudo apt update
sudo apt install -y build-essential cmake git libhiredis-dev pkg-config
if ! command -v redis-server >/dev/null 2>&1; then
  sudo apt install -y redis-server
fi
if ! pkg-config --exists redis++; then
  tmpdir=$(mktemp -d)
  trap 'rm -rf "$tmpdir"' EXIT
  cd "$tmpdir"
  git clone https://github.com/sewenew/redis-plus-plus.git
  cd redis-plus-plus && mkdir -p build && cd build
  cmake .. -DREDIS_PLUS_PLUS_BUILD_TEST=OFF -DREDIS_PLUS_PLUS_BUILD_SHARED=ON
  make -j
  sudo make install
  sudo ldconfig
fi
echo "redis-plus-plus installed."
