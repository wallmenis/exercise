#!/bin/bash

mkdir -p backups

cp logs/app.log backups/app.log.$(date +%Y-%m-%d.%H_%M_%S.%N)
echo > logs/app.log