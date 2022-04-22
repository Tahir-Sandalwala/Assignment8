# Scalar Pipelined Processor Implementation

## Instructions

```shell
# Cloning
git clone https://github.com/Tahir-Sandalwala/Assignment8.git
cd Assignment8

# Build
mkdir build
cd build
cmake ..
make

# Setup
cp $INPUT/ICache.txt $INPUT/DCache.txt $INPUT/RF.txt .  # where $INPUT is the directory containing the input files

# Run
./PipelinedProcessor | tee Output.txt

# Results
cat DCache.out.txt RF.out.txt Output.txt
```

## Authors

Dhruv Maroo (CS20B025)
Tahir Sandalwala (CS20B078)
