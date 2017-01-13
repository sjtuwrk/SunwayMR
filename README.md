# SunwayMR

A parallel computing framework written in C++ more than 8000 lines code by reaserchers from School of electronic information and electrical engineering, Shanghai Jiao Tong University. We reference much on Spark's RDD design. 

The paper of **SunwayMR: A Distributed Parallel Computing Framework with Convenient Data-intensive Applications Programming** has been completed accepted by **Future Generation Computer System (CCF Journal)** in 12 Jan 2017.


* Now, we have provided application demos videos in the "demos" file of the project.


## Dependencies

You will need `gcc/g++` when using GNU `make`.

## Usage

* Download and make source **on each node**

```bash
    make
```

* Start SunwayMR resource manager **on each node**, while specifying `master IP`, `master port`, `shared threads of node`, `shared memory of node`

```bash
    ./sunwaymr -t 192.168.1.85 19113 4 1024
```

* Now, you can run example program **on master** (in a new terminal)

```bash
    ./sunwaymr -a examples/SunwayMRPi.cpp
```

* See results in listening terminal 
