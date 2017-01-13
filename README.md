## Introduction

A parallel computing framework written in C++ more than 8000 lines code by reaserchers from School of Electronic Information and Electrical Engineering, Shanghai Jiao Tong University. We reference much on Spark's RDD design. Now, we have provided application demos videos in the "demos" file of the project. 

## Team

Renke Wu (sjtuwrk@sjtu.edu.cn), Yanyan Shen, Peng Yu (yuzhiyu3@sjtu.edu.cn), Kai Shen, Qiuwei Shi, Bowen Zhang, Yijie Mei, Yanan Xu

## Accepted Papers

* The paper of **Renke Wu, Linpeng Huang, Peng Yu, Haojie Zhou. SunwayMR: A Distributed Parallel Computing Framework with Convenient Data-intensive Applications Programming** (http://authors.elsevier.com/TrackPaper.html?trk_article=FUTURE3300&trk_surname=Wu) has been completed accepted by **Future Generation Computer System (Impact Factor: 2.430)** in **12 Jan 2017**.

* The paper of **Renke Wu, Linpeng Huang, Peng Yu, Kai Shen, Qiuwei Shi and Haojie Zhou. Meta-model Evolution with Self-Adaptation: An Empirical Development Approach for Distributed Parallel Computing Framework** has been completed accepted by **TrustCom-BigDataSE-ISPA 2016** in **17 June 2016**.

## Software copyrights & Talent

Achieved one talent & two software copyrights.

## Architecture

The HPC clustering system for running SunwayMR ought to include several computing nodes and desktops, etc., as depicted in Fig. 1. Parallel machines are networked together through a high speed network (e.g., GigaNet, InfiniBand). Such design constructs the foundation for the framework’s running environment. In order to provide remote access and control the cluster, the architecture of heterogeneous clustering system is organized in masterslaves paradigm, as shown in Fig. 2. The master node (consists of at least one CPU core) is responding for managing the whole clustering system, setting up every service in system management, and receiving the jobs from the client of the clustering system. Before running any application, SunwayMR kernel code is sent from master node and deployed in each slave node in advance.

Execution overview. Fig. 3 depicts the main data computing process in SunwayMR, The process in SunwayMR can be formally represented as: Process := (U, g)+× Sin ⇒ Sout, where Sin is the initial input data, Sout is the result data, g represents the running code, U is the computing nodes set. Phase 1: SunwayMR gets the user’s shell commands to start each server’s listening port for preparing to execute jobs. Phase 2: After data has been received, data set is divided into several parts by a distributed memory dataset managing mechanism. Phase 3: It gets application execution commands through user terminal in master node. Phase 4: All nodes begin to execute tasks and send results back to master node.

![image](https://github.com/sjtuwrk/SunwayMR/blob/master/testData/pic.png)

The layered software architecture Today’s popular software architecture generally follows the loosely-coupled layered manner. Likely, SunwayMR is the layered software architecture stack, The framework’s code can be divided into mainly three abstracted layers totally from the perspective of software engineering: 

* (1) the upper code layer provides interfaces for application programming; 

* (2) the bottom code layer manages the computing hardware resource; 

* (3) the middle code layer block mainly connects link between the preceding and following role. 

Thus, it not only improves the reusability of software architecture and flexibility in programming specifications, but also improves the complicated system’s maintainability. Before the programmers develop corresponding dataintensive applications, they should be familiar with this distributed parallel computing framework to a large extent. That is, they ought to know the open programmable APIs for programming, rather than framework’s explicit functions from inner design to implementation. In addition, SunwayMR uses an intuitive interface for launching and managing programs on distributed system. SunwayMR allows users easily to launch any pre-existing command to drive application program for data processing.

## Contributions

To summarize, the main contributions of our work include:
* We first present and discuss the framework’s design. Based on clustering system’s two-level (master-slaves) hierarchy architecture, a distributed dataset managing mechanism organizes data into partitions as data computing unit sets (DCUS). More critically, task organization, job/task scheduling and message communication are given out subsequently.
* We present system optimizations of thread-level stringstream to accelerate information communication between nodes substantially, and lightweight fault tolerance to solve reliability problem.
* We make an implementation of SunwayMR, which provides advantages of both ease-of-use and extensibility. More data-intensive applications can be achieved quickly by invoking public high-level APIs from lower layers of the framework, so as to write less low-leve 
code.
* We conduct extensively empirical studies to evaluate the performance of SunwayMR using various applications and real datasets. Experimental results demonstrate that our solution achieves better performance in efficiency, speedup and execution time, compared with Spark framework.

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
