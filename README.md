# USP Assignment
  
  In this project, I have created a server-client based application to demonstrate the application of orphaned processes. 

## Getting Started

Download or clone the given repository

### Prerequisites

Ubuntu must be installed on your system.

Install the gcc compiler to run the code.

### Installing

Install the gcc compiler using the following steps:

```

sudo apt update
sudo apt install build-essential
sudo apt-get install manpages-dev
``````

And to verify installation use:

```
gcc --version

```

## Running the tests

Now inorder to run the Server use the following command:

```
gcc Server.c
./a.out
```
Similarly, inorder to run a client for the server use the following commands:
```
gcc Client.c
./a.out
```
Then type in two integers with space separated values.

Output on server side:

![Image contains the output that would be displayed on Server side](https://github.com/Nityam00/USPAssignment/blob/master/Server.jpeg)

Output on Client Side:



![Image contains the output that would be displayed on Server side](https://github.com/Nityam00/USPAssignment/blob/master/USPClient.jpeg)




## Deployment

In order to deploy it on the local machine firstly create a new terminal window and run the Server.c using the method stated above. Create a new terminal in which you would display the client side method for the same. Then run the file Client.c and enter two integers a and b in the form a space b Example:
```
2 1
```
And the desired output would be seen on the page of both the Server and the client
In case the value of b is 0. A signal is caught as SIGFPE and the server handles it appropriately.
The code also takes care in case a SIGCHLD or SIGINT is encountered

## Real Applications:

Many a times it is observed that the server crashes abruptly and the clients are unable to access them. In order for them to be accessible even after crashing my program tries handling them For example, if you press Ctrl-C on the Server side, the program still continues to run denoting that despite a creash in the server the signals handle the code properly.

## Built With

* [Ubuntu](https://ubuntu.com/) - The OS used
* [Gcc](https://gcc.gnu.org/) -The compiler used
## Authors

* **[Nityam Agarwal](https://github.com/Nityam00)**  
* **Parakh Shah**  
* **Poorvi Seth**  

