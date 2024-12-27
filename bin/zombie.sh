#!/bin/bash
ps -eo ppid,pid,stat,cmd | grep ' Z' 
#ps -eo ppid,pid,stat,cmd | grep ' Z' | awk '{print $1}' | xargs kill -9
#ps aux | grep './minishell' | grep -v grep | awk '{print $2}' | xargs kill -9
