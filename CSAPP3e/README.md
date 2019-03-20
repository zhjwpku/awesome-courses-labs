All the lab will be down in the docker container

1. build the docker image

```
docker build -t zhjwpku/csapp3e .
```

2. run container as a deamon

```
# use absolute path to pass a host directory
# the --cap-add=SYS_PTRACE option is for running gdb in docker
docker run --cap-add=SYS_PTRACE -dit --name csapp3e -v /Users/zhjwpku/fancy/awesome-courses-labs/CSAPP3e/solutions:/opt/csapp3e zhjwpku/csapp3e /bin/bash
# login to the container
docker exec -it csapp3e /bin/bash
```
