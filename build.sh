set -e

mkdir -p build
cd build 
cmake ..
make 
cd -

cp -rf api/* /vagrant/code/netcoreagent-code/src/cppprofiler/c_sdk/src/opentelemetry-cpp/api/
cp -rf sdk/*  /vagrant/code/netcoreagent-code/src/cppprofiler/c_sdk/src/opentelemetry-cpp/sdk/
