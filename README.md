# SunwayMR

A parallel computing framework written in C++ more than 8000 lines code by reaserchers from School of electronic information and electrical engineering, Shanghai Jiao Tong University. We reference much on Spark's RDD design. Now, we have provided application demos videos in the "demos" file of the project. 

## Accepted Papers

* The paper of **SunwayMR: A Distributed Parallel Computing Framework with Convenient Data-intensive Applications Programming** (http://authors.elsevier.com/TrackPaper.html?trk_article=FUTURE3300&trk_surname=Wu) has been completed accepted by **Future Generation Computer System (Impact Factor: 2.430)** in **12 Jan 2017**.

* The paper of **Meta-model Evolution with Self-Adaptation: An Empirical Development Approach for Distributed Parallel Computing Framework** has been completed accepted by **TrustCom-BigDataSE-ISPA 2016** in **17 June 2016**.

## Software copyrights & Talent

Achieved one talent & two software copyrights.

## Team

Renke Wu (sjtuwrk@sjtu.edu.cn), Yanyan Shen, Peng Yu (yuzhiyu3@sjtu.edu.cn), Kai Shen, Qiuwei Shi, Bowen Zhang, Yijie Mei, Yanan Xu

## Dependencies

You will need `gcc/g++` when using GNU `make`.

## Usage

* Download and make source **on each node**

```bash
    make
```

* Start SunwayMR resource manager **on each node**, while specifying `master IP`, `master port`, `shared threads of node`, `shared memory of node`

```bash
    ./sunwaymr -t 11 MASTER IP MASTER PORT NUMBER OF THREADs SIZE OF MEMORY &
    such as **./sunwaymr -t 192.168.1.85 19113 4 1024**
```

* Now, you can run example program **on master** (in a new terminal)

```bash
    ./sunwaymr -a APPLICATION &
    such as **./sunwaymr -a examples/SunwayMRPi.cpp**
```

* See results in listening terminal 
