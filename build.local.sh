#! /bin/bash

set -e

PROJECT_DIR=$(cd $(dirname $0); pwd -P)
DOCKER_IMAGE="images.br007.top/cpp/builder/libc-2.17:2.0.0"
INSTALL_PREFIX=${PROJECT_DIR}/target

if [ -z ${VERSION} ]; then
    if [ `git describe --tags --abbrev=0` ]; then
        VERSION=`git describe --tags --abbrev=0`
    else
        VERSION=0.0.0.0-alpha1
    fi
fi

echo ${VERSION}

# 是否跑在 docker 里面，是：0   否：1
isRunInDocker() {
    if [ -f "/.dockerenv" ]; then
        return 0
    fi
    if hostname | grep -E "^[a-f0-9]{12}$"  > /dev/null; then
        return 0
    fi
    if [ "$(hostname)" = "buildkitsandbox" ] ; then
        return 0
    fi
    if [ -f "/proc/self/cgroup" ];then
        docker_count=`cat /proc/self/cgroup|grep docker |wc -l`
        if [ ${docker_count} -eq "0" ]; then
            return 1
        fi
        return 0
    else
        return 1
    fi
}

buildInDocker() {
    g++ --version
    mkdir -p build
    cd build
    cmake -DBONREE_SDK_VERSION=$VERSION -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX ..
    make -j4
    cd -
}

build() {
    echo "start build..."
    if isRunInDocker; then
        echo "buildInDocker"
        buildInDocker
    else
        echo "run in node"
        docker run --rm -v ${PROJECT_DIR}:/work -w /work \
            $DOCKER_IMAGE \
            bash -c "bash build.local.sh"
            
        cp -rf api/* /vagrant/code/netcoreagent-code/src/cppprofiler/c_sdk/src/opentelemetry-cpp/api/
        cp -rf sdk/*  /vagrant/code/netcoreagent-code/src/cppprofiler/c_sdk/src/opentelemetry-cpp/sdk/
        cp -rf exporters/*  /vagrant/code/netcoreagent-code/src/cppprofiler/c_sdk/src/opentelemetry-cpp/exporters/
    fi
}

main() {
  build
}

main
