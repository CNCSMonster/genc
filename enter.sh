#!/bin/bash

# docker exec -it  klee /bin/bash
# 改成 直接进入文件后指定路径
docker exec -it -w /home/klee/workplace  genc /bin/bash