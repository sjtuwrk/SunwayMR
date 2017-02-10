## Introduction of SunwayMR

Managing servers integration to realize distributed data computing framework is an important concern. Regardless
of the underlying architecture and the actual distributed system’s complexity, such framework gives programmers an
abstract view of systems to achieve variously data-intensive applications. However, some state-of-the-art frameworks
need too much library dependencies and parameters configuration, or lack extensibility in application programming.
Moreover, general framework’s precise design is a nontrivial work, which is fraught with challenges of task scheduling,
message communication and computing efficiency, etc. To address these problems, we present a general, scalable and
programmable parallel computing framework called SunwayMR, which only needs GCC/G++ environment. The on-going SunwayMR 
is able to run on Sunway TaihuLight processors (National Computing Center in Wuxi of China: http://www.nsccwx.cn/) now.

A parallel computing framework written in C++ more than 8000 lines code by reaserchers from School of Electronic Information and Electrical Engineering, Shanghai Jiao Tong University. We reference much on Spark's RDD design. Now, we have provided application demos and videos in the "demos" file of the project. 

* Sunway TaihuLight： The Sunway TaihuLight (Chinese: 神威·太湖之光) is a Chinese supercomputer which, as of June 2016, is ranked number one in the TOP500 list as the fastest supercomputer in the world, with a LINPACK benchmark rating of 93 petaflops. This is nearly three times as fast as the previous holder of the record, the Tianhe-2, which ran at 34 petaflops. As of June 2016, it is also ranked as the third most energy-efficient supercomputer in TOP500, with an efficiency of 6,051.30 MFLOPS/W. It was designed by the National Research Center of Parallel Computer Engineering & Technology (NRCPC) and is located at the National Supercomputing Center in Wuxi in the city of Wuxi, in Jiangsu province, China. (https://en.wikipedia.org/wiki/Sunway_TaihuLight)


## Teamers

Renke Wu (sjtuwrk@sjtu.edu.cn), Yanyan Shen (yanyanshen14@gmail.com), Peng Yu (yuzhiyu3@sjtu.edu.cn), Kai Shen (knshen@sjtu.edu.cn), Qiuwei Shi, Bowen Zhang, Yijie Mei, Yanan Xu, Haojie Zhou (The State Key Laboratory of Mathematic Engineering and Advance Computing, Jiangnan Institute of Computing Technology)

## Accepted Papers

1: * The paper of **SunwayMR: A distributed parallel computing framework with convenient data-intensive applications programming**  ( http://www.sciencedirect.com/science/article/pii/S0167739X17300584 ) has been completed accepted by **Future Generation Computer System (Impact Factor: 2.430)** in **12 Jan 2017**. (Authors: Renke Wu, Linpeng Huang, Peng Yu, Haojie Zhou.)

2: * The paper of **Meta-model evolution with self-adaptation: An empirical development approach for distributed parallel computing framework** (http://ieeexplore.ieee.org/search/searchresult.jsp?queryText=Renke%20Wu&newsearch=true ) has been completed accepted by **TrustCom-BigDataSE-ISPA 2016** in **17 June 2016**. (Authors: Renke Wu, Linpeng Huang, Peng Yu, Kai Shen, Qiuwei Shi and Haojie Zhou.)

3: * The paper of **Multicast routing tree for sequenced packet transmission in software-defined networks** 
(http://dl.acm.org/citation.cfm?id=2993721&CFID=898883172&CFTOKEN=57917688 ) has been completed accepted by **Internetware '16**. (Authors: Peng Yu, Renke Wu, Haojie Zhou, Haibo Yu, Yuting Chen, Hao Zhong)

4: * The paper of **A failure detection solution for multiple QoS in data center networks** ( http://dl.acm.org/citation.cfm?id=2993728&CFID=898883172&CFTOKEN=57917688 ) has been completed accepted by **Internetware '16**.
(Authors: Kai Shen, Renke Wu, Haojie Zhou, Haibo Yu, Hao Zhong)

## Software Copyrights & Talent

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

## Programming Interface

![image](https://github.com/sjtuwrk/SunwayMR/blob/master/testData/platform.png)

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

## Results

To ensure ease-of-use, open Application Programming Interface (API) excerpts can be invoked by various of applications with fewer handwritten code than OpenMPI/MPI. We conduct extensively experimental studies to evaluate the performance of SunwayMR over real-world datasets. Results indicate that SunwayMR (runs on 16 computational nodes) outperforms Spark in various applications, and has good scaling with data sizes, nodes and threads. 

## Fund Support
This work is partially supported by the National HighTechnology Research and Development Program of China under Grant No.2014AA01A301, Grant No.2015AA015303 and the National Natural Science Foundation of China (NSFC) under Grant No.61472241.
